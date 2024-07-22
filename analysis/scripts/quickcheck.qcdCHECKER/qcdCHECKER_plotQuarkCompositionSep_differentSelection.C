#define LOG(format, args...)     fprintf(stderr, "---------------------debug-    %s  \n  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)

const int NMCSEP = 9; // QCD madgraph samples are separated into 9 HT slices.
const int NUMBIN = 25;
const int colors[] = {2,46,42,49,32,8,3,4,38};
const int marks[] = {33,34, 26,27,28,30, 24,25};
static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000});
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
int jetptBin_100CUT[NMCSEP] = {7,16,16,18,20,21,22,23,24};
int jetptBin_10CUT[NMCSEP] = {11,20,20,21,22,23,24,24,24};
int jetptBin_tenToMinusFiveCut[NMCSEP] = {10,10,15,17,20,20,22,23,24};

void LowStatEntryRemoval(TH1* hh, int iMC)
{
    for ( int ibin = hh->GetNbinsX(); ibin >= jetptBin_tenToMinusFiveCut[iMC]; --ibin )
        hh->SetBinContent(ibin,0.);
}
TH1* histFactory_MergeMCSlices(TDirectoryFile* ifile, const char* nameTEMPLATE)
{
    std::vector<TH1*> loadhists(NMCSEP, nullptr);
    for ( int i=0;i<NMCSEP;++i )
        loadhists.at(i) = (TH1*) ifile->Get( Form(nameTEMPLATE,i) );
    TH1* l = loadhists.at(0);
    TH1F* outhist = new TH1F( "tmp", "", l->GetNbinsX(), l->GetXaxis()->GetXbins()->GetArray() );

    for ( int iMC = 0; iMC < loadhists.size(); ++iMC )
        LowStatEntryRemoval(loadhists[iMC], iMC);
    for ( int ibin = outhist->GetNbinsX()+1; ibin !=0; --ibin )
    {
        double bin_integral = 0.;
        for ( TH1* h : loadhists )
            bin_integral += h->GetBinContent(ibin);
        outhist->SetBinContent(ibin, bin_integral);
    }
    return outhist;
}
TH1* histFactory_MergePtBinning(TFile* ifile, const char* nameTEMPLATE)
{
    std::vector<TH1*> loadhists(NUMBIN, nullptr);
    for ( int i = 0; i < NUMBIN; ++i )
        loadhists.at(i) = (TH1*) ifile->Get( Form(nameTEMPLATE,i) );

    TH1F* outhist = new TH1F( "tmp", "", jetptBin.size()-1, &(jetptBin.front()) );

    for ( int ibin = outhist->GetNbinsX()+1; ibin !=0; --ibin )
        outhist->SetBinContent( ibin, loadhists[ibin-1]->Integral() );
    return outhist;
}
void SetHistProperty(TH1* h, int fillcolor, const char* name, const char* illustration)
{
    h->SetName(name);
    h->SetTitle(illustration); // title is only used to be the label of TLegend
    h->SetTitleSize(0); // to hide title
    h->SetLineColor(13);
    h->SetLineWidth(1);
    h->SetFillColor(fillcolor);
    h->SetFillStyle(1001);
    h->GetXaxis()->SetTitle("reco jet Pt (GeV)");
    h->GetYaxis()->SetTitle("Quark Composition");
}
void normalization_eachBinBackToOne(std::vector<TH1*>& hists)
{
    TH1* h = hists.front();
    for ( auto ibin = h->GetNbinsX(); ibin != 0; --ibin )
    {
        double integral = 0.;
        for ( TH1* hist : hists )
            integral += hist->GetBinContent(ibin);
        for ( TH1* hist : hists )
            hist->SetBinContent(ibin, hist->GetBinContent(ibin)/integral);
    }
}



enum quarks { b,c,L, totNum };
std::vector<TH1*> GetQuarkCompositions(TDirectoryFile* ifile, bool normalizedHists = false)
{
    std::vector<TH1*> quark_hists(quarks::totNum,nullptr);
    // load b
    quark_hists[quarks::b] = histFactory_MergeMCSlices(ifile, "b_yield_file%d");
    SetHistProperty(quark_hists[quarks::b], colors[0], "bYield", "b quark");
    // load c
    quark_hists[quarks::c] = histFactory_MergeMCSlices(ifile, "c_yield_file%d");
    SetHistProperty(quark_hists[quarks::c], colors[1], "cYield", "c quark");
    // load L
    quark_hists[quarks::L] = histFactory_MergeMCSlices(ifile, "L_yield_file%d");
    SetHistProperty(quark_hists[quarks::L], colors[2], "LYield", "light quark");

    if ( normalizedHists ) normalization_eachBinBackToOne(quark_hists);

    return quark_hists;
}
class MyLegend : public TLegend
{
public:
    MyLegend(double x1, double y1, double x2, double y2) : TLegend(x1,y1,x2,y2)
    {
        SetFillColor(4000);
        SetFillStyle(4000);
        SetBorderSize(0);
    }
};
class MyCanvas : public TCanvas
{
    public:
    MyCanvas(const char* n, const char* t, int w, int d ) : TCanvas(n,t,w,d)
    {
        SetTopMargin(0.2);
        SetBottomMargin(0.2);
        SetLeftMargin(0.15);
        SetRightMargin(0.15);
        SetFillColor(4000);
        SetFillStyle(4000);
    }
};
void qcdCHECKER_plotQuarkCompositionSep_differentSelection()
{
    //TFile* ifile = TFile::Open("qcdCHECKER_histTOcheckCUTs_C.root");
    TFile* ifile = TFile::Open("qcdCHECKER_interestingHIST_C.root");
    TCanvas* canv = new TCanvas("canv", "", 1000,1000);

    std::list< std::pair<const char*, std::vector<TH1*>> > recordedHists;
    
    TDirectoryFile* dir = nullptr;
    const char* dirname = nullptr;
    bool normalizedHists = true;

    dirname = Form("allSample");
    dir = (TDirectoryFile*) ifile->Get(dirname);
    recordedHists.push_back( std::make_pair(dirname,GetQuarkCompositions(dir, normalizedHists) ));

    dirname = Form("noLargePU");
    dir = (TDirectoryFile*) ifile->Get(dirname);
    recordedHists.push_back( std::make_pair(dirname,GetQuarkCompositions(dir, normalizedHists) ));

    /*
    dirname = Form("PUvetoAndPtBintenTOminusFIVE");
    dir = (TDirectoryFile*) ifile->Get(dirname);
    recordedHists.push_back( std::make_pair(dirname,GetQuarkCompositions(dir, normalizedHists) ));

    dirname = Form("PUvetoAndPtBin100");
    dir = (TDirectoryFile*) ifile->Get(dirname);
    recordedHists.push_back( std::make_pair(dirname,GetQuarkCompositions(dir, normalizedHists)) );

    dirname = Form("PUvetoAndPtBin10");
    dir = (TDirectoryFile*) ifile->Get(dirname);
    recordedHists.push_back( std::make_pair(dirname,GetQuarkCompositions(dir, normalizedHists)) );
    */

    delete canv;

    MyCanvas* c1 = new MyCanvas("c1", "", 1400,1400); MyLegend* leg1 = new MyLegend(0.5,0.3,0.8,0.50);
    MyCanvas* c2 = new MyCanvas("c2", "", 1400,1400); MyLegend* leg2 = new MyLegend(0.5,0.3,0.8,0.50);
    MyCanvas* c3 = new MyCanvas("c3", "", 1400,1400); MyLegend* leg3 = new MyLegend(0.5,0.5,0.8,0.7);
    int idx = 0;
    for ( auto iter = recordedHists.begin(); iter != recordedHists.end(); ++iter )
    {
        const char* dirname = iter->first;
        std::vector<TH1*>& hists = iter->second;
        for ( TH1* hist : hists )
        {
            hist->SetLineColor( colors[idx] );
            hist->SetMarkerStyle( marks[idx] );
            hist->SetMarkerSize(1);
            hist->SetMarkerColor(colors[idx] );
            hist->SetLineWidth(1);
            hist->SetFillColor(0);
            hist->SetFillStyle(1001);
            hist->SetStats(false);

            hist->GetXaxis()->SetTitleSize( hist->GetYaxis()->GetTitleSize() );
            hist->GetXaxis()->SetTitleOffset(1.1);
            //std::cout << hist->GetXaxis()->GetTitleOffset() << std::endl;
        }
        idx++;

        c1->cd();
        if ( iter == recordedHists.begin() ) hists[quarks::b]->Draw("axis");
        hists[quarks::b]->Draw("LP SAME");
        //hists[quarks::b]->Draw("HIST SAME");
        leg1->AddEntry(hists[quarks::b], dirname, "lp");


        c2->cd();
        if ( iter == recordedHists.begin() ) hists[quarks::c]->Draw("axis");
        hists[quarks::c]->Draw("LP SAME");
        //hists[quarks::c]->Draw("HIST SAME");
        leg2->AddEntry(hists[quarks::c], dirname, "lp");
        
        c3->cd();
        if ( iter == recordedHists.begin() ) hists[quarks::L]->Draw("axis");
        hists[quarks::L]->Draw("PL SAME");
        //hists[quarks::L]->Draw("HIST SAME");
        leg3->AddEntry(hists[quarks::L], dirname, "lp");
    }

    c1->cd(); leg1->Draw();
    c1->SetLogx();
    //c1->SetLogy();
    c1->RedrawAxis();
    c1->SaveAs("qcdCHECKER_plotQuarkCompositionSep_differentSelection_C_b.pdf");

    c2->cd(); leg2->Draw();
    c2->SetLogx();
    //c2->SetLogy();
    c2->RedrawAxis();
    c2->SaveAs("qcdCHECKER_plotQuarkCompositionSep_differentSelection_C_c.pdf");

    c3->cd(); leg3->Draw();
    c3->SetLogx();
    //c3->SetLogy();
    c3->RedrawAxis();
    c3->SaveAs("qcdCHECKER_plotQuarkCompositionSep_differentSelection_C_L.pdf");

    delete leg1,leg2,leg3;
    delete c1,c2,c3;
    ifile->Close();
}

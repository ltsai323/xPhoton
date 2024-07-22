#define LOG(format, args...)     fprintf(stderr, "---------------------debug-    %s  \n  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)

const int NMCSEP = 9; // QCD madgraph samples are separated into 9 HT slices.
const int NUMBIN = 25;
const int colors[] = {2,46,42,49,32,8,3,4,38};
static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000});
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
int jetptBin_100CUT[NMCSEP] = {7,16,16,18,20,21,22,23,24};
int jetptBin_10CUT[NMCSEP] = {11,20,20,21,22,23,24,24,24};
int jetptBin_tenToMinusFiveCut[NMCSEP] = {10,10,15,17,20,20,22,23,24};
void LowStatEntryRemoval(TH1* hh, int iMC)
{
    for ( int ibin = hh->GetNbinsX(); ibin != 0; --ibin )
    {
        if ( ibin < jetptBin_tenToMinusFiveCut[iMC] ) break;
        hh->SetBinContent(ibin,0.);
    }
}

TH1* histFactory_MergeMCSlices(TFile* ifile, const char* nameTEMPLATE)
{
    std::vector<TH1*> loadhists(NMCSEP, nullptr);
    for ( int i=0;i<NMCSEP;++i )
        loadhists.at(i) = (TH1*) ifile->Get( Form(nameTEMPLATE,i) );
    TH1* l = loadhists.at(0);
    TH1F* outhist = new TH1F( "tmp", "", l->GetNbinsX(), l->GetXaxis()->GetXbins()->GetArray() );

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
void normalization_eachBinBackToOne(std::list<TH1*>& hists)
{
    for ( auto ibin = hists.front()->GetNbinsX(); ibin != 0; --ibin )
    {
        double integral = 0.;
        for ( TH1* hist : hists )
            integral += hist->GetBinContent(ibin);
        for ( TH1* hist : hists )
            hist->SetBinContent(ibin, hist->GetBinContent(ibin)/integral);
    }
}


const char* slicename[NMCSEP] = { "50To100", "100To200", "200To300", "300To500", "500To700", "700To1000", "1000To1500", "1500To2000", "2000ToInf" };

void qcdCHECKER_plotHTSlicesComposition()
{
    TFile* ifile = TFile::Open("qcdCHECKER_interestingHIST_C.root");
    //TFile* ifile = TFile::Open("qcdCHECKER_histTOcheckCUTs_C.root");
    TCanvas* canv = new TCanvas("canv", "", 1000,1000);

    std::list<TH1*> mcslices_hists;
    for ( int iMC = 0; iMC < NMCSEP; ++iMC )
    {
        //const char* histnameTEMPLATE = Form("%s_%s","allSample/weight_ptbin%d", Form("file%d",iMC));
        const char* histnameTEMPLATE = Form("%s_%s","allsample/weight_ptbin%d", Form("file%d",iMC));
        //const char* histnameTEMPLATE = Form("%s_%s","noLargePU/weight_ptbin%d", Form("file%d",iMC));
        mcslices_hists.push_back( histFactory_MergePtBinning(ifile,histnameTEMPLATE) );
        SetHistProperty(mcslices_hists.back(), colors[iMC], Form("slice_%d",iMC), slicename[iMC]);

        LowStatEntryRemoval( mcslices_hists.back(), iMC );
    }



    normalization_eachBinBackToOne(mcslices_hists);

    THStack* stackplot = new THStack( "thestackplot", "");
    TLegend* legend = new TLegend(0.13, 0.15, 0.33,0.4);
    legend->SetFillColor(4000);
    legend->SetFillStyle(4000);
    legend->SetBorderSize(0);

    for ( TH1* hist : mcslices_hists )
    {
        stackplot->Add(hist);
        legend->AddEntry(hist, hist->GetTitle(), "F");
    }
    
    stackplot->Draw();
    legend->Draw();

    stackplot->GetXaxis()->SetTitle("reco jet Pt (GeV)");
    stackplot->GetYaxis()->SetTitle("Compositions");

    canv->Modified();
    canv->SetFillStyle(4000);
    canv->SetFillColor(4000);
    canv->SetLogx();
    canv->SaveAs("qcdCHECKER_plotHTSlicesComposition_C.pdf");

}

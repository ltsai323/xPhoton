
#define LOG(format, args...)     fprintf(stderr, "---------------------debug-    %s  \n  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)

const int NMCSEP = 9; // QCD madgraph samples are separated into 9 HT slices.
const int NUMBIN = 25;
const int colors[] = {2,46,42,49,32,8,3,4,38};
static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000});
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
int jetptBin_100CUT[NMCSEP] = {7,16,16,18,20,21,22,23,24};
int jetptBin_10CUT[NMCSEP] = {11,20,20,21,22,23,24,24,24};
int jetptBin_tenTOminusFIVEcut[NMCSEP] = {10,10,15,17,20,20,22,23,24};
void LowStatEntryRemoval(TH1* hh, int iMC)
{
    //for ( int ibin = hh->GetNbinsX(); ibin >= jetptBin_10CUT[iMC]; --ibin )
    for ( int ibin = hh->GetNbinsX(); ibin >= jetptBin_100CUT[iMC]; --ibin )
        hh->SetBinContent(ibin,1e-20);
}
TLegend* compositeLeg = nullptr;
THStack* CompositionPlot( TFile* ifile, const char* htemp )
{
    std::vector<TH1*> h_ptspectrum_MC;
    for ( int iMC = 0; iMC < NMCSEP; ++iMC )
    {
        h_ptspectrum_MC.push_back(new TH1F( Form("pt_composition_spectrum_%d",iMC), "", jetptBin.size()-1, &(jetptBin.front()) ));
        TH1* hist = h_ptspectrum_MC.back();
        hist->SetLineColor(13);
        hist->SetLineWidth(1);
        hist->SetFillColor(colors[iMC]);
        hist->SetFillStyle(1001);
        hist->GetXaxis()->SetTitle("reco jet Pt (GeV)");
        hist->GetYaxis()->SetTitle("Composition");
    }
    for ( int ibin = 0; ibin < NUMBIN; ++ibin )
    {
        double integral_mc[NMCSEP] = {0};
        for ( int iMC = 0; iMC < NMCSEP; ++iMC ) integral_mc[iMC] = 0;
        double integral = 0.;
        for ( int iMC = 0; iMC < NMCSEP; ++iMC )
        {
            //if ( ibin >= jetptBin_10CUT[iMC] ) continue;
            if ( ibin >= jetptBin_tenTOminusFIVEcut[iMC] ) continue;
            //TH1* h = (TH1*) ifile->Get( Form("weight_%d_%d", ibin, iMC) );
            TH1* h = (TH1*) ifile->Get( Form(htemp, ibin, iMC) );

            integral_mc[iMC] = h->Integral();
            integral += integral_mc[iMC];
        }
        for ( int iMC = 0; iMC < NMCSEP; ++iMC )
        {
            h_ptspectrum_MC.at(iMC)->SetBinContent(ibin, integral_mc[iMC]/integral);
            //h_ptspectrum_MC.at(iMC)->SetBinContent(ibin, integral_mc[iMC]);
        }
    }
    //for ( int iMC = 0; iMC < NMCSEP; ++iMC )
    //{ LowStatEntryRemoval(h_ptspectrum_MC.at(iMC), iMC); }
    THStack* stack = new THStack( "composition_of_MC", "");
    //stack->SetMaximum(1.);
    //stack->SetMinimum(0.);
    //stack->GetYaxis()->SetRangeUser(0.,1.);

    if ( compositeLeg != nullptr ) delete compositeLeg;
    compositeLeg = new TLegend(0.5, 0.15, 0.89,0.4);
    TLegend* leg = compositeLeg;
    leg->SetNColumns(2);
    leg->SetBorderSize(0);
    leg->SetFillColor(4000);
    leg->SetFillStyle(4000);
    for ( int iMC = 0; iMC < h_ptspectrum_MC.size(); ++iMC )
    {
        TH1* hist = h_ptspectrum_MC.at(iMC);
        stack->Add(hist); 
        
        int lHTidx = iMC;
        int rHTidx = iMC+1;
        std::string lowerHT = std::to_string( int(genHTBin[iMC]) );
        std::string upperHT = iMC != h_ptspectrum_MC.size()-1 ? std::to_string( int(genHTBin[iMC+1]) ) : "inf";
        
        leg->AddEntry( hist, (lowerHT+"to"+upperHT).c_str(), "F" );
    }

    return stack;
}
THStack* StackPlot( TFile* ifile, int ibin )
{
    THStack* stack = new THStack(Form("stackplot_%d", ibin), "");

    std::vector<TH1*> hists;
    double integral = 0.;
    for ( int iMC = 0; iMC < NMCSEP; ++iMC )
    {
        hists.push_back((TH1*) ifile->Get( Form("weight_%d_%d", ibin, iMC) ) );
        integral += hists.back()->Integral();
    }
    for ( int iMC = 0; iMC < NMCSEP; ++iMC )
    {
        TH1* hist = hists.at(iMC);
        hist->SetLineColor(colors[iMC]);
        hist->SetFillColor(colors[iMC]);
        hist->SetFillStyle(1001);
        hist->Scale(1./integral);

        stack->Add(hist);
    }
    stack->SetMaximum(1.);
    stack->SetMinimum(5.e-4);
    return stack;
}
TText* ShowPtRange( int rangeIdx )
{
    int lowerptbin = rangeIdx-1;
    int upperptbin = rangeIdx;

    TString lBoundary;
    if ( lowerptbin < 0 ) lBoundary = "0";
    else lBoundary = Form("%d", int(jetptBin[lowerptbin]));

    TString rBoundary;
    if ( upperptbin == jetptBin.size() ) rBoundary = "inf";
    else rBoundary = Form("%d", int(jetptBin[upperptbin]));

    return new TText(0.13, 1.82, Form( "Pt = [%s,%s] GeV", lBoundary.Data(),rBoundary.Data() ));
}
void compositionPlotMaker()
{
    TFile* ifile = TFile::Open("qcdCHECKER_interestingHIST_C.root");
    TCanvas* canv = new TCanvas("canv", "", 1000,1000);
    //canv->SetLogx();
    //canv->SetLogy();
    THStack* stackplot = nullptr;
    stackplot = CompositionPlot(ifile,"allsample/weight_ptbin%d_file%d");
    stackplot->Draw("hist");
    compositeLeg->Draw();
    canv->SaveAs("h_compositionPlot.allsample.pdf");
    delete stackplot;

    stackplot = CompositionPlot(ifile,"noLargePU/weight_ptbin%d_file%d");
    stackplot->Draw("hist");
    compositeLeg->Draw();
    canv->SaveAs("h_compositionPlot.noLargePU.pdf");
    delete stackplot;
}



const int NMCSEP = 9; // QCD madgraph samples are separated into 9 HT slices.
const int NUMBIN = 25;
const int colors[] = {2,46,42,49,32,8,3,4,38};
static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000});
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
int jetptBin_100CUT[NMCSEP] = {7,16,16,18,20,21,22,23,24};
int jetptBin_10CUT[NMCSEP] = {11,20,20,21,22,23,24,24,24};
int jetptBin_tenToMinusFiveCut[NMCSEP] = {10,10,15,17,20,20,22,23,24};
bool LowStatEntryRemoval( int iMC, int ibin )
{
    if ( ibin >= jetptBin_tenToMinusFiveCut[iMC] ) return true;
    return false;
}
THStack* StackPlot( TFile* ifile, int ibin )
{
    THStack* stack = new THStack(Form("stackplot_%d", ibin), "");

    std::vector<TH1*> hists;
    double integral = 0.;
    for ( int iMC = 0; iMC < NMCSEP; ++iMC )
    {
        //hists.push_back((TH1*) ifile->Get( Form("noLargePU/weight_ptbin%d_file%d", ibin, iMC) ) );
        hists.push_back((TH1*) ifile->Get( Form("noEvtWeig/weight_ptbin%d_file%d", ibin, iMC) ) );
        if ( LowStatEntryRemoval(iMC, ibin) ) continue;

        //hists.push_back((TH1*) ifile->Get( Form("weight_%d_%d", ibin, iMC) ) );
        integral += hists.back()->Integral();
    }
    for ( int iMC = 0; iMC < NMCSEP; ++iMC )
    {
        if ( LowStatEntryRemoval(iMC, ibin) ) continue;
        TH1* hist = hists.at(iMC);
        hist->SetLineColor(colors[iMC]);
        hist->SetFillColor(colors[iMC]);
        hist->SetFillStyle(1001);
        hist->SetLineWidth(4);
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
void qcdCHECKER_plotMCWeightComposition()
{
    TFile* ifile = TFile::Open("qcdCHECKER_interestingHIST_C.root");
    TCanvas* canv = new TCanvas("canv", "", 1000,1000);
    canv->SetLogx();
    canv->SetLogy();
    std::vector<THStack*> stackplots;
    for ( int ibin = 0; ibin < NUMBIN; ++ibin )
    {
        stackplots.push_back( StackPlot(ifile, ibin) );
        THStack* stackplot = stackplots.back();
        stackplot->Draw("HIST");
        
        TText* txt = ShowPtRange(ibin);
        txt->Draw();
        canv->SaveAs( Form("h_stackplot_%s.png", stackplot->GetName()) );
    }
    TCanvas* bigcanvas = new TCanvas("bigCanvas", "", 2000,2000);
    bigcanvas->cd();
    bigcanvas->Divide(5,5);
    for ( int plotidx = 0; plotidx < stackplots.size(); ++plotidx )
    {
        TPad* pad = (TPad*) bigcanvas->cd(plotidx+1);
        pad->SetLogy(); pad->SetLogx();
        stackplots.at(plotidx)->Draw("HIST");
        
        TText* txt = ShowPtRange(plotidx);
        txt->Draw();
        pad->SetFillColor(4000);
        pad->SetFillStyle(4000);
    }
    bigcanvas->SetFillColor(4000);
    bigcanvas->SetFillStyle(4000);
    bigcanvas->SaveAs("h_compositionPlot_mcweightcomposition.pdf");

}

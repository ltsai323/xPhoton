#define PlotObject_cxx
#include "../../analysis/interface/PlotObject.h"

void SetHist( TH1* h,
        int markersize,
        int linecolor,
        int linewidth,
        int fillcolor,
        int fillstyle
        )
{
    h->GetYaxis()->SetTitle("Entries/0.2");

    h->SetMarkerSize(markersize);
    h->SetMarkerColor(1);
    h->SetMarkerStyle(20);
    h->SetLineColor(linecolor);
    h->SetLineWidth(linewidth);
    h->SetFillColor(fillcolor);
    h->SetFillStyle(fillstyle);
}
void SetDataHist( TH1* h ) { SetHist(h,1,1,2,0,0); }
void SetFitHist( TH1* h ) { SetHist(h,0,2,2,0,0); }
void SetCompomentHist( TH1* h, int color, int style ) { SetHist(h,0,color,1,color,style); }

TH1* ShapeUnc(TH1* sigHIST, TH1* sigHISTcentral, TH1* sigHISTshapeUP)
{
    TH1* sigHIST_updateShapeUnc = (TH1*) sigHIST->Clone();
    sigHIST_updateShapeUnc->SetName( Form("shapeUpdated_%s",sigHIST->GetName()) );

    double totEntries = sigHIST->Integral();
    for ( int ibin = sigHIST->GetNbinsX() ; ibin != 0 ; --ibin )
    {
        double shapeUpErr = sigHISTshapeUP->GetBinContent(ibin);
        double centralVal = sigHISTcentral->GetBinContent(ibin);
        double resetError = fabs(shapeUpErr-centralVal) * sigHIST->Integral() / sigHISTcentral->Integral();
        sigHIST_updateShapeUnc->SetBinError(ibin,resetError);
    }
    return sigHIST_updateShapeUnc;
}
TH1* GetSystErrHist(TH1* h, TH1* hTotFit)
{
    TH1* uncOnly = (TH1*) h->Clone();
    uncOnly->SetName( Form("uncOnly_%s",h->GetName()) );
    //SetCompomentHist(uncOnly,12,3005);
    SetCompomentHist(uncOnly,12,0);

    for ( int ibin = h->GetNbinsX(); ibin != 0; --ibin )
    {
        //uncOnly->SetBinError(ibin, uncOnly->GetBinError(ibin) / dataEntries );
        uncOnly->SetBinError(ibin, uncOnly->GetBinError(ibin) / hTotFit->GetBinContent(ibin) );
        //uncOnly->SetBinError(ibin, uncOnly->GetBinError(ibin) * 100.); // only for test
        uncOnly->SetBinContent(ibin, 1.00);
    }
    return uncOnly;
}
void UNCchecker(TH1* source, TH1* updated)
{
    for ( int ibin = source->GetNbinsX() ; ibin != 0; --ibin )
    {
        double oldERR = source->GetBinError(ibin);
        double newERR = updated->GetBinError(ibin);
        printf("@ bin %d. Unc = orig:%8.4f new:%8.4f",ibin, oldERR, newERR);
        if ( newERR > oldERR ) printf(" ----- updated error is larger!");
        printf("\n");
    }
}
void combineFRAG2_plot(
    int pETAbin, int jETAbin, int pPTbin,
    const char* pETArange, const char* jETArange, const char* pPTrange,
    const char* sourceHISTfile)
{
  auto ifile = TFile::Open("postfit.root");
  auto hdata = (TH1D*) ifile->Get("cat_BDT_postfit/data_obs");
  auto hfit  = (TH1D*) ifile->Get("cat_BDT_postfit/TotalProcs");
  auto hsig  = (TH1D*) ifile->Get("cat_BDT_postfit/TotalSig");
  auto hbkg  = (TH1D*) ifile->Get("cat_BDT_postfit/TotalBkg");

  // get sig shape unc hists
  auto sourceHistFile = TFile::Open(sourceHISTfile);
  auto hsig_central = (TH1F*) sourceHistFile->Get( Form("bin_%d_%d_%d/BDT_gjet_signalRegion",pETAbin,jETAbin,pPTbin) );
  auto hsig_shapeUp = (TH1F*) sourceHistFile->Get( Form("bin_%d_%d_%d/BDT_gjet_signalRegion_shapeUncUp",pETAbin,jETAbin,pPTbin) );

  TH1* hsig_shapeError = ShapeUnc(hsig, hsig_central,hsig_shapeUp);
  UNCchecker(hsig,hsig_shapeError);


  hdata->SetMinimum(0.);
  hdata->SetMaximum(hdata->GetMaximum()*1.5);
  SetDataHist(hdata);
  SetFitHist(hfit);
  SetCompomentHist(hsig, 46, 3002);
  SetCompomentHist(hbkg, 31, 3004);
  SetCompomentHist(hsig_shapeError, 46, 3002);

  TCanvas* canv = ARTKIT::signalCanvas();
  TPad* upperpad = ARTKIT::TopPad();
  upperpad->Draw();
  TPad* lowerpad = ARTKIT::BottomPad();
  lowerpad->Draw();

  upperpad->cd();
  hdata->Draw("AXIS");
  hsig->Draw("HIST SAME");
  hbkg->Draw("HIST SAME");
  hfit->Draw("HIST E0 SAME");
  hdata->Draw("P E0 X0 SAME");

  TLegend* leg = ARTKIT::newLegend();
  leg->AddEntry(hdata, Form("data in %.0f entries",hdata->Integral()), "lp");
  leg->AddEntry(hfit, Form("fit chi2 = %.1f", 0.0), "l");
  leg->AddEntry(hsig, Form("#signal = %.1f", hsig->Integral()), "f");
  leg->AddEntry(hbkg, Form("#bkg = %.1f", hbkg->Integral()), "f");
  leg->Draw();

  TPaveText* text = new TPaveText(0.17,0.71,0.42,0.92,"NDC");
  text->AddText(pPTrange);
  text->AddText(pETArange);
  text->AddText(jETArange);
  text->SetBorderSize(0);
  text->SetFillStyle(0);
  text->Draw();


  TH1D* ratioplot = ARTKIT::ratioPlot(hdata,hfit,"BDT Score", "Data/MC");
  TH1* shapeUncRatio = GetSystErrHist( hsig_shapeError, hfit);

  //TH1* shapeUncRatio = GetSystErrHist( hfit, hfit); // check original error
  lowerpad->cd();
  ratioplot->SetTitle("");
  ratioplot->Draw("E0 X0");
  shapeUncRatio->DrawCopy("HIST SAME"); // draw central line
  SetCompomentHist(shapeUncRatio,1,3005);
  shapeUncRatio->SetLineWidth(0);
  shapeUncRatio->Draw("E2 SAME"); // draw error bar

  ratioplot->Draw("E0 X0 SAME");
  canv->SaveAs("fitres.pdf");
}

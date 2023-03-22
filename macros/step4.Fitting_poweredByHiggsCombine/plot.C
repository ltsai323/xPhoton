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
    h->SetMarkerStyle(5);
    h->SetLineColor(linecolor);
    h->SetLineWidth(linewidth);
    h->SetFillColor(fillcolor);
    h->SetFillStyle(fillstyle);
}
void SetDataHist( TH1* h ) { SetHist(h,1,1,2,0,0); }
void SetFitHist( TH1* h ) { SetHist(h,0,2,2,0,0); }
void SetCompomentHist( TH1* h, int color, int style ) { SetHist(h,0,color,1,color,style); }
    
void plot(const char* pETArange, const char* jETArange, const char* pPTrange)
{
  auto ifile = TFile::Open("postfit.root");
  auto hdata = (TH1D*) ifile->Get("cat_BDT_postfit/data_obs");
  auto hfit  = (TH1D*) ifile->Get("cat_BDT_postfit/TotalProcs");
  auto hsig  = (TH1D*) ifile->Get("cat_BDT_postfit/TotalSig");
  auto hbkg  = (TH1D*) ifile->Get("cat_BDT_postfit/TotalBkg");

  hdata->SetMinimum(0.);
  hdata->SetMaximum(hdata->GetMaximum()*1.5);
  SetDataHist(hdata);
  SetFitHist(hfit);
  SetCompomentHist(hsig, 46, 3002);
  SetCompomentHist(hbkg, 31, 3004);

  TCanvas* canv = ARTKIT::signalCanvas();
  canv->SetFillColor(4000);
  canv->SetFillStyle(4000);

  TPad* upperpad = ARTKIT::TopPad();
  upperpad->Draw();
  upperpad->SetFillColor(4000);
  upperpad->SetFillStyle(4000);
  TPad* lowerpad = ARTKIT::BottomPad();
  lowerpad->Draw();
  lowerpad->SetFillColor(4000);
  lowerpad->SetFillStyle(4000);

  upperpad->cd();
  hdata->Draw("AXIS");
  hsig->Draw("HIST E0 SAME");
  hbkg->Draw("HIST SAME");
  hfit->Draw("HIST E SAME");
  hdata->Draw("P E0 SAME");

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
  lowerpad->cd();
  ratioplot->SetTitle("");
  ratioplot->SetMarkerSize(0);
  ratioplot->Draw("E0");
  canv->SaveAs("fitres.pdf");
}

#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TTree.h"
#include <fstream>
#include <iostream>
#include <TMinuit.h>
#include <vector>
#include <iostream>
#include <TMath.h>
#include "TVirtualFitter.h"
#include "TFile.h"
#include "TLegend.h"
#include "TMarker.h"
#include "TLine.h"
#include "TRandom3.h"
#include "xEGM/CMS_lumi.C"
#include "TString.h"

using namespace std;

#define NPAR 2

TF1* fchi2;
//TH1F* h1;
TF1* bsFin;

// Remember to change the values of xh and xl in all_tree.C too!!!
//Double_t xh = 6.5;
//Double_t xl = 4.5;
Double_t xl = -1.;
Double_t xh = 1.;
Double_t bin_size = 0.01;

const double _two_pi = 2.0 * TMath::Pi();
Double_t fit_lo_edge = -1.;
Double_t fit_hi_edge = 1.;

Int_t toymc_sig=30000;
Int_t toymc_bkg=6000;

vector<Double_t> dataColl;
vector<Double_t> sigColl;
vector<Double_t> bkgColl;

vector<Double_t> totalColl;
vector<Double_t> ctauColl;

vector<Double_t> info;
vector<Double_t> info_err;

//par[0] = fs Jpsi signal fraction;
//-----mass part-----------------------------------------------------
//par[1] = g norm; par[2] g1 mean; par[3] g1 width; 
//par[4] g2 ratio;  par[5] g2 mean; par[6] g2 width;
//par[7] bg norm; par[8] bg slope;

void fcn(Int_t &npar, Double_t *gin, Double_t &f, Double_t *par, Int_t iflag)
{

  Double_t Lsum=0.;
  Double_t Nevt=0.;
  Double_t fs = par[0];
  Double_t fb = par[1];

  for ( int i=0; i<dataColl.size(); i++ ) {
    Nevt += dataColl[i];
    //PDF for signal and background
    Double_t Ls = sigColl[i]; if(Ls<0.) Ls=0.;
    Double_t Lb = bkgColl[i]; if(Lb<0.) Lb=0.;
    for (int data=0; data<dataColl[i]; data++) {	
      //Get Log Likelihood
      if(Ls!=0. ||  Lb!=0.) Lsum += TMath::Log( (fs*Ls + fb*Lb) / (fs+fb) );
    }
  }
  f=2*( -1*Lsum + (fs+fb)  - Nevt*TMath::Log(fs+fb) );
}

std::vector<float> ptbin_ranges()
{
  // for 2016
  std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
  return vec_ptcut;
}
int numPtBins() { return ptbin_ranges().size()-1; } // pt range N has n-1 intevals

Int_t ptbin_index(float pt){
  std::vector<float> vec_ptcut = ptbin_ranges();

  // ignoring last one due to lack of [last, inf] bin in physics.
  for ( int ibin = vec_ptcut.size()-2; ibin >= 0 ; --ibin )
      if ( pt > vec_ptcut[ibin] ) return ibin;
  return -1;
}
Int_t findbin_phopt(float phopt) {
    return ptbin_index(phopt);
}
        

Int_t ptbin_lowedge(float ptbin){ return int( ptbin_ranges().at(ptbin) ); }
const char* EtaName(int ebee)
{
    if ( ebee == 0 ) return "EB";
    if ( ebee == 1 ) return "EE";
    return "hi";

    /* used for 2015, 4 eta bins analysis
    if ( ebee > 1 ) return "EE";
    return "EB";
    */
}


//___________________________________________________________________________
Double_t* Ifit(Int_t ptbin=13, int ebee=0, int fit_data=1, int jetbin=0)
{
  TRandom3 *trd = new TRandom3();
  Double_t* fitted = new Double_t[8];

  TCanvas _c1("HF1", "Histos1", 0, 0, 600, 600);
  TPad  _pad1("pad1","",0.02, 0.02, 0.99, 0.99);
  TCanvas *c1 = &_c1;
  TPad* pad1 = &_pad1;
  pad1->Draw();
  pad1->cd();

  double count=0;
  dataColl.clear();
  sigColl.clear();
  bkgColl.clear();

  totalColl.clear();
  ctauColl.clear();
  const char* EBEE = EtaName(ebee);
  //char EBEE[10]="EB";
  //if(ebee!=0) sprintf(EBEE,"EE");
  //Get data from looping tree
  TFile *ff = new TFile("isovsbdt_template.root");
  //TFile *ff = new TFile("isovsbdt_template_nominal.root");
  //TFile *ff = new TFile("isovsbdt_template_sig_altm.root");
  //TFile *ff = new TFile("isovsbdt.root");
  TFile *fhisto_data = nullptr; // = new TFile("data.root");
  TFile *fhisto_qcd = nullptr; // = new TFile("mc_QCD.root");
  /*TFile *fhisto_gjet6000 = new TFile("mc_gjet6000.root");*/
  //TFile *fhisto_gjet6000 = new TFile("mc_hggfilter.root");
  //TFile *fhisto_sigalt = new TFile("isovsbdt_template_sig_altp.root");
  //TFile *fhisto_sig = new TFile("sigtemplate_sys.root");  
  TFile *fhisto_sig = new TFile("isovsbdt_template.root");
  /*TFile *fhisto_sigalt = new TFile("isovsbdt_template_sig_shiftm.root");*/


  if(ptbin < 0) {
    if ( fhisto_data ) fhisto_data->Close();
    if ( fhisto_qcd  ) fhisto_qcd->Close();
    /*fhisto_gjet6000->Close();*/
    if ( ff          ) ff->Close();
    if ( fhisto_sig  ) fhisto_sig->Close();
    /*fhisto_sigalt->Close();*/
    return fitted;
  }

  TH1F *hsig; // = new TH1F();
  TH1F *hbkg; // = new TH1F();
  TH1F *hsig_toymc; // = new TH1F();
  TH1F *hbkg_toymc; // = new TH1F();

  char hname[30];
  // int ebee=0;
  // if(strcmp(EBEE,"EB")==0) { ebee=0; }
  // else if(strcmp(EBEE,"EE")==0) { ebee=1;   }

    
  if(fit_data==1 || fit_data==11){ //1 norminal fit; 11 fit with toy template
    sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
    printf(hname);
    //if(ebee==1 && jetbin==1 && ptbin==21)     sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, 20);
    //hsig=(TH1F*)ff->Get(hname);
    hsig=(TH1F*)fhisto_sig->Get(hname);
    
    sprintf(hname,"data_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
    if(ptbin >=20) sprintf(hname,"data_%d_%d_%d_px2_chIso",ebee, jetbin, 19);
    hbkg=(TH1F*)ff->Get(hname);      
  }else if(fit_data==0){
    sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);    

    hsig_toymc=(TH1F*)fhisto_sig->Get(hname);
    //hsig=(TH1F*)ff->Get(hname);    

    //hsig_toymc=(TH1F*)ff->Get(hname);    
    hsig = (TH1F*)hsig_toymc->Clone();
    //hsig_toymc=(TH1F*)fhisto_sigalt->Get(hname);        

    //sprintf(hname,"qcd_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
    sprintf(hname,"qcd_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
    hbkg_toymc=(TH1F*)ff->Get(hname);
    //hbkg=(TH1F*)hbkg_toymc->Clone();
    //sprintf(hname,"qcd_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
    sprintf(hname,"data_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
    hbkg=(TH1F*)ff->Get(hname);    

  }else if(fit_data==2){
    sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
    hsig=(TH1F*)fhisto_sig->Get(hname);
    // sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
    // hsig=(TH1F*)ff->Get(hname);
    sprintf(hname,"qcd_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
    hbkg=(TH1F*)ff->Get(hname);
  }else if(fit_data==3){
    sprintf(hname,"gjet_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
    hsig=(TH1F*)ff->Get(hname);
    sprintf(hname,"qcd_%d_%d_%d_px2_chIso",ebee, jetbin, ptbin);
    hbkg=(TH1F*)ff->Get(hname);
  }else if(fit_data==4){ // fit phoIso
    sprintf(hname,"gjet_%d_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
    hsig=(TH1F*)ff->Get(hname);
    //sprintf(hname,"data_%d_%d_%d_px2_phoIso",ebee, jetbin, ptbin);
    sprintf(hname,"qcd_%d_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
    hbkg=(TH1F*)ff->Get(hname);
  }else if(fit_data==5){ // fit phoIso
    sprintf(hname,"gjet_%d_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
    hsig=(TH1F*)ff->Get(hname);
    hsig_toymc = (TH1F*)hsig->Clone();
    sprintf(hname,"qcd_%d_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
    hbkg_toymc=(TH1F*)ff->Get(hname);    
    sprintf(hname,"qcd_%d_%d_%d_px2_phoIso",ebee, jetbin, ptbin);
    hbkg=(TH1F*)ff->Get(hname);    
  }
  /*
  else if(fit_data==99){
    sprintf(hname,"h_BDT_%d_%d_%d_%d_0",ebee, 0, ptbin);
    hsig=(TH1F*)fhisto_gjet6000->Get(hname);
    sprintf(hname,"h_BDT_%d_%d_%d_%d_0",ebee, 1, ptbin);
    hsig->Add((TH1F*)fhisto_gjet6000->Get(hname));
    sprintf(hname,"h_BDT_%d_%d_%d_%d_1",ebee, 0, ptbin);
    hbkg=(TH1F*)fhisto_qcd->Get(hname);
    sprintf(hname,"h_BDT_%d_%d_%d_%d_1",ebee, 1, ptbin);
    hbkg->Add((TH1F*)fhisto_qcd->Get(hname));
  }
  */

  
  // hsig->Draw();
  // // // hbkg_toymc->Draw();
  // return fitted;

  TH1F *hEGdata;
  if(fit_data==99){
    sprintf(hname,"h_BDT_%d_%d_%d_0",ebee, jetbin,  ptbin);
    hEGdata = (TH1F*)fhisto_data->Get(hname);
  } else if(fit_data<=3 || fit_data==11){
    sprintf(hname,"data_%d_%d_%d_px1_chIso",ebee, jetbin, ptbin);
    hEGdata=(TH1F*)ff->Get(hname);
  }//  else {
  //   sprintf(hname,"data_%d_%d_%d_px1_phoIso",ebee, jetbin, ptbin);
  //   hEGdata=(TH1F*)ff->Get(hname);
  // }    



  hsig->Rebin(10);
  hbkg->Rebin(10);
  hEGdata->Rebin(10);
  if(fit_data==0 || fit_data==5){  
    hsig_toymc->Rebin(10);
    hbkg_toymc->Rebin(10);
  }

  //----------------------------------------------------------------------------  
  //not allowing negative contribution
  for(int ibin=0; ibin<hbkg->GetNbinsX(); ibin++){
    if(hbkg->GetBinContent(ibin+1)<1e-6){
      printf("set bkg bin %d, content %f to 0. \n", ibin+1, hbkg->GetBinContent(ibin+1));
      hbkg->SetBinContent(ibin+1,1e-6);
    }
    if(hsig->GetBinContent(ibin+1)<1e-6){
      printf("set sig bin %d, content %f to 0. \n", ibin+1, hsig->GetBinContent(ibin+1));
      hsig->SetBinContent(ibin+1,1e-6);
    }
  }

  //adding systematcis error on template
  for(int ibin=0; ibin<hbkg->GetNbinsX(); ibin++){
    float tmperr = 0.04*0.04;
    if(ebee==1) tmperr = 0.06*0.06;
    tmperr += hbkg->GetBinError(ibin+1)/hbkg->GetBinContent(ibin+1)*hbkg->GetBinError(ibin+1)/hbkg->GetBinContent(ibin+1);
    tmperr = TMath::Sqrt(tmperr)*hbkg->GetBinContent(ibin+1);
    //printf("ibin %d, err %f, new err %f \n", ibin, hbkg->GetBinError(ibin+1), tmperr);    
    if(hbkg->GetBinContent(ibin+1)>0.) hbkg->SetBinError(ibin+1, tmperr);
  }

  //if modifing signal template to 0x or 2x in BDT<0
  // for(int ibin=0; ibin<hbkg->GetNbinsX()/2.; ibin++){
  //   //hsig->SetBinContent(ibin+1,0.);
  //   hsig->SetBinContent(ibin+1,hsig->GetBinContent(ibin+1)*2.);
  // }

  if(fit_data==11){ //fluctuate signal template by the error)
    TH1F *htmp = (TH1F*)hsig->Clone();
    hsig->Reset();
    hsig->FillRandom(htmp, htmp->Integral());
  }

  // normalize template
  hsig->Scale(1./hsig->Integral());
  hbkg->Scale(1./hbkg->Integral());  
  if(fit_data!=1){
    hsig_toymc->Scale(1./hsig_toymc->Integral());
    hbkg_toymc->Scale(1./hbkg_toymc->Integral());
  }

  TH1F *hsum = new TH1F();
  int ntemplate = 1000.;
  float sigfrac = 0.7;
  TH1F *hsum_norm = new TH1F();
  TH1F *hdata = new TH1F();

  int ndata=0;
  if ( fit_data!=0 && fit_data!=5 ) {
    hdata = (TH1F*)hEGdata->Clone();
    ndata = hdata->GetEntries();
  }else { //generate toymc
    // hsum = (TH1F*)hsig_toymc->Clone();
    // hsum->Scale(toymc_sig);
    // hsum->Add(hbkg_toymc,toymc_bkg);
    
    // hsum_norm = (TH1F*)hsum->Clone();  
    // hsum_norm->Scale(1./hsum->Integral());
    // hdata = (TH1F*)hsum_norm->Clone();
    // //ndata = (int) gRandom->Poisson(hsum->Integral());
    // ndata=toymc_sig+toymc_bkg;
    // hdata->FillRandom(hsum_norm, ndata);
    TH1F *hss = (TH1F*)hsig_toymc->Clone();    hss->Reset();
    TH1F *hsss = (TH1F*)hsig_toymc->Clone();    hsss->Reset();
    TH1F *hbb = (TH1F*)hbkg_toymc->Clone();    //hbb->Reset();
    TH1F *hbbb = (TH1F*)hbkg_toymc->Clone();    hbbb->Reset();
    for(int ibin=0; ibin<hsig_toymc->GetNbinsX(); ibin++){
      printf("ibin %d, content %f, err %f \n", ibin, hsig_toymc->GetBinContent(ibin+1), hsig_toymc->GetBinError(ibin+1) );
      printf("    bkg  content %f, err %f \n", hbkg_toymc->GetBinContent(ibin+1), hbkg_toymc->GetBinError(ibin+1) );
      float tmp = trd->Gaus( hsig_toymc->GetBinContent(ibin+1), hsig_toymc->GetBinError(ibin+1) );
      hss->SetBinContent(ibin+1, tmp);
      // tmp = trd->Gaus( hbkg_toymc->GetBinContent(ibin+1), hbkg_toymc->GetBinError(ibin+1) );
      // hbb->SetBinContent(ibin+1, tmp);
    }
     hsss = (TH1F*)hss->Clone();
     hsss->Scale(toymc_sig/hsss->Integral());
    // hbbb = (TH1F*)hbb->Clone();
    // hsss->Scale(toymc_sig/hsss->Integral());
    // hbbb->Scale(toymc_bkg/hbbb->Integral());

    // hsss->FillRandom(hss, toymc_sig);
    hbbb->FillRandom(hbb, toymc_bkg);

    hdata = (TH1F*)hsss->Clone();
    ndata=toymc_sig+toymc_bkg;
    hdata->Add(hbbb);
    printf("toymc sig %f, bkg %f, total %f, generated %f \n", toymc_sig, toymc_bkg, ndata, hdata->Integral());   

  }
  if(ndata==0) {
    printf(" ---  no events in the fit \n");
    fitted[0] = 0.;
    fitted[1] = 0.;
    fitted[2] = 0.;
    fitted[3] = 0.;
    fitted[4] = 0.;
    fitted[5] = 0.;
    fitted[6] = 0.;
    fitted[7] = 0.;
    if ( fhisto_data ) fhisto_data->Close();
    if ( fhisto_qcd  ) fhisto_qcd->Close();
    /*fhisto_gjet6000->Close();*/
    if ( ff          ) ff->Close();
    /*fhisto_sigalt->Close();*/
    if ( fhisto_sig  ) fhisto_sig->Close();
    return fitted;
  }    

  printf(" --------- before the fit ------------- \n");
  printf("Nsig %2.3f, Nbg %2.3f, Ntemplate %3.3f \n", hsig->Integral(), hbkg->Integral(), ntemplate);
  printf("Purity %2.3f, init size %4.3f,  test sample size %4d\n", hsig->Integral()/hsum->Integral(), hsum->Integral(), ndata);
  printf(" -------------------------------------- \n");

  int nbins = hdata->GetNbinsX();
  for (int ibin=1; ibin<=nbins; ibin++) {
    dataColl.push_back(hdata->GetBinContent(ibin));
    sigColl.push_back(hsig->GetBinContent(ibin));
    bkgColl.push_back(hbkg->GetBinContent(ibin));    
  }
  
  printf( " -----  Got %d, %d, %d bins for fit ----- \n ", dataColl.size(),
	  sigColl.size(), bkgColl.size() );  
  if ( dataColl.size() != sigColl.size() || sigColl.size()!=bkgColl.size() ) {
    printf(" error ...  inconsistent hit collection size \n");
    if ( fhisto_data ) fhisto_data->Close();
    if ( fhisto_qcd  ) fhisto_qcd->Close();
    /*fhisto_gjet6000->Close();*/
    if ( ff          ) ff->Close();
    /*fhisto_sigalt->Close();*/
    if ( fhisto_sig  ) fhisto_sig->Close();
    return fitted;
  }

  //--------------------------------------------------
  //init parameters for fit
  Double_t vstart[10] = {1., 1.};
  vstart[0] = sigfrac*ndata;
  vstart[1] = (1-sigfrac)*ndata;
 
  TMinuit *gMinuit = new TMinuit(NPAR);  
  gMinuit->Command("SET STR 1");
  gMinuit->SetFCN(fcn);
  Double_t arglist[10];
  Int_t ierflg = 0;
  
  arglist[0] = 1;
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
  arglist[0] = 1;
  gMinuit->mnexcm("SET PRINT", arglist ,1,ierflg);

  Double_t step[] = { 0.1, 0.1,};

  gMinuit->mnparm(0,  "Signal yield"  , vstart[0],  step[0], 0., ndata*2.  , ierflg);
  gMinuit->mnparm(1,  "background yield"  , vstart[1],  step[1], 0., ndata*2. , ierflg);
  
  printf(" --------------------------------------------------------- \n");
  printf(" Now ready for minimization step \n --------------------------------------------------------- \n");
  
  arglist[0] = 2000; // number of iteration
  arglist[1] = 1.;

  gMinuit->mnexcm("MIGRAD", arglist ,2,ierflg);
  printf (" -------------------------------------------- \n");
  printf("Finished.  ierr = %2.2f \n", ierflg);

  info.clear();
  info_err.clear();

  double para[NPAR+1],errpara[NPAR+1];
  if ( ierflg == 0 ) 
    {
      for(int j=0; j<=NPAR-1;j++) {
        gMinuit->GetParameter(j, para[j],errpara[j]);
        para[NPAR] = dataColl.size();
        info.push_back(para[j]);
        info_err.push_back(errpara[j]);
        printf("Parameter (yeild) %d = %f +- %f\n",j,para[j],errpara[j]);
	
      }
      printf(" fitted yield %2.3f \n", (para[0]+para[1])/ndata );

      info.push_back(sigColl.size());

      //do minos if fit sucessed.
      printf("         ---------------------------------------------------------\n");
      printf("          Now call for minos step \n");
      printf("         ---------------------------------------------------------\n");
      
      arglist[0] = 200; // number of iteration
      arglist[1] = 1;
      gMinuit->mnexcm("MINOS", arglist ,2,ierflg);
      printf("         --------------------------------------------------------- \n");
      printf("         Done Minos.  ierr = %d \n", ierflg);
      Double_t amin;
      gMinuit->mnprin(1,amin);
      if(ierflg !=0 ) {
	printf(" *****  MINOS fit failed ***** \n");
	return fitted;
      }
    }
  else {
    printf(" *********** Fit failed! ************\n");
    gMinuit->GetParameter(0, para[0],errpara[0]);
    gMinuit->GetParameter(1, para[1],errpara[1]);
    para[0]=0.; errpara[0]=0.;
  }

  
  // Print results
  Double_t amin,edm,errdef;
  Int_t nvpar,nparx,icstat;
  gMinuit->mnstat(amin,edm,errdef,nvpar,nparx,icstat);
  gMinuit->mnprin(1,amin);  
  gMinuit->mnmatu(1);
  printf(" ========= happy ending !? =========================== \n");
  
  printf("FCN =  %3.3f \n", amin);

  double yerr[100];
  for(int i=0;i<100;i++){
    yerr[i] = 0.;
  }

  hsig->Scale(para[0]/hsig->Integral());
  hbkg->Scale(para[1]/hbkg->Integral());
  TH1F *hfit = (TH1F*)hsig->Clone();
  hfit->Add(hbkg);

  hsig->SetLineColor(kGreen+3);
  hsig->SetLineWidth(2);
//   hsig->SetFillColor(5);
//   hsig->SetFillStyle(3001);

//   hbkg->SetLineWidth(2);
  // plot
  c1->Draw();  


  hdata->SetLineColor(1);

  hdata->SetNdivisions(505,"XY");
  hdata->SetXTitle("BDT output");
  hdata->SetYTitle("Entries");
  hdata->SetTitle("");
  hdata->SetMarkerStyle(8);
  hdata->SetMinimum(0.);

  
  float ymax = hdata->GetMaximum();
  if ( hfit->GetMaximum() > hdata->GetMaximum() ) ymax = hfit->GetMaximum();
  if ( ymax < 20 ) ymax = 20;
  hdata->SetMaximum(ymax*1.5);
  hfit->SetMaximum(ymax*1.5);
  hsig->SetMaximum(ymax*1.5);
  hbkg->SetMaximum(ymax*1.5);
  hdata->SetLineWidth(2);


  //if draw lowscale
  //gPad->SetLogy();
  // hdata->SetMaximum(ymax*100.);
  // hdata->SetMinimum(10.);


  hdata->Draw("p e1");
  

  hbkg->SetMarkerStyle(0);
  hbkg->SetFillColor(2);
  hbkg->SetLineWidth(2);
  hbkg->SetLineColor(2);
  hbkg->SetFillStyle(3005);
  //hbkg->SetError(yerr);
  hbkg->Draw("he2 same");
  


  hsig->SetMarkerStyle(0);
  //hsig->SetError(yerr);
  hsig->Draw("he same");


  hfit->SetMarkerStyle(0);
  hfit->SetLineColor(4);
  hfit->SetLineWidth(2);
  //hfit->SetError(yerr);
  //printf("nbins hfit %d \n", hfit->GetNbinsX());
  hfit->Draw("h e same");
  //hdata->Draw("p e same");
  
  //TLegend *tleg = new TLegend(0.33, 0.65, 0.8, 0.88);
  TLegend *tleg = new TLegend(0.12, 0.5, 0.75, 0.75);
  char text[50];
  //sprintf(text,"%s Photon Pt %.0f - %.0f GeV",EBEE, ptbin_lowedge(ptbin),  ptbin_lowedge(ptbin+1));
  if(ebee==0){
    sprintf(text,"|#eta^{#gamma}|<1.4442, %d<p_{T}<%d GeV", ptbin_lowedge(ptbin),  ptbin_lowedge(ptbin+1));
  }else  if(ebee==1){
    sprintf(text,"1.566<|#eta^{#gamma}|<2.5, %d<p_{T}<%d GeV", ptbin_lowedge(ptbin),  ptbin_lowedge(ptbin+1));
  }
  tleg->SetHeader(text);
  tleg->SetTextSize(0.03);
  tleg->SetFillStyle(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);
  sprintf(text,"Data %5.1f events",hdata->Integral());
  tleg->AddEntry(hdata,text,"pl");
  sprintf(text,"Fitted %5.1f events",hfit->Integral());
  
  tleg->AddEntry(hfit,text,"l");
  sprintf(text,"SIG %5.1f #pm %5.1f events",para[0], errpara[0]);
  tleg->AddEntry(hsig,text,"f");
  sprintf(text,"BKG %5.1f #pm %5.1f events",para[1], errpara[1]);
  
  tleg->AddEntry(hbkg,text,"f");
  tleg->Draw();

  hbkg->Draw("h same");
  hsig->Draw("h same");
  hfit->Draw("h same");
  hdata->Draw("p e same");


  if(fit_data!=0) {
    writeExtraText = true;       // if extra text
    extraText  = "Preliminary";  // default extra text is "Preliminary"
    lumiTextSize     = 0.4; 
    lumiTextOffset   = 0.; 
    cmsTextSize      = 0.5;
    cmsTextOffset    = 2.; 
    CMS_lumi( pad1, 2016, 11); // 2016 is data era
  }
  // TLatex *tlx = new TLatex();
  // tlx->SetTextSize(0.035);
  // tlx->DrawLatex(-0.5, hdata->GetMaximum(), "CMS Preliminary #sqrt{s} = 13TeV, L=2.57 fb^{-1}");
  

  gPad->RedrawAxis();
  float bdtcut = 0.374;
  int ibin1=0;
  if(ebee==1) bdtcut = 0.336;
  float binw = hfit->GetBinWidth(1);
  for(int ibin= 1; ibin<=hfit->GetNbinsX(); ibin++){
    //printf("bin %d, bin edge %.2f \n", ibin, hfit->GetBinCenter(ibin)-0.5*binw);
    if(hfit->GetBinCenter(ibin)-0.5*binw < bdtcut && hfit->GetBinCenter(ibin)+0.5*binw > bdtcut) {
      ibin1 = ibin;
      //printf("set start integral bin here\n");
    }     
  }
  
  float sig_part = hsig->Integral(ibin1,hfit->GetNbinsX());
  float sig_part_err = hsig->Integral(ibin1,hfit->GetNbinsX())*errpara[0]/para[0];
  float bkg_part = hbkg->Integral(ibin1,hfit->GetNbinsX());
  float bkg_part_err = hbkg->Integral(ibin1,hfit->GetNbinsX())*errpara[1]/para[1];
  printf("%s Data %5.1f events, fitted %5.1f\n", EBEE, hdata->Integral(), hfit->Integral());
  printf("%s Data %5.1f, and fitted (in 5GeV) %5.1f events \n", EBEE, hdata->Integral(ibin1,hfit->GetNbinsX()), hfit->Integral(ibin1,hfit->GetNbinsX()));
  printf("%s bin %d SIG %5.1f #pm %5.1f events \n", EBEE, ptbin, para[0], errpara[0]);
  printf("%s SIG (in 5GeV) %5.1f #pm %5.1f events \n", EBEE, sig_part, sig_part_err);
  printf("%s bin %d BKG %5.1f #pm %5.1f events \n", EBEE, ptbin, para[1], errpara[1]);
  printf("%s BKG (in 5GeV) %5.1f #pm %5.1f events \n", EBEE, bkg_part, bkg_part_err);
  printf("----------------------------------------------- \n");
  printf("%s Data (<0) %.1f (>0) %.1f events \n", EBEE, hdata->Integral(1,nbins/2.), hdata->Integral(nbins/2+1,nbins));
  printf("%s sig (<0) %.1f (>0) %.1f events \n", EBEE, hsig->Integral(1,nbins/2.), hsig->Integral(nbins/2+1,nbins));
  printf("%s bkg (<0) %.1f (>0) %.1f events \n", EBEE, hbkg->Integral(1,nbins/2.), hbkg->Integral(nbins/2+1,nbins));
  printf("----- fit results with signal projection   ----------- \n");
  Double_t chi2;
  if(fit_data==1 || fit_data==2) chi2=hdata->Chi2Test(hfit,"UW P CHI2");
  //ftemplate->Close();
  printf (" chi2/ndf is %.2e\n", chi2);
  TLatex *tlx = new TLatex();
  tlx->SetTextSize(0.03);
  sprintf(text,"#chi^{2}/ndf = %.1f/9", chi2);
  //tlx->DrawLatex(-0.15, hdata->GetMaximum()*0.65, text);
  tlx->DrawLatex(-0.65, hdata->GetMaximum()*0.46, text);

  char fname[30];
  sprintf(fname,"plots/test_Ifit%s_%d_%d_%d.pdf",EBEE, ebee, jetbin, ptbin);
  if(fit_data==1 || fit_data==2) c1->SaveAs(fname);


  fitted[0] = para[0];
  fitted[1] = errpara[0]/TMath::Sqrt(2);
  fitted[2] = para[1];
  //if (fit_data==2 ) fitted[2] += hdata->GetBinContent(hdata->GetNbinsX()+1);
  fitted[3] = errpara[1]/TMath::Sqrt(2);
  fitted[4] = sig_part;
  fitted[5] = sig_part_err/TMath::Sqrt(2);
  fitted[6] = bkg_part;
  fitted[7] = bkg_part_err/TMath::Sqrt(2);
  
  if(fit_data==0 || fit_data==5 || fit_data==11) {
    printf(" all files closed ... \n");
    if ( ff          ) ff->Close();
    if ( fhisto_data ) fhisto_data->Close();
    if ( fhisto_qcd  ) fhisto_qcd->Close();
    /*fhisto_gjet6000->Close();*/
    /*fhisto_sigalt->Close();    */
    if ( fhisto_sig  ) fhisto_sig->Close();
  }
  return fitted;
} // end of Ifit

void pulltest(int ptbin=13, int ebee=0, int jetbin=0, int sig=400, int bkg=400){

  double *fitted;
  TH1F *h1 = new TH1F("h1","",200,-10., 10.);
  int nbin=1000;
  if(sig*1.5/2. < 1000) nbin=(int)sig*1.5/2.;
  TH1F *h2 = new TH1F("h2","",nbin, 0., sig*1.5);

  h1->SetNdivisions(505,"XY");
  h2->SetNdivisions(505,"XY");

  int nexp=200;
  Double_t Nevt=0.;
  //to check the template stat err.
  // sig = fitted[0]; bkg=fitted[2];
  
  toymc_sig = sig;
  toymc_bkg = bkg;

  for (int i=0; i<nexp; i++) {    
    //nominal
    //fitted = Ifit(ptbin,EBEE, 0, jetbin);
    fitted = Ifit(ptbin,ebee, 0, jetbin);
    //to check teh template stat err.
    // fitted = Ifit(ptbin,EBEE, 2, jetbin);
    // Nevt=sig+bkg;


    // for ( int ii=0; ii<dataColl.size(); ii++ ) {
    //   Nevt += dataColl[ii];
    // }
    // printf("fit purity %2.2f +- %2.2f err with %d events. \n", info[0], info_err[0], Nevt);
    // h1->Fill((info[0]/Nevt-input)/(info_err[0]/Nevt));
    printf("input %d, %d, fitted %.2f %.2f \n", toymc_sig, toymc_bkg, fitted[0], fitted[1]);
    h1->Fill((fitted[0]-toymc_sig)/fitted[1]*TMath::Sqrt(2.));
    h2->Fill(fitted[0]);
  }    

  TCanvas *c2 = new TCanvas("c2","",1000,500);
  c2->Divide(2,1);
  c2->cd(1);
  char txt[100];
  sprintf(txt, "(fitted-gen)/error");
  h1->SetXTitle(txt);
  h1->Fit("gaus");
  //h1->GetXaxis()->SetRangeUser(-5.,5.);
  h1->Draw();
  c2->cd(2);
  sprintf(txt, "fitted signal (input %d)", toymc_sig);
  h2->SetXTitle(txt);
  h2->Fit("gaus");
  TF1 *func = (TF1*)h2->GetFunction("gaus");
  h2->Fit("gaus","","",func->GetParameter(1)-2*func->GetParameter(2),func->GetParameter(1)+2.*func->GetParameter(2));
//TF1 *func = (TF1*)h2->GetFunction("gaus"); // unknown...
       func = (TF1*)h2->GetFunction("gaus"); // unknown...
  h2->GetXaxis()->SetRangeUser(func->GetParameter(1)-5.*func->GetParameter(2),func->GetParameter(1)+5.*func->GetParameter(2));
  h2->Draw();  
  sprintf(txt, "plots/extmLfit_pull_%d_%d_pt%d.pdf", ebee, jetbin,  ptbin);
  c2->SaveAs(txt);
  sprintf(txt, "plots/extmLfit_pull_%d_%d_pt%d.C", ebee, jetbin,  ptbin);
  c2->SaveAs(txt);


  printf(" toygen %d with stat error %.2f\% \n", sig, TMath::Sqrt(sig)/sig*100.);
  printf(" TOYTOY pt %d, mean %.2f, width %.2f \n", ptbin, func->GetParameter(1), func->GetParameter(2));
  printf(" %5.2f \\\% \\pm %5.2f \\\% \n", (func->GetParameter(1)/sig*100.)-100.,(func->GetParameter(2)/func->GetParameter(1)*100.));
  
}
// decouple eff.dat file
void DrawYield(int ebee=0, int jetbin=0){
    const char* EBEE = EtaName(ebee);
    int ebeebin = ebee>0 ? 1 : 0;
    /*
  char EBEE[20]="EB";
  if(ebee==1) sprintf(EBEE,"EE");
   int ebeebin=0;
   if(strcmp(EBEE,"EE")==0) {
     ebeebin=1;
   }
   */



  std::vector<float> vec_ptcut = ptbin_ranges();
  float* ptcut = &vec_ptcut.front();

  //int nbin=vec_ptcut.size();
  int nbin=numPtBins();

  TH1F *h_yield = new TH1F("h_yield","",nbin, ptcut);
  TH1F *h_purity = new TH1F("h_purity","",nbin, ptcut);
  TH1F *h_purity_tight = new TH1F("h_purity_tight","",nbin, ptcut);

  TH1F *h_sig_yield = new TH1F("h_sig_yield","",nbin, ptcut);
  TH1F *h_sig_yield_tight = new TH1F("h_sig_yield_tight","",nbin, ptcut);
  TH1F *h_bkg_yield = new TH1F("h_bkg_yield","",nbin, ptcut);
  TH1F *h_bkg_yield_tight = new TH1F("h_bkg_yield_tight","",nbin, ptcut);


  double *fitted;
  float lumi = 35.9;

  char txt[100];
  for(int ii=0; ii<numPtBins(); ii++){
    //perform fit for yield
    fitted=Ifit(ii, ebee, 1, jetbin);
    if(fitted[0]>0.) {

      h_yield->SetBinContent(ii+1, fitted[0]/h_yield->GetBinWidth(ii+1));
      h_yield->SetBinError(ii+1, fitted[1]/h_yield->GetBinWidth(ii+1));

      float djet_eta=1.5*2.;
      if(jetbin==1) djet_eta = 0.9*2.;
      if(jetbin==2) djet_eta = 1;

      h_sig_yield->SetBinContent(ii+1, fitted[0]);
      h_bkg_yield->SetBinContent(ii+1, fitted[2]);

      h_sig_yield_tight->SetBinContent(ii+1, fitted[4]);
      h_bkg_yield_tight->SetBinContent(ii+1, fitted[6]);
    } // if fitted yield found
  } // end of photon bins

  TCanvas *c10 = new TCanvas("c10","",600,600);
  c10->Draw();
  gPad->SetLogy();
  h_yield->SetNdivisions(505,"XY");
  h_yield->SetXTitle("p_{T} (GeV)");
  h_yield->SetYTitle("Entries / GeV");
  h_yield->SetMarkerStyle(8);
  h_yield->GetXaxis()->SetRangeUser(150.,1000.);
  h_yield->Draw("pe");

  char pho_text[100];
  char jet_text[100];
  if(ebeebin==0) sprintf(pho_text,"|#eta_{#gamma}|<1.4442");
  else sprintf(pho_text,"1.566<|#eta_{#gamma}|<2.5");
  if(jetbin==0) sprintf(jet_text,"|#eta_{jet}|<1.5");
  else sprintf(jet_text,"1.5<|#eta_{jet}|<2.4");


  TLegend *tleg = new TLegend(0.4, 0.65, 0.85, 0.92);
  char text[50];
  sprintf(text,"CMS 13TeV, %.0f fb^{-1}",lumi);
  tleg->SetHeader(text);
  tleg->SetFillColor(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);  
  sprintf(text,"%s, %s",pho_text, jet_text);
  if(jetbin==2)   sprintf(text,"%s",pho_text);
  tleg->AddEntry(h_yield,text,"pl");
  tleg->Draw();
} // end of DrawYield

/*
void Draw_yield_treeeff(int ebee=0, int jetbin=0){
  char EBEE[20]="EB";
  if(ebee>1) sprintf(EBEE,"EE");
  int ptbin_int=0;
  std::vector<float> vec_ptcut = ptbin_ranges();
  float* ptcut = &vec_ptcut.front();

  int nbin=vec_ptcut.size();

  TH1F *h_yield = new TH1F("h_yield","",nbin, ptcut);
  TH1F *h_purity = new TH1F("h_purity","",nbin, ptcut);
  TH1F *h_purity_tight = new TH1F("h_purity_tight","",nbin, ptcut);

  TH1F *h_sig_yield = new TH1F("h_sig_yield","",nbin, ptcut);
  TH1F *h_sig_yield_tight = new TH1F("h_sig_yield_tight","",nbin, ptcut);
  TH1F *h_bkg_yield = new TH1F("h_bkg_yield","",nbin, ptcut);
  TH1F *h_bkg_yield_tight = new TH1F("h_bkg_yield_tight","",nbin, ptcut);


  TH1F *h_xs = new TH1F("h_xs","",nbin,ptcut);
  double *fitted;
  float lumi = 2568.83;
  float lumi_err = lumi*0.046;
  float deta = 1.4442*2.; 
  float template_sys = TMath::Sqrt(0.49*0.49+0.7*0.7+3.24*3.24)*0.01;
  int ebeebin=0;
  if(strcmp(EBEE,"EE")==0) {
    deta = (2.5-1.566)*2.;
    ebeebin=1;
    template_sys =  TMath::Sqrt(1.98*1.98+3.03*3.03+8.6*8.6)*0.01;
  }

  TTree *tt = new TTree();
  tt->ReadFile("eff.dat");
  Int_t   ptbin_;
  Int_t   ebee_;
  Int_t   jetbin_;
  Float_t trigeff;
  Float_t trigeff_err;
  Float_t recoeff;
  Float_t recoeff_err;
  Float_t SF;
  Float_t SF_err;       
  Float_t vetoSF;
  Float_t vetoSF_err;       
  Double_t JEC_err;

  tt->SetBranchAddress("ptbin", &ptbin_);
  tt->SetBranchAddress("EBEE", &ebee_);
  tt->SetBranchAddress("jetbin", &jetbin_);
  tt->SetBranchAddress("trigeff", &trigeff);
  tt->SetBranchAddress("trigeff_err", &trigeff_err);
  tt->SetBranchAddress("recoeff", &recoeff);
  tt->SetBranchAddress("recoeff_err", &recoeff_err);
  tt->SetBranchAddress("SF", &SF);
  tt->SetBranchAddress("SF_err", &SF_err);
  tt->SetBranchAddress("vetoSF", &vetoSF);
  tt->SetBranchAddress("vetoSF_err", &vetoSF_err);
  tt->SetBranchAddress("JEC_err", &JEC_err);

  char txt[100];
  for(int ii=13; ii<22; ii++){
    //perform fit for yield
    fitted=Ifit(ii, ebee, 1, jetbin);
    if(fitted[0]>0.) {

      h_yield->SetBinContent(ii+1, fitted[0]/h_yield->GetBinWidth(ii+1));
      h_yield->SetBinError(ii+1, fitted[1]/h_yield->GetBinWidth(ii+1));

      Long64_t jentry = ii-13 + 9*3*ebeebin + 9*jetbin;
      tt->GetEntry(jentry);
      printf("bin %d, %d, %d \n", ptbin_, ebee_, jetbin_);
    
      float djet_eta=1.5*2.;
      if(jetbin==1) djet_eta = 0.9*2.;
      if(jetbin==2) djet_eta = 1;
      printf("bin %d, ptcut %.1f,  fit %.0f , bkg %.0f , eff %.2f, binwidth %.1f, deta %.2f \n", ii, ptcut[ii], fitted[0], fitted[2], recoeff, h_yield->GetBinWidth(ii+1), deta );
      printf(" %f %f %f %f %f %f %f %f %f \n",  fitted[0] , lumi , trigeff, recoeff ,  h_yield->GetBinWidth(ii+1) ,SF, vetoSF ,deta , djet_eta);
      float xs = fitted[0] / lumi / trigeff/ recoeff / h_yield->GetBinWidth(ii+1) /SF /vetoSF /deta / djet_eta ; //xs per GeV
      float xs_err = (fitted[1]/fitted[0])*(fitted[1]/fitted[0]) + (lumi_err/lumi)*(lumi_err/lumi) + 
	(recoeff_err/recoeff)*(recoeff_err/recoeff) + 
	(trigeff_err/trigeff)*(trigeff_err/trigeff) +
	(SF_err/SF)*(SF_err/SF) +
	(vetoSF_err/vetoSF)*(vetoSF_err/vetoSF) +
	(template_sys*template_sys)+
	(JEC_err*JEC_err);
      xs_err = TMath::Sqrt(xs_err)*xs;
      printf("ptbin %d  ebeebin %d jetbin %d xs %e  xs_err %e \n", ii, ebeebin, jetbin, xs, xs_err);
      h_xs->SetBinContent(ii+1, xs);
      h_xs->SetBinError(ii+1, xs_err);

      h_sig_yield->SetBinContent(ii+1, fitted[0]);
      h_bkg_yield->SetBinContent(ii+1, fitted[2]);

      h_sig_yield_tight->SetBinContent(ii+1, fitted[4]);
      h_bkg_yield_tight->SetBinContent(ii+1, fitted[6]);

      // //perform fit for purity in WP90 region
      // h_purity_tight->SetBinContent(ii+1, fitted[4]/(fitted[4]+fitted[6]));
      // float err = TMath::Sqrt(fitted[4]*fitted[6]/(fitted[4]+fitted[6])/(fitted[4]+fitted[6])/(fitted[4]+fitted[6]));
      // h_purity_tight->SetBinError(ii+1, err);    
      // h_purity->SetBinContent(ii+1, fitted[0]/(fitted[0]+fitted[2]));
      // err = TMath::Sqrt(fitted[0]*fitted[2]/(fitted[0]+fitted[2])/(fitted[0]+fitted[2])/(fitted[0]+fitted[2]));
      // h_purity->SetBinError(ii+1, err);    
    }
  }
  for(int ii=13; ii<nbin; ii++){
    //   printf("ptbin %d, %.2f, xs %f , xs_err %f \n", ii, ptcut[ii], h_xs->GetBinContent(ii+1), h_xs->GetBinError(ii+1));
    printf("ptbin %d, %.2f, yield, %.2f, %.2f \n", ii, ptcut[ii], h_sig_yield_tight->GetBinContent(ii+1), h_bkg_yield_tight->GetBinContent(ii+1));
  }

  TCanvas *c10 = new TCanvas("c10","",600,600);
  c10->Draw();
  gPad->SetLogy();
  h_yield->SetNdivisions(505,"XY");
  h_yield->SetXTitle("p_{T} (GeV)");
  h_yield->SetYTitle("Entries / GeV");
  h_yield->SetMarkerStyle(8);
  h_yield->GetXaxis()->SetRangeUser(150.,1000.);
  h_yield->Draw("pe");

  char pho_text[100];
  char jet_text[100];
  if(ebeebin==0) sprintf(pho_text,"|#eta_{#gamma}|<1.4442");
  else sprintf(pho_text,"1.566<|#eta_{#gamma}|<2.5");
  if(jetbin==0) sprintf(jet_text,"|#eta_{jet}|<1.5");
  else sprintf(jet_text,"1.5<|#eta_{jet}|<2.4");


  TLegend *tleg = new TLegend(0.4, 0.65, 0.85, 0.92);
  char text[50];
  sprintf(text,"CMS 13TeV, %.0f pb^{-1}",lumi);
  tleg->SetHeader(text);
  tleg->SetFillColor(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);  
  sprintf(text,"%s, %s",pho_text, jet_text);
  if(jetbin==2)   sprintf(text,"%s",pho_text);
  tleg->AddEntry(h_yield,text,"pl");
  tleg->Draw();
  
  // TLatex *tlx = new TLatex();
  // tlx->SetTextSize(0.04);
  // tlx->DrawLatex(100, h_yield->GetMaximum()*1.3, "CMS Preliminary #sqrt{s} = 13TeV");

  // //purity plot
  // TCanvas *c11 = new TCanvas("c11","",600,600);
  // h_purity->SetNdivisions(505,"XY");
  // h_purity->SetXTitle("P_{T} (GeV)");
  // h_purity->SetYTitle("Purity");
  // h_purity->SetMarkerStyle(8);
  // h_purity->GetXaxis()->SetRangeUser(150.,1000.);
  // h_purity->GetYaxis()->SetRangeUser(0., 1.01);
  // h_purity->Draw();
  // // h_purity_tight->SetMarkerStyle(8);
  // // h_purity_tight->SetMarkerColor(4);
  // // h_purity_tight->SetLineColor(4);
  // // h_purity_tight->Draw("pe same");

  
  // TGraphAsymmErrors *tgrs = new TGraphAsymmErrors();
  // h_bkg_yield->Add(h_sig_yield);

  // tgrs->BayesDivide(h_sig_yield, h_bkg_yield);
  // tgrs->SetMarkerStyle(8);
  // tgrs->Draw("pe same");

  // TGraphAsymmErrors *tgrs_tight = new TGraphAsymmErrors();
  // h_bkg_yield_tight->Add(h_sig_yield_tight);
  // for(int ii=13; ii<nbin; ii++){
  //   //   printf("ptbin %d, %.2f, xs %f , xs_err %f \n", ii, ptcut[ii], h_xs->GetBinContent(ii+1), h_xs->GetBinError(ii+1));
  //   printf("ptbin %d, %.2f, yield, %.2f, %.2f \n", ii, ptcut[ii], h_sig_yield_tight->GetBinContent(ii+1), h_bkg_yield_tight->GetBinContent(ii+1));
  // }

  // tgrs_tight->BayesDivide(h_sig_yield_tight, h_bkg_yield_tight,"v");
  // tgrs_tight->SetMarkerStyle(8);
  // tgrs_tight->SetMarkerColor(4);
  // tgrs_tight->SetLineColor(4);
  // tgrs_tight->Draw("pe same");

  // tleg = new TLegend(0.3, 0.15, 0.85, 0.35);
  // char text[50];
  // sprintf(text,"Single Photon PD %.0f pb^{-1}", lumi);
  // tleg->SetHeader(text);
  // tleg->SetFillColor(0);
  // tleg->SetShadowColor(0);
  // tleg->SetBorderSize(0);
  // sprintf(text,"%s, %s",pho_text, jet_text);
  // tleg->AddEntry(tgrs,text,"pl");
  // sprintf(text,"%s, %s, BDT>0.37",pho_text, jet_text);
  // tleg->AddEntry(tgrs_tight,text,"pl");
  // tleg->Draw();

  // tlx->SetTextSize(0.04);
  // tlx->DrawLatex(200, 1.01, "CMS Preliminary #sqrt{s} = 13TeV");
  
}
*/

void Draw_XS(char EBEE[20]="EB", int jetbin=0){

  float ptcut[30] = {22, 30, 36, 50, 75, 90, 105,  120, 135, 150, 165, 175, 185,
		     190, 200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000};
  int nbin=22;
  TH1F *h_xs = new TH1F("h_xs","",nbin,ptcut);

  double *fitted;
  float lumi = 2568.83;
  float lumi_err = lumi*0.046;
  float deta = 1.4442*2.; 
  float template_sys = TMath::Sqrt(3.2*3.2+3.*3.)*0.01;
  int ebeebin=0;
  if(strcmp(EBEE,"EE")==0) {
    deta = (2.5-1.566)*2.;
    ebeebin=1;
  }
  float djet_eta = 1.5*2.; 
  if(jetbin==1) djet_eta=(2.4-1.5)*2.; 
  if(jetbin==2) djet_eta=1.;

  char pho_text[100];
  char jet_text[100];
  if(ebeebin==0) sprintf(pho_text,"|#eta_{#gamma}|<1.4442");
  else sprintf(pho_text,"1.566<|#eta_{#gamma}|<2.5");
  if(jetbin==0) sprintf(jet_text,"|#eta_{jet}|<1.5");
  else sprintf(jet_text,"1.5<|#eta_{jet}|<2.4");

  TTree *tt = new TTree();
  tt->ReadFile("data_xs.dat");
  Int_t   ptbin_;
  Int_t   ebee_;
  Int_t   jetbin_;
  Double_t xs_data;
  Double_t xs_data_err;

  tt->SetBranchAddress("ptbin", &ptbin_);
  tt->SetBranchAddress("EBEE", &ebee_);
  tt->SetBranchAddress("jetbin", &jetbin_);
  tt->SetBranchAddress("xs", &xs_data);
  tt->SetBranchAddress("xs_err", &xs_data_err);

  for(int ii=13; ii<22; ii++){
    Long64_t jentry = ii-13 + 9*3*ebeebin + 9*jetbin;
    tt->GetEntry(jentry);
    //printf("bin %d, %d, %d \n", ptbin_1, ebee_1, jetbin_1);
    h_xs->SetBinContent(ii+1, xs_data);
    h_xs->SetBinError(ii+1, xs_data_err);
  }


  //Draw XS plot
  TCanvas *c12 = new TCanvas("c12","",600,700);  
  c12->Draw();

  TPad* pad1 = new TPad("pad1","",0.02, 0.25, 0.99, 0.99);
  TPad* pad2 = new TPad("pad1","",0.02, 0.02, 0.99, 0.25);


  // pad1->SetLeftMargin(0.02);
  pad1->SetRightMargin(0.035);
  // pad1->SetTopMargin(0.02);
  pad1->SetBottomMargin(0.0);
  pad1->SetFrameBorderMode(0);
  pad1->SetBorderMode(0);
  pad1->SetBorderSize(0);

  // pad2->SetLeftMargin(0.02);
  pad2->SetRightMargin(0.035);
  pad2->SetTopMargin(0.0);
  pad2->SetBottomMargin(0.275);
  pad2->SetFrameBorderMode(0);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(0);

  pad1->Draw();
  pad2->Draw();
  
  pad1->cd();

  gPad->SetLogy();

  TH2F *hh2 = new TH2F("hh2","",100, 150, 1000, 100, 2e-7, 1.);
  if(ebeebin==1) hh2 = new TH2F("hh2","",100, 150, 1000, 100, 2e-7, 1.);

  hh2->SetNdivisions(505,"XY");
  hh2->SetXTitle("P_{T} (GeV)");
  hh2->SetYTitle("d^{3}#sigma / d^{#gamma}p_{T}d^{#gamma}#eta d^{jet}#eta [pb/GeV]");
  if(jetbin==2)   hh2->SetYTitle("d^{2}#sigma / d^{#gamma}p_{T}d^{#gamma}#eta [pb/GeV]");
  hh2->GetXaxis()->SetLabelSize(0.035);
  hh2->GetYaxis()->SetLabelSize(0.035);
  hh2->GetYaxis()->SetTitleSize(0.04);
  hh2->GetYaxis()->SetTitleOffset(1.1);
  hh2->Draw();
  
  h_xs->SetMarkerStyle(8);
  h_xs->Draw("pel same");

  //--------------------------------------------------------------------------------
  //Draw JetPhox value
  TTree *t_th = new TTree();
  t_th->ReadFile("jetphox.dat");
  t_th->Print();

  Int_t ptbin_1;
  Int_t ebee_1;
  Int_t jetbin_1;
  Double_t xs_th;
  Double_t xs_th_err;
    
  t_th->SetBranchAddress("ptbin", &ptbin_1);
  t_th->SetBranchAddress("EBEE", &ebee_1);
  t_th->SetBranchAddress("jetbin", &jetbin_1);
  t_th->SetBranchAddress("xs", &xs_th);
  t_th->SetBranchAddress("xs_err", &xs_th_err);
  
  
  TH1F *h_th_xs = new TH1F("h_th_xs","",nbin, ptcut);
  TH1F *h_th_xs_err = new TH1F("h_th_xs_err","",nbin, ptcut);

  for(int ii=0; ii<13; ii++){
    h_th_xs_err->SetBinContent(ii+1, 1.);
    h_th_xs_err->SetBinError(ii+1, 0.);
  }
  for(int ii=13; ii<22; ii++){
    Long64_t jentry = ii-13 + 9*3*ebeebin + 9*jetbin;
    t_th->GetEntry(jentry);
    //printf("bin %d, %d, %d \n", ptbin_1, ebee_1, jetbin_1);
    h_th_xs->SetBinContent(ii+1, xs_th);
    h_th_xs->SetBinError(ii+1, xs_th_err);
    h_th_xs_err->SetBinContent(ii+1, 1.);
    h_th_xs_err->SetBinError(ii+1, xs_th_err/xs_th);

    if(jetbin==2){
      if(ebeebin==0){
	h_th_xs->SetBinContent(ii+1, xs_th/deta);
	h_th_xs->SetBinError(ii+1, xs_th_err/deta);
      }else{
	h_th_xs->SetBinContent(ii+1, xs_th/deta*2.);
	h_th_xs->SetBinError(ii+1, xs_th_err/deta*2.);
      }
    }
  }

  h_th_xs->SetMarkerStyle(25);
  h_th_xs->SetMarkerColor(2);
  h_th_xs->SetLineColor(2);
  h_th_xs->Draw("same ple");

  //--------------------------------------------------------------------------------
  //Draw MCFM value
  TTree *t_th_mcfm = new TTree();
  t_th_mcfm->ReadFile("mcfm.dat");
  t_th_mcfm->Print();

  // Int_t ptbin_1;
  // Int_t ebee_1;
  // Int_t jetbin_1;
  Double_t xs_th_mcfm;
  Double_t xs_th_mcfm_err;
    
  t_th_mcfm->SetBranchAddress("ptbin", &ptbin_1);
  t_th_mcfm->SetBranchAddress("EBEE", &ebee_1);
  t_th_mcfm->SetBranchAddress("jetbin", &jetbin_1);
  t_th_mcfm->SetBranchAddress("xs", &xs_th_mcfm);
  t_th_mcfm->SetBranchAddress("xs_err", &xs_th_mcfm_err);
  
  
  TH1F *h_th_mcfm_xs = new TH1F("h_th_mcfm_xs","",nbin, ptcut);
  TH1F *h_th_mcfm_xs_err = new TH1F("h_th_mcfm_xs_err","",nbin, ptcut);

  for(int ii=0; ii<13; ii++){
    h_th_mcfm_xs_err->SetBinContent(ii+1, 1.);
    h_th_mcfm_xs_err->SetBinError(ii+1, 0.);
  }

  if(ebeebin==0 && jetbin<=2) {
    for(int ii=13; ii<22; ii++){
      Long64_t jentry = ii-13 + 9*3*ebeebin + 9*jetbin;
      t_th_mcfm->GetEntry(jentry);
      printf("bin %d, %d, %d \n", ptbin_1, ebee_1, jetbin_1);
      h_th_mcfm_xs->SetBinContent(ii+1, xs_th_mcfm / deta / djet_eta *0.001 );
      h_th_mcfm_xs->SetBinError(ii+1, xs_th_mcfm_err / deta / djet_eta *0.001);
      h_th_mcfm_xs_err->SetBinContent(ii+1, 1.);
      h_th_mcfm_xs_err->SetBinError(ii+1, xs_th_mcfm_err/xs_th_mcfm);
    }
  }

  h_th_mcfm_xs->SetMarkerStyle(26);
  h_th_mcfm_xs->SetMarkerColor(4);
  h_th_mcfm_xs->SetLineColor(4);
  h_th_mcfm_xs->Draw("same ple");


  TLegend *tleg = new TLegend(0.4, 0.65, 0.85, 0.85);
  char text[50];
  // sprintf(text,"CMS 13TeV, %.0f pb^{-1}",lumi);
  // tleg->SetHeader(text);
  tleg->SetFillColor(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);  
  sprintf(text,"%s, %s",pho_text, jet_text);
  if(jetbin==2)   sprintf(text,"%s",pho_text);
  tleg->AddEntry(h_xs,text,"pl");
  tleg->AddEntry(h_th_xs,"JETPHOX","pl");
  if(ebeebin==0 && jetbin<=2)  tleg->AddEntry(h_th_mcfm_xs,"MCFM","pl");
  tleg->Draw();
  
  // TLatex *tlx = new TLatex();
  // tlx->DrawLatex(150, 1., "CMS Preliminary #sqrt{s} = 13TeV");
  //CMS_lumi( TPad* pad, int iPeriod, int iPosX )
  writeExtraText = true;       // if extra text
  extraText  = "Preliminary";  // default extra text is "Preliminary"
  lumiTextSize     = 0.45; 
  lumiTextOffset   = 0.1; 
  cmsTextSize      = 0.55;
  cmsTextOffset    = 0.05; 
  CMS_lumi( pad1, 4, 0);

  //-----------------------------------------------------------------
  //Draw JETPHOX ratio
  
  //Draw data/th XS ratio
  pad2->cd();
  gPad->SetGridy();
  TH1F *h_xs_ratio = (TH1F*)h_xs->Clone();
  
  h_xs_ratio->Divide(h_th_xs);
  // TGraphAsymmErrors *tgrs = new TGraphAsymmErrors();
  // tgrs->Divide(h_xs, h_th_xs);
  // TH1F *h_xs_ratio = new TH1F("h_xs_ratio","",nbin,ptcut);
  h_xs_ratio->SetMinimum(0.);
  h_xs_ratio->SetMaximum(2.);
  h_xs_ratio->SetNdivisions(505,"XY");
  h_xs_ratio->SetXTitle("P_{T} (GeV)");
  h_xs_ratio->SetYTitle("Data / MC");
  h_xs_ratio->GetXaxis()->SetLabelSize(0.12);
  h_xs_ratio->GetYaxis()->SetLabelSize(0.1);
  h_xs_ratio->GetXaxis()->SetTitleSize(0.12);
  h_xs_ratio->GetYaxis()->SetTitleSize(0.12);
  h_xs_ratio->GetXaxis()->SetTitleOffset(1.);
  h_xs_ratio->GetYaxis()->SetTitleOffset(0.4);

  h_xs_ratio->GetXaxis()->SetRangeUser(150,1000);
  // h_xs_ratio->GetYaxis()->SetRangeUser(0.55, 1.45);
  // if(ebeebin==1) h_xs_ratio->GetYaxis()->SetRangeUser(0., 2.2);
  // if(jetbin==1) h_xs_ratio->GetYaxis()->SetRangeUser(0., 2.2);
  h_xs_ratio->GetYaxis()->SetRangeUser(0., 2.2);

  //h_xs_ratio->GetYaxis()->SetNdivisions(102,"Y");
  h_xs_ratio->Draw("pe");
  // tgrs->SetMarkerStyle(8);
  // tgrs->Draw("pe same");

  h_th_xs_err->SetFillColor(29);
  h_th_xs_err->SetFillStyle(3002);
  h_th_xs_err->SetMarkerStyle(0);
  h_th_xs_err->Draw("e2 same");
  h_xs_ratio->SetMarkerStyle(21);
  h_xs_ratio->SetMarkerColor(2);
  h_xs_ratio->SetLineColor(2);
  h_xs_ratio->SetLineWidth(2);
  h_xs_ratio->Draw("pe1 same");
  gPad->RedrawAxis();
  
  //-----------------------------------------------------------------
  //Draw MCFM ratio
  if(ebeebin==0 && jetbin<=2){

    
    TH1F *h_xs_ratio_mcfm = (TH1F*)h_xs->Clone();
    printf("entry %f, xs %f , mcfm %f \n", h_xs_ratio_mcfm->GetBinCenter(14), h_xs_ratio_mcfm->GetBinContent(14), h_th_mcfm_xs->GetBinContent(14));
    h_xs_ratio_mcfm->Divide(h_th_mcfm_xs);

    //h_xs_ratio_mcfm->Divide(h_th_mcfm_xs);
     // for(int ibin=13; ibin<=22; ibin++){
     //   h_xs_ratio_mcfm->SetBinContent(ibin, h_xs_ratio_mcfm->GetBinContent(ibin)/h_th_mcfm_xs->GetBinContent(ibin));
     //   double tmperr = (h_xs_ratio_mcfm->GetBinError(ibin)/h_xs_ratio_mcfm->GetBinContent(ibin))*
     // 	(h_xs_ratio_mcfm->GetBinError(ibin)/h_xs_ratio_mcfm->GetBinContent(ibin)) +
     // 	(h_th_mcfm_xs->GetBinError(ibin)/h_th_mcfm_xs->GetBinContent(ibin))*
     // 	(h_th_mcfm_xs->GetBinError(ibin)/h_th_mcfm_xs->GetBinContent(ibin));
     //   tmperr = TMath::Sqrt(tmperr)*h_xs_ratio_mcfm->GetBinContent(ibin)/h_th_mcfm_xs->GetBinContent(ibin);
     //   h_xs_ratio_mcfm->SetBinError(ibin, tmperr); 
     // }
    printf("entry %f, xs ratio %f \n", h_xs_ratio_mcfm->GetBinCenter(14), h_xs_ratio_mcfm->GetBinContent(14));

    h_xs_ratio_mcfm->SetBinContent(13,0.);
    for(int ii=0; ii<h_xs_ratio_mcfm->GetNbinsX(); ii++){
      printf("bin %d, bin center %.2f , ratio %.3f \n", ii, h_xs_ratio_mcfm->GetBinCenter(ii+1), h_xs_ratio_mcfm->GetBinContent(ii+1));
    }
    
    h_th_mcfm_xs_err->SetFillColor(28);
    h_th_mcfm_xs_err->SetFillStyle(3004);
    h_th_mcfm_xs_err->SetMarkerStyle(0);
    //h_th_mcfm_xs_err->Draw("e2 same");
    h_xs_ratio_mcfm->SetMarkerStyle(22);
    h_xs_ratio_mcfm->SetMarkerColor(4);
    h_xs_ratio_mcfm->SetLineColor(4);
    //h_xs_ratio_mcfm->Print();
    h_xs_ratio_mcfm->Draw("pe same");
    gPad->RedrawAxis();
    
  }
  return;

    
  if(ebeebin==0 && jetbin==2){
    //draw theory  MCFM
    FILE *infile = fopen("mcfm.dat","r");
    double xdata1, xdata2, xdata3;
    double th_mcfm_bin[50], th_mcfm_bin_err[50], th_mcfm_xs[50], th_mcfm_xs_err[50];
    int datapoint = 41;
    for (int i=0;i<datapoint;i++){
      fscanf(infile,"%lf %lf %lf",&xdata1, &xdata2, &xdata3);
      th_mcfm_bin[i] = xdata1; th_mcfm_xs[i] = xdata2; th_mcfm_xs_err[i] = xdata3;
      if(th_mcfm_bin[i]<300.)th_mcfm_bin_err[i]=5.;
      else th_mcfm_bin_err[i] = 12.5;
    }  
    for(int ii=0; ii<41; ii++){
      th_mcfm_xs[ii] = th_mcfm_xs[ii]*0.001/deta;
      th_mcfm_xs_err[ii] = th_mcfm_xs_err[ii]*0.001/deta;
      printf("bin %d, center %.1f,  xs %f, err %f \n", ii, th_mcfm_bin[ii], th_mcfm_xs[ii], th_mcfm_xs_err[ii]);
    }
    double th_mcfm_xs_newbin[30];
    double th_mcfm_xs_err_newbin[30];
    for(int ii=0; ii<30; ii++){th_mcfm_xs_newbin[ii]=0.;th_mcfm_xs_err_newbin[ii]=0.;}
    for(int ii=0; ii<41; ii++){
      int tmp_bin = ptbin_index( th_mcfm_bin[ii] );
      th_mcfm_xs_newbin[tmp_bin] += th_mcfm_xs[ii]*th_mcfm_bin_err[ii]*2.;
      th_mcfm_xs_err_newbin[tmp_bin] += (th_mcfm_xs_err[ii]/th_mcfm_xs[ii]) * (th_mcfm_xs_err[ii]/th_mcfm_xs[ii]);
      printf("newbin %d, old bin %d, xs integrate %f, xs_err %f \n", tmp_bin, ii, th_mcfm_xs_newbin[tmp_bin], th_mcfm_xs_err_newbin[tmp_bin]);
    }
    for(int ii=0; ii<21; ii++){
      //printf("bin %d, value %f, %f, %f\n", ii, th_mcfm_xs_newbin[ii], th_mcfm_xs_err_newbin[ii], h_th_mcfm_xs->GetBinWidth(ii+1));
      h_th_mcfm_xs->SetBinContent(ii+1, th_mcfm_xs_newbin[ii]/h_th_mcfm_xs->GetBinWidth(ii+1));
      h_th_mcfm_xs->SetBinError(ii+1, TMath::Sqrt(th_mcfm_xs_err_newbin[ii]) * th_mcfm_xs_newbin[ii]/h_th_mcfm_xs->GetBinWidth(ii+1) );
      printf("bin %d, value %f, %f, %f\n", ii, th_mcfm_xs_newbin[ii], th_mcfm_xs_err_newbin[ii], h_th_mcfm_xs->GetBinWidth(ii+1));
      h_th_mcfm_xs_err->SetBinContent(ii+1, 1.);
      h_th_mcfm_xs_err->SetBinError(ii+1, h_th_mcfm_xs->GetBinError(ii+1));
    }
    
    
    pad1->cd();
    h_th_mcfm_xs->Draw("same ple");
    TH1F *h_xs_ratio_mcfm = (TH1F*)h_xs->Clone();
    printf("entry %f, xs %f , mcfm %f \n", h_xs_ratio_mcfm->GetBinCenter(14), h_xs_ratio_mcfm->GetBinContent(14), h_th_mcfm_xs->GetBinContent(14));
    
    //h_xs_ratio_mcfm->Divide(h_th_mcfm_xs);
    for(int ibin=13; ibin<=21; ibin++){
      h_xs_ratio_mcfm->SetBinContent(ibin, h_xs_ratio_mcfm->GetBinContent(ibin)/h_th_mcfm_xs->GetBinContent(ibin));
      double tmperr = (h_xs_ratio_mcfm->GetBinError(ibin)/h_xs_ratio_mcfm->GetBinContent(ibin))*
	(h_xs_ratio_mcfm->GetBinError(ibin)/h_xs_ratio_mcfm->GetBinContent(ibin)) +
	(h_th_mcfm_xs->GetBinError(ibin)/h_th_mcfm_xs->GetBinContent(ibin))*
	(h_th_mcfm_xs->GetBinError(ibin)/h_th_mcfm_xs->GetBinContent(ibin));
      tmperr = TMath::Sqrt(tmperr)*h_xs_ratio_mcfm->GetBinContent(ibin)/h_th_mcfm_xs->GetBinContent(ibin);
      h_xs_ratio_mcfm->SetBinError(ibin, tmperr); 
    }
    printf("entry %f, xs %f \n", h_xs_ratio_mcfm->GetBinCenter(14), h_xs_ratio_mcfm->GetBinContent(14));
    
    pad2->cd();
    h_th_mcfm_xs_err->SetFillColor(28);
    h_th_mcfm_xs_err->SetFillStyle(3004);
    h_th_mcfm_xs_err->SetMarkerStyle(0);
    h_th_mcfm_xs_err->Draw("e2 same");
    h_xs_ratio_mcfm->SetMarkerStyle(22);
    h_xs_ratio_mcfm->SetMarkerColor(4);
    h_xs_ratio_mcfm->SetLineColor(4);
    h_xs_ratio_mcfm->Draw("pe0 same");
    gPad->RedrawAxis();
  }


}

void Draw_yield_eta(int ptbin=17){
  double *fitted;

  float etaedge[19]={-2.5, -2.4, -2.3, -2.2, -2.1, -1.566, -1.4442, -0.8, 0., 0.8, 1.4442, 1.566, 2.1, 2.2, 2.3, 2.4, 2.5};
  int netabin = 16;
  
  // int netabin=5;
  // float etaedge[5]={0., 0.8, 1.4442, 1.566, 2.1, 2.5};
 
  TH1F *hdata = new TH1F("hdata","data", netabin, etaedge);
  float MG_Kfactor=1.6;

  hdata->Sumw2();

  // h1->SetNdivisions(505,"XY");
  // h2->SetNdivisions(505,"XY");

  for (int i=0; i<netabin-2; i++) {    
    //for (int i=0; i<netabin-1; i++) {    
    fitted = Ifit(ptbin, i, 1, 2);
    int ibin=i+1;
    if(netabin==16){
      if(i>=5) ibin++;
      if(i>=9) ibin++;
    }else {
      if(i>=2) ibin++;
    }
    hdata->SetBinContent(ibin,(fitted[0])/hdata->GetBinWidth(ibin)/2.);
    if(i<=1)
      hdata->SetBinError(ibin,(fitted[1])/hdata->GetBinWidth(ibin)/2.); //EE sys
    else
      hdata->SetBinError(ibin,(fitted[1])/hdata->GetBinWidth(ibin)/2.); //EB sys
    printf("bin %d, %d, BinCenter %.2f, fitted %f \n", i, ibin, hdata->GetBinCenter(ibin), fitted[0]);
  }
  hdata->SetMarkerStyle(8);
  hdata->SetNdivisions(505,"XY");
  hdata->SetMaximum(hdata->GetMaximum()*1.5);
  hdata->SetXTitle("#eta_{#gamma}");
  hdata->SetYTitle("yield / deta");

  hdata->SetTitle("");



  TCanvas *c12 = new TCanvas("c12","",600,600);  
  c12->Draw();

  TPad* pad1 = new TPad("pad1","",0.02, 0.30, 0.99, 0.99);
  TPad* pad2 = new TPad("pad1","",0.02, 0.02, 0.99, 0.30);
  // pad1->SetLeftMargin(0.02);
  pad1->SetRightMargin(0.035);
  // pad1->SetTopMargin(0.02); 
  pad1->SetBottomMargin(0.04);
  pad1->SetFrameBorderMode(0);
  pad1->SetBorderMode(0);
  pad1->SetBorderSize(0);

  // pad2->SetLeftMargin(0.02);
  pad2->SetRightMargin(0.035);
  pad2->SetTopMargin(0.04);
  pad2->SetBottomMargin(0.2);
  pad2->SetFrameBorderMode(0);
  pad2->SetBorderMode(0);
  pad2->SetBorderSize(0);


  pad1->Draw();
  pad2->Draw();
  
  pad1->cd();
  //gPad->SetLogy();
  

  hdata->Draw("pe0");

  printf("Get MadGraph entries \n");
  TFile *fMG = new TFile("isovsbdt_template.root");
  
  TH1F *hMG = new TH1F("hMG","MadGraph", netabin, etaedge);
  hMG->Sumw2();
  
  char hname[100];
  for(int i=0; i<netabin-2; i++){
    //for(int i=0; i<netabin-1; i++){
    int ibin=i+1;
    //if(i>=2) ibin++;
    if(netabin==16){
      if(i>=5) ibin++;
      if(i>=9) ibin++;
    }else {
      if(i>=2) ibin++;
    }
    sprintf(hname,"gjet_%d_2_%d_px1_chIso", i, ptbin);
    TH1F *h1 = (TH1F*)fMG->Get(hname);
    Double_t err;
    Double_t area = h1->IntegralAndError(1,1000,err);
    hMG->SetBinContent(ibin, area*2.3*MG_Kfactor/hMG->GetBinWidth(ibin));
    hMG->SetBinError(ibin,err*2.3*MG_Kfactor/hMG->GetBinWidth(ibin));
  }

  hMG->SetLineColor(2);
  hMG->Draw("eh same");

  TLegend *tleg = new TLegend(0.2, 0.7, 0.8, 0.9);
  //tleg->SetHeader("300GeV < E_{T}^{#gamma} < 350GeV");
  char txt[100];
  sprintf(txt,"%d GeV < E_{T}^{#gamma} < %d GeV",ptbin_lowedge(ptbin),ptbin_lowedge(ptbin+1));
  tleg->SetHeader(txt);
  tleg->SetFillStyle(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);
  tleg->SetTextSize(0.04);
  tleg->AddEntry(hdata,"data 2.3fb^{-1}","pl");  
  sprintf(txt,"MadGraph * %.1f", MG_Kfactor);
  tleg->AddEntry(hMG,txt,"fb");
  tleg->Draw();
  
  gPad->RedrawAxis();



  pad2->cd();
  gPad->SetGridy();
  gPad->SetGridx();

  TH1F* hratio = (TH1F*)hdata->Clone();
  hratio->Divide(hMG);
  hratio->SetXTitle(hratio->GetTitle());
  hratio->SetYTitle("Data / MC");
  hratio->GetXaxis()->SetLabelSize(0.085);
  hratio->GetYaxis()->SetLabelSize(0.08);
  hratio->GetXaxis()->SetTitleSize(0.09);
  hratio->GetYaxis()->SetTitleSize(0.09);
  hratio->GetXaxis()->SetTitleOffset(1.);
  hratio->GetYaxis()->SetTitleOffset(0.5);
  hratio->SetTitle("");
  hratio->SetNdivisions(505,"X");
  hratio->SetNdivisions(105,"Y");
  hratio->SetMinimum(0.);
  hratio->SetMaximum(2.);

  // if(ivar ==15) hratio->GetXaxis()->SetRangeUser(0.75,1.0);
  hratio->Draw("pe"); 
  

}

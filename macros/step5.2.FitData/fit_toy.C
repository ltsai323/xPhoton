#include "TH2.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TF1.h"
#include <fstream>
#include <iostream>
#include <TMinuit.h>
#include <vector>
#include <TMath.h>
#include "TVirtualFitter.h"
#include "TFile.h"
#include "TLegend.h"
#include "TMarker.h"
#include "TLine.h"
#include "TRandom2.h"
#include <stdio.h>


using namespace std;



#define NPAR 3

//int PTBIN = 2;

TF1* fchi2;
//TH1F* h1;
TF1* bsFin;

// Remember to change the values of xh and xl in all_tree.C too!!!
//Double_t xh = 6.5;
//Double_t xl = 4.5;
Double_t xl = -1.;
Double_t xh = 1.;
Double_t bin_size = 0.05;

const double _two_pi = 2.0 * TMath::Pi();
Double_t fit_lo_edge = -1.;
Double_t fit_hi_edge = 1.;


vector<Double_t> dataColl;
vector<Double_t> sigColl;
vector<Double_t> bkgColl;
vector<Double_t> bkg2Coll;

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
  Double_t fb2 = par[2];

  for ( int i=0; i<dataColl.size(); i++ ) {
    Nevt += dataColl[i];
    //PDF for signal and background
    //PDF for signal and background
    Double_t Ls = sigColl[i]; if(Ls<0.) Ls=0.;
    Double_t Lb = bkgColl[i]; if(Lb<0.) Lb=0.;
    Double_t Lb2 = bkg2Coll[i]; if(Lb<0.) Lb=0.;
    for (int data=0; data<dataColl[i]; data++) {	
      //Get Log Likelihood
      if(Ls!=0. ||  Lb!=0. || Lb2!=0) Lsum += TMath::Log( (fs*Ls+ fb*Lb+ fb2*Lb2)/(fs+fb+fb2) );
      //if(Ls!=0. ||  Lb!=0. || Lb2!=0) Lsum += TMath::Log( ( (fs/(fs+fb+fb2))*(fs/(fs+fb))*Ls + (fb/(fs+fb+fb2))*(fb/(fs+fb))*Lb + (fb2/(fs+fb+fb2))*Lb2) );
    }
  }
  //f=2*( -1*Lsum  );
  f=2*( -1*Lsum + (fs+fb+fb2) - Nevt*TMath::Log(fs+fb+fb2) );
  
}


//___________________________________________________________________________
Double_t* Ifit(int PTBIN, float &w_L, float &w_C, float &w_B, char EBEE[10]="EB", int fit_data=1)//////Ifit
{
  printf("%d", PTBIN);
  TCanvas *c1 = new TCanvas("HF1", "Histos1", 0, 0, 600, 600);
  double count=0;
  dataColl.clear();
  sigColl.clear();
  bkgColl.clear();
  bkg2Coll.clear();//

  totalColl.clear();
  ctauColl.clear();

 //Get data from looping tree
  TFile *ftemplate2 = new TFile("./templates.root");
  TFile *ftemplate = new TFile("./templates.root");

  float ptmax = 20;
/*
  if (ptbin==20) ptmax=30;
  if (ptbin==30) ptmax=50;
  if (ptbin==50) ptmax=80;
  if (ptbin==80) ptmax=120;
*/
  TH1F *hsig = new TH1F();

  char hname[30];

  //sprintf(hname,"h_%s_ESRatio_sig_pt%d",EBEE, ptbin);
  sprintf(hname,"h_jettag_0_%d_0_0_2", PTBIN);
  //sprintf(hname,"l", PTBIN);
  //hsig = (TH1F*)ftemplate->Get(hname); 
  hsig = (TH1F*)ftemplate->Get("MC_tag0_L"); 

  //sprintf(hname,"h_%s_ESRatioSB_bkg_pt%d",EBEE, ptbin);
  sprintf(hname,"h_jettag_0_%d_0_1_2", PTBIN);
  //sprintf(hname,"b", PTBIN);
  //TH1F *hbkg = (TH1F*)ftemplate->Get(hname);
  TH1F *hbkg = (TH1F*)ftemplate->Get("MC_tag0_C");

  //sprintf(hname,"h_%s_ESRatioSB_bkg_pt%d",EBEE, ptbin);
  sprintf(hname,"h_jettag_0_%d_0_2_2", PTBIN);
  //sprintf(hname,"c", PTBIN);
//  TH1F *hbkg2 = (TH1F*)ftemplate->Get(hname);//
  TH1F *hbkg2 = (TH1F*)ftemplate->Get("MC_tag0_B");

  //sprintf(hname,"h_%s_ESRatio_EGdata_pt%d",EBEE, ptbin);
  sprintf(hname,"h_jettag_0_%d_0_0_2", PTBIN);
  //sprintf(hname,"data", PTBIN);
//  TH1F *hEGdata = (TH1F*)ftemplate2->Get(hname);////////////////////////////////////////////////////////////////////////
TH1F *hEGdata = (TH1F*)ftemplate2->Get("DATA_tag0");
  //sprintf(hname,"h_btag_mc_%d", PTBIN);
  //TH1F *hEGdata = (TH1F*)ftemplate->Get(hname);

  /*
  hsig->Rebin(10);
  hbkg->Rebin(10);
  hbkg2->Rebin(10);//10->2
  hEGdata->Rebin(10);
  */
  
  hsig->Sumw2();
  hbkg->Sumw2();
  hbkg2->Sumw2();
  hEGdata->Sumw2();

  TH1F *hsum = new TH1F();
  int ntemplate = 1.;
  float sigfrac = 0.1;
  float backfrac = 0.1;
  TH1F *hsum_norm = new TH1F();
  TH1F *hdata = new TH1F();

  Double_t* fitted = new Double_t[4];
  int ndata=0;
  if ( fit_data>0 ) {
    hdata = (TH1F*)hEGdata->Clone();
    ndata = hdata->GetEntries();
  }else {/// hsum = hsig+hbkg+hbkg2
    hsum = (TH1F*)hsig->Clone();
    hsum->Add(hbkg,1);
    hsum->Add(hbkg2,1);
    if (hsum->Integral()>1.) ntemplate = hsum->Integral(); // ntemplate is the total numbers of l+b+c
    sigfrac = hsig->Integral()/ntemplate; //pick the starting point for b-jet (b/(l+b+c))
    backfrac = hbkg->Integral()/ntemplate; //pick the starting point for light-jet (l/(l+b+c))  ??this part didn't work
    printf("the sigfrac is %f \n", sigfrac);
    printf("the backfrac is %f \n", backfrac);
    /// ???

    hsum_norm = (TH1F*)hsum->Clone();  
    hsum_norm->Scale(1./hsum->Integral());

    hdata = (TH1F*)hsum_norm->Clone();
    //ndata = (int) gRandom->Poisson(hsum->Integral());
    ndata=ntemplate;
    hdata->FillRandom(hsum_norm, ndata);
  }
  if(ndata==0) {
    printf(" ---  no events in the fit \n");
    fitted[0] = 0.;
    fitted[1] = 0.;
    fitted[2] = 0.;
    fitted[3] = 0.;
    return fitted;
  }
    
  printf(" --------- before the fit ------------- \n");
  printf("Nsig %2.3f, Nbg %2.3f, Ntemplate %3.3f \n", hsig->Integral(), hbkg->Integral(), ntemplate);
  printf("Purity %2.3f, init size %4.3f,  test sample size %4d\n", hsig->Integral()/hsum->Integral(), hsum->Integral(), ndata);
  printf(" -------------------------------------- \n");

  int nbins = hdata->GetNbinsX();

  hsig->Scale(1./hsig->Integral());
  hbkg->Scale(1./hbkg->Integral()); 
  hbkg2->Scale(1./hbkg2->Integral());/////////////////////////////////////////
  for (int ibin=1; ibin<=nbins; ibin++) {
    dataColl.push_back(hdata->GetBinContent(ibin));
    sigColl.push_back(hsig->GetBinContent(ibin));
    bkgColl.push_back(hbkg->GetBinContent(ibin));   
    bkg2Coll.push_back(hbkg2->GetBinContent(ibin));/////////////////////////////////////////
  }
  printf( " -----  Got %d, %d, %d, %d events for fit ----- \n ", dataColl.size(),
	  sigColl.size(), bkgColl.size(), bkg2Coll.size() );  
  if ( dataColl.size() != sigColl.size() || sigColl.size()!=bkgColl.size() ) {
    printf(" error ...  inconsistent hit collection size \n");
    return fitted;
  }

  //--------------------------------------------------
  //init parameters for fit
  Double_t vstart[10] = {1., 1., 1.};//Double_t vstart[10] = {1., 1., 1.};
  vstart[0] = sigfrac*ndata;
  vstart[1] = backfrac*ndata;
  vstart[2] = (1-sigfrac-backfrac)*ndata;
 
  TMinuit *gMinuit = new TMinuit(NPAR);  
  gMinuit->Command("SET STR 1");
  gMinuit->SetFCN(fcn);
  Double_t arglist[10];
  Int_t ierflg = 0;
  
  arglist[0] = 1;
  gMinuit->mnexcm("SET ERR", arglist ,1,ierflg);
  arglist[0] = 1;
  gMinuit->mnexcm("SET PRINT", arglist ,1,ierflg);

  Double_t step[] = { 0.1, 0.1, 0.1};

  gMinuit->mnparm(0,  "Signal yield"  , vstart[0],  step[0], 0., ndata*2.  , ierflg);
  gMinuit->mnparm(1,  "background yield"  , vstart[1],  step[1], 0., ndata*2. , ierflg);
  gMinuit->mnparm(2,  "background yield2"  , vstart[2],  step[2], 0., ndata*2. , ierflg);///////////////////////////ndata*2 ???
  
  printf(" --------------------------------------------------------- \n");
  printf(" Now ready for minimization step \n --------------------------------------------------------- \n");
  
  arglist[0] = 2000; // number of iteration
  arglist[1] = 1.;
  gMinuit->mnexcm("MIGRAD", arglist , 3 , ierflg); ////////////////////////////2->3
  printf (" -------------------------------------------- \n");
  printf("Finished.  ierr = %3.3f \n", ierflg); //////2.2f->3.3f

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
      printf(" fitted yield %2.3f \n", (para[0]+para[1]+para[2])/ndata );
      
      printf("########################\n");
      printf("%f \t %f \t %f \n", para[0]/(para[0]+para[1]+para[2]), para[1]/(para[0]+para[1]+para[2]), para[2]/(para[0]+para[1]+para[2]));
      printf("########################\n");
      info.push_back(sigColl.size());

      //do minos if fit sucessed.
//       printf("         ---------------------------------------------------------\n");
//       printf("          Now call for minos step \n");
//       printf("         ---------------------------------------------------------\n");
      
//       arglist[0] = 200; // number of iteration
//       arglist[1] = 1;
//       gMinuit->mnexcm("MINOS", arglist ,2,ierflg);
//       printf("         --------------------------------------------------------- \n");
//       printf("         Done Minos.  ierr = %d \n", ierflg);
//       Double_t amin;
//       gMinuit->mnprin(1,amin);
    }
  else {
    printf(" *********** Fit failed! ************\n");
    gMinuit->GetParameter(0, para[0],errpara[0]);
    gMinuit->GetParameter(1, para[1],errpara[1]);
    gMinuit->GetParameter(2, para[2],errpara[2]);
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

  double yerr[20];
  for(int i=0;i<20;i++){
    yerr[i] = 0.;
  }

  hsig->Scale(para[0]);
  hbkg->Scale(para[1]);
  hbkg2->Scale(para[2]);
  TH1F *hfit = (TH1F*)hsig->Clone();
  hfit->Add(hbkg);
  hfit->Add(hbkg2);
  


   hsig->SetLineColor(2);//////////////////////////////
   hbkg->SetLineColor(3);
   hbkg2->SetLineColor(4);
//   hsig->SetFillColor(5);
//   hsig->SetFillStyle(3001);

//   hbkg->SetLineWidth(2);
  // plot
  c1->Draw();  
  //gPad->SetLogy();
  hdata->SetLineColor(1);

  hdata->SetNdivisions(505,"XY");
  hdata->SetXTitle("btagger");
  hdata->SetYTitle("Entries");
  hdata->SetTitle("");
  hdata->SetMarkerStyle(8);
  hdata->SetMinimum(0.);
  hdata->SetMaximum(hdata->GetMaximum()*1.4);
  if ( hfit->GetMaximum() > hdata->GetMaximum() ) hdata->SetMaximum(hfit->GetMaximum()*1.4);
  if ( hdata->GetMaximum() < 15 ) hdata->SetMaximum(15);
  hdata->SetStats(0);
  hdata->Draw("p e");
  
  hsig->SetMarkerStyle(0);
  hsig->SetStats(0);
  hsig->Draw("h same");
  hbkg->SetMarkerStyle(0);
//   hbkg->SetFillColor(8);
  hbkg->SetLineWidth(1);
  hbkg2->SetMarkerStyle(0);
//   hbkg->SetFillColor(8);
  hbkg2->SetLineWidth(1);
  //hbkg->SetLineColor(2);
//   hbkg->SetFillStyle(3013);
//   hbkg->SetError(yerr);
//   hbkg->SetError(yerr);

  hbkg2->SetStats(0);
  hbkg->SetStats(0);
  hsig->SetStats(0);
  hbkg2->Draw("h same");
  hbkg->Draw("h same");
  hsig->Draw("h same");


  hfit->SetMarkerStyle(0);
  hfit->SetLineColor(1);
  hfit->SetLineWidth(2);
  hfit->SetError(yerr);
  hfit->SetStats(0);
  hfit->Draw("h same");
  hdata->SetStats(0);
  hdata->Draw("p e same");

   TLegend *tleg = new TLegend(0.1, 0.65, 0.65, 0.9); //0.4, 0.65, 0.95, 0.9);
   //TLegend *tleg = new TLegend(0.4, 0.65, 0.95, 0.9);
   char text[50];
   sprintf(text,"CvsB");////////////////////////////////////////////////////////////////////////////////////
   tleg->SetHeader(text);
   //tleg->SetFillColor(0);
   tleg->SetShadowColor(0);
   tleg->SetBorderSize(0);
   
   sprintf(text,"Data %5.1f events",hdata->Integral());
   tleg->AddEntry(hdata,text,"pl");
   sprintf(text,"Fitted %5.1f events",hfit->Integral());
   tleg->AddEntry(hfit,text,"l");

   sprintf(text,"light-jet %5.1f #pm %5.1f events",para[0], errpara[0]);
   tleg->AddEntry(hsig,text,"f");////
   sprintf(text,"c-jet %5.1f #pm %5.1f events",para[1], errpara[1]);
   tleg->AddEntry(hbkg,text,"f");////
   sprintf(text,"b-jet %5.1f #pm %5.1f events",para[2], errpara[2]);
   tleg->AddEntry(hbkg2,text,"f");
   
   tleg->Draw();

   gPad->RedrawAxis();

   printf("%s Data %5.1f events, fitted %5.1f\n", EBEE, hdata->Integral(), hfit->Integral());
   printf("%s Data %5.1f, and fitted (in 5GeV) %5.1f events \n", EBEE, hdata->Integral(1,10), hfit->Integral(1,10));
   printf("%s SIG %5.1f #pm %5.1f events \n", EBEE, para[0], errpara[0]);
   printf("%s SIG (in 5GeV) %5.1f #pm %5.1f events \n", EBEE, hsig->Integral(1,10), hsig->Integral(1,10)*errpara[0]/para[0]);
   printf("%s BKG %5.1f #pm %5.1f events \n", EBEE, para[1], errpara[1]);
   printf("%s BKG (in 5GeV) %5.1f #pm %5.1f events \n", EBEE, hbkg->Integral(1,10), hbkg->Integral(1,10)*errpara[1]/para[1]);
   

  char fname[30];
  sprintf(fname,"plots/fit_CvsB_%d.png", PTBIN);//////////////////////////////PTBIN
  c1->SaveAs(fname);

  printf("----- fit results with signal projection   ----------- \n");
  hdata->Chi2Test(hfit,"P");

//   ftemplate->Close();

  fitted[0] = para[0];
  fitted[1] = errpara[0];
  fitted[2] = para[1];
  if (fit_data==2 ) fitted[2] += hdata->GetBinContent(hdata->GetNbinsX()+1);
  fitted[3] = errpara[1];

  w_L = para[0];
  w_C = para[1];
  w_B = para[2];
  return fitted;
  //return para[0]/(para[0]+para[1]+para[2]), para[1]/(para[0]+para[1]+para[2]), para[2]/(para[0]+para[1]+para[2]);
}

void pulltest(int ptbin=15, char EBEE[10]="EB", float input=0.5){


  TH1F *h1 = new TH1F("h1","",100,-10., 10.);
  TH1F *h2 = new TH1F("h2","",3000, 0., 3000);

  h1->SetNdivisions(505,"XY");
  h2->SetNdivisions(505,"XY");

  int nexp=1000;
  Double_t Nevt=0.;

  for (int i=0; i<nexp; i++) {
    //Ifit(ptbin,EBEE);
    Nevt=0.;
    for ( int ii=0; ii<dataColl.size(); ii++ ) {
      Nevt += dataColl[ii];
    }
    printf("fit purity %2.2f +- %2.2f err with %d events. \n", info[0], info_err[0], Nevt);
    h1->Fill((info[0]/Nevt-input)/(info_err[0]/Nevt));
    h2->Fill(info[0]);
  }    

  TCanvas *c2 = new TCanvas("c2","",1000,500);
  c2->Divide(2,1);
  c2->cd(1);
  char txt[100];
  sprintf(txt, "(purity-input)/error");
  h1->SetXTitle(txt);
  h1->Fit("gaus");
  h1->Draw();
  c2->cd(2);
  sprintf(txt, "fitted signal (input %d)", input*Nevt);
  h2->SetXTitle(txt);
  h2->Fit("gaus");
  h2->GetXaxis()->SetRangeUser(0., Nevt*1.2);
  if ( input >0.8 )  h2->GetXaxis()->SetRangeUser(0., Nevt*1.4);
  h2->Draw();  
  //sprintf(txt, "plots/fit_%d.png", PTBIN);//////////////////PTBIN
  //c2->SaveAs(txt);

  
}


int fit_toy(int argc = 0)
{
    //do the fit for particular ptbin (1~24):
    //root.exe .x 'fit_btag.C(5)'

    float w_L, w_C, w_B;
    float ar_L[24], ar_C[24], ar_B[24];
    if(argc != 0){
    	Ifit(argc, w_L, w_C, w_B);
    	printf("%f, %f, %f, \n", w_L, w_C, w_B);
    }else{
	//for(int i=0; i<24; i++){
	for(int i=0; i<1; i++){
		Ifit(i+1, w_L, w_C, w_B);
	        printf("%f, %f, %f, \n", w_L, w_C, w_B);
		ar_L[i] = w_L;
		ar_C[i] = w_C;
		ar_B[i] = w_B;
	}
	printf("weight_L:\n");
	for(int i=0; i<24; i++){
		printf("%f, ", ar_L[i]);
	}
	printf("\n");

	printf("weight_C:\n");
	for(int i=0; i<24; i++){
                printf("%f, ", ar_C[i]);
        }
        printf("\n");

	printf("weight_B:\n");
	for(int i=0; i<24; i++){
                printf("%f, ", ar_B[i]);
        }
        printf("\n");

    }
    return 0;
}

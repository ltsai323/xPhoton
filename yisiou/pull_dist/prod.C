#include "TRandom3.h"
#include <TH1.h>

void prod(int ptbin = 0){

TFile *toymc    = new TFile("../step3/toy_mc.root");
TFile *mc  = new TFile("../step2_makehisto/storeroot_weightcut1/makehisto_sig_madgraph.root");

///toymc
//b+bb
TH1F *btag_l = (TH1F*)toymc->Get("tag0_L");
TH1F *btag_c = (TH1F*)toymc->Get("tag0_C");
TH1F *btag_b = (TH1F*)toymc->Get("tag0_B");
//cvsl
TH1F *cvsl_l = (TH1F*)toymc->Get("tag1_L");
TH1F *cvsl_c = (TH1F*)toymc->Get("tag1_C");
TH1F *cvsl_b = (TH1F*)toymc->Get("tag1_B");
//cvsb
TH1F *cvsb_l = (TH1F*)toymc->Get("tag2_L");
TH1F *cvsb_c = (TH1F*)toymc->Get("tag2_C");
TH1F *cvsb_b = (TH1F*)toymc->Get("tag2_B");
//svxmass
TH1F *mass_l = (TH1F*)toymc->Get("tag3_L");
TH1F *mass_c = (TH1F*)toymc->Get("tag3_C");
TH1F *mass_b = (TH1F*)toymc->Get("tag3_B");


///mc
TH1F *mc_l = (TH1F*)mc->Get(Form("h_jettag_0_%d_0_0_0_1", ptbin));
TH1F *mc_c = (TH1F*)mc->Get(Form("h_jettag_0_%d_0_1_0_1", ptbin));
TH1F *mc_b = (TH1F*)mc->Get(Form("h_jettag_0_%d_0_2_0_1", ptbin));


 cout << ptbin << endl;

TH1F *btag = new TH1F("btag","btag",10,0.,1.);
TH1F *cvsl = new TH1F("cvsl","cvsl",10,0.,1.);
TH1F *cvsb = new TH1F("cvsb","cvsb",10,0.,1.);
TH1F *mass = new TH1F("mass","mass",10,0.,5.);


if(gRandom) delete gRandom;
gRandom = new TRandom3(0);

float num1,num2,num3;

num1 = mc_l->Integral();
num2 = mc_c->Integral();
num3 = mc_b->Integral();
cout << num1 << " " << num2 << " " << num3 << endl;

btag->FillRandom(btag_l,num1);
btag->FillRandom(btag_c,num2);
btag->FillRandom(btag_b,num3);

cvsl->FillRandom(cvsl_l,num1);
cvsl->FillRandom(cvsl_c,num2);
cvsl->FillRandom(cvsl_b,num3);

cvsb->FillRandom(cvsb_l,num1);
cvsb->FillRandom(cvsb_c,num2);
cvsb->FillRandom(cvsb_b,num3);

mass->FillRandom(mass_l,num1);
mass->FillRandom(mass_c,num2);
mass->FillRandom(mass_b,num3);

TFile *f = new TFile("./toy.root","recreate");

   btag->Write();
   cvsl->Write();
   cvsb->Write();
   mass->Write();


f->Close();
}

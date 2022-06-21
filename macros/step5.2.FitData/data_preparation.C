#include <TH1.h>
#include <TH2.h>
#include <cmath>
#define NUM_FLVR 3  // light, c, b ( + FAKE ) 
#define NUM_TAGR 4  // b+bb, cvsl, cvsb, svxmass
#define NUM_PRTY 2  // even, odd
#define PHOETA 0
#define JETETA 0

void data_preparation(int ptbin = 0){

//TFile *mc  = new TFile("../step2.makehistos/storeroot0/makehisto_sig_madgraph.root");
//TFile *data = new TFile("../step2.makehistos/storeroot0/makehisto_data.root");
TFile *mc   = new TFile("../makehisto_sig.root");
TFile *data = new TFile("../makehisto_data.root");
TFile *bdt  = new TFile("../isovsbdt_template.root");
//data_0_0_0_px2_chIso
//EBEE, jetBin, ptBin
//for mc[--][tagr] -> data(b+bb)_0_0_ptbin_px2_chIso + data(b+bb)_0_1_ptbin_px2_chIso
cout << "ptbin is " << ptbin << endl;

//MC
TH2F *h_mc[NUM_FLVR+1][NUM_TAGR]; //(L, C, B, and FAKE)
TH1F *h_mc_1D[NUM_FLVR+1][NUM_TAGR]; 
//DATA
TH2F *h_data[NUM_TAGR];
TH1F *h_data_1D[NUM_TAGR];

const int tagrIdx_svxmass=3;
const std::vector< int > matchIdx = { 0, 2, 3 };
const std::vector< const char* > jetFlvr = { "L", "C", "B", "FAKE" };
const std::vector< const char* > jetFlvrNames = { "sigma", "alpha", "beta" };
const std::vector< const char* > VarNames = { "deepCSVDiscriminatorTags_BvsAll", "deepCSVDiscriminatorTags_CvsL", "deepCSVDiscriminatorTags_CvsB", "subVtxMass" };

 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
   int xbin = tagrIdx == tagrIdx_svxmass ? 100 : 10;
   h_data[tagrIdx] = new TH2F( Form("tag%d", tagrIdx), Form("tag%d", tagrIdx), xbin, 0., upperboundary, 30, 0., 15.);
   h_data[tagrIdx]->Sumw2();

   for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
     h_mc[flvrIdx][tagrIdx] = new TH2F( Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), 
					Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), xbin, 0., upperboundary, 30, 0., 15.);
     h_mc[flvrIdx][tagrIdx]->Sumw2();
     
     for(int prtyIdx = 0; prtyIdx < NUM_PRTY; prtyIdx++) {
       h_mc[flvrIdx][tagrIdx]->Add( (TH2F*)mc->Get( Form("btagDeepCSV/btagDeepCSV.0_%d_%d__%d_%d_%d__0_%d", tagrIdx, flvrIdx, JETETA, PHOETA, ptbin, prtyIdx) ) ) ;
	cout << h_mc[flvrIdx][tagrIdx]->GetNbinsX() << " " << h_mc[flvrIdx][tagrIdx]->GetNbinsY() << endl;
	h_mc_1D[flvrIdx][tagrIdx] = (TH1F*)h_mc[flvrIdx][tagrIdx] -> ProjectionX();
     }
   }

  for(int prtyIdx = 0; prtyIdx < NUM_PRTY; prtyIdx++) {
     h_data[tagrIdx]->Add( (TH2F*)data->Get( Form("btagDeepCSV/btagDeepCSV.0_%d_0__%d_%d_%d__0_%d", tagrIdx, JETETA, PHOETA, ptbin, prtyIdx) ) );
	h_data_1D[tagrIdx] = (TH1F*)h_data[tagrIdx] -> ProjectionX();}
	//   h_data[tagrIdx]->Rebin(10);
 }

 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++){
   float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
   int xbin = tagrIdx == tagrIdx_svxmass ? 100 : 10;
   h_mc[NUM_FLVR][tagrIdx] = new TH2F( Form("tag%d_%s", tagrIdx, jetFlvr[NUM_FLVR]), 
					 Form("tag%d_%s", tagrIdx, jetFlvr[NUM_FLVR]), xbin, 0., upperboundary, 30, 0., 15.);
   h_mc[NUM_FLVR][tagrIdx]->Sumw2();
  for(int prtyIdx = 0; prtyIdx < NUM_PRTY; prtyIdx++) {   
   h_mc[NUM_FLVR][tagrIdx]
	->Add( (TH2F*)data->Get( Form("btagDeepCSV/btagDeepCSV.0_%d_0__%d_%d_%d__1_%d", tagrIdx, JETETA, PHOETA, ptbin, prtyIdx) ) );}
   h_mc_1D[NUM_FLVR][tagrIdx] =  (TH1F*)h_mc[NUM_FLVR][tagrIdx] -> ProjectionX();

//   h_mc[NUM_FLVR][tagrIdx]->Rebin(10);
 }



///setname
//MC
 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   for(int flvrIdx = 0; flvrIdx < NUM_FLVR+1; flvrIdx++) {
	h_mc_1D[flvrIdx][tagrIdx] ->SetNameTitle(
                Form("MC_tag%d_%s", tagrIdx, jetFlvr[flvrIdx]),
                Form("MC_tag%d_%s", tagrIdx, jetFlvr[flvrIdx]));
   }
 }

//DATA
 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
        h_data_1D[tagrIdx] ->SetNameTitle(
                Form("DATA_tag%d", tagrIdx),
                Form("DATA_tag%d", tagrIdx));
}

//READ bkg entries dat file
  TTree* t = new TTree();
  t->ReadFile("../data.bkg.dat");
  t->SetDirectory(0);

  std::vector<Float_t> bkgentries;

  Int_t EBEE, jetbin;
  Float_t fitvalue;
  t->SetBranchAddress("EBEE", &EBEE);
  t->SetBranchAddress("jetbin", &jetbin);
  t->SetBranchAddress("fitvalue", &fitvalue);

  for(int jentry=0; jentry < t->GetEntries(); jentry++){
    t->GetEntry(jentry);
    if(EBEE==0 && jetbin==0) bkgentries.push_back(fitvalue);
  }

  //for(int i=0; i<bkgentries.size(); i++)
  //      cout << bkgentries[i] << endl ;


//WRITE
TFile *f = new TFile("./templates.root","recreate");

 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   for(int flvrIdx = 0; flvrIdx < NUM_FLVR+1; flvrIdx++) {
     h_mc_1D[flvrIdx][tagrIdx]->Scale(1./h_mc_1D[flvrIdx][tagrIdx]->Integral());
     if (flvrIdx == NUM_FLVR)
       h_mc_1D[flvrIdx][tagrIdx]->Scale(bkgentries[ptbin]);
     h_mc_1D[flvrIdx][tagrIdx]->Write();
   }
   h_data_1D[tagrIdx]->Write();
 }
 cout << bkgentries[ptbin] << endl;
   f->Close();
/*
  TCanvas *c1 = new TCanvas("c1","c1",800, 600);
char fname[100];
 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   for(int flvrIdx = 0; flvrIdx < NUM_FLVR+1; flvrIdx++) {
        h_mc[flvrIdx][tagrIdx]->Draw("h");
  	sprintf(fname,"./plots/MC_tag%d_%s.png",tagrIdx, jetFlvr[flvrIdx]);
  	c1->SaveAs(fname);
	}
   	h_data[tagrIdx]->Draw("h");
        sprintf(fname,"./plots/DATA_tag%d.png",tagrIdx);
        c1->SaveAs(fname);
 }
*/

}

#include <TH1.h>
#include <cmath>
#define NUM_FLVR 3  // light, c, b ( + FAKE ) 
#define NUM_TAGR 4  // b+bb, cvsl, cvsb, svxmass
#define NUM_PRTY 2  // even, odd


void data_preparation(int ptbin = 0){

//TFile *mc  = new TFile("../step2.makehistos/storeroot0/makehisto_sig_madgraph.root");
//TFile *data = new TFile("../step2.makehistos/storeroot0/makehisto_data.root");
TFile *mc   = new TFile("../step2.makehistos/storeroot_mcweightcut_on_lightcut_1/makehisto_sig_madgraph.root");
TFile *data = new TFile("../step2.makehistos/storeroot_mcweightcut_on_lightcut_1/makehisto_data.root");
TFile *bdt  = new TFile("../step3.DrawIsoBDT/isovsbdt_template.root");
//data_0_0_0_px2_chIso
//EBEE, jetBin, ptBin
//for mc[--][tagr] -> data(b+bb)_0_0_ptbin_px2_chIso + data(b+bb)_0_1_ptbin_px2_chIso
cout << "ptbin is " << ptbin << endl;

//MC
TH1F *h_mc[NUM_FLVR+1][NUM_TAGR]; //(L, C, B, and FAKE)
//DATA
TH1F *h_data[NUM_TAGR];

const int tagrIdx_svxmass=3;
const std::vector< int > matchIdx = { 0, 2, 3 };
const std::vector< const char* > jetFlvr = { "L", "C", "B", "FAKE" };
const std::vector< const char* > jetFlvrNames = { "sigma", "alpha", "beta" };
const std::vector< const char* > VarNames = { "deepCSVDiscriminatorTags_BvsAll", "deepCSVDiscriminatorTags_CvsL", "deepCSVDiscriminatorTags_CvsB", "subVtxMass" };

 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
   h_data[tagrIdx] = new TH1F( Form("tag%d", tagrIdx), 
			       Form("tag%d", tagrIdx), 100, 0., upperboundary);
   h_data[tagrIdx]->Sumw2();

   for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
     h_mc[flvrIdx][tagrIdx] = new TH1F( Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), 
					Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), 10, 0., upperboundary);
     h_mc[flvrIdx][tagrIdx]->Sumw2();
     
     for(int prtyIdx = 0; prtyIdx < NUM_PRTY; prtyIdx++) {
       h_mc[flvrIdx][tagrIdx]
	 ->Add( (TH1F*)mc->Get( Form("h_jettag_0_0_%d_0_%d_%d_%d", ptbin, flvrIdx, tagrIdx, prtyIdx) ) ) ;
     }
   }
   h_data[tagrIdx]
	->Add( (TH1F*)bdt->Get( Form("fitVars/data_%s_0_0_%d_px1", VarNames[tagrIdx], ptbin) ) ) ;
   h_data[tagrIdx]->Rebin(10);
 }

 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++){
   float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
   h_mc[NUM_FLVR][tagrIdx] = new TH1F( Form("tag%d_%s", tagrIdx, jetFlvr[NUM_FLVR]), 
					 Form("tag%d_%s", tagrIdx, jetFlvr[NUM_FLVR]), 100, 0., upperboundary);
   h_mc[NUM_FLVR][tagrIdx]->Sumw2();
   
   h_mc[NUM_FLVR][tagrIdx]
     ->Add( (TH1F*)bdt->Get( Form("fitVars/data_%s_0_0_%d_px2", VarNames[tagrIdx], ptbin) ) ) ;

   h_mc[NUM_FLVR][tagrIdx]->Rebin(10);
 }



///setname
//MC
 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   for(int flvrIdx = 0; flvrIdx < NUM_FLVR+1; flvrIdx++) {
	h_mc[flvrIdx][tagrIdx] ->SetNameTitle(
                Form("MC_tag%d_%s", tagrIdx, jetFlvr[flvrIdx]),
                Form("MC_tag%d_%s", tagrIdx, jetFlvr[flvrIdx]));
   }
 }

//DATA
 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
        h_data[tagrIdx] ->SetNameTitle(
                Form("DATA_tag%d", tagrIdx),
                Form("DATA_tag%d", tagrIdx));
}

//READ bkg entries dat file
  TTree* t = new TTree();
  t->ReadFile("./data_bkg.dat");
  t->SetDirectory(0);

  std::vector<Float_t> bkgentries;

  Int_t EBEE, jetbin;
  Float_t bkg;
  t->SetBranchAddress("EBEE", &EBEE);
  t->SetBranchAddress("jetbin", &jetbin);
  t->SetBranchAddress("bkg", &bkg);

  for(int jentry=0; jentry < t->GetEntries(); jentry++){
    t->GetEntry(jentry);
    if(EBEE==0 && jetbin==0) bkgentries.push_back(bkg);
  }

  //for(int i=0; i<bkgentries.size(); i++)
  //      cout << bkgentries[i] << endl ;


//WRITE
TFile *f = new TFile("./templates.root","recreate");

 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   for(int flvrIdx = 0; flvrIdx < NUM_FLVR+1; flvrIdx++) {
     h_mc[flvrIdx][tagrIdx]->Scale(1./h_mc[flvrIdx][tagrIdx]->Integral());
     if (flvrIdx == NUM_FLVR)
       h_mc[flvrIdx][tagrIdx]->Scale(bkgentries[ptbin]);
     h_mc[flvrIdx][tagrIdx]->Write();
   }
   h_data[tagrIdx]->Write();
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

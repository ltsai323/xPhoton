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
 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
   h_data[tagrIdx] = new TH1F( Form("tag%d", tagrIdx), 
			       Form("tag%d", tagrIdx), 10, 0., upperboundary);

   for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
     h_mc[flvrIdx][tagrIdx] = new TH1F( Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), 
					Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), 10, 0., upperboundary);
     
     for(int prtyIdx = 0; prtyIdx < NUM_PRTY; prtyIdx++) {
       h_mc[flvrIdx][tagrIdx]
	 ->Add( (TH1F*)mc->Get( Form("h_jettag_0_%d_0_%d_%d_%d", ptbin, flvrIdx, tagrIdx, prtyIdx) ) ) ;
       h_data[tagrIdx]
	 ->Add( (TH1F*)data->Get( Form("h_jettag_0_%d_0_%d_%d_%d", ptbin, flvrIdx, tagrIdx, prtyIdx) ) ) ;
     }
   }
 }

 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++){
   float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
   h_mc[NUM_FLVR][tagrIdx] = new TH1F( Form("tag%d_%s", tagrIdx, jetFlvr[NUM_FLVR]), 
					 Form("tag%d_%s", tagrIdx, jetFlvr[NUM_FLVR]), 100, -1., 1.);
   
   h_mc[NUM_FLVR][tagrIdx]
     ->Add( (TH1F*)bdt->Get( Form("data_0_0_%d_px2_chIso", ptbin) ) ) ;
   h_mc[NUM_FLVR][tagrIdx]
     ->Add( (TH1F*)bdt->Get( Form("data_0_1_%d_px2_chIso", ptbin) ) ) ;
 }


TFile *f = new TFile("./templates.root","recreate");

 for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
   for(int flvrIdx = 0; flvrIdx < NUM_FLVR+1; flvrIdx++) {
     h_mc[flvrIdx][tagrIdx]->Scale(1./h_mc[flvrIdx][tagrIdx]->Integral());
     h_mc[flvrIdx][tagrIdx]->Write();
   }
   h_data[tagrIdx]->Write();
 }

   f->Close();


}

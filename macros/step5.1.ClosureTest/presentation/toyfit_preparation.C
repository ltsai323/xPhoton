#include <TH1.h>
#include <TH2.h>
#include <cmath>
#define NUM_PART 3
#define NUM_FLVR 3 
#define NUM_TAGR 4
#define NUM_PRTY 2
#define NUM_PTBN 20
#define PHOETA 0
#define JETETA 0

auto modi( TH1F* input ){
        TH1F *temp = (TH1F*) input->Clone();
        for(int i=1; i<=temp->GetNbinsX(); i++) {
                if( temp->GetBinContent(i)<0 ) temp->SetBinContent(i, 0.00001); }
        return temp;
}

void toyfit_preparation(int PHOPT = 0){

  TFile *dat = new TFile("../../makehisto_data.root");
  TFile *mc  = new TFile("../../makehisto_sig.root");
  TFile *qcd = new TFile("../../makehisto_QCD.root");

  cout << "PhoEtaBin : " << PHOETA << endl;
  cout << "JetEtaBin : " << JETETA << endl;
  cout << "PhoPtBin  : " << PHOPT  << endl;

  const int tagrIdx_svxmass=3;
  const std::vector< int > matchIdx = { 0, 2, 3 };
  const std::vector< const char* > jetFlvr = { "L", "C", "B", "FAKE" };
  const std::vector< const char* > tagName = { "BvsAll", "CvsL", "CvsB", "Svxmass" };

  TH2F *data_2D  [NUM_PART][NUM_FLVR][NUM_TAGR][NUM_PRTY];
  TH1F *data_1D  [NUM_PART][NUM_FLVR][NUM_TAGR][NUM_PRTY];
  TH1F *data     [NUM_PART][NUM_FLVR][NUM_TAGR];
  TH1F *data_N   [NUM_PART][NUM_TAGR];

  TH1F *toymc    [NUM_FLVR+1][NUM_TAGR];
  TH1F *toydata  [NUM_TAGR];

  float nL    = 50000.;
  float nC    = 40000.;
  float nB    = 10000.;
  float nFake = 50000.;
  float nAll  = nL + nC + nB;

  for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
    float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
    for(int partIdx = 0; partIdx < NUM_PART; partIdx++) {
      for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
	for(int prtyIdx = 0; prtyIdx < NUM_PRTY; prtyIdx++) {
	  if(partIdx == 0){
	    data_2D[partIdx][flvrIdx][tagrIdx][prtyIdx] = 
	      (TH2F*) mc -> Get( Form("btagDeepCSV/btagDeepCSV.0_%d_%d__%d_%d_%d__%d_%d", tagrIdx, flvrIdx, JETETA, PHOETA, PHOPT, matchIdx[partIdx], prtyIdx) );
	    data_1D[partIdx][flvrIdx][tagrIdx][prtyIdx] = (TH1F*)data_2D[partIdx][flvrIdx][tagrIdx][prtyIdx] -> ProjectionX();
	  }else{
	    data_2D[partIdx][flvrIdx][tagrIdx][prtyIdx] = 
	      (TH2F*)qcd -> Get( Form("btagDeepCSV/btagDeepCSV.0_%d_%d__%d_%d_%d__%d_%d", tagrIdx, flvrIdx, JETETA, PHOETA, PHOPT, matchIdx[partIdx], prtyIdx) );
	    data_1D[partIdx][flvrIdx][tagrIdx][prtyIdx] = (TH1F*)data_2D[partIdx][flvrIdx][tagrIdx][prtyIdx] -> ProjectionX();
	  }
	}
	data[partIdx][flvrIdx][tagrIdx] = new TH1F("temp", "temp", 10, 0., upperboundary);
	*data[partIdx][flvrIdx][tagrIdx] = *data_1D[partIdx][flvrIdx][tagrIdx][0] + *data_1D[partIdx][flvrIdx][tagrIdx][1];
	data[partIdx][flvrIdx][tagrIdx]->Scale(1./data[partIdx][flvrIdx][tagrIdx]->Integral());
      }
      data_N[partIdx][tagrIdx] = new TH1F("temp", "temp", 10, 0., upperboundary);
      *data_N[partIdx][tagrIdx] = nL*(*data[partIdx][0][tagrIdx]) + nC*(*data[partIdx][1][tagrIdx]) + nB*(*data[partIdx][2][tagrIdx]);
    }
  }

  //toymc
  for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
    float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
    for(int flvrIdx = 0; flvrIdx < NUM_FLVR+1; flvrIdx++) {
      toymc[flvrIdx][tagrIdx] = new TH1F("temp", "temp", 10, 0., upperboundary);
      if(flvrIdx != NUM_FLVR){
	*toymc[flvrIdx][tagrIdx] = *data[0][flvrIdx][tagrIdx];
      }
      else{
	*toymc[flvrIdx][tagrIdx] = *data_N[2][tagrIdx];//should be 2
	toymc[flvrIdx][tagrIdx] -> Scale(nFake/toymc[flvrIdx][tagrIdx]->Integral());
      }
      toymc[flvrIdx][tagrIdx] -> SetNameTitle(Form("toymc_%s_%s", tagName[tagrIdx], jetFlvr[flvrIdx]), Form("toymc_%s_%s", tagName[tagrIdx], jetFlvr[flvrIdx]));
    }
  }

  //toydata
    for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
      float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
      toydata[tagrIdx] = new TH1F("temp", "temp", 10, 0., upperboundary);
      *toydata[tagrIdx] = *data_N[0][tagrIdx] + nFake/nAll*(*data_N[1][tagrIdx]);
      toydata[tagrIdx] -> SetNameTitle(Form("toydata_%s", tagName[tagrIdx]), Form("toydata_%s", tagName[tagrIdx]));
    }


//Write
TFile *f_toy = new TFile("./toy.root","recreate");

for(int tagrIdx=0; tagrIdx<NUM_TAGR-1; tagrIdx++){
   toydata[tagrIdx]->Write();
   for(int flvrIdx = 0; flvrIdx < NUM_FLVR+1; flvrIdx++) {
     toymc[flvrIdx][tagrIdx]->Write();
   }
}
   f_toy->Close();
}

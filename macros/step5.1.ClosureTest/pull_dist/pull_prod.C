#include <TH1.h>
#include <TH2.h>
#include <cmath>
#include "TRandom3.h"
#define NUM_PART 3
#define NUM_FLVR 3 
#define NUM_TAGR 4
#define NUM_PTBN 20
#define PHOETA 0
#define JETETA 0
#define REALDATA
#define DATA
auto modi( TH1F* input ){
        TH1F *temp = (TH1F*) input->Clone();
        for(int i=1; i<=temp->GetNbinsX(); i++) {
                if( temp->GetBinContent(i)<0 ) temp->SetBinContent(i, 0.00001); }
        return temp;
}

void pull_prod(int ptbin = 7){

TFile *dat = new TFile("../../makehisto_data.root");
TFile *mc  = new TFile("../../makehisto_sig.root");
TFile *qcd = new TFile("../../makehisto_QCD.root");

cout << "PhoEtaBin : " << PHOETA << endl;
cout << "JetEtaBin : " << JETETA << endl;
cout << "PtBin     : " << ptbin  << endl;

const int tagrIdx_svxmass=3;
const std::vector< int > matchIdx = { 0, 2, 3 };
const std::vector< const char* > jetFlvr = { "L", "C", "B" };
const std::vector< const char* > tagName = { "BvsAll", "CvsL", "CvsB", "Svxmass" };

#ifdef REALDATA
TH2F *realdata_2D [NUM_TAGR];
TH1F *realdata_1D [NUM_TAGR];
for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
	float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.; // idx goes to svxmass, change upper boundary.
	realdata_2D[tagrIdx] = (TH2F*) dat -> Get( Form("btagDeepCSV/btagDeepCSV.0_%d_0__%d_%d_%d__1_1", tagrIdx, JETETA, PHOETA, ptbin) );
	realdata_1D[tagrIdx] = (TH1F*) realdata_2D[tagrIdx] ->ProjectionX();
	realdata_1D[tagrIdx] -> SetNameTitle( Form("realdata_N2_tag%d", tagrIdx), Form("realdata_N2_tag%d", tagrIdx) );
}

TH2F *data_sig_2D [NUM_TAGR];
TH1F *data_sig_1D [NUM_TAGR];
for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
        float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.; // idx goes to svxmass, change upper boundary.
        data_sig_2D[tagrIdx] = (TH2F*) dat -> Get( Form("btagDeepCSV/btagDeepCSV.0_%d_0__%d_%d_%d__0_1", tagrIdx, JETETA, PHOETA, ptbin) );
        data_sig_1D[tagrIdx] = (TH1F*) data_sig_2D[tagrIdx] ->ProjectionX();
        data_sig_1D[tagrIdx] -> SetNameTitle( Form("data_sig_tag%d", tagrIdx), Form("data_sig_tag%d", tagrIdx) );
	cout << data_sig_1D[tagrIdx]->Integral() << endl;
}


#endif //REALDATA

#ifdef DATA
///plot 1D-hists in N0 & N1 & N2 to check the size of the error
TH2F *data_2D  [NUM_PART][NUM_FLVR][NUM_TAGR];
TH1F *data_1D  [NUM_PART][NUM_FLVR][NUM_TAGR];
TH1F *data_N   [NUM_PART][NUM_TAGR];
TH1F *data     [NUM_TAGR];
TH1F *data_flv [NUM_FLVR][NUM_TAGR];
TH1F *data_pos [NUM_FLVR][NUM_TAGR];

for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
        float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.; // idx goes to svxmass, change upper boundary.
        data[tagrIdx] = new TH1F( Form("tag%d", tagrIdx), Form("tag%d", tagrIdx), 10, 0., upperboundary);
	for(int partIdx = 0; partIdx < NUM_PART; partIdx++) {
		for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {

        		if(partIdx == 0){
                		data_2D[partIdx][flvrIdx][tagrIdx] = 
					(TH2F*) mc -> Get( Form("btagDeepCSV/btagDeepCSV.0_%d_%d__%d_%d_%d__%d_1", tagrIdx, flvrIdx, JETETA, PHOETA, ptbin, matchIdx[partIdx]) );
                		data_1D[partIdx][flvrIdx][tagrIdx] = (TH1F*)data_2D[partIdx][flvrIdx][tagrIdx] -> ProjectionX();
       			}else{
                		data_2D[partIdx][flvrIdx][tagrIdx] = 
					(TH2F*)qcd -> Get( Form("btagDeepCSV/btagDeepCSV.0_%d_%d__%d_%d_%d__%d_1", tagrIdx, flvrIdx, JETETA, PHOETA, ptbin, matchIdx[partIdx]) );
                		data_1D[partIdx][flvrIdx][tagrIdx] = (TH1F*)data_2D[partIdx][flvrIdx][tagrIdx] -> ProjectionX();
        		}

        		data_2D[partIdx][flvrIdx][tagrIdx] ->SetNameTitle(
                		Form("N%d_%s_tag%d", partIdx, jetFlvr[flvrIdx], tagrIdx),
                		Form("N%d_%s_tag%d", partIdx, jetFlvr[flvrIdx], tagrIdx));
		}

        	data_N[partIdx][tagrIdx] = new TH1F("temp", "temp", 10, 0., upperboundary);
       		*data_N[partIdx][tagrIdx] = *data_1D[partIdx][0][tagrIdx] + *data_1D[partIdx][1][tagrIdx] + *data_1D[partIdx][2][tagrIdx];
        	data_N[partIdx][tagrIdx] ->SetNameTitle(
			Form("N%d_tag%d", partIdx, tagrIdx),
                	Form("N%d_tag%d", partIdx, tagrIdx));
	}
}

for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++){
	float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.; 
for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
   data_flv[flvrIdx][tagrIdx] = new TH1F( Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), 10, 0., upperboundary);
} }


// data = N0 + N1 - N2*(#N1/#N2)
float N1overN2[NUM_TAGR];
for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){
        N1overN2[tagrIdx] = data_N[1][tagrIdx]->Integral() / data_N[2][tagrIdx]->Integral();
        *data[tagrIdx] = *data_N[0][tagrIdx] + *data_N[1][tagrIdx] - N1overN2[tagrIdx]*(*data_N[2][tagrIdx]) ;

	for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
		*data_flv[flvrIdx][tagrIdx] = *data_1D[0][flvrIdx][tagrIdx] + *data_1D[1][flvrIdx][tagrIdx] - N1overN2[tagrIdx]*(*data_1D[2][flvrIdx][tagrIdx]) ;
		data_flv[flvrIdx][tagrIdx] -> SetNameTitle(Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]), Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]));
	}
  
      data[tagrIdx] -> SetNameTitle(Form("tag%d", tagrIdx), Form("tag%d", tagrIdx));
}

//modi to positive
for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){
        data_pos[flvrIdx][tagrIdx] = (TH1F*) data_flv[flvrIdx][tagrIdx]->Clone();
        data_pos[flvrIdx][tagrIdx] = (TH1F*) modi(data_flv[flvrIdx][tagrIdx])->Clone();
} }

//Write
TFile *f_pull = new TFile("./pull.root","recreate");

for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++){
   data_pos[flvrIdx][tagrIdx]->Scale(1./data_pos[flvrIdx][tagrIdx]->Integral());
   data_pos[flvrIdx][tagrIdx]->Write();
} }
   f_pull->Close();

#endif //DATA


TH1F *btag = new TH1F("btag","btag",10,0.,1.);
TH1F *cvsl = new TH1F("cvsl","cvsl",10,0.,1.);
TH1F *cvsb = new TH1F("cvsb","cvsb",10,0.,1.);

if(gRandom) delete gRandom;
gRandom = new TRandom3(0);

float total = 150000;
float frac_L = 0.875;
float frac_C = 0.100;
float frac_B = 0.025;
float NL = total*frac_L;
float NC = total*frac_C;
float NB = total*frac_B;

btag->FillRandom(data_pos[0][0],NL);
btag->FillRandom(data_pos[1][0],NC);
btag->FillRandom(data_pos[2][0],NB);

cvsl->FillRandom(data_pos[0][1],NL);
cvsl->FillRandom(data_pos[1][1],NC);
cvsl->FillRandom(data_pos[2][1],NB);

cvsb->FillRandom(data_pos[0][2],NL);
cvsb->FillRandom(data_pos[1][2],NC);
cvsb->FillRandom(data_pos[2][2],NB);

TFile *f = new TFile("./random_toy.root","recreate");

   btag->Write();
   cvsl->Write();
   cvsb->Write();

      f->Close();

}

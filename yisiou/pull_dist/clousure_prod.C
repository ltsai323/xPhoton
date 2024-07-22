#include <TH1.h>
#include <cmath>
#define NUM_PART 3
#define NUM_FLVR 3 
#define NUM_TAGR 4

//Usage
//root.exe "clousure_prod.C(7)"
//this will create a root file contiain four tagger in i-th PtBin as the toy_data

void clousure_prod(int ptbin = 0){

//TFile *mc  = new TFile("../step2_makehisto/storeroot0/makehisto_sig_madgraph.root");
//TFile *qcd = new TFile("../step2_makehisto/storeroot0/makehisto_QCD_madgraph.root");
TFile *mc  = new TFile("../step2_makehisto/storeroot_weightcut1/makehisto_sig_madgraph.root");
TFile *qcd = new TFile("../step2_makehisto/storeroot_weightcut1/makehisto_QCD_madgraph.root");

cout << "ptbin is " << ptbin << endl;

//we need (N0+N1) - N2*(N1/N2) = N0

//toydata
TH1F *h[NUM_PART][NUM_FLVR][NUM_TAGR];
TH1F *h_part[NUM_PART][NUM_TAGR];
TH1F *tag_data[NUM_TAGR];
//toymc
TH1F *tag_mc[NUM_FLVR][NUM_TAGR];
TH1F *tag_mc_up[NUM_FLVR][NUM_TAGR];
TH1F *tag_mc_down[NUM_FLVR][NUM_TAGR];

const int tagrIdx_svxmass=3;
const std::vector< int > matchIdx = { 0, 2, 3 };
const std::vector< const char* > jetFlvr = { "L", "C", "B" };
const std::vector< const char* > jetFlvrNames = { "sigma", "alpha", "beta" };
//loop for toydata
for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
        float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.; // idx goes to svxmass, change upper boundary.
        tag_data[tagrIdx] = new TH1F( Form("tag%d", tagrIdx), Form("tag%d", tagrIdx), 10, 0., upperboundary);
for(int partIdx = 0; partIdx < NUM_PART; partIdx++) {
for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {

        if(partIdx==0){
                h[partIdx][flvrIdx][tagrIdx] =
                        (TH1F*)mc->Get( Form("h_jettag_0_%d_%d_%d_%d_1", ptbin, matchIdx[partIdx], flvrIdx, tagrIdx) );
        }else{
                h[partIdx][flvrIdx][tagrIdx] =
                        (TH1F*)qcd->Get( Form("h_jettag_0_%d_%d_%d_%d_1", ptbin, matchIdx[partIdx], flvrIdx, tagrIdx) );
        }
        
        h[partIdx][flvrIdx][tagrIdx] ->SetNameTitle(
                Form("N%d_%s_tag%d", partIdx, jetFlvr[flvrIdx], tagrIdx),
                Form("N%d_%s_tag%d", partIdx, jetFlvr[flvrIdx], tagrIdx));

}
        h_part[partIdx][tagrIdx] = new TH1F("temp", "temp", 10, 0., upperboundary);
        *h_part[partIdx][tagrIdx] = *h[partIdx][0][tagrIdx] + *h[partIdx][1][tagrIdx] + *h[partIdx][2][tagrIdx];
        h_part[partIdx][tagrIdx] ->SetNameTitle(
                Form("N%d_tag%d", partIdx, tagrIdx),
                Form("N%d_tag%d", partIdx, tagrIdx));
} }

        cout << "L:" << h[0][0][0]->Integral() << endl;
        cout << "C:" << h[0][1][0]->Integral() << endl;
        cout << "B:" << h[0][2][0]->Integral() << endl;


//loop for toymc
for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
        float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {

        tag_mc[flvrIdx][tagrIdx] =
                (TH1F*)mc->Get( Form("h_jettag_0_%d_0_%d_%d_0", ptbin, flvrIdx, tagrIdx) );
        tag_mc[flvrIdx][tagrIdx] -> SetNameTitle(
                Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]),
                Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]));

        if(tagrIdx!=3){
                tag_mc_up[flvrIdx][tagrIdx] =
                        (TH1F*)mc->Get( Form("h_jettag_%sUp_0_%d_0_%d_%d_0", jetFlvrNames[flvrIdx], ptbin, flvrIdx, tagrIdx) );
                tag_mc_down[flvrIdx][tagrIdx] =
                        (TH1F*)mc->Get( Form("h_jettag_%sDown_0_%d_0_%d_%d_0", jetFlvrNames[flvrIdx], ptbin, flvrIdx, tagrIdx) );

                tag_mc_up[flvrIdx][tagrIdx] -> SetNameTitle(
                        Form("tag%d_%s_%sUp", tagrIdx, jetFlvr[flvrIdx], jetFlvrNames[flvrIdx]),
                        Form("tag%d_%s_%sUp", tagrIdx, jetFlvr[flvrIdx], jetFlvrNames[flvrIdx]));
                tag_mc_down[flvrIdx][tagrIdx] -> SetNameTitle(
                        Form("tag%d_%s_%sDown", tagrIdx, jetFlvr[flvrIdx], jetFlvrNames[flvrIdx]),
                        Form("tag%d_%s_%sDown", tagrIdx, jetFlvr[flvrIdx], jetFlvrNames[flvrIdx]));
        }

} }

float ratio[NUM_TAGR];

for(int tagrIdx=0; tagrIdx<=NUM_TAGR; tagrIdx++){
        ratio[tagrIdx] = h_part[1][tagrIdx]->Integral() / h_part[2][tagrIdx]->Integral();
        *tag_data[tagrIdx] = *h_part[0][tagrIdx] + *h_part[1][tagrIdx] - ratio[tagrIdx]*(*h_part[2][tagrIdx]) ;
        tag_data[tagrIdx] -> SetNameTitle(Form("tag%d", tagrIdx), Form("tag%d", tagrIdx));      
} 

//tag_data[0]->Draw("HE");

TFile *f_toydata = new TFile("./toy_data.root","recreate");

for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){
   tag_data[tagrIdx]->Write();
}
   f_toydata->Close();


TFile *f_toymc = new TFile("./toy_mc.root","recreate");

for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
        tag_mc[flvrIdx][tagrIdx]->Scale(1./tag_mc[flvrIdx][tagrIdx]->Integral());
        tag_mc[flvrIdx][tagrIdx]->Write();
        if(tagrIdx!=3){ 
                tag_mc_up[flvrIdx][tagrIdx]->Scale(1./tag_mc_up[flvrIdx][tagrIdx]->Integral());
                tag_mc_down[flvrIdx][tagrIdx]->Scale(1./tag_mc_down[flvrIdx][tagrIdx]->Integral());
                tag_mc_up[flvrIdx][tagrIdx]->Write();
                tag_mc_down[flvrIdx][tagrIdx]->Write();
        }
} }

   f_toymc->Close();


}

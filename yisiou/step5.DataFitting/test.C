#include <TH1.h>
#include <cmath>
#define NUM_FLVR 3  // light, c, b
#define NUM_TAGR 4  // b+bb, cvsl, cvsb, svxmass
#define NUM_PRTY 2  // even, odd
/*
TH2F* GetHistFromFile_IsovsBDT(TFile* infile, int isBkg,
        int ebee, int jetbin, int ptbin, int IsoOption )
{
    TH2F* hist;
    char hname[200];
    sprintf(hname,"h_IsovsBDT_%d_%d_%d_%d_%d", ebee, jetbin, ptbin, isBkg, IsoOption);
    hist = (TH2F*)infile->Get(hname);
    if ( jetbin == 0 || jetbin == 1 ) return hist;

    while ( jetbin-- )
    {
        sprintf(hname,"h_IsovsBDT_%d_%d_%d_%d_%d", ebee, jetbin, ptbin, isBkg, IsoOption);
        hist->Add( (TH2F*)infile->Get(hname) );
    }
    return hist;

}
i*/

void test(int ptbin = 0){

TFile *mc  = new TFile("../step2.makehistos/storeroot_mcweightcut_on_lightcut_1/makehisto_sig_madgraph.root");
TFile *data = new TFile("../step2.makehistos/storeroot_mcweightcut_on_lightcut_1/makehisto_data.root");

cout << "ptbin is " << ptbin << endl;

//MC
TH1F *h_mc[NUM_FLVR][NUM_TAGR];

//DATA
TH1F *h_data[NUM_TAGR];

const int tagrIdx_svxmass=3;
const std::vector< int > matchIdx = { 0, 2, 3 };
const std::vector< const char* > jetFlvr = { "L", "C", "B" };
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
//TH1F *d = new TH1F("d","d",10,0.,1.);
//d = (TH1F*)data->Get("h_jettag_0_0_0_0_0_0");
//d->Draw("h");

//h_mc[0][0]->Draw("h");
h_data[3]->Draw("h");
}

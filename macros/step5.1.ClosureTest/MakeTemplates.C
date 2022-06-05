#include <TH1.h>
#include <TH2.h>
#include <cmath>
#define NUM_PART 3
#define NUM_FLVR 3 
#define NUM_TAGR 4
#define NUM_PTBN 20
#define PHOETA 0
#define JETETA 0

auto modi( TH1F* input ){
        TH1F *temp = (TH1F*) input->Clone();
        for(int i=1; i<=temp->GetNbinsX(); i++) {
                if( temp->GetBinContent(i)<0 ) temp->SetBinContent(i, 0.00001); }
        return temp;
}

void MakeTemplates(int ptbin = 0){

TFile *dat = new TFile("../makehisto_data.root");
TFile *mc  = new TFile("../makehisto_sig.root");
TFile *qcd = new TFile("../makehisto_QCD.root");

cout << "PhoEtaBin : " << PHOETA << endl;
cout << "JetEtaBin : " << JETETA << endl;
cout << "PtBin     : " << ptbin  << endl;

const int tagrIdx_svxmass=3;
const std::vector< int > matchIdx = { 0, 2, 3 };
const std::vector< const char* > jetFlvr = { "L", "C", "B" };
const std::vector< const char* > tagName = { "BvsAll", "CvsL", "CvsB", "Svxmass" };

///plot 1D-hists in N0 & N1 & N2 to check the size of the error
TH2F *data_2D  [NUM_PART][NUM_FLVR][NUM_TAGR];
TH1F *data_1D  [NUM_PART][NUM_FLVR][NUM_TAGR];
TH1F *data_N   [NUM_PART][NUM_TAGR];
TH1F *data     [NUM_TAGR];
TH1F *data_pos [NUM_TAGR];

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

// data = N0 + N1 - N2*(#N1/#N2)
float N1overN2[NUM_TAGR];
for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){
        N1overN2[tagrIdx] = data_N[1][tagrIdx]->Integral() / data_N[2][tagrIdx]->Integral();
        *data[tagrIdx] = *data_N[0][tagrIdx] + *data_N[1][tagrIdx] - N1overN2[tagrIdx]*(*data_N[2][tagrIdx]) ;
        data[tagrIdx] -> SetNameTitle(Form("tag%d", tagrIdx), Form("tag%d", tagrIdx));
}

//modi to positive
for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){
        data_pos[tagrIdx] = (TH1F*) data[tagrIdx]->Clone();
        data_pos[tagrIdx] = (TH1F*) modi(data[tagrIdx])->Clone();
}

	cout << "================== N0-part ===================" << endl;
	cout << "    " << "\t" << "L" << "\t" << "C" << "\t" << "B" << "\t" << "total" << endl;
	cout << "btag" << "\t" << data_1D[0][0][0]->Integral() << "\t" << data_1D[0][1][0]->Integral() << "\t" << data_1D[0][2][0]->Integral()  << "\t" << data_N[0][0]->Integral() << endl;
	cout << "cvsl" << "\t" << data_1D[0][0][1]->Integral() << "\t" << data_1D[0][1][1]->Integral() << "\t" << data_1D[0][2][1]->Integral()  << "\t" << data_N[0][1]->Integral() << endl;
	cout << "cvsb" << "\t" << data_1D[0][0][2]->Integral() << "\t" << data_1D[0][1][2]->Integral() << "\t" << data_1D[0][2][2]->Integral()  << "\t" << data_N[0][2]->Integral() << endl;
	cout << "mass" << "\t" << data_1D[0][0][3]->Integral() << "\t" << data_1D[0][1][3]->Integral() << "\t" << data_1D[0][2][3]->Integral()  << "\t" << data_N[0][3]->Integral() << endl;
	cout << endl;
	cout << "================== N1-part ===================" << endl;
        cout << "    " << "\t" << "L" << "\t" << "C" << "\t" << "B" << "\t" << "total" << endl;
        cout << "btag" << "\t" << data_1D[1][0][0]->Integral() << "\t" << data_1D[1][1][0]->Integral() << "\t" << data_1D[1][2][0]->Integral()  << "\t" << data_N[1][0]->Integral() << endl;
        cout << "cvsl" << "\t" << data_1D[1][0][1]->Integral() << "\t" << data_1D[1][1][1]->Integral() << "\t" << data_1D[1][2][1]->Integral()  << "\t" << data_N[1][1]->Integral() << endl;
        cout << "cvsb" << "\t" << data_1D[1][0][2]->Integral() << "\t" << data_1D[1][1][2]->Integral() << "\t" << data_1D[1][2][2]->Integral()  << "\t" << data_N[1][2]->Integral() << endl;
        cout << "mass" << "\t" << data_1D[1][0][3]->Integral() << "\t" << data_1D[1][1][3]->Integral() << "\t" << data_1D[1][2][3]->Integral()  << "\t" << data_N[1][3]->Integral() << endl;
        cout << endl;
	cout << "================== N2-part ===================" << endl;
        cout << "    " << "\t" << "L" << "\t" << "C" << "\t" << "B" << "\t" << "total" << endl;
        cout << "btag" << "\t" << data_1D[2][0][0]->Integral() << "\t" << data_1D[2][1][0]->Integral() << "\t" << data_1D[2][2][0]->Integral()  << "\t" << data_N[2][0]->Integral() << endl;
        cout << "cvsl" << "\t" << data_1D[2][0][1]->Integral() << "\t" << data_1D[2][1][1]->Integral() << "\t" << data_1D[2][2][1]->Integral()  << "\t" << data_N[2][1]->Integral() << endl;
        cout << "cvsb" << "\t" << data_1D[2][0][2]->Integral() << "\t" << data_1D[2][1][2]->Integral() << "\t" << data_1D[2][2][2]->Integral()  << "\t" << data_N[2][2]->Integral() << endl;
        cout << "mass" << "\t" << data_1D[2][0][3]->Integral() << "\t" << data_1D[2][1][3]->Integral() << "\t" << data_1D[2][2][3]->Integral()  << "\t" << data_N[2][3]->Integral() << endl;
        cout << endl;

	cout << "================== data (N0 + N1 - N2*(#N1/#N2)) ===================" << endl;	
	cout << "btag" << "\t" << data[0]->Integral() << endl;
	cout << "cvsl" << "\t" << data[1]->Integral() << endl;
	cout << "cvsb" << "\t" << data[2]->Integral() << endl;
	cout << "mass" << "\t" << data[3]->Integral() << endl;

//Write
TFile *f_toydata = new TFile("./toy_data.root","recreate");

for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){
   data[tagrIdx]->Write();
   //data_pos[tagrIdx]->Write();
}
   f_toydata->Close();

TH2F *mc_2D  [NUM_FLVR][NUM_TAGR];
TH1F *mc_1D  [NUM_FLVR][NUM_TAGR];
TH1F *mc_pos [NUM_FLVR][NUM_TAGR];

for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
        float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
	for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
        	mc_2D[flvrIdx][tagrIdx] =
                	(TH2F*)mc->Get( Form("btagDeepCSV/btagDeepCSV.0_%d_%d__%d_%d_%d__0_0", tagrIdx, flvrIdx, JETETA, PHOETA, ptbin) );
		mc_1D[flvrIdx][tagrIdx] =
        	        (TH1F*)mc_2D[flvrIdx][tagrIdx]->ProjectionX();
	        mc_1D[flvrIdx][tagrIdx] -> SetNameTitle(
        	        Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]),
	                Form("tag%d_%s", tagrIdx, jetFlvr[flvrIdx]));
	}
}

for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){
	for(int flvrIdx=0; flvrIdx<NUM_FLVR; flvrIdx++){
		mc_pos[flvrIdx][tagrIdx] = (TH1F*) mc_1D[flvrIdx][tagrIdx]->Clone();
		mc_pos[flvrIdx][tagrIdx] = (TH1F*) modi(mc_1D[flvrIdx][tagrIdx])->Clone();
	}
}

TFile *f_toymc = new TFile("./toy_mc.root","recreate");
for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
	for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {

		mc_1D[flvrIdx][tagrIdx]->Scale(1./mc_1D[flvrIdx][tagrIdx]->Integral());
		mc_1D[flvrIdx][tagrIdx]->Write();
        	//mc_pos[flvrIdx][tagrIdx]->Scale(1./mc_pos[flvrIdx][tagrIdx]->Integral());
        	//mc_pos[flvrIdx][tagrIdx]->Write();
	}
}
   f_toymc->Close();

        cout << "================== toymc ===================" << endl;
        cout << "    " << "\t" << "BvsAll" << "\t" << "CvsL" << "\t" << "CvsB" << "\t" << "Svxmass" << endl;
        cout << "L" << "\t" << mc_1D[0][0]->Integral() << "\t" << mc_1D[0][1]->Integral() << "\t" << mc_1D[0][2]->Integral()  << "\t" << mc_1D[0][3]->Integral() << endl;
        cout << "C" << "\t" << mc_1D[1][0]->Integral() << "\t" << mc_1D[1][1]->Integral() << "\t" << mc_1D[1][2]->Integral()  << "\t" << mc_1D[1][3]->Integral() << endl;
        cout << "B" << "\t" << mc_1D[2][0]->Integral() << "\t" << mc_1D[2][1]->Integral() << "\t" << mc_1D[2][2]->Integral()  << "\t" << mc_1D[2][3]->Integral() << endl;
        cout << endl;
}

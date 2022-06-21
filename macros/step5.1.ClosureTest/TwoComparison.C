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

void TwoComparison(int ptbin = 0){

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

	/////4plots
	//plot1:
	//N1N2_L_btag   N1N2_C_btag   N1N2_B_btag
	//plot2
	//N1N2_L_CvsL   N1N2_C_CvsL   N1N2_B_CvsL
	//plot3
	//N1N2_L_CvsB   N1N2_C_CvsB   N1N2_B_CvsB

	//data_1D[1][0][0]	data_1D[1][1][0]	data_1D[1][2][0]

  float chi2;
  float upperbdd =  2.8;
  float lowerbdd = -0.8;
  float binmidpoint, bincontent, binerror;

TCanvas *canvas_N1N2 = new TCanvas("N1N2","N1N2", 900, 1000);
canvas_N1N2->Divide(3,3);
for(int flvrIdx=0; flvrIdx<NUM_FLVR; flvrIdx++){
for(int tagrIdx=0; tagrIdx<NUM_TAGR-1; tagrIdx++){
	canvas_N1N2->cd(flvrIdx+NUM_FLVR*tagrIdx+1);
        TPad* pad1 = new TPad("","",0.02, 0.30, 0.99, 0.99);
        TPad* pad2 = new TPad("","",0.02, 0.02, 0.99, 0.30);
	chi2 = data_1D[1][flvrIdx][tagrIdx]->Chi2Test( data_1D[2][flvrIdx][tagrIdx], "P CHI2");
	data_1D[1][flvrIdx][tagrIdx]->Scale(1./data_1D[1][flvrIdx][tagrIdx]->Integral());
      	data_1D[2][flvrIdx][tagrIdx]->Scale(1./data_1D[2][flvrIdx][tagrIdx]->Integral());
	data_1D[1][flvrIdx][tagrIdx]->SetMaximum(std::max(data_1D[1][flvrIdx][tagrIdx]->GetMaximum(),data_1D[2][flvrIdx][tagrIdx]->GetMaximum())*1.1);
	data_1D[1][flvrIdx][tagrIdx]->SetStats(0);

	pad1->SetRightMargin(0.035);
	pad1->SetBottomMargin(0.04);
        pad1->SetFrameBorderMode(0);
        pad1->SetBorderMode(0);
        pad1->SetBorderSize(0);
        pad2->SetRightMargin(0.035);
        pad2->SetTopMargin(0.04);
        pad2->SetBottomMargin(0.22);
        pad2->SetFrameBorderMode(0);
        pad2->SetBorderMode(0);
        pad2->SetBorderSize(0);

        pad1->Draw();
        pad2->Draw();
  
	//pad1
        pad1->cd();
        gPad->SetTickx();
        gPad->SetTicky();
	data_1D[1][flvrIdx][tagrIdx]->SetTitle(Form("%s_%s", jetFlvr[flvrIdx], tagName[tagrIdx]));
        data_1D[1][flvrIdx][tagrIdx]->SetLineColor(kBlue);
        data_1D[2][flvrIdx][tagrIdx]->SetLineColor(kRed);
        data_1D[1][flvrIdx][tagrIdx]->Draw("he");
        data_1D[2][flvrIdx][tagrIdx]->Draw("he same");

	//pad2
	gPad->RedrawAxis();
        pad2->cd();
        gPad->SetGridy();
        TH1F *hratio = (TH1F*)data_1D[1][flvrIdx][tagrIdx]->Clone();
        hratio->Sumw2();
        hratio->Divide(data_1D[2][flvrIdx][tagrIdx]);
        hratio->SetYTitle("N1 / N2");
	hratio->GetXaxis()->SetLabelSize(0.07);
        hratio->GetXaxis()->SetTitleSize(0.1);
        hratio->GetXaxis()->SetLabelOffset(0.);

        hratio->GetYaxis()->SetLabelSize(0.07);
        hratio->GetYaxis()->SetTitleSize(0.07);
        hratio->GetYaxis()->SetTitleOffset(0.60);
        hratio->SetNdivisions(505,"X");
        hratio->SetNdivisions(205,"Y");
        hratio->SetLineColor(4);
        hratio->SetLineWidth(2);

        hratio->GetYaxis()->SetRangeUser(lowerbdd, upperbdd);
        data_1D[1][flvrIdx][tagrIdx]->SetNdivisions(102,"Y");
        hratio->SetTitle("");
        hratio->Draw("pe");
/*
     for(int bin=0; bin<10; bin++){
        binmidpoint = 0.25+bin*0.5;
        bincontent = hratio->GetBinContent(bin+1);
        binerror = hratio->GetBinError(bin+1);
        TLine *errorpatch = new TLine(binmidpoint,std::max(bincontent-binerror,lowerbdd),binmidpoint,std::min(bincontent+binerror,upperbdd));
        errorpatch->SetLineColor(4);
        errorpatch->SetLineWidth(2);
        errorpatch->Draw();
      }
*/    
      TLatex *tlx = new TLatex();
      tlx->SetTextSize(0.07);
      tlx->DrawLatex(0.065, 2.2, Form("#chi^{2}/NDF = %.2f", chi2/10.));
      gPad->RedrawAxis();
} }
canvas_N1N2->SaveAs(Form("./plots_twocomp/pt%d.pdf",ptbin));
}

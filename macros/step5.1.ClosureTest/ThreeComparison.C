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

void ThreeComparison(int ptbin = 0){

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

TH2F *realdata_2D [NUM_TAGR];
TH1F *realdata_1D [NUM_TAGR];
for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
	float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.; // idx goes to svxmass, change upper boundary.
	realdata_2D[tagrIdx] = (TH2F*) dat -> Get( Form("btagDeepCSV/btagDeepCSV.0_%d_0__%d_%d_%d__1_1", tagrIdx, JETETA, PHOETA, ptbin) );
	realdata_1D[tagrIdx] = (TH1F*) realdata_2D[tagrIdx] ->ProjectionX();
	realdata_1D[tagrIdx] -> SetNameTitle( Form("realdata_N2_tag%d", tagrIdx), Form("realdata_N2_tag%d", tagrIdx) );
}

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

  float chi2_1, chi2_2, chi2_3;
  float upperbdd2 =  2.8;
  float lowerbdd2 = -0.8;
TCanvas *canvas_threecomp = new TCanvas("threecomp","threecomp", 2700, 1000);
canvas_threecomp->Divide(4,1);
for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){
	canvas_threecomp->cd(tagrIdx+1);
	TPad* pad1 = new TPad("","",0.02, 0.41, 0.99, 0.99);
        TPad* pad2 = new TPad("","",0.02, 0.28, 0.99, 0.41);
	TPad* pad3 = new TPad("","",0.02, 0.15, 0.99, 0.28);
        TPad* pad4 = new TPad("","",0.02, 0.02, 0.99, 0.15);
        chi2_1 = data_N[1][tagrIdx]->Chi2Test( data_N[2][tagrIdx], "P CHI2");
	chi2_2 = realdata_1D[tagrIdx]->Chi2Test( data_N[1][tagrIdx], "P CHI2");
	chi2_3 = realdata_1D[tagrIdx]->Chi2Test( data_N[2][tagrIdx], "P CHI2");
        data_N[1][tagrIdx]->Scale(1./data_N[1][tagrIdx]->Integral());
        data_N[2][tagrIdx]->Scale(1./data_N[2][tagrIdx]->Integral());
	realdata_1D[tagrIdx]->Scale(1./realdata_1D[tagrIdx]->Integral());
	auto array = {data_N[1][tagrIdx]->GetMaximum(), data_N[2][tagrIdx]->GetMaximum(), realdata_1D[tagrIdx]->GetMaximum()};
        //data_N[1][tagrIdx]->SetMaximum(std::max(data_N[1][tagrIdx]->GetMaximum(),data_N[2][tagrIdx]->GetMaximum())*1.1);
        data_N[1][tagrIdx]->SetMaximum(std::max(array)*1.1);
	data_N[1][tagrIdx]->SetMinimum(0);
        data_N[1][tagrIdx]->SetStats(0);

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
        pad3->SetRightMargin(0.035);
        pad3->SetTopMargin(0.04);
        pad3->SetBottomMargin(0.22);
        pad3->SetFrameBorderMode(0);
        pad3->SetBorderMode(0);
        pad3->SetBorderSize(0);
        pad4->SetRightMargin(0.035);
        pad4->SetTopMargin(0.04);
        pad4->SetBottomMargin(0.22);
        pad4->SetFrameBorderMode(0);
        pad4->SetBorderMode(0);
        pad4->SetBorderSize(0);


        pad1->Draw();
        pad2->Draw();
	pad3->Draw();
	pad4->Draw();
	//pad1
        pad1->cd();
        gPad->SetTickx();
        gPad->SetTicky();
        data_N[1][tagrIdx]->SetTitle(Form("%s", tagName[tagrIdx]));
        data_N[1][tagrIdx]->SetLineColor(kBlue);
        data_N[2][tagrIdx]->SetLineColor(kRed);
	realdata_1D[tagrIdx]->SetLineColor(kGreen);
        data_N[1][tagrIdx]->Draw("he");
        data_N[2][tagrIdx]->Draw("he same");
	realdata_1D[tagrIdx]->Draw("he same");

	if(tagrIdx == 0){	
        	TLegend *tleg = new TLegend(0.27, 0.55, 0.92, 0.85);
	        tleg->AddEntry(data_N[1][tagrIdx], "QCD, chIsoRaw 2~5", "l");
		tleg->AddEntry(data_N[2][tagrIdx], "QCD, chIsoRaw 5~10", "l");
		tleg->AddEntry(realdata_1D[tagrIdx], "2016data, chIsoRaw 5~10", "l");
		tleg->SetTextSize(0.045);
	        tleg->Draw();
	}


	//pad2
        gPad->RedrawAxis();
        pad2->cd();
        gPad->SetGridy();
        TH1F *hratio1 = (TH1F*)data_N[1][tagrIdx]->Clone();
        hratio1->Sumw2();
        hratio1->Divide(data_N[2][tagrIdx]);
        hratio1->SetYTitle("QCDN1 / QCDN2");
        hratio1->GetXaxis()->SetLabelSize(0.07);
        hratio1->GetXaxis()->SetTitleSize(0.1);
        hratio1->GetXaxis()->SetLabelOffset(0.);

        hratio1->GetYaxis()->SetLabelSize(0.07);
        hratio1->GetYaxis()->SetTitleSize(0.095);
        hratio1->GetYaxis()->SetTitleOffset(0.35);
        hratio1->SetNdivisions(505,"X");
        hratio1->SetNdivisions(205,"Y");
        hratio1->SetLineColor(4);
        hratio1->SetLineWidth(2);

        hratio1->GetYaxis()->SetRangeUser(lowerbdd2, upperbdd2);
        data_N[1][tagrIdx]->SetNdivisions(102,"Y");
        hratio1->SetTitle("");
        hratio1->Draw("pe");
	
     	TLatex *tlx1 = new TLatex();
      	tlx1->SetTextSize(0.14);
      	tlx1->DrawLatex(0.065, 2.2, Form("#chi^{2}/NDF = %.2f", chi2_1/10.));
     	gPad->RedrawAxis();

	//pad3
	gPad->RedrawAxis();
        pad3->cd();
        gPad->SetGridy();
        TH1F *hratio2 = (TH1F*)realdata_1D[tagrIdx]->Clone();
        hratio2->Sumw2();
        hratio2->Divide(data_N[1][tagrIdx]);
        hratio2->SetYTitle("DATAN2 / QCDN1");
        hratio2->GetXaxis()->SetLabelSize(0.07);
        hratio2->GetXaxis()->SetTitleSize(0.1);
        hratio2->GetXaxis()->SetLabelOffset(0.);

        hratio2->GetYaxis()->SetLabelSize(0.07);
        hratio2->GetYaxis()->SetTitleSize(0.095);
        hratio2->GetYaxis()->SetTitleOffset(0.35);
        hratio2->SetNdivisions(505,"X");
        hratio2->SetNdivisions(205,"Y");
        hratio2->SetLineColor(4);
        hratio2->SetLineWidth(2);

        hratio2->GetYaxis()->SetRangeUser(lowerbdd2, upperbdd2);
        realdata_1D[tagrIdx]->SetNdivisions(102,"Y");
        hratio2->SetTitle("");
        hratio2->Draw("pe");

        TLatex *tlx2 = new TLatex();
        tlx2->SetTextSize(0.14);
        tlx2->DrawLatex(0.065, 2.2, Form("#chi^{2}/NDF = %.2f", chi2_2/10.));
        gPad->RedrawAxis();

	//pad4
	gPad->RedrawAxis();
        pad4->cd();
        gPad->SetGridy();
        TH1F *hratio3 = (TH1F*)realdata_1D[tagrIdx]->Clone();
        hratio3->Sumw2();
        hratio3->Divide(data_N[2][tagrIdx]);
        hratio3->SetYTitle("DATAN2 / QCDN2");
	
        hratio3->GetXaxis()->SetLabelSize(0.07);
        hratio3->GetXaxis()->SetTitleSize(0.1);
        hratio3->GetXaxis()->SetLabelOffset(0.);

        hratio3->GetYaxis()->SetLabelSize(0.07);
        hratio3->GetYaxis()->SetTitleSize(0.095);
        hratio3->GetYaxis()->SetTitleOffset(0.35);
        hratio3->SetNdivisions(505,"X");
        hratio3->SetNdivisions(205,"Y");
        hratio3->SetLineColor(4);
        hratio3->SetLineWidth(2);

        hratio3->GetYaxis()->SetRangeUser(lowerbdd2, upperbdd2);
        realdata_1D[tagrIdx]->SetNdivisions(102,"Y");
        hratio3->SetTitle("");
        hratio3->Draw("pe");

        TLatex *tlx3 = new TLatex();
        tlx3->SetTextSize(0.14);
        tlx3->DrawLatex(0.065, 2.2, Form("#chi^{2}/NDF = %.2f", chi2_3/10.));
        gPad->RedrawAxis();
	
	canvas_threecomp->SaveAs(Form("./plots_threecomp/pt%d.pdf",ptbin));
}
}

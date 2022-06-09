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

void DrawTaggers(int ptbin = 0){

  TFile *mc  = new TFile("../../makehisto_sig.root");

  cout << "PhoEtaBin : " << PHOETA << endl;
  cout << "JetEtaBin : " << JETETA << endl;
  cout << "PtBin     : " << ptbin  << endl;

  const int tagrIdx_svxmass=3;
  const std::vector< const char* > jetFlvr = { "L", "C", "B" };
  const std::vector< const char* > tagName = { "BvsAll", "CvsL", "CvsB", "Svxmass" };
  std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000};
  
  TH2F *tagger2D [NUM_FLVR][NUM_TAGR][NUM_PRTY];
  TH1F *tagger1D [NUM_FLVR][NUM_TAGR][NUM_PRTY];
  TH1F *tagger   [NUM_FLVR][NUM_TAGR];
  for(int tagrIdx = 0; tagrIdx < NUM_TAGR; tagrIdx++) {
    float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
    for(int flvrIdx = 0; flvrIdx < NUM_FLVR; flvrIdx++) {
      tagger[flvrIdx][tagrIdx] = new TH1F ("temp", "temp", 10, 0., upperboundary);
      for(int prtyIdx = 0; prtyIdx < NUM_PRTY; prtyIdx++) {
	tagger2D[flvrIdx][tagrIdx][prtyIdx] = (TH2F*) mc -> Get( Form("btagDeepCSV/btagDeepCSV.0_%d_%d__%d_%d_%d__0_%d", tagrIdx, flvrIdx, JETETA, PHOETA, ptbin, prtyIdx) );
	tagger1D[flvrIdx][tagrIdx][prtyIdx] = (TH1F*) tagger2D[flvrIdx][tagrIdx][prtyIdx] -> ProjectionX();
      }
      *tagger[flvrIdx][tagrIdx] = *tagger1D[flvrIdx][tagrIdx][0] + *tagger1D[flvrIdx][tagrIdx][1];
      tagger[flvrIdx][tagrIdx] -> SetNameTitle( Form("%s_%s", tagName[tagrIdx], jetFlvr[flvrIdx]), Form("%s_%s", tagName[tagrIdx], jetFlvr[flvrIdx]) );
    }
  }

  TCanvas *c1 = new TCanvas("c1","c1", 1850, 600);
  c1 -> Divide(3,1);

    for(int tagrIdx=0; tagrIdx<NUM_TAGR-1; tagrIdx++){
      c1->cd(tagrIdx+1);
      gStyle->SetOptStat(0);
      tagger[0][tagrIdx] -> SetTitle( Form("%s;tag(%s);Entries", tagName[tagrIdx], tagName[tagrIdx]) );
      tagger[0][tagrIdx] -> GetYaxis() -> SetTitleOffset(1.4);
      tagger[0][tagrIdx] -> SetLineColor(kBlue);
      tagger[1][tagrIdx] -> SetLineColor(kGreen+1);
      tagger[2][tagrIdx] -> SetLineColor(kRed);
      for(int flvrIdx=0; flvrIdx<NUM_FLVR; flvrIdx++){
	cout << Form("%s_%s", tagName[tagrIdx], jetFlvr[flvrIdx]) << tagger[flvrIdx][tagrIdx]->Integral() << endl;
	tagger[flvrIdx][tagrIdx] -> SetLineWidth(3);
	tagger[flvrIdx][tagrIdx] -> Draw("same");
      }
      
      if(tagrIdx == 0){
	TLegend *tleg0 = new TLegend(0.6, 0.6, 0.9, 0.88);
	char text[50];
	tleg0->SetFillStyle(0);
	tleg0->SetTextSize(0.04);
	tleg0->SetShadowColor(0);
	tleg0->SetBorderSize(0);
	tleg0->AddEntry(tagger[0][0],"light jet","l");
	tleg0->AddEntry(tagger[1][0],"c jet","l");
	tleg0->AddEntry(tagger[2][0],"b jet","l");
	tleg0->Draw();
      }
      if(tagrIdx == 1){
	TLegend *tleg1 = new TLegend(0.25, 0.6, 0.8, 0.88);
	char text[50];
	tleg1->SetFillStyle(0);
	tleg1->SetTextSize(0.04);
	tleg1->SetShadowColor(0);
	tleg1->SetBorderSize(0);
	sprintf(text,"%.0f < PHOPT < %.0f", vec_ptcut.at(ptbin), vec_ptcut.at(ptbin+1));
	tleg1->AddEntry((TObject*)0, "-1.5 < JETETA < 1.5", "");
	tleg1->AddEntry((TObject*)0, "-1.4442 < PHOETA < 1.4442", "");
	tleg1->AddEntry((TObject*)0, text, "");
	tleg1->Draw();
      }
      
    }
  
  c1 -> SaveAs(Form("./plots/taggers_pt%d.png", ptbin));
  if (c1) { c1->Close(); gSystem->ProcessEvents(); }
  
}

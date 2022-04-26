#include <TH1.h>
#include <cmath>
#define NUM_PART 3
#define NUM_FLVR 3 
#define NUM_TAGR 4

void plot_n1n2n3(int ptbin = 0){

//  TFile *mc  = new TFile("../step2.makehistos/storeroot1/makehisto_sig_madgraph.root");
//  TFile *qcd = new TFile("../step2.makehistos/storeroot1/makehisto_QCD_madgraph.root");
  TFile *mc  = new TFile("../step2.makehistos/storeroot_weightcut1/makehisto_sig_madgraph.root");
  TFile *qcd = new TFile("../step2.makehistos/storeroot_weightcut1/makehisto_QCD_madgraph.root");

  cout << "ptbin is " << ptbin << endl;

  //toydata
  TH1F *h[NUM_PART][NUM_FLVR][NUM_TAGR];
  TH1F *h_part[NUM_PART][NUM_TAGR];
  TH1F *tag_data[NUM_TAGR];
  char fname[100];
  const int tagrIdx_svxmass=3;
  const std::vector< int > matchIdx = { 0, 2, 3 };
  const std::vector< const char* > jetFlvr = { "L", "C", "B" };


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
        
        h[partIdx][flvrIdx][tagrIdx] ->SetNameTitle(Form("N%d_%s_tag%d", partIdx, jetFlvr[flvrIdx], tagrIdx),
                                                    Form("N%d_%s_tag%d", partIdx, jetFlvr[flvrIdx], tagrIdx));

      }

      h_part[partIdx][tagrIdx] = new TH1F("temp" ,"temp" ,10 ,0. ,upperboundary);
      *h_part[partIdx][tagrIdx] = *h[partIdx][0][tagrIdx] + *h[partIdx][1][tagrIdx] + *h[partIdx][2][tagrIdx];
      h_part[partIdx][tagrIdx] -> SetNameTitle(Form("N%d_tag%d", partIdx, tagrIdx),
                                               Form("N%d_tag%d", partIdx, tagrIdx));

    }
  }

  float ratio[NUM_TAGR];

  for(int tagrIdx=0; tagrIdx<=NUM_TAGR; tagrIdx++){
    ratio[tagrIdx] = h_part[1][tagrIdx]->Integral() / h_part[2][tagrIdx]->Integral();
    *tag_data[tagrIdx] = *h_part[0][tagrIdx] + *h_part[1][tagrIdx] - ratio[tagrIdx]*(*h_part[2][tagrIdx]) ;
    tag_data[tagrIdx] -> SetNameTitle(Form("tag%d", tagrIdx), Form("tag%d", tagrIdx));  
  } 

  TCanvas *c2 = new TCanvas("c2","c2",1200, 300);
  c2->Divide(4,1);
  gStyle->SetTitleFontSize(0.06);
  c2->cd(1);
  tag_data[0]->Draw("he");
  c2->cd(2);
  tag_data[1]->Draw("he");
  c2->cd(3);
  tag_data[2]->Draw("he");
  c2->cd(4);
  tag_data[3]->Draw("he");
for(int j=0;j<4;j++){
  cout << h[0][0][j]->Integral() << endl;
  cout << tag_data[j]->Integral() << endl;
  cout << endl;
  }
  

  TCanvas *c0 = new TCanvas("c0","c0",2000, 600);
  c0->Divide(4,3);
//  gStyle->SetTitleFontSize(0.1);
  c0->cd(1);
  h[0][0][0]->Draw("he");
  c0->cd(2);
  h[0][0][1]->Draw("he");
  c0->cd(3);
  h[0][0][2]->Draw("he");
  c0->cd(4);
  h[0][0][3]->Draw("he");

  c0->cd(5);
  h[1][0][0]->Draw("he");
  c0->cd(6);
  h[1][0][1]->Draw("he");
  c0->cd(7);
  h[1][0][2]->Draw("he");
  c0->cd(8);
  h[1][0][3]->Draw("he");

  c0->cd(9);
  h[2][0][0]->Draw("he");
  c0->cd(10);
  h[2][0][1]->Draw("he");
  c0->cd(11);
  h[2][0][2]->Draw("he");
  c0->cd(12);
  h[2][0][3]->Draw("he");
 

    sprintf(fname,"./n0n1n2.png");
    c0->SaveAs(fname);
    sprintf(fname,"./toydata.png");
    c2->SaveAs(fname);
  

}

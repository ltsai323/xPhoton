#include <TH1.h>
#include <cmath>
#define NUM_PART 3
#define NUM_FLVR 3 
#define NUM_TAGR 4

void comparison_n1n2(int ptbin = 0){

//  TFile *mc  = new TFile("../step2_makehisto/storeroot1/makehisto_sig_madgraph.root");
//  TFile *qcd = new TFile("../step2_makehisto/storeroot1/makehisto_QCD_madgraph.root");
  TFile *mc  = new TFile("../step2_makehisto/storeroot_weightcut1/makehisto_sig_madgraph.root");
  TFile *qcd = new TFile("../step2_makehisto/storeroot_weightcut1/makehisto_QCD_madgraph.root");


  cout << "ptbin is " << ptbin << endl;

  //toydata
  TH1F *h[NUM_PART][NUM_FLVR][NUM_TAGR];
  TH1F *h_part[NUM_PART][NUM_TAGR];
  TH1F *tag_data[NUM_TAGR];

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

  
  TCanvas *c1 = new TCanvas("c1","c1",2000, 1200);
  c1->Divide(NUM_TAGR,1);
  
  char fname[100];
  float chi2;
  float upperbdd =  2.8;
  float lowerbdd = -0.8;
  float binmidpoint, bincontent, binerror;

  for(int flvrIdx=0; flvrIdx<NUM_FLVR; flvrIdx++){
    for(int tagrIdx=0; tagrIdx<NUM_TAGR; tagrIdx++){    
      float upperboundary = tagrIdx == tagrIdx_svxmass ? 5. : 1.;
      chi2=h[1][flvrIdx][tagrIdx]->Chi2Test(h[2][flvrIdx][tagrIdx],"P CHI2");
      h[1][flvrIdx][tagrIdx]->Scale(1./h[1][flvrIdx][tagrIdx]->Integral());
      h[2][flvrIdx][tagrIdx]->Scale(1./h[2][flvrIdx][tagrIdx]->Integral());
      h[1][flvrIdx][tagrIdx]->SetMaximum(std::max(h[1][flvrIdx][tagrIdx]->GetMaximum(),h[2][flvrIdx][tagrIdx]->GetMaximum())*1.1);
      h[1][flvrIdx][tagrIdx]->SetStats(0);

      c1->cd(tagrIdx+1);
      TPad* pad1 = new TPad("pad1","",0.02, 0.30, 0.99, 0.99);
      TPad* pad2 = new TPad("pad1","",0.02, 0.02, 0.99, 0.30);

      // pad1->SetLeftMargin(0.02);
      pad1->SetRightMargin(0.035);
      // pad1->SetTopMargin(0.02); 
      pad1->SetBottomMargin(0.04);
      pad1->SetFrameBorderMode(0);
      pad1->SetBorderMode(0);
      pad1->SetBorderSize(0);

      // pad2->SetLeftMargin(0.02);
      pad2->SetRightMargin(0.035);
      pad2->SetTopMargin(0.04);
      pad2->SetBottomMargin(0.22);
      pad2->SetFrameBorderMode(0);
      pad2->SetBorderMode(0);
      pad2->SetBorderSize(0);

      pad1->Draw();
      pad2->Draw();
  

      //------------------------------------------------------------pad1
      pad1->cd();
      gPad->SetTickx();
      gPad->SetTicky();

      
      /*
        if(tagrIdx==0){
        hdata[flvrIdx]->SetName(Form("Btag_%s");}
        if(tagrIdx==1){
        hdata[flvrIdx]->SetName("CvsL");}
        if(tagrIdx==2){
        hdata[flvrIdx]->SetName("CvsB");}
      */
      
      h[1][flvrIdx][tagrIdx]->SetLineColor(kBlue);
      h[2][flvrIdx][tagrIdx]->SetLineColor(kRed);

      h[1][flvrIdx][tagrIdx]->Draw("he");
      h[2][flvrIdx][tagrIdx]->Draw("he same");


      //------------------------------------------------------------pad2
      gPad->RedrawAxis();
      pad2->cd();
      gPad->SetGridy();
      TH1F *hratio = (TH1F*)h[1][flvrIdx][tagrIdx]->Clone();
      hratio->Sumw2();
      hratio->Divide(h[2][flvrIdx][tagrIdx]);
      hratio->SetYTitle("N1 / N2");
      /*
      if(nn==0) hratio->SetXTitle("tag(B)");
      else if(nn==1) hratio->SetXTitle("tag(CvsL)");
      else if(nn==2) hratio->SetXTitle("tag(CvsB)");
      else hratio->SetXTitle("SVX mass");
      */
      hratio->GetXaxis()->SetLabelSize(0.07);
      hratio->GetXaxis()->SetTitleSize(0.1);
      hratio->GetXaxis()->SetLabelOffset(0.);
      //hratio->GetXaxis()->SetTitleOffset(0.8);
      hratio->GetYaxis()->SetLabelSize(0.07);
      hratio->GetYaxis()->SetTitleSize(0.07);
      //hratio->GetYaxis()->SetLabelOffset(0.3);
      hratio->GetYaxis()->SetTitleOffset(0.60);
      hratio->SetNdivisions(505,"X");
      hratio->SetNdivisions(205,"Y");
      hratio->SetLineColor(4);
      hratio->SetLineWidth(2);

      hratio->GetYaxis()->SetRangeUser(lowerbdd, upperbdd);
      h[1][flvrIdx][tagrIdx]->SetNdivisions(102,"Y");
      hratio->SetTitle("");
      hratio->Draw("pe");
      
      for(int bin=0; bin<10; bin++){
        binmidpoint =  tagrIdx == tagrIdx_svxmass ? (0.25+bin*0.5) : (0.05+bin*0.1) ;
        bincontent = hratio->GetBinContent(bin+1);
        binerror = hratio->GetBinError(bin+1);
        TLine *errorpatch = new TLine(binmidpoint,std::max(bincontent-binerror,lowerbdd),binmidpoint,std::min(bincontent+binerror,upperbdd));
        errorpatch->SetLineColor(4);
        errorpatch->SetLineWidth(2);
        errorpatch->Draw();

      }
      
      TLatex *tlx = new TLatex();
      tlx->SetTextSize(0.07);
      tlx->DrawLatex(0.065*upperboundary, 2.2, Form("#chi^{2}/NDF = %.2f", chi2/10.));
    
      gPad->RedrawAxis();

    }
    sprintf(fname,"./output_compn1n2/%s/%d.pdf",jetFlvr[flvrIdx],ptbin);
    c1->SaveAs(fname);
  }
}

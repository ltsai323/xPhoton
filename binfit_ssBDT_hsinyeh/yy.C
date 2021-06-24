void yy(){

  float ptcut[30] = {25, 34, 40, 55, 70, 85, 100,  115, 135, 155, 175, 190,
    200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000};

  // float ptcut[30] = {25, 34, 40, 55, 70, 85, 100,  115, 135, 155, 175,
  //   200, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000}; //22 bins

  // float ptcut[30] = {22, 30, 36, 50, 75, 90, 105,  120, 135, 150, 165, 175, 185,
  //   190, 200, 220, 250, 300, 350, 400, 500, 750, 1000, 1500, 2000, 3000, 10000}; //22 bins

  int nbin=21;

  TH1F* h_yield_2015[2][3];
  TH1F* h_yield_2016[2][3];
  ifstream f_2016, f_2015;
  f_2015.open("2016_yield.new.txt");
  f_2016.open("2016_yield.old.txt");

  float sig_yield_2015, sig_yield_2016;
  //float lumi2015 = 2.26;
  float lumi2015 = 35.9;
  float lumi2016 = 35.9;
  string tmp;

  TFile *ftest = new TFile("test.root","recreate");

  for (int ebeebin=0; ebeebin<2; ebeebin++){
    for (int jetbin=0; jetbin<3; jetbin++){

      h_yield_2015[ebeebin][jetbin] = new TH1F(Form("h_yield_2015_%d",ebeebin*3+jetbin),"",nbin, ptcut);
      h_yield_2016[ebeebin][jetbin] = new TH1F(Form("h_yield_2016_%d",ebeebin*3+jetbin),"",nbin, ptcut);

      for(int ii=0; ii<nbin; ii++){

        f_2016 >> tmp >> tmp >> tmp >> tmp >> sig_yield_2016 >> tmp;
        f_2015 >> tmp >> tmp >> tmp >> tmp >> sig_yield_2015 >> tmp;
        std::cout << sig_yield_2015 << " "
            << sig_yield_2015/lumi2015/h_yield_2015[ebeebin][jetbin]->GetBinWidth(ii+1) << " "
                  << sig_yield_2016 << " "
            << sig_yield_2016/lumi2016/h_yield_2016[ebeebin][jetbin]->GetBinWidth(ii+1) << std::endl;
        h_yield_2015[ebeebin][jetbin]->SetBinContent(ii+1, (sig_yield_2015/lumi2015)/h_yield_2015[ebeebin][jetbin]->GetBinWidth(ii+1));
        h_yield_2016[ebeebin][jetbin]->SetBinContent(ii+1, (sig_yield_2016/lumi2016)/h_yield_2016[ebeebin][jetbin]->GetBinWidth(ii+1));
      }
      auto c1 = new TCanvas("c1", "A ratio example",600,600);
      c1->SetLogy();

      h_yield_2015[ebeebin][jetbin]->SetNdivisions(505,"XY");
      h_yield_2015[ebeebin][jetbin]->SetXTitle("p_{T} (GeV)");
      h_yield_2015[ebeebin][jetbin]->SetYTitle("Entries / Lumi*GeV");
      h_yield_2015[ebeebin][jetbin]->SetMarkerStyle(8);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetRangeUser(0,1000);
      h_yield_2015[ebeebin][jetbin]->SetMarkerColor(1);
      h_yield_2016[ebeebin][jetbin]->SetMarkerStyle(22);
      h_yield_2016[ebeebin][jetbin]->SetMarkerColor(2);

      gStyle->SetPadBottomMargin(0.4);
      gStyle->SetLegendTextSize(0.035);

      TPad *pad1 = new TPad("pad1","pad1",0,0.2,1,1);
      pad1->SetBottomMargin(0);
      pad1->Draw();
      pad1->cd();
      pad1->SetLogy();
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetTitleOffset(1.2);
      h_yield_2015[ebeebin][jetbin]->DrawCopy("pe");
      h_yield_2016[ebeebin][jetbin]->Draw("pesame");
      c1->cd();
      TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.2);
      pad2->SetTopMargin(0);
      pad2->Draw();
      pad2->cd();
      pad2->SetGridy();
      h_yield_2015[ebeebin][jetbin]->Sumw2();
      h_yield_2015[ebeebin][jetbin]->SetStats(0);
      h_yield_2015[ebeebin][jetbin]->Divide(h_yield_2016[ebeebin][jetbin]);
      h_yield_2015[ebeebin][jetbin]->SetMarkerStyle(21);
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetRangeUser(0.5,1.5);
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetTitle("new / old");
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetTitleSize(0.15);
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetTitleOffset(0.3);
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetLabelSize(0.12);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetTitleOffset(1.2);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetTitleSize(0.15);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetLabelSize(0.15);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetTickSize(0.12);
      h_yield_2015[ebeebin][jetbin]->Draw("ep");
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetRangeUser(0.7,1.3);
      //h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetRangeUser(0.2,1.8);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetRangeUser(0,1000);
      pad1->cd();

      char pho_text[100];
      char jet_text[100];
      if(ebeebin==0) sprintf(pho_text,"|#eta_{#gamma}|<1.4442");
      else sprintf(pho_text,"1.566<|#eta_{#gamma}|<2.5");
      if(jetbin==0) sprintf(jet_text,"|#eta_{jet}|<1.5");
      else sprintf(jet_text,"1.5<|#eta_{jet}|<2.4");

      TLegend *tleg = new TLegend(0.4, 0.68, 0.88, 0.88);
      char text[100];
      sprintf(text,"CMS 13TeV, %s, %s",pho_text, jet_text);
      if(jetbin==2)   sprintf(text,"CMS 13TeV, %s",pho_text);
      tleg->SetHeader(text);
      tleg->SetFillColor(0);
      tleg->SetShadowColor(0);
      tleg->SetBorderSize(0);
      sprintf(text,"new");
      tleg->AddEntry(h_yield_2015[ebeebin][jetbin],text,"pl");
      sprintf(text,"old");
      tleg->AddEntry(h_yield_2016[ebeebin][jetbin],text,"pl");
      tleg->Draw();
      c1->Update();

      char phoEBEE[10], jetEBEE[10];
      if ( ebeebin==0 ) sprintf(phoEBEE,"phoEB");
      if ( ebeebin==1 ) sprintf(phoEBEE,"phoEE");
      if ( jetbin==0 ) sprintf(jetEBEE,"jetEB");
      if ( jetbin==1 ) sprintf(jetEBEE,"jetEE");
      if ( jetbin==2 ) sprintf(jetEBEE,"jetAll");
      c1->SaveAs(Form("ratio_%s_%s.png",phoEBEE, jetEBEE));
      c1->SaveAs(Form("ratio_%s_%s.pdf",phoEBEE, jetEBEE));
      delete c1;
    }
  }
}

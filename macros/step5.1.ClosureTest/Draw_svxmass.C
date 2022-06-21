void Draw_svxmass(int argc){


  TFile *f = new TFile("postfit.root");
  TFile *f1 = new TFile("toy_data.root");
  TFile *f2 = new TFile("toy_mc.root");

  TH1F *h1[20];
  TH1F *hdata[3];
  char hname[100];
  char fname[100];  
  
  Int_t ci_cyan = TColor::GetFreeColorIndex();
  TColor *color = new TColor(ci_cyan, 0.6275, 0.9255, 0.8471);
  Int_t ci_red = TColor::GetFreeColorIndex();
  TColor *color1 = new TColor(ci_red, 0.9059, 0.1961, 0.1373);    
  Int_t ci_yellow = TColor::GetFreeColorIndex(); 
  TColor *color2 = new TColor(ci_yellow, 0.95804, 0.8902, 0.5569);

  int nalgo=3;
  TCanvas *c1 = new TCanvas("c1","c1",1800, 800);
  c1->Divide(3,1);


  for(int nn=0; nn<nalgo; nn++){ //tagalgo                                                                                          
                                     
    if(nn!=3){

      //sprintf(hname,"cat%d_postfit/data_obs",nn);
      //hdata[nn] = (TH1F*)f->Get(hname);
      sprintf(hname,"tag%d",nn);
      hdata[nn] = (TH1F*)f1->Get(hname);
      hdata[nn]->SetMarkerStyle(8);
      //hdata[nn]->SetName("test");
      hdata[nn]->SetTitle("");
      hdata[nn]->SetMaximum(hdata[nn]->GetMaximum()*1.1);
      hdata[nn]->SetMinimum(0);
      hdata[nn]->SetNdivisions(505,"XY");
      hdata[nn]->GetXaxis()->SetLabelOffset(1.);

      sprintf(hname,"cat%d_postfit/bkgL",nn);
      h1[nn*3]=(TH1F*)f->Get(hname);
      //h1[nn*3]->Scale(mu3);
      h1[nn*3]->SetFillColor(ci_yellow);
      h1[nn*3]->SetLineColor(1);    

      sprintf(hname,"cat%d_postfit/sigC",nn);
      h1[1+nn*3]=(TH1F*)f->Get(hname);
      //h1[1+nn*3]->Scale(mu2);
      h1[1+nn*3]->SetFillColor(ci_cyan);
      h1[1+nn*3]->Add(h1[nn*3]);
      h1[1+nn*3]->SetLineColor(1);    

      sprintf(hname,"cat%d_postfit/sigB",nn);
      h1[2+nn*3]=(TH1F*)f->Get(hname);
      //h1[2+nn*3]->Scale(mu1);//
      h1[2+nn*3]->SetFillColor(ci_red);
      h1[2+nn*3]->Add(h1[1+nn*3]);
      h1[2+nn*3]->SetLineColor(1);    
    }else{
      //sprintf(hname,"svxmass")//"h_jettag_0_%d_0_0_3",argc);
      hdata[nn] = (TH1F*)f1->Get("tag3");
      hdata[nn]->SetMarkerStyle(8);
      hdata[nn]->SetTitle("");
      hdata[nn]->SetMaximum(hdata[nn]->GetMaximum()*1.1);
      hdata[nn]->SetMinimum(0); 
      hdata[nn]->SetNdivisions(505,"XY");
      hdata[nn]->GetXaxis()->SetLabelOffset(1.);

      sprintf(hname,"tag3_L");
      h1[nn*3]=(TH1F*)f2->Get(hname);
      h1[nn*3]->Scale(h1[0]->Integral());
      h1[nn*3]->SetFillColor(ci_yellow);
      h1[nn*3]->SetLineColor(1);    

      sprintf(hname,"tag3_C");
      h1[1+nn*3]=(TH1F*)f2->Get(hname);
      h1[1+nn*3]->Scale(h1[1]->Integral()-h1[0]->Integral());
      h1[1+nn*3]->SetFillColor(ci_cyan);
      h1[1+nn*3]->Add(h1[nn*3]);
      h1[1+nn*3]->SetLineColor(1);    

      sprintf(hname,"tag3_B");
      h1[2+nn*3]=(TH1F*)f2->Get(hname);
      h1[2+nn*3]->Scale(h1[2]->Integral()-h1[1]->Integral());//
      h1[2+nn*3]->SetFillColor(ci_red);
      h1[2+nn*3]->Add(h1[1+nn*3]);
      h1[2+nn*3]->SetLineColor(1);  
                
        
    }
  }
  

  for(int nn=0; nn<nalgo; nn++){ //tagalgo    
    c1->cd(nn+1);

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
  
    pad1->cd();
    gPad->SetTickx();
    gPad->SetTicky();

    //------------------------------------------------------------
    if(nn==0){
    hdata[nn]->SetName("Btag");}
    if(nn==1){
    hdata[nn]->SetName("CvsL");}
    if(nn==2){
    hdata[nn]->SetName("CvsB");}
    hdata[nn]->Draw("pe1 same");
    //hdata[nn]->SetName("");
    h1[2+nn*3]->Draw("hf same");
    h1[1+nn*3]->Draw("hf same");
    h1[nn*3]->Draw("hf same");

    hdata[nn]->Draw("pe1 same");
    if(nn==0){
      TLegend *tleg = new TLegend(0.3, 0.6, 0.8, 0.88);
      char text[50];
      tleg->SetFillStyle(0);
      tleg->SetTextSize(0.04);
      tleg->SetShadowColor(0);
      tleg->SetBorderSize(0);  
      sprintf(text,"Data (%.0f evts)", hdata[nn]->Integral());
      tleg->AddEntry(hdata[nn],text,"pl");
      sprintf(text,"Fit  (%.1f evts)", h1[2+nn*3]->Integral());
      tleg->AddEntry(h1[2+nn*3],text,"l");

      tleg->AddEntry(h1[nn*3],  Form("l jet (%7.1f evts)", h1[nn*3]->Integral()),"fb");
      tleg->AddEntry(h1[1+nn*3],Form("c jet (%7.1f evts)", h1[1+nn*3]->Integral()-h1[nn*3]->Integral()),"fb");
      tleg->AddEntry(h1[2+nn*3],Form("b jet (%7.1f evts)", h1[2+nn*3]->Integral()-h1[1+nn*3]->Integral()),"fb");
      tleg->Draw();
    }
    if(nn==3){
      gPad->SetLogy();
    }

    gPad->RedrawAxis();

    pad2->cd();
    gPad->SetGridy();
    TH1F *hratio = (TH1F*)hdata[nn]->Clone();
    hratio->Divide(h1[2+nn*3]);
    if(nn!=3){
    hratio->SetYTitle("Data / Fit");
    }else{
    hratio->SetYTitle("Data / MC");
    }
    

    float chi2;
    
    chi2=hdata[nn]->Chi2Test(h1[2+nn*3],"P CHI2");

    // float tmptmp=0.;
    // int nbin=0;
    // TH1F *hratio = new TH1F("hratio","",10, 0., 1.);
    // for(int ii=0; ii<hdata[nn]->GetNbinsX(); ii++){
    //   if(hdata[nn]->GetBinContent(ii+1) > 0.){
    //  float tmpV = (hdata[nn]->GetBinContent(ii+1)-h1[2+nn*3]->GetBinContent(ii+1))/hdata[nn]->GetBinError(ii+1);
    //  hratio->SetBinContent(ii+1, tmpV);
    //  tmptmp+= tmpV * tmpV;
    //  hratio->SetBinError(ii+1, 1.);//hdata->GetErrorY(ii)/yy);
    //  nbin++;
    //   }
    // }
    // printf("tmptmp = %.2f \n", tmptmp);
    // hratio->SetYTitle("(Data-Fit)/#sigma_{Data}");

    if(nn==0) hratio->SetXTitle("tag(B)");
    else if(nn==1) hratio->SetXTitle("tag(CvsL)");
    else if(nn==2) hratio->SetXTitle("tag(CvsB)");
    else hratio->SetXTitle("SVX mass");

    hratio->GetXaxis()->SetLabelSize(0.1);
    hratio->GetXaxis()->SetTitleSize(0.1);
    hratio->GetXaxis()->SetLabelOffset(0.);
    //hratio->GetXaxis()->SetTitleOffset(0.8);
    hratio->GetYaxis()->SetLabelSize(0.1);
    hratio->GetYaxis()->SetTitleSize(0.1);
    hratio->GetYaxis()->SetTitleOffset(0.35);
    hratio->SetNdivisions(505,"X");
    hratio->SetNdivisions(205,"Y");
    hratio->SetLineColor(4);
    hratio->SetLineWidth(2);

    // hratio->GetYaxis()->SetRangeUser(-10, 10);
    hratio->GetYaxis()->SetRangeUser(0.4, 1.6);

    
    hdata[nn]->SetNdivisions(102,"Y");
    hratio->Draw("pe");

    TLatex *tlx = new TLatex();
    tlx->SetTextSize(0.08);
    tlx->DrawLatex(0.05, 1.2, Form("#chi^{2}/NDF = %.2f", chi2/10.));
    
    gPad->RedrawAxis();
    

  }


  sprintf(fname,"./plots_fittoy/%d.png",argc);
  c1->SaveAs(fname);
//  c1->SaveAs("testfit.png");
        
  ofstream ofs;
  ofs.open("Nfitted.txt", std::ios::app);
  if (!ofs.is_open()) {
       cout << "Failed to open file.\n";
  } else {
        ofs <<  hdata[0]->Integral() << "\t" << h1[0]->Integral() << "\t" << h1[1]->Integral()-h1[0]->Integral() << "\t" << h1[2]->Integral()-h1[1]->Integral() << "\n";
  }
}

void Draw_ptetarw(){
  TFile *f = new TFile("rw_out.root");
  
  TH2F *hsig = (TH2F*)f->Get("h_pho_pt_eta");
  TH2F *hsig_rw = (TH2F*)f->Get("h_pho_pt_eta_rw");
  TH2F *hbkg = (TH2F*)f->Get("h_fake_pt_eta");
  TH2F *hbkg_rw = (TH2F*)f->Get("h_fake_pt_eta_rw");


  TCanvas *c2 = new TCanvas("c2","",1000,500);
  c2->Divide(2,1);
  c2->cd(1);
  gPad->SetLogy();
  TH1F *hsig_pt = (TH1F*)hsig->ProjectionX();
  TH1F *hsig_ptrw = (TH1F*)hsig_rw->ProjectionX();
  TH1F *hbkg_pt = (TH1F*)hbkg->ProjectionX();
  TH1F *hbkg_ptrw = (TH1F*)hbkg_rw->ProjectionX();
  
  
  hbkg_pt->SetLineColor(2);
  hbkg_pt->SetMarkerColor(2);
  hbkg_pt->SetLineColor(2);
  hbkg_pt->SetMarkerStyle(25);
  hbkg_pt->SetLineWidth(2);
  hbkg_pt->SetMaximum(hbkg_pt->GetMaximum()*5.);
  // hbkg_pt->SetMinimum(0.5);

  hbkg_pt->Draw();
  hsig_pt->Draw("same");

  hsig_ptrw->SetMarkerStyle(26);
  hsig_ptrw->Draw("p e same");

  hbkg_ptrw->SetMarkerColor(6);
  hbkg_ptrw->SetLineColor(6);
  hbkg_ptrw->SetMarkerStyle(27);
  //hbkg_ptrw->Draw("p  same");
  
  TLegend *tleg = new TLegend(0.2, 0.65, 0.8, 0.85);
  //tleg->SetHeader(text);
  tleg->SetFillColor(0);
  tleg->SetShadowColor(0);
  tleg->SetBorderSize(0);
  tleg->AddEntry(hsig_pt,"signal unweighted","lpe");
  tleg->AddEntry(hsig_ptrw,"signal weighted","lpe");
  tleg->AddEntry(hbkg_pt,"bkg unweighted","lpe");
  tleg->AddEntry(hbkg_ptrw,"bkg weighted","lpe");

  tleg->Draw();



  c2->cd(2);
  gPad->SetLogy();
  TH1F *hsig_eta = (TH1F*)hsig->ProjectionY();
  TH1F *hsig_etarw = (TH1F*)hsig_rw->ProjectionY();
  TH1F *hbkg_eta = (TH1F*)hbkg->ProjectionY();
  TH1F *hbkg_etarw = (TH1F*)hbkg_rw->ProjectionY();
  
  
  hbkg_eta->SetLineColor(2);
  hbkg_eta->SetMarkerColor(2);
  hbkg_eta->SetMarkerStyle(25);
  hbkg_eta->SetLineWidth(2);
  hbkg_eta->SetMaximum(hbkg_eta->GetMaximum()*5.);
  //hbkg_eta->SetMinimum(0.5);
  hbkg_eta->Draw();
  hsig_eta->Draw("same");
  hsig_etarw->SetMarkerStyle(26);
  hsig_etarw->Draw("p e same");

  hbkg_etarw->SetMarkerColor(2);
  hbkg_etarw->SetMarkerStyle(27);
  //hbkg_etarw->Draw("p e same");

}

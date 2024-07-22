{
  TTree *tree = new TTree("tree", "tree");
  tree->ReadFile("frac.dat", "frac_L/F:frac_C/F:frac_B/F");
  
  int ptbin = 6;
  TFile *mc  = new TFile("../step2_makehisto/storeroot_weightcut1/makehisto_sig_madgraph.root");
  TH1F *mc_l = (TH1F*)mc->Get(Form("h_jettag_0_%d_0_0_0_1", ptbin));
  TH1F *mc_c = (TH1F*)mc->Get(Form("h_jettag_0_%d_0_1_0_1", ptbin));
  TH1F *mc_b = (TH1F*)mc->Get(Form("h_jettag_0_%d_0_2_0_1", ptbin));
  float num1,num2,num3;
  float total;
  num1 = mc_l->Integral();
  num2 = mc_c->Integral();
  num3 = mc_b->Integral();
  total = num1 + num2 + num3;

  TCanvas* c1 = new TCanvas("c1","",800,600);

  tree->Draw("frac_B>>bfrac","","h");
  TH1F *bfrac = (TH1F*)gDirectory->Get("bfrac");
  bfrac->Fit("gaus");
  bfrac->SetNameTitle("bfrac","b-jet fraction");
  c1->SaveAs("frac_b.png");

  tree->Draw("frac_C>>cfrac","","h");
  TH1F *cfrac = (TH1F*)gDirectory->Get("cfrac");
  cfrac->Fit("gaus");
  cfrac->SetNameTitle("cfrac","c-jet fraction");
  c1->SaveAs("frac_c.png");

  tree->Draw(Form("((frac_B*%f-%f)/sqrt(%f))>>bfrac_norm",total,num3,num3),"","h");
  TH1F *bfrac_norm = (TH1F*)gDirectory->Get("bfrac_norm");
  bfrac_norm->Fit("gaus");
  bfrac_norm->SetNameTitle("bfrac_norm","b-jet");
  c1->SaveAs("frac_b_norm.png");

  tree->Draw(Form("((frac_C*%f-%f)/sqrt(%f))>>cfrac_norm",total,num2,num2),"","h");
  TH1F *cfrac_norm = (TH1F*)gDirectory->Get("cfrac_norm");
  cfrac_norm->Fit("gaus");
  cfrac_norm->SetNameTitle("cfrac_norm","c-jet");
  c1->SaveAs("frac_c_norm.png");
}

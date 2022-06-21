{
  TTree *MyTree = new TTree("MyTree", "MyTree");
  MyTree->ReadFile("frac.dat", "frac_L/F:frac_C/F:frac_B/F");
  MyTree->SetEstimate(-1);
  MyTree->SetMarkerStyle(kFullStar);
  MyTree->Draw("frac_B");
}

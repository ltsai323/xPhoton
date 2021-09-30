void runMakeHisto(Int_t op=0){
  gROOT->LoadMacro("MakeHisto.C++");
  MakeHisto t(op);
  t.Loop();
}

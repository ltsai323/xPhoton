std::vector<float> ptbin_ranges()
{
  // for 2016
  //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
  std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
  return vec_ptcut;
}
struct DATTree
{
    DATTree( const char* datfile ) :
        _tree( new TTree() )
    {
        _tree->ReadFile(datfile);

        if (!_tree->FindBranch("bkg") ) throw std::runtime_error("DATTree::DATTree(); input dat file is not loaded or not fake yield. Please check input dat file\n");
        _tree->SetBranchAddress("ptbin"  , &ptbin);
        _tree->SetBranchAddress("EBEE"   , &etabin);
        _tree->SetBranchAddress("jetbin" , &jetbin);
        _tree->SetBranchAddress("bkg"    , &fityield);
        _tree->SetBranchAddress("bkg_err", &fityield_err);

        _ptmax  = _tree->GetMaximum("ptbin" ) + 1;
        _etamax = _tree->GetMaximum("EBEE"  ) + 1;
        _jetmax = _tree->GetMaximum("jetbin") + 1;
    }
    ~DATTree()
    { delete _tree; printf("~DATTree() : Loaded Tree Closed\n"); }

    Int_t MaxBin_PtBin () { return _ptmax;  }
    Int_t MaxBin_EtaBin() { return _etamax; }
    Int_t MaxBin_JetBin() { return _jetmax; }

    TTree* GetTree() { return _tree; }

    TTree *_tree;
    Int_t   ptbin;
    Int_t   etabin;
    Int_t   jetbin;
    Float_t fityield;
    Float_t fityield_err;

    Int_t  _ptmax;
    Int_t  _etamax;
    Int_t  _jetmax;
};
TTree* ReadDat(const char* infile)
{
    TTree* t = new TTree();
    t->ReadFile(infile);
    t->SetDirectory(nullptr);
    return t;
}


void yield_cmp_plot() {
  std::vector<float> ptranges = ptbin_ranges();
  float* ptcut = &ptranges.front();
  int nbin = ptranges.size()-1;
  nbin=22;


  TTree* t_2015 = ReadDat("2015_yield.dat");
  TTree* t_2016 = ReadDat("2016_yield.dat");
  t_2015->Print();
  
  float sig_yield_2015, sig_yield_2016;
  float lumi2015 = 2.26;
  float lumi2016 = 35.9;
  string tmp;

  TH1F* h_yield_2015[2][3];
  TH1F* h_yield_2016[2][3];


  TFile *ftest = new TFile("test.root","recreate");
  for (int ebeebin=0; ebeebin<2; ebeebin++){
    for (int jetbin=0; jetbin<3; jetbin++){

      h_yield_2015[ebeebin][jetbin] = new TH1F(Form("h_yield_2015_%d",ebeebin*3+jetbin),"",nbin, ptcut);
      h_yield_2016[ebeebin][jetbin] = new TH1F(Form("h_yield_2016_%d",ebeebin*3+jetbin),"",nbin, ptcut);
      h_yield_2015[ebeebin][jetbin]->Sumw2();
      h_yield_2016[ebeebin][jetbin]->Sumw2();
      h_yield_2015[ebeebin][jetbin]->SetStats(false);
      h_yield_2016[ebeebin][jetbin]->SetStats(false);
    }}
  {
      TTree* tmptree = t_2015;
      float lumi = lumi2015;
      int   ptbin, isEE, jetbin;
      float Yield, Yielderr;
      tmptree->SetBranchAddress("ptbin"    , &ptbin    );
      tmptree->SetBranchAddress("EBEE"     , &isEE     );
      tmptree->SetBranchAddress("jetbin"   , &jetbin   );
      tmptree->SetBranchAddress("yield"    , &Yield    );
      tmptree->SetBranchAddress("yield_err", &Yielderr );
      for ( Long64_t ievt = 0; ievt < tmptree->GetEntries(); ++ievt )
      {
          tmptree->GetEntry(ievt);
          TH1* h = h_yield_2015[isEE][jetbin];
          float denuminator = lumi * h->GetBinWidth(ptbin+1);
          h->SetBinContent( ptbin+1, Yield    / denuminator );
          float fiterr = Yielderr / denuminator;
          float staterr = sqrt(Yield) / denuminator;
          //float myerr = fiterr*fiterr + staterr*staterr;
          h->SetBinError  ( ptbin+1, staterr );
      }
  }
  {
      TTree* tmptree = t_2016;
      float lumi = lumi2016;
      int   ptbin, isEE, jetbin;
      float Yield, Yielderr;
      tmptree->SetBranchAddress("ptbin"    , &ptbin    );
      tmptree->SetBranchAddress("EBEE"     , &isEE     );
      tmptree->SetBranchAddress("jetbin"   , &jetbin   );
      tmptree->SetBranchAddress("yield"    , &Yield    );
      tmptree->SetBranchAddress("yield_err", &Yielderr );
      for ( Long64_t ievt = 0; ievt < tmptree->GetEntries(); ++ievt )
      {
          tmptree->GetEntry(ievt);
          TH1* h = h_yield_2016[isEE][jetbin];
          float denuminator = lumi * h->GetBinWidth(ptbin+1);
          h->SetBinContent( ptbin+1, Yield    / denuminator );
          float fiterr = Yielderr / denuminator;
          float staterr = sqrt(Yield) / denuminator;
          //float myerr = fiterr*fiterr + staterr*staterr;
          h->SetBinError  ( ptbin+1, staterr );
          
          printf("2016 yield at ptbin %2d, etabin %2d and jet etabin %2d = %8.0f +- %6.1f(stat) and %6.1f(fit).\n", ptbin, isEE, jetbin, Yield/denuminator, sqrt(Yield/denuminator), Yielderr/denuminator);
      }
  }
  



  for (int ebeebin=0; ebeebin<2; ebeebin++){
    for (int jetbin=0; jetbin<3; jetbin++){
      TCanvas cc("c1", "A ratio example",600,600);
      TCanvas* c1 = &cc;
      c1->Clear();
      c1->SetLogy();

      h_yield_2015[ebeebin][jetbin]->SetMaximum( h_yield_2016[ebeebin][jetbin]->GetMaximum() * 10. );
      h_yield_2015[ebeebin][jetbin]->SetNdivisions(505,"XY");
      h_yield_2015[ebeebin][jetbin]->SetXTitle("p_{T} (GeV)");
      h_yield_2015[ebeebin][jetbin]->SetYTitle("Entries / Lumi / GeV");
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
      h_yield_2015[ebeebin][jetbin]->DrawCopy();
      h_yield_2016[ebeebin][jetbin]->Draw("p e0 same");
      c1->cd();
      TPad *pad2 = new TPad("pad2","pad2",0,0,1,0.2);
      pad2->SetTopMargin(0);
      pad2->Draw();
      pad2->cd();
      pad2->SetGridy();
      h_yield_2015[ebeebin][jetbin]->Divide(h_yield_2016[ebeebin][jetbin]);
      h_yield_2015[ebeebin][jetbin]->SetMarkerStyle(21);
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetRangeUser(0.5,1.5);
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetTitle("2015 / 2016");
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetTitleSize(0.15);
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetTitleOffset(0.3);
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetLabelSize(0.12);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetTitleOffset(1.2);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetTitleSize(0.15);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetLabelSize(0.15);
      h_yield_2015[ebeebin][jetbin]->GetXaxis()->SetTickSize(0.12);
      h_yield_2015[ebeebin][jetbin]->Draw("ep");
      h_yield_2015[ebeebin][jetbin]->GetYaxis()->SetRangeUser(0.5,1.5);
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
      sprintf(text,"2015");
      tleg->AddEntry(h_yield_2015[ebeebin][jetbin],text,"pl");
      sprintf(text,"2016");
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

    }
  }
}
TH1*** ReadFromDAT(const char* filename) {
  std::vector<float> ptranges = ptbin_ranges();
  float* ptcut = &ptranges.front();
  int nbin = ptranges.size()-1;
  nbin=22;


  DATTree data_base(filename);

  TH1*** hist;
  hist = new TH1**[ data_base.MaxBin_EtaBin() ];
  for ( int etabin = 0; etabin < data_base.MaxBin_EtaBin(); ++etabin )
      hist[etabin] = new TH1*[ data_base.MaxBin_JetBin() ];
  for ( int etabin = 0; etabin < data_base.MaxBin_EtaBin(); ++etabin )
      for ( int jetbin = 0; jetbin < data_base.MaxBin_JetBin(); ++jetbin )
  {
      const char* name = "yield_2015";
      hist[ebeebin][jetbin] = new TH1F(Form("%s_%d_%d",name,ebeebin,jetbin),"",nbin, ptcut);
      hist[ebeebin][jetbin]->Sumw2();
      hist[ebeebin][jetbin]->SetStats(false);
  }
  TTree* t = data_base.GetTree();
  for ( unsigned ievt = 0; ievt < t->GetEntries(); ++ievt )
  {
      t->GetEntry(ievt);
      float isEE = data_base.etabin;
      float jetbin = data_base.jetbin;
      float Yield = data_base.fityield;

      TH1* h = hist[isEE][jetbin];
      /*
      float denuminator = h->GetBinWidth(ptbin+1);
      h->SetBinContent( ptbin+1, Yield  / denuminator );
      //float fiterr = Yielderr / denuminator;
      float staterr = sqrt(Yield) / denuminator;
      //float myerr = fiterr*fiterr + staterr*staterr;
      h->SetBinError  ( ptbin+1, staterr );
      */
  }

  return hist;
}

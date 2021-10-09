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

        _tree->SetBranchAddress("ptbin"  , &ptbin);
        _tree->SetBranchAddress("EBEE"   , &etabin);
        _tree->SetBranchAddress("jetbin" , &jetbin);
        if ( _tree->FindBranch("bkg") )
        {
            _tree->SetBranchAddress("bkg"    , &fityield);
            _tree->SetBranchAddress("bkg_err", &fityield_err);
        }
        else if ( _tree->FindBranch("yield") )
        {
            _tree->SetBranchAddress("yield"    , &fityield);
            _tree->SetBranchAddress("yield_err", &fityield_err);
        }
        else throw std::runtime_error("DATTree::DATTree(); input dat file is incorrect. Please check input dat file\n");


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

TH1** check()
{
    TH1* h[10];
    for ( int i=0; i<10; ++i )
        h[i] = new TH1F("kk", "", 10,0,10);
    return h;
}


void TruthComparison()
{
    DATTree fityields("../step4.DrawYield/storeroot/fakesample0_yield_barrelJet.dat");
    DATTree fitbkgs  ("../step4.DrawYield/storeroot/fakesample0_bkg_barrelJet.dat");
    TFile* sigfile = TFile::Open("../step7.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_sig.root");
    //TFile* bkgfile = TFile::Open("../step7.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_bkg.root");
    std::vector<float> ptranges = ptbin_ranges();
    std::cout << ptranges.front();
    for ( auto range : ptranges ) std::cout << range << ", "; std::cout << "\n";
    int nbin = 16;
    TH1F* h_fit_sig = new TH1F( "fitsig", "", nbin, &ptranges.front() );
    TH1F* h_fit_bkg = new TH1F( "fitbkg", "", nbin, &ptranges.front() );
    TH1F* h_mc_sig = new TH1F( "sig", "", nbin, &ptranges.front() );
    TH1F* h_mc_bkg = new TH1F( "bkg", "", nbin, &ptranges.front() );
    h_fit_sig->Sumw2();
    h_fit_bkg->Sumw2();
    h_mc_sig->Sumw2();
    h_mc_bkg->Sumw2();

    TTree* t = fityields.GetTree();
    for ( int ievt = 0; ievt != t->GetEntries(); ++ievt )
    {
        t->GetEntry(ievt);

        // only use barrel photon
        if ( fityields.etabin == 1 ) continue;
        if ( fityields.ptbin > 18 ) continue;
        h_fit_sig->SetBinContent( fityields.ptbin+1, fityields.fityield );
        h_fit_sig->SetBinError( fityields.ptbin+1, fityields.fityield_err );
        
        char histname[100];
        sprintf( histname, "data_0_0_%d_px1_chIso", fityields.ptbin );
        TH1* horig = (TH1*) sigfile->Get(histname);
        h_mc_sig->SetBinContent( fityields.ptbin+1, horig->GetEntries() );
    }


    
    
    //h_fit_sig->SetMarkerColor(2);
    //h_fit_bkg->SetMarkerColor(2);
    h_mc_sig->SetLineColor(48);
    h_mc_bkg->SetLineColor(48);
    //h_mc_sig->SetFillColor(48);
    //h_mc_bkg->SetFillColor(48);

    TCanvas* c1 = new TCanvas("c1","",1200,1000);
    std::cout << "1. " << h_mc_sig->GetNbinsX() << ". 2. " << h_fit_sig->GetNbinsX() << std::endl;
    TRatioPlot* ratiosig = new TRatioPlot(h_fit_sig, h_mc_sig, "divsym");
    //TRatioPlot* ratiobkg = new TRatioPlot(h_fit_bkg, h_mc_bkg);

    ratiosig->Draw();
    ratiosig->GetLowerRefGraph()->SetMaximum(1.4);
    ratiosig->GetLowerRefGraph()->SetMinimum(0.6);
    ratiosig->GetUpperPad()->cd();
    ratiosig->GetUpperPad()->Clear();
    h_mc_sig->Draw();
    h_fit_sig->Draw("p same");
    c1->Update();
    c1->SaveAs("h_cmp_barrelpho_barreljet.png");
}


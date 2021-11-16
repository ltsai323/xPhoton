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

void Visualize_RatioPlot(TH1* hist, const char* ytitle)
{
    hist->GetYaxis()->SetTitle(ytitle);
    hist->SetNdivisions(510, "X");
    hist->SetNdivisions(505, "Y");

    hist->SetLineWidth(0);
    hist->SetMarkerSize(2);
    hist->GetYaxis()->SetLabelSize(0.1);
    hist->GetYaxis()->SetTitleSize(0.15);
    hist->GetYaxis()->SetTitleOffset(0.30);
    hist->GetXaxis()->SetLabelSize(0.1);

    return hist;
}
TH1* devhist(TH1* h_target, TH1* h_base, const char* ytitle="#frac{|data-truth|}{err_data}")
{
    TH1* hist = (TH1*) h_target->Clone();
    std::vector<float> val;
    for ( int i=0; i < h_target->GetNbinsX(); ++i )
    {
        float diff = fabs( h_target->GetBinContent(i+1)-h_base->GetBinContent(i+1) );
        float err = h_target->GetBinError(i+1);
        if ( err > 1e-3 )
            val.push_back( diff / err );
        else
            val.push_back( -1. );
        std::cout << i << " : " << diff / err << std::endl;
    }
    for ( int i=0; i < val.size(); ++i )
    {
        hist->SetBinContent( i+1, val[i] );
        hist->SetBinError( i+1, 0 );
    }
    
    hist->SetMinimum( 0. );
    hist->SetMaximum( 5. );
    Visualize_RatioPlot(hist, ytitle);
    return hist;
}
TH1* ratiohist(TH1* h_numerator, TH1* h_denumerator, const char* ytitle="fit/truth")
{
    TH1* hist = (TH1*) h_numerator->Clone();
    hist->Divide(h_denumerator);
    hist->GetYaxis()->SetTitle(ytitle);
    hist->SetMinimum(0.5);
    hist->SetMaximum(1.5);

    Visualize_RatioPlot(hist, ytitle);
    return hist;
}
TPad* UpperPad()
{
    TPad* pad = new TPad("upperpad", "", 0., 0.245, 1., 0.98);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.05);
    pad->SetBottomMargin(0.019);
    pad->SetLeftMargin(0.135);//0.12
    pad->SetRightMargin(0.06);//0.12

	return pad;
}
TPad* LowerPad()
{
    TPad* pad = new TPad("lowerpad","",0.,0.0,1.,0.258);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.0);
    pad->SetBottomMargin(0.35);
    pad->SetLeftMargin(0.135);
    pad->SetRightMargin(0.06);

	return pad;
}
const char* File_DATOldBkg(int isendcapjet )
{ return Form("data_bkg_%sJet.dat", isendcapjet?"endcap":"barrel"); }
const char* File_DATNewBkg()
{ return "data.bkg.dat"; }
const char* File_DATOldYield(int isendcapjet )
{ return Form("data_yield_%sJet.dat", isendcapjet?"endcap":"barrel"); }
const char* File_DATNewYield()
{ return "data.yield.dat"; }



void TruthComparison(int fakeid, int isendcappho, int isendcapjet)
{
    DATTree fityields( File_DATRec(fakeid, isendcapjet) );
    DATTree fitbkgs  ( File_DATRecBkg(fakeid, isendcapjet) );
    TFile* sigfile = TFile::Open( File_Source_Sig(fakeid) );
    TFile* bkgfile = TFile::Open( File_Source_Bkg(fakeid) );
    TFile* totfile = TFile::Open( File_Source_Overall(fakeid) );

    std::vector<float> ptranges = ptbin_ranges();
    int nbin = 16;

    TH1F* h_fit_sig = new TH1F( "fitsig", "", nbin, &ptranges.front() );
    TH1F* h_fit_bkg = new TH1F( "fitbkg", "", nbin, &ptranges.front() );
    TH1F* h_mc_sig = new TH1F( "sig", "", nbin, &ptranges.front() );
    TH1F* h_mc_bkg = new TH1F( "bkg", "", nbin, &ptranges.front() );
    TH1F* h_mc_tot = new TH1F( "tot", "", nbin, &ptranges.front() );
    h_fit_sig->Sumw2();
    h_fit_bkg->Sumw2();
    h_mc_sig->Sumw2();
    h_mc_bkg->Sumw2();
    h_mc_tot->Sumw2();


    TTree* t = fityields.GetTree();
    for ( int ievt = 0; ievt != t->GetEntries(); ++ievt )
    {
        t->GetEntry(ievt);

        // only use barrel photon
        if ( isendcappho )
        { if ( fityields.etabin == 0 ) continue; }
        else
        { if ( fityields.etabin == 1 ) continue; }
        if ( fityields.ptbin > 18 ) continue;
        h_fit_sig->SetBinContent( fityields.ptbin+1, fityields.fityield );
        h_fit_sig->SetBinError( fityields.ptbin+1, fityields.fityield_err );
        
        char histname[100];
        sprintf( histname, "data_%d_%d_%d_px1_chIso", fityields.etabin, fityields.jetbin, fityields.ptbin );
        TH1* horig = (TH1*) sigfile->Get(histname);
        h_mc_sig->SetBinContent( fityields.ptbin+1, horig->GetEntries() );
    }
    t = fitbkgs.GetTree();
    for ( int ievt = 0; ievt != t->GetEntries(); ++ievt )
    {
        t->GetEntry(ievt);

        // only use barrel photon
        if ( isendcappho )
        { if ( fitbkgs.etabin == 0 ) continue; }
        else
        { if ( fitbkgs.etabin == 1 ) continue; }
        if ( fitbkgs.ptbin > 18 ) continue;
        h_fit_bkg->SetBinContent( fitbkgs.ptbin+1, fitbkgs.fityield );
        h_fit_bkg->SetBinError( fitbkgs.ptbin+2, fitbkgs.fityield_err );
        
        char histname[100];
        sprintf( histname, "data_%d_%d_%d_px1_chIso", fitbkgs.etabin, fitbkgs.jetbin, fitbkgs.ptbin );
        TH1* horig = (TH1*) bkgfile->Get(histname);
        h_mc_bkg->SetBinContent( fitbkgs.ptbin+1, horig->GetEntries() );

        sprintf( histname, "data_%d_%d_%d_px1_chIso", fitbkgs.etabin, fitbkgs.jetbin, fitbkgs.ptbin );
             horig = (TH1*) totfile->Get(histname);
        h_mc_tot->SetBinContent( fitbkgs.ptbin+1, horig->GetEntries() );
    }

    float maxval = h_mc_tot->GetMaximum() * 1.5;
    h_mc_tot ->SetMaximum( maxval );
    h_mc_sig ->SetMaximum( maxval );
    h_mc_bkg ->SetMaximum( maxval );
    h_fit_sig->SetMaximum( maxval );
    h_fit_bkg->SetMaximum( maxval );

    
    
    h_fit_sig->SetMarkerColor(kRed);
    h_fit_bkg->SetMarkerColor(kBlue);
    h_fit_sig->SetMarkerStyle(20);
    h_fit_bkg->SetMarkerStyle(34);
    h_fit_sig->SetMarkerSize(2);
    h_fit_bkg->SetMarkerSize(2);
    h_fit_sig->SetLineColor(kRed);
    h_fit_bkg->SetLineColor(kBlue);
    h_mc_sig->SetLineColor(48);
    h_mc_bkg->SetLineColor(38);
    h_mc_tot->SetFillColor(29);
    h_mc_tot->SetLineColor(29);

    TCanvas* c1 = new TCanvas("c1","",1200,1000);
	c1->cd();
    TPad* upperpad = UpperPad();
    upperpad->Draw();
    upperpad->cd();

    h_mc_tot->Draw("hist");
    h_mc_sig->Draw("hist same");
    h_mc_bkg->Draw("hist same");
    h_fit_sig->Draw("p same");
    h_fit_bkg->Draw("p same");

    TLegend* leg = new TLegend(0.20, 0.70, 0.89, 0.89);
    leg->AddEntry(h_mc_sig, "Signal truth", "l");
    leg->AddEntry(h_mc_bkg, "Background truth", "l");
    leg->AddEntry(h_fit_sig, "Signal fitted", "p");
    leg->AddEntry(h_fit_bkg, "Background fitted", "p");
    leg->AddEntry(h_mc_tot, "Overall Candidates", "f");
    leg->SetNColumns(2);
    leg->Draw();
    leg->SetBorderSize(0);

    TPad* lowerpad = LowerPad();
    c1->Update();
    c1->cd();
    lowerpad->Draw();
    lowerpad->cd();
    

    TH1* ratiosig = ratiohist( h_fit_sig, h_mc_sig, "#frac{Fit}{Truth}" );
    TH1* ratiobkg = ratiohist( h_fit_bkg, h_mc_bkg, "#frac{Fit}{Truth}" );
    //TH1* ratiosig = devhist( h_fit_sig, h_mc_sig, "#frac{|Fit-Truth|}{FitError}");
    //TH1* ratiobkg = devhist( h_fit_bkg, h_mc_bkg, "#frac{|Fit-Truth|}{FitError}");
    ratiosig->Draw("p");
    ratiobkg->Draw("p same");

    c1->Update();

    c1->SaveAs( Form("plots_fakesample%d/h_truthComp_%sPho_%sJet.pdf",
                fakeid,
                isendcappho?"barrel":"endcap",
                isendcapjet?"barrel":"endcap") );
    delete c1;
}

/*
 * Procedure :
 * 1. load fake yields from dat file
 * 2. access data sideband in each binning
 * 3. reweight distribution of datasideband by loaded dat file
 * 4. Integral all binning of datasideband.
 * 5. Ouptut file : integrated distribution and separated distribution.
 */
void printhistinfo(TH1* oldhist, TH1* newhist = nullptr)
{
    int nbinO,nbinN;
    float LedgeO,LedgeN;
    float RedgeO,RedgeN;
    nbinO = nbinN = 0;
    LedgeO = LedgeN = RedgeO = RedgeN = 0.;
    if ( newhist )
    nbinN = newhist->GetNbinsX();
    nbinO = oldhist->GetNbinsX();
    if ( newhist )
    LedgeN = newhist->GetBinLowEdge(1);
    LedgeO = oldhist->GetBinLowEdge(1);
    if ( newhist )
    RedgeN = newhist->GetBinLowEdge(nbinN);
    RedgeO = oldhist->GetBinLowEdge(nbinO);
    if ( nbinO != nbinN ) printf ("-- check -- nbin = ( %d, %d )\n", nbinO, nbinN );
    if ( LedgeO != LedgeN ) printf ("--- chedk --- left edge = ( %.2f, %.2f )\n", LedgeO, LedgeN );
    if ( RedgeO != RedgeN ) printf ("--- chedk --- right edge = ( %.2f, %.2f )\n", RedgeO, RedgeN );
}
struct DATTree
{
    DATTree( const char* datfile ) :
        _tree( new TTree() )
    {
        _tree->ReadFile(datfile);

        if (!_tree->FindBranch("bkg") ) throw std::runtime_error("input dat file is not fake yield. Please check input dat file\n");
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

struct VARList
{
    enum vars
    {
        deepCSVTags_b,
        deepCSVTags_bb,
        deepCSVTags_c,
        deepCSVTags_udsg,
        deepFlavourTags_b,
        deepFlavourTags_c,
        deepFlavourTags_g,
        deepFlavourTags_lepb,
        deepFlavourTags_bb,
        deepFlavourTags_uds,
        deepCSVDiscriminatorTags_BvsAll,
        deepCSVDiscriminatorTags_CvsB,
        deepCSVDiscriminatorTags_CvsL,
        subVtxMass,
        totvars
    };
    std::vector<const char*> histnames;

    VARList( int etamax_ ) : histnames(totvars), bins(etamax_)
    {
        histnames[deepCSVTags_b]                      = "deepCSVTags_b";                   
        histnames[deepCSVTags_bb]                     = "deepCSVTags_bb";
        histnames[deepCSVTags_c]                      = "deepCSVTags_c";
        histnames[deepCSVTags_udsg]                   = "deepCSVTags_udsg";
        histnames[deepFlavourTags_b]                  = "deepFlavourTags_b";
        histnames[deepFlavourTags_c]                  = "deepFlavourTags_c";
        histnames[deepFlavourTags_g]                  = "deepFlavourTags_g";
        histnames[deepFlavourTags_lepb]               = "deepFlavourTags_lepb";
        histnames[deepFlavourTags_bb]                 = "deepFlavourTags_bb";
        histnames[deepFlavourTags_uds]                = "deepFlavourTags_uds";
        histnames[deepCSVDiscriminatorTags_BvsAll]    = "deepCSVDiscriminatorTags_BvsAll";
        histnames[deepCSVDiscriminatorTags_CvsB]      = "deepCSVDiscriminatorTags_CvsB";
        histnames[deepCSVDiscriminatorTags_CvsL]      = "deepCSVDiscriminatorTags_CvsL";
        histnames[subVtxMass]                         = "subVtxMass";
    }
    struct BinHistNaming
    {
        int phopt, phoeta, jeteta;
        int _jetmax, _etamax;
        void SetEta(int phoeta_) { phoeta = phoeta_; }
        void SetPt(int phopt_ ) { phopt = phopt_; }
        void SetJet(int jeteta_ ) { jeteta = jeteta_; }
        BinHistNaming(int etamax_) : _etamax(etamax_){ }
        int Size() { return totvars * _etamax; }
        int HistIdx( int varidx ) { return varidx + totvars * phoeta; }
    } bins;
    TString GetNameFromTemplate( int varnum, const char* name_template )
    {
        TString output;
        output.Form( name_template, histnames[varnum], bins.phoeta, bins.jeteta, bins.phopt );
        return output;
    }

    TString data_sideband( int varnum )
    { return GetNameFromTemplate( varnum, "fitVars/data_%s_%d_%d_%d_px2" ); }
    TString data_signalregion( int varnum )
    { return GetNameFromTemplate( varnum, "fitVars/data_%s_%d_%d_%d_px1" ); }
    TString qcd_sideband( int varnum )
    { return GetNameFromTemplate( varnum, "fitVars/qcd_%s_%d_%d_%d_px2" ); }
    TString MC_signalregion( int varnum )
    { return GetNameFromTemplate( varnum, "fitVars/gjet_%s_%d_%d_%d_px1" ); }
};
void ScaleHist( TH1* hist, float Nentry )
{
    float histentry = 0;
    for ( int ibin = hist->GetNbinsX(); ibin > 0; --ibin )
        histentry += hist->GetBinContent(ibin);
    if ( histentry == 0 )
    { std::cerr << "ScaleHist() : [Info] hist contains 0 event. {" << hist->GetName() << "}\n"; return; }
    hist->Scale( Nentry/histentry );
}
    
void ReNames( TH1* hist )
{
    std::string origname( hist->GetName() );
    std::string newname;
    newname.assign(origname, 0, origname.size() - 6);
    hist->SetName( newname.c_str() );
}

std::vector<TH1*> GetFakeTemplates( TFile* fdata, const char* datfile )
{
    DATTree datcontent( datfile );
    VARList histvars( datcontent.MaxBin_EtaBin() );
    TTree* t_datcontent = datcontent.GetTree();

    std::vector<TH1*> outputs(histvars.bins.Size(), nullptr);

    int binInfoIdx = 0;
    int binInfoNdx = t_datcontent->GetEntries();
    while ( binInfoIdx != binInfoNdx )
    {
        t_datcontent->GetEntry(binInfoIdx++);
        histvars.bins.SetPt( datcontent.ptbin );
        histvars.bins.SetEta( datcontent.etabin );
        histvars.bins.SetJet( datcontent.jetbin );

        // for ptbin > 19, use 19 to add statistics.
        if ( datcontent.ptbin > 19 ) histvars.bins.SetPt( 19 );

        TH1* loadhist;

        // change to use step3 result. Change loading naming.
        for ( int ivar = 0; ivar < VARList::totvars; ++ivar )
        {
            int histidx = histvars.bins.HistIdx(ivar);
            loadhist = (TH1*) fdata->Get( histvars.data_sideband(ivar) );

            ScaleHist( loadhist, datcontent.fityield );
            if (!outputs[histidx] ) outputs[histidx] = (TH1*)loadhist->Clone();
            else                   outputs[histidx]->Add(loadhist);
        }
    }
    for ( TH1* hist : outputs ) ReNames(hist);


    return outputs;
}

void FakeEstimation()
{
    TFile* fin = TFile::Open("../step3.DrawIsoBDT/storeroot/isovsbdt_template.root");

    std::vector<TH1*> barrel = GetFakeTemplates(fin, "../step4.DrawYield/data_bkg_barrelJet.dat");
    std::vector<TH1*> endcap = GetFakeTemplates(fin, "../step4.DrawYield/data_bkg_endcapJet.dat");
    //std::vector<TH1*> allpho = GetFakeTemplates(fin, "../step4.DrawYield/data_bkg_inclusivepho.dat"); // need to be refined

    TFile* fout = new TFile("output.root", "recreate");
    fout->cd();
    for ( auto hist : barrel ) hist->Write();
    for ( auto hist : endcap ) hist->Write();
    fout->Close();
}

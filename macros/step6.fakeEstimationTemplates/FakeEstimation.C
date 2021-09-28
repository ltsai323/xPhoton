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

        _ptmax  = _tree->GetMaximum("ptbin" );
        _etamax = _tree->GetMaximum("EBEE"  );
        _jetmax = _tree->GetMaximum("jetbin");
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

    VARList() : histnames(totvars)
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
        int phopt, phoeta, jeteta; //, isbkg;
        //const char* nameformat;
        void SetEta(int phoeta_) { phoeta = phoeta_; }
        void SetPt(int phopt_ ) { phopt = phopt_; }
        void SetJet(int jeteta_ ) { jeteta = jeteta_; }
        //void SetIsBkg(int isbkg_ ) { isbkg = isbkg_; }
        //BinHistNaming(const char* n_) : nameformat(n_) { isbkg=-1; }
        BinHistNaming() { }
        /*
        TString BinningName( const char* formatedStr )
        {
            TString output;
            if ( isbkg < 0 )
                output.Form( formatedStr, phoeta, jeteta, phopt );
            else
                output.Form( formatedStr, phoeta, jeteta, phopt, isbkg );
            return output;
        }
        */

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
    

std::vector<TH1*> GetFakeTemplates( TFile* fdata, const char* datfile )
{
    DATTree datcontent( datfile );
    VARList histvars;
    TTree* t_datcontent = datcontent.GetTree();

    std::vector<TH1*> outputs(VARList::totvars, nullptr);

    int binInfoIdx = 0;
    int binInfoNdx = t_datcontent->GetEntries();
    while ( binInfoIdx != binInfoNdx )
    {
        t_datcontent->GetEntry(binInfoIdx++);
        histvars.bins.SetPt( datcontent.ptbin );
        histvars.bins.SetEta( datcontent.etabin );
        histvars.bins.SetJet( datcontent.jetbin );
        
        TH1* loadhist;

        // change to use step3 result. Change loading naming.
        for ( int varidx = 0; varidx < VARList::totvars; ++varidx )
        {
            loadhist = (TH1*) fdata->Get( histvars.data_sideband(varidx) );
            ScaleHist( loadhist, datcontent.fityield );
            if (!outputs[varidx] ) outputs[varidx] = (TH1*)loadhist->Clone();
            else                   outputs[varidx]->Add(loadhist);
                
        }
    }

    return outputs;
}


int main()
{
    TFile* fdata = TFile::Open("../step2.makehistos/storeroot/makehisto_data.root");
    TFile* f_sig = TFile::Open("../step2.makehistos/storeroot/makehisto_sig_madgraph.root");
    TFile* f_bkg = TFile::Open("../step2.makehistos/storeroot/makehisto_QCD_madgraph.root");

    VARList histvars;
    histvars.bins.SetEta(1);

    //std::cout << ( (TH1*)fdata->Get( histvars.HistName(VARList::subVtxMass, 15, 0, 0, 0) ) ) ->GetMean() << std::endl;

    //DATTree fakePho_barrelJet("../step4.DrawYield/data_bkg_barrelJet.dat");
    //DATTree fakePho_endcapJet("../step4.DrawYield/data_bkg_endcapJet.dat");
    //DATTree fakePho_jetVeto  ("../step4.DrawYield/data_bkg_inclusivepho.dat");

    //DATTree signPho_barrelJet("../step4.DrawYield/data_yield_barrelJet.dat");
    //DATTree signPho_endcapJet("../step4.DrawYield/data_yield_endcapJet.dat");
    //DATTree signPho_jetVeto  ("../step4.DrawYield/data_yield_inclusivepho.dat");


    return 0;
}

void FakeEstimation()
{
    TFile* fin = TFile::Open("../step3.DrawIsoBDT/storeroot/isovsbdt_template.root");
    /*
    TFile* fdata = TFile::Open("../step2.makehistos/storeroot/makehisto_data.root");
    TFile* f_sig = TFile::Open("../step2.makehistos/storeroot/makehisto_sig_madgraph.root");
    TFile* f_bkg = TFile::Open("../step2.makehistos/storeroot/makehisto_QCD_madgraph.root");
    */
    std::vector<TH1*> hi = GetFakeTemplates(fin, "../step4.DrawYield/data_bkg_barrelJet.dat");
    std::vector<TH1*> hj = GetFakeTemplates(fin, "../step4.DrawYield/data_yield_barrelJet.dat");
}

#define NUMBIN_PHOETA 2
#define NUMBIN_JETETA 3
#define NUMBIN_PHOPT 22

struct BinFile : public TFile
{
    SetBin(int pETA, int jETA, int pPt) { pEta = pETA; jEta = jETA; pPt = pPT; }
    TObject* get(const char* histTEMPLATE) { return this->Get( Form(histTEMPLATE,pEta,jEta,pPt) ); }
    TH1* GetHist( const char* newNAME, const std::vector<const char*>& histTEMPLATE)
    {
        if ( histTEMPLATE.size() == 0 )
        { std::cerr << "GetHist() : input histogram name template is empty\n"; exit(); }
        TH1* trg = (TH1*) get(histTEMPLATE[0]);
        TH1* obj = new TH1F( newNAME, "", trg->GetNbinsX(), trg->GetXaxis()->GetXbins()->GetArray() );
        for ( const char* hTemplate : histTEMPLATE )
            obj->Add( ((TH1*) get(hTemplate)) );
        return obj;
    }
    TH2* GetHist2D( const char* newNAME, const std::vector<const char*>& histTEMPLATE)
    {
        if ( histTEMPLATE.size() == 0 )
        { std::cerr << "GetHist() : input histogram name template is empty\n"; exit(); }
        TH2* trg = (TH2*) get(histTEMPLATE[0]);
        TH2* obj = new TH2F( newNAME, "", trg->GetNbinsX(), trg->GetXaxis()->GetXbins()->GetArray(),
                                          trg->GetNbinsY(), trg->GetYaxis()->GetXbins()->GetArray() );
        for ( const char* hTemplate : histTEMPLATE )
            obj->Add( ((TH2*) get(hTemplate)) );
        return obj;
    }
    int pEta, jEta, pPt;
};

void HistTranslateToHiggsCombine()
{
    const char* ifile_exp = "";
    const char* ifile_sig = "";
    const char* ifile_QCD = "";

    auto bfile_exp = BinFile::Open(ifile_exp);
    auto bfile_sig = BinFile::Open(ifile_sig);
    auto bfile_QCD = BinFile::Open(ifile_QCD);

    for ( int idxphoeta = 0; idxphoeta < NUMBIN_PHOETA; ++idxphoeta )
        for ( int idxjeteta = 0; idxjeteta < NUMBIN_JETETA; ++idxjeteta )
            for ( int idxphopt = 0; idxphopt < NUMBIN_PHOPT; ++idxphopt )
    {
        auto newfile = new TFile( Form("hists_%d_%d_%d.root",idxphoeta,idxjeteta,idxphopt), "RECREATE" );
        newfile->cd();
        bfile_exp->SetBin(idxphoeta,idxjeteta,idxphopt);
        bfile_sig->SetBin(idxphoeta,idxjeteta,idxphopt);
        bfile_QCD->SetBin(idxphoeta,idxjeteta,idxphopt);

        // L, C , B, FAKE
        // b+bb, cvsl, cvsb, svxmass
        TH1* DATA_tag0 = bfile_exp->GetHist( "DATA_tag0", {
                "btagDeepCSV/btagDeepCSV.0_0_0__%d_%d_%d__0_0",
                "btagDeepCSV/btagDeepCSV.0_0_0__%d_%d_%d__0_1"
                } );
        TH1* SIGN_tag0_L = bfile_QCD->GetHist( "MC_tag0_L", {
                "btagDeepCSV/btagDeepCSV.0_0_0__%d_%d_%d__2_0",
                "btagDeepCSV/btagDeepCSV.0_0_0__%d_%d_%d__2_1"
                } );
        TH1* SIGN_tag0_C = bfile_QCD->GetHist( "MC_tag0_C", {
                "btagDeepCSV/btagDeepCSV.1_0_0__%d_%d_%d__2_0",
                "btagDeepCSV/btagDeepCSV.1_0_0__%d_%d_%d__2_1"
                } );
        TH1* SIGN_tag0_B = bfile_QCD->GetHist( "MC_tag0_B", {
                "btagDeepCSV/btagDeepCSV.2_0_0__%d_%d_%d__2_0",
                "btagDeepCSV/btagDeepCSV.2_0_0__%d_%d_%d__2_1"
                } );
        TH1* SIGN_tag0_F = bfile_exp->GetHist( "MC_tag0_FAKE", {
                "btagDeepCSV/btagDeepCSV.0_0_0__%d_%d_%d__1_0",
                "btagDeepCSV/btagDeepCSV.0_0_0__%d_%d_%d__1_1"
                } );
    }
    newfile->Close();
}

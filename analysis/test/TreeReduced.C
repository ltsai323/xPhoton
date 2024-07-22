void CorrectedChIso();
float EffectiveArea_ChIso(float eta)
{
    float abseta = fabs(eta);
    if      ( abseta < 1.0   ) return 0.0112;
    else if ( abseta < 1.479 ) return 0.0108;
    else if ( abseta < 2.0   ) return 0.0106;
    else if ( abseta < 2.2   ) return 0.01002;
    else if ( abseta < 2.3   ) return 0.0098;
    else if ( abseta < 2.4   ) return 0.0089;
    else                       return 0.0087;
    return 0;
}
float RhoCorrected( float iso, float rho, float effectivearea )
{
    float cIso = iso - rho * effectivearea;
    return cIso > 0. ? cIso : 0.;
}

TTree* skim( TTree* tree )
{

    // add selection variables here
    float chiso, rho, eta;
    tree->SetBranchAddress("chIsoRaw", &chiso);
    tree->SetBranchAddress("rho", &rho);
    tree->SetBranchAddress("recoEta", &eta);
    
    // please not to delete this line
    tree->SetBranchStatus("*",1);


    TTree *newtree = tree->CloneTree(0);
    float chIsoCalb;
    newtree->Branch("chIsoCalb", &chIsoCalb, "chIsoCalb/F");

    for (Long64_t ievt = 0; ievt < tree->GetEntries(); ++ievt )
    {
        tree->GetEntry(ievt);
        chIsoCalb = RhoCorrected( chiso, rho, EffectiveArea_ChIso(eta) );

        newtree->Fill();
    }

    return newtree;
}

void TreeReduced( const char* loadedFile )
{
    TFile* f_load = TFile::Open(loadedFile);
    TTree* t_load = (TTree*) f_load->Get("t");

    TFile* f_out = new TFile("reducedTree.root", "recreate");
    TTree* t_out = skim(t_load);
    printf( "Reduced tree contains %lld events from %lld events.\n", t_out->GetEntries(), t_load->GetEntries() );
    f_out->cd();
    t_out->Write();
    f_out->Close();
}

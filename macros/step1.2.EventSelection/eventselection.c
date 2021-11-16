TTree* skim( TTree* tree )
{
    bool IsMC = t_load->GetBranch("mcPt") ? kTRUE : kFALSE;

    // add selection variables here
    int isMatched;
    int jetID;
    int jetPUIDbit;
    int jetHadFlvr;
    int phoFiredTrgs;
    Bool_t isData;
    float jetPt;
    float jetEta;
    float recoPt;
    float recoEta;
    float mva;
    float jetDeepCSVTags_b;
    float jetDeepCSVTags_bb;
    float jetDeepCSVTags_c;
    float jetDeepCSVTags_udsg;
    float jetDeepCSVDiscriminatorTags_BvsAll;
    float jetDeepCSVDiscriminatorTags_CvsB;
    float jetDeepCSVDiscriminatorTags_CvsL;
    float jetSubVtxMass;
    float chIsoRaw;
    float mcweight;
    float jetSF_DeepCSV_central;
    float jetSF_DeepCSV_down_cferr1;
    float jetSF_DeepCSV_down_cferr2;
    float jetSF_DeepCSV_down_hf;
    float jetSF_DeepCSV_down_lf;
    float jetSF_DeepCSV_up_cferr1;
    float jetSF_DeepCSV_up_cferr2;
    float jetSF_DeepCSV_up_hf;
    float jetSF_DeepCSV_up_lf;
    
    tree->SetBranchAddress("isMatched", &isMatched);
    tree->SetBranchAddress("jetID", &jetID);
    tree->SetBranchAddress("jetPUIDbit", &jetPUIDbit);
    tree->SetBranchAddress("jetHadFlvr", &jetHadFlvr);
    tree->SetBranchAddress("phoFiredTrgs", &phoFiredTrgs);
    tree->SetBranchAddress("isData", &isData);
    tree->SetBranchAddress("jetPt", &jetPt);
    tree->SetBranchAddress("jetEta", &jetEta);
    tree->SetBranchAddress("recoPt", &recoPt);
    tree->SetBranchAddress("recoEta", &recoEta);
    tree->SetBranchAddress("mva", &mva);
    tree->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b);
    tree->SetBranchAddress("jetDeepCSVTags_bb", &jetDeepCSVTags_bb);
    tree->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c);
    tree->SetBranchAddress("jetDeepCSVTags_udsg", &jetDeepCSVTags_udsg);
    tree->SetBranchAddress("jetDeepCSVDiscriminatorTags_BvsAll", &jetDeepCSVDiscriminatorTags_BvsAll);
    tree->SetBranchAddress("jetDeepCSVDiscriminatorTags_CvsB", &jetDeepCSVDiscriminatorTags_CvsB);
    tree->SetBranchAddress("jetDeepCSVDiscriminatorTags_CvsL", &jetDeepCSVDiscriminatorTags_CvsL);
    tree->SetBranchAddress("jetSubVtxMass", &jetSubVtxMass);
    tree->SetBranchAddress("chIsoRaw", &chIsoRaw);
    tree->SetBranchAddress("mcweight", &mcweight);
    tree->SetBranchAddress("jetSF.DeepCSV.central", &jetSF_DeepCSV_central);
    tree->SetBranchAddress("jetSF.DeepCSV.down_cferr1", &jetSF_DeepCSV_down_cferr1);
    tree->SetBranchAddress("jetSF.DeepCSV.down_cferr2", &jetSF_DeepCSV_down_cferr2);
    tree->SetBranchAddress("jetSF.DeepCSV.down_hf", &jetSF_DeepCSV_down_hf);
    tree->SetBranchAddress("jetSF.DeepCSV.down_lf", &jetSF_DeepCSV_down_lf);
    tree->SetBranchAddress("jetSF.DeepCSV.up_cferr1", &jetSF_DeepCSV_up_cferr1);
    tree->SetBranchAddress("jetSF.DeepCSV.up_cferr2", &jetSF_DeepCSV_up_cferr2);
    tree->SetBranchAddress("jetSF.DeepCSV.up_hf", &jetSF_DeepCSV_up_hf);
    tree->SetBranchAddress("jetSF.DeepCSV.up_lf", &jetSF_DeepCSV_up_lf);
    
    // please not to delete this line
    tree->SetBranchStatus("*",1);

    TTree *newtree = tree->CloneTree(0);

    for (Long64_t ievt = 0; ievt < tree->GetEntries(); ++ievt )
    {
        tree->GetEntry(ievt);

        // put your selection here
        if( jetPt<30. ) continue;
	    if( fabs(jetEta)>2.5 ) continue;
	    if( jetDeepCSVTags_c<-0.99 ) continue;
	    if( jetID != 1 ) continue;
	    if( jetPUIDbit != 7 ) continue;

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

TTree* skim( TTree* tree )
{
    bool IsMC = t_load->GetBranch("mcPt") ? kTRUE : kFALSE;

    // add selection variables here
    int isMatched;
    Long64_t phoFiredTrgs;
    if ( IsMC )
    {
        tree->SetBranchAddress("isMatched", &isMatched);
    }
    
    // please not to delete this line
    tree->SetBranchStatus("*",1);

    TTree *newtree = tree->CloneTree(0);

    for (Long64_t ievt = 0; ievt < tree->GetEntries(); ++ievt )
    {
        tree->GetEntry(ievt);

        // put your selection here
        if ( isMatched != 1 ) continue;

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

TTree* skim( TTree* tree )
{
    bool IsMC = tree->GetBranch("mcPt") ? kTRUE : kFALSE;

    // selection variables
    int isMatched;
    int jetID;
    int jetPUIDbit;
    int phoFiredTrgs;
    Bool_t isData;
    int isQCD;
    float jetPt;
    float jetEta;
    float jetDeepCSVTags_c;
    
    tree->SetBranchAddress("isMatched", &isMatched);
    tree->SetBranchAddress("jetID", &jetID);
    tree->SetBranchAddress("jetPUIDbit", &jetPUIDbit);
    tree->SetBranchAddress("phoFiredTrgs", &phoFiredTrgs);
    tree->SetBranchAddress("isData", &isData);
    tree->SetBranchAddress("isQCD", &isQCD);
    tree->SetBranchAddress("jetPt", &jetPt);
    tree->SetBranchAddress("jetEta", &jetEta);
    tree->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c);
    
    tree->SetBranchStatus("*",1);

    TTree *newtree = tree->CloneTree(0);
    Long64_t nentries = tree->GetEntries();
    tree->GetEntry(0);
    if (isData){ // Data
      for (Long64_t ievt = 0; ievt < nentries; ++ievt )
	{
	  if (ievt % 100000 == 0){
	    fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", ievt+1, nentries, (ievt+1)*100./nentries);
	  }

	  tree->GetEntry(ievt);

	  // selections
	  if( jetPt<30. ) continue;
	  if( fabs(jetEta)>2.5 ) continue;
	  if( jetDeepCSVTags_c<-0.99 ) continue;

	  newtree->Fill();
	}
    }else{ //MC or QCD
      for (Long64_t ievt = 0; ievt < nentries; ++ievt )
	{
	  if (ievt % 100000 == 0){
	    fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", ievt+1, nentries, (ievt+1)*100./nentries);
	  }

	  tree->GetEntry(ievt);

	  // selections
	  if( jetPt<30. ) continue;
	  if( fabs(jetEta)>2.5 ) continue;
	  if( jetDeepCSVTags_c<-0.99 ) continue;
	  if( jetID != 1 ) continue;
	  if( jetPUIDbit != 7 ) continue;

	  newtree->Fill();
	}
    }

    return newtree;
}

void TreeReduced( const char* loadedFile )
{
    TFile* f_load = TFile::Open(loadedFile);
    TTree* t_load = (TTree*) f_load->Get("t");
    TFile* f_out;

    const char file_data[] = "/wk_cms/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root";
    const char file_mc[] = "/wk_cms/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root";
    const char file_qcd[] = "/wk_cms/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root";

    if( strcmp(loadedFile,file_data) == 0 )
      f_out = new TFile("reduced_data.root", "recreate");
    else if( strcmp(loadedFile,file_mc) == 0)
      f_out = new TFile("reduced_mc.root", "recreate");
    else if( strcmp(loadedFile,file_qcd) == 0 )
      f_out = new TFile("reduced_qcd.root", "recreate");
    else
      cout << "[ERROR] Please check the name of the file..." << endl;

    TTree* t_out = skim(t_load);
    printf( "Reduced tree contains %lld events from %lld events.\n", t_out->GetEntries(), t_load->GetEntries() );
    f_out->cd();
    t_out->Write();
    f_out->Close();
}

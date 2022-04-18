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

void TreeReduced( const char* loadedFile, const char* outputlabel )
{
    TFile* f_load = TFile::Open(loadedFile);
    TTree* t_load = (TTree*) f_load->Get("t");
    TFile* f_out = new TFile( Form("reduced_%s.root", outputlabel), "RECREATE");

    TTree* t_out = skim(t_load);
    printf( "Reduced tree contains %lld events from %lld events.\n", t_out->GetEntries(), t_load->GetEntries() );
    f_out->cd();
    t_out->Write();
    f_out->Close();
}
        // if (Cut(ientry) < 0) continue;
        if(TMath::Abs(recoEta)>1.4442 && TMath::Abs(recoEta)<1.566) continue;
        if(TMath::Abs(recoEta)>2.5) continue;

        if(MET/photonpt > 0.7) continue;
        if(eleVeto==1 && bdt_score>0.35 && chIsoRaw<2.){
            if(ebee==1 && HoverE > 0.01) continue;
            /*  asdf Modified needed !!!! asdf */
        std::string dataera = "UL2018";
        if ( dataera == "2016ReReco" )
            if(HLTOPTION==1 && (((phoFiredTrgs>>8)&1)==0) ) continue; //asdf need to add ERA!
        if ( dataera == "UL2018" )
            if(HLTOPTION==1 && (((phoFiredTrgs>>8)&1)==0) ) continue; //asdf need to add ERA!
        // asdf selections
        if ( TMath::Abs(recoEta)<1.5 && sieieFull5x5 > 0.015 ) continue;
        if ( TMath::Abs(recoEta)>1.5 && sieieFull5x5 > 0.045 ) continue;
	//if ( mcweight>3000. ) continue;
	if ( extracut == 1 ){
	  if ( jetSubVtxMass == 0 ) continue;
	}else if ( extracut == 2 ){
	  if ( jetDeepCSVDiscriminatorTags_CvsL < 0.155) continue;
	}

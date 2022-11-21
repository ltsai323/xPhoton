{
    TFile* inPUT = TFile::Open("Madgraph_lheJetMatch_maxPUhat_QCD_HT50to100.root");
    TTree* input = (TTree*) inPUT->Get("nt");
    input->SetBranchStatus("*", 1);

    TFile* ouPUT = new TFile("check.root", "RECREATE");
    TTree* ouput = (TTree*) input->CloneTree(0);

    int check = 1;
    ouput->Branch("check", &check, "check/I");
    for ( Long64_t ievt = 0; ievt < input->GetEntries(); ++ievt )
    {
        input->GetEntry(ievt);
        ++check;
        ouput->Fill();
    }
    ouPUT->cd();
    ouput->Write();
    ouPUT->Close();
}




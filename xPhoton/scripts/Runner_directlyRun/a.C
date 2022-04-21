{
    TFile* f = TFile::Open("output_job_PhotonHFJet_0.root");
    TTree* t = (TTree*) f->Get("t");

    TH1F* F = new TH1F("hh", "", 16, 0., 16.);

    Long64_t trg = 0;
    t->SetBranchAddress("mu1.trg", &trg);

    int ievt = 0;
    int nevt = t->GetEntries();
    while ( ievt != nevt )
    {
        t->GetEntry(ievt++);
        for ( int ibit = 0; ibit < 16; ++ibit )
            if ( (trg>>ibit)&1 ) F->Fill(ibit);

    }
    TCanvas* c1 = new TCanvas("c1", "", 1200,1000);
    F->Draw();
    c1->SaveAs("hi.png");
}

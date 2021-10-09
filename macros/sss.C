{
    TFile* f = TFile::Open("step3.DrawIsoBDT/storeroot/isovsbdt_template.root");

    TString histname;
    TH1* h = nullptr;
    //for ( int ebee = 0; ebee <= 1 ; ++ebee )
    //    for ( int jeteta = 0; jeteta <=1 ; ++jeteta )
            for ( int phopt = 0; phopt < 22; ++phopt )
    {
       //histname.Form("fitVars/h_deepCSVDiscriminatorTags_CvsB_1_1_%d_0", phopt);
       histname.Form("fitVars/data_deepCSVDiscriminatorTags_CvsB_1_1_%d_px1", phopt);
       TH1* tmphist = (TH1*) f->Get(histname);
       std::cout << tmphist->GetEntries() << std::endl;
       if ( h == nullptr ) h = tmphist;
       else                h -> Add(tmphist);
    }
    
    TFile* ftemp = TFile::Open("step6.fakeEstimationTemplates/output.root");
    TH1* htemp = (TH1*) ftemp->Get("data_deepCSVDiscriminatorTags_CvsB_1_1");
    htemp->SetLineColor(2);
    htemp->SetFillColor(2);

    TCanvas* c1 = new TCanvas("c1","", 1200,1000);
    h->Draw();
    htemp->Draw("same hist");
    c1->SaveAs("hi.png");
}

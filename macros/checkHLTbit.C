void checkHLTbit()
{
    TFile* fOrig = TFile::Open("checkdata_orig.root");
    TH1* hOrigUp_EB = (TH1*) fOrig->Get("EB_HLTpass");
    TH1* hOrigDn_EB = (TH1*) fOrig->Get("EB_HLT_all");
    TH1* hOrigUp_EE = (TH1*) fOrig->Get("EE_HLTpass");
    TH1* hOrigDn_EE = (TH1*) fOrig->Get("EE_HLT_all");

    TFile* fver2 = TFile::Open("checkdata_ver2.root");
    TH1* hver2Up_EB = (TH1*) fver2->Get("EB_HLTpass");
    TH1* hver2Dn_EB = (TH1*) fver2->Get("EB_HLT_all");
    TH1* hver2Up_EE = (TH1*) fver2->Get("EE_HLTpass");
    TH1* hver2Dn_EE = (TH1*) fver2->Get("EE_HLT_all");

    TH1* hEBRatio = (TH1*) hOrigUp_EB->Clone();
    hEBRatio->SetName("EB");
    hEBRatio->Divide(hver2Up_EB);

    TH1* hEERatio = (TH1*) hOrigUp_EE->Clone();
    hEERatio->SetName("EE");
    hEERatio->Divide(hver2Up_EE);

    TCanvas* c1 = new TCanvas("c","", 1000,500);
    c1->Divide(2,1);
    c1->cd(1); hEBRatio->Draw();
    c1->cd(2); hEERatio->Draw();
    c1->SaveAs("hi.png");


}

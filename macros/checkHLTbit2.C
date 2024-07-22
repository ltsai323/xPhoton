void checkHLTbit2()
{
    TFile* fOrig = TFile::Open("checkdata_orig.root");
    //TFile* fOrig = TFile::Open("checkdata_ver2.old.root");
    TH1* hOrigUp_EB = (TH1*) fOrig->Get("EB_HLTpass");
    TH1* hOrigDn_EB = (TH1*) fOrig->Get("EB_HLT_all");
    TH1* hOrigUp_EE = (TH1*) fOrig->Get("EE_HLTpass");
    TH1* hOrigDn_EE = (TH1*) fOrig->Get("EE_HLT_all");

    TFile* fver2 = TFile::Open("checkdata_ver3.root");
    //TFile* fver2 = TFile::Open("checkdata_ver2.root");
    TH1* hver2Up_EB = (TH1*) fver2->Get("EB_HLTpass");
    TH1* hver2Dn_EB = (TH1*) fver2->Get("EB_HLT_all");
    TH1* hver2Up_EE = (TH1*) fver2->Get("EE_HLTpass");
    TH1* hver2Dn_EE = (TH1*) fver2->Get("EE_HLT_all");

    hOrigUp_EB->Divide(hOrigDn_EB);
    hOrigUp_EE->Divide(hOrigDn_EE);
    hver2Up_EB->Divide(hver2Dn_EB);
    hver2Up_EE->Divide(hver2Dn_EE);

    hOrigUp_EB->SetLineColor( 2);
    hOrigUp_EB->SetLineWidth( 4);
    hOrigUp_EB->SetStats(false);
    hOrigUp_EB->GetYaxis()->SetTitle("Passed HLT / all photon");
    hOrigUp_EB->GetXaxis()->SetTitle("photon pt bin");
    hOrigUp_EB->SetTitle("HLT passing efficiency in each pt bin");

    hOrigUp_EE->SetLineColor( 2);
    hOrigUp_EE->SetLineWidth( 4);
    hOrigUp_EE->SetStats(false);
    hOrigUp_EE->GetYaxis()->SetTitle("Passed HLT / all photon");
    hOrigUp_EE->GetXaxis()->SetTitle("photon pt bin");
    hOrigUp_EE->SetTitle("HLT passing efficiency in each pt bin");

    hver2Up_EB->SetLineColor(30);
    hver2Up_EB->SetLineWidth( 3);
    hver2Up_EB->SetStats(false);
    hver2Up_EB->GetYaxis()->SetTitle("Passed HLT / all photon");
    hver2Up_EB->GetXaxis()->SetTitle("photon pt bin");
    hver2Up_EB->SetTitle("HLT passing efficiency in each pt bin");

    hver2Up_EE->SetLineColor(30);
    hver2Up_EE->SetLineWidth( 3);
    hver2Up_EE->SetStats(false);
    hver2Up_EE->GetYaxis()->SetTitle("Passed HLT / all photon");
    hver2Up_EE->GetXaxis()->SetTitle("photon pt bin");
    hver2Up_EE->SetTitle("HLT passing efficiency in each pt bin");

    TCanvas* c1 = new TCanvas("c","", 1000,500);
    c1->Divide(2,1);
    c1->cd(1); hOrigUp_EB->Draw(); hver2Up_EB->Draw("same");
    c1->cd(2); hOrigUp_EE->Draw(); hver2Up_EE->Draw("same");
    c1->SaveAs("hi.png");


}

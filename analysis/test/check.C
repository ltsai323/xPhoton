{
    TFile* fin = TFile::Open("newfile.root");
    TH2* horig = (TH2*) fin->Get("horig");
    TH2* hcalb = (TH2*) fin->Get("hcalb");
    TH2* hcaSC = (TH2*) fin->Get("hcaSC");

    TProfile* porig = (TProfile*) horig->ProfileX();
    TProfile* pcalb = (TProfile*) hcalb->ProfileX();
    TProfile* pcaSC = (TProfile*) hcaSC->ProfileX();
    //porig->SetMarkerStyle(29);
    pcalb->SetMarkerColor(2);
    //pcalb->SetMarkerStyle(30);
    pcalb->SetLineColor(2);

    TCanvas* c1 = new TCanvas("c","", 1200,1000);
    c1->SetFillColor(4000);
    c1->SetFillStyle(4000);
    
    
    porig->Draw("P");
    pcalb->Draw("P SAME");

    TLegend* leg = new TLegend(0.2,0.2, 0.7,0.3);
    leg->AddEntry(porig, "Raw data", "p");
    leg->AddEntry(pcalb, "#rho calibrated", "p");
    leg->Draw();
}

    

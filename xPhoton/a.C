void a(const char* fname, const char* var)
{
    TFile* f = TFile::Open(fname);
    TTree* t = (TTree*) f->Get("t");

    // TCanvas* c1 = new TCanvas("c1", "", 1600, 400);
    // c1->Divide(4,1);
    // c1->cd(1);
    TCanvas* c1 = new TCanvas("CANV", "", 1600,1000);
    c1->SetFrameFillColor(4000);
    c1->SetFrameFillStyle(4000);
    c1->SetFillColor(4000);
    c1->SetFillStyle(4000);
    t->SetLineColor(2);t->SetLineWidth(3);
    t->Draw(Form("%s >> EBSig", var), "recoPt > 200 && fabs(recoEta)<1.5 && chIsoRaw<2");
    auto h = (TH1*) gROOT->FindObject("EBSig");
    h->SetTitle("");
    h->GetXaxis()->SetTitle("BDT score");
    h->Draw();

    t->SetLineColor(46);
    t->Draw(Form("%s >> EBBkg", var), "recoPt > 200 && fabs(recoEta)<1.5 && chIsoRaw>5", "SAME");
    t->SetLineColor(9); t->SetFillColor(9); t->SetFillStyle(3690);
    t->Draw(Form("%s >> EESig", var), "recoPt > 200 && fabs(recoEta)>1.5 && chIsoRaw<2", "SAME");
    t->SetLineColor(8); t->SetFillColor(8); t->SetFillStyle(3005);
    t->Draw(Form("%s >> EEBkg", var), "recoPt > 200 && fabs(recoEta)>1.5 && chIsoRaw>5", "SAME");

    TLegend* leg = new TLegend(0.25, 0.4, 0.5, 0.85);
    leg->SetBorderSize(0);
    leg->AddEntry( "EBSig", "Signal region in Barrel.", "l");
    leg->AddEntry( "EBBkg", "Datasideband  in Barrel", "l");
    leg->AddEntry( "EESig", "Signal region in Endcap", "lf");
    leg->AddEntry( "EEBkg", "Datasideband  in Endcap", "lf");
    leg->Draw();

    c1->SaveAs("UL18TrainingResult.pdf");
}

void a(const char* filename)
{
    TFile* f = TFile::Open(filename);
    TH1* h = (TH1*) f->Get("MuonHLTPassedBits");

    TCanvas* c1 = new TCanvas("c1","",1000,1000);
    c1->SetLogy();
    h->Draw();
    c1->SaveAs("hi.png");
}

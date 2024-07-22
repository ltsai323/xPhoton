
void BUG(const char* inf)
{ printf("%s\n",inf); }
TH1* Load(TFile* ifile, const char* name, int color, int fillstyle)
{
    BUG("01");
    auto h = (TH1*) ifile->Get(name);
    BUG("02");
    
    h->SetLineColor(color);
    h->SetFillColor(color);
    h->SetFillStyle(fillstyle);
    BUG("03");
    return h;
}

void check()
{
    BUG("-1");
    auto ifile = TFile::Open("test_makeComparisonHistWithoutFit/makehisto.root");
    BUG("00");
    TCanvas* canv;
    canv = new TCanvas("c1", "", 800,800);

    //BUG("000");
    //TH1* hdata = Load(ifile,"overall_binning/BDT_data_signalRegion", 1, 0);
    //TH1* hsign = Load(ifile,"overall_binning/BDT_gjet_signalRegion", 2, 1001);

    //hdata->Draw("AXIS");
    //hsign->Draw("HIST SAME");
    //hdata->Draw("EP SAME");
    //canv->SaveAs("hi.png");
}

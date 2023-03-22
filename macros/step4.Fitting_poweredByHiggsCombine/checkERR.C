void checkERR(int pEta, int jEta, int pPt)
{
    auto ifile = TFile::Open("makehist.root");
    auto hdata = (TH1*) ifile->Get(Form("bin_%d_%d_%d/BDT_data_signalRegion", pEta,jEta,pPt));
    auto hsig  = (TH1*) ifile->Get(Form("bin_%d_%d_%d/BDT_gjet_signalRegion_norm", pEta,jEta,pPt));
    auto hsigU = (TH1*) ifile->Get(Form("bin_%d_%d_%d/BDT_gjet_signalRegion_shapeUncUp_norm", pEta,jEta,pPt));
    auto hsigD = (TH1*) ifile->Get(Form("bin_%d_%d_%d/BDT_gjet_signalRegion_shapeUncDown_norm", pEta,jEta,pPt));
    
    auto canv = new TCanvas("c1", "", 600,600);
    hsig ->SetLineColor(2 ); hsig ->Draw("HIST");
    hsigU->SetLineColor(45); hsigU->Draw("HIST SAME");
    hsigD->SetLineColor(38); hsigD->Draw("HIST SAME");
    canv->SaveAs("hi.png");
    
    std::cout << "data entries : " << hdata->GetEntries() << std::endl;
}


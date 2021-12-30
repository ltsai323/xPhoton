#include "DrawYield.C"

void CheckFitter(int ebee=0, int jetbin=0)
{
    const char* EBEE = EtaName(ebee);
    int ebeebin = ebee>0 ? 1 : 0;

    std::vector<float> vec_ptcut = ptbin_ranges();
    float* ptcut = &vec_ptcut.front();

    //int nbin=vec_ptcut.size();
    int nbin=numPtBins();

    TH1F *h_yield = new TH1F("h_yield","",nbin, ptcut);
    TH1F *h_purity = new TH1F("h_purity","",nbin, ptcut);
    TH1F *h_purity_tight = new TH1F("h_purity_tight","",nbin, ptcut);

    TH1F *h_sig_yield = new TH1F("h_sig_yield","",nbin, ptcut);
    TH1F *h_sig_yield_tight = new TH1F("h_sig_yield_tight","",nbin, ptcut);
    TH1F *h_bkg_yield = new TH1F("h_bkg_yield","",nbin, ptcut);
    TH1F *h_bkg_yield_tight = new TH1F("h_bkg_yield_tight","",nbin, ptcut);


    double *fitted;
    float lumi = 35.9;

    char txt[100];
    std::cerr << "total bins : " << numPtBins() << std::endl;
    for(int ii=0; ii<numPtBins(); ii++){
        //perform fit for yield
        fitted=Ifit(ii, ebee, 0, jetbin); // 0 for toy MC
        if(fitted[0]>0.) {

            h_yield->SetBinContent(ii+1, fitted[0]/h_yield->GetBinWidth(ii+1));
            h_yield->SetBinError(ii+1, fitted[1]/h_yield->GetBinWidth(ii+1));

            float djet_eta=1.5*2.;
            if(jetbin==1) djet_eta = 0.9*2.;
            if(jetbin==2) djet_eta = 1;

            h_sig_yield->SetBinContent(ii+1, fitted[0]);
            h_bkg_yield->SetBinContent(ii+1, fitted[2]);

            h_sig_yield_tight->SetBinContent(ii+1, fitted[4]);
            h_bkg_yield_tight->SetBinContent(ii+1, fitted[6]);
        } // if fitted yield found
    } // end of photon bins

    TCanvas *c10 = new TCanvas("c10","",600,600);
    c10->Draw();
    gPad->SetLogy();
    h_yield->SetNdivisions(505,"XY");
    h_yield->SetXTitle("p_{T} (GeV)");
    h_yield->SetYTitle("Entries / GeV");
    h_yield->SetMarkerStyle(8);
    h_yield->GetXaxis()->SetRangeUser(150.,1000.);
    h_yield->Draw("pe");

    char pho_text[100];
    char jet_text[100];
    if(ebeebin==0) sprintf(pho_text,"|#eta_{#gamma}|<1.4442");
    else sprintf(pho_text,"1.566<|#eta_{#gamma}|<2.5");
    if(jetbin==0) sprintf(jet_text,"|#eta_{jet}|<1.5");
    else sprintf(jet_text,"1.5<|#eta_{jet}|<2.4");


    TLegend *tleg = new TLegend(0.4, 0.65, 0.85, 0.92);
    char text[50];
    sprintf(text,"CMS 13TeV, %.0f fb^{-1}",lumi);
    tleg->SetHeader(text);
    tleg->SetFillColor(0);
    tleg->SetShadowColor(0);
    tleg->SetBorderSize(0);  
    sprintf(text,"%s, %s",pho_text, jet_text);
    if(jetbin==2)   sprintf(text,"%s",pho_text);
    tleg->AddEntry(h_yield,text,"pl");
    tleg->Draw();
    c10->SaveAs("k.png");
}

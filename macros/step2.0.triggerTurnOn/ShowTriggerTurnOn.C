#define MAXBIT 8

TH1F* CalculateRatio(TH1* hUp, TH1* hDn, const char* histname)
{
    TH1F* ratiohist = (TH1F*) hUp->Clone();
    ratiohist->SetName(histname);
    for ( int ibin = ratiohist->GetNbinsX(); ibin != 0; --ibin )
    {
        double content_up = hUp->GetBinContent(ibin);
        double content_dn = hDn->GetBinContent(ibin);
        double err_up = hUp->GetBinError(ibin);
        double err_dn = hDn->GetBinError(ibin);
        
        if      ( content_dn < 1e-6 && content_up < 1e-6 )
        { ratiohist->SetBinContent(ibin, 0); ratiohist->SetBinError  (ibin, 0); }
        else if ( content_dn < 1e-6 && content_up > 1e-6 )
        {
            printf("--- warning, filling hist %s at binning %d reports a zero denominator\n",
                    histname, ibin);
            ratiohist->SetBinContent(ibin, 0);
            ratiohist->SetBinError  (ibin, 0);
        }
        else
        {
            ratiohist->SetBinContent( ibin, content_up / content_dn );
            double calcErr1 = err_up / content_dn;
            double calcErr2 = err_dn * content_up / content_dn / content_dn;
            ratiohist->SetBinError( ibin, sqrt(calcErr1*calcErr1 + calcErr2*calcErr2) );
        }
    }
    return ratiohist;
}

void ShowTriggerTurnOn( const char* ifile = "output.root" )
{
    TFile* fin = TFile::Open(ifile);
    
    const char* denominatorTemplate = "HLT_%d";
    const char* numeratorTemplate = "HLTintersect_%d_%d";

    TCanvas* c2 = new TCanvas("c2", "", 1600, 1000);
    c2->SetFillColor(4000);
    c2->SetFillStyle(4000);
    TCanvas* c1 = new TCanvas("c1", "", 1600, 1200);
    c1->Divide(2,1);
    c1->cd(2)->Divide(1,3);
    for ( int ibit = 0; ibit <= MAXBIT; ++ibit )
        for ( int jbit = ibit + 1; jbit <= MAXBIT; ++jbit )
        {
            TH1F* h_num = (TH1F*) fin->Get( Form(numeratorTemplate,ibit,jbit) );
            TH1F* h_den = (TH1F*) fin->Get( Form(denominatorTemplate,ibit) );
            
            TH1F* ratioplot = CalculateRatio(h_num, h_den, Form("HLTTurnOn_%dOver%d", jbit, ibit));
            if ( ratioplot->GetMaximum() > 0.5 )
                ratioplot->GetYaxis()->SetRangeUser(-0.05,1.05);
            ratioplot->SetLineWidth(5);
            c1->cd(1);
            ratioplot->Draw("ep");

            double maxnum = h_den->GetMaximum()*1.05;
            h_num->GetYaxis()->SetRangeUser(0., maxnum);
            h_num->SetLineColor(38);
            h_den->GetYaxis()->SetRangeUser(0., maxnum);
            h_den->SetLineColor(46);
            c1->cd(2)->cd(1);
            h_num->Draw("EP");
            c1->cd(2)->cd(2);
            h_den->Draw("EP");
            c1->cd(2)->cd(3);
            h_num->Draw("EP");
            h_den->Draw("EP same");
            c1->SaveAs( Form("checking_trunOn_%s.pdf", ratioplot->GetName()) );

            c2->cd();
            ratioplot->SetStats(false);
            ratioplot->SetTitle("");
            ratioplot->Draw("EP");
            c2->SaveAs( Form("turnOn_%s.pdf", ratioplot->GetName()) );
        }
}

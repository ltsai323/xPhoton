double NEntries(TH1* hist)
{
    double sum = 0;
    int ibin = hist->GetNbinsX();
    while ( ibin-- )
        sum += hist->GetBinContent(ibin);
    return sum;
}

void check()
{
    TFile* fin = TFile::Open("step3.DrawIsoBDT/storeroot/isovsbdt_template.root");

    TString histname;
    for ( int ebee = 0; ebee <= 1 ; ++ebee )
        for ( int jeteta = 0; jeteta <=1 ; ++jeteta )
            for ( int phopt = 0; phopt < 22; ++phopt )
    {
       histname.Form("fitVars/qcd_deepCSVTags_udsg_%d_%d_%d_px2", ebee, jeteta, phopt);
       TH1* h = (TH1*) fin->Get( histname );
       printf ( "phoeta : %2d, jeteta : %2d, phopt : %2d with entries : %12.2f\n", ebee, jeteta, phopt, NEntries(h) );
    }
}

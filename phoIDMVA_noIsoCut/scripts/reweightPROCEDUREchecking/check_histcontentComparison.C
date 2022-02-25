struct LoadedHists
{
    LoadedHists( const char* ifile )// : f(TFile::Open(ifile))
    {
        f = TFile::Open(ifile);
        h0 = (TH2*) f->Get("h_pho_pt_eta");
        h1 = (TH2*) f->Get("h_pho_pt_eta_rw");
        h2 = (TH2*) f->Get("h_fake_pt_eta");
        h3 = (TH2*) f->Get("h_fake_pt_eta_rw");
        h4 = (TH2*) f->Get("h_weight_pt_eta");
        h5 = (TH1*) f->Get("h_pt");
    }
    ~LoadedHists() { f->Close(); }

    TH2* h0;
    TH2* h1;
    TH2* h2;
    TH2* h3;
    TH2* h4;
    TH1* h5;
    TFile* f;
};
bool Comparison1D( TH1* histL, TH1* histR )
{
    for ( unsigned xBin = 0; xBin < histL->GetNbinsX(); ++xBin )
    {
        unsigned xbin = xBin + 1;

        double contentL = histL->GetBinContent(xbin);
        double contentR = histR->GetBinContent(xbin);

        if ( contentL != contentR )
        {
            printf( " at hist %s, content L %.1f and content R %.1f are different. Break checking\n", histL->GetName(), contentL, contentR );
            return false;
        }
    }
    return true;
}
bool Comparison2D( TH2* histL, TH2* histR )
{
    for ( unsigned xBin = 0; xBin < histL->GetNbinsX(); ++xBin )
    {
        for ( unsigned yBin = 0; yBin < histL->GetNbinsY(); ++yBin )
        {
            unsigned xbin = xBin + 1;
            unsigned ybin = yBin + 1;
            
            double contentL = histL->GetBinContent(xbin,ybin);
            double contentR = histR->GetBinContent(xbin,ybin);
            
            if ( contentL != contentR )
            {
                printf( " at hist %s @ bin (%d,%d), content L %.1f and content R %.1f are different. Break checking\n", histL->GetName(), xBin, yBin, contentL, contentR );
                //return false;
            }
        }
    }
    return true;
}
bool Comparsion( const LoadedHists& hists0, const LoadedHists& hists1 )
{
    if ( !Comparison2D(hists0.h0, hists1.h0) ) return false;
    if ( !Comparison2D(hists0.h1, hists1.h1) ) return false;
    if ( !Comparison2D(hists0.h2, hists1.h2) ) return false;
    if ( !Comparison2D(hists0.h3, hists1.h3) ) return false;
    if ( !Comparison2D(hists0.h4, hists1.h4) ) return false;
    if ( !Comparison1D(hists0.h5, hists1.h5) ) return false;
    return true;
}


void check_histcontentComparison()
{
    LoadedHists hists0("mytesting.root");
    LoadedHists hists1("rw_out.root");
    Comparsion(hists0, hists1);
}

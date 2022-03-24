{
    TFile* f = TFile::Open("../rw_out.root");

    TH2* h_pho_pt_eta    = (TH2*) f->Get("h_pho_pt_eta");
    TH2* h_pho_pt_eta_rw = (TH2*) f->Get("h_pho_pt_eta_rw");
    TH2* h_fake_pt_eta   = (TH2*) f->Get("h_fake_pt_eta");
    TH2* h_fake_pt_eta_rw= (TH2*) f->Get("h_fake_pt_eta_rw");
    TH2* h_weight_pt_eta = (TH2*) f->Get("h_weight_pt_eta");

    TH1* h = 

    const int binx = h_pho_pt_eta->GetNbinsX() + 1;
    const int biny = h_pho_pt_eta->GetNbinsY() + 1;

    int xIdx = binx;
    int yIdx = biny;

    for ( int xIdx = h_pho_pt_eta->GetNbinsX(); xIdx != 0; --xIdx )
        for ( int yIdx = h_pho_pt_eta->GetNbinsY(); yIdx != 0; --yIdx )
        {
        double valOrig = h_pho_pt_eta   ->GetBinContent(xIdx,yIdx);
        double weights = h_weight_pt_eta->GetBinContent(xIdx,yIdx);
        double valTarg = h_pho_pt_eta   ->GetBinContent(xIdx,yIdx);
        double valCalc = valOrig * weights;

        if ( valOrig < 1e-3 && valTarg < 1e-3 ) continue;
        if ( fabs(valCalc-valTarg) < 1e-6 ) continue;
        printf("True? %s @ bin(%d,%d) pt eta content : orig %.3e, reweighted %.3e and target %.3e\n",
                (valCalc-valTarg) < 1e-6 ? "Yes" : "No ", xIdx,yIdx, valOrig, valCalc, valTarg );

        }
    printf("hiii\n");
}

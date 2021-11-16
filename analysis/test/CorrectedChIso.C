void CorrectedChIso();
float EffectiveArea_ChIso(float eta)
{
    float abseta = fabs(eta);
    if      ( abseta < 1.0   ) return 0.0112;
    else if ( abseta < 1.479 ) return 0.0108;
    else if ( abseta < 2.0   ) return 0.0106;
    else if ( abseta < 2.2   ) return 0.01002;
    else if ( abseta < 2.3   ) return 0.0098;
    else if ( abseta < 2.4   ) return 0.0089;
    else                       return 0.0087;
    return 0;
}
float EffectiveArea_ChIso_Spring16(float eta)
{
    float abseta = fabs(eta);
    if      ( abseta < 1.0   ) return 0.0360;
    else if ( abseta < 1.479 ) return 0.0377;
    else if ( abseta < 2.0   ) return 0.0306;
    else if ( abseta < 2.2   ) return 0.0283;
    else if ( abseta < 2.3   ) return 0.0254;
    else if ( abseta < 2.4   ) return 0.0217;
    else                       return 0.0167;
    return 0;
}

float RhoCorrected( float iso, float rho, float effectivearea )
{
    float cIso = iso - rho * effectivearea;
    return cIso > 0. ? cIso : 0.;
}





void CorrectedChIso()
{
    TFile* fin = TFile::Open("/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root");
    TTree* tin = (TTree*) fin->Get("t");

    float eta, sceta, chiso, rho;
    tin->SetBranchAddress("chIsoRaw", &chiso);
    tin->SetBranchAddress("rho", &rho);
    tin->SetBranchAddress("recoSCEta", &sceta);
    tin->SetBranchAddress("recoEta", &eta);

    TH2F* horig = new TH2F("horig", "", 80, 0., 40., 75, 0., 15.);
    TH2F* hcalb = new TH2F("hcalb", "", 80, 0., 40., 75, 0., 15.);
    TH2F* hcaSC = new TH2F("hcaSC", "", 80, 0., 40., 75, 0., 15.);
    for ( int ientry = 0; ientry != tin->GetEntries(); ++ientry )
    {
        tin->GetEntry(ientry);
        
        horig->Fill(rho, chiso);
        hcalb->Fill(rho, RhoCorrected( chiso, rho, EffectiveArea_ChIso(eta) ) );
        hcaSC->Fill(rho, RhoCorrected( chiso, rho, EffectiveArea_ChIso(sceta) ) );
    }
    TFile* newfile = new TFile("newfile.root", "recreate");
    newfile->cd();
    horig->Write();
    hcalb->Write();
    hcaSC->Write();
}



        



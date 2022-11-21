 std::vector<float> vec_ptcut{25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]

TH1* ConvertToBinningAxis(TH1* hin)
{
    TH1* newhist = new TH1F( Form("%s_bin", hin->GetName()), Form("fraction to %s", hin->GetName()), hin->GetNbinsX(), 0, hin->GetNbinsX() );
    for ( int ibin = hin->GetNbinsX() + 1; ibin != 0; --ibin )
    {
        newhist->SetBinContent( ibin, hin->GetBinContent(ibin) );
        newhist->SetBinError( ibin, hin->GetBinError(ibin) );
    }
    return newhist;
}
#define BARREL 1
#define ENDCAP 2
#define SIGNALREGION 1
#define DATASIDEBAND 2
struct MCCutStrMgr
{
    MCCutStrMgr() : cut("1"),
    tag_fiducialRegion(0), tag_controlRegion(0)
    {BasicCuts();}
    void BasicCuts() { cut+= TString(" && ") + TString("isMatched!=1&&recoPtCalib>30.&&jetDeepCSVTags_c>-0.99&&jetID==1&&jetPUIDbit==7&&jetSubVtxMass!=0"); }
    void AddCut(const char* c) { cut += TString(" && ") + TString(c); }
    void BarrelPhoton()
    { tag_fiducialRegion = BARREL; cut += TString(" && fabs(recoEta)<1.5&&sieieFull5x5<0.012&&HoverE<0.08"); }
    void EndcapPhoton()
    { tag_fiducialRegion = ENDCAP; cut += TString(" && fabs(recoEta)>1.5&&sieieFull5x5<0.027&&HoverE<0.05"); }
    void SignalRegion()
    {
        tag_controlRegion = SIGNALREGION;
        if ( tag_fiducialRegion == 0 ) throw "-- MCCutStrMgr::SignalRegion() -- Error: Fiducial region is needed to be determined first\n";
        if ( tag_fiducialRegion == BARREL ) cut += TString(" && chIsoRaw<2");
        if ( tag_fiducialRegion == ENDCAP ) cut += TString(" && chIsoRaw<1.5");
    }
    void DataSideband()
    {
        tag_controlRegion = DATASIDEBAND;
        if ( tag_fiducialRegion == 0 ) throw "-- MCCutStrMgr::DataSideband() -- Error: Fiducial region is needed to be determined first\n";
        if ( tag_fiducialRegion == BARREL ) cut += TString(" && chIsoRaw>7&&chIsoRaw<13");
        if ( tag_fiducialRegion == ENDCAP ) cut += TString(" && chIsoRaw>6&&chIsoRaw<12");
    }

    
    const char* bFrac()
    { outSelection = "mcweight*("+cut+" && fabs(jetHadFlvr)==5"+" )"; return outSelection.Data(); }
    const char* cFrac()
    { outSelection = "mcweight*("+cut+" && fabs(jetHadFlvr)==4"+" )"; return outSelection.Data(); }
    const char* lFrac()
    { outSelection = "mcweight*("+cut+" && fabs(jetHadFlvr)==0"+" )"; return outSelection.Data(); }
    const char* EventSelections()
    { outSelection = "mcweight*("+cut+")"; return outSelection.Data(); }

    TString cut;
    TString outSelection;
    int tag_fiducialRegion;
    int tag_controlRegion;
};
void DrawingCheck( const char* v0, const char* v1 )
{ printf("var : %s -- cut : %s\n", v0, v1); }
struct FlavourHistMgr
{
    FlavourHistMgr( TString nametag, const MCCutStrMgr& cuts , int nArr, float* xArr )
    {
        if ( cuts.tag_fiducialRegion == 0 ) throw "-- FlavourHistMgr -- incoming MCCutStrMgr is incompleted. fiducial region is needed\n";
        TString fiducialTag( cuts.tag_fiducialRegion == BARREL ? "EB" : "EE" );
        if ( cuts.tag_controlRegion  == 0 ) throw "-- FlavourHistMgr -- incoming MCCutStrMgr is incompleted. control region is needed\n";
        TString controlTag( cuts.tag_controlRegion == SIGNALREGION ? "SR" : "SB" );
        SelectionName = nametag+"_"+fiducialTag+"_"+controlTag+"_";
        
        hBFlavour = new TH1F( NewName("bYield"), "", nArr, xArr );
        hCFlavour = new TH1F( NewName("cYield"), "", nArr, xArr );
        hLFlavour = new TH1F( NewName("lYield"), "", nArr, xArr );
    }
    void FractionHistsCalc()
    {
        hBFrac = (TH1*) hBFlavour->Clone( NewName("bFrac") );
        hCFrac = (TH1*) hCFlavour->Clone( NewName("cFrac") );
        hLFrac = (TH1*) hLFlavour->Clone( NewName("lFrac") );
        
        for ( int ibin = hBFlavour->GetNbinsX() + 1 ; ibin != 0 ; --ibin )
        {
            float allB = hBFlavour->GetBinContent(ibin);
            float allC = hCFlavour->GetBinContent(ibin);
            float allL = hLFlavour->GetBinContent(ibin);
            float errB = hBFlavour->GetBinError  (ibin);
            float errC = hCFlavour->GetBinError  (ibin);
            float errL = hLFlavour->GetBinError  (ibin);
            float Nentries = allB + allC + allL;
            float fracB = allB / Nentries;
            float fracC = allC / Nentries;
            float fracL = allL / Nentries;
            hBFrac->SetBinContent( ibin, fracB );
            hBFrac->SetBinError( ibin,
                    sqrt( (allC+allL)*(allC+allL)*errB*errB + allB*allB*(errC*errC+errL*errL) ) /
                    (Nentries*Nentries)
                    );
            hCFrac->SetBinContent( ibin, fracC );
            hCFrac->SetBinError( ibin,
                    sqrt( (allB+allL)*(allB+allL)*errC*errC + allC*allC*(errB*errB+errL*errL) ) /
                    (Nentries*Nentries)
                    );
            hLFrac->SetBinContent( ibin, fracL );
            hLFrac->SetBinError( ibin,
                    sqrt( (allC+allB)*(allC+allB)*errL*errL + allL*allL*(errC*errC+errB*errB) ) /
                    (Nentries*Nentries)
                    );
        }
        hBFrac_bin = ConvertToBinningAxis( hBFrac );
        hCFrac_bin = ConvertToBinningAxis( hCFrac );
        hLFrac_bin = ConvertToBinningAxis( hLFrac );
    }
    const char* bName() { return hBFlavour->GetName(); }
    const char* cName() { return hCFlavour->GetName(); }
    const char* lName() { return hLFlavour->GetName(); }
    const char* NewName( const char* name ) { tmpName = SelectionName + name; return tmpName.Data(); }
    void SetLineColorWidthAll(int color_, int width_)
    {
        hBFlavour->SetLineColor(color_);
        hCFlavour->SetLineColor(color_);
        hLFlavour->SetLineColor(color_);
        hBFrac->SetLineColor(color_);
        hCFrac->SetLineColor(color_);
        hLFrac->SetLineColor(color_);
        hBFrac_bin->SetLineColor(color_);
        hCFrac_bin->SetLineColor(color_);
        hLFrac_bin->SetLineColor(color_);

        hBFlavour->SetLineWidth(width_);
        hCFlavour->SetLineWidth(width_);
        hLFlavour->SetLineWidth(width_);
        hBFrac->SetLineWidth(width_);
        hCFrac->SetLineWidth(width_);
        hLFrac->SetLineWidth(width_);
        hBFrac_bin->SetLineWidth(width_);
        hCFrac_bin->SetLineWidth(width_);
        hLFrac_bin->SetLineWidth(width_);
    }
    void Write()
    {
        hBFlavour->Write();
        hCFlavour->Write();
        hLFlavour->Write();
        hBFrac->Write();
        hCFrac->Write();
        hLFrac->Write();
        hBFrac_bin->Write();
        hCFrac_bin->Write();
        hLFrac_bin->Write();
    }

    TH1* hBFlavour;
    TH1* hCFlavour;
    TH1* hLFlavour;
    TH1* hBFrac;
    TH1* hCFrac;
    TH1* hLFrac;
    TH1* hBFrac_bin;
    TH1* hCFrac_bin;
    TH1* hLFrac_bin;
    TString SelectionName;
    TString tmpName;
};


void JetFractionCalc()
{
    //TFile* fin = TFile::Open("/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root");
    TFile* fin = TFile::Open("/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph_loosedPhoSelection.root");
    TTree* tin = (TTree*) fin->Get("t");

    
    int    nArr = 20;
    float* xArr = &(vec_ptcut.front());

    MCCutStrMgr allBarrel_SR;
    allBarrel_SR.BarrelPhoton();
    allBarrel_SR.SignalRegion();
    FlavourHistMgr hAllEB_SR("all", allBarrel_SR, nArr, xArr);
    tin->Draw( Form("recoPtCalib >> %s",hAllEB_SR.bName()), allBarrel_SR.bFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEB_SR.cName()), allBarrel_SR.cFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEB_SR.lName()), allBarrel_SR.lFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEB_SR.bName()), allBarrel_SR.bFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEB_SR.cName()), allBarrel_SR.cFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEB_SR.lName()), allBarrel_SR.lFrac() );
    hAllEB_SR.FractionHistsCalc();
    //hAllEB_SR.SetLineColorWidthAll(39,4);

    MCCutStrMgr allBarrel_SB;
    allBarrel_SB.BarrelPhoton();
    allBarrel_SB.DataSideband();
    FlavourHistMgr hAllEB_SB("all", allBarrel_SB, nArr, xArr);
    tin->Draw( Form("recoPtCalib >> %s",hAllEB_SB.bName()), allBarrel_SB.bFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEB_SB.cName()), allBarrel_SB.cFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEB_SB.lName()), allBarrel_SB.lFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEB_SB.bName()), allBarrel_SB.bFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEB_SB.cName()), allBarrel_SB.cFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEB_SB.lName()), allBarrel_SB.lFrac() );
    hAllEB_SB.FractionHistsCalc();
    //hAllEB_SB.SetLineColorWidthAll(49,4);

    MCCutStrMgr cutBarrel_SR;
    cutBarrel_SR.AddCut( "mcweight<13000" );
    cutBarrel_SR.BarrelPhoton();
    cutBarrel_SR.SignalRegion();
    FlavourHistMgr hCutEB_SR("cut", cutBarrel_SR, nArr, xArr);
    tin->Draw( Form("recoPtCalib >> %s",hCutEB_SR.bName()), cutBarrel_SR.bFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEB_SR.cName()), cutBarrel_SR.cFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEB_SR.lName()), cutBarrel_SR.lFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEB_SR.bName()), cutBarrel_SR.bFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEB_SR.cName()), cutBarrel_SR.cFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEB_SR.lName()), cutBarrel_SR.lFrac() );
    hCutEB_SR.FractionHistsCalc();
    //hCutEB_SR.SetLineColorWidthAll( 4,2);

    MCCutStrMgr cutBarrel_SB;
    cutBarrel_SB.AddCut( "mcweight<13000" );
    cutBarrel_SB.BarrelPhoton();
    cutBarrel_SB.DataSideband();
    FlavourHistMgr hCutEB_SB("cut", cutBarrel_SB, nArr, xArr);
    tin->Draw( Form("recoPtCalib >> %s",hCutEB_SB.bName()), cutBarrel_SB.bFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEB_SB.cName()), cutBarrel_SB.cFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEB_SB.lName()), cutBarrel_SB.lFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEB_SB.bName()), cutBarrel_SB.bFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEB_SB.cName()), cutBarrel_SB.cFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEB_SB.lName()), cutBarrel_SB.lFrac() );
    hCutEB_SB.FractionHistsCalc();
    //hCutEB_SB.SetLineColorWidthAll( 2,2);

    MCCutStrMgr allEndcap_SR;
    allEndcap_SR.EndcapPhoton();
    allEndcap_SR.SignalRegion();
    FlavourHistMgr hAllEE_SR("all", allEndcap_SR, nArr, xArr);
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEE_SR.bName()), allEndcap_SR.bFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEE_SR.cName()), allEndcap_SR.cFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEE_SR.lName()), allEndcap_SR.lFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEE_SR.bName()), allEndcap_SR.bFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEE_SR.cName()), allEndcap_SR.cFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEE_SR.lName()), allEndcap_SR.lFrac() );
    hAllEE_SR.FractionHistsCalc();
    //hAllEE_SR.SetLineColorWidthAll(39,4);

    MCCutStrMgr allEndcap_SB;
    allEndcap_SB.EndcapPhoton();
    allEndcap_SB.DataSideband();
    FlavourHistMgr hAllEE_SB("all", allEndcap_SB, nArr, xArr);
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEE_SB.bName()), allEndcap_SB.bFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEE_SB.cName()), allEndcap_SB.cFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hAllEE_SB.lName()), allEndcap_SB.lFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEE_SB.bName()), allEndcap_SB.bFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEE_SB.cName()), allEndcap_SB.cFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hAllEE_SB.lName()), allEndcap_SB.lFrac() );
    hAllEE_SB.FractionHistsCalc();
    //hAllEE_SB.SetLineColorWidthAll(49,4);

    MCCutStrMgr cutEndcap_SR;
    cutEndcap_SR.AddCut( "mcweight<13000" );
    cutEndcap_SR.EndcapPhoton();
    cutEndcap_SR.SignalRegion();
    FlavourHistMgr hCutEE_SR("cut", cutEndcap_SR, nArr, xArr);
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEE_SR.bName()), cutEndcap_SR.bFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEE_SR.cName()), cutEndcap_SR.cFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEE_SR.lName()), cutEndcap_SR.lFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEE_SR.bName()), cutEndcap_SR.bFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEE_SR.cName()), cutEndcap_SR.cFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEE_SR.lName()), cutEndcap_SR.lFrac() );
    hCutEE_SR.FractionHistsCalc();
    //hCutEE_SR.SetLineColorWidthAll( 4,2);

    MCCutStrMgr cutEndcap_SB;
    cutEndcap_SB.AddCut( "mcweight<13000" );
    cutEndcap_SB.EndcapPhoton();
    cutEndcap_SB.DataSideband();
    FlavourHistMgr hCutEE_SB("cut", cutEndcap_SB, nArr, xArr);
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEE_SB.bName()), cutEndcap_SB.bFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEE_SB.cName()), cutEndcap_SB.cFrac() );
    //DrawingCheck( Form("recoPtCalib >> %s",hCutEE_SB.lName()), cutEndcap_SB.lFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEE_SB.bName()), cutEndcap_SB.bFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEE_SB.cName()), cutEndcap_SB.cFrac() );
    tin->Draw( Form("recoPtCalib >> %s",hCutEE_SB.lName()), cutEndcap_SB.lFrac() );
    hCutEE_SB.FractionHistsCalc();
    //hCutEE_SB.SetLineColorWidthAll( 2,2);

    TFile* outfile = new TFile("fractionHists.root", "RECREATE");
    outfile->cd();
    hAllEE_SR.Write();
    hAllEB_SR.Write();
    hAllEE_SB.Write();
    hAllEB_SB.Write();

    hCutEE_SR.Write();
    hCutEB_SR.Write();
    hCutEE_SB.Write();
    hCutEB_SB.Write();

    printf( "Overall used cuts :\n" );
    printf( " --> %s --- %s\n", hAllEB_SB.NewName("selections"), allBarrel_SB.EventSelections() );
    printf( " --> %s --- %s\n", hAllEB_SR.NewName("selections"), allBarrel_SR.EventSelections() );
    printf( " --> %s --- %s\n", hAllEE_SB.NewName("selections"), allEndcap_SB.EventSelections() );
    printf( " --> %s --- %s\n", hAllEE_SR.NewName("selections"), allEndcap_SR.EventSelections() );

    printf( " --> %s --- %s\n", hCutEB_SB.NewName("selections"), cutBarrel_SB.EventSelections() );
    printf( " --> %s --- %s\n", hCutEB_SR.NewName("selections"), cutBarrel_SR.EventSelections() );
    printf( " --> %s --- %s\n", hCutEE_SB.NewName("selections"), cutEndcap_SB.EventSelections() );
    printf( " --> %s --- %s\n", hCutEE_SR.NewName("selections"), cutEndcap_SR.EventSelections() );
    outfile->Close();
}

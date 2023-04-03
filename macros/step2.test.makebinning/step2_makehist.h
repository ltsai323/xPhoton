#ifndef __newhists_h__
#define __newhists_h__
struct filterfunc
{
    // used variables
    static std::vector<float> vec_ptcut;
    static int HLTOPTION;
    static std::string dataera;
    static int cutIndicator;
    static int IsMC;
    static int IsQCD;
    static bool checkplots;

    static void ValidCheck()
    {
        if ( filterfunc::dataera == "" ) throw "filterfunc :: dataera not set\n\nn";
        if ( filterfunc::vec_ptcut.size() == 0 ) throw "filterfunc :: vec_ptcut is empty\n\n";
        if ( filterfunc::IsMC == -1 ) throw "filterfunc :: IsMC is not set\n\n";
    }


    static Int_t    EBEE(Float_t eta);
    static Int_t    Ptbin(Float_t pt);
    static Int_t    JetEtaBin(Float_t pt, Float_t eta);
    static Int_t    triggerbit(const std::string& dataera, float phopt);
    static Int_t    JetFlavourBin( int jetHadFlvr ); //
    static Int_t    IsFakePhoton(int isMatched, int isConverted, int isMatchedEle);

    static bool PhoSignalRegion(Float_t isovar, Float_t eta);
    static bool PhoDataSideband(Float_t isovar, Float_t eta);
    static bool HLTPassed(float phopt, Long64_t phoFiredTrgs);
    static Int_t PhoMatchedStatus(); //
    static Int_t EventParity(Long64_t evtidx); //

    static bool PassJetAdditionalSelection_passPUcut(int passMaxPUcut);
    static bool PassJetAdditionalSelection(float jetPt, float jetEta, float jetDeepCSVTags_c, float jetSubVtxMass, float jetDeepCSVDiscriminatorTags_CvsL);
    static bool PassJetAdditionalSelection_MC(int jetID, int jetPUIDbit);
    static bool basic_selection(float recoSCEta, float MET, float photonpt, int eleVeto);
    static bool fiducial_photon(float recoSCEta, float sieieFull5x5, float HoverE);
};
std::vector<float> filterfunc::vec_ptcut = {};
int filterfunc::HLTOPTION = 0;
std::string filterfunc::dataera = "";
int filterfunc::cutIndicator = 0;
int filterfunc::IsMC = -1;
int filterfunc::IsQCD = -1;
bool filterfunc::checkplots = false;

Int_t filterfunc::EBEE(Float_t eta)
{
    if ( TMath::Abs(eta)<1.5 )    return 0;
    else                          return 1;
}
Int_t filterfunc::Ptbin(Float_t pt)
{
    std::vector<float> ptcut = filterfunc::vec_ptcut;
    int ibin = ptcut.size();

    // returned ibin = 0 to size-1
    while ( ibin-- )
    { if ( pt >= ptcut[ibin] ) return ibin; }

    // nothing found.
    return -1;
}

Int_t filterfunc::JetEtaBin(Float_t pt, Float_t eta) {  
    if(pt< 1e-3) return 2;
    if(TMath::Abs(eta)<1.5) return 0;
    return 1;
}

bool filterfunc::PassJetAdditionalSelection(float jetPt, float jetEta, float jetDeepCSVTags_c, float jetSubVtxMass, float jetDeepCSVDiscriminatorTags_CvsL)
{
    filterfunc::ValidCheck();
    if ( jetPt < 30. ) return false;
    if ( fabs(jetEta) > 2.5 ) return false;
    if ( jetDeepCSVTags_c < -0.99 ) return false;

    //if ( mcweight>3000. ) return false;
    if ( filterfunc::cutIndicator == 1 && jetSubVtxMass == 0 ) return false;
    if ( filterfunc::cutIndicator == 2 && jetDeepCSVDiscriminatorTags_CvsL < 0.155) return false;

    return true;
}
bool filterfunc::PassJetAdditionalSelection_MC(int jetID, int jetPUIDbit)
{
    filterfunc::ValidCheck();
    if ( filterfunc::IsMC==1 && jetID!=1 ) return false;
    if ( filterfunc::IsMC==1 && jetPUIDbit!=7 ) return false;
    return true;
}
bool filterfunc::PassJetAdditionalSelection_passPUcut(int passMaxPUcut)
{
    filterfunc::ValidCheck();
    if ( filterfunc::IsQCD==1 &&!passMaxPUcut ) return false;
    return true;
}

bool filterfunc::PhoSignalRegion(Float_t isovar, Float_t eta)
{
    int ebee = EBEE(eta);
    if ( ebee == 0 && fabs(isovar) < 2  ) return true;
    if ( ebee == 1 && fabs(isovar) < 1.5) return true;
    return false;
}
bool filterfunc::PhoDataSideband(Float_t isovar, Float_t eta)
{
    int ebee = EBEE(eta);
    if ( ebee == 0 && fabs(isovar)>7 && fabs(isovar)<13 ) return true;
    if ( ebee == 1 && fabs(isovar)>6 && fabs(isovar)<12 ) return true;
    return false;
}
bool filterfunc::HLTPassed(float phopt, Long64_t phoFiredTrgs)
{
    filterfunc::ValidCheck();
    int hltbit = filterfunc::triggerbit(filterfunc::dataera, phopt);
    if ( filterfunc::HLTOPTION == 1 && !((phoFiredTrgs>>hltbit)&1) ) return false;
    return true;
}
Int_t filterfunc::triggerbit( const std::string& dataera, float phopt){
    Int_t ptbin = filterfunc::Ptbin(phopt);
    //std::cout << dataera << endl;
    if ( dataera == "2016ReReco" )
    {
        if ( ptbin == 0 ) return 0;  //  25- 34 -> 25-34
        if ( ptbin == 1 ) return 1;  //  34- 40 -> 34-41
        if ( ptbin == 2 ) return 2;  //  40- 55 -> 41-56
        if ( ptbin == 3 ) return 3;  //  55- 70 -> 56-70?
        if ( ptbin == 4 ) return 3;  //  70- 85
        if ( ptbin == 5 ) return 4;  // 85-100
        if ( ptbin == 6 ) return 5;  // 100-115
        if ( ptbin == 7 ) return 5;  // 115-135
        if ( ptbin == 8 ) return 6;  // 135-155
        if ( ptbin == 9 ) return 6;  // 155-175
        if ( ptbin ==10 ) return 6;  // 175-190
        if ( ptbin ==11 ) return 7;  // 190-200
        if ( ptbin ==12 ) return 7;  // 200-300
        if ( ptbin ==13 ) return 7;  // 300-350
        if ( ptbin ==14 ) return 7;  // 350-400
        if ( ptbin ==15 ) return 7;  // 400-500
        if ( ptbin ==16 ) return 7;  // 500-750
        if ( ptbin ==17 ) return 7;  // 750-1000
        if ( ptbin ==18 ) return 7;  //1000-1500
        if ( ptbin ==19 ) return 7;  //1500-2000
        if ( ptbin ==20 ) return 7;  //2000-3000
        if ( ptbin ==21 ) return 7;  //3000-10000
        if ( ptbin ==22 ) return 7;  // to inf
    }
    if ( dataera == "UL2017" )
    {
        return 0;
    }
    if ( dataera == "UL2018" )
    {
        if ( ptbin == 0 ) return 0;  //  25- 34
        if ( ptbin == 1 ) return 0;  //  34- 40
        if ( ptbin == 2 ) return 0;  //  40- 55
        if ( ptbin == 3 ) return 1;  //  55- 70
        if ( ptbin == 4 ) return 1;  //  70- 85
        if ( ptbin == 5 ) return 2;  // 85-100
        if ( ptbin == 6 ) return 3;  // 100-115
        if ( ptbin == 7 ) return 3;  // 115-135
        if ( ptbin == 8 ) return 4;  // 135-155
        if ( ptbin == 9 ) return 5;  // 155-175
        if ( ptbin ==10 ) return 6;  // 175-190
        if ( ptbin ==11 ) return 6;  // 190-200
        if ( ptbin ==12 ) return 7;  // 200-300
        if ( ptbin ==13 ) return 8;  // 300-350
        if ( ptbin ==14 ) return 8;  // 350-400
        if ( ptbin ==15 ) return 8;  // 400-500
        if ( ptbin ==16 ) return 8;  // 500-750
        if ( ptbin ==17 ) return 8;  // 750-1000
        if ( ptbin ==18 ) return 8;  //1000-1500
        if ( ptbin ==19 ) return 8;  //1500-2000
        if ( ptbin ==20 ) return 8;  //2000-3000
        if ( ptbin ==21 ) return 8;  //3000-10000
        if ( ptbin ==22 ) return 8;  // to inf
    }

    return -1; // nothing
}
bool filterfunc::basic_selection(float recoSCEta, float MET, float photonpt, int eleVeto)
{
    if(TMath::Abs(recoSCEta)>1.4442 && TMath::Abs(recoSCEta)<1.566) return false;
    if(TMath::Abs(recoSCEta)>2.5) return false;
    if(MET/photonpt > 0.7) return false;
    if ( eleVeto == 0 ) return false;
    return true;
}


bool filterfunc::fiducial_photon(float recoSCEta, float sieieFull5x5, float HoverE)
{
    if ( TMath::Abs(recoSCEta)<1.5 && sieieFull5x5 > 0.012 ) return false;
    if ( TMath::Abs(recoSCEta)<1.5 && HoverE       > 0.08  ) return false;
    if ( TMath::Abs(recoSCEta)>1.5 && sieieFull5x5 > 0.027 ) return false;
    if ( TMath::Abs(recoSCEta)>1.5 && HoverE       > 0.05  ) return false;
    return true;
}
Int_t filterfunc::IsFakePhoton(int isMatched, int isConverted, int isMatchedEle)
{
    filterfunc::ValidCheck();
    if( filterfunc::IsMC &&  isMatched!=1 && isConverted!=1 && isMatchedEle!=1) return 1;
    return 0;
}
#endif

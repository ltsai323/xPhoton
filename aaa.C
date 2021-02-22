
//void xPhotonHFJet(Char_t fname[200], Char_t oname[200]){
void xPhotonHFJet(vector<string> pathes, Char_t oname[200]){
  TreeReader data(pathes);

  for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
    TLorentzVector phoP4, lepP4[2], zllP4, electronP4, wlnP4, nueP4, trigger_jetP4, jetP4;
    data.GetEntry(ev);
    run     = data.GetInt("run");
    event   = data.GetLong64("event"); 
    isData = data.GetBool("isData");
    nVtx = data.GetInt("nVtx");    
    Int_t    nPho     = data.GetInt("nPho");
    Int_t nJet = data.GetInt("nJet");

    if(!data.HasMC())
    {
      HLT = data.GetLong64("HLTPho");
      HLTIsPrescaled  = data.GetLong64("HLTPhoIsPrescaled");
      metFilters = data.GetInt("metFilters");
    }

    if(data.HasMC())
    {
      pthat     = data.GetFloat("pthat");
      nMC       = data.GetInt("nMC");
      mcPID     = data.GetPtrInt("mcPID");
      mcMomPID  = data.GetPtrInt("mcMomPID");
      mcGMomPID = data.GetPtrInt("mcGMomPID");
      mcPt      = data.GetPtrFloat("mcPt");
      mcEta     = data.GetPtrFloat("mcEta");
      mcPhi     = data.GetPtrFloat("mcPhi");
      mcE       = data.GetPtrFloat("mcE");
      mcMomPt   = data.GetPtrFloat("mcMomPt");
      mcMomEta   = data.GetPtrFloat("mcMomEta");
      mcMomPhi   = data.GetPtrFloat("mcMomPhi");
      mcStatus = data.GetPtrShort("mcStatusFlag");
      genHT = data.GetFloat("genHT");
      jetGenJetPt = data.GetPtrFloat("jetGenJetPt");
      jetGenJetEn = data.GetPtrFloat("jetGenJetEn");
      jetGenJetEta = data.GetPtrFloat("jetGenJetEta");
      jetGenJetPhi = data.GetPtrFloat("jetGenJetPhi");

      /* temporarily disabled
      {
          nPUInfo = data.GetInt("nPUInfo");
          puBX    = data.GetPtrInt("puBX");
          puTrue  = data.GetPtrFloat("puTrue");
          for (Int_t i=0; i<nPUInfo; ++i) { if (puBX[i] == 0) nPU = puTrue[i]; }      
      }
      mcCalIsoDR04 = data.GetPtrFloat("mcCalIsoDR04");
      mcTrkIsoDR04 = data.GetPtrFloat("mcTrkIsoDR04");
      puwei_ = (float) puCalc.GetWeight(run, puTrue[1]); // in-time PU
      */

      {
          genWeight = data.GetFloat("genWeight");      
          if(genWeight>0.) xsweight=XS;
          else xsweight=XS*-1.;
          if(gjet15to6000==1) xsweight=genWeight;
      }
    } // not data end

    // if ( hasSubVtxInfo )
    {
      jetSubVtxPt    = data.GetPtrFloat("jetSubVtxPt"   );
      jetSubVtxMass  = data.GetPtrFloat("jetSubVtxMass" );
      jetSubVtx3DVal = data.GetPtrFloat("jetSubVtx3DVal");
      jetSubVtx3DErr = data.GetPtrFloat("jetSubVtx3DErr");
      jetSubVtxNtrks = data.GetPtrInt("jetSubVtxNtrks");
    }

    Float_t pfMET = data.GetFloat("pfMET"); MET = pfMET;
    Float_t pfMETPhi = data.GetFloat("pfMETPhi"); METPhi = pfMETPhi;

    //Int_t nJet = data.GetInt("nJet");
    Float_t* jetPt = data.GetPtrFloat("jetPt");
    Float_t* jetEn = data.GetPtrFloat("jetEn");
    Float_t* jetEta = data.GetPtrFloat("jetEta");
    Float_t* jetPhi = data.GetPtrFloat("jetPhi");
    Long64_t*   jetFiredTrgs = data.GetPtrLong64("jetFiredTrgs");      
    Float_t *jetJECUnc = data.GetPtrFloat("jetJECUnc");

    Float_t *jetCSV2BJetTags = data.GetPtrFloat("jetCSV2BJetTags");
    Float_t *jetDeepCSVTags_b = data.GetPtrFloat("jetDeepCSVTags_b");
    Float_t *jetDeepCSVTags_bb = data.GetPtrFloat("jetDeepCSVTags_bb");
    Float_t *jetDeepCSVTags_c = data.GetPtrFloat("jetDeepCSVTags_c");
    Float_t *jetDeepCSVTags_udsg = data.GetPtrFloat("jetDeepCSVTags_udsg");

    if ( data.HasMC() )
    { // is MC
        Int_t *jetPartonID = data.GetPtrInt("jetPartonID");
        Int_t *jetGenPartonID = data.GetPtrInt("jetGenPartonID");
        Int_t *jetHadFlvr = data.GetPtrInt("jetHadFlvr");
    }

    Float_t* phoEta   = data.GetPtrFloat("phoEta");
    Float_t* phoPhi   = data.GetPtrFloat("phoPhi");
    Float_t* phoEt    = data.GetPtrFloat("phoEt");
    Float_t* phoR9    = data.GetPtrFloat("phoR9");
    Float_t* phoSCEta = data.GetPtrFloat("phoSCEta");
    
    // Int_t*   phoEleVeto          = data.GetPtrInt("phoEleVeto");
    eleVeto          = data.GetPtrInt("phoEleVeto") [phoIdx];
    Float_t* phoHoverE           = data.GetPtrFloat("phoHoverE");
    Float_t* phoPFChIso          = data.GetPtrFloat("phoPFChIso");
    Float_t* phoPFNeuIso         = data.GetPtrFloat("phoPFNeuIso");
    Float_t* phoPFPhoIso         = data.GetPtrFloat("phoPFPhoIso");
    Int_t* phohasPixelSeed     = data.GetPtrInt("phohasPixelSeed");

    rho                 = data.GetFloat("rho");

    Float_t* phoSCRawE         = data.GetPtrFloat("phoSCRawE");
    Float_t* phoSCEtaWidth     = data.GetPtrFloat("phoSCEtaWidth");
    Float_t* phoSCPhiWidth     = data.GetPtrFloat("phoSCPhiWidth");
    Float_t* phoESEnP1           = data.GetPtrFloat("phoESEnP1");
    Float_t* phoESEnP2           = data.GetPtrFloat("phoESEnP2");
    Float_t* phoESEffSigmaRR   = data.GetPtrFloat("phoESEffSigmaRR");
    Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso");

    Float_t* phoSigmaIEtaIEtaFull5x5  = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
    Float_t* phoSigmaIEtaIPhiFull5x5  = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
    Float_t* phoSigmaIPhiIPhiFull5x5  = data.GetPtrFloat("phoSigmaIPhiIPhiFull5x5");
    Float_t* phoR9Full5x5           = data.GetPtrFloat("phoR9Full5x5");
    Float_t* phoE2x2Full5x5            = data.GetPtrFloat("phoE2x2Full5x5");
    Float_t* phoE5x5Full5x5            = data.GetPtrFloat("phoE5x5Full5x5");
    Float_t* phoIDMVA = data.GetPtrFloat("phoIDMVA");

    Long64_t* phoFiredTrgs = data.GetPtrLong64("phoFiredSingleTrgs");
    Short_t* phoIDbit = data.GetPtrShort("phoIDbit");

    if ( !hasMC() ) // but phoSeedEnergy exists in MC
    {
      phoSeedEnergy = data.GetPtrFloat("phoSeedEnergy");
      }


    float* elePt  = data.GetPtrFloat("elePt");
    float* eleEta = data.GetPtrFloat("eleEta");
    float* elePhi = data.GetPtrFloat("elePhi");    
    


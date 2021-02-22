        {
        }


        if ( !isMC )
        {
        }

        t->Branch("HLT50ns",         &HLT50ns,        "HLT50ns/L");
        t->Branch("HLTIsPrescaled50ns",         &HLTIsPrescaled50ns,        "HLTIsPrescaled50ns/L");

        if ( isMC )
        {
            t->Branch("mcCalIso04",   &mcCalIso04,   "mcCalIso04/F");
            t->Branch("mcTrkIso04",   &mcTrkIso04,   "mcTrkIso04/F");
        }

        if ( isMC )
        {
            t->Branch("isMatched",    &isMatched,    "isMatched/I");
            t->Branch("isMatchedEle", &isMatchedEle, "isMatchedEle/I");
            t->Branch("isConverted",    &isConverted,    "isConverted/I");
        }
        t->Branch("nVtx",         &nVtx,         "nVtx/I");

        if (isMC )
        {
            t->Branch("nPU",          &nPU,          "nPU/I");
            t->Branch("puwei",        &puwei,        "puwei/F");
        }
        t->Branch("sieie",        &sieie,        "sieie/F"); // disabled
        t->Branch("sieip",        &sieip,        "sieip/F"); // disabled
        t->Branch("sipip",        &sipip,        "sipip/F"); // disabled
        t->Branch("chIso",        &chIso,        "chIso/F"); // decalred but not used in any region
        t->Branch("phoIso",       &phoIso,       "phoIso/F"); // decalred but not used in any region
        t->Branch("phoIsoRaw",    &phoIsoRaw,    "phoIsoRaw/F");
        t->Branch("nhIsoRaw",     &nhIsoRaw,     "nhIsoRaw/F");
        t->Branch("e1x3",         &e1x3,         "e1x3/F"); // disabled
        t->Branch("e2x2",         &e2x2,         "e2x2/F"); // disabled
        t->Branch("e2x5",         &e2x5,         "e2x5/F"); // disabled
        t->Branch("e5x5",         &e5x5,         "e5x5/F"); // disabled
        t->Branch("mva",          &mva,          "mva/F");  
        t->Branch("photonIDmva",       &photonIDmva,       "photonIDmva/F");  
        t->Branch("mva_hgg",      &mva_hgg,      "mva_hgg/F");  
        t->Branch("HggPresel",    &HggPresel,    "HggPresel/I");  // disabled
        t->Branch("Mmm",    &Mmm,    "Mmm/F");  
        t->Branch("Mee",    &Mee,    "Mee/F");  
        t->Branch("MTm",    &MTm,    "MTm/F");  
        t->Branch("MTe",    &MTe,    "MTe/F");  
        t->Branch("deta_wg",    &deta_wg,    "deta_wg/F");  
        t->Branch("dphi_wg",    &dphi_wg,    "dphi_wg/F");  

        t->Branch("e1x3Full5x5",        &e1x3Full5x5,        "e1x3Full5x5/F"); // disabled
        t->Branch("e2x5Full5x5",        &e2x5Full5x5,        "e2x5Full5x5/F"); // disabled

        t->Branch("jetY", &jetY, "jetY/F");

        if ( isMC )
        {
            t->Branch("jetGenJetY", &jetGenJetY, "jetGenJetY/F");
        }


        if ( isMC )
        {
        }


        t->Branch("photon_jetID", &photon_jetID, "photon_jetID/I");

        if ( !isMC )
        {
        }
     

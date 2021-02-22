#ifndef __READGGANALYSIS_H__
#define __READGGANALYSIS_H__
// you can only load ONE readBrahBrah.h in the analysis.
#include <vector>

    enum var{
        // bool
        isData,
        hasGoodVtx,

        // float
        pthat,
        genHT,
        genWeight,
        pfMET,
        pfMETPhi,
        rho,

        // float array
        mcPt,
        mcEta,
        mcPhi,
        mcE,
        mcMomPt,
        mcMomEta,
        mcMomPhi,
        jetGenJetPt,
        jetGenJetEn,
        jetGenJetEta,
        jetGenJetPhi,
        puTrue,
        mcCalIsoDR04,
        mcTrkIsoDR04,
        jetSubVtxPt,
        jetSubVtxMass,
        jetSubVtx3DVal,
        jetSubVtx3DErr,
        jetPt,
        jetEn,
        jetEta,
        jetPhi,
        jetJECUnc,
        jetNHF,
        jetNEF,
        jetCSV2BJetTags,
        jetDeepCSVTags_b,
        jetDeepCSVTags_bb,
        jetDeepCSVTags_c,
        jetDeepCSVTags_udsg,
        phoEta,
        phoPhi,
        phoEt,
        phoR9,
        phoSCEta,
        phoHoverE,
        phoPFChIso,
        phoPFNeuIso,
        phoPFPhoIso,
        phoSCRawE,
        phoSCEtaWidth,
        phoSCPhiWidth,
        phoESEnP1,
        phoESEnP2,
        phoESEffSigmaRR,
        phoPFChWorstIso,
        phoSigmaIEtaIEtaFull5x5,
        phoSigmaIEtaIPhiFull5x5,
        phoSigmaIPhiIPhiFull5x5,
        phoR9Full5x5,
        phoE2x2Full5x5,
        phoE5x5Full5x5,
        phoIDMVA,
        phoSeedEnergy,
        elePt,
        eleEta,
        elePhi,
        muPt,
        muEta,
        muPhi,

        // int
        run,
        nVtx,
        nPho,
        nJet,
        metFilters,
        nMC,
        nPUInfo,
        nEle,

        // int array
        mcPID,
        mcMomPID,
        mcGMomPID,
        puBX,
        jetSubVtxNtrks,
        jetPartonID,
        jetGenPartonID,
        jetHadFlvr,
        phoEleVeto,
        phohasPixelSeed,

        // Long64_t
        event,
        HLTPho,
        HLTPhoIsPrescaled,
        HLTEleMuX,


        // Long64_t array
        jetFiredTrgs,
        phoFiredSingleTrgs,


        // Short_t array
        mcStatusFlag,
        phoIDbit,

        // other
        jetPFLooseId,
        totVar
    };

    std::vector<const char*> branchesFromGGAnalysis={
        // bool
        "isData",
        "hasGoodVtx",

        // float
        "pthat",
        "genHT",
        "genWeight",
        "pfMET",
        "pfMETPhi",
        "rho",

        // float array
        "mcPt",
        "mcEta",
        "mcPhi",
        "mcE",
        "mcMomPt",
        "mcMomEta",
        "mcMomPhi",
        "jetGenJetPt",
        "jetGenJetEn",
        "jetGenJetEta",
        "jetGenJetPhi",
        "puTrue",
        "mcCalIsoDR04",
        "mcTrkIsoDR04",
        "jetSubVtxPt",
        "jetSubVtxMass",
        "jetSubVtx3DVal",
        "jetSubVtx3DErr",
        "jetPt",
        "jetEn",
        "jetEta",
        "jetPhi",
        "jetJECUnc",
        "jetNHF",
        "jetNEF",
        "jetCSV2BJetTags",
        "jetDeepCSVTags_b",
        "jetDeepCSVTags_bb",
        "jetDeepCSVTags_c",
        "jetDeepCSVTags_udsg",
        "phoEta",
        "phoPhi",
        "phoEt",
        "phoR9",
        "phoSCEta",
        "phoHoverE",
        "phoPFChIso",
        "phoPFNeuIso",
        "phoPFPhoIso",
        "phoSCRawE",
        "phoSCEtaWidth",
        "phoSCPhiWidth",
        "phoESEnP1",
        "phoESEnP2",
        "phoESEffSigmaRR",
        "phoPFChWorstIso",
        "phoSigmaIEtaIEtaFull5x5",
        "phoSigmaIEtaIPhiFull5x5",
        "phoSigmaIPhiIPhiFull5x5",
        "phoR9Full5x5",
        "phoE2x2Full5x5",
        "phoE5x5Full5x5",
        "phoIDMVA",
        "phoSeedEnergy",
        "elePt",
        "eleEta",
        "elePhi",
        "muPt",
        "muEta",
        "muPhi",

        // int
        "run",
        "nVtx",
        "nPho",
        "nJet",
        "metFilters",
        "nMC",
        "nPUInfo",
        "nEle",

        // int array
        "mcPID",
        "mcMomPID",
        "mcGMomPID",
        "puBX",
        "jetSubVtxNtrks",
        "jetPartonID",
        "jetGenPartonID",
        "jetHadFlvr",
        "phoEleVeto",
        "phohasPixelSeed",

        // Long64_t
        "event",
        "HLTPho",
        "HLTPhoIsPrescaled",
        "HLTEleMuX",


        // Long64_t array
        "jetFiredTrgs",
        "phoFiredSingleTrgs",


        // Short_t array
        "mcStatusFlag",
        "phoIDbit",

        // other
        "jetPFLooseId"
    };


//};
#endif

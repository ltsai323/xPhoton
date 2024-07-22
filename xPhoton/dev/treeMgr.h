#ifndef __TREEMGR_H__
#define __TREEMGR_H__
#include <memory.h>
#include "TTree.h"
#include "TDirectory.h"

#include "xPhoton/xPhoton/interface/readMgr.h"

#include "xPhoton/xPhoton/interface/LogMgr.h"
// note before tree content update


struct treeMgr
{
    void FillEvt();
    void Clean();
    void WriteTo(TDirectory* dir = nullptr );
    void Delete();

    explicit treeMgr(bool additionalinfo);
    // virtual ~treeMgr() {} // memset cannot be used if the class own virtual member

    TTree* BuildingTreeStructure(const std::string& name, bool isMC );
    bool _additionalInfo;


    TTree* t;

    Int_t nMC;
    Int_t run;
    Long64_t event;
    Bool_t isData;
    Long64_t HLT;
    Long64_t HLTIsPrescaled;
    Long64_t HLT50ns;
    Long64_t HLTIsPrescaled50ns;
    Long64_t phoFiredTrgs;
    Float_t pthat;
    Float_t genHT;
    Float_t mcPt;
    Float_t mcEta;
    Float_t mcPhi;
    Float_t mcCalIso04;
    Float_t mcTrkIso04;
    Float_t recoPt;
    Float_t recoEta;
    Float_t recoPhi;
    Float_t recoSCEta;
    Float_t r9;
    Int_t isMatched;
    Int_t isMatchedEle;
    Int_t isConverted;
    Int_t idLoose;
    Int_t idMedium;
    Int_t idTight;
    Int_t nVtx;
    Int_t nPU;
    Float_t puwei;
    Int_t eleVeto;
    Float_t HoverE;
    Float_t sieie;
    Float_t sieip;
    Float_t sipip;
    Float_t chIso;
    Float_t phoIso;
    Float_t nhIso;
    Float_t chIsoRaw;
    Float_t chWorstIsoRaw; // asdf renamed
    Float_t phoIsoRaw;
    Float_t nhIsoRaw;
    Float_t rho;
    Float_t e1x3;
    Float_t e2x2;
    Float_t e2x5;
    Float_t e5x5;
    Float_t rawE;
    Float_t scEtaWidth;
    Float_t scPhiWidth;
    Float_t esRR;
    Float_t esEn;
    Float_t mva;
    Float_t photonIDmva;
    Int_t phoIDbit;
    Float_t mva_hgg;
    Int_t HggPresel;
    Float_t Mmm;
    Float_t Mee;
    Float_t MET;
    Int_t metFilters;
    Float_t METPhi;
    Int_t phohasPixelSeed;
    Float_t MTm;
    Float_t MTe;
    Float_t deta_wg;
    Float_t dphi_wg;
    Float_t sieieFull5x5;
    Float_t sieipFull5x5;
    Float_t sipipFull5x5;
    Float_t e1x3Full5x5;
    Float_t r9Full5x5;
    Float_t e2x2Full5x5;
    Float_t e2x5Full5x5;
    Float_t e5x5Full5x5;
    Float_t jetPt;
    Float_t jetEta;
    Float_t jetPhi;
    Float_t jetY;
    Float_t jetJECUnc;
    Float_t jetGenJetPt;
    Float_t jetGenJetEta;
    Float_t jetGenJetPhi;
    Float_t jetGenJetY;
    Float_t jetCSV2BJetTags;
    Float_t jetDeepCSVTags_b;
    Float_t jetDeepCSVTags_bb;
    Float_t jetDeepCSVTags_c;
    Float_t jetDeepCSVTags_udsg;
    Int_t jetPartonID;
    Int_t jetGenPartonID;
    Int_t jetHadFlvr;
    Float_t jetSubVtxPt;
    Float_t jetSubVtxMass;
    Float_t jetSubVtx3DVal;
    Float_t jetSubVtx3DErr;
    Int_t jetSubVtxNtrks;
    Float_t xsweight;
    Int_t photon_jetID;
    Float_t SeedTime;
    Float_t SeedEnergy;
    Float_t MIPTotEnergy;
};

#endif

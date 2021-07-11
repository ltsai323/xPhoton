#ifndef __xElectrons_h__
#define __xElectrons_h__
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <TTree.h>
#include <TFile.h>


#define PASS_HLTBIT -1
#define BINNING 100
#define MASS_ELECTRON 0.511*0.001
#define MASS_Z 90
#define WINDOW_Z 40
// 0 : veto, 1 : loose, 2: medium, 3: tight
#define ELECTRONWORKINGPOINT 2
struct rec_Electron
{
    Float_t
        mcE,
        mcPt,
        mcEta,
        mcPhi,
        recoPt,
        recoEta,
        recoPhi;
    Float_t
        recoPtCalib,
        recoSCEta,
        r9,
        HoverE,
        chIsoRaw,
        phoIsoRaw,
        nhIsoRaw,
        chWorstIso,
        rawE,
        scEtaWidth,
        scPhiWidth,
        esRR,
        esEn,
        mva,
        mva_nocorr,
        officalIDmva,
        r9Full5x5,
        sieieFull5x5,
        sipipFull5x5,
        e2x2Full5x5,
        e2x5Full5x5;

    Int_t
        firedTrgs,
        isMatched;
    Long64_t
        firedTrgsL;
};
struct rec_Z
{
    Float_t
        mcE,
        mcPt,
        mcEta,
        mcPhi,
        recoE,
        recoPt,
        recoEta,
        recoPhi;

    Int_t
        isMatched;
};
struct rec_Event
{
    Int_t
        run,
        xsweight,
        puwei,
        pthat,
        MET,
        METPhi,
        nVtx,
        rho,
        nPU;

    Long64_t
        HLT,
        HLTPhoIsPrescaled,
        event;
};
void RegBranch( TTree* t, const char* name, rec_Electron* var )
{
    t->Branch(name, var, "mcE/F:mcPt/F:mcEta/F:mcPhi/F:recoPt/F:recoEta/F:recoPhi/F:recoPtCalib/F:recoSCEta/F:r9/F:HoverE/F:chIsoRaw/F:phoIsoRaw/F:nhIsoRaw/F:chWorstIso/F:rawE/F:scEtaWidth/F:scPhiWidth/F:esRR/F:esEn/F:mva/F:mva_nocorr/F:officalIDmva/F:r9Full5x5/F:sieieFull5x5/F:sipipFull5x5/F:e2x2Full5x5/F:e2x5Full5x5/F:firedTrgs/I:isMatched/I:firedTrgsL/L");
}
void RegBranch( TTree* t, const char* name, rec_Z* var )
{
    t->Branch(name, var, "mcE/F:mcPt/F:mcEta/F:mcPhi/F:recoE/F:recoPt/F:recoEta/F:recoPhi/F:isMatched/I");
}
void RegBranch( TTree* t, const char* name, rec_Event* var )
{
    t->Branch(name, var, "run/I:xsweight/I:puwei/I:pthat/I:MET/I:METPhi/I:nVtx/I:rho/F:nPU/I:HLT/L:HLTPhoIsPrescaled/L:event/L");
}


void xElectrons(
        std::vector<std::string> pathes,
        char oname[200]);

void xElectrons(std::string ipath, int outID);
#endif

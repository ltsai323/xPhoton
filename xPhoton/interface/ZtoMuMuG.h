#ifndef __ZtoMuMuG_h__
#define __ZtoMuMuG_h__
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <TTree.h>
#include <TFile.h>

#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/recoInfo.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#define BINNING 100
#define MASS_ELECTRON 0.511*0.001
#define MASS_MUON 0.105658
#define MASS_Z 90
#define WINDOW_Z 40
// 0 : veto, 1 : loose, 2: medium, 3: tight. Minus : Disable
#define ELECTRONWORKINGPOINT -1
struct rec_Electron
{
    Float_t
        mcPt,
        mcEta,
        recoPt,
        recoEta,
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
        sieipFull5x5,
        sipipFull5x5,
        s4Full5x5,
        esEnergyOverSCRawEnergy;
    Float_t
        scEtaWidth_corrected     ,
        scPhiWidth_corrected     ,
        r9Full5x5_corrected      ,
        s4Full5x5_corrected      ,
        sieieFull5x5_corrected   ,
        sieipFull5x5_corrected   ,
        esEnergyOverSCRawEnergy_corrected;

    Int_t
        recoIdx,
        idbit,
        isMatched;
    Long64_t
        firedTrgsL;
};
struct rec_Z
{
    Float_t
        mcPt,
        recoMass,
        recoPt,
        mumuMass,
        mumuPt;

    Int_t
        isMatched;
};
struct rec_Mu
{
    Float_t
        recoPt,
        recoEta,
        deltaR;
};
struct rec_Event
{
    Int_t
        run,
        xsweight,
        pthat,
        nVtx,
        nPU;
    Float_t
        rho,
        fixedGridRhoAll,
        MET,
        METPhi,
        puwei,
        genweight;

    Long64_t
        HLT,
        HLTPhoIsPrescaled,
        event;
};
std::vector<TLorentzCand> TriggeredDiMuon(TreeReader* dataptr);
std::vector<TLorentzCand> RecoPhoton(TreeReader* dataptr);
int                      FindMatchedIdx_Muon(TreeReader* dataptr, const TLorentzCand& recoCand);
void RegBranchZMuMu( TTree* t, const std::string& name, rec_Electron* var );
void RegBranchZMuMu( TTree* t, const std::string& name, rec_Z* var );
void RegBranchZMuMu( TTree* t, const std::string& name, rec_Mu* var );
void RegBranchZMuMu( TTree* t, const std::string& name, rec_Event* var );

#include <string.h>
template<typename T>
void ClearStruct(T* obj) { memset( obj, 0x00, sizeof(T) ); }


void ZtoMuMuG(
        std::vector<std::string> pathes,
        char oname[200]);

void ZtoMuMuG(std::string ipath, int outID);
#endif

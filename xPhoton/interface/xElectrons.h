#ifndef __xElectrons_h__
#define __xElectrons_h__
#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>

#include <TTree.h>
#include <TFile.h>

#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/recoInfo.h"
#define BINNING 100
#define MASS_ELECTRON 0.511*0.001
#define MASS_Z 90
#define WINDOW_Z 40
// 0 : veto, 1 : loose, 2: medium, 3: tight. Minus : Disable
#define ELECTRONWORKINGPOINT -1
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
        idbit,
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
        recoMass,
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
std::vector<TLorentzCand> RecoElectrons(TreeReader* dataptr);
std::vector<TLorentzCand> RecoElectronsInPhotonCollection_(TreeReader* dataptr);
TLorentzCand              TriggeredElectron(TreeReader* dataptr);
int                      FindMatchedIdx_Electron(TreeReader* dataptr, const TLorentzCand& recoCand);
bool PassElectronPreselection_(TreeReader* dataptr, int WP, const TLorentzCand& cand);
bool PassPhotonPreselection_(TreeReader* dataptr, const TLorentzCand& cand);
bool PassTagElePreselection_(TreeReader* dataptr, const TLorentzCand& cand);
void RegBranch( TTree* t, const std::string& name, rec_Electron* var );
void RegBranch( TTree* t, const std::string& name, rec_Z* var );
void RegBranch( TTree* t, const std::string& name, rec_Event* var );

#include <string.h>
template<typename T>
void ClearStruct(T* obj) { memset( obj, 0x00, sizeof(T) ); }


void xElectrons(
        std::vector<std::string> pathes,
        char oname[200]);

void xElectrons(std::string ipath, int outID);
#endif

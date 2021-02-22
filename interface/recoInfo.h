#ifndef __RECOINFO_H__
#define __RECOINFO_H__
#include "/home/ltsai/Work/github/xPhoton/interface/readContent_gganalysis.h"
#include "/home/ltsai/Work/github/xPhoton/interface/readMgr.h"
#include "/home/ltsai/Work/github/xPhoton/interface/PhotonSelections.h"
#include "/home/ltsai/Work/github/xPhoton/interface/logger.h"

#include <TLorentzVector.h>
#include <TMath.h>
#define NOCANDFOUND -999

namespace recoInfo
{
    struct pInfo {
        int idx;
        TLorentzVector fourmom;
        TLorentzVector P4() const { return fourmom; }
        int idxInEvt() const { return idx; }
        bool isZombie() const { return idx==NOCANDFOUND; }
        pInfo() { idx = NOCANDFOUND; }
    };
    struct TLorentzDATA : public TLorentzVector {
        int _idx;
        int idxInEvt() const { return _idx; }
        bool isZombie() const { return _idx == NOCANDFOUND; }
        TLorentzDATA() : TLorentzVector() { _idx = NOCANDFOUND; }
        TLorentzDATA(int idx) : TLorentzVector() { _idx = idx; }
    };



    bool JETPD_PHOTONHLT = false;
    bool ONLY_LEADINGPHOTON = false;
    bool doWmn = false;

    std::vector<TLorentzDATA> buildingCandidates_jet(readMgr* evtInfo, std::vector<int> candIdxs);
    std::vector<TLorentzDATA> buildingCandidates_photon(readMgr* evtInfo, std::vector<int> candIdxs);

    std::vector<int> evtIdxsPassingSelection_Jets  (readMgr* evtInfo);
    std::vector<int> evtIdxsPassingSelection_Photons(readMgr* evtInfo);
    std::vector<TLorentzDATA> selectedJets   (readMgr* evtInfo);
    std::vector<TLorentzDATA> selectedPhotons(readMgr* evtInfo);

    bool isEB(float eta) { return TMath::Abs(eta) < 1.4442; }
    bool isEE(float eta) { return TMath::Abs(eta) > 1.566 && TMath::Abs(eta) < 2.5; }
};
std::vector<recoInfo::TLorentzDATA> recoInfo::selectedJets(readMgr* evtInfo)
{
    Int_t nJet = evtInfo->Int(var::nJet);
    int triggeredIdx = -1;

    std::vector<int> jetIdxs;
    if(recoInfo::JETPD_PHOTONHLT)
        for(int ijet=0; ijet<nJet; ijet++)
            if(jetFiredTrgs!=0)
                jetIdxs.emplace_back(ijet);
    std::vector<recoInfo::TLorentzDATA> selCands = recoInfo::buildingCandidates_jet(evtInfo, jetIdxs);
    
    return selCands;
}
std::vector<int> recoInfo::evtIdxsPassingSelection_Jets(readMgr* evtInfo)
{
    LOG_DEBUG("algorithm to select preselected photons in event");
    std::vector<int> idxList;
    Long64_t* phoFiredTrgs = evtInfo->GetPtrLong64("phoFiredSingleTrgs");
    for ( Int_t i=0; i < evtInfo->Int(var::nPho); ++i )
        if ( PhotonPreselection(*evtInfo, i, kFALSE)!=1 && !phoFiredTrgs[i] )
            if ( !(recoInfo::JETPD_PHOTONHLT==0&&phoFiredTrgs[i]==0) ) // this must have problem! asdf
            //if ( recoInfo::JETPD_PHOTONHLT&&phoFiredTrgs[i]) )       // It MUST BE modified as this. 
                idxList.emplace_back(i);
    return idxList;
}
std::vector<int> recoInfo::evtIdxsPassingSelection_Photons(readMgr* evtInfo)
{
    LOG_DEBUG("algorithm to select preselected photons in event");
    std::vector<int> idxList;
    Long64_t* phoFiredTrgs = evtInfo->GetPtrLong64("phoFiredSingleTrgs");
    for ( Int_t i=0; i < evtInfo->Int(var::nPho); ++i )
        if ( PhotonPreselection(*evtInfo, i, kFALSE)!=1 && !phoFiredTrgs[i] )
            if ( !(recoInfo::JETPD_PHOTONHLT==0&&phoFiredTrgs[i]==0) ) // this must have problem! asdf
            //if ( recoInfo::JETPD_PHOTONHLT&&phoFiredTrgs[i]) )       // It MUST BE modified as this. 
                idxList.emplace_back(i);
    return idxList;
}

std::vector<recoInfo::TLorentzDATA> recoInfo::selectedPhotons(readMgr* evtInfo)
{
    LOG_DEBUG("algorithm to find selected photon");
    return recoInfo::buildingCandidates_photon(evtInfo, recoInfo::evtIdxsPassingSelection_Photons(evtInfo));
}
std::vector<recoInfo::TLorentzDATA> recoInfo::buildingCandidates_jet(readMgr* evtInfo, std::vector<int> candIdxs)
{
    LOG_DEBUG("building candidates...");
    std::vector<recoInfo::TLorentzDATA> cands;
    Float_t* jetPt  = evtInfo->PtrFloat(var::jetPt );
    Float_t* jetEta = evtInfo->PtrFloat(var::jetEta);
    Float_t* jetPhi = evtInfo->PtrFloat(var::jetPhi);
    Float_t* jetEn  = evtInfo->PtrFloat(var::jetEn );

    for ( int idx : candIdxs )
    {
        if ( idx == NOCANDFOUND ) continue;
        cands.emplace_back(idx);
        cands.back().SetPtEtaPhiE(
                evtInfo->PtrFloat(var::jetPt )[idx],
                evtInfo->PtrFloat(var::jetEta)[idx],
                evtInfo->PtrFloat(var::jetPhi)[idx],
                evtInfo->PtrFloat(var::jetEn )[idx]
                );
    }
    
    return cands;
}
std::vector<recoInfo::TLorentzDATA> recoInfo::buildingCandidates_photon(readMgr* evtInfo, std::vector<int> candIdxs)
{
    LOG_DEBUG("building candidates...");
    std::vector<recoInfo::TLorentzDATA> cands;
    Float_t* et  = evtInfo->PtrFloat(var::phoEt );
    Float_t* eta = evtInfo->PtrFloat(var::phoEta);
    Float_t* phi = evtInfo->PtrFloat(var::phoPhi);

    for ( int idx : candIdxs )
    {
        if ( idx == NOCANDFOUND ) continue;
        cands.emplace_back(idx);
        cands.back().SetPtEtaPhiM(
                evtInfo->PtrFloat(var::phoEt )[idx],
                evtInfo->PtrFloat(var::phoEta)[idx],
                evtInfo->PtrFloat(var::phoPhi)[idx],
                0.
                );
    }
    return cands;
}

// std::vector<int>  recoInfo::photonCandidateIdxs(readMgr* evtInfo)
// {
//     std::vector<int> photon_list;
//     Float_t* phoEt = evtInfo->PtrFloat(var::phoEt);
//     Float_t* phoSCEta= evtInfo->PtrFloat(var::phoSCEta);
//     Float_t* phoEta= evtInfo->PtrFloat(var::phoEta);
//     Float_t* phoPhi= evtInfo->PtrFloat(var::phoPhi);
//     Long64_t* phoFiredTrgs = evtInfo->GetPtrLong64("phoFiredSingleTrgs");
//     Bool_t isData = evtInfo->Bool(var::isData);
// 
//     for (Int_t i=0; i<evtInfo->Int(var::nPho); ++i)
//     {
//         if(phoEt[i]<15.) continue;       
//         if ( !recoInfo::isEE(phoEta[i]) && !recoInfo::isEB(phoEta[i]) ) continue;
//         if(isData==1 && recoInfo::JETPD_PHOTONHLT==0 && phoFiredTrgs==0) continue;
// 
//         TLorentzVector phoP4;
//         phoP4.SetPtEtaPhiM(phoEt[i], phoEta[i], phoPhi[i], 0.);
//         int pho_presel = 0;
//         // if(recoInfo::doWmn==1) pho_presel = PhotonPreselection(data, i, kFALSE);
//         // else pho_presel = PhotonPreselection(data, i, kTRUE);
//         pho_presel = PhotonPreselection(*evtInfo, i, kTRUE);
// 
// 
//         if(pho_presel!=1) continue;
//         // if(JETPD_PHOTONHLT==1 && phoP4.DeltaR(trigger_jetP4)<0.7) continue; // asdf Todo
//         photon_list.push_back(i); 
//         if(recoInfo::ONLY_LEADINGPHOTON && photon_list.size()==1) break;
//         //skim for TMVA training
//         //int pho_skim_presel = PhotonSkimPreselection(data, i, kTRUE);
//         //if(pho_skim_presel==1) photon_list.push_back(i);
//         // 	break;
// 
//     }   
//     return photon_list;
// }
#endif

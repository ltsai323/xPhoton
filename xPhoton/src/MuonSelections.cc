#include "xPhoton/xPhoton/interface/MuonSelections.h"

void TightMuons2015(TreeReader &data, std::vector<int> &accepted) {

  accepted.clear();

  Int_t  nMu         = data.GetInt("nMu");
  float* muPt        = data.GetPtrFloat("muPt");
  float* muEta       = data.GetPtrFloat("muEta");
  Int_t* muType      = data.GetPtrInt("muType");
  float* muChi2NDF   = data.GetPtrFloat("muChi2NDF");
  Int_t* muStations  = data.GetPtrInt("muStations");
  float* muD0        = data.GetPtrFloat("muD0");
  float* muDz        = data.GetPtrFloat("muDz");
  Int_t* muMuonHits  = data.GetPtrInt("muMuonHits");
  Int_t* muPixelHits = data.GetPtrInt("muPixelHits");
  Int_t* muTrkLayers = data.GetPtrInt("muTrkLayers");
  Int_t* muBit       = data.GetPtrInt("muIDbit");

// https://github.com/ltsai323/ggAnalysis/blob/106X/ggNtuplizer/plugins/ggNtuplizer_muons.cc
//    if (iMu->passed(reco::Muon::CutBasedIdLoose))        tmpmuIDbit += pow(2,  0);
//    if (iMu->passed(reco::Muon::CutBasedIdMedium))       tmpmuIDbit += pow(2,  1);
//    if (iMu->passed(reco::Muon::CutBasedIdMediumPrompt)) tmpmuIDbit += pow(2,  2);
//    if (iMu->passed(reco::Muon::CutBasedIdTight))        tmpmuIDbit += pow(2,  3);
//    if (iMu->passed(reco::Muon::CutBasedIdGlobalHighPt)) tmpmuIDbit += pow(2,  4);
//    if (iMu->passed(reco::Muon::CutBasedIdTrkHighPt))    tmpmuIDbit += pow(2,  5);
//    if (iMu->passed(reco::Muon::PFIsoVeryLoose))         tmpmuIDbit += pow(2,  6);
//    if (iMu->passed(reco::Muon::PFIsoLoose))             tmpmuIDbit += pow(2,  7);
//    if (iMu->passed(reco::Muon::PFIsoMedium))            tmpmuIDbit += pow(2,  8);
//    if (iMu->passed(reco::Muon::PFIsoTight))             tmpmuIDbit += pow(2,  9);
//    if (iMu->passed(reco::Muon::PFIsoVeryTight))         tmpmuIDbit += pow(2, 10);
//    if (iMu->passed(reco::Muon::TkIsoLoose))             tmpmuIDbit += pow(2, 11);
//    if (iMu->passed(reco::Muon::TkIsoTight))             tmpmuIDbit += pow(2, 12);
//    if (iMu->passed(reco::Muon::SoftCutBasedId))         tmpmuIDbit += pow(2, 13);
//    if (iMu->passed(reco::Muon::SoftMvaId))              tmpmuIDbit += pow(2, 14);
//    if (iMu->passed(reco::Muon::MvaLoose))               tmpmuIDbit += pow(2, 15);
//    if (iMu->passed(reco::Muon::MvaMedium))              tmpmuIDbit += pow(2, 16);
//    if (iMu->passed(reco::Muon::MvaTight))               tmpmuIDbit += pow(2, 17);
//    if (iMu->passed(reco::Muon::MiniIsoLoose))           tmpmuIDbit += pow(2, 18);
//    if (iMu->passed(reco::Muon::MiniIsoMedium))          tmpmuIDbit += pow(2, 19);
//    if (iMu->passed(reco::Muon::MiniIsoTight))           tmpmuIDbit += pow(2, 20);
//    if (iMu->passed(reco::Muon::MiniIsoVeryTight))       tmpmuIDbit += pow(2, 21);

  for (int i = 0; i < nMu; ++i) {
    if (muPt[i] < 20) continue;

    if (fabs(muEta[i]) > 2.4) continue;

    // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h
    // namely: GlobalMuon     = 1<<1
    //         TrackerMuon    = 1<<2
    //         StandAloneMuon = 1<<3
    //         CaloMuon       = 1<<4
    //         PFMuon         = 1<<5
    //         RPCMuon        = 1<<6
    if ((muType[i] >> 5 & 1) == 0 && (muType[i] >> 1 & 1) == 0) continue;
    
    if (muChi2NDF[i] > 10) continue;
    if (muMuonHits[i] == 0) continue;
    if (muStations[i] < 2) continue;	
    if (fabs(muD0[i]) > 0.2) continue;
    if (fabs(muDz[i]) > 0.5) continue;
    if (muPixelHits[i] == 0) continue;
    if (muTrkLayers[i] < 6) continue;
    if (!((muBit[i]>>0)&1) ) continue; // loose cut ID
    if (!((muBit[i]>>9)&1) ) continue; // tight pfIso

    accepted.push_back(i);
  }
  
}

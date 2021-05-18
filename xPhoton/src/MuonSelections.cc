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

    accepted.push_back(i);
  }
  
}

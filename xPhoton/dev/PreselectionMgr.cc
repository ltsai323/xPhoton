//#include "xPhoton/xPhoton/interface/PreselectionMgr.h"
#include "xPhoton/xPhoton/dev/PreselectionMgr.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"

bool PreselectionMgr::passed(int ID)
{ return ID==0; }

int PreselectionMgr::_ElectronID_CutBased_2015(TreeReader& data, Int_t WP, int idx)
{
   if (      data.GetPtrFloat("elePt"   )[idx]  < 15.    ) return 1;
   if (!usefulFuncs::isBarrel(data.GetPtrFloat("eleSCEta")[idx]) &&
       !usefulFuncs::isEndCap(data.GetPtrFloat("eleSCEta")[idx]) ) return 2;

   if (!(( (UShort_t*)data.GetPtrShort("eleIDbit") )[idx]>>WP&1) ) return 3;
   return 0;
}
int PreselectionMgr::_MuonID_Tight_2015(TreeReader& data, int idx)
{
    if (      data.GetPtrFloat("muPt"     )[idx]  < 20   ) return 1;
    if ( fabs(data.GetPtrFloat("muEta"    )[idx]) > 2.4  ) return 2;
        // muon types are defined here: CMSSW/DataFormats/MuonReco/interface/Muon.h
        // namely: GlobalMuon     = 1<<1
        //         TrackerMuon    = 1<<2
        //         StandAloneMuon = 1<<3
        //         CaloMuon       = 1<<4
        //         PFMuon         = 1<<5
        //         RPCMuon        = 1<<6
    if (    !(data.GetPtrInt("muType"     )[idx]>>5)&1 &&
            !(data.GetPtrInt("muType"     )[idx]>>1)&1  ) return 3;
    if (      data.GetPtrFloat("muChi2NDF")[idx]  > 10  ) return 4;
    if (      data.GetPtrInt("muMuonHits" )[idx]  == 0  ) return 5;
    if (      data.GetPtrInt("muStations" )[idx]  <  2  ) return 6;
    if ( fabs(data.GetPtrFloat("muD0"     )[idx]) > 0.2 ) return 7;
    if ( fabs(data.GetPtrFloat("muDz"     )[idx]) > 0.5 ) return 8;
    if (      data.GetPtrInt("muPixelHits")[idx]  == 0  ) return 9;
    if (      data.GetPtrInt("muTrkLayers")[idx]  <  6  ) return 10;
    return 0;
}
int PreselectionMgr::_PhotonID_CutBased_2015(TreeReader& data, int idx, bool eleVeto)
{
  if ( data.GetPtrFloat("phoEt"   )[idx] < 10          ) return 1;
  if ( data.GetPtrInt("phoEleVeto")[idx]==0 && eleVeto ) return 2;
  
  if      ( usefulFuncs::isBarrel(data.GetPtrFloat("phoSCEta")[idx]) )
  {
     if ( data.GetPtrFloat("phoPFChWorstIso"        )[idx] > 15. ) return  10;
     if ( data.GetPtrFloat("phoPFPhoIso"            )[idx] > 15. ) return  11;
     if ( data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[idx] > 0.015 ) return 12;
     if ( data.GetPtrFloat("phoHoverE"              )[idx] > 0.08  ) return 13;
  }
  else if ( usefulFuncs::isEndCap(data.GetPtrFloat("phoSCEta")[idx]) )
  {
     if ( data.GetPtrFloat("phoPFChWorstIso"        )[idx] > 15. ) return  10;
     if ( data.GetPtrFloat("phoPFPhoIso"            )[idx] > 15. ) return  11;
     if ( data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[idx] > 0.045 ) return 12;
     if ( data.GetPtrFloat("phoHoverE"              )[idx] > 0.05  ) return 13;
  }
  else return 4; // neither EB nor EE
  return 0;
}

std::vector<int> PreselectionMgr::GetElectrons(TreeReader& data, Int_t WP)
{
    std::vector<int> passedIdxs;
    for ( int i=0; i<data.GetInt("nEle"); ++i )
        if ( passed(_ElectronID_CutBased_2015(data, WP, i)) )
            passedIdxs.push_back(i);
    return passedIdxs;
}
std::vector<int> PreselectionMgr::GetElectronsVeto(TreeReader& data)
{ return GetElectrons(data,0); }
std::vector<int> PreselectionMgr::GetElectronsLoose(TreeReader& data)
{ return GetElectrons(data,1); }
std::vector<int> PreselectionMgr::GetElectronsMedium(TreeReader& data)
{ return GetElectrons(data,2); }
std::vector<int> PreselectionMgr::GetElectronsTight(TreeReader& data)
{ return GetElectrons(data,3); }


std::vector<int> PreselectionMgr::GetMuonsTight(TreeReader& data)
{
    std::vector<int> passedIdxs;
    for ( int i=0; i<data.GetInt("nMu"); ++i )
        if ( passed(_MuonID_Tight_2015(data,i)) )
            passedIdxs.push_back(i);
    return passedIdxs;
}
std::vector<int> PreselectionMgr::GetPhotons(TreeReader& data, bool eleVeto)
{
    std::vector<int> passedIdxs;
    for ( int i=0; i<data.GetInt("nPho"); ++i )
        if ( passed(_PhotonID_CutBased_2015(data, i, eleVeto)) )
            passedIdxs.push_back(i);
    return passedIdxs;
}

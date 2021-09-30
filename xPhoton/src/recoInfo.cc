#include "xPhoton/xPhoton/interface/recoInfo.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"

#include <TLorentzVector.h>
#include <TAxis.h>
#include <TMath.h>
#include <vector>
/*
int  TLorentzDATA::idx() const { return _idx; }
int  TLorentzDATA::charge() const { return _charge; }
bool TLorentzDATA::IsZombie() const { return _idx == NOCANDFOUND; }
     TLorentzDATA::TLorentzDATA() : TLorentzVector() { _idx = NOCANDFOUND; }
     TLorentzDATA::TLorentzDATA(int idx, int charge_) : TLorentzVector() { _idx = idx; _charge = charge_;}
     */
int  TLorentzCand::idx() const { return _idx; }
int  TLorentzCand::genidx() const { return _genidx; }
int  TLorentzCand::charge() const { return _charge; }
bool TLorentzCand::IsZombie() const { return _deadcand; }
     TLorentzCand::TLorentzCand() :
         TLorentzVector(), _idx(NOCANDFOUND),_genidx(-1),_charge(0),_deadcand(true)
{}
     TLorentzCand::TLorentzCand(int idx_, int charge_) :
         TLorentzVector(), _idx(idx_),_genidx(-1),_charge(charge_),_deadcand(false)
{}
     TLorentzCand::TLorentzCand(int idx_, int charge_, float pt_, float eta_, float phi_, float mass_) :
         TLorentzVector(), _idx(idx_),_genidx(-1),_charge(charge_),_deadcand(false)
{ this->SetPtEtaPhiM(pt_,eta_,phi_,mass_); }
TLorentzCand TLorentzCand::operator+(const TLorentzCand& cand_) const
{
    TLorentzCand sumup;
    TLorentzVector tmpP4 = TLorentzVector(*this) + TLorentzVector(cand_);

    sumup = tmpP4;
    sumup._charge = this->charge() + cand_.charge();
    sumup.adddaughter(*this);
    sumup.adddaughter(cand_);

    return sumup;
}
TLorentzCand TLorentzCand::operator=(const TLorentzVector& vec_)
{
    this->SetPtEtaPhiE(
            vec_.Pt(),
            vec_.Eta(),
            vec_.Phi(),
            vec_.E()
            );
    this->_deadcand=true;

    return *this;
}
TLorentzCand TLorentzCand::operator=(const TLorentzCand& vec_)
{
    this->SetPtEtaPhiE(
            vec_.Pt(),
            vec_.Eta(),
            vec_.Phi(),
            vec_.E()
            );
    this->_idx=             vec_._idx;
    this->_genidx=          vec_._genidx;
    this->_charge=          vec_._charge;
    this->_deadcand=        vec_._deadcand;
    this->_daughterCands=    vec_._daughterCands;

    return *this;
}

void TLorentzCand::SetAlive(bool stat) { _deadcand =!stat; }
void TLorentzCand::SetGenIdx(int idx) { _genidx = idx; }
void TLorentzCand::adddaughter( const TLorentzCand& d_ )
{ this->_daughterCands.push_back(d_); }
std::vector<TLorentzCand> TLorentzCand::daughters() const { return _daughterCands; }

     /*
void TLorentzCompCand::AddDaughter( const TLorentzCand& d_ ) { daugs.push_back(d_); }
bool TLorentzCompCand::IsZombie() const { return _deadcand; }
void TLorentzCompCand::SetAlive() { _deadcand = true; }
     //TLorentzCompCand::TLorentzCompCand() : TLorentzVector(), _deadcand(false) { }
     TLorentzCompCand::TLorentzCompCand() : TLorentzCand(), _deadcand(false) { }
     */
     //TLorentzCompCand::TLorentzCompCand(int idx, int charge_) : TLorentzVector() { _idx = idx; _charge = charge_;}
 std::map<int,TLorentzVector> recoInfo::PreselectedElectron_2016(TreeReader* data)
{
    int nEle = data->GetInt("nEle");
    
    Float_t* pt    = data->GetPtrFloat("");
    Float_t* eta   = data->GetPtrFloat("");
    Float_t* phi   = data->GetPtrFloat("");

    std::map<int,TLorentzVector> selectedElectrons;
    for ( int iEle = 0; iEle < nEle; ++iEle )
    {
        TLorentzVector particle;

        particle.SetPtEtaPhiM( pt[iEle], eta[iEle], phi[iEle], 0.511*0.001 );
        selectedElectrons[iEle] = particle;
    }
    return selectedElectrons;
}

/*
TLorentzCand recoInfo::BuildSelectedParticles( int idx, float pt, float eta, float phi, float mass, int charge )
{
    TLorentzCand particle(idx,charge);
    particle.SetPtEtaPhiM(pt,eta,phi,mass);
    return particle;
}
*/
bool recoInfo::ordering_pt(const TLorentzCand& cand1, const TLorentzCand& cand2)
{ return cand1.Pt() > cand2.Pt(); }
bool recoInfo::ordering_recopt( const std::pair<TLorentzCand,TLorentzCand>& candpair1, const std::pair<TLorentzCand,TLorentzCand>& candpair2 )
{ return candpair1.second.Pt() > candpair2.second.Pt(); }

bool recoInfo::InFiducialRegion(const TLorentzCand& cand_)
{
    float abseta = fabs(cand_.Eta());
    if ( abseta > 1.4442 && abseta < 1.566 ) return false;
    if ( abseta > 2.5 ) return false;
    if ( cand_.Pt() < 12 ) return false;
    return true;
}
bool recoInfo::ValidEtaRegion(float eta)
{
    float abseta = fabs(eta);
    if ( abseta > 1.4442 && abseta < 1.566 ) return false;
    if ( abseta > 2.5 ) return false;
    return true;
}
bool recoInfo::IsEE(float eta)
{
    if (!recoInfo::ValidEtaRegion(eta) ) throw std::range_error("intput eta is out of range\n");
    return fabs(eta) > 1.5; }
float recoInfo::CorrectedValue( TGraph* correctionFunc, float val )
{
    if ( correctionFunc )
        if ( val > correctionFunc->GetXaxis()->GetXmin() && val < correctionFunc->GetXaxis()->GetXmax() )
        {
            LOG_DEBUG("corrected value : before %.5f, after %.5f", val, correctionFunc->Eval(val) );
            return correctionFunc->Eval(val);
        }
    LOG_DEBUG("nothing corrected : return original value %.5f", val );
    return val;
}
/*
std::vector<recoInfo::TLorentzDATA> recoInfo::triggeredJets(readMgr* evtInfo, bool isGJetprocess=false)
{
    Int_t nJet = evtInfo->Int(var::nJet);
    Long64_t*   jetFiredTrgs = evtInfo->GetPtrLong64("jetFiredTrgs");      
    int triggeredIdx = -1;

    std::vector<int> jetIdxs;
    if( isGJetprocess )
        for(int ijet=0; ijet<nJet; ijet++)
            if(jetFiredTrgs[ijet])
                jetIdxs.emplace_back(ijet);
    std::vector<recoInfo::TLorentzDATA> selCands = recoInfo::buildingCandidates_jet(evtInfo, jetIdxs);
    
    return selCands;
}
std::vector<int> recoInfo::evtIdxsPassingSelection_Jets(readMgr* evtInfo)
{
    return {0};
}

recoInfo::TLorentzDATA recoInfo::triggeredJet(readMgr* evtInfo, bool isGJetprocess=false)
{
    Int_t nJet = evtInfo->Int(var::nJet);
    Long64_t*   jetFiredTrgs = evtInfo->GetPtrLong64("jetFiredTrgs");      

    if( isGJetprocess )
        for(int ijet=0; ijet<nJet; ijet++)
            if(jetFiredTrgs[ijet])
                return buildingCandidate_jet(evtInfo, ijet);
    return TLorentzDATA();
}
std::vector< recoInfo::TLorentzDATA> recoInfo::selectedJets_rejectphoton(readMgr* evtInfo, const TLorentzDATA& photon)
{
    vector<bool> &jetID             = *((vector<bool>*) evtInfo->GetPtr("jetPFLooseId"));
    std::vector<recoInfo::TLorentzDATA> selJet;
    float jetunc= 1.;
    for ( Int_t ijet = 0; ijet < evtInfo->Int(var::nJet); ++ijet )
    {
        recoInfo::TLorentzDATA iJet = recoInfo::buildingCandidate_jet(evtInfo, ijet);
        if ( TMath::Abs( iJet.Eta() ) > 2.4 ) continue;
        if ( iJet.Pt()*jetjecunc < 30. ) continue;
        if (!jetID[ijet] ) continue;
        if ( photon.DeltaR(iJet) < 0.4 ) continue;
        selJet.push_back(iJet);
    }
    return selJet;
}
std::vector<int> recoInfo::evtIdxsPassingSelection_Photons(readMgr* evtInfo, bool isGJetProcess=false)
{
    LOG_DEBUG("algorithm to find cut based selected photons in event");
    std::vector<int> idxList;
    Long64_t* phoFiredTrgs = evtInfo->GetPtrLong64("phoFiredSingleTrgs");
    for ( Int_t i=0; i < evtInfo->Int(var::nPho); ++i )
        if ( PhotonPreselection(*evtInfo, i, kFALSE)!=1 && !phoFiredTrgs[i] )
            // if ( !(recoInfo::JETPD_PHOTONHLT==0&&phoFiredTrgs[i]==0) ) // this must have problem! asdf
            if ( recoInfo::JETPD_PHOTONHLT||phoFiredTrgs[i] )
                idxList.emplace_back(i);
    return idxList;
}

std::vector<recoInfo::TLorentzDATA> recoInfo::selectedPhotons(readMgr* evtInfo)
{
    LOG_DEBUG("algorithm to find cut based selected photon");
    return recoInfo::buildingCandidates_photon(evtInfo, recoInfo::evtIdxsPassingSelection_Photons(evtInfo));
}
recoInfo::TLorentzDATA recoInfo::buildingCandidate_jet(readMgr* evtInfo, int idx)
{
    LOG_DEBUG("building candidates...");
    if ( idx == NOCANDFOUND ) continue;
    Float_t* jetPt  = evtInfo->PtrFloat(var::jetPt );
    Float_t* jetEta = evtInfo->PtrFloat(var::jetEta);
    Float_t* jetPhi = evtInfo->PtrFloat(var::jetPhi);
    Float_t* jetEn  = evtInfo->PtrFloat(var::jetEn );

    TLorentzDATA cand(idx);
    cand.SetPtEtaPhiE(
        evtInfo->PtrFloat(var::jetPt )[idx],
        evtInfo->PtrFloat(var::jetEta)[idx],
        evtInfo->PtrFloat(var::jetPhi)[idx],
        evtInfo->PtrFloat(var::jetEn )[idx]
    );
    
    return cand;
}
std::vector<recoInfo::TLorentzDATA> recoInfo::buildingCandidates_jet(readMgr* evtInfo, const std::vector<int>& candIdxs)
{
    LOG_DEBUG("building candidates...");
    std::vector<recoInfo::TLorentzDATA> cands;

    for ( int idx : candIdxs )
        cands.push_back( recoInfo::buildingCandidate_jet(evtInfo, idx) );
    
    return cands;
}
std::vector<recoInfo::TLorentzDATA> recoInfo::buildingCandidates_photon(readMgr* evtInfo, const std::vector<int>& candIdxs)
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
                et [idx],
                eta[idx],
                phi[idx],
                0.
                );
    }
    return cands;
}
std::vector<recoInfo::TLorentzDATA> recoInfo::buildingCandidates_electron(readMgr* evtInfo, const std::vector<int>& candIdxs)
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
                et [idx],
                eta[idx],
                phi[idx],
                0.511*0.001
                );
    }
    return cands;
}

std::vector<int> recoInfo::electronsInEvt(readMgr* evtInfo)
{
    std::vector<int> id;
    ElectronIDCutBased2015(*evtInfo, ELEIDENTIFICATION, id); //0 veto, 1 loose, 2 medium, 3 tight 
    return id;
}
std::vector<int> recoInfo::    muonsInEvt(readMgr* evtInfo)
{
    std::vector<int> id;
    TightMuons2015(*evtInfo, id);
    return id;
}

bool recoInfo::isElectron( readMgr* evtInfo, const recoInfo::TLorentzDATA& photon, const std::vector<recoInfo::TLorentzDATA>& electronpool )
{
    for ( const recoInfo::TLorentzDATA& electron : electronpool )
    {
        if(electron.Pt()<100.) continue;
        if(photon.DeltaR(electron) < 0.3) 
            return true;
    }
    return false;
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
bool recoInfo::isjetPhoton( readMgr* evtInfo, const recoInfo::TLorentzDATA& photon, const std::vector<recoInfo::TLorentzDATA>&jets )
{
    vector<bool> &jetID             = *((vector<bool>*) evtInfo->GetPtr("jetPFLooseId"));
    Float_t* jetNHF = evtInfo->GetPtrFloat("jetNHF");
    Float_t* jetNEF = evtInfo->GetPtrFloat("jetNEF");
    float jetjecunc = 1.;
    for ( const recoInfo::TLorentzDATA& jet : jets )
    {
        if ( TMath::Abs(jet.Eta() > 2.4) ) continue;
        if ( jet.Pt()*jetjecunc<30. ) continue;

        float ptratio = jet.Pt() / photon.Pt();
        if ( ptratio < 0.5 ) continue;
        if ( ptratio > 2.0 ) continue;
        if (!jetID [jet.idxInEvt()] ) continue;
        if ( jetNHF[jet.idxInEvt()] ) continue;
        if ( jetNEF[jet.idxInEvt()] ) continue;
        return true;
    }
    return false;
}
recoInfo::TLorentzDATA recoInfo::leadingJet( readMgr* evtInfo, const recoInfo::TLorentzDATA& photon, const std::vector<recoInfo::TLorentzDATA>&jets )
{
    vector<bool> &jetID             = *((vector<bool>*) evtInfo->GetPtr("jetPFLooseId"));
    float jetjecunc = 1.;
    for ( const recoInfo::TLorentzDATA& jet : jets )
    {
        if ( TMath::Abs(jet.Eta() > 2.4) ) continue;
        if ( jet.Pt()*jetjecunc   < 30.  ) continue;
        if (!jetID[jet.idxInEvt()]       ) continue;
        if ( photon.DeltaR(jet)   < 0.4  ) continue;
        return jet;
    }
    return recoInfo::TLorentzDATA();
}
*/

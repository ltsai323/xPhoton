#include "xPhoton/xPhoton/interface/xElectrons.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/recoInfo.h"
#include <TLorentzVector.h>
#include <map>

#define BINNING 100
#define MASS_ELECTRON 0.511*0.001
#define MASS_Z 90
#define WINDOW_Z 40

static std::map<const char*, TH1*> histMap;


std::vector<TLorentzCand> PreselectedElectrons(TreeReader* dataptr, int WP);
std::vector<TLorentzCand> matchedGenZee(TreeReader* dataptr, const TLorentzCand& ZCand_);
void xElectrons(
        std::vector<std::string> pathes,
        char oname[200] )
{
    TreeReader data(pathes);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");

    TTree *outtree_ = new TTree("t", "mini tree");
    
    rec_Electron ele1cand, ele2cand;
    rec_Z Zcand;
    rec_Event event;

    RegBranch( outtree_, "ele1", &ele1cand );
    RegBranch( outtree_, "ele2", &ele2cand );
    RegBranch( outtree_, "Z", &Zcand );
    RegBranch( outtree_, "Events", &event );

    histMap["DeltaR_GenZee"] = new TH1F("DeltaR_GenZee", "", BINNING, 0., 5.);
    histMap["DeltaR_GenEle"] = new TH1F("DeltaR_GenEle", "", BINNING, 0., 5.);

    /*
    std::map<int, Float_t > ele1CandF,ele2CandF, ZCandF;
    std::map<int, Float_t > ele1RecoF,ele2RecoF;
    std::map<int, Int_t   > ele1CandI,ele2CandI, ZCandI;
    std::map<int, Int_t   > ele1RecoI,ele2RecoI;
    std::map<int, Long64_t> ele1RecoL,ele2RecoL;
    std::map<int, Int_t   > eventI;
    std::map<int, Long64_t> eventL;

    // std::map<candF, Float_t > ele1CandF,ele2CandF, ZCandF;
    // std::map<recoF, Float_t > ele1RecoF,ele2RecoF;
    // std::map<recoI, Int_t   > ele1RecoI,ele2RecoI;
    // std::map<recoL, Long64_t> ele1RecoL,ele2RecoL;
    // std::map<evtI , Int_t   > eventI;
    // std::map<evtL , Long64_t> eventL;
    for ( int i=0; i<totCandF; ++i )
    { ele1CandF[i] = 0; ele2CandF[i] = 0; ZCandF[i] = 0; }
    for ( int i=0; i<totRecoF; ++i )
    { ele1RecoF[i] = 0; ele2RecoF[i] = 0; }
    for ( int i=0; i<totRecoI; ++i )
    { ele1RecoI[i] = 0; ele2RecoI[i] = 0; }
    for ( int i=0; i<totRecoL; ++i )
    { ele1RecoL[i] = 0; ele2RecoL[i] = 0; }
    for ( int i=0; i<totEvtI; ++i )
    { eventI[i] = 0; }
    for ( int i=0; i<totEvtL; ++i )
    { eventL[i] = 0; }




    // ele1
// candF
outtree_->Branch("ele1.mcE",&ele1CandF[candF::mcE],"ele1.mcE/F");
outtree_->Branch("ele1.mcPt",&ele1CandF[candF::mcPt],"ele1.mcPt/F");
outtree_->Branch("ele1.mcEta",&ele1CandF[candF::mcEta],"ele1.mcEta/F");
outtree_->Branch("ele1.mcPhi",&ele1CandF[candF::mcPhi],"ele1.mcPhi/F");
outtree_->Branch("ele1.recoE",&ele1CandF[candF::recoE],"ele1.recoE/F");
outtree_->Branch("ele1.recoPt",&ele1CandF[candF::recoPt],"ele1.recoPt/F");
outtree_->Branch("ele1.recoEta",&ele1CandF[candF::recoEta],"ele1.recoEta/F");
outtree_->Branch("ele1.recoPhi",&ele1CandF[candF::recoPhi],"ele1.recoPhi/F");
// recoF
outtree_->Branch("ele1.recoPtCalib",&ele1RecoF[recoF::recoPtCalib],"ele1.recoPtCalib/F");
outtree_->Branch("ele1.recoSCEta",&ele1RecoF[recoF::recoSCEta],"ele1.recoSCEta/F");
outtree_->Branch("ele1.r9",&ele1RecoF[recoF::r9],"ele1.r9/F");
outtree_->Branch("ele1.HoverE",&ele1RecoF[recoF::HoverE],"ele1.HoverE/F");
outtree_->Branch("ele1.chIsoRaw",&ele1RecoF[recoF::chIsoRaw],"ele1.chIsoRaw/F");
outtree_->Branch("ele1.phoIsoRaw",&ele1RecoF[recoF::phoIsoRaw],"ele1.phoIsoRaw/F");
outtree_->Branch("ele1.nhIsoRaw",&ele1RecoF[recoF::nhIsoRaw],"ele1.nhIsoRaw/F");
outtree_->Branch("ele1.chWorstIso",&ele1RecoF[recoF::chWorstIso],"ele1.chWorstIso/F");
outtree_->Branch("ele1.rho",&ele1RecoF[recoF::rho],"ele1.rho/F");
outtree_->Branch("ele1.rawE",&ele1RecoF[recoF::rawE],"ele1.rawE/F");
outtree_->Branch("ele1.scEtaWidth",&ele1RecoF[recoF::scEtaWidth],"ele1.scEtaWidth/F");
outtree_->Branch("ele1.scPhiWidth",&ele1RecoF[recoF::scPhiWidth],"ele1.scPhiWidth/F");
outtree_->Branch("ele1.esRR",&ele1RecoF[recoF::esRR],"ele1.esRR/F");
outtree_->Branch("ele1.esEn",&ele1RecoF[recoF::esEn],"ele1.esEn/F");
outtree_->Branch("ele1.mva",&ele1RecoF[recoF::mva],"ele1.mva/F");
outtree_->Branch("ele1.mva_nocorr",&ele1RecoF[recoF::mva_nocorr],"ele1.mva_nocorr/F");
outtree_->Branch("ele1.officalIDmva",&ele1RecoF[recoF::officalIDmva],"ele1.officalIDmva/F");
outtree_->Branch("ele1.r9Full5x5",&ele1RecoF[recoF::r9Full5x5],"ele1.r9Full5x5/F");
outtree_->Branch("ele1.sieieFull5x5",&ele1RecoF[recoF::sieieFull5x5],"ele1.sieieFull5x5/F");
outtree_->Branch("ele1.sieipFull5x5",&ele1RecoF[recoF::sieipFull5x5],"ele1.sieipFull5x5/F");
outtree_->Branch("ele1.sipipFull5x5",&ele1RecoF[recoF::sipipFull5x5],"ele1.sipipFull5x5/F");
outtree_->Branch("ele1.e2x2Full5x5",&ele1RecoF[recoF::e2x2Full5x5],"ele1.e2x2Full5x5/F");
outtree_->Branch("ele1.e2x5Full5x5",&ele1RecoF[recoF::e2x5Full5x5],"ele1.e2x5Full5x5/F");
// candI
outtree_->Branch("ele1.isMatched",&ele1CandI[candI::isMatched],"ele1.isMatched/I");
// recoI
outtree_->Branch("ele1.firedTrgs",&ele1RecoI[recoI::firedTrgs],"ele1.firedTrgs/I");
outtree_->Branch("ele1.hasPixelSeed",&ele1RecoI[recoI::hasPixelSeed],"ele1.hasPixelSeed/I");
outtree_->Branch("ele1.IDbits",&ele1RecoI[recoI::IDbits],"ele1.IDbits/I");
// recoL
outtree_->Branch("ele1.firedTrgsL", &ele1RecoL[recoL::firedTrgsL],"ele1.firedTrgsL/L");

    //ele2
// candF
outtree_->Branch("ele2.mcE",&ele2CandF[candF::mcE],"ele2.mcE/F");
outtree_->Branch("ele2.mcPt",&ele2CandF[candF::mcPt],"ele2.mcPt/F");
outtree_->Branch("ele2.mcEta",&ele2CandF[candF::mcEta],"ele2.mcEta/F");
outtree_->Branch("ele2.mcPhi",&ele2CandF[candF::mcPhi],"ele2.mcPhi/F");
outtree_->Branch("ele2.recoE",&ele2CandF[candF::recoE],"ele2.recoE/F");
outtree_->Branch("ele2.recoPt",&ele2CandF[candF::recoPt],"ele2.recoPt/F");
outtree_->Branch("ele2.recoEta",&ele2CandF[candF::recoEta],"ele2.recoEta/F");
outtree_->Branch("ele2.recoPhi",&ele2CandF[candF::recoPhi],"ele2.recoPhi/F");
// recoF
outtree_->Branch("ele2.recoPtCalib",&ele2RecoF[recoF::recoPtCalib],"ele2.recoPtCalib/F");
outtree_->Branch("ele2.recoSCEta",&ele2RecoF[recoF::recoSCEta],"ele2.recoSCEta/F");
outtree_->Branch("ele2.r9",&ele2RecoF[recoF::r9],"ele2.r9/F");
outtree_->Branch("ele2.HoverE",&ele2RecoF[recoF::HoverE],"ele2.HoverE/F");
outtree_->Branch("ele2.chIsoRaw",&ele2RecoF[recoF::chIsoRaw],"ele2.chIsoRaw/F");
outtree_->Branch("ele2.phoIsoRaw",&ele2RecoF[recoF::phoIsoRaw],"ele2.phoIsoRaw/F");
outtree_->Branch("ele2.nhIsoRaw",&ele2RecoF[recoF::nhIsoRaw],"ele2.nhIsoRaw/F");
outtree_->Branch("ele2.chWorstIso",&ele2RecoF[recoF::chWorstIso],"ele2.chWorstIso/F");
outtree_->Branch("ele2.rho",&ele2RecoF[recoF::rho],"ele2.rho/F");
outtree_->Branch("ele2.rawE",&ele2RecoF[recoF::rawE],"ele2.rawE/F");
outtree_->Branch("ele2.scEtaWidth",&ele2RecoF[recoF::scEtaWidth],"ele2.scEtaWidth/F");
outtree_->Branch("ele2.scPhiWidth",&ele2RecoF[recoF::scPhiWidth],"ele2.scPhiWidth/F");
outtree_->Branch("ele2.esRR",&ele2RecoF[recoF::esRR],"ele2.esRR/F");
outtree_->Branch("ele2.esEn",&ele2RecoF[recoF::esEn],"ele2.esEn/F");
outtree_->Branch("ele2.mva",&ele2RecoF[recoF::mva],"ele2.mva/F");
outtree_->Branch("ele2.mva_nocorr",&ele2RecoF[recoF::mva_nocorr],"ele2.mva_nocorr/F");
outtree_->Branch("ele2.officalIDmva",&ele2RecoF[recoF::officalIDmva],"ele2.officalIDmva/F");
outtree_->Branch("ele2.r9Full5x5",&ele2RecoF[recoF::r9Full5x5],"ele2.r9Full5x5/F");
outtree_->Branch("ele2.sieieFull5x5",&ele2RecoF[recoF::sieieFull5x5],"ele2.sieieFull5x5/F");
outtree_->Branch("ele2.sieipFull5x5",&ele2RecoF[recoF::sieipFull5x5],"ele2.sieipFull5x5/F");
outtree_->Branch("ele2.sipipFull5x5",&ele2RecoF[recoF::sipipFull5x5],"ele2.sipipFull5x5/F");
outtree_->Branch("ele2.e2x2Full5x5",&ele2RecoF[recoF::e2x2Full5x5],"ele2.e2x2Full5x5/F");
outtree_->Branch("ele2.e2x5Full5x5",&ele2RecoF[recoF::e2x5Full5x5],"ele2.e2x5Full5x5/F");
// candI
outtree_->Branch("ele2.isMatched",&ele2CandI[candI::isMatched],"ele2.isMatched/I");
// recoI
outtree_->Branch("ele2.firedTrgs",&ele2RecoI[recoI::firedTrgs],"ele2.firedTrgs/I");
outtree_->Branch("ele2.hasPixelSeed",&ele2RecoI[recoI::hasPixelSeed],"ele2.hasPixelSeed/I");
outtree_->Branch("ele2.IDbits",&ele2RecoI[recoI::IDbits],"ele2.IDbits/I");
// recoL
outtree_->Branch("ele2.firedTrgsL", &ele2RecoL[recoL::firedTrgsL],"ele2.firedTrgsL/L");

// ele2 end

// Z
// candF
outtree_->Branch("Z.mcE",&ZCandF[candF::mcE],"Z.mcE/F");
outtree_->Branch("Z.mcPt",&ZCandF[candF::mcPt],"Z.mcPt/F");
outtree_->Branch("Z.mcEta",&ZCandF[candF::mcEta],"Z.mcEta/F");
outtree_->Branch("Z.mcPhi",&ZCandF[candF::mcPhi],"Z.mcPhi/F");
outtree_->Branch("Z.recoE",&ZCandF[candF::recoE],"Z.recoE/F");
outtree_->Branch("Z.recoPt",&ZCandF[candF::recoPt],"Z.recoPt/F");
outtree_->Branch("Z.recoEta",&ZCandF[candF::recoEta],"Z.recoEta/F");
outtree_->Branch("Z.recoPhi",&ZCandF[candF::recoPhi],"Z.recoPhi/F");
outtree_->Branch("Z.recoPhi",&ZCandF[candF::recoPhi],"Z.recoPhi/F");
// candI
outtree_->Branch("Z.isMatched",&ZCandI[candI::isMatched],"Z.isMatched/I");


// evt
// evtI
outtree_->Branch("evt.Run",&eventI[evtI::Run],"evt.Run/I");
outtree_->Branch("evt.xsweight",&eventI[evtI::xsweight],"evt.xsweight/I");
outtree_->Branch("evt.puwei",&eventI[evtI::puwei],"evt.puwei/I");
outtree_->Branch("evt.pthat",&eventI[evtI::pthat],"evt.pthat/I");
outtree_->Branch("evt.MET",&eventI[evtI::MET],"evt.MET/I");
outtree_->Branch("evt.METPhi",&eventI[evtI::METPhi],"evt.METPhi/I");
outtree_->Branch("evt.nVtx",&eventI[evtI::nVtx],"evt.nVtx/I");
outtree_->Branch("evt.nPU",&eventI[evtI::nPU],"evt.nPU/I");

// evtL
outtree_->Branch("evt.HLT",&eventL[evtL::HLT],"evt.HLT/L");
outtree_->Branch("evt.HLTPhoIsPrescaled",&eventL[evtL::HLTPhoIsPrescaled],"evt.HLTPhoIsPrescaled/L");
outtree_->Branch("evt.event",&eventL[evtL::event],"evt.event/L");

*/





    
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        // 1. load data
        // 2. build electron 4mom and pass electron preselection (and HLT)
        // 3. build Z candidate and reject event.
        // 4. mc truth matching.
        // 5. fill tree
        // 6. mva
        data.GetEntry(ev);
        std::vector<TLorentzCand> selelectrons = PreselectedElectrons(&data, 0);
        
        if ( selelectrons.size() < 2 ) continue;


        TLorentzCand ZcandP4;
        for ( int idx=0; idx<selelectrons.size(); ++idx )
            for ( int jdx=idx+1; jdx<selelectrons.size(); ++jdx )
            {
                const TLorentzCand& ele1 = selelectrons.at(idx);
                const TLorentzCand& ele2 = selelectrons.at(jdx);
                int TIGHTID = 0;
                if ( (( (UShort_t*)data.GetPtrShort("eleIDbit") )[ele1.idx()]>>TIGHTID)&1 == 0 ) continue; // tight ID for tag photon.
                // need to check the validation
                /* asdf
                if ( ( (UShort_t*)data.GetPtrShort("eleIDbit") )[ele1.idx()] & 1<<TIGHTID == 0 ) continue; // tight ID for tag photon.
                */
                if ( ele1.charge() * ele2.charge() > 0 ) continue;
                ZcandP4 = ele1+ele2;
                if ( ZcandP4.M() <  MASS_Z-WINDOW_Z || ZcandP4.M() > MASS_Z+WINDOW_Z ) continue;
                ZcandP4.SetAlive();
                break;
            }

        if ( ZcandP4.IsZombie() ) continue;
        
        // MC truth matching

        matchedGenZee(&data, ZcandP4);






        Int_t nEle = data.GetInt("nEle");
        Int_t* eleCharge = data.GetPtrInt("eleCharge");
        Float_t* elePt = data.GetPtrFloat("elePt");
        Float_t* eleEta = data.GetPtrFloat("eleEta");
        Float_t* elePhi = data.GetPtrFloat("elePhi");
        Float_t* eleR9  = data.GetPtrFloat("eleR9");
        Float_t* eleCalibPt = data.GetPtrFloat("eleCalibPt");
        Float_t* eleCalibEta = data.GetPtrFloat("eleCalibEta");
        /*
        Float_t* 
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        Float_t*
        */
        


        std::map<int, TLorentzVector> electrons = recoInfo::PreselectedElectron_2016(&data);
        for ( int eleIdx1 = 0; eleIdx1 < nEle; ++eleIdx1 )
        {
            continue;
        }
        



        outtree_->Fill();
    }


    fout_->cd();
    outtree_->Write();
    for ( auto iter = histMap.begin(); iter != histMap.end(); ++iter ) iter->second->Write();
    fout_->Close();
    for ( auto iter = histMap.begin(); iter != histMap.end(); ++iter ) delete iter->second;
    LOG_INFO("All %lld Events processed", data.GetEntriesFast());
}
void xElectrons(std::string ipath, int outID)
{
   char fname[200];
   std::vector<std::string> pathes;

   pathes.push_back(ipath);

   char oname[200];
   sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

   xElectrons(pathes, oname);
}

std::vector<TLorentzCand> PreselectedElectrons(TreeReader* dataptr, int WP)
{
    std::vector<int> selParticleIdxs;
    
    Int_t Size = dataptr->GetInt("nEle");
    Int_t* charge = dataptr->GetPtrInt("eleCharge");
    Float_t* pt = dataptr->GetPtrFloat("elePt");
    Float_t* eta = dataptr->GetPtrFloat("eleSCEta");
    Float_t* phi = dataptr->GetPtrFloat("eleSCPhi");
    UShort_t* idbit = (UShort_t*)dataptr->GetPtrShort("eleIDbit");
    for ( int i = 0; i < Size; ++i )
    {
        if ( pt[i] < 15. ) continue;
        float abseta = fabs(eta[i]);
        if ( abseta > 2.5 ) continue;
        if ( abseta > 1.4442 && abseta < 1.566 ) continue;
        if (!((idbit[i] >> WP) & 1) ) continue;
        selParticleIdxs.push_back(i);
    }

    std::vector<TLorentzCand> outputs;
    for ( int idx : selParticleIdxs )
        outputs.emplace_back( recoInfo::BuildSelectedParticles(idx, pt[idx], eta[idx], phi[idx], MASS_ELECTRON, charge[idx]) );
    return outputs;
}
std::vector<TLorentzCand> matchedGenZee(TreeReader* dataptr, const TLorentzCand& ZCand_)
{
    #define DELTARCUT 0.4
    #define FINALSTATE_STATUSCUT 3
    #define PID_Z 23
    #define PID_ELECTRON 11
    
    if (!dataptr->HasMC() ) return std::vector<TLorentzCand>();

    Int_t  nMC_         = dataptr->GetInt("nMC");
    Int_t* mcPID_       = dataptr->GetPtrInt("mcPID");
    Int_t* mcMomPID_    = dataptr->GetPtrInt("mcMomPID");
    Int_t* mcStatus_    = dataptr->GetPtrInt("mcStatus");



    std::vector<Int_t> genElectronIdxs;
    std::vector<Int_t> genZElectronIdxs;
    for ( Int_t iMC = 0; iMC < nMC_; ++iMC )
        if ( fabs(mcPID_[iMC]) == PID_ELECTRON && mcStatus_[iMC] <= FINALSTATE_STATUSCUT )
        {
            genElectronIdxs.emplace_back(iMC);
            if ( mcMomPID_[iMC] == PID_Z )
                genZElectronIdxs.emplace_back(iMC);
        }
    
    Float_t* pt_        = dataptr->GetPtrFloat("elePt");
    Float_t* eta_       = dataptr->GetPtrFloat("eleEta");
    Float_t* phi_       = dataptr->GetPtrFloat("elePhi");
    Int_t  * charge_    = dataptr->GetPtrInt("eleCharge");
    Float_t* genpt_     = dataptr->GetPtrFloat("mcPt");
    Float_t* geneta_    = dataptr->GetPtrFloat("mcEta");
    Float_t* genphi_    = dataptr->GetPtrFloat("mcPhi");
    


    TLorentzCand recoEle0( ZCand_.daughters().at(0), charge_[ZCand_.daughters().at(0)] );
    TLorentzCand recoEle1( ZCand_.daughters().at(1), charge_[ZCand_.daughters().at(1)] );
    recoEle0.SetPtEtaPhiM(pt_[ZCand_.daughters().at(0)], eta_[ZCand_.daughters().at(0)], phi_[ZCand_.daughters().at(0)], MASS_ELECTRON );
    recoEle1.SetPtEtaPhiM(pt_[ZCand_.daughters().at(1)], eta_[ZCand_.daughters().at(1)], phi_[ZCand_.daughters().at(1)], MASS_ELECTRON );
    
    bool matched_signal = false;
    bool matched_background = false;
    for ( Int_t geleIdx0 : genZElectronIdxs )
        for ( Int_t geleIdx1 : genZElectronIdxs )
        {
            if ( genpt_[geleIdx0] < genpt_[geleIdx1] ) continue;
            if ( mcMomPID_[geleIdx0] != mcMomPID_[geleIdx1] ) continue;
            TLorentzCand genEle0(geleIdx0, mcPID_[geleIdx0] > 0 ? -0 : 0 );
            TLorentzCand genEle1(geleIdx1, mcPID_[geleIdx1] > 0 ? -0 : 0 );
            genEle0.SetPtEtaPhiM(genpt_[geleIdx0], geneta_[geleIdx0], genphi_[geleIdx0], MASS_ELECTRON );
            genEle1.SetPtEtaPhiM(genpt_[geleIdx1], geneta_[geleIdx1], genphi_[geleIdx1], MASS_ELECTRON );

            if ( genEle0.charge() != recoEle0.charge() || genEle1.charge() != recoEle1.charge() ) continue;
            double deltaR0 = genEle0.DeltaR(recoEle0);
            double deltaR1 = genEle1.DeltaR(recoEle1);
            if ( deltaR0 < DELTARCUT && deltaR1 < DELTARCUT )
                matched_signal = true;
        }
    if ( matched_signal ) return std::vector<TLorentzCand>();
    for ( Int_t geleIdx0 : genElectronIdxs )
        for ( Int_t geleIdx1 : genElectronIdxs )
        {
            if ( genpt_[geleIdx0] < genpt_[geleIdx1] ) continue;
            if ( mcMomPID_[geleIdx0] != mcMomPID_[geleIdx1] ) continue;
            TLorentzCand genEle0(geleIdx0, mcPID_[geleIdx0] > 0 ? -0 : 0 );
            TLorentzCand genEle1(geleIdx1, mcPID_[geleIdx1] > 0 ? -0 : 0 );
            genEle0.SetPtEtaPhiM(genpt_[geleIdx0], geneta_[geleIdx0], genphi_[geleIdx0], MASS_ELECTRON );
            genEle1.SetPtEtaPhiM(genpt_[geleIdx1], geneta_[geleIdx1], genphi_[geleIdx1], MASS_ELECTRON );

            if ( genEle0.charge() != recoEle0.charge() || genEle1.charge() != recoEle1.charge() ) continue;
            double deltaR0 = genEle0.DeltaR(recoEle0);
            double deltaR1 = genEle1.DeltaR(recoEle1);
            if ( deltaR0 < DELTARCUT && deltaR1 < DELTARCUT )
                matched_background = true;
        }
    

    return std::vector<TLorentzCand>();
}

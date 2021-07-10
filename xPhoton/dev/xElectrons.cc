#include "xPhoton/xPhoton/interface/xElectrons.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/recoInfo.h"
#include "xPhoton/xPhoton/interface/histMgr.h"
#include <TLorentzVector.h>
#include <map>

static histMgr hists;



std::vector<TLorentzCand> MCmatchedZElectronPair(TreeReader* dataptr);
bool PassElectronPreselection(TreeReader* dataptr, int WP, const TLorentzCand& cand);
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
    
    rec_Electron elecand[2];
    rec_Z Zcand;
    rec_Event event;

    //RegBranch( outtree_, "electron0", &ele0cand );
    //RegBranch( outtree_, "electron1", &ele1cand );
    RegBranch( outtree_, "electron0", &elecand[0] );
    RegBranch( outtree_, "electron1", &elecand[1] );
    RegBranch( outtree_, "Z", &Zcand );
    RegBranch( outtree_, "Events", &event );

    
    // check the reason why event failed
    // 0: all event record in ROOT file
    // 1: passed if the preselected electrons >= 2
    // 2: passed if Z->ee candidate found
    hists.Create("eventStat", 3.,0.,3.);

    // preselection cut applied for select electron candidate
    // 0: number of electron in event.
    // 1: electron pt > 12
    // 2: |eta| < 2.5
    // 3: eta is not in barrel - endcap gap.
    // 4: pass electron id bit in data
    hists.Create("elePreselectStat", 5., 0., 5.);

    // number of electron selected.
    hists.Create("Nele", 4,0.,4.);

    // Filling condition to reconstruct Z->ee channel.
    // 0: number of electron pairs
    // 1: pass HLT in data
    // 2: electron pair with opposite charge
    // 3: Z candidate mass = [ 90-40, 90+40 ]
    hists.Create("ZRecoStat", 4, 0., 4.);

    // matched electrons in each event.
    // -1: the total number of events.
    //  n: n electrons matched in each event.
    hists.Create("nEleMatched", 6, -1, 5);

    // number of signal gen electron
    hists.Create("nGenEle", 6, -1, 5);
    hists.Create("DeltaR", BINNING, 0., 0.10);
    hists.Create("ptratio", BINNING, 0., 2.0);



    
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        // 1. load data
        // 2. build electron 4mom and pass electron preselection (and HLT)
        // 3. build Z candidate and reject event.
        // 4. mc truth matching.
        // 5. fill tree
        // 6. mva
        data.GetEntry(ev);

        std::vector<TLorentzCand> matchedRes = MCmatchedZElectronPair(&data);
        std::vector<TLorentzCand> selelectrons = PreselectedElectrons(&data, ELECTRONWORKINGPOINT);
        hists.FillStatus("eventStat", 0);
        
        hists.Fill("Nele", selelectrons.size() );
        if ( selelectrons.size() < 2 ) continue;

        hists.FillStatus("eventStat", 1);

        TLorentzCand ZcandP4;
        for ( int idx=0; idx<selelectrons.size(); ++idx )
        {
            for ( int jdx=idx+1; jdx<selelectrons.size(); ++jdx )
            {
                const TLorentzCand& ele0 = selelectrons.at(idx);
                const TLorentzCand& ele1 = selelectrons.at(jdx);
                if (!data.HasMC() )
                {
                    if ( ( (ULong64_t*)data.GetPtrLong64("eleFiredDoubleTrgs") )[ele0.idx()] == 0 ) continue; // nothing triggered.
                            
                    if ( PASS_HLTBIT > 0 ) // although ULong64_t used. but only 0~31 bits recorded in ROOT. bit larger than 31 is useless.
                    {
                        int bit = PASS_HLTBIT;
                        if ( (( (ULong64_t*)data.GetPtrLong64("eleFiredDoubleTrgs") )[ele0.idx()]>>bit)&1 == 0 ) continue; // tight ID for tag photon.
                        // need to check the validation
                        /* asdf
                        if ( ( (UShort_t*)data.GetPtrShort("eleIDbit") )[ele0.idx()] & 1<<bit == 0 ) continue; // tight ID for tag photon.
                        */
                    }
                }
                hists.FillStatus("ZRecoStat", 0);
                hists.FillStatus("ZRecoStat", 1);

                if ( ele0.charge() * ele1.charge() > 0 ) continue;
                hists.FillStatus("ZRecoStat", 2);
                ZcandP4 = ele0+ele1;
                if ( ZcandP4.M() <  MASS_Z-WINDOW_Z || ZcandP4.M() > MASS_Z+WINDOW_Z ) continue;
                hists.FillStatus("ZRecoStat", 3);
                ZcandP4.SetAlive();
                break;
            }
            if (!ZcandP4.IsZombie() ) break;
        }

        if ( ZcandP4.IsZombie() ) continue;
        hists.FillStatus("eventStat", 2);
        LOG_DEBUG("Z candidate found, owning %d electrons", ZcandP4.daughters().size());
        
        // MC truth matching

        std::vector<TLorentzCand> matchedElectrons = matchedGenZee(&data, ZcandP4);
        LOG_DEBUG("MC matched %d", matchedElectrons.size());
        if ( matchedElectrons.size() ) hists.FillStatus("ZRecoStat",4);

        



        // filling events
        
        //for ( int i = 0; i < 2; ++i )
            
        /*
        {
        }
        
        Int_t* eleCharge = data.GetPtrInt("eleCharge");
        Float_t* elePt = data.GetPtrFloat("elePt");
        Float_t* eleEta = data.GetPtrFloat("eleEta");
        Float_t* elePhi = data.GetPtrFloat("elePhi");
        Float_t* eleR9  = data.GetPtrFloat("eleR9");
        Float_t* eleCalibPt = data.GetPtrFloat("eleCalibPt");
        Float_t* eleCalibEta = data.GetPtrFloat("eleCalibEta");
        



        */

        outtree_->Fill();
    }


    LOG_INFO("event looping end. Storing everything into root file");
    fout_->cd();
    LOG_DEBUG("writing tree");
    outtree_->Write();
    LOG_DEBUG("writing histograms");
    hists.WriteTo(fout_);
    LOG_DEBUG("closing output ROOT file");
    fout_->Close();
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
        hists.FillStatus("elePreselectStat", 0);
        if ( pt[i] < 12. ) continue;
        hists.FillStatus("elePreselectStat", 1);
        float abseta = fabs(eta[i]);
        if ( abseta > 2.5 ) continue;
        hists.FillStatus("elePreselectStat", 2);
        if ( abseta > 1.4442 && abseta < 1.566 ) continue;
        hists.FillStatus("elePreselectStat", 3);
        if (!dataptr->HasMC() ) if (!((idbit[i] >> WP) & 1) ) continue;
        hists.FillStatus("elePreselectStat", 4);
        selParticleIdxs.push_back(i);
    }

    std::vector<TLorentzCand> outputs;
    for ( int idx : selParticleIdxs )
        outputs.emplace_back( recoInfo::BuildSelectedParticles(idx, pt[idx], eta[idx], phi[idx], MASS_ELECTRON, charge[idx]) );
    return outputs;
}
bool PassElectronPreselection(TreeReader* dataptr, int WP, const TLorentzCand& cand)
{
    int idx = cand.idx();
    hists.FillStatus("elePreselectStat", 0);
    if ( dataptr->GetPtrFloat("elePt")[idx] < 12. ) return false;
    hists.FillStatus("elePreselectStat", 1);
    float abseta = fabs(dataptr->GetPtrFloat("eleSCEta")[idx]);
    if ( abseta > 2.5 ) return false;
    hists.FillStatus("elePreselectStat", 2);
    if ( abseta > 1.4442 && abseta < 1.566 ) return false;
    hists.FillStatus("elePreselectStat", 3);
    if (!dataptr->HasMC() ) if (!((((UShort_t*)dataptr->GetPtrShort("eleIDbit"))[idx] >> WP) & 1) ) return false;
    hists.FillStatus("elePreselectStat", 4);
    return true;
}
std::vector<TLorentzCand> matchedGenZee(TreeReader* dataptr, const TLorentzCand& ZCand_)
{
    #define DELTARCUT 0.10
    #define PTRATIOCUT 1.0
    #define FINALSTATE_STATUSCUT 1
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
    
    
    LOG_DEBUG("Got %d Z electrons in gen level, and %d gen electrons", genZElectronIdxs.size(), genElectronIdxs.size() );
    const std::vector<Int_t>& genIdxsContainer = (genZElectronIdxs.size()>1) ? genZElectronIdxs : genElectronIdxs;
    for ( Int_t geleIdx0 : genIdxsContainer )
        for ( Int_t geleIdx1 : genIdxsContainer )
        {
            LOG_DEBUG("starting matching");
            if ( geleIdx0 == geleIdx1 ) continue;
            LOG_DEBUG("selection1");
            if ( genpt_[geleIdx0] < genpt_[geleIdx1] ) continue;
            LOG_DEBUG("selection2");
            if ( mcMomPID_[geleIdx0] != mcMomPID_[geleIdx1] ) continue;
            LOG_DEBUG("selection3");
            TLorentzCand genEle0(geleIdx0, mcPID_[geleIdx0] > 0 ? -1 : 1 );
            TLorentzCand genEle1(geleIdx1, mcPID_[geleIdx1] > 0 ? -1 : 1 );
            genEle0.SetPtEtaPhiM(genpt_[geleIdx0], geneta_[geleIdx0], genphi_[geleIdx0], MASS_ELECTRON );
            genEle1.SetPtEtaPhiM(genpt_[geleIdx1], geneta_[geleIdx1], genphi_[geleIdx1], MASS_ELECTRON );

            if ( genEle0.charge() != recoEle0.charge() || genEle1.charge() != recoEle1.charge() ) continue;
            LOG_DEBUG("selection4");
            double deltaR0 = genEle0.DeltaR(recoEle0);
            double deltaR1 = genEle1.DeltaR(recoEle1);
            LOG_DEBUG("Calculating delta R value : %.3f -- %.3f", deltaR0, deltaR1);
        }
    

    return std::vector<TLorentzCand>();
}
std::vector<TLorentzCand> MCmatchedZElectronPair(TreeReader* dataptr)
{
    //hists.Fill("nEleMatched", -1);
    if (!dataptr->HasMC() ) return std::vector<TLorentzCand>();
    //hists.Fill("nEleMatched", 0);

    Int_t  nMC_         = dataptr->GetInt("nMC");
    Int_t* genPID_      = dataptr->GetPtrInt("mcPID");
    Int_t* genMomPID_   = dataptr->GetPtrInt("mcMomPID");
    Int_t* genStatus_   = dataptr->GetPtrInt("mcStatus");

    Float_t* genpt_     = dataptr->GetPtrFloat("mcPt");
    Float_t* geneta_    = dataptr->GetPtrFloat("mcEta");
    Float_t* genphi_    = dataptr->GetPtrFloat("mcPhi");

    Int_t  nEle_        = dataptr->GetInt("nEle");
    Float_t* pt_        = dataptr->GetPtrFloat("elePt");
    Float_t* eta_       = dataptr->GetPtrFloat("eleEta");
    Float_t* phi_       = dataptr->GetPtrFloat("elePhi");
    Int_t  * charge_    = dataptr->GetPtrInt("eleCharge");


    // finding Zee in gen level.
    TLorentzCand genZElectrons[2];
    for ( Int_t iMC = 0; iMC < nMC_; ++iMC )
        if ( abs(genPID_[iMC]) == PID_ELECTRON && genStatus_[iMC] <= FINALSTATE_STATUSCUT && genMomPID_[iMC] == PID_Z )
        {
            TLorentzCand genCand(iMC,
                    genPID_[iMC] == PID_ELECTRON ? -1 : 1, // charge
                    genpt_[iMC], geneta_[iMC], genphi_[iMC], MASS_ELECTRON );
        
            int fillIdx = genCand.charge() < 0 ? 0 : 1;
            if ( genZElectrons[fillIdx].IsZombie() ) genZElectrons[fillIdx] = genCand;
            else
            {
                LOG_INFO("more than 1 candidate found : info (pt,stat) = orig(%.3f,%d) and new(%.3f,%d). Use greater pt candidate",
                        genZElectrons[fillIdx].Pt(), genStatus_[genZElectrons[fillIdx].idx()],
                        genCand.Pt(), genStatus_[genCand.idx()]);
                if ( genZElectrons[fillIdx].Pt() < genCand.Pt() ) genZElectrons[fillIdx] = genCand;
            }
        }
    if ( genZElectrons[0].IsZombie() || genZElectrons[1].IsZombie() ) return std::vector<TLorentzCand>();
    hists.Fill("nEleMatched", -1);


    
    
    // matching to reco electron
    std::vector<TLorentzCand> matchedPairs;
    int check0 = 0;
    int check1 = 0;
    for ( int genZEIdx = 0; genZEIdx < 2; ++genZEIdx )
    {
        const TLorentzCand& genElectron = genZElectrons[genZEIdx];
        for ( Int_t iEle = 0; iEle < nEle_; ++iEle )
        {
            if ( genElectron.charge() != charge_[iEle] ) continue;
            TLorentzCand recoElectron( iEle, charge_[iEle], pt_[iEle], eta_[iEle], phi_[iEle], MASS_ELECTRON );

            double deltaR = genElectron.DeltaR(recoElectron);
            double ptratio = (recoElectron.Pt()-genElectron.Pt()) / genElectron.Pt();
            hists.Fill("DeltaR", deltaR);
            hists.Fill("ptratio", ptratio);
            if ( deltaR < DELTARCUT && ptratio < PTRATIOCUT )
            {
                recoElectron.SetGenIdx(genElectron.idx());
                matchedPairs.push_back(recoElectron);
                // only for check
                if ( genZEIdx == 0 ) ++check0;
                if ( genZEIdx == 1 ) ++check1;
            }
        }
    }
    if ( check0 != 1 || check1 != 1 ) LOG_INFO("mc matching status : number of reco electron matched at (ele0,ele1) = (%d, %d)", check0, check1);
    hists.Fill("nEleMatched",matchedPairs.size());
    std::sort(matchedPairs.begin(), matchedPairs.end(), recoInfo::ordering_pt);
    return matchedPairs;
}

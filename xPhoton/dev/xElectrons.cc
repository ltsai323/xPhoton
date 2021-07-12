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
std::vector<TLorentzCand> RecoElectrons(TreeReader* dataptr);
bool PassElectronPreselection(TreeReader* dataptr, int WP, const TLorentzCand& cand);
void xElectrons(
        std::vector<std::string> pathes,
        char oname[200] )
{
    TreeReader data(pathes);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");

    TTree *outtree_ = new TTree("t", "mini tree");
    
    rec_Electron record_electrons[2];
    rec_Z record_Z;
    //rec_Event event;

    RegBranch( outtree_, "electron_tag", &record_electrons[0] );
    RegBranch( outtree_, "electron_probe", &record_electrons[1] );
    RegBranch( outtree_, "Z", &record_Z );
    //RegBranch( outtree_, "Events", &event );

    
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
    // 3: Z candidate mass > 90 - 40
    // 4: Z candidate mass < 90 + 40
    hists.Create("ZRecoStat", 5, 0., 5.);

    // matched electrons in each event.
    // -1: the total number of events.
    //  n: n electrons matched in each event.
    hists.Create("nEleMatched", 6, -1, 5);

    // number of signal gen electron
    hists.Create("nGenEle", 6, -1, 5);
    hists.Create("DeltaR", BINNING, 0., 0.10);
    hists.Create("ptratio", BINNING, 0., 2.0);

    hists.Create("Zmass", BINNING, 50., 110.);



    
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        // 1. match reco electron and gen electron if MC used
        // 2. pass electron preselection
        // 3. build reco Z candidate
        // 4. fill tree
        // 5. load photon mva
        data.GetEntry(ev);

        std::vector<TLorentzCand> electrons;
        if ( data.HasMC() )
            electrons = MCmatchedZElectronPair(&data);
        else
            electrons = RecoElectrons(&data);

        for ( TLorentzCand& cand : electrons )
            cand.SetAlive( PassElectronPreselection(&data, ELECTRONWORKINGPOINT, cand) );
        hists.FillStatus("eventStat", 0);
        
        int aliveEleNum = 0;
        for ( auto ele : electrons )
            if (!ele.IsZombie() )
                ++aliveEleNum;

        hists.Fill("Nele", aliveEleNum);
        if ( aliveEleNum < 2 ) continue;

        hists.FillStatus("eventStat", 1);

        TLorentzCand ZcandP4;
        LOG_DEBUG( "ELECTRON (0,1) = Pt(%.2f,%.2f), Eta(%.2f,%.2f), charge(%d,%d)",
                electrons[0].Pt(), electrons[1].Pt(),
                electrons[0].Eta(), electrons[1].Eta(),
                electrons[0].charge(), electrons[1].charge() );
        for ( int eleI = 0; eleI < electrons.size(); ++eleI )
        {
            const TLorentzCand& ele0 = electrons.at(eleI);
            if ( ele0.IsZombie() ) continue;
            for ( int eleJ = eleI+1; eleJ < electrons.size(); ++eleJ )
            {
                const TLorentzCand& ele1 = electrons.at(eleJ);
                if ( ele1.IsZombie() ) continue;

                hists.FillStatus("ZRecoStat", 0);
                if (!data.HasMC() )
                {
                    ULong64_t* trigs = (ULong64_t*) data.GetPtrLong64("eleFiredDoubleTrgs");
                    if ( trigs[ele0.idx()] == 0 ) continue; // nothing triggered.
                            
                    if ( PASS_HLTBIT > 0 ) // although ULong64_t used. but only 0~31 bits recorded in ROOT. bit larger than 31 is useless.
                    {
                        int bit = PASS_HLTBIT;
                        if ( (trigs[ele0.idx()]>>bit)&1 == 0 ) continue; // tight ID for tag photon.
                        // need to check the validation
                        /* asdf
                        if ( trigs[ele0.idx()] & 1<<bit == 0 ) continue; // tight ID for tag photon.
                        */
                    }
                }
                hists.FillStatus("ZRecoStat", 1);

                ZcandP4 = ele0+ele1;
                if ( ZcandP4.M() > 50 && ZcandP4.M() < 110 ) hists.Fill("Zmass", ZcandP4.M());
                LOG_DEBUG("ZcandPt = %.3f from e1Pt = %.3f + e2Pt = %.3f. Zmass = %.2f. ch1=%d, ch2=%d", ZcandP4.Pt(), ele0.Pt(), ele1.Pt(), ZcandP4.M(), ele0.charge(), ele1.charge() );
                if ( ele0.charge() * ele1.charge() != -1 ) continue;
                hists.FillStatus("ZRecoStat", 2);
                if ( ZcandP4.M() < MASS_Z-WINDOW_Z ) continue;
                hists.FillStatus("ZRecoStat", 3);
                if ( ZcandP4.M() > MASS_Z+WINDOW_Z ) continue;
                hists.FillStatus("ZRecoStat", 4);
                ZcandP4.SetAlive(true);
                LOG_DEBUG("Z CAND found!");
                break;
            }
            if (!ZcandP4.IsZombie() ) break;
        }

        if ( ZcandP4.IsZombie() ) continue;
        hists.FillStatus("eventStat", 2);
        

        



        // filling events
        
        
        if ( data.HasMC() )
        {
            Float_t* mcPt = data.GetPtrFloat("mcPt");
            Float_t* mcEta = data.GetPtrFloat("mcEta");
            Float_t* mcPhi = data.GetPtrFloat("mcPhi");
            Float_t* mcCalIso04 = data.GetPtrFloat("mcCalIsoDR04");
            Float_t* mcTrkIso04 = data.GetPtrFloat("mcTrkIsoDR04");
        }

        Int_t* eleCharge = data.GetPtrInt("eleCharge");
        Float_t* elePt = data.GetPtrFloat("elePt");
        Float_t* eleEta = data.GetPtrFloat("eleEta");
        Float_t* elePhi = data.GetPtrFloat("elePhi");
        Float_t* eleCalibPt = data.GetPtrFloat("eleCalibPt");
        Float_t* eleCalibEn = data.GetPtrFloat("eleCalibEn");
        Float_t* eleSCEta = data.GetPtrFloat("eleSCEta");
        Float_t* eleSCPhi = data.GetPtrFloat("eleSCPhi");
        Float_t* eleHoverE = data.GetPtrFloat("eleHoverE");
        Float_t* eleR9  = data.GetPtrFloat("eleR9");
        Float_t* eleRawE = data.GetPtrFloat("eleSCRawEn");
        Float_t* eleSCEtaWidth = data.GetPtrFloat("eleSCEtaWidth");
        Float_t* eleSCPhiWidth = data.GetPtrFloat("eleSCPhiWidth");
        Float_t* eleESRR = data.GetPtrFloat("eleESEffSigmaRR");
        Float_t* eleESEnP1 = data.GetPtrFloat("eleESEnP1");
        Float_t* eleESEnP2 = data.GetPtrFloat("eleESEnP2");


        Float_t* eleR9Full5x5  = data.GetPtrFloat("eleR9Full5x5");
        Float_t* eleSigmaIEtaIEtaFull5x5 = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5");
        Float_t* eleSigmaIPhiIPhiFull5x5 = data.GetPtrFloat("eleSigmaIPhiIPhiFull5x5");

        Float_t* eleChIsoRaw = data.GetPtrFloat("elePFChIso");
        Float_t* elePhoIsoRaw = data.GetPtrFloat("elePFPhoIso");
        Float_t* eleNeuIsoRaw = data.GetPtrFloat("elePFNeuIso");
        //Float_t* eleChWorstRaw = data.GetPtrFloat("nothing");

        
        Short_t* eleID = data.GetPtrShort("eleIDbit");
        Long64_t* doubleEleTrgs = data.GetPtrLong64("eleFiredDoubleTrgs");
        Long64_t* singleEleTrgs = data.GetPtrLong64("eleFiredSingleTrgs");


        Float_t rho = data.GetFloat("rho");



    // clear everything.
        ClearStruct(&record_electrons[0]);
        ClearStruct(&record_electrons[1]);

        for ( int idx=0; idx<2; ++idx )
        {
            const TLorentzCand& cand = ZcandP4.daughters().at(idx);
            int recoIdx = cand.idx();
                    
            if ( data.HasMC() )
            {
                int genIdx = cand.genidx();
            record_electrons[idx].mcE          = data.GetPtrFloat("mcE")[genIdx];
            record_electrons[idx].mcPt         = data.GetPtrFloat("mcPt")[genIdx];
            record_electrons[idx].mcEta        = data.GetPtrFloat("mcEta")[genIdx];
            record_electrons[idx].mcPhi        = data.GetPtrFloat("mcPhi")[genIdx];
            }
            record_electrons[idx].recoPt       = data.GetPtrFloat("elePt")[recoIdx];
            record_electrons[idx].recoEta      = data.GetPtrFloat("eleEta")[recoIdx];
            record_electrons[idx].recoPhi      = data.GetPtrFloat("elePhi")[recoIdx];
            record_electrons[idx].recoPtCalib  = data.GetPtrFloat("eleCalibPt")[recoIdx];
            record_electrons[idx].recoSCEta    = data.GetPtrFloat("eleSCEta")[recoIdx];
            record_electrons[idx].r9           = data.GetPtrFloat("eleR9")[recoIdx];
            record_electrons[idx].HoverE       = data.GetPtrFloat("eleHoverE")[recoIdx];
            record_electrons[idx].chIsoRaw     = data.GetPtrFloat("elePFChIso")[recoIdx];
            record_electrons[idx].phoIsoRaw    = data.GetPtrFloat("elePFPhoIso")[recoIdx];
            record_electrons[idx].nhIsoRaw     = data.GetPtrFloat("elePFNeuIso")[recoIdx];
            record_electrons[idx].rawE         = data.GetPtrFloat("eleSCRawEn")[recoIdx];
            record_electrons[idx].scEtaWidth   = data.GetPtrFloat("eleSCEtaWidth")[recoIdx];
            record_electrons[idx].scPhiWidth   = data.GetPtrFloat("eleSCPhiWidth")[recoIdx];
            record_electrons[idx].esRR         = data.GetPtrFloat("eleESEffSigmaRR")[recoIdx];
            record_electrons[idx].esEn         = data.GetPtrFloat("eleESEnP1")[recoIdx]+
                                                 data.GetPtrFloat("eleESEnP2")[recoIdx];
            record_electrons[idx].mva          = 0; //data.GetPtrFloat("")[recoIdx];
            record_electrons[idx].mva_nocorr   = 0; //data.GetPtrFloat("")[recoIdx];
            record_electrons[idx].officalIDmva = data.GetPtrFloat("eleIDMVAIso")[recoIdx];
            record_electrons[idx].r9Full5x5    = data.GetPtrFloat("eleR9Full5x5")[recoIdx];
            record_electrons[idx].sieieFull5x5 = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5")[recoIdx];
            //record_electrons[idx].sieipFull5x5 = data.GetPtrFloat("")[recoIdx];
            record_electrons[idx].sipipFull5x5 = data.GetPtrFloat("eleSigmaIPhiIPhiFull5x5")[recoIdx];
            record_electrons[idx].e2x2Full5x5  = 0; //data.GetPtrFloat("")[recoIdx];
            record_electrons[idx].e2x5Full5x5  = 0; //data.GetPtrFloat("")[recoIdx];

            record_electrons[idx].firedTrgs    = int( data.GetPtrLong64("eleFiredDoubleTrgs")[recoIdx] );
            record_electrons[idx].isMatched    = cand.genidx() >= 0;
            record_electrons[idx].firedTrgsL   = data.GetPtrLong64("eleFiredDoubleTrgs")[recoIdx];
        }
        if ( data.HasMC() )
        {
            int ZMCidx = data.GetPtrInt("mcMomPID")[ZcandP4.daughters().at(0).idx()];
        record_Z.mcE       = 0;
        record_Z.mcPt      = 0;
        record_Z.mcEta     = 0;
        record_Z.mcPhi     = 0;
        }
        record_Z.recoMass  = ZcandP4.M();
        record_Z.recoE     = ZcandP4.Energy();
        record_Z.recoPt    = ZcandP4.Pt();
        record_Z.recoEta   = ZcandP4.Eta();
        record_Z.recoPhi   = ZcandP4.Phi();
        record_Z.isMatched = ZcandP4.daughters().at(0).genidx() > 0 && ZcandP4.daughters().at(1).genidx() > 0;
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
std::vector<TLorentzCand> RecoElectrons(TreeReader* dataptr)
{
    std::vector<TLorentzCand> outputs;
    for ( Int_t idx = 0; idx < dataptr->GetInt("nEle"); ++idx )
        outputs.emplace_back( recoInfo::BuildSelectedParticles(
                    idx,
                    dataptr->GetPtrInt  ("eleCharge")[idx],
                    dataptr->GetPtrFloat("elePt")[idx],
                    dataptr->GetPtrFloat("eleEta")[idx],
                    dataptr->GetPtrFloat("elePhi")[idx],
                    MASS_ELECTRON
                ) );
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
std::vector<TLorentzCand> MCmatchedZElectronPair(TreeReader* dataptr)
{
    #define DELTARCUT 0.10
    #define PTRATIOCUT 1.0
    #define FINALSTATE_STATUSCUT 1
    #define PID_Z 23
    #define PID_ELECTRON 11
    if (!dataptr->HasMC() ) return std::vector<TLorentzCand>();

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
    if ( check0 != 1 || check1 != 1 ) LOG_INFO("Failed mc matching status : number of reco electron matched at (ele0,ele1) = (%d, %d)", check0, check1);
    hists.Fill("nEleMatched",matchedPairs.size());
    std::sort(matchedPairs.begin(), matchedPairs.end(), recoInfo::ordering_pt);
    return matchedPairs;
}

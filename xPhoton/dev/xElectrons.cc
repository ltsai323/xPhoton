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
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include <TLorentzVector.h>
#include <map>
#include <TNtupleD.h>


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
    TNtupleD* nt_sumupgenweight = new TNtupleD("genweightsummary", "", "sumupgenweight:hasNon1Val");
    //Double_t overallGenweight[1] = {0};
    Double_t overallGenweight = 0;
    Double_t hasNon1Val = 0;
    
    rec_Electron record_electrons[2];
    rec_Z record_Z;
    rec_Event record_evt;

    RegBranch( outtree_, "electron_tag", &record_electrons[0] );
    RegBranch( outtree_, "electron_probe", &record_electrons[1] );
    RegBranch( outtree_, "Z", &record_Z );
    RegBranch( outtree_, "Events", &record_evt );

    
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
    // 2: pass single electron HLT pt threshold
    // 3: pass single electron HLT work point threshold
    // 4: electron pair with opposite charge
    // 5: Z candidate mass > 90 - 40
    // 6: Z candidate mass < 90 + 40
    hists.Create("ZRecoStat", 7, 0., 7.);

    // matched electrons in each event.
    // -1: the total number of events.
    //  n: n electrons matched in each event.
    hists.Create("nEleMatched", 5, 0, 5);

    hists.Create("DeltaR", BINNING, 0., 0.10);
    hists.Create("ptratio", BINNING, 0., 2.0);

    hists.Create("Zmass", BINNING, 50., 110.);

    // check how much reco electrons in Zee
    hists.Create("nEleInZee", 5,0.,5.);
    // check how much gen Zee in MC.
    // 0 : number of gen Zee.
    // 1 : number of gen Zee, all electrons belongs to fiducial region.
    // 2 : number of gen Zee, with all electrons are reco matched.
    hists.Create("numGenZee", 4, 0., 4.);

    TFile* f_showershapecorrection;
    PUWeightCalculator pucalc;
    std::map<std::string, TGraph*> endcapCorrections;
    std::map<std::string, TGraph*> barrelCorrections;
    if ( data.HasMC() )
    {
    f_showershapecorrection = TFile::Open( ExternalFilesMgr::RooFile_ShowerShapeCorrection() );
    endcapCorrections["scEtaWidth"  ] = (TGraph*)f_showershapecorrection->Get("transfEtaWidthEE");
    endcapCorrections["s4"          ] = (TGraph*)f_showershapecorrection->Get("transfS4EE");
    endcapCorrections["r9Full5x5"   ] = (TGraph*)f_showershapecorrection->Get("transffull5x5R9EE");
    endcapCorrections["sieieFull5x5"] = (TGraph*)f_showershapecorrection->Get("transffull5x5sieieEE");

    barrelCorrections["scEtaWidth"  ] = (TGraph*)f_showershapecorrection->Get("transfEtaWidthEB");
    barrelCorrections["s4"          ] = (TGraph*)f_showershapecorrection->Get("transfS4EB");
    barrelCorrections["r9Full5x5"   ] = (TGraph*)f_showershapecorrection->Get("transffull5x5R9EB");
    barrelCorrections["sieieFull5x5"] = (TGraph*)f_showershapecorrection->Get("transffull5x5sieieEB");

    pucalc.Init( ExternalFilesMgr::RooFile_PileUp() );
    }


    
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        // 1. match reco electron and gen electron if MC used
        // 2. pass electron preselection
        // 3. build reco Z candidate
        // 4. fill tree
        // 5. load photon mva
        data.GetEntry(ev);
        if ( data.HasMC() )
        {
            overallGenweight += data.GetFloat("genWeight");
            if ( hasNon1Val < 0.1 )
                if ( data.GetFloat("genWeight") != 1. )
                    hasNon1Val = 1;
        }

        std::vector<TLorentzCand> electrons;
        if ( data.HasMC() )
        {
            LOG_DEBUG("hiiiiii");
            electrons = MCmatchedZElectronPair(&data);
            if ( electrons.size() > 1 )
            LOG_DEBUG("event obtained electrons matched with Zee sample in gen level. Gen indexes are (%d,%d).", electrons.at(0).genidx(), electrons.at(1).genidx());
        }
        else
            electrons = RecoElectrons(&data);

        for ( TLorentzCand& cand : electrons ) cand.SetAlive( PassElectronPreselection(&data, ELECTRONWORKINGPOINT, cand) );
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
                // HLT_Ele25_WPTight_Gsf_v1
                const int PASS_HLTBIT = 5;
                const int HLTWP = 3;
                if (!data.HasMC() )
                { // HLT selections
                    ULong64_t* trigs = (ULong64_t*) data.GetPtrLong64("eleFiredSingleTrgs");
                    if ( trigs[ele0.idx()] == 0 ) continue; // nothing triggered.
                            
                    if ( PASS_HLTBIT > 0 ) // although ULong64_t used. but only 0~31 bits recorded in ROOT. bit larger than 31 is useless.
                    {
                        int hltbit_singlephoton = PASS_HLTBIT;
                        if ( (trigs[ele0.idx()]>>hltbit_singlephoton)&1 == 0 ) continue; // single photon 
                    }
                }
                hists.FillStatus("ZRecoStat", 1);
                if ( data.GetPtrFloat("elePt")[ele0.idx()] < 25 ) continue; // used for singlePhoton HLT.
                hists.FillStatus("ZRecoStat", 2);
                if ( HLTWP > 0 )
                    if (!((((UShort_t*)data.GetPtrShort("eleIDbit"))[ele0.idx()] >> HLTWP ) & 1) ) continue;
                hists.FillStatus("ZRecoStat", 3);


                ZcandP4 = ele0+ele1;
                if ( ZcandP4.M() > 50 && ZcandP4.M() < 110 ) hists.Fill("Zmass", ZcandP4.M());
                LOG_DEBUG("ZcandPt = %.3f from e1Pt = %.3f + e2Pt = %.3f. Zmass = %.2f. ch1=%d, ch2=%d", ZcandP4.Pt(), ele0.Pt(), ele1.Pt(), ZcandP4.M(), ele0.charge(), ele1.charge() );
                if ( ele0.charge() * ele1.charge() != -1 ) continue;
                hists.FillStatus("ZRecoStat", 4);
                if ( ZcandP4.M() < MASS_Z-WINDOW_Z ) continue; // lower bond
                hists.FillStatus("ZRecoStat", 5);
                if ( ZcandP4.M() > MASS_Z+WINDOW_Z ) continue; // upper bond
                hists.FillStatus("ZRecoStat", 6);
                ZcandP4.SetAlive(true);
                LOG_DEBUG("Z CAND found!");
                break;
            }
            if (!ZcandP4.IsZombie() ) break;
        }

        if ( ZcandP4.IsZombie() ) continue;
        hists.FillStatus("eventStat", 2);
        if ( data.HasMC() )
        {
            LOG_DEBUG("reco Z candidate contains matched gen electron in idx (%d,%d)", ZcandP4.daughters().at(0).genidx(), ZcandP4.daughters().at(1).genidx());
        }



    // clear everything.
        ClearStruct(&record_electrons[0]);
        ClearStruct(&record_electrons[1]);
        ClearStruct(&record_Z);
        ClearStruct(&record_evt);

        for ( int idx=0; idx<2; ++idx )
        {
            const TLorentzCand cand = ZcandP4.daughters().at(idx);
            int recoIdx = cand.idx();
            rec_Electron& eleRecording = record_electrons[idx];
                    
            eleRecording.recoPt       = data.GetPtrFloat("elePt")[recoIdx];
            eleRecording.recoEta      = data.GetPtrFloat("eleEta")[recoIdx];
            eleRecording.recoPhi      = data.GetPtrFloat("elePhi")[recoIdx];
            eleRecording.recoPtCalib  = data.GetPtrFloat("eleCalibPt")[recoIdx];
            eleRecording.recoSCEta    = data.GetPtrFloat("eleSCEta")[recoIdx];
            eleRecording.r9           = data.GetPtrFloat("eleR9")[recoIdx];
            eleRecording.HoverE       = data.GetPtrFloat("eleHoverE")[recoIdx];
            eleRecording.chIsoRaw     = data.GetPtrFloat("elePFChIso")[recoIdx];
            eleRecording.phoIsoRaw    = data.GetPtrFloat("elePFPhoIso")[recoIdx];
            eleRecording.nhIsoRaw     = data.GetPtrFloat("elePFNeuIso")[recoIdx];
            eleRecording.rawE         = data.GetPtrFloat("eleSCRawEn")[recoIdx];
            eleRecording.scEtaWidth   = data.GetPtrFloat("eleSCEtaWidth")[recoIdx];
            eleRecording.scPhiWidth   = data.GetPtrFloat("eleSCPhiWidth")[recoIdx];
            eleRecording.esRR         = data.GetPtrFloat("eleESEffSigmaRR")[recoIdx];
            eleRecording.esEn         = data.GetPtrFloat("eleESEnP1")[recoIdx]+
                                        data.GetPtrFloat("eleESEnP2")[recoIdx];
            eleRecording.mva          = 0; //data.GetPtrFloat("")[recoIdx];
            eleRecording.mva_nocorr   = 0; //data.GetPtrFloat("")[recoIdx];
            eleRecording.officalIDmva = data.GetPtrFloat("eleIDMVAIso")[recoIdx];
            eleRecording.r9Full5x5    = data.GetPtrFloat("eleR9Full5x5")[recoIdx];
            eleRecording.sieieFull5x5 = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5")[recoIdx];
            //eleRecording.sieipFull5x5 = data.GetPtrFloat("")[recoIdx];
            eleRecording.sipipFull5x5 = data.GetPtrFloat("eleSigmaIPhiIPhiFull5x5")[recoIdx];
            eleRecording.e2x2Full5x5  = 0; //data.GetPtrFloat("")[recoIdx];
            eleRecording.e2x5Full5x5  = 0; //data.GetPtrFloat("")[recoIdx];

            eleRecording.firedTrgs    = int( data.GetPtrLong64("eleFiredDoubleTrgs")[recoIdx] );
            eleRecording.isMatched    = cand.genidx() >= 0;
            eleRecording.firedTrgsL   = data.GetPtrLong64("eleFiredDoubleTrgs")[recoIdx];

            if ( data.HasMC() )
            {
                int genIdx = cand.genidx();
            eleRecording.mcE          = genIdx < 0 ? 0 : data.GetPtrFloat("mcE")[genIdx];
            eleRecording.mcPt         = genIdx < 0 ? 0 : data.GetPtrFloat("mcPt")[genIdx];
            eleRecording.mcEta        = genIdx < 0 ? 0 : data.GetPtrFloat("mcEta")[genIdx];
            eleRecording.mcPhi        = genIdx < 0 ? 0 : data.GetPtrFloat("mcPhi")[genIdx];
            
            
            std::map<std::string, TGraph*>* corrections = recoInfo::IsEE(eleRecording.recoSCEta) ? &endcapCorrections : &barrelCorrections;
            eleRecording.scEtaWidth_corrected      = recoInfo::CorrectedValue( corrections->at("scEtaWidth")  , eleRecording.scEtaWidth );

            eleRecording.r9Full5x5_corrected       = recoInfo::CorrectedValue( corrections->at("r9Full5x5")   , eleRecording.r9Full5x5 );
            eleRecording.s4_corrected              = 0;
            eleRecording.sieieFull5x5_corrected    = recoInfo::CorrectedValue( corrections->at("sieieFull5x5"), eleRecording.sieieFull5x5 );
            }
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

        record_evt.run               = data.GetInt("run"); 
        if ( data.HasMC() )
        {
            Float_t* puTrue = data.GetPtrFloat("puTrue");
            Int_t npuInfo = data.GetInt("nPUInfo");
            int _purec = 0;
            for ( int i=0; i<npuInfo; ++i ) if ( data.GetPtrInt("puBX")[i] == 0 ) _purec = puTrue[i];
            
        record_evt.xsweight          = 0;
        record_evt.genweight         = data.HasMC() ? data.GetFloat("genWeight") : 1;
        record_evt.puwei             = (float) pucalc.GetWeight(record_evt.run, puTrue[1]);
        record_evt.pthat             = data.GetFloat("pthat");
        record_evt.nPU               = _purec;
        }

        record_evt.MET               = data.GetFloat("pfMET");
        record_evt.METPhi            = data.GetFloat("pfMETPhi");
        record_evt.rho               = data.GetFloat("rho");

        record_evt.nVtx              = data.GetInt("nVtx");
        record_evt.HLT               = data.GetLong64("HLTPho");
        record_evt.HLTPhoIsPrescaled = data.GetLong64("HLTPhoIsPrescaled");
        record_evt.event             = data.GetLong64("event"); 


        outtree_->Fill();
        LOG_DEBUG("one event ended");
    }
    LOG_DEBUG("event loop ended");
    


    LOG_INFO("event looping end. Storing everything into root file");
    fout_->cd();
    LOG_DEBUG("writing tree");
    outtree_->Write();
    LOG_DEBUG("writing ntuples");
    if ( data.HasMC() )
    {
    	nt_sumupgenweight->Fill(overallGenweight,hasNon1Val);
    	nt_sumupgenweight->Write();
    }
    LOG_DEBUG("writing histograms");
    hists.WriteTo(fout_);
    LOG_DEBUG("closing output ROOT file");
    fout_->Close();
    LOG_INFO("All %lld Events processed", data.GetEntriesFast());
    if ( data.HasMC() )
	    f_showershapecorrection->Close();
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
    if ( WP >= 0 ) if (!((((UShort_t*)dataptr->GetPtrShort("eleIDbit"))[idx] >> WP) & 1) ) return false;
    //if (!dataptr->HasMC() ) if (!((((UShort_t*)dataptr->GetPtrShort("eleIDbit"))[idx] >> WP) & 1) ) return false;
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


    LOG_DEBUG("chk point 01");
    // finding Zee in gen level.
    TLorentzCand genZElectrons[2];
    LOG_DEBUG("chk point 01.0");
    for ( Int_t iMC = 0; iMC < nMC_; ++iMC )
        if ( abs(genPID_[iMC]) == PID_ELECTRON && genStatus_[iMC] <= FINALSTATE_STATUSCUT && genMomPID_[iMC] == PID_Z )
        {
            TLorentzCand genCand(iMC,
                    genPID_[iMC] == PID_ELECTRON ? -1 : 1, // charge
                    genpt_[iMC], geneta_[iMC], genphi_[iMC], MASS_ELECTRON );
        
            int fillIdx = genCand.charge() < 0 ? 0 : 1;
            //if (!recoInfo::InFiducialRegion(genCand) ) continue;
            if ( genZElectrons[fillIdx].IsZombie() ) genZElectrons[fillIdx] = genCand;
            else
            {
                LOG_INFO("more than 1 candidate found : info (pt,stat) = orig(%.3f,%d) and new(%.3f,%d). Use greater pt candidate",
                        genZElectrons[fillIdx].Pt(), genStatus_[genZElectrons[fillIdx].idx()],
                        genCand.Pt(), genStatus_[genCand.idx()]);
                if ( genZElectrons[fillIdx].Pt() < genCand.Pt() ) genZElectrons[fillIdx] = genCand;
            }
        }
    LOG_DEBUG("chk point 01.1");
    //if (!genZElectrons[0].IsZombie() ||!genZElectrons[1].IsZombie() ) hists.FillStatus("numGenZee",0);
    if ( genZElectrons[0].IsZombie() || genZElectrons[1].IsZombie() ) return std::vector<TLorentzCand>();
    LOG_DEBUG("chk point 01.2");
    hists.FillStatus("numGenZee",0);
    if (!recoInfo::InFiducialRegion( genZElectrons[0] ) ||!recoInfo::InFiducialRegion( genZElectrons[1] ) ) return std::vector<TLorentzCand>();
    hists.FillStatus("numGenZee",1);
    if ( nEle_ < 2 ) return std::vector<TLorentzCand>();
    hists.FillStatus("numGenZee",2);
    hists.Fill("nEleInZee", nEle_);


    
    LOG_DEBUG("chk point 02");
    
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
    LOG_DEBUG("chk point 03");
    hists.Fill("nEleMatched",matchedPairs.size());
    if ( check0 != 1 || check1 != 1 )
    {
        LOG_INFO("Failed mc matching status : number of reco electron matched at (ele0,ele1) = (%d, %d)", check0, check1);
        return std::vector<TLorentzCand>();
    }
    hists.FillStatus("numGenZee",3);
    LOG_DEBUG("electrons matched with Zee sample in gen level. Gen indexes are (%d,%d). Max index = %d", matchedPairs.at(0).genidx(), matchedPairs.at(1).genidx(), nMC_ );

    std::sort(matchedPairs.begin(), matchedPairs.end(), recoInfo::ordering_pt);
    return matchedPairs;
}
void RegBranch( TTree* t, const std::string& name, rec_Electron* var )
{
    //t->Branch(name, var, "mcE/F:mcPt/F:mcEta/F:mcPhi/F:recoPt/F:recoEta/F:recoPhi/F:recoPtCalib/F:recoSCEta/F:r9/F:HoverE/F:chIsoRaw/F:phoIsoRaw/F:nhIsoRaw/F:chWorstIso/F:rawE/F:scEtaWidth/F:scPhiWidth/F:esRR/F:esEn/F:mva/F:mva_nocorr/F:officalIDmva/F:r9Full5x5/F:sieieFull5x5/F:sipipFull5x5/F:e2x2Full5x5/F:e2x5Full5x5/F:firedTrgs/I:isMatched/I:firedTrgsL/L");

    t->Branch( (name+".mcE").c_str()                ,&var->mcE          , (name+".mcE/F").c_str()              );
    t->Branch( (name+".mcPt").c_str()               ,&var->mcPt         , (name+".mcPt/F").c_str()             );
    t->Branch( (name+".mcEta").c_str()              ,&var->mcEta        , (name+".mcEta/F").c_str()            );
    t->Branch( (name+".mcPhi").c_str()              ,&var->mcPhi        , (name+".mcPhi/F").c_str()            );
    t->Branch( (name+".recoPt").c_str()             ,&var->recoPt       , (name+".recoPt/F").c_str()           );
    t->Branch( (name+".recoEta").c_str()            ,&var->recoEta      , (name+".recoEta/F").c_str()          );
    t->Branch( (name+".recoPhi").c_str()            ,&var->recoPhi      , (name+".recoPhi/F").c_str()          );
    t->Branch( (name+".recoPtCalib").c_str()        ,&var->recoPtCalib  , (name+".recoPtCalib/F").c_str()      );
    t->Branch( (name+".recoSCEta").c_str()          ,&var->recoSCEta    , (name+".recoSCEta/F").c_str()        );
    t->Branch( (name+".r9").c_str()                 ,&var->r9           , (name+".r9/F").c_str()               );
    t->Branch( (name+".HoverE").c_str()             ,&var->HoverE       , (name+".HoverE/F").c_str()           );
    t->Branch( (name+".chIsoRaw").c_str()           ,&var->chIsoRaw     , (name+".chIsoRaw/F").c_str()         );
    t->Branch( (name+".phoIsoRaw").c_str()          ,&var->phoIsoRaw    , (name+".phoIsoRaw/F").c_str()        );
    t->Branch( (name+".nhIsoRaw").c_str()           ,&var->nhIsoRaw     , (name+".nhIsoRaw/F").c_str()         );
    t->Branch( (name+".chWorstIso").c_str()         ,&var->chWorstIso   , (name+".chWorstIso/F").c_str()       );
    t->Branch( (name+".rawE").c_str()               ,&var->rawE         , (name+".rawE/F").c_str()             );
    t->Branch( (name+".scEtaWidth").c_str()         ,&var->scEtaWidth   , (name+".scEtaWidth/F").c_str()       );
    t->Branch( (name+".scPhiWidth").c_str()         ,&var->scPhiWidth   , (name+".scPhiWidth/F").c_str()       );
    t->Branch( (name+".esRR").c_str()               ,&var->esRR         , (name+".esRR/F").c_str()             );
    t->Branch( (name+".esEn").c_str()               ,&var->esEn         , (name+".esEn/F").c_str()             );
    t->Branch( (name+".mva").c_str()                ,&var->mva          , (name+".mva/F").c_str()              );
    t->Branch( (name+".mva_nocorr").c_str()         ,&var->mva_nocorr   , (name+".mva_nocorr/F").c_str()       );
    t->Branch( (name+".officalIDmva").c_str()       ,&var->officalIDmva , (name+".officalIDmva/F").c_str()     );
    t->Branch( (name+".r9Full5x5").c_str()          ,&var->r9Full5x5    , (name+".r9Full5x5/F").c_str()        );
    t->Branch( (name+".sieieFull5x5").c_str()       ,&var->sieieFull5x5 , (name+".sieieFull5x5/F").c_str()     );
    t->Branch( (name+".sipipFull5x5").c_str()       ,&var->sipipFull5x5 , (name+".sipipFull5x5/F").c_str()     );
    t->Branch( (name+".e2x2Full5x5").c_str()        ,&var->e2x2Full5x5  , (name+".e2x2Full5x5/F").c_str()      );
    t->Branch( (name+".e2x5Full5x5").c_str()        ,&var->e2x5Full5x5  , (name+".e2x5Full5x5/F").c_str()      );
    t->Branch( (name+".calib_scEtaWidth"  ).c_str(), &var->scEtaWidth_corrected     , (name+".calib_scEtaWidth/F").c_str()      );
    t->Branch( (name+".calib_r9Full5x5"   ).c_str(), &var->r9Full5x5_corrected      , (name+".calib_r9Full5x5/F").c_str()      );
    t->Branch( (name+".calib_s4"          ).c_str(), &var->s4_corrected             , (name+".calib_s4/F").c_str()      );
    t->Branch( (name+".calib_sieieFull5x5").c_str(), &var->sieieFull5x5_corrected   , (name+".calib_sieieFull5x5/F").c_str()      );


    t->Branch( (name+".firedTrgs").c_str()          ,&var->firedTrgs    , (name+".firedTrgs/I").c_str()        );
    t->Branch( (name+".isMatched").c_str()          ,&var->isMatched    , (name+".isMatched/I").c_str()        );

    t->Branch( (name+".firedTrgsL").c_str()         ,&var->firedTrgsL   , (name+".firedTrgsL/L").c_str()       );
}
void RegBranch( TTree* t, const std::string& name, rec_Z* var )
{
    t->Branch( (name+".mcE").c_str()            ,&var->mcE       , (name+".mcE/F").c_str()        );
    t->Branch( (name+".mcPt").c_str()           ,&var->mcPt      , (name+".mcPt/F").c_str()       );
    t->Branch( (name+".mcEta").c_str()          ,&var->mcEta     , (name+".mcEta/F").c_str()      );
    t->Branch( (name+".mcPhi").c_str()          ,&var->mcPhi     , (name+".mcPhi/F").c_str()      );
    t->Branch( (name+".recoMass").c_str()       ,&var->recoMass  , (name+".recoMass/F").c_str()   );
    t->Branch( (name+".recoE").c_str()          ,&var->recoE     , (name+".recoE/F").c_str()      );
    t->Branch( (name+".recoPt").c_str()         ,&var->recoPt    , (name+".recoPt/F").c_str()     );
    t->Branch( (name+".recoEta").c_str()        ,&var->recoEta   , (name+".recoEta/F").c_str()    );
    t->Branch( (name+".recoPhi").c_str()        ,&var->recoPhi   , (name+".recoPhi/F").c_str()    );

    t->Branch( (name+".isMatched").c_str()      ,&var->isMatched , (name+".isMatched/I").c_str()  );
}
void RegBranch( TTree* t, const string& name, rec_Event* var )
{
    t->Branch( (name+".run").c_str()               , &var->run,                     "run/I");
    t->Branch( (name+".xsweight").c_str()          , &var->xsweight,                "xsweight/I");
    t->Branch( (name+".puwei").c_str()             , &var->puwei,                   "puwei/I");
    t->Branch( (name+".pthat").c_str()             , &var->pthat,                   "pthat/I");
    t->Branch( (name+".nVtx").c_str()              , &var->nVtx,                    "nVtx/I");
    t->Branch( (name+".nPU").c_str()               , &var->nPU,                     "nPU/I");

    t->Branch( (name+".rho").c_str()               , &var->rho,                     "rho/F");
    t->Branch( (name+".genweight").c_str()         , &var->genweight,               "genweight/F");
    t->Branch( (name+".MET").c_str()               , &var->MET,                     "MET/F");
    t->Branch( (name+".METPhi").c_str()            , &var->METPhi,                  "METPhi/F");
    
    t->Branch( (name+".HLT").c_str()               , &var->HLT,                     "HLT/L");
    t->Branch( (name+".HLTPhoIsPres.caled").c_str(), &var->HLTPhoIsPrescaled,       "HLTPhoIsPrescaled/L");
    t->Branch( (name+".event").c_str()             , &var->event,                   "event/L");
}

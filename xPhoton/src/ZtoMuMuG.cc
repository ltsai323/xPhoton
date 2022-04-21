#include "xPhoton/xPhoton/interface/ZtoMuMuG.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/histMgr.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include "xPhoton/xPhoton/interface/ShowerShapeCorrectionAdapter.h"
#include <TLorentzVector.h>
#include <map>
#include <TNtuple.h>


static histMgr hists;
void ZtoMuMuG(
        std::vector<std::string> pathes,
        char oname[200] )
{
    TreeReader data(pathes);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");

    TTree *outtree_ = new TTree("t", "mini tree");
    TNtuple* nt_sumupgenweight = new TNtuple("genweightsummary", "", "sumupgenweight:hasNon1Val");
    Float_t overallGenweight = 0;
    Float_t hasNon1Val = 0;
    
    rec_Electron record_electrons[2]; // probe photon : need to be modified.
    rec_Mu record_Mu[2];
    rec_Z record_Z;
    rec_Event record_evt;

    RegBranchZMuMu( outtree_, "", &record_electrons[1] ); // probe electron, like a photon
    RegBranchZMuMu( outtree_, "mu0", &record_Mu[0] );
    RegBranchZMuMu( outtree_, "mu1", &record_Mu[1] );
    RegBranchZMuMu( outtree_, "Z", &record_Z );
    RegBranchZMuMu( outtree_, "Events", &record_evt );

    
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
    hists.Create("NumMuonPassedHLT", 4, 0., 4.);
    hists.Create("MuonHLTPassedBits", 32, 0., 32.);

    std::string dataEra = "UL2018";
    ShowerShapeCorrectionAdapter SScorr( dataEra, data.HasMC() );
    PhotonMVACalculator mvaloader( &data, dataEra );
    PUWeightCalculator pucalc;

    if ( data.HasMC() )
    { pucalc.Init( ExternalFilesMgr::RooFile_PileUp(dataEra) ); }


    
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

        LOG_DEBUG(" check point 01");
        std::vector<TLorentzCand> trigMuons = TriggeredDiMuon(&data);
        if ( trigMuons.size() != 2 ) continue;
        LOG_DEBUG(" check point 02");

        std::vector<TLorentzCand> photons = RecoPhoton(&data);
        LOG_DEBUG(" number of reco photon : %d", int(photons.size()) );


        int Zidx = 0;
        std::vector<TLorentzCand> selectedPhoton;
        for ( auto photon : photons )
        {
            TLorentzCand ZcandP4;
            ZcandP4 = trigMuons[0] + trigMuons[1];
            ZcandP4 += photon;

            ZcandP4.SetAlive(false);
            if ( ZcandP4.M() < MASS_Z-WINDOW_Z ) continue; // lower bond
            if ( ZcandP4.M() > MASS_Z+WINDOW_Z ) continue; // upper bond
            ZcandP4.SetAlive(true);
            selectedPhoton.push_back(photon);
        }
        LOG_DEBUG(" number of selected photon : %d", int(selectedPhoton.size()) );
            
        for ( auto photon : selectedPhoton )
        {
        LOG_DEBUG("starting to fill event");
        ClearStruct(&record_electrons[0]);
        ClearStruct(&record_electrons[1]);
        ClearStruct(&record_Mu[0]);
        ClearStruct(&record_Mu[1]);
        ClearStruct(&record_Z);
        ClearStruct(&record_evt);

            int recoIdx = photon.idx();
            rec_Electron& eleRecording = record_electrons[1];
                    
            eleRecording.recoPt       = data.GetPtrFloat("phoEt")[recoIdx];
            eleRecording.recoEta      = data.GetPtrFloat("phoEta")[recoIdx];
            eleRecording.recoPtCalib  = data.GetPtrFloat("phoCalibEt")[recoIdx];
            eleRecording.recoSCEta    = data.GetPtrFloat("phoSCEta")[recoIdx];
            eleRecording.r9           = data.GetPtrFloat("phoR9")[recoIdx];
            eleRecording.HoverE       = data.GetPtrFloat("phoHoverE")[recoIdx];
            eleRecording.chIsoRaw     = data.GetPtrFloat("phoPFChIso")[recoIdx];
            eleRecording.phoIsoRaw    = data.GetPtrFloat("phoPFPhoIso")[recoIdx];
            eleRecording.nhIsoRaw     = data.GetPtrFloat("phoPFNeuIso")[recoIdx];
            eleRecording.rawE         = data.GetPtrFloat("phoSCRawE")[recoIdx];
            eleRecording.scEtaWidth   = data.GetPtrFloat("phoSCEtaWidth")[recoIdx];
            eleRecording.scPhiWidth   = data.GetPtrFloat("phoSCPhiWidth")[recoIdx];
            eleRecording.esRR         = data.GetPtrFloat("phoESEffSigmaRR")[recoIdx];
            eleRecording.esEn         = data.GetPtrFloat("phoESEnP1")[recoIdx]+
                                        data.GetPtrFloat("phoESEnP2")[recoIdx];
            eleRecording.mva          = mvaloader.GetMVA_noIso(recoIdx, &SScorr);
            eleRecording.mva_nocorr   = mvaloader.GetMVA_noIso(recoIdx);
            eleRecording.officalIDmva = data.GetPtrFloat("phoIDMVA")[recoIdx];
            eleRecording.r9Full5x5    = data.GetPtrFloat("phoR9Full5x5")[recoIdx];
            eleRecording.sieieFull5x5 = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[recoIdx];
            eleRecording.sieipFull5x5 = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5")[recoIdx];
            eleRecording.sipipFull5x5 = data.GetPtrFloat("phoSigmaIPhiIPhiFull5x5")[recoIdx];
            eleRecording.s4Full5x5    = data.GetPtrFloat("phoE2x2Full5x5")[recoIdx] /
                                        data.GetPtrFloat("phoE5x5Full5x5")[recoIdx];
            eleRecording.esEnergyOverSCRawEnergy = eleRecording.esEn / eleRecording.rawE;

            eleRecording.isMatched    = photon.genidx() >= 0;
            eleRecording.firedTrgsL   = data.GetPtrLong64("phoFiredSingleTrgs")[recoIdx];
            eleRecording.idbit        = ((UShort_t*)data.GetPtrShort("phoIDbit"))[recoIdx];

            if ( data.HasMC() )
            {
                int genIdx = photon.genidx();
            eleRecording.mcPt         = genIdx < 0 ? 0 : data.GetPtrFloat("mcPt")[genIdx];
            eleRecording.mcEta        = genIdx < 0 ? 0 : data.GetPtrFloat("mcEta")[genIdx];
            
            
                if (!ShowerShapeCorrectionParameters_ggNtuple::isSameEvent(&SScorr, &data, recoIdx) )
                {
                    ShowerShapeCorrectionParameters_ggNtuple::loadVars(&SScorr, &data, recoIdx);
                    SScorr.CalculateCorrections();
                }
            eleRecording.r9Full5x5_corrected               = SScorr.Corrected(ShowerShapeCorrectionAdapter::r9                     );
            eleRecording.s4Full5x5_corrected               = SScorr.Corrected(ShowerShapeCorrectionAdapter::s4                     );
            eleRecording.sieieFull5x5_corrected            = SScorr.Corrected(ShowerShapeCorrectionAdapter::sieie                  );
            eleRecording.sieipFull5x5_corrected            = SScorr.Corrected(ShowerShapeCorrectionAdapter::sieip                  );
            eleRecording.scEtaWidth_corrected              = SScorr.Corrected(ShowerShapeCorrectionAdapter::etaWidth               );
            eleRecording.scPhiWidth_corrected              = SScorr.Corrected(ShowerShapeCorrectionAdapter::phiWidth               );
            eleRecording.esEnergyOverSCRawEnergy_corrected = SScorr.Corrected(ShowerShapeCorrectionAdapter::esEnergyOverSCRawEnergy);
            }

        // add Mu block
        record_Mu[0].recoPt  = trigMuons[0].Pt();
        record_Mu[0].recoEta = trigMuons[0].Eta();
        record_Mu[0].deltaR  = trigMuons[0].DeltaR(photon);
        record_Mu[0].trg     = data.GetPtrLong64("muFiredTrgs")[ trigMuons[0].idx() ];
        record_Mu[1].recoPt  = trigMuons[1].Pt();
        record_Mu[1].recoEta = trigMuons[1].Eta();
        record_Mu[1].deltaR  = trigMuons[1].DeltaR(photon);
        record_Mu[1].trg     = data.GetPtrLong64("muFiredTrgs")[ trigMuons[1].idx() ];
        // ZcandP4 does not exist

        TLorentzCand mumuP4 = trigMuons[0] + trigMuons[1];
        TLorentzCand ZcandP4 = mumuP4 + photon;

        if ( data.HasMC() )
        {
            int ZMCidx = data.GetPtrInt("mcMomPID")[mumuP4.daughters().at(0).idx()];
        record_Z.mcPt      = 0;
        }
        record_Z.recoMass  = ZcandP4.M();
        record_Z.recoPt    = ZcandP4.Pt();
        record_Z.isMatched = trigMuons[0].genidx() >= 0 && trigMuons[1].genidx() >= 0;
        record_Z.mumuMass  = mumuP4.M();
        record_Z.mumuPt    = mumuP4.Pt();

        record_evt.run               = data.GetInt("run"); 
        if ( data.HasMC() )
        {
            Float_t* puTrue = data.GetPtrFloat("puTrue");
            Int_t npuInfo = data.GetInt("nPUInfo");
            int _purec = 0;
            for ( int i=0; i<npuInfo; ++i ) if ( data.GetPtrInt("puBX")[i] == 0 ) _purec = puTrue[i];
            
        record_evt.xsweight          = 1.;
        record_evt.genweight         = data.HasMC() ? data.GetFloat("genWeight") : 1;
        record_evt.puwei             = (float) pucalc.GetWeight(record_evt.run, puTrue[1]);
        record_evt.pthat             = data.GetFloat("pthat");
        record_evt.nPU               = _purec;
        }

        record_evt.MET               = data.GetFloat("pfMET");
        record_evt.METPhi            = data.GetFloat("pfMETPhi");
        record_evt.rho               = data.GetFloat("rho");
        record_evt.fixedGridRhoAll   = data.GetFloat("rhoAll");

        record_evt.nVtx              = data.GetInt("nVtx");
        record_evt.HLT               = data.GetLong64("HLTPho");
        record_evt.HLTPhoIsPrescaled = data.GetLong64("HLTPhoIsPrescaled");
        record_evt.event             = data.GetLong64("event"); 


        outtree_->Fill();
        }
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
}
void ZtoMuMuG(std::string ipath, int outID)
{
   char fname[200];
   std::vector<std::string> pathes;

   pathes.push_back(ipath);

   char oname[200];
   sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

   ZtoMuMuG(pathes, oname);
}
std::vector<TLorentzCand> TriggeredDiMuon(TreeReader* dataptr)
{
    const int PASS_HLTBIT = 10; // HLT_Mu17_TrkIsoVVL_Mu8_TrkIsoVVL_DZ @ UL2018

    // muon types from github
    // https://github.com/cms-sw/cmssw/blob/CMSSW_10_6_X/DataFormats/MuonReco/interface/Muon.h
    //    static const unsigned int GlobalMuon     =  1<<1;
    //    static const unsigned int TrackerMuon    =  1<<2;
    //    static const unsigned int StandAloneMuon =  1<<3;
    //    static const unsigned int CaloMuon =  1<<4;
    //    static const unsigned int PFMuon =  1<<5;
    //    static const unsigned int RPCMuon =  1<<6;
    //    static const unsigned int GEMMuon =  1<<7;
    //    static const unsigned int ME0Muon =  1<<8;
    const int WP_GM = 1;
    const int WP_PF = 5;

    Int_t nCand         = dataptr->GetInt("nMu");
    Float_t* pt         = dataptr->GetPtrFloat("muPt");
    Float_t* eta        = dataptr->GetPtrFloat("muEta");
    Float_t* phi        = dataptr->GetPtrFloat("muPhi");
    Int_t* charge       = dataptr->GetPtrInt("muCharge");


    Float_t* muChi2NDF  = dataptr->GetPtrFloat("muChi2NDF");
    Float_t* muD0       = dataptr->GetPtrFloat("muD0");
    Float_t* muDz       = dataptr->GetPtrFloat("muDz");

    Int_t* muType     = dataptr->GetPtrInt("muType");
    Int_t* muStations = dataptr->GetPtrInt("muStations");
    Int_t* muMuonHits = dataptr->GetPtrInt("muMuonHits");
    Int_t* muPixelHits= dataptr->GetPtrInt("muPixelHits");
    Int_t* muTrkLayers= dataptr->GetPtrInt("muTrkLayers");

    Long64_t* trg = dataptr->GetPtrLong64("muFiredTrgs");

    std::vector<TLorentzCand> outputs;
    int testidx = 0;
    for ( Int_t idx = 0; idx < nCand; ++idx )
    {
        for ( int ibit = 0; ibit < 32; ++ibit ) if ( (trg[idx]>>ibit)&1 ) hists.FillStatus("MuonHLTPassedBits", ibit);
        if ( !((muType[idx]>>WP_GM)&1) && !((muType[idx]>>WP_GM)&1) ) continue;
        if ( fabs(eta[idx]) > 2.4 ) continue;

        if ( muChi2NDF[idx] > 10 ) continue;
        if ( muMuonHits[idx] == 0 ) continue;
        if ( muStations[idx] < 2 ) continue;
        if ( fabs(muD0[idx]) > 0.2 ) continue;
        if ( fabs(muDz[idx]) > 0.5 ) continue;
        if ( muPixelHits[idx] == 0 ) continue;
        if ( muTrkLayers[idx] < 6 ) continue;
        if (((trg[idx]>>PASS_HLTBIT)&1) ) hists.FillStatus("NumMuonPassedHLT", testidx++);
        if ( outputs.size() == 0 ) if ( pt[idx] < 17 ) continue;
        if ( outputs.size() == 1 ) if ( pt[idx] <  8 ) continue;

        TLorentzCand output(
                    idx,
                    charge[idx],
                    pt[idx],eta[idx],phi[idx], MASS_MUON );
        int genIdx = FindMatchedIdx_Muon( dataptr, output );
        if ( genIdx >= 0 ) output.SetGenIdx( genIdx );
        outputs.push_back(output);
        LOG_DEBUG("Got Triggered muon : %d in 2", int(outputs.size()) );
        if ( outputs.size() == 2 ) return outputs;
    }
    return std::vector<TLorentzCand>();
}

void RegBranchZMuMu( TTree* t, const std::string& name, rec_Electron* var )
{
    t->Branch( (name+"mcPt").c_str()               ,&var->mcPt         , (name+"mcPt/F").c_str()             );
    t->Branch( (name+"mcEta").c_str()              ,&var->mcEta        , (name+"mcEta/F").c_str()            );
    t->Branch( (name+"recoPt").c_str()             ,&var->recoPt       , (name+"recoPt/F").c_str()           );
    t->Branch( (name+"recoEta").c_str()            ,&var->recoEta      , (name+"recoEta/F").c_str()          );
    t->Branch( (name+"recoPtCalib").c_str()        ,&var->recoPtCalib  , (name+"recoPtCalib/F").c_str()      );
    t->Branch( (name+"recoSCEta").c_str()          ,&var->recoSCEta    , (name+"recoSCEta/F").c_str()        );
    t->Branch( (name+"r9").c_str()                 ,&var->r9           , (name+"r9/F").c_str()               );
    t->Branch( (name+"HoverE").c_str()             ,&var->HoverE       , (name+"HoverE/F").c_str()           );
    t->Branch( (name+"chIsoRaw").c_str()           ,&var->chIsoRaw     , (name+"chIsoRaw/F").c_str()         );
    t->Branch( (name+"phoIsoRaw").c_str()          ,&var->phoIsoRaw    , (name+"phoIsoRaw/F").c_str()        );
    t->Branch( (name+"nhIsoRaw").c_str()           ,&var->nhIsoRaw     , (name+"nhIsoRaw/F").c_str()         );
    t->Branch( (name+"chWorstIso").c_str()         ,&var->chWorstIso   , (name+"chWorstIso/F").c_str()       );
    t->Branch( (name+"rawE").c_str()               ,&var->rawE         , (name+"rawE/F").c_str()             );
    t->Branch( (name+"scEtaWidth").c_str()         ,&var->scEtaWidth   , (name+"scEtaWidth/F").c_str()       );
    t->Branch( (name+"scPhiWidth").c_str()         ,&var->scPhiWidth   , (name+"scPhiWidth/F").c_str()       );
    t->Branch( (name+"esRR").c_str()               ,&var->esRR         , (name+"esRR/F").c_str()             );
    t->Branch( (name+"esEn").c_str()               ,&var->esEn         , (name+"esEn/F").c_str()             );
    t->Branch( (name+"mva").c_str()                ,&var->mva          , (name+"mva/F").c_str()              );
    t->Branch( (name+"mva_nocorr").c_str()         ,&var->mva_nocorr   , (name+"mva_nocorr/F").c_str()       );
    t->Branch( (name+"officalIDmva").c_str()       ,&var->officalIDmva , (name+"officalIDmva/F").c_str()     );
    t->Branch( (name+"r9Full5x5").c_str()          ,&var->r9Full5x5    , (name+"r9Full5x5/F").c_str()        );
    t->Branch( (name+"sieieFull5x5").c_str()       ,&var->sieieFull5x5 , (name+"sieieFull5x5/F").c_str()     );
    t->Branch( (name+"sieipFull5x5").c_str()       ,&var->sieipFull5x5 , (name+"sieipFull5x5/F").c_str()     );
    t->Branch( (name+"sipipFull5x5").c_str()       ,&var->sipipFull5x5 , (name+"sipipFull5x5/F").c_str()     );
    t->Branch( (name+"s4Full5x5").c_str()          ,&var->s4Full5x5    , (name+"s4Full5x5/F").c_str() );
    t->Branch( (name+"esEnergyOverSCRawEnergy").c_str(),&var->esEnergyOverSCRawEnergy,(name+"esEnergyOverSCRawEnergy/F").c_str() );

    t->Branch( (name+"calib_scEtaWidth"  ).c_str(), &var->scEtaWidth_corrected     , (name+"calib_scEtaWidth/F"       ).c_str() );
    t->Branch( (name+"calib_scPhiWidth"  ).c_str(), &var->scPhiWidth_corrected     , (name+"calib_scPhiWidth/F"       ).c_str() );
    t->Branch( (name+"calib_r9Full5x5"   ).c_str(), &var->r9Full5x5_corrected      , (name+"calib_r9Full5x5/F"        ).c_str() );
    t->Branch( (name+"calib_s4Full5x5"   ).c_str(), &var->s4Full5x5_corrected      , (name+"calib_s4Full5x5/F"        ).c_str() );
    t->Branch( (name+"calib_sieieFull5x5").c_str(), &var->sieieFull5x5_corrected   , (name+"calib_sieieFull5x5/F"     ).c_str() );
    t->Branch( (name+"calib_sieipFull5x5").c_str(), &var->sieipFull5x5_corrected   , (name+"calib_sieipFull5x5/F"     ).c_str() );
    t->Branch( (name+"calib_esEnergyOverSCRawEnergy").c_str(), &var->esEnergyOverSCRawEnergy_corrected, (name+"calib_esEnergyOverSCRawEnergy/F").c_str() );


    t->Branch( (name+"recoIdx").c_str()            ,&var->recoIdx      , (name+"recoIdx/I").c_str()          );
    t->Branch( (name+"isMatched").c_str()          ,&var->isMatched    , (name+"isMatched/I").c_str()        );

    t->Branch( (name+"firedTrgsL").c_str()         ,&var->firedTrgsL   , (name+"firedTrgsL/L").c_str()       );
    t->Branch( (name+"idbit").c_str()              ,&var->idbit        , (name+"idbit/I").c_str()            );
}
void RegBranchZMuMu( TTree* t, const std::string& name, rec_Z* var )
{
    t->Branch( (name+".mcPt").c_str()           ,&var->mcPt      , (name+".mcPt/F").c_str()       );
    t->Branch( (name+".recoMass").c_str()       ,&var->recoMass  , (name+".recoMass/F").c_str()   );
    t->Branch( (name+".recoPt").c_str()         ,&var->recoPt    , (name+".recoPt/F").c_str()     );
    t->Branch( (name+".mumuMass").c_str()       ,&var->mumuMass  , (name+".mumuMass/F").c_str()   );
    t->Branch( (name+".mumuPt"  ).c_str()       ,&var->mumuMass  , (name+".mumuPt/F"  ).c_str()   );

    t->Branch( (name+".isMatched").c_str()      ,&var->isMatched , (name+".isMatched/I").c_str()  );
}
void RegBranchZMuMu( TTree* t, const std::string& name, rec_Mu* var )
{
    t->Branch( (name+".recoPt").c_str()         ,&var->recoPt    , (name+".recoPt/F").c_str()     );
    t->Branch( (name+".recoEta").c_str()        ,&var->recoEta   , (name+".recoEta/F").c_str()    );
    t->Branch( (name+".deltaR").c_str()         ,&var->deltaR    , (name+".deltaR/F").c_str()     );
    t->Branch( (name+".trg").c_str()            ,&var->trg       , (name+".trg/L").c_str()        );
}
void RegBranchZMuMu( TTree* t, const string& name, rec_Event* var )
{
    t->Branch("run"               , &var->run,                     "run/I");
    t->Branch("xsweight"          , &var->xsweight,                "xsweight/I");
    t->Branch("pthat"             , &var->pthat,                   "pthat/I");
    t->Branch("nVtx"              , &var->nVtx,                    "nVtx/I");
    t->Branch("nPU"               , &var->nPU,                     "nPU/I");

    t->Branch("rho"               , &var->rho,                     "rho/F");
    t->Branch("fixedGridRhoAll"   , &var->fixedGridRhoAll,         "fixedGridRhoAll/F");
    t->Branch("puwei"             , &var->puwei,                   "puwei/F");
    t->Branch("genWeight"         , &var->genweight,               "genWeight/F");
    t->Branch("MET"               , &var->MET,                     "MET/F");
    t->Branch("METPhi"            , &var->METPhi,                  "METPhi/F");
    
    t->Branch("HLT"               , &var->HLT,                     "HLT/L");
    t->Branch("HLTPhoIsPrescaled" , &var->HLTPhoIsPrescaled,       "HLTPhoIsPrescaled/L");
    t->Branch("event"             , &var->event,                   "event/L");
}

bool PassPhotonPreselection(TreeReader* dataptr, const TLorentzCand& cand)
{
    // HLT_Ele27_WPTight_Gsf
    //const int PASS_HLTBIT = 12;
    //const int HLTWP = 3;

    unsigned idx = cand.idx();
    LOG_DEBUG("cand idx = %d / %d", idx , dataptr->GetInt("nPho") );
    Float_t Et            = dataptr->GetPtrFloat("phoCalibEt")[idx];
    Float_t Eta           = dataptr->GetPtrFloat("phoSCEta")[idx];
    Float_t SigmaIetaIeta = dataptr->GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[idx];
    Float_t HoverE        = dataptr->GetPtrFloat("phoHoverE")[idx];
    Float_t ChWorstIso    = dataptr->GetPtrFloat("phoPFChWorstIso")[idx];
    Float_t PhoIso        = dataptr->GetPtrFloat("phoPFPhoIso")[idx];


    if ( Et < 10 ) return false;
    //if ( fabs(Eta) > 1.4442 && fabs(Eta) < 1.566 ) return false;
    //if ( fabs(Eta) > 3.0 ) return false;
    if (!recoInfo::ValidEtaRegion(Eta) ) return false;

    if ( recoInfo::IsEE(Eta) )
    { // EE
        if ( ChWorstIso > 15.        ) return false;
        if ( PhoIso > 15.            ) return false;
        if ( SigmaIetaIeta > 0.045   ) return false;
        if ( HoverE > 0.05           ) return false;
    }
    else
    { // EB
        if ( ChWorstIso > 15.        ) return false;
        if ( PhoIso > 15.            ) return false;
        if ( SigmaIetaIeta > 0.015   ) return false;
        if ( HoverE > 0.08           ) return false;
    }
    
    return true;
}
int FindMatchedIdx_Muon(TreeReader* dataptr, const TLorentzCand& recoCand) // modification needed
{
    const int NOTHING_MATCHED=-1;
    const double CUT_DELTA_R = 0.20;
    const double CUT_PT_RATIO = 1.0;
    const int PID_Z = 23;
    const int PID_ELECTRON = 11;
    const int STATUS_FINALSTATE = 3;
    if (!dataptr->HasMC() ) return NOTHING_MATCHED;

    Int_t  nMC_         = dataptr->GetInt("nMC");
    Int_t* genPID_      = dataptr->GetPtrInt("mcPID");
    Int_t* genMomPID_   = dataptr->GetPtrInt("mcMomPID");
    Int_t* genStatus_   = dataptr->GetPtrInt("mcStatus");

    Float_t* genpt_     = dataptr->GetPtrFloat("mcPt");
    Float_t* geneta_    = dataptr->GetPtrFloat("mcEta");
    Float_t* genphi_    = dataptr->GetPtrFloat("mcPhi");


    for ( Int_t iMC = 0; iMC < nMC_; ++iMC )
        if ( abs(genPID_[iMC]) == PID_ELECTRON && genStatus_[iMC] <= STATUS_FINALSTATE && genMomPID_[iMC] == PID_Z )
        {
            TLorentzCand genCand(iMC,
                    genPID_[iMC] == PID_ELECTRON ? -1 : 1, // charge
                    genpt_[iMC], geneta_[iMC], genphi_[iMC], MASS_ELECTRON );
        
            if (!recoInfo::InFiducialRegion(genCand) ) continue;
    

            double deltaR = genCand.DeltaR(recoCand);
            double ptratio = (recoCand.Pt()-genCand.Pt()) / genCand.Pt();
            hists.Fill("DeltaR", deltaR);
            hists.Fill("ptratio", ptratio);
            if ( deltaR < CUT_DELTA_R && ptratio < CUT_PT_RATIO )
                return iMC;
        }
    return NOTHING_MATCHED;
}
std::vector<TLorentzCand> RecoPhoton(TreeReader* dataptr)
{
    std::vector<TLorentzCand> outputs;
    for ( Int_t idx = 0; idx < dataptr->GetInt("nPho"); ++idx )
        outputs.emplace_back(
                    idx,
                    0,
                    dataptr->GetPtrFloat("phoCalibEt")[idx], // for photon, et is equiv to pt
                    dataptr->GetPtrFloat("phoEta")[idx],
                    dataptr->GetPtrFloat("phoPhi")[idx],
                    0
                );
    return outputs;
}

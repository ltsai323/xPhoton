#include "xPhoton/xPhoton/interface/xElectrons.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/histMgr.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include "xPhoton/xPhoton/interface/ShowerShapeCorrectionAdapter.h"
#include <TLorentzVector.h>
#include <map>
#include <TNtuple.h>


static histMgr hists;
void xElectrons(
        const std::vector<std::string>& pathes,
        char oname[200],
        const std::string& dataEra )
{
    TreeReader data(pathes);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");

    TTree *outtree_ = new TTree("t", "mini tree");
    TNtuple* nt_sumupgenweight = new TNtuple("genweightsummary", "", "sumupgenweight:hasNon1Val");
    Float_t overallGenweight = 0;
    Float_t hasNon1Val = 0;
    
    rec_Electron record_electrons[2];
    rec_Z record_Z;
    rec_Event record_evt;

    RegBranch( outtree_, "electron_tag.", &record_electrons[0] );
    RegBranch( outtree_, "", &record_electrons[1] ); // probe electron, like a photon
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


    //std::string dataEra = "UL2018";
    //ShowerShapeCorrectionAdapter SScorr( dataEra, data.HasMC() );
    LOG_DEBUG("inptu dataera = %s",dataEra.c_str());
    ShowerShapeCorrectionAdapter* SScorr = ( (dataEra != "UL2016PreVFP") && (dataEra != "UL2016PostVFP") ) ?
        new ShowerShapeCorrectionAdapter( dataEra, data.HasMC() ) : nullptr;
    PhotonMVACalculator mvaloader( &data, dataEra );
    //TFile* f_showershapecorrection;
    //TGraph *tgr[8];
    PUWeightCalculator pucalc;

    //std::map<std::string, TGraph*> endcapCorrections;
    //std::map<std::string, TGraph*> barrelCorrections;
    if ( data.HasMC() )
    {
    //f_showershapecorrection = TFile::Open( ExternalFilesMgr::RooFile_ShowerShapeCorrection() );
    /*
    endcapCorrections["scEtaWidth"  ] = (TGraph*)f_showershapecorrection->Get("transfEtaWidthEE");
    endcapCorrections["s4"          ] = (TGraph*)f_showershapecorrection->Get("transfS4EE");
    endcapCorrections["r9Full5x5"   ] = (TGraph*)f_showershapecorrection->Get("transffull5x5R9EE");
    endcapCorrections["sieieFull5x5"] = (TGraph*)f_showershapecorrection->Get("transffull5x5sieieEE");

    barrelCorrections["scEtaWidth"  ] = (TGraph*)f_showershapecorrection->Get("transfEtaWidthEB");
    barrelCorrections["s4"          ] = (TGraph*)f_showershapecorrection->Get("transfS4EB");
    barrelCorrections["r9Full5x5"   ] = (TGraph*)f_showershapecorrection->Get("transffull5x5R9EB");
    barrelCorrections["sieieFull5x5"] = (TGraph*)f_showershapecorrection->Get("transffull5x5sieieEB");
    tgr[0] = (TGraph*) f_showershapecorrection->Get("transfEtaWidthEB");
    tgr[1] = (TGraph*) f_showershapecorrection->Get("transfS4EB");
    tgr[2] = (TGraph*) f_showershapecorrection->Get("transffull5x5R9EB");
    tgr[3] = (TGraph*) f_showershapecorrection->Get("transffull5x5sieieEB");

    tgr[4] = (TGraph*) f_showershapecorrection->Get("transfEtaWidthEE");
    tgr[5] = (TGraph*) f_showershapecorrection->Get("transfS4EE");
    tgr[6] = (TGraph*) f_showershapecorrection->Get("transffull5x5R9EE");
    tgr[7] = (TGraph*) f_showershapecorrection->Get("transffull5x5sieieEE");
    */

    pucalc.Init( ExternalFilesMgr::RooFile_PileUp(dataEra) );
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

        LOG_DEBUG(" check point 01");
        //std::vector<TLorentzCand> electronpool = RecoElectrons(&data);
        std::vector<TLorentzCand> electronpool = RecoElectronsInPhotonCollection_(&data);
        TLorentzCand tag_electron = TriggeredElectron(&data);
        if ( tag_electron.IsZombie() ) continue;

        LOG_DEBUG(" check point 02");
        for ( TLorentzCand& electron : electronpool )
        {
            int genIdx = FindMatchedIdx_Electron( &data, electron );
            if ( genIdx < 0 ) continue;
            electron.SetGenIdx(genIdx);
        }
        LOG_DEBUG(" check point 03");

        //for ( TLorentzCand& cand : electronpool ) cand.SetAlive( PassElectronPreselection_(&data, ELECTRONWORKINGPOINT, cand) );
        for ( TLorentzCand& cand : electronpool ) cand.SetAlive( PassPhotonPreselection_(&data, cand) );
        hists.FillStatus("eventStat", 0);
        LOG_DEBUG(" check point 04");

        int aliveEleNum = 0;
        for ( auto ele : electronpool )
            if (!ele.IsZombie() )
                ++aliveEleNum;

        hists.Fill("Nele", aliveEleNum);
        //if ( aliveEleNum < 2 ) continue;
        if ( aliveEleNum == 0 ) continue;

        hists.FillStatus("eventStat", 1);

        TLorentzCand ZcandP4;
        TLorentzCand probe_electron;
        LOG_DEBUG( "ELECTRON (0,1) = Pt(%.2f,%.2f), Eta(%.2f,%.2f), charge(%d,%d)",
                electronpool[0].Pt(), electronpool[1].Pt(),
                electronpool[0].Eta(), electronpool[1].Eta(),
                electronpool[0].charge(), electronpool[1].charge() );
        for ( auto& fake_photon : electronpool )
        {
            if ( fake_photon.IsZombie() ) continue;
            ZcandP4 = tag_electron + fake_photon;
            ZcandP4.SetAlive(false);
            if ( ZcandP4.M() < MASS_Z-WINDOW_Z ) continue; // lower bond
            hists.FillStatus("ZRecoStat", 5);
            if ( ZcandP4.M() > MASS_Z+WINDOW_Z ) continue; // upper bond
            hists.FillStatus("ZRecoStat", 6);
            ZcandP4.SetAlive(true);
            probe_electron = fake_photon;

            break;
        }


        if ( ZcandP4.IsZombie() ) continue;
        hists.FillStatus("eventStat", 2);
        if ( data.HasMC() )
        { LOG_DEBUG("reco Z candidate contains matched gen electron in idx (%d,%d)", ZcandP4.daughters().at(0).genidx(), ZcandP4.daughters().at(1).genidx()); }



    // clear everything.
        LOG_DEBUG("starting to fill event");
        ClearStruct(&record_electrons[0]);
        ClearStruct(&record_electrons[1]);
        ClearStruct(&record_Z);
        ClearStruct(&record_evt);

        LOG_DEBUG("evt fill status 01");
        { // fillin tag electron information
            int recoIdx = tag_electron.idx();
            rec_Electron& eleRecording = record_electrons[0];
          
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
            eleRecording.officalIDmva = data.GetPtrFloat("eleIDMVAIso")[recoIdx];
            eleRecording.r9Full5x5    = data.GetPtrFloat("eleR9Full5x5")[recoIdx];
            eleRecording.sieieFull5x5 = data.GetPtrFloat("eleSigmaIEtaIEtaFull5x5")[recoIdx];
            eleRecording.sieipFull5x5 = 0; // = data.GetPtrFloat("eleSigmaIEtaIPhiFull5x5")[recoIdx]; no sieip in electron
            eleRecording.sipipFull5x5 = data.GetPtrFloat("eleSigmaIPhiIPhiFull5x5")[recoIdx];
            //eleRecording.e2x2Full5x5  = 0; //data.GetPtrFloat("")[recoIdx];
            //eleRecording.e2x5Full5x5  = 0; //data.GetPtrFloat("")[recoIdx];

            eleRecording.isMatched    = tag_electron.genidx() >= 0;

            eleRecording.mva_corrected= 0; //data.GetPtrFloat("")[recoIdx];
            eleRecording.r9Full5x5_corrected               = 0;
            eleRecording.s4Full5x5_corrected               = 0;
            eleRecording.sieieFull5x5_corrected            = 0;
            eleRecording.sieipFull5x5_corrected            = 0;
            eleRecording.scEtaWidth_corrected              = 0;
            eleRecording.scPhiWidth_corrected              = 0;
            eleRecording.esEnergyOverSCRawEnergy_corrected = 0;
        }
        LOG_DEBUG("evt fill status 02");
        { // fill in probe electron information
        LOG_DEBUG("evt fill status 02.1");
            int recoIdx = probe_electron.idx();
        LOG_DEBUG("evt fill status 02.2");
            rec_Electron& eleRecording = record_electrons[1];
        LOG_DEBUG("evt fill status 02.3");
                    
            eleRecording.recoPt       = data.GetPtrFloat("phoEt")[recoIdx];
            eleRecording.recoEta      = data.GetPtrFloat("phoEta")[recoIdx];
            eleRecording.recoPhi      = data.GetPtrFloat("phoPhi")[recoIdx];
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
        LOG_DEBUG("evt fill status 02.4");
            eleRecording.mva = mvaloader.GetMVA_noIso(recoIdx);
        LOG_DEBUG("evt fill status 02.5");
            eleRecording.officalIDmva = data.GetPtrFloat("phoIDMVA")[recoIdx];
            eleRecording.r9Full5x5    = data.GetPtrFloat("phoR9Full5x5")[recoIdx];
            eleRecording.sieieFull5x5 = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[recoIdx];
            eleRecording.sieipFull5x5 = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5")[recoIdx];
            eleRecording.sipipFull5x5 = data.GetPtrFloat("phoSigmaIPhiIPhiFull5x5")[recoIdx];
            eleRecording.s4Full5x5    = data.GetPtrFloat("phoE2x2Full5x5")[recoIdx] /
                                        data.GetPtrFloat("phoE5x5Full5x5")[recoIdx];
            eleRecording.esEnergyOverSCRawEnergy = eleRecording.esEn / eleRecording.rawE;

            eleRecording.isMatched    = probe_electron.genidx() >= 0;
            eleRecording.firedTrgsL   = data.GetPtrLong64("phoFiredSingleTrgs")[recoIdx];
            eleRecording.idbit        = ((UShort_t*)data.GetPtrShort("phoIDbit"))[recoIdx];

        LOG_DEBUG("evt fill status 02.6");
            LOG_DEBUG("ss corr is null? %d", SScorr == nullptr);
            if ( data.HasMC() && SScorr != nullptr )
            {
                int genIdx = probe_electron.genidx();
            eleRecording.mcE          = genIdx < 0 ? 0 : data.GetPtrFloat("mcE")[genIdx];
            eleRecording.mcPt         = genIdx < 0 ? 0 : data.GetPtrFloat("mcPt")[genIdx];
            eleRecording.mcEta        = genIdx < 0 ? 0 : data.GetPtrFloat("mcEta")[genIdx];
            eleRecording.mcPhi        = genIdx < 0 ? 0 : data.GetPtrFloat("mcPhi")[genIdx];
            
            
                if (!ShowerShapeCorrectionParameters_ggNtuple::isSameEvent(SScorr, &data, recoIdx) )
                {
                    ShowerShapeCorrectionParameters_ggNtuple::loadVars(SScorr, &data, recoIdx);
                    SScorr->CalculateCorrections();
                }
            eleRecording.mva_corrected = mvaloader.GetMVA_noIso(recoIdx, SScorr);
            eleRecording.r9Full5x5_corrected               = SScorr->Corrected(ShowerShapeCorrectionAdapter::r9                     );
            eleRecording.s4Full5x5_corrected               = SScorr->Corrected(ShowerShapeCorrectionAdapter::s4                     );
            eleRecording.sieieFull5x5_corrected            = SScorr->Corrected(ShowerShapeCorrectionAdapter::sieie                  );
            eleRecording.sieipFull5x5_corrected            = SScorr->Corrected(ShowerShapeCorrectionAdapter::sieip                  );
            eleRecording.scEtaWidth_corrected              = SScorr->Corrected(ShowerShapeCorrectionAdapter::etaWidth               );
            eleRecording.scPhiWidth_corrected              = SScorr->Corrected(ShowerShapeCorrectionAdapter::phiWidth               );
            eleRecording.esEnergyOverSCRawEnergy_corrected = SScorr->Corrected(ShowerShapeCorrectionAdapter::esEnergyOverSCRawEnergy);
            }
        }
        LOG_DEBUG("evt fill status 03");

        if ( data.HasMC() )
        {
            int ZMCidx = data.GetPtrInt("mcMomPID")[ZcandP4.daughters().at(0).idx()];
        record_Z.mcE       = 0;
        record_Z.mcPt      = 0;
        record_Z.mcEta     = 0;
        record_Z.mcPhi     = 0;
        }
        LOG_DEBUG("evt fill status 04");
        record_Z.recoMass  = ZcandP4.M();
        record_Z.recoE     = ZcandP4.Energy();
        record_Z.recoPt    = ZcandP4.Pt();
        record_Z.recoEta   = ZcandP4.Eta();
        record_Z.recoPhi   = ZcandP4.Phi();
        record_Z.isMatched = ZcandP4.daughters().at(0).genidx() >= 0 && ZcandP4.daughters().at(1).genidx() >= 0;

        record_evt.run               = data.GetInt("run"); 
        LOG_DEBUG("evt fill status 05");
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
        LOG_DEBUG("evt fill status 06");

        record_evt.MET               = data.GetFloat("pfMET");
        record_evt.METPhi            = data.GetFloat("pfMETPhi");
        record_evt.rho               = data.GetFloat("rho");
        record_evt.fixedGridRhoAll   = data.GetFloat("rhoAll");

        record_evt.nVtx              = data.GetInt("nVtx");
        record_evt.HLT               = data.GetLong64("HLTPho");
        record_evt.HLTPhoIsPrescaled = data.GetLong64("HLTPhoIsPrescaled");
        record_evt.event             = data.GetLong64("event"); 


        LOG_DEBUG("evt fill status 07");
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
    /*
    if ( data.HasMC() )
	    f_showershapecorrection->Close();
    */
}
void xElectrons(const std::vector<std::string>& ipath, int outID, const std::string& dataEra )
{
   char fname[200];
   //std::vector<std::string> pathes;

   //pathes.push_back(ipath);

   char oname[200];
   sprintf(oname, "output_job_Zee_%d.root", outID);

   xElectrons(ipath, oname, dataEra);
}
std::vector<TLorentzCand> RecoElectrons(TreeReader* dataptr)
{
    std::vector<TLorentzCand> outputs;
    for ( Int_t idx = 0; idx < dataptr->GetInt("nEle"); ++idx )
        outputs.emplace_back(
                    idx,
                    dataptr->GetPtrInt  ("eleCharge")[idx],
                    dataptr->GetPtrFloat("elePt")[idx],
                    dataptr->GetPtrFloat("eleEta")[idx],
                    dataptr->GetPtrFloat("elePhi")[idx],
                    MASS_ELECTRON
                );
    return outputs;
}
std::vector<TLorentzCand> RecoElectronsInPhotonCollection_(TreeReader* dataptr)
{
    std::vector<TLorentzCand> outputs;
    for ( Int_t idx = 0; idx < dataptr->GetInt("nPho"); ++idx )
        outputs.emplace_back(
                    idx,
                    0,
                    //dataptr->GetPtrFloat("phoPt")[idx],
                    dataptr->GetPtrFloat("phoCalibEt")[idx], // for photon, et is equiv to pt
                    dataptr->GetPtrFloat("phoEta")[idx],
                    dataptr->GetPtrFloat("phoPhi")[idx],
                    MASS_ELECTRON
                );
    return outputs;
}
TLorentzCand TriggeredElectron(TreeReader* dataptr)
{
    // const int PASS_HLTBIT = 12; // HLT_Ele27_WPTight_Gsf @ 2016ReReco
    const int PASS_HLTBIT = 13; // HLT_Ele32_eta2p1_WPTight_Gsf @ UL2018
    const int HLTWP = 3;

    for ( Int_t idx = 0; idx < dataptr->GetInt("nEle"); ++idx )
    {
        if ( dataptr->GetPtrFloat("elePt")[idx] < 27. ) continue;
        UShort_t* id_bits = (UShort_t*)dataptr->GetPtrShort("eleIDbit");
        if (!(id_bits[idx]>>HLTWP&1) ) continue;
        if (!dataptr->HasMC() )
        {
            ULong64_t* hlt_bits = (ULong64_t*) dataptr->GetPtrLong64("eleFiredSingleTrgs");
            if (!(hlt_bits[idx]>>PASS_HLTBIT&1) ) continue;
        }

        TLorentzCand output(
                    idx,
                    dataptr->GetPtrInt  ("eleCharge")[idx],
                    dataptr->GetPtrFloat("elePt")[idx],
                    dataptr->GetPtrFloat("eleEta")[idx],
                    dataptr->GetPtrFloat("elePhi")[idx],
                    MASS_ELECTRON
                );
        int genIdx = FindMatchedIdx_Electron( dataptr, output );
        if ( genIdx >= 0 ) output.SetGenIdx( genIdx );
        return output;
    }
    return TLorentzCand();
}

bool PassElectronPreselection_(TreeReader* dataptr, int WP, const TLorentzCand& cand)
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
void RegBranch( TTree* t, const std::string& name, rec_Electron* var )
{
    t->Branch( (name+"mcE").c_str()                ,&var->mcE          , (name+"mcE/F").c_str()              );
    t->Branch( (name+"mcPt").c_str()               ,&var->mcPt         , (name+"mcPt/F").c_str()             );
    t->Branch( (name+"mcEta").c_str()              ,&var->mcEta        , (name+"mcEta/F").c_str()            );
    t->Branch( (name+"mcPhi").c_str()              ,&var->mcPhi        , (name+"mcPhi/F").c_str()            );
    t->Branch( (name+"recoPt").c_str()             ,&var->recoPt       , (name+"recoPt/F").c_str()           );
    t->Branch( (name+"recoEta").c_str()            ,&var->recoEta      , (name+"recoEta/F").c_str()          );
    t->Branch( (name+"recoPhi").c_str()            ,&var->recoPhi      , (name+"recoPhi/F").c_str()          );
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
    t->Branch( (name+"officalIDmva").c_str()       ,&var->officalIDmva , (name+"officalIDmva/F").c_str()     );
    t->Branch( (name+"r9Full5x5").c_str()          ,&var->r9Full5x5    , (name+"r9Full5x5/F").c_str()        );
    t->Branch( (name+"sieieFull5x5").c_str()       ,&var->sieieFull5x5 , (name+"sieieFull5x5/F").c_str()     );
    t->Branch( (name+"sieipFull5x5").c_str()       ,&var->sieipFull5x5 , (name+"sieipFull5x5/F").c_str()     );
    t->Branch( (name+"sipipFull5x5").c_str()       ,&var->sipipFull5x5 , (name+"sipipFull5x5/F").c_str()     );
    //t->Branch( (name+"e2x2Full5x5").c_str()        ,&var->e2x2Full5x5  , (name+"e2x2Full5x5/F").c_str()      );
    //t->Branch( (name+"e2x5Full5x5").c_str()        ,&var->e2x5Full5x5  , (name+"e2x5Full5x5/F").c_str()      );
    t->Branch( (name+"s4Full5x5").c_str()          ,&var->s4Full5x5    , (name+"s4Full5x5/F").c_str() );
    t->Branch( (name+"esEnergyOverSCRawEnergy").c_str(),&var->esEnergyOverSCRawEnergy,(name+"esEnergyOverSCRawEnergy/F").c_str() );
    /*
    t->Branch( (name+"calib_scEtaWidth"  ).c_str(), &var->scEtaWidth_corrected     , (name+"calib_scEtaWidth/F").c_str()      );
    t->Branch( (name+"calib_r9Full5x5"   ).c_str(), &var->r9Full5x5_corrected      , (name+"calib_r9Full5x5/F").c_str()      );
    t->Branch( (name+"calib_s4"          ).c_str(), &var->s4_corrected             , (name+"calib_s4/F").c_str()      );
    t->Branch( (name+"calib_sieieFull5x5").c_str(), &var->sieieFull5x5_corrected   , (name+"calib_sieieFull5x5/F").c_str()      );
    */

    t->Branch( (name+"calib_mva"         ).c_str(), &var->mva_corrected            , (name+"calib_mva/F").c_str()        );
    t->Branch( (name+"calib_scEtaWidth"  ).c_str(), &var->scEtaWidth_corrected     , (name+"calib_scEtaWidth/F"       ).c_str() );
    t->Branch( (name+"calib_scPhiWidth"  ).c_str(), &var->scPhiWidth_corrected     , (name+"calib_scPhiWidth/F"       ).c_str() );
    t->Branch( (name+"calib_r9Full5x5"   ).c_str(), &var->r9Full5x5_corrected      , (name+"calib_r9Full5x5/F"        ).c_str() );
    t->Branch( (name+"calib_s4Full5x5"   ).c_str(), &var->s4Full5x5_corrected      , (name+"calib_s4Full5x5/F"        ).c_str() );
    t->Branch( (name+"calib_sieieFull5x5").c_str(), &var->sieieFull5x5_corrected   , (name+"calib_sieieFull5x5/F"     ).c_str() );
    t->Branch( (name+"calib_sieipFull5x5").c_str(), &var->sieipFull5x5_corrected   , (name+"calib_sieipFull5x5/F"     ).c_str() );
    t->Branch( (name+"calib_esEnergyOverSCRawEnergy").c_str(), &var->esEnergyOverSCRawEnergy_corrected, (name+"calib_esEnergyOverSCRawEnergy/F").c_str() );


    t->Branch( (name+"isMatched").c_str()          ,&var->isMatched    , (name+"isMatched/I").c_str()        );

    t->Branch( (name+"firedTrgsL").c_str()         ,&var->firedTrgsL   , (name+"firedTrgsL/L").c_str()       );
    t->Branch( (name+"idbit").c_str()              ,&var->idbit        , (name+"idbit/I").c_str()            );
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

bool PassPhotonPreselection_(TreeReader* dataptr, const TLorentzCand& cand)
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
bool PassTagElePreselection_(TreeReader* dataptr, const TLorentzCand& cand)
{
    unsigned idx = cand.idx();
    // HLT_Ele27_WPTight_Gsf
    const int PASS_HLTBIT = -1; // HLT selected afterward

    ULong64_t Trigs =  ((ULong64_t*) dataptr->GetPtrLong64("phoFiredSingleTrgs") ) [idx];
    Int_t EleVeto = dataptr->GetPtrInt("phoEleVeto")[idx];



    if (!dataptr->HasMC() )
    { // HLT selections
        if ( Trigs == 0 ) return false;

        if ( PASS_HLTBIT > 0 )
        { // although ULong64_t used. but only 0~31 bits recorded in ROOT. bit larger than 31 is useless.
            int hltbit = PASS_HLTBIT;
            if ( ((Trigs>>hltbit)&1) == 0 ) return false;
        }
    }
    if ( EleVeto == 1 ) return false; // select electron
  

    return true;
}
int FindMatchedIdx_Electron(TreeReader* dataptr, const TLorentzCand& recoCand)
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

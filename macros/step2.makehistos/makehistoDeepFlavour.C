#define MakeHistoData_cxx
#define MakeHistoSIG_cxx
#define MakeHistoQCD_cxx
#include "makehisto.h"
//#include "HLTTriggerBitSetting.cc"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>
#include <iostream>
#include <TLorentzVector.h>


#include "MakeHistoData.h"
#include "MakeHistoSIG.h"
#include "MakeHistoQCD.h"







// QCD section {{{
EvtSelMgr EvtSelFactory(const MakeHistoQCD& loadvar);
void Fill_AllCTagReshaped( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight, const MakeHistoQCD& loadvars);
void SumNormalization( const EventBinning& bin, Normalization_CTagReshaped& N,const MakeHistoQCD& loadvars );
void LoopQCD( Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename, int processNEvt = -1 );
EventBinning BinningFactory(const MakeHistoQCD & v) { return  EventBinning(v.recoPt     ,v.recoEta,v.jetPt,v.jetY,v.chIsoRaw   ); }


EvtSelMgr EvtSelFactory(const MakeHistoQCD& loadvar)
{
    bool isMC          = true;
    bool isQCD         = true;
    bool HLTOPTION     = true;
    EvtSelMgr output(isMC,isQCD,HLTOPTION);

    //output.jethadflvr    = loadvar.jetHadFlvr;
    //output.chIso         = loadvar.chIsoRaw;
    //output.phoEta        = loadvar.recoEta;
    //output.isMatched     = loadvar.isMatched;

    //output.jetPt         = loadvar.jetPt;
    //output.jetEta        = loadvar.jetEta;
    //output.cScore        = loadvar.jetDeepCSVTags_c;
    //output.jetID         = loadvar.jetID;
    //output.jetPUIDbit    = loadvar.jetPUIDbit;
    //output.jetSubVtxMass = loadvar.jetSubVtxMass;
    //output.CvsL          = loadvar.DeepCSV_CvsL;
    //output.passMaxPUcut  = loadvar.passMaxPUcut;

    //output.recoSCEta     = loadvar.recoSCEta;
    //output.sieieFull5x5  = loadvar.sieieFull5x5;
    //output.HoverE        = loadvar.HoverE;
    //output.MET           = loadvar.MET;
    //output.phoPt         = loadvar.recoPt;
    //output.eleVeto       = loadvar.eleVeto;

    //output.phoFiredTrgs  = loadvar.phoFiredTrgs;
    output.SetUsedVar_4(loadvar.jetHadFlvr);
    output.SetUsedVar_3(
        loadvar.chIsoRaw,
        loadvar.recoEta,
        loadvar.isMatched);

    output.SetUsedVar_2(
        loadvar.jetPt,
        loadvar.jetEta,
        loadvar.jetDeepCSVTags_c,
        loadvar.jetID,
        loadvar.jetPUIDbit,
        loadvar.jetSubVtxMass,
        loadvar.DeepCSV_CvsL,
        loadvar.passMaxPUcut);

    output.SetUsedVar_1(
        loadvar.recoSCEta,
        loadvar.sieieFull5x5,
        loadvar.HoverE);
    output.SetUsedVar_0(
        loadvar.MET,
        loadvar.recoPt,
        loadvar.eleVeto,
        0);
        //loadvar.phoFillIdx);

    output.SetUsedVar__(loadvar.phoFiredTrgs);
    return output;
}
void Fill_AllCTagReshaped( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight, const MakeHistoQCD& loadvars)
{
    Fill_allctagreshaped_general(bin,h,val, evt_weight,
            loadvars.DeepFlavour_ctagWeight_central,
            loadvars.DeepFlavour_ctagWeight_PUWeightUp,
            loadvars.DeepFlavour_ctagWeight_PUWeightDown,
            loadvars.DeepFlavour_ctagWeight_StatUp,
            loadvars.DeepFlavour_ctagWeight_StatDown
            );
}
void SumNormalization( const EventBinning& bin, Normalization_CTagReshaped& N,const MakeHistoQCD& loadvars )
{
    normalization_ctagreshaped& n = N.binned_norm[bin.pEtaBin][bin.jEtaBin][bin.pPtBin];
    n.Add(
            loadvars.DeepFlavour_ctagWeight_central,
            loadvars.DeepFlavour_ctagWeight_PUWeightUp,
            loadvars.DeepFlavour_ctagWeight_PUWeightDown,
            loadvars.DeepFlavour_ctagWeight_StatUp,
            loadvars.DeepFlavour_ctagWeight_StatDown
            );
}

void LoopQCD( Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename, int processNEvt = -1 )
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();

    //if (fChain == 0) return;
    TRandom3 *trd = new TRandom3();

    TFile *fout = new TFile( Form("makehisto_%s.root", dataTYPE),"recreate");
    fout->cd();

    LOG("output file : makehisto_%s.root", dataTYPE);

    Hists* BDT_QCD_signalRegion = Hists_BDT("BDT_QCD_signalRegion", "calib_mva");
    Hists* BDT_QCD_dataSideband = Hists_BDT("BDT_QCD_dataSideband", "calib_mva");
    Hists* BDT_QCD_signalRegion_shapeUncUp = Hists_BDT("BDT_QCD_signalRegion_shapeUncUp", "mva");
    Hists* BDT_QCD_dataSideband_shapeUncUp = Hists_BDT("BDT_QCD_dataSideband_shapeUncUp", "mva");


    Hists_CTagReshaped* jettag0_QCD_DiJetL_signalRegion = new Hists_CTagReshaped("jettag0_QCD_DiJetL_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_DiJetL_dataSideband = new Hists_CTagReshaped("jettag0_QCD_DiJetL_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_DiJetC_signalRegion = new Hists_CTagReshaped("jettag0_QCD_DiJetC_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_DiJetC_dataSideband = new Hists_CTagReshaped("jettag0_QCD_DiJetC_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_DiJetB_signalRegion = new Hists_CTagReshaped("jettag0_QCD_DiJetB_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_DiJetB_dataSideband = new Hists_CTagReshaped("jettag0_QCD_DiJetB_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_GJetsL_signalRegion = new Hists_CTagReshaped("jettag0_QCD_GJetsL_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_GJetsL_dataSideband = new Hists_CTagReshaped("jettag0_QCD_GJetsL_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_GJetsC_signalRegion = new Hists_CTagReshaped("jettag0_QCD_GJetsC_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_GJetsC_dataSideband = new Hists_CTagReshaped("jettag0_QCD_GJetsC_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_GJetsB_signalRegion = new Hists_CTagReshaped("jettag0_QCD_GJetsB_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_QCD_GJetsB_dataSideband = new Hists_CTagReshaped("jettag0_QCD_GJetsB_dataSideband", "DeepFlavour.bScore");

    Hists_CTagReshaped* jettag1_QCD_DiJetL_signalRegion = new Hists_CTagReshaped("jettag1_QCD_DiJetL_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_DiJetL_dataSideband = new Hists_CTagReshaped("jettag1_QCD_DiJetL_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_DiJetC_signalRegion = new Hists_CTagReshaped("jettag1_QCD_DiJetC_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_DiJetC_dataSideband = new Hists_CTagReshaped("jettag1_QCD_DiJetC_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_DiJetB_signalRegion = new Hists_CTagReshaped("jettag1_QCD_DiJetB_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_DiJetB_dataSideband = new Hists_CTagReshaped("jettag1_QCD_DiJetB_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_GJetsL_signalRegion = new Hists_CTagReshaped("jettag1_QCD_GJetsL_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_GJetsL_dataSideband = new Hists_CTagReshaped("jettag1_QCD_GJetsL_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_GJetsC_signalRegion = new Hists_CTagReshaped("jettag1_QCD_GJetsC_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_GJetsC_dataSideband = new Hists_CTagReshaped("jettag1_QCD_GJetsC_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_GJetsB_signalRegion = new Hists_CTagReshaped("jettag1_QCD_GJetsB_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_QCD_GJetsB_dataSideband = new Hists_CTagReshaped("jettag1_QCD_GJetsB_dataSideband", "DeepFlavour.CvsL");

    Hists_CTagReshaped* jettag2_QCD_DiJetL_signalRegion = new Hists_CTagReshaped("jettag2_QCD_DiJetL_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_DiJetL_dataSideband = new Hists_CTagReshaped("jettag2_QCD_DiJetL_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_DiJetC_signalRegion = new Hists_CTagReshaped("jettag2_QCD_DiJetC_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_DiJetC_dataSideband = new Hists_CTagReshaped("jettag2_QCD_DiJetC_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_DiJetB_signalRegion = new Hists_CTagReshaped("jettag2_QCD_DiJetB_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_DiJetB_dataSideband = new Hists_CTagReshaped("jettag2_QCD_DiJetB_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_GJetsL_signalRegion = new Hists_CTagReshaped("jettag2_QCD_GJetsL_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_GJetsL_dataSideband = new Hists_CTagReshaped("jettag2_QCD_GJetsL_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_GJetsC_signalRegion = new Hists_CTagReshaped("jettag2_QCD_GJetsC_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_GJetsC_dataSideband = new Hists_CTagReshaped("jettag2_QCD_GJetsC_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_GJetsB_signalRegion = new Hists_CTagReshaped("jettag2_QCD_GJetsB_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_QCD_GJetsB_dataSideband = new Hists_CTagReshaped("jettag2_QCD_GJetsB_dataSideband", "DeepFlavour.CvsB");

    Hists* jettag3_QCD_DiJetL_signalRegion = Hists_SubVtxMass("jettag3_QCD_DiJetL_signalRegion", "jetSubVtxMass");
    Hists* jettag3_QCD_DiJetL_dataSideband = Hists_SubVtxMass("jettag3_QCD_DiJetL_dataSideband", "jetSubVtxMass");
    Hists* jettag3_QCD_DiJetC_signalRegion = Hists_SubVtxMass("jettag3_QCD_DiJetC_signalRegion", "jetSubVtxMass");
    Hists* jettag3_QCD_DiJetC_dataSideband = Hists_SubVtxMass("jettag3_QCD_DiJetC_dataSideband", "jetSubVtxMass");
    Hists* jettag3_QCD_DiJetB_signalRegion = Hists_SubVtxMass("jettag3_QCD_DiJetB_signalRegion", "jetSubVtxMass");
    Hists* jettag3_QCD_DiJetB_dataSideband = Hists_SubVtxMass("jettag3_QCD_DiJetB_dataSideband", "jetSubVtxMass");
    Hists* jettag3_QCD_GJetsL_signalRegion = Hists_SubVtxMass("jettag3_QCD_GJetsL_signalRegion", "jetSubVtxMass");
    Hists* jettag3_QCD_GJetsL_dataSideband = Hists_SubVtxMass("jettag3_QCD_GJetsL_dataSideband", "jetSubVtxMass");
    Hists* jettag3_QCD_GJetsC_signalRegion = Hists_SubVtxMass("jettag3_QCD_GJetsC_signalRegion", "jetSubVtxMass");
    Hists* jettag3_QCD_GJetsC_dataSideband = Hists_SubVtxMass("jettag3_QCD_GJetsC_dataSideband", "jetSubVtxMass");
    Hists* jettag3_QCD_GJetsB_signalRegion = Hists_SubVtxMass("jettag3_QCD_GJetsB_signalRegion", "jetSubVtxMass");
    Hists* jettag3_QCD_GJetsB_dataSideband = Hists_SubVtxMass("jettag3_QCD_GJetsB_dataSideband", "jetSubVtxMass");


    Normalization_CTagReshaped norm_QCD_DiJetL_signalRegion;
    Normalization_CTagReshaped norm_QCD_DiJetL_dataSideband;
    Normalization_CTagReshaped norm_QCD_DiJetC_signalRegion;
    Normalization_CTagReshaped norm_QCD_DiJetC_dataSideband;
    Normalization_CTagReshaped norm_QCD_DiJetB_signalRegion;
    Normalization_CTagReshaped norm_QCD_DiJetB_dataSideband;
    Normalization_CTagReshaped norm_QCD_GJetsL_signalRegion;
    Normalization_CTagReshaped norm_QCD_GJetsL_dataSideband;
    Normalization_CTagReshaped norm_QCD_GJetsC_signalRegion;
    Normalization_CTagReshaped norm_QCD_GJetsC_dataSideband;
    Normalization_CTagReshaped norm_QCD_GJetsB_signalRegion;
    Normalization_CTagReshaped norm_QCD_GJetsB_dataSideband;

    TFile* iii = TFile::Open(inputfilename);
    TTree* ttt = (TTree*) iii->Get("t");
    MakeHistoQCD load_qcd(ttt);

    Long64_t nentries = processNEvt > 0 ? processNEvt : load_qcd.fChain->GetEntries();

    LOG("Looping in %lli entries", nentries);

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = load_qcd.LoadTree(jentry);
        
        if (ientry < 0) break;
        nb = load_qcd.GetEntry(jentry); nbytes += nb;

        if (jentry % 100000 == 0){ fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries); }


        Float_t eventweight = load_qcd.mcweight * load_qcd.puwei * load_qcd.weight_passMaxPUcut;

	
        const EventBinning evtbin = BinningFactory(load_qcd);
        int hltbit = TriggerBit(dataERA, evtbin.pPtBin);
        EvtSelMgr sel = EvtSelFactory(load_qcd);
        bool isFakePhoton =
            (load_qcd.isMatched!=1 && load_qcd.isConverted!=1 && load_qcd.isMatchedEle!=1 )?
            1 : 0;

        // preselections
        if (!sel.PassPhotonPreSelection(evtbin.pPtBin) ) continue;
        if (!sel.InFiducialRegion() ) continue;
        if (!sel.PassJetAdditionalSelection(extracut) ) continue;
        if (!sel.PassHLT(hltbit) ) continue; // indeed it is useless in signal MC


        if ( evtbin.isSignalRegion &&!isFakePhoton )
        {
            Fill(evtbin,BDT_QCD_signalRegion           , load_qcd.calib_mva,eventweight);
            Fill(evtbin,BDT_QCD_signalRegion_shapeUncUp, load_qcd.mva      ,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton )
        {
            Fill(evtbin,BDT_QCD_dataSideband           , load_qcd.calib_mva,eventweight);
            Fill(evtbin,BDT_QCD_dataSideband_shapeUncUp, load_qcd.mva      ,eventweight);
        }


        // L jet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isLJet() )
        {
            SumNormalization(evtbin,norm_QCD_DiJetL_signalRegion, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetL_signalRegion, load_qcd.DeepFlavour_bScore, eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetL_signalRegion, load_qcd.DeepFlavour_CvsL  , eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetL_signalRegion, load_qcd.DeepFlavour_CvsB  , eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_DiJetL_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isLJet() )
        {
            SumNormalization(evtbin,norm_QCD_DiJetL_dataSideband, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetL_dataSideband, load_qcd.DeepFlavour_bScore,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetL_dataSideband, load_qcd.DeepFlavour_CvsL  ,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetL_dataSideband, load_qcd.DeepFlavour_CvsB  ,eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_DiJetL_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isLJet() )
        {
            SumNormalization(evtbin,norm_QCD_GJetsL_signalRegion, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsL_signalRegion, load_qcd.DeepFlavour_bScore, eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsL_signalRegion, load_qcd.DeepFlavour_CvsL  , eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsL_signalRegion, load_qcd.DeepFlavour_CvsB  , eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_GJetsL_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isLJet() )
        {
            SumNormalization(evtbin,norm_QCD_GJetsL_dataSideband, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsL_dataSideband, load_qcd.DeepFlavour_bScore,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsL_dataSideband, load_qcd.DeepFlavour_CvsL  ,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsL_dataSideband, load_qcd.DeepFlavour_CvsB  ,eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_GJetsL_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }


        // c jet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isCJet() )
        {
            SumNormalization(evtbin,norm_QCD_DiJetC_signalRegion, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetC_signalRegion, load_qcd.DeepFlavour_bScore, eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetC_signalRegion, load_qcd.DeepFlavour_CvsL  , eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetC_signalRegion, load_qcd.DeepFlavour_CvsB  , eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_DiJetC_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isCJet() )
        {
            SumNormalization(evtbin,norm_QCD_DiJetC_dataSideband, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetC_dataSideband, load_qcd.DeepFlavour_bScore,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetC_dataSideband, load_qcd.DeepFlavour_CvsL  ,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetC_dataSideband, load_qcd.DeepFlavour_CvsB  ,eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_DiJetC_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isCJet() )
        {
            SumNormalization(evtbin,norm_QCD_GJetsC_signalRegion, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsC_signalRegion, load_qcd.DeepFlavour_bScore, eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsC_signalRegion, load_qcd.DeepFlavour_CvsL  , eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsC_signalRegion, load_qcd.DeepFlavour_CvsB  , eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_GJetsC_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isCJet() )
        {
            SumNormalization(evtbin,norm_QCD_GJetsC_dataSideband, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsC_dataSideband, load_qcd.DeepFlavour_bScore,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsC_dataSideband, load_qcd.DeepFlavour_CvsL  ,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsC_dataSideband, load_qcd.DeepFlavour_CvsB  ,eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_GJetsC_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }


        // bjet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isBJet() )
        {
            SumNormalization(evtbin,norm_QCD_DiJetB_signalRegion, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetB_signalRegion, load_qcd.DeepFlavour_bScore, eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetB_signalRegion, load_qcd.DeepFlavour_CvsL  , eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetB_signalRegion, load_qcd.DeepFlavour_CvsB  , eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_DiJetB_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isBJet() )
        {
            SumNormalization(evtbin,norm_QCD_DiJetB_dataSideband, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetB_dataSideband, load_qcd.DeepFlavour_bScore,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetB_dataSideband, load_qcd.DeepFlavour_CvsL  ,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetB_dataSideband, load_qcd.DeepFlavour_CvsB  ,eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_DiJetB_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isBJet() )
        {
            SumNormalization(evtbin,norm_QCD_GJetsB_signalRegion, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsB_signalRegion, load_qcd.DeepFlavour_bScore, eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsB_signalRegion, load_qcd.DeepFlavour_CvsL  , eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsB_signalRegion, load_qcd.DeepFlavour_CvsB  , eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_GJetsB_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isBJet() )
        {
            SumNormalization(evtbin,norm_QCD_GJetsB_dataSideband, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsB_dataSideband, load_qcd.DeepFlavour_bScore,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsB_dataSideband, load_qcd.DeepFlavour_CvsL  ,eventweight, load_qcd);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsB_dataSideband, load_qcd.DeepFlavour_CvsB  ,eventweight, load_qcd);
            Fill(evtbin,jettag3_QCD_GJetsB_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }
    }
    LOG("hiiii end of loop");

    fout->cd();
    for ( int pEtaIdx = 0; pEtaIdx < NUMBIN_PHOETA; ++pEtaIdx )
        for ( int jEtaIdx = 0; jEtaIdx < NUMBIN_JETETA; ++jEtaIdx )
            for ( int pPtIdx = 0; pPtIdx < NUMBIN_PHOPT; ++pPtIdx )
    {
        TDirectory* outputfolder = fout->mkdir( Form("bin_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx) );
        outputfolder->cd();
        EventBinning bin(pEtaIdx,jEtaIdx,pPtIdx);
        Write(bin,BDT_QCD_signalRegion);
        Write(bin,BDT_QCD_dataSideband);

        Write(bin,BDT_QCD_signalRegion_shapeUncUp);
        Write(bin,BDT_QCD_dataSideband_shapeUncUp);
        WriteShapeUncDown(bin,BDT_QCD_signalRegion,BDT_QCD_signalRegion_shapeUncUp);
        WriteShapeUncDown(bin,BDT_QCD_dataSideband,BDT_QCD_dataSideband_shapeUncUp);


        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetL_signalRegion,norm_QCD_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetL_dataSideband,norm_QCD_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetC_signalRegion,norm_QCD_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetC_dataSideband,norm_QCD_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetB_signalRegion,norm_QCD_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetB_dataSideband,norm_QCD_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsL_signalRegion,norm_QCD_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsL_dataSideband,norm_QCD_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsC_signalRegion,norm_QCD_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsC_dataSideband,norm_QCD_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsB_signalRegion,norm_QCD_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsB_dataSideband,norm_QCD_GJetsB_dataSideband);

        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetL_signalRegion,norm_QCD_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetL_dataSideband,norm_QCD_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetC_signalRegion,norm_QCD_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetC_dataSideband,norm_QCD_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetB_signalRegion,norm_QCD_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetB_dataSideband,norm_QCD_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsL_signalRegion,norm_QCD_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsL_dataSideband,norm_QCD_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsC_signalRegion,norm_QCD_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsC_dataSideband,norm_QCD_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsB_signalRegion,norm_QCD_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsB_dataSideband,norm_QCD_GJetsB_dataSideband);

        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetL_signalRegion,norm_QCD_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetL_dataSideband,norm_QCD_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetC_signalRegion,norm_QCD_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetC_dataSideband,norm_QCD_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetB_signalRegion,norm_QCD_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetB_dataSideband,norm_QCD_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsL_signalRegion,norm_QCD_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsL_dataSideband,norm_QCD_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsC_signalRegion,norm_QCD_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsC_dataSideband,norm_QCD_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsB_signalRegion,norm_QCD_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsB_dataSideband,norm_QCD_GJetsB_dataSideband);

        Write(bin,jettag3_QCD_DiJetL_signalRegion);
        Write(bin,jettag3_QCD_DiJetL_dataSideband);
        Write(bin,jettag3_QCD_DiJetC_signalRegion);
        Write(bin,jettag3_QCD_DiJetC_dataSideband);
        Write(bin,jettag3_QCD_DiJetB_signalRegion);
        Write(bin,jettag3_QCD_DiJetB_dataSideband);
        Write(bin,jettag3_QCD_GJetsL_signalRegion);
        Write(bin,jettag3_QCD_GJetsL_dataSideband);
        Write(bin,jettag3_QCD_GJetsC_signalRegion);
        Write(bin,jettag3_QCD_GJetsC_dataSideband);
        Write(bin,jettag3_QCD_GJetsB_signalRegion);
    }
    
    fout->Close();
}
// QCD section end }}}

// sig section {{{
EvtSelMgr EvtSelFactory(const MakeHistoSIG& loadvar);
void Fill_AllCTagReshaped( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight, const MakeHistoSIG& loadvars);
void SumNormalization( const EventBinning& bin, Normalization_CTagReshaped& N,const MakeHistoSIG& loadvars );
void LoopSIG( Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename, int processNEvt = -1 );
EventBinning BinningFactory(const MakeHistoSIG & v) { return  EventBinning(v.recoPt     ,v.recoEta,v.jetPt,v.jetY,v.chIsoRaw   ); }


EvtSelMgr EvtSelFactory(const MakeHistoSIG& loadvar)
{
    bool isMC          = true;
    bool isQCD         = false;
    bool HLTOPTION     = false;
    EvtSelMgr output(isMC,isQCD,HLTOPTION);

    //output.jethadflvr    = loadvar.jetHadFlvr;
    //output.chIso         = loadvar.chIsoRaw;
    //output.phoEta        = loadvar.recoEta;
    //output.isMatched     = loadvar.isMatched;

    //output.jetPt         = loadvar.jetPt;
    //output.jetEta        = loadvar.jetEta;
    //output.cScore        = loadvar.jetDeepCSVTags_c;
    //output.jetID         = loadvar.jetID;
    //output.jetPUIDbit    = loadvar.jetPUIDbit;
    //output.jetSubVtxMass = loadvar.jetSubVtxMass;
    //output.CvsL          = loadvar.DeepCSV_CvsL;
    //output.passMaxPUcut  = 0;

    //output.recoSCEta     = loadvar.recoSCEta;
    //output.sieieFull5x5  = loadvar.sieieFull5x5;
    //output.HoverE        = loadvar.HoverE;
    //output.MET           = loadvar.MET;
    //output.phoPt         = loadvar.recoPt;
    //output.eleVeto       = loadvar.eleVeto;

    //output.phoFiredTrgs  = loadvar.phoFiredTrgs;
    output.SetUsedVar_4(loadvar.jetHadFlvr);
    output.SetUsedVar_3(
        loadvar.chIsoRaw,
        loadvar.recoEta,
        loadvar.isMatched);

    output.SetUsedVar_2(
        loadvar.jetPt,
        loadvar.jetEta,
        loadvar.jetDeepCSVTags_c,
        loadvar.jetID,
        loadvar.jetPUIDbit,
        loadvar.jetSubVtxMass,
        loadvar.DeepCSV_CvsL,
        0); // passMaxPUcut

    output.SetUsedVar_1(
        loadvar.recoSCEta,
        loadvar.sieieFull5x5,
        loadvar.HoverE);
    output.SetUsedVar_0(
        loadvar.MET,
        loadvar.recoPt,
        loadvar.eleVeto,
        0);
        //loadvar.phoFillIdx);

    output.SetUsedVar__(loadvar.phoFiredTrgs);
    return output;
}
void Fill_AllCTagReshaped( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight, const MakeHistoSIG& loadvars)
{
    Fill_allctagreshaped_general(bin,h,val, evt_weight,
            loadvars.DeepFlavour_ctagWeight_central,
            loadvars.DeepFlavour_ctagWeight_PUWeightUp,
            loadvars.DeepFlavour_ctagWeight_PUWeightDown,
            loadvars.DeepFlavour_ctagWeight_StatUp,
            loadvars.DeepFlavour_ctagWeight_StatDown
            );
}
void SumNormalization( const EventBinning& bin, Normalization_CTagReshaped& N,const MakeHistoSIG& loadvars )
{
    normalization_ctagreshaped& n = N.binned_norm[bin.pEtaBin][bin.jEtaBin][bin.pPtBin];
    n.Add(
            loadvars.DeepFlavour_ctagWeight_central,
            loadvars.DeepFlavour_ctagWeight_PUWeightUp,
            loadvars.DeepFlavour_ctagWeight_PUWeightDown,
            loadvars.DeepFlavour_ctagWeight_StatUp,
            loadvars.DeepFlavour_ctagWeight_StatDown
            );
}
void LoopSIG( Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename, int processNEvt = -1 )
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();

    TRandom3 *trd = new TRandom3();

    TFile *fout = new TFile( Form("makehisto_%s.root", dataTYPE),"recreate");
    fout->cd();

    LOG("output file : makehisto_%s.root", dataTYPE);

    Hists* BDT_gjet_signalRegion = Hists_BDT("BDT_gjet_signalRegion", "calib_mva");
    Hists* BDT_gjet_dataSideband = Hists_BDT("BDT_gjet_dataSideband", "calib_mva");
    Hists* BDT_gjet_signalRegion_shapeUncUp = Hists_BDT("BDT_gjet_signalRegion_shapeUncUp", "mva");
    Hists* BDT_gjet_dataSideband_shapeUncUp = Hists_BDT("BDT_gjet_dataSideband_shapeUncUp", "mva");


    Hists_CTagReshaped* jettag0_gjet_DiJetL_signalRegion = new Hists_CTagReshaped("jettag0_gjet_DiJetL_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_DiJetL_dataSideband = new Hists_CTagReshaped("jettag0_gjet_DiJetL_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_DiJetC_signalRegion = new Hists_CTagReshaped("jettag0_gjet_DiJetC_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_DiJetC_dataSideband = new Hists_CTagReshaped("jettag0_gjet_DiJetC_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_DiJetB_signalRegion = new Hists_CTagReshaped("jettag0_gjet_DiJetB_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_DiJetB_dataSideband = new Hists_CTagReshaped("jettag0_gjet_DiJetB_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_GJetsL_signalRegion = new Hists_CTagReshaped("jettag0_gjet_GJetsL_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_GJetsL_dataSideband = new Hists_CTagReshaped("jettag0_gjet_GJetsL_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_GJetsC_signalRegion = new Hists_CTagReshaped("jettag0_gjet_GJetsC_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_GJetsC_dataSideband = new Hists_CTagReshaped("jettag0_gjet_GJetsC_dataSideband", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_GJetsB_signalRegion = new Hists_CTagReshaped("jettag0_gjet_GJetsB_signalRegion", "DeepFlavour.bScore");
    Hists_CTagReshaped* jettag0_gjet_GJetsB_dataSideband = new Hists_CTagReshaped("jettag0_gjet_GJetsB_dataSideband", "DeepFlavour.bScore");

    Hists_CTagReshaped* jettag1_gjet_DiJetL_signalRegion = new Hists_CTagReshaped("jettag1_gjet_DiJetL_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_DiJetL_dataSideband = new Hists_CTagReshaped("jettag1_gjet_DiJetL_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_DiJetC_signalRegion = new Hists_CTagReshaped("jettag1_gjet_DiJetC_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_DiJetC_dataSideband = new Hists_CTagReshaped("jettag1_gjet_DiJetC_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_DiJetB_signalRegion = new Hists_CTagReshaped("jettag1_gjet_DiJetB_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_DiJetB_dataSideband = new Hists_CTagReshaped("jettag1_gjet_DiJetB_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_GJetsL_signalRegion = new Hists_CTagReshaped("jettag1_gjet_GJetsL_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_GJetsL_dataSideband = new Hists_CTagReshaped("jettag1_gjet_GJetsL_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_GJetsC_signalRegion = new Hists_CTagReshaped("jettag1_gjet_GJetsC_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_GJetsC_dataSideband = new Hists_CTagReshaped("jettag1_gjet_GJetsC_dataSideband", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_GJetsB_signalRegion = new Hists_CTagReshaped("jettag1_gjet_GJetsB_signalRegion", "DeepFlavour.CvsL");
    Hists_CTagReshaped* jettag1_gjet_GJetsB_dataSideband = new Hists_CTagReshaped("jettag1_gjet_GJetsB_dataSideband", "DeepFlavour.CvsL");

    Hists_CTagReshaped* jettag2_gjet_DiJetL_signalRegion = new Hists_CTagReshaped("jettag2_gjet_DiJetL_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_DiJetL_dataSideband = new Hists_CTagReshaped("jettag2_gjet_DiJetL_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_DiJetC_signalRegion = new Hists_CTagReshaped("jettag2_gjet_DiJetC_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_DiJetC_dataSideband = new Hists_CTagReshaped("jettag2_gjet_DiJetC_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_DiJetB_signalRegion = new Hists_CTagReshaped("jettag2_gjet_DiJetB_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_DiJetB_dataSideband = new Hists_CTagReshaped("jettag2_gjet_DiJetB_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_GJetsL_signalRegion = new Hists_CTagReshaped("jettag2_gjet_GJetsL_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_GJetsL_dataSideband = new Hists_CTagReshaped("jettag2_gjet_GJetsL_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_GJetsC_signalRegion = new Hists_CTagReshaped("jettag2_gjet_GJetsC_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_GJetsC_dataSideband = new Hists_CTagReshaped("jettag2_gjet_GJetsC_dataSideband", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_GJetsB_signalRegion = new Hists_CTagReshaped("jettag2_gjet_GJetsB_signalRegion", "DeepFlavour.CvsB");
    Hists_CTagReshaped* jettag2_gjet_GJetsB_dataSideband = new Hists_CTagReshaped("jettag2_gjet_GJetsB_dataSideband", "DeepFlavour.CvsB");

    Hists* jettag3_gjet_DiJetL_signalRegion = Hists_SubVtxMass("jettag3_gjet_DiJetL_signalRegion", "jetSubVtxMass");
    Hists* jettag3_gjet_DiJetL_dataSideband = Hists_SubVtxMass("jettag3_gjet_DiJetL_dataSideband", "jetSubVtxMass");
    Hists* jettag3_gjet_DiJetC_signalRegion = Hists_SubVtxMass("jettag3_gjet_DiJetC_signalRegion", "jetSubVtxMass");
    Hists* jettag3_gjet_DiJetC_dataSideband = Hists_SubVtxMass("jettag3_gjet_DiJetC_dataSideband", "jetSubVtxMass");
    Hists* jettag3_gjet_DiJetB_signalRegion = Hists_SubVtxMass("jettag3_gjet_DiJetB_signalRegion", "jetSubVtxMass");
    Hists* jettag3_gjet_DiJetB_dataSideband = Hists_SubVtxMass("jettag3_gjet_DiJetB_dataSideband", "jetSubVtxMass");
    Hists* jettag3_gjet_GJetsL_signalRegion = Hists_SubVtxMass("jettag3_gjet_GJetsL_signalRegion", "jetSubVtxMass");
    Hists* jettag3_gjet_GJetsL_dataSideband = Hists_SubVtxMass("jettag3_gjet_GJetsL_dataSideband", "jetSubVtxMass");
    Hists* jettag3_gjet_GJetsC_signalRegion = Hists_SubVtxMass("jettag3_gjet_GJetsC_signalRegion", "jetSubVtxMass");
    Hists* jettag3_gjet_GJetsC_dataSideband = Hists_SubVtxMass("jettag3_gjet_GJetsC_dataSideband", "jetSubVtxMass");
    Hists* jettag3_gjet_GJetsB_signalRegion = Hists_SubVtxMass("jettag3_gjet_GJetsB_signalRegion", "jetSubVtxMass");
    Hists* jettag3_gjet_GJetsB_dataSideband = Hists_SubVtxMass("jettag3_gjet_GJetsB_dataSideband", "jetSubVtxMass");


    Normalization_CTagReshaped norm_gjet_DiJetL_signalRegion;
    Normalization_CTagReshaped norm_gjet_DiJetL_dataSideband;
    Normalization_CTagReshaped norm_gjet_DiJetC_signalRegion;
    Normalization_CTagReshaped norm_gjet_DiJetC_dataSideband;
    Normalization_CTagReshaped norm_gjet_DiJetB_signalRegion;
    Normalization_CTagReshaped norm_gjet_DiJetB_dataSideband;
    Normalization_CTagReshaped norm_gjet_GJetsL_signalRegion;
    Normalization_CTagReshaped norm_gjet_GJetsL_dataSideband;
    Normalization_CTagReshaped norm_gjet_GJetsC_signalRegion;
    Normalization_CTagReshaped norm_gjet_GJetsC_dataSideband;
    Normalization_CTagReshaped norm_gjet_GJetsB_signalRegion;
    Normalization_CTagReshaped norm_gjet_GJetsB_dataSideband;

    TFile* iii = TFile::Open(inputfilename);
    TTree* ttt = (TTree*) iii->Get("t");
    MakeHistoSIG load_sig(ttt);

    Long64_t nentries = processNEvt > 0 ? processNEvt : load_sig.fChain->GetEntries();

    LOG("Looping in %lli entries", nentries);

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = load_sig.LoadTree(jentry);
        
        if (ientry < 0) break;
        nb = load_sig.GetEntry(jentry); nbytes += nb;

        if (jentry % 100000 == 0){ fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries); }


        Float_t eventweight = load_sig.mcweight * load_sig.puwei;

	
        const EventBinning evtbin = BinningFactory(load_sig);
        int hltbit = TriggerBit(dataERA, evtbin.pPtBin);
        EvtSelMgr sel = EvtSelFactory(load_sig);
        bool isFakePhoton =
            (load_sig.isMatched!=1 && load_sig.isConverted!=1 && load_sig.isMatchedEle!=1 )?
            1 : 0;

        // preselections
        if (!sel.PassPhotonPreSelection(evtbin.pPtBin) ) continue;
        if (!sel.InFiducialRegion() ) continue;
        if (!sel.PassJetAdditionalSelection(extracut) ) continue;
        if (!sel.PassHLT(hltbit) ) continue; // indeed it is useless in signal MC


        if ( evtbin.isSignalRegion &&!isFakePhoton )
        {
            Fill(evtbin,BDT_gjet_signalRegion           , load_sig.calib_mva,eventweight);
            Fill(evtbin,BDT_gjet_signalRegion_shapeUncUp, load_sig.mva      ,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton )
        {
            Fill(evtbin,BDT_gjet_dataSideband           , load_sig.calib_mva,eventweight);
            Fill(evtbin,BDT_gjet_dataSideband_shapeUncUp, load_sig.mva      ,eventweight);
        }


        // L jet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isLJet() )
        {
            SumNormalization(evtbin,norm_gjet_DiJetL_signalRegion, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetL_signalRegion, load_sig.DeepFlavour_bScore, eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetL_signalRegion, load_sig.DeepFlavour_CvsL  , eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetL_signalRegion, load_sig.DeepFlavour_CvsB  , eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_DiJetL_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isLJet() )
        {
            SumNormalization(evtbin,norm_gjet_DiJetL_dataSideband, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetL_dataSideband, load_sig.DeepFlavour_bScore,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetL_dataSideband, load_sig.DeepFlavour_CvsL  ,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetL_dataSideband, load_sig.DeepFlavour_CvsB  ,eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_DiJetL_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isLJet() )
        {
            SumNormalization(evtbin,norm_gjet_GJetsL_signalRegion, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsL_signalRegion, load_sig.DeepFlavour_bScore, eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsL_signalRegion, load_sig.DeepFlavour_CvsL  , eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsL_signalRegion, load_sig.DeepFlavour_CvsB  , eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_GJetsL_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isLJet() )
        {
            SumNormalization(evtbin,norm_gjet_GJetsL_dataSideband, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsL_dataSideband, load_sig.DeepFlavour_bScore,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsL_dataSideband, load_sig.DeepFlavour_CvsL  ,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsL_dataSideband, load_sig.DeepFlavour_CvsB  ,eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_GJetsL_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }


        // c jet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isCJet() )
        {
            SumNormalization(evtbin,norm_gjet_DiJetC_signalRegion, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetC_signalRegion, load_sig.DeepFlavour_bScore, eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetC_signalRegion, load_sig.DeepFlavour_CvsL  , eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetC_signalRegion, load_sig.DeepFlavour_CvsB  , eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_DiJetC_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isCJet() )
        {
            SumNormalization(evtbin,norm_gjet_DiJetC_dataSideband, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetC_dataSideband, load_sig.DeepFlavour_bScore,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetC_dataSideband, load_sig.DeepFlavour_CvsL  ,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetC_dataSideband, load_sig.DeepFlavour_CvsB  ,eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_DiJetC_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isCJet() )
        {
            SumNormalization(evtbin,norm_gjet_GJetsC_signalRegion, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsC_signalRegion, load_sig.DeepFlavour_bScore, eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsC_signalRegion, load_sig.DeepFlavour_CvsL  , eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsC_signalRegion, load_sig.DeepFlavour_CvsB  , eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_GJetsC_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isCJet() )
        {
            SumNormalization(evtbin,norm_gjet_GJetsC_dataSideband, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsC_dataSideband, load_sig.DeepFlavour_bScore,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsC_dataSideband, load_sig.DeepFlavour_CvsL  ,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsC_dataSideband, load_sig.DeepFlavour_CvsB  ,eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_GJetsC_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }


        // bjet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isBJet() )
        {
            SumNormalization(evtbin,norm_gjet_DiJetB_signalRegion, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetB_signalRegion, load_sig.DeepFlavour_bScore, eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetB_signalRegion, load_sig.DeepFlavour_CvsL  , eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetB_signalRegion, load_sig.DeepFlavour_CvsB  , eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_DiJetB_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isBJet() )
        {
            SumNormalization(evtbin,norm_gjet_DiJetB_dataSideband, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetB_dataSideband, load_sig.DeepFlavour_bScore,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetB_dataSideband, load_sig.DeepFlavour_CvsL  ,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetB_dataSideband, load_sig.DeepFlavour_CvsB  ,eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_DiJetB_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isBJet() )
        {
            SumNormalization(evtbin,norm_gjet_GJetsB_signalRegion, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsB_signalRegion, load_sig.DeepFlavour_bScore, eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsB_signalRegion, load_sig.DeepFlavour_CvsL  , eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsB_signalRegion, load_sig.DeepFlavour_CvsB  , eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_GJetsB_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isBJet() )
        {
            SumNormalization(evtbin,norm_gjet_GJetsB_dataSideband, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsB_dataSideband, load_sig.DeepFlavour_bScore,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsB_dataSideband, load_sig.DeepFlavour_CvsL  ,eventweight, load_sig);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsB_dataSideband, load_sig.DeepFlavour_CvsB  ,eventweight, load_sig);
            Fill(evtbin,jettag3_gjet_GJetsB_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }
    }
    LOG("hiiii end of loop");

    fout->cd();
    for ( int pEtaIdx = 0; pEtaIdx < NUMBIN_PHOETA; ++pEtaIdx )
        for ( int jEtaIdx = 0; jEtaIdx < NUMBIN_JETETA; ++jEtaIdx )
            for ( int pPtIdx = 0; pPtIdx < NUMBIN_PHOPT; ++pPtIdx )
    {
        TDirectory* outputfolder = fout->mkdir( Form("bin_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx) );
        outputfolder->cd();
        EventBinning bin(pEtaIdx,jEtaIdx,pPtIdx);
        Write(bin,BDT_gjet_signalRegion);
        Write(bin,BDT_gjet_dataSideband);

        Write(bin,BDT_gjet_signalRegion_shapeUncUp);
        Write(bin,BDT_gjet_dataSideband_shapeUncUp);
        WriteShapeUncDown(bin,BDT_gjet_signalRegion,BDT_gjet_signalRegion_shapeUncUp);
        WriteShapeUncDown(bin,BDT_gjet_dataSideband,BDT_gjet_dataSideband_shapeUncUp);


        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetL_signalRegion,norm_gjet_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetL_dataSideband,norm_gjet_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetC_signalRegion,norm_gjet_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetC_dataSideband,norm_gjet_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetB_signalRegion,norm_gjet_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetB_dataSideband,norm_gjet_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsL_signalRegion,norm_gjet_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsL_dataSideband,norm_gjet_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsC_signalRegion,norm_gjet_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsC_dataSideband,norm_gjet_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsB_signalRegion,norm_gjet_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsB_dataSideband,norm_gjet_GJetsB_dataSideband);

        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetL_signalRegion,norm_gjet_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetL_dataSideband,norm_gjet_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetC_signalRegion,norm_gjet_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetC_dataSideband,norm_gjet_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetB_signalRegion,norm_gjet_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetB_dataSideband,norm_gjet_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsL_signalRegion,norm_gjet_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsL_dataSideband,norm_gjet_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsC_signalRegion,norm_gjet_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsC_dataSideband,norm_gjet_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsB_signalRegion,norm_gjet_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsB_dataSideband,norm_gjet_GJetsB_dataSideband);

        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetL_signalRegion,norm_gjet_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetL_dataSideband,norm_gjet_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetC_signalRegion,norm_gjet_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetC_dataSideband,norm_gjet_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetB_signalRegion,norm_gjet_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetB_dataSideband,norm_gjet_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsL_signalRegion,norm_gjet_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsL_dataSideband,norm_gjet_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsC_signalRegion,norm_gjet_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsC_dataSideband,norm_gjet_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsB_signalRegion,norm_gjet_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsB_dataSideband,norm_gjet_GJetsB_dataSideband);

        Write(bin,jettag3_gjet_DiJetL_signalRegion);
        Write(bin,jettag3_gjet_DiJetL_dataSideband);
        Write(bin,jettag3_gjet_DiJetC_signalRegion);
        Write(bin,jettag3_gjet_DiJetC_dataSideband);
        Write(bin,jettag3_gjet_DiJetB_signalRegion);
        Write(bin,jettag3_gjet_DiJetB_dataSideband);
        Write(bin,jettag3_gjet_GJetsL_signalRegion);
        Write(bin,jettag3_gjet_GJetsL_dataSideband);
        Write(bin,jettag3_gjet_GJetsC_signalRegion);
        Write(bin,jettag3_gjet_GJetsC_dataSideband);
        Write(bin,jettag3_gjet_GJetsB_signalRegion);
    }
    
    fout->Close();
}
// sig section end }}}

// data section {{{
EvtSelMgr EvtSelFactory(const MakeHistoData& loadvar);
void LoopData( Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename, int processNEvt = -1 );
EventBinning BinningFactory(const MakeHistoData& v) { return  EventBinning(v.recoPtCalib,v.recoEta,v.jetPt,v.jetY,v.calib_chIso); }


EvtSelMgr EvtSelFactory(const MakeHistoData& loadvar)
{
    bool isMC          = false;
    bool isQCD         = false;
    bool HLTOPTION     = true;
    EvtSelMgr output(isMC,isQCD,HLTOPTION);

    //// not finished
    //output.jethadflvr    = 0;
    //output.chIso         = loadvar.calib_chIso;
    //output.phoEta        = loadvar.recoEta;
    //output.isMatched     = 0;

    //output.jetPt         = loadvar.jetPt;
    //output.jetEta        = loadvar.jetEta;
    //output.cScore        = loadvar.jetDeepCSVTags_c;
    //output.jetID         = 0;
    //output.jetPUIDbit    = 0;
    //output.jetSubVtxMass = loadvar.jetSubVtxMass;
    //output.CvsL          = loadvar.DeepCSV_CvsL;
    //output.passMaxPUcut  = 0;   

    //output.recoSCEta     = loadvar.recoSCEta;
    //output.sieieFull5x5  = loadvar.sieieFull5x5;
    //output.HoverE        = loadvar.HoverE;
    //output.MET           = loadvar.MET;
    //output.phoPt         = loadvar.recoPtCalib;
    //output.eleVeto       = loadvar.eleVeto;

    //output.phoFiredTrgs  = loadvar.phoFiredTrgs;
    output.SetUsedVar_4(0);
    output.SetUsedVar_3(
        loadvar.calib_chIso,
        loadvar.recoEta,
        0);

    output.SetUsedVar_2(
        loadvar.jetPt,
        loadvar.jetEta,
        loadvar.jetDeepFlavourTags_c,
        0,
        0,
        loadvar.jetSubVtxMass,
        loadvar.DeepCSV_CvsL,
        0); // passMaxPUcut

    output.SetUsedVar_1(
        loadvar.recoSCEta,
        loadvar.sieieFull5x5,
        loadvar.HoverE);
    output.SetUsedVar_0(
        loadvar.MET,
        loadvar.recoPt,
        loadvar.eleVeto,
        0);
        //loadvar.phoFillIdx);

    output.SetUsedVar__(loadvar.phoFiredTrgs);
    return output;
}
void LoopData( Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename, int processNEvt = -1 )
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();

    TRandom3 *trd = new TRandom3();

    TFile *fout = new TFile( Form("makehisto_%s.root", dataTYPE),"recreate");
    fout->cd();
    LOG("output file : makehisto_%s.root", dataTYPE);

    Hists* BDT_data_signalRegion = Hists_BDT("BDT_data_signalRegion", "mva");
    Hists* BDT_data_dataSideband = Hists_BDT("BDT_data_dataSideband", "mva");

    Hists* jettag0_data_signalRegion = Hists_CTags("jettag0_data_signalRegion", "DeepFlavour.bScore");
    Hists* jettag0_data_dataSideband = Hists_CTags("jettag0_data_dataSideband", "DeepFlavour.bScore");

    Hists* jettag1_data_signalRegion = Hists_CTags("jettag1_data_signalRegion", "DeepFlavour.CvsL");
    Hists* jettag1_data_dataSideband = Hists_CTags("jettag1_data_dataSideband", "DeepFlavour.CvsL");

    Hists* jettag2_data_signalRegion = Hists_CTags("jettag2_data_signalRegion", "DeepFlavour.CvsB");
    Hists* jettag2_data_dataSideband = Hists_CTags("jettag2_data_dataSideband", "DeepFlavour.CvsB");

    Hists* jettag3_data_signalRegion = Hists_SubVtxMass("jettag3_data_signalRegion", "jetSubVtxMass");
    Hists* jettag3_data_dataSideband = Hists_SubVtxMass("jettag3_data_dataSideband", "jetSubVtxMass");

    TH1F* hist_HLT[30];
    for ( int i=0; i<30; ++i )
        hist_HLT[i] = new TH1F( Form("HLT_ptbin%d",i), Form("HLT bin distribution at ptbin %d",i), 10, 0.,10.);


    TFile* iii = TFile::Open(inputfilename);
    TTree* ttt = (TTree*) iii->Get("t");
    MakeHistoData load_data(ttt);
    Long64_t nentries = processNEvt > 0 ? processNEvt : load_data.fChain->GetEntries();

    LOG("Looping in %lli entries", nentries);

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = load_data.LoadTree(jentry);
        
        if (ientry < 0) break;
        nb = load_data.GetEntry(jentry); nbytes += nb;

        if (jentry % 100000 == 0)
        { fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries); }
        Float_t eventweight = 1.;

        const EventBinning evtbin = BinningFactory(load_data);
        int hltbit = TriggerBit(dataERA, evtbin.pPtBin);
        EvtSelMgr sel = EvtSelFactory(load_data);


        if ( evtbin.pPtBin < 0 ) continue;
        for ( int iHLT = 0; iHLT < 10; ++iHLT )
            if ( sel.PassHLT(iHLT) )
                hist_HLT[evtbin.pPtBin]->Fill(iHLT);

        if (!sel.PassPhotonPreSelection(evtbin.pPtBin) ) continue;
        if (!sel.InFiducialRegion() ) continue;
        if (!sel.PassJetAdditionalSelection(extracut) ) continue;
        if (!sel.PassHLT(hltbit) ) continue;


        if ( evtbin.isSignalRegion )
        {
            Fill(evtbin,BDT_data_signalRegion    , load_data.mva,eventweight);
            Fill(evtbin,jettag0_data_signalRegion, load_data.DeepFlavour_bScore,eventweight);
            Fill(evtbin,jettag1_data_signalRegion, load_data.DeepFlavour_CvsL,eventweight);
            Fill(evtbin,jettag2_data_signalRegion, load_data.DeepFlavour_CvsB,eventweight);
            Fill(evtbin,jettag3_data_signalRegion, load_data.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband )
        {
            Fill(evtbin,BDT_data_dataSideband    , load_data.mva,eventweight);
            Fill(evtbin,jettag0_data_dataSideband, load_data.DeepFlavour_bScore,eventweight);
            Fill(evtbin,jettag1_data_dataSideband, load_data.DeepFlavour_CvsL,eventweight);
            Fill(evtbin,jettag2_data_dataSideband, load_data.DeepFlavour_CvsB,eventweight);
            Fill(evtbin,jettag3_data_dataSideband, load_data.jetSubVtxMass,eventweight);
        }
        
    }
    LOG("hiiii end of loop");

    fout->cd();
    for ( int i=0; i< NUMBIN_PHOPT; ++i )
        hist_HLT[i]->Write();

    for ( int pEtaIdx = 0; pEtaIdx < NUMBIN_PHOETA; ++pEtaIdx )
        for ( int jEtaIdx = 0; jEtaIdx < NUMBIN_JETETA; ++jEtaIdx )
            for ( int pPtIdx = 0; pPtIdx < NUMBIN_PHOPT; ++pPtIdx )
    {
        TDirectory* outputfolder = fout->mkdir( Form("bin_%d_%d_%d",pEtaIdx,jEtaIdx,pPtIdx) );
        outputfolder->cd();
        EventBinning bin(pEtaIdx,jEtaIdx,pPtIdx);
        Write(bin,BDT_data_signalRegion);
        Write(bin,BDT_data_dataSideband);

        Write(bin,jettag0_data_signalRegion);
        Write(bin,jettag0_data_dataSideband);

        Write(bin,jettag1_data_signalRegion);
        Write(bin,jettag1_data_dataSideband);

        Write(bin,jettag2_data_signalRegion);
        Write(bin,jettag2_data_dataSideband);

        Write(bin,jettag3_data_signalRegion);
        Write(bin,jettag3_data_dataSideband);
    }
    
    fout->Close();
}
// data section end }}}

void Loop(Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename )
{
    const std::string dataType(dataTYPE);

    //int NEVENT = 10; // testing event
    int NEVENT = -1; // all event

    int processTag = 0;
    if ( dataType == "data" )
    { LoopData(extracut, dataERA, dataTYPE, inputfilename, NEVENT); processTag += 1; }
    if ( dataType == "gjet" )
    { LoopSIG(extracut, dataERA, dataTYPE, inputfilename, NEVENT); processTag += 1; }
    if ( dataType == "QCD"  )
    { LoopQCD(extracut, dataERA, dataTYPE, inputfilename, NEVENT); processTag += 1; }


    if ( dataType == "testdata" )
    { LoopData(extracut, dataERA, dataTYPE, inputfilename, NEVENT); processTag += 1; }
    if ( dataType == "testgjet" )
    { LoopSIG(extracut, dataERA, dataTYPE, inputfilename, NEVENT); processTag += 1; }
    if ( dataType == "testQCD"  )
    { LoopQCD(extracut, dataERA, dataTYPE, inputfilename, NEVENT); processTag += 1; }


    if ( processTag == 0 ) std::cerr << Form("input data type '%s' is wrong. Please check!\n", dataTYPE);
}


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
#include <cstring>
#include <TLorentzVector.h>


#include "MakeHistoData.h"
#include "MakeHistoSIG.h"
#include "MakeHistoQCD.h"


// GetBJetVar functions {{{
template<typename T>
float GetBJetVar(const T& loadVAR, const char* tagALGO, const char* varID)
{
    if ( strcmp(tagALGO,"DeepCSV") == 0 )
    {
        if ( strcmp(varID,"CvsB") == 0 ) return loadVAR.DeepCSV_CvsB;
        if ( strcmp(varID,"CvsL") == 0 ) return loadVAR.DeepCSV_CvsL;
        if ( strcmp(varID,"bScore") == 0 ) return loadVAR.DeepCSV_bScore;
        if ( strcmp(varID,"tags_c") == 0 ) return loadVAR.jetDeepCSVTags_c;
    }
    if ( strcmp(tagALGO,"DeepFlavour") == 0 )
    {
        if ( strcmp(varID,"CvsB") == 0 ) return loadVAR.DeepFlavour_CvsB;
        if ( strcmp(varID,"CvsL") == 0 ) return loadVAR.DeepFlavour_CvsL;
        if ( strcmp(varID,"bScore") == 0 ) return loadVAR.DeepFlavour_bScore;
        if ( strcmp(varID,"tags_c") == 0 ) return loadVAR.jetDeepFlavourTags_c;
    }
    throw Form("\n\nFailed to find variable '%s' stored in tag algorithm '%s'\n\n",varID,tagALGO); 
}
template<typename T>
float GetBJetVarWeights(const T& loadVAR, const char* tagALGO, const char* varID)
{
    if ( strcmp(tagALGO,"DeepCSV") == 0 )
    {
        if ( strcmp(varID,"weight_central") == 0 ) return loadVAR.DeepCSV_ctagWeight_central;
        if ( strcmp(varID,"weight_PUUp") == 0 ) return loadVAR.DeepCSV_ctagWeight_PUWeightUp;
        if ( strcmp(varID,"weight_PUDown") == 0 ) return loadVAR.DeepCSV_ctagWeight_PUWeightDown;
        if ( strcmp(varID,"weight_StatUp") == 0 ) return loadVAR.DeepCSV_ctagWeight_StatUp;
        if ( strcmp(varID,"weight_StatDown") == 0 ) return loadVAR.DeepCSV_ctagWeight_StatDown;
    }
    if ( strcmp(tagALGO,"DeepFlavour") == 0 )
    {
        if ( strcmp(varID,"weight_central") == 0 ) return loadVAR.DeepFlavour_ctagWeight_central;
        if ( strcmp(varID,"weight_PUUp") == 0 ) return loadVAR.DeepFlavour_ctagWeight_PUWeightUp;
        if ( strcmp(varID,"weight_PUDown") == 0 ) return loadVAR.DeepFlavour_ctagWeight_PUWeightDown;
        if ( strcmp(varID,"weight_StatUp") == 0 ) return loadVAR.DeepFlavour_ctagWeight_StatUp;
        if ( strcmp(varID,"weight_StatDown") == 0 ) return loadVAR.DeepFlavour_ctagWeight_StatDown;
    }
    throw Form("\n\nFailed to find variable '%s' stored in tag algorithm '%s'\n\n",varID,tagALGO); 
}
// GetBJetVar functions end }}}






// QCD section {{{
EventBinning BinningFactory(const MakeHistoQCD & v) { return  EventBinning(v.recoPt     ,v.recoEta,v.jetPt,v.jetY,v.chIsoRaw   ); }
EvtSelMgr EvtSelFactory(const MakeHistoQCD& loadvar, const char* tagALGO) // {{{
{
    bool isMC          = true;
    bool isQCD         = true;
    bool HLTOPTION     = true;
    EvtSelMgr output(isMC,isQCD,HLTOPTION);


    output.SetUsedVar_4(loadvar.jetHadFlvr);
    output.SetUsedVar_3(
        loadvar.chIsoRaw,
        loadvar.recoEta,
        loadvar.isMatched);

    output.SetUsedVar_2(
        loadvar.jetPt,
        loadvar.jetEta,
        GetBJetVar(loadvar, tagALGO, "tags_c"),
        loadvar.jetID,
        loadvar.jetPUIDbit,
        loadvar.jetSubVtxMass,
        loadvar.jetSubVtx3DVal,
        loadvar.jetSubVtx3DErr,
        loadvar.jetSubVtxNtrks,
        GetBJetVar(loadvar, tagALGO, "CvsL"),
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
} // }}}
void Fill_AllCTagReshaped( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight, const MakeHistoQCD& loadvars, const char* tagALGO) // {{{
{
    Fill_allctagreshaped_general(bin,h,val, evt_weight,
            GetBJetVarWeights(loadvars,tagALGO, "weight_central"),
            GetBJetVarWeights(loadvars,tagALGO, "weight_PUUp"),
            GetBJetVarWeights(loadvars,tagALGO, "weight_PUDown"),
            GetBJetVarWeights(loadvars,tagALGO, "weight_StatUp"),
            GetBJetVarWeights(loadvars,tagALGO, "weight_StatDown")
            );
} // Fill_AllCTagReshaped end }}}

void LoopQCD( Int_t extracut, const char* dataERA, const char* tagALGO, TFile* fout, const char* inputfilename, int processNEvt = -1 ) // {{{
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();
    fout->cd();


    Hists* BDT_QCD_signalRegion = Hists_BDT("BDT_QCD_signalRegion", "calib_mva");
    Hists* BDT_QCD_dataSideband = Hists_BDT("BDT_QCD_dataSideband", "calib_mva");
    Hists* BDT_QCD_signalRegion_shapeUncUp = Hists_BDT("BDT_QCD_signalRegion_shapeUncUp", "mva");
    Hists* BDT_QCD_dataSideband_shapeUncUp = Hists_BDT("BDT_QCD_dataSideband_shapeUncUp", "mva");


    Hists_CTagReshaped* jettag0_QCD_DiJetL_signalRegion = new Hists_CTagReshaped("jettag0_QCD_DiJetL_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_DiJetL_dataSideband = new Hists_CTagReshaped("jettag0_QCD_DiJetL_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_DiJetC_signalRegion = new Hists_CTagReshaped("jettag0_QCD_DiJetC_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_DiJetC_dataSideband = new Hists_CTagReshaped("jettag0_QCD_DiJetC_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_DiJetB_signalRegion = new Hists_CTagReshaped("jettag0_QCD_DiJetB_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_DiJetB_dataSideband = new Hists_CTagReshaped("jettag0_QCD_DiJetB_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_GJetsL_signalRegion = new Hists_CTagReshaped("jettag0_QCD_GJetsL_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_GJetsL_dataSideband = new Hists_CTagReshaped("jettag0_QCD_GJetsL_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_GJetsC_signalRegion = new Hists_CTagReshaped("jettag0_QCD_GJetsC_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_GJetsC_dataSideband = new Hists_CTagReshaped("jettag0_QCD_GJetsC_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_GJetsB_signalRegion = new Hists_CTagReshaped("jettag0_QCD_GJetsB_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_QCD_GJetsB_dataSideband = new Hists_CTagReshaped("jettag0_QCD_GJetsB_dataSideband", Form("%s.bScore",tagALGO));

    Hists_CTagReshaped* jettag1_QCD_DiJetL_signalRegion = new Hists_CTagReshaped("jettag1_QCD_DiJetL_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_DiJetL_dataSideband = new Hists_CTagReshaped("jettag1_QCD_DiJetL_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_DiJetC_signalRegion = new Hists_CTagReshaped("jettag1_QCD_DiJetC_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_DiJetC_dataSideband = new Hists_CTagReshaped("jettag1_QCD_DiJetC_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_DiJetB_signalRegion = new Hists_CTagReshaped("jettag1_QCD_DiJetB_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_DiJetB_dataSideband = new Hists_CTagReshaped("jettag1_QCD_DiJetB_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_GJetsL_signalRegion = new Hists_CTagReshaped("jettag1_QCD_GJetsL_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_GJetsL_dataSideband = new Hists_CTagReshaped("jettag1_QCD_GJetsL_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_GJetsC_signalRegion = new Hists_CTagReshaped("jettag1_QCD_GJetsC_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_GJetsC_dataSideband = new Hists_CTagReshaped("jettag1_QCD_GJetsC_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_GJetsB_signalRegion = new Hists_CTagReshaped("jettag1_QCD_GJetsB_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_QCD_GJetsB_dataSideband = new Hists_CTagReshaped("jettag1_QCD_GJetsB_dataSideband", Form("%s.CvsL",tagALGO));

    Hists_CTagReshaped* jettag2_QCD_DiJetL_signalRegion = new Hists_CTagReshaped("jettag2_QCD_DiJetL_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_DiJetL_dataSideband = new Hists_CTagReshaped("jettag2_QCD_DiJetL_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_DiJetC_signalRegion = new Hists_CTagReshaped("jettag2_QCD_DiJetC_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_DiJetC_dataSideband = new Hists_CTagReshaped("jettag2_QCD_DiJetC_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_DiJetB_signalRegion = new Hists_CTagReshaped("jettag2_QCD_DiJetB_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_DiJetB_dataSideband = new Hists_CTagReshaped("jettag2_QCD_DiJetB_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_GJetsL_signalRegion = new Hists_CTagReshaped("jettag2_QCD_GJetsL_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_GJetsL_dataSideband = new Hists_CTagReshaped("jettag2_QCD_GJetsL_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_GJetsC_signalRegion = new Hists_CTagReshaped("jettag2_QCD_GJetsC_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_GJetsC_dataSideband = new Hists_CTagReshaped("jettag2_QCD_GJetsC_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_GJetsB_signalRegion = new Hists_CTagReshaped("jettag2_QCD_GJetsB_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_QCD_GJetsB_dataSideband = new Hists_CTagReshaped("jettag2_QCD_GJetsB_dataSideband", Form("%s.CvsB",tagALGO));

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

        if (jentry % 1000000 == 0){ fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries); }


        // not to use mcweight because pre-scaled HLT owns different effective luminosity. So put it afterward.
        //Float_t eventweight = load_qcd.mcweight * load_qcd.puwei * load_qcd.weight_passMaxPUcut;
        Float_t eventweight = load_qcd.weight_passMaxPUcut * \
                              load_qcd.puwei * \
                              load_qcd.genWeight * load_qcd.crossSection / load_qcd.integratedGenWeight;

	
        const EventBinning evtbin = BinningFactory(load_qcd);
        int hltbit = TriggerBit(dataERA, evtbin.pPtBin);
        EvtSelMgr sel = EvtSelFactory(load_qcd,tagALGO);
        bool isFakePhoton =
            (load_qcd.isMatched!=1 && load_qcd.isConverted!=1 && load_qcd.isMatchedEle!=1 )?
            1 : 0;

        // preselections
        if (!sel.PassPhotonPreSelection(evtbin.pPtBin) ) continue;
        if (!sel.InFiducialRegion() ) continue;
        if (!sel.PassJetAdditionalSelection(extracut) ) continue;
        if (!sel.PassHLT(hltbit) ) continue; // indeed it is useless in signal MC


        if ( evtbin.isSignalRegion && isFakePhoton )
        {
            Fill(evtbin,BDT_QCD_signalRegion           , load_qcd.calib_mva,eventweight);
            Fill(evtbin,BDT_QCD_signalRegion_shapeUncUp, load_qcd.mva      ,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton )
        {
            Fill(evtbin,BDT_QCD_dataSideband           , load_qcd.calib_mva,eventweight);
            Fill(evtbin,BDT_QCD_dataSideband_shapeUncUp, load_qcd.mva      ,eventweight);
        }


        // L jet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isLJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetL_signalRegion, GetBJetVar(load_qcd,tagALGO,"bScore"), eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetL_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsL")  , eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetL_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsB")  , eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_DiJetL_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isLJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetL_dataSideband, GetBJetVar(load_qcd,tagALGO,"bScore"),eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetL_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsL")  ,eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetL_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsB")  ,eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_DiJetL_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isLJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsL_signalRegion, GetBJetVar(load_qcd,tagALGO,"bScore"), eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsL_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsL")  , eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsL_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsB")  , eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_GJetsL_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isLJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsL_dataSideband, GetBJetVar(load_qcd,tagALGO,"bScore"),eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsL_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsL")  ,eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsL_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsB")  ,eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_GJetsL_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }


        // c jet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isCJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetC_signalRegion, GetBJetVar(load_qcd,tagALGO,"bScore"), eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetC_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsL")  , eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetC_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsB")  , eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_DiJetC_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isCJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetC_dataSideband, GetBJetVar(load_qcd,tagALGO,"bScore"),eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetC_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsL")  ,eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetC_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsB")  ,eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_DiJetC_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isCJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsC_signalRegion, GetBJetVar(load_qcd,tagALGO,"bScore"), eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsC_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsL")  , eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsC_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsB")  , eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_GJetsC_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isCJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsC_dataSideband, GetBJetVar(load_qcd,tagALGO,"bScore"),eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsC_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsL")  ,eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsC_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsB")  ,eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_GJetsC_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }


        // bjet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isBJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetB_signalRegion, GetBJetVar(load_qcd,tagALGO,"bScore"), eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetB_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsL")  , eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetB_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsB")  , eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_DiJetB_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isBJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_DiJetB_dataSideband, GetBJetVar(load_qcd,tagALGO,"bScore"),eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_DiJetB_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsL")  ,eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_DiJetB_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsB")  ,eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_DiJetB_dataSideband, load_qcd.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isBJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsB_signalRegion, GetBJetVar(load_qcd,tagALGO,"bScore"), eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsB_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsL")  , eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsB_signalRegion, GetBJetVar(load_qcd,tagALGO,"CvsB")  , eventweight, load_qcd, tagALGO);
            Fill(evtbin,jettag3_QCD_GJetsB_signalRegion, load_qcd.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isBJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_QCD_GJetsB_dataSideband, GetBJetVar(load_qcd,tagALGO,"bScore"),eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_QCD_GJetsB_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsL")  ,eventweight, load_qcd, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_QCD_GJetsB_dataSideband, GetBJetVar(load_qcd,tagALGO,"CvsB")  ,eventweight, load_qcd, tagALGO);
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


        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_QCD_GJetsB_dataSideband);

        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_QCD_GJetsB_dataSideband);

        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_QCD_GJetsB_dataSideband);

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
    
} // LoopQCD end }}}
// QCD section end }}}

// sig section {{{
EventBinning BinningFactory(const MakeHistoSIG & v) { return  EventBinning(v.recoPt     ,v.recoEta,v.jetPt,v.jetY,v.chIsoRaw   ); }


EvtSelMgr EvtSelFactory(const MakeHistoSIG& loadvar, const char* tagALGO) // {{{
{
    bool isMC          = true;
    bool isQCD         = false;
    bool HLTOPTION     = false;
    EvtSelMgr output(isMC,isQCD,HLTOPTION);

    output.SetUsedVar_4(loadvar.jetHadFlvr);
    output.SetUsedVar_3(
        loadvar.chIsoRaw,
        loadvar.recoEta,
        loadvar.isMatched);

    output.SetUsedVar_2(
        loadvar.jetPt,
        loadvar.jetEta,
        GetBJetVar(loadvar, tagALGO, "tags_c"),
        loadvar.jetID,
        loadvar.jetPUIDbit,
        loadvar.jetSubVtxMass,
        loadvar.jetSubVtx3DVal,
        loadvar.jetSubVtx3DErr,
        loadvar.jetSubVtxNtrks,
        GetBJetVar(loadvar, tagALGO, "CvsL"),
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
} // EvtSelFactory end }}}
void Fill_AllCTagReshaped( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight, const MakeHistoSIG& loadvars, const char* tagALGO) // {{{
{
    Fill_allctagreshaped_general(bin,h,val, evt_weight,
            GetBJetVarWeights(loadvars,tagALGO, "weight_central"),
            GetBJetVarWeights(loadvars,tagALGO, "weight_PUUp"),
            GetBJetVarWeights(loadvars,tagALGO, "weight_PUDown"),
            GetBJetVarWeights(loadvars,tagALGO, "weight_StatUp"),
            GetBJetVarWeights(loadvars,tagALGO, "weight_StatDown")
            );
} // Fill_AllCTagReshaped end }}}
void LoopSIG( Int_t extracut, const char* dataERA, const char* tagALGO, TFile* fout, const char* inputfilename, int processNEvt = -1 ) // {{{
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();

    fout->cd();

    Hists* BDT_gjet_signalRegion = Hists_BDT("BDT_gjet_signalRegion", "calib_mva");
    Hists* BDT_gjet_dataSideband = Hists_BDT("BDT_gjet_dataSideband", "calib_mva");
    Hists* BDT_gjet_signalRegion_shapeUncUp = Hists_BDT("BDT_gjet_signalRegion_shapeUncUp", "mva");
    Hists* BDT_gjet_dataSideband_shapeUncUp = Hists_BDT("BDT_gjet_dataSideband_shapeUncUp", "mva");


    Hists_CTagReshaped* jettag0_gjet_DiJetL_signalRegion = new Hists_CTagReshaped("jettag0_gjet_DiJetL_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_DiJetL_dataSideband = new Hists_CTagReshaped("jettag0_gjet_DiJetL_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_DiJetC_signalRegion = new Hists_CTagReshaped("jettag0_gjet_DiJetC_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_DiJetC_dataSideband = new Hists_CTagReshaped("jettag0_gjet_DiJetC_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_DiJetB_signalRegion = new Hists_CTagReshaped("jettag0_gjet_DiJetB_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_DiJetB_dataSideband = new Hists_CTagReshaped("jettag0_gjet_DiJetB_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_GJetsL_signalRegion = new Hists_CTagReshaped("jettag0_gjet_GJetsL_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_GJetsL_dataSideband = new Hists_CTagReshaped("jettag0_gjet_GJetsL_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_GJetsC_signalRegion = new Hists_CTagReshaped("jettag0_gjet_GJetsC_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_GJetsC_dataSideband = new Hists_CTagReshaped("jettag0_gjet_GJetsC_dataSideband", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_GJetsB_signalRegion = new Hists_CTagReshaped("jettag0_gjet_GJetsB_signalRegion", Form("%s.bScore",tagALGO));
    Hists_CTagReshaped* jettag0_gjet_GJetsB_dataSideband = new Hists_CTagReshaped("jettag0_gjet_GJetsB_dataSideband", Form("%s.bScore",tagALGO));

    Hists_CTagReshaped* jettag1_gjet_DiJetL_signalRegion = new Hists_CTagReshaped("jettag1_gjet_DiJetL_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_DiJetL_dataSideband = new Hists_CTagReshaped("jettag1_gjet_DiJetL_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_DiJetC_signalRegion = new Hists_CTagReshaped("jettag1_gjet_DiJetC_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_DiJetC_dataSideband = new Hists_CTagReshaped("jettag1_gjet_DiJetC_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_DiJetB_signalRegion = new Hists_CTagReshaped("jettag1_gjet_DiJetB_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_DiJetB_dataSideband = new Hists_CTagReshaped("jettag1_gjet_DiJetB_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_GJetsL_signalRegion = new Hists_CTagReshaped("jettag1_gjet_GJetsL_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_GJetsL_dataSideband = new Hists_CTagReshaped("jettag1_gjet_GJetsL_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_GJetsC_signalRegion = new Hists_CTagReshaped("jettag1_gjet_GJetsC_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_GJetsC_dataSideband = new Hists_CTagReshaped("jettag1_gjet_GJetsC_dataSideband", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_GJetsB_signalRegion = new Hists_CTagReshaped("jettag1_gjet_GJetsB_signalRegion", Form("%s.CvsL",tagALGO));
    Hists_CTagReshaped* jettag1_gjet_GJetsB_dataSideband = new Hists_CTagReshaped("jettag1_gjet_GJetsB_dataSideband", Form("%s.CvsL",tagALGO));

    Hists_CTagReshaped* jettag2_gjet_DiJetL_signalRegion = new Hists_CTagReshaped("jettag2_gjet_DiJetL_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_DiJetL_dataSideband = new Hists_CTagReshaped("jettag2_gjet_DiJetL_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_DiJetC_signalRegion = new Hists_CTagReshaped("jettag2_gjet_DiJetC_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_DiJetC_dataSideband = new Hists_CTagReshaped("jettag2_gjet_DiJetC_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_DiJetB_signalRegion = new Hists_CTagReshaped("jettag2_gjet_DiJetB_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_DiJetB_dataSideband = new Hists_CTagReshaped("jettag2_gjet_DiJetB_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_GJetsL_signalRegion = new Hists_CTagReshaped("jettag2_gjet_GJetsL_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_GJetsL_dataSideband = new Hists_CTagReshaped("jettag2_gjet_GJetsL_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_GJetsC_signalRegion = new Hists_CTagReshaped("jettag2_gjet_GJetsC_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_GJetsC_dataSideband = new Hists_CTagReshaped("jettag2_gjet_GJetsC_dataSideband", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_GJetsB_signalRegion = new Hists_CTagReshaped("jettag2_gjet_GJetsB_signalRegion", Form("%s.CvsB",tagALGO));
    Hists_CTagReshaped* jettag2_gjet_GJetsB_dataSideband = new Hists_CTagReshaped("jettag2_gjet_GJetsB_dataSideband", Form("%s.CvsB",tagALGO));

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

        if (jentry % 1000000 == 0){ fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries); }


        // not to use mcweight because pre-scaled HLT owns different effective luminosity. So put it afterward.
        //Float_t eventweight = load_sig.mcweight * load_sig.puwei;
        Float_t eventweight = load_sig.puwei * \
                              load_sig.genWeight * load_sig.crossSection / load_sig.integratedGenWeight;

	
        const EventBinning evtbin = BinningFactory(load_sig);
        int hltbit = TriggerBit(dataERA, evtbin.pPtBin);
        EvtSelMgr sel = EvtSelFactory(load_sig, tagALGO);
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
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetL_signalRegion, GetBJetVar(load_sig,tagALGO,"bScore"), eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetL_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsL")  , eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetL_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsB")  , eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_DiJetL_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isLJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetL_dataSideband, GetBJetVar(load_sig,tagALGO,"bScore"),eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetL_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsL")  ,eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetL_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsB")  ,eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_DiJetL_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isLJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsL_signalRegion, GetBJetVar(load_sig,tagALGO,"bScore"), eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsL_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsL")  , eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsL_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsB")  , eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_GJetsL_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isLJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsL_dataSideband, GetBJetVar(load_sig,tagALGO,"bScore"),eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsL_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsL")  ,eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsL_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsB")  ,eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_GJetsL_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }


        // c jet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isCJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetC_signalRegion, GetBJetVar(load_sig,tagALGO,"bScore"), eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetC_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsL")  , eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetC_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsB")  , eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_DiJetC_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isCJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetC_dataSideband, GetBJetVar(load_sig,tagALGO,"bScore"),eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetC_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsL")  ,eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetC_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsB")  ,eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_DiJetC_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isCJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsC_signalRegion, GetBJetVar(load_sig,tagALGO,"bScore"), eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsC_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsL")  , eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsC_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsB")  , eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_GJetsC_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isCJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsC_dataSideband, GetBJetVar(load_sig,tagALGO,"bScore"),eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsC_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsL")  ,eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsC_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsB")  ,eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_GJetsC_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }


        // bjet
        if ( evtbin.isSignalRegion && isFakePhoton && sel.isBJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetB_signalRegion, GetBJetVar(load_sig,tagALGO,"bScore"), eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetB_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsL")  , eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetB_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsB")  , eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_DiJetB_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband && isFakePhoton && sel.isBJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_DiJetB_dataSideband, GetBJetVar(load_sig,tagALGO,"bScore"),eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_DiJetB_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsL")  ,eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_DiJetB_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsB")  ,eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_DiJetB_dataSideband, load_sig.jetSubVtxMass,eventweight);
        }

        if ( evtbin.isSignalRegion &&!isFakePhoton && sel.isBJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsB_signalRegion, GetBJetVar(load_sig,tagALGO,"bScore"), eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsB_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsL")  , eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsB_signalRegion, GetBJetVar(load_sig,tagALGO,"CvsB")  , eventweight, load_sig, tagALGO);
            Fill(evtbin,jettag3_gjet_GJetsB_signalRegion, load_sig.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband &&!isFakePhoton && sel.isBJet() )
        {
            Fill_AllCTagReshaped(evtbin,jettag0_gjet_GJetsB_dataSideband, GetBJetVar(load_sig,tagALGO,"bScore"),eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag1_gjet_GJetsB_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsL")  ,eventweight, load_sig, tagALGO);
            Fill_AllCTagReshaped(evtbin,jettag2_gjet_GJetsB_dataSideband, GetBJetVar(load_sig,tagALGO,"CvsB")  ,eventweight, load_sig, tagALGO);
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


        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag0_gjet_GJetsB_dataSideband);

        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag1_gjet_GJetsB_dataSideband);

        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetL_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetL_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetC_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetC_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetB_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_DiJetB_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsL_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsL_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsC_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsC_dataSideband);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsB_signalRegion);
        Write_AllCTagReshaped(bin,jettag2_gjet_GJetsB_dataSideband);

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
        Write(bin,jettag3_gjet_GJetsB_dataSideband);
    }
} // LoopSIG end }}}
// sig section end }}}

// data section {{{
EventBinning BinningFactory(const MakeHistoData& v) { return  EventBinning(v.recoPtCalib,v.recoEta,v.jetPt,v.jetY,v.calib_chIso); }


EvtSelMgr EvtSelFactory(const MakeHistoData& loadvar, const char* tagALGO) // {{{
{
    bool isMC          = false;
    bool isQCD         = false;
    bool HLTOPTION     = true;
    EvtSelMgr output(isMC,isQCD,HLTOPTION);

    output.SetUsedVar_4(0);
    output.SetUsedVar_3(
        loadvar.calib_chIso,
        loadvar.recoEta,
        0);

    output.SetUsedVar_2(
        loadvar.jetPt,
        loadvar.jetEta,
        GetBJetVar(loadvar, tagALGO, "tags_c"),
        0,
        0,
        loadvar.jetSubVtxMass,
        loadvar.jetSubVtx3DVal,
        loadvar.jetSubVtx3DErr,
        loadvar.jetSubVtxNtrks,
        GetBJetVar(loadvar, tagALGO, "CvsL"),
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
} // EvtSelFactory end }}}
void LoopData( Int_t extracut, const char* dataERA, const char* tagALGO, TFile* fout, const char* inputfilename, int processNEvt = -1 ) // {{{
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();
    fout->cd();

    Hists* BDT_data_signalRegion = Hists_BDT("BDT_data_signalRegion", "mva");
    Hists* BDT_data_dataSideband = Hists_BDT("BDT_data_dataSideband", "mva");

    Hists* jettag0_data_signalRegion = Hists_CTags("jettag0_data_signalRegion", Form("%s.bScore",tagALGO));
    Hists* jettag0_data_dataSideband = Hists_CTags("jettag0_data_dataSideband", Form("%s.bScore",tagALGO));

    Hists* jettag1_data_signalRegion = Hists_CTags("jettag1_data_signalRegion", Form("%s.CvsL",tagALGO));
    Hists* jettag1_data_dataSideband = Hists_CTags("jettag1_data_dataSideband", Form("%s.CvsL",tagALGO));

    Hists* jettag2_data_signalRegion = Hists_CTags("jettag2_data_signalRegion", Form("%s.CvsB",tagALGO));
    Hists* jettag2_data_dataSideband = Hists_CTags("jettag2_data_dataSideband", Form("%s.CvsB",tagALGO));

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

        if (jentry % 1000000 == 0)
        { fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries); }
        Float_t eventweight = 1.;

        const EventBinning evtbin = BinningFactory(load_data);
        int hltbit = TriggerBit(dataERA, evtbin.pPtBin);
        EvtSelMgr sel = EvtSelFactory(load_data, tagALGO);


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
            Fill(evtbin,jettag0_data_signalRegion, GetBJetVar(load_data,tagALGO,"bScore"),eventweight);
            Fill(evtbin,jettag1_data_signalRegion, GetBJetVar(load_data,tagALGO,"CvsL")  ,eventweight);
            Fill(evtbin,jettag2_data_signalRegion, GetBJetVar(load_data,tagALGO,"CvsB")  ,eventweight);
            Fill(evtbin,jettag3_data_signalRegion, load_data.jetSubVtxMass,eventweight);
        }
        if ( evtbin.isDataSideband )
        {
            Fill(evtbin,BDT_data_dataSideband    , load_data.mva,eventweight);
            Fill(evtbin,jettag0_data_dataSideband, GetBJetVar(load_data,tagALGO,"bScore"),eventweight);
            Fill(evtbin,jettag1_data_dataSideband, GetBJetVar(load_data,tagALGO,"CvsL")  ,eventweight);
            Fill(evtbin,jettag2_data_dataSideband, GetBJetVar(load_data,tagALGO,"CvsB")  ,eventweight);
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
    
} // LoopData end }}}
// data section end }}}

void Loop(Int_t extracut, const char* dataERA, const char* tagALGO, const char* dataTYPE, const char* inputfilename )
{
    int NEVENT = -1; // for all event
    if ( extracut < 0 )
    { // for testing
        NEVENT = 10;
        extracut = 0;
    }
    NEVENT = -1;

    TFile *fout = new TFile( Form("makehisto_%s.root", dataTYPE),"recreate");
    LOG("output file : %s", fout->GetName());

    int processTag = 0;
    if ( strcmp(dataTYPE,"data") == 0 )
    { LoopData(extracut, dataERA, tagALGO, fout, inputfilename, NEVENT); processTag += 1; }
    if ( strcmp(dataTYPE,"gjet") == 0 )
    { LoopSIG (extracut, dataERA, tagALGO, fout, inputfilename, NEVENT); processTag += 1; }
    if ( strcmp(dataTYPE,"QCD") == 0 )
    { LoopQCD (extracut, dataERA, tagALGO, fout, inputfilename, NEVENT); processTag += 1; }


    fout->Close();
    if ( processTag == 0 ) std::cerr << Form("input data type '%s' is wrong. Please check!\n", dataTYPE);
}

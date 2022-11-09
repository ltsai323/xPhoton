#define MakeHisto_cxx
#include "MakeHisto.h"
//#include "HLTTriggerBitSetting.cc"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>
#include <iostream>
#include <TLorentzVector.h>
#define NUMBIN_PHOETA 2
#define NUMBIN_JETETA 3
#define NUMBIT_HLT 9 // 0~8
#define NUMBIN_ISOVAR 4
#define NUMBIN_MATCHEDPHOTONSTATUS 5
#define NUMBIN_JETFLVR 3
#define NUM_BTAGVAR 4
#define NUM_PARITY 2


std::vector<float> ptbin_ranges()
{
    // for 2016
    //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
    std::vector<float> vec_ptcut{25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
    //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15] // old version
    return vec_ptcut;
}

void MakeHisto::Loop(Int_t extracut = 0)
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();

    if (fChain == 0) return;
    TRandom3 *trd = new TRandom3();

    TFile *fout = new TFile( Form("makehisto_%s.root", _outputlabel),"recreate");
    fout->cd();
    cout << "OUTPUT:" << Form("makehisto_%s.root", _outputlabel) << endl;
    BinnedHist* h_BDT_all = new BinnedHist1D_BDT    ( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2}, "BDT_all.%d_%d_%d_%d");
    BinnedHist* h_BDT     = new BinnedHist1D_BDT    ( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2}, "BDT.%d_%d_%d_%d"    );
    BinnedHist* h_Pt_all  = new BinnedHist1D_PtAll  ( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2}, "Pt_all.%d_%d_%d_%d" );
    BinnedHist* h_Pt      = new BinnedHist1D_Pt     ( {NUMBIN_PHOETA,2}, "Pt.%d_%d");
    BinnedHist* h_Ptspec  = new BinnedHist1D_Pt     ( {NUMBIN_PHOETA,2}, "Pt_spec.%d_%d");

    BinnedHist* h_IsovsBDT = new BinnedHist2D_ISOvsBDT(
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR},"IsovsBDT.%d_%d_%d_%d_%d");
    BinnedHist* h_IsovsBDTorig = new BinnedHist2D_ISOvsBDT(
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR},"IsovsBDTorig.%d_%d_%d_%d_%d" );
    BinnedHist* jc_IsovsBDT = new BinnedHist2D_ISOvsBDT(
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR},"jetcut_IsovsBDT.%d_%d_%d_%d_%d" );
    BinnedHist* jc_IsovsBDTorig = new BinnedHist2D_ISOvsBDT(
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR},"jetcut_IsovsBDTorig.%d_%d_%d_%d_%d" );

    BinnedHist* h_HLT_all       = new BinnedHist1D_HLT( {NUMBIN_PHOETA,NUMBIT_HLT} ,"HLT_ebee.%d_bit%d"           );
    BinnedHist* h_HLTpass       = new BinnedHist1D_HLT( {NUMBIN_PHOETA,NUMBIT_HLT} ,"HLT_ebee.%d_bit%d_pass"      );
    BinnedHist* h_HLTpass_test  = new BinnedHist1D_HLT( {NUMBIN_PHOETA,NUMBIT_HLT} ,"HLT_ebee.%d_bit%d_pass_test" );

    TH1F* h_phopt = new TH1F("phoptDist", "overall pho pt distribution", 200, 0., 500.);
    TH1F* h_jetpt = new TH1F("jetptDist", "overall jet pt distribution", 200, 0., 500.);

    BinnedHist* mySigSignalRegionBDTOrig= new BinnedHist1D_BDT( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT}, "testBDTsig_signalRegionOrig.%d_%d_%d");
    BinnedHist* mySigSignalRegionBDT    = new BinnedHist1D_BDT( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT}, "testBDTsig_signalRegion.%d_%d_%d");
    BinnedHist* myQCDSignalRegionBDT    = new BinnedHist1D_BDT( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT}, "testBDTqcd_signalRegion.%d_%d_%d");
    BinnedHist* myExpSignalRegionBDT    = new BinnedHist1D_BDT( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT}, "testBDTexp_signalRegion.%d_%d_%d");
    BinnedHist* mySigSidebandRegionBDT  = new BinnedHist1D_BDT( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT}, "testBDTsig_sidebandRegion.%d_%d_%d");
    BinnedHist* myQCDSidebandRegionBDT  = new BinnedHist1D_BDT( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT}, "testBDTqcd_sidebandRegion.%d_%d_%d");
    BinnedHist* myExpSidebandRegionBDT  = new BinnedHist1D_BDT( {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT}, "testBDTexp_sidebandRegion.%d_%d_%d");

    TH1F *h_EB_HLTpass = new TH1F("EB_HLTpass","passed HLT bin", NUMBIN_PHOPT+1, 0., NUMBIN_PHOPT+1);
    TH1F *h_EE_HLTpass = new TH1F("EE_HLTpass","passed HLT bin", NUMBIN_PHOPT+1, 0., NUMBIN_PHOPT+1);
    TH1F *h_EB_HLT_all = new TH1F("EB_HLT_all","all HLT photon", NUMBIN_PHOPT+1, 0., NUMBIN_PHOPT+1);
    TH1F *h_EE_HLT_all = new TH1F("EE_HLT_all","all HLT photon", NUMBIN_PHOPT+1, 0., NUMBIN_PHOPT+1);

    TH1F *h_chiso_sg = new TH1F("chiso_sg","chiso signal region", 150, 0., 30);
    TH1F *h_chworst_sg = new TH1F("chworst_sg","chworst signal region", 150, 0., 30);

    int _NPtBin=20;
    TH1F *h_HLTstat_EBPtBin[_NPtBin];
    TH1F *h_HLTstat_EEPtBin[_NPtBin];
    for ( int ibin = 0; ibin<_NPtBin; ++ibin )
    {
        h_HLTstat_EBPtBin[ibin]= new TH1F( Form("HLTStat_EB_pPtBin%d",ibin),"",16,-1,15 );
        h_HLTstat_EEPtBin[ibin]= new TH1F( Form("HLTStat_EE_pPtBin%d",ibin),"",16,-1,15 );
    }

    BinnedHist* h_btagDeepCSV_BvsAll_central    = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.0_0_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_BvsAll_up         = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.1_0_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_BvsAll_down       = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.2_0_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_CvsL_central      = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.0_1_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_CvsL_up           = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.1_1_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_CvsL_down         = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.2_1_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_CvsB_central      = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.0_2_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_CvsB_up           = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.1_2_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_CvsB_down         = new BinnedHist2D_BTAGvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.2_2_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_secVtxMass_central= new BinnedHist2D_secVTXMASSvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.0_3_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_secVtxMass_up     = new BinnedHist2D_secVTXMASSvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.1_3_%d__%d_%d_%d__%d_%d");
    BinnedHist* h_btagDeepCSV_secVtxMass_down   = new BinnedHist2D_secVTXMASSvsBDT(
        {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY}, "btagDeepCSV.2_3_%d__%d_%d_%d__%d_%d");






    Long64_t nentries = fChain->GetEntries();
    printf("nentries %lli \n", nentries);
    printf("HLT option %d \n", HLTOPTION);

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        bool basicRecording = true;
        bool fiducialPhoton = true;
        bool HLTRequirement = false;
        bool isSignalRegion = false;
        bool isDataSideband = false;
        bool jetSelAcquired = false;
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        if (jentry % 100000 == 0){
            fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries);
          }


        // new
        Float_t eventweight = IsMC() ? mcweight * puwei : 1.;
        Float_t photonpt = recoPt;
        Float_t chargedIsolation = IsMC() ? chIsoRaw : calib_chIso;


        //test new mva with isolation smearing
        Float_t bdt_score = IsMC() ? calib_mva : mva; // for MC, use of weighted bdt score.
        Float_t orig_bdt = IsMC() ? mva : -999; // for MC, get use this to be syst err.

        int ebee = EBEE(recoEta);
        int ptbin = IsMC() ? Ptbin(recoPt) : Ptbin(recoPtCalib); // only pt bin used calibrated pt in data
        int hltbit = triggerbit(_dataera, ptbin);
        int jetbin = JetEtaBin(jetPt,jetY);
        int isfakephoton = 0;
        if( IsMC() &&  isMatched!=1 && isConverted!=1 && isMatchedEle!=1) isfakephoton=1; //fake
        int jetflvBin = JetFlavourBin(jetHadFlvr);
        int phoMatchStatIdx = PhoMatchedStatus();
        int parityIdx = EventParity(jentry);

	

        float btag_evtweight_central     = eventweight * bTagWeight_Central(jetflvBin);
        float btag_evtweight_up  = eventweight * bTagWeight_Up(jetflvBin);
        float btag_evtweight_down= eventweight * bTagWeight_Down(jetflvBin);
              btag_evtweight_up  = 1.;





        if(TMath::Abs(recoSCEta)>1.4442 && TMath::Abs(recoSCEta)<1.566) basicRecording = false;
        if(TMath::Abs(recoSCEta)>2.5) basicRecording = false;
        if(MET/photonpt > 0.7) basicRecording = false;
        if ( eleVeto == 0 ) basicRecording = false;
        if ( ptbin<0 ) basicRecording = false;


        // these selections are in PhotonSelections.cc
        if ( TMath::Abs(recoSCEta)<1.5 && sieieFull5x5 > 0.012 ) fiducialPhoton = false;
        if ( TMath::Abs(recoSCEta)<1.5 && HoverE       > 0.08  ) fiducialPhoton = false;
        if ( TMath::Abs(recoSCEta)>1.5 && sieieFull5x5 > 0.027 ) fiducialPhoton = false;
        if ( TMath::Abs(recoSCEta)>1.5 && HoverE       > 0.05  ) fiducialPhoton = false;


        HLTRequirement = HLTPassed(hltbit);
        isSignalRegion = PhoSignalRegion(chargedIsolation, recoEta);
        isDataSideband = PhoDataSideband(chargedIsolation, recoEta);
        jetSelAcquired = PassJetAdditionalSelection(extracut);

        if ( basicRecording )
        {
            h_BDT_all->Fill({ebee,jetbin,ptbin,isfakephoton},bdt_score, eventweight);
            h_Pt_all ->Fill({ebee,jetbin,ptbin,isfakephoton},photonpt , eventweight);
            if ( basicRecording && fiducialPhoton && HLTRequirement && jetSelAcquired )
            {
                h_phopt->Fill(photonpt, eventweight);
                h_jetpt->Fill(jetPt, eventweight);
            }
        }
        if ( basicRecording && fiducialPhoton )
        {
            // checking plot
            if      ( ebee == 0 )
            {
                h_EB_HLT_all->Fill(ptbin);
                if ( (phoFiredTrgs>>hltbit)&1 )
                    h_EB_HLTpass->Fill(ptbin);
                
                
                if ( ptbin < _NPtBin )
                {
                    h_HLTstat_EBPtBin[ptbin]->Fill(-1);
                    for ( int ihlt = 0; ihlt < 8; ++ihlt)
                        if ( (phoFiredTrgs>>ihlt)&1 )
                            h_HLTstat_EBPtBin[ptbin]->Fill(ihlt);
                }
            }
            else if ( ebee == 1 )
            {
                h_EE_HLT_all->Fill(ptbin);
                if ( (phoFiredTrgs>>hltbit)&1 )
                    h_EE_HLTpass->Fill(ptbin);


                if ( ptbin < _NPtBin )
                {
                    h_HLTstat_EEPtBin[ptbin]->Fill(-1);
                    for ( int ihlt = 0; ihlt < 15; ++ihlt)
                        if ( (phoFiredTrgs>>ihlt)&1 )
                            h_HLTstat_EEPtBin[ptbin]->Fill(ihlt);
                }
            }
        }
        if ( basicRecording && fiducialPhoton && HLTRequirement )
        {
            h_IsovsBDT    ->Fill({ebee,jetbin,ptbin,isfakephoton,0},bdt_score, chargedIsolation, eventweight);
            h_IsovsBDT    ->Fill({ebee,jetbin,ptbin,isfakephoton,1},bdt_score, phoIsoRaw, eventweight);
            h_IsovsBDT    ->Fill({ebee,jetbin,ptbin,isfakephoton,2},bdt_score, chargedIsolation+phoIsoRaw, eventweight);
            h_IsovsBDT    ->Fill({ebee,jetbin,ptbin,isfakephoton,3},bdt_score, chWorstRaw, eventweight);
            h_IsovsBDTorig->Fill({ebee,jetbin,ptbin,isfakephoton,0},orig_bdt, chargedIsolation, eventweight);
            h_IsovsBDTorig->Fill({ebee,jetbin,ptbin,isfakephoton,1},orig_bdt, phoIsoRaw, eventweight);
            h_IsovsBDTorig->Fill({ebee,jetbin,ptbin,isfakephoton,2},orig_bdt, chargedIsolation+phoIsoRaw, eventweight);
            h_IsovsBDTorig->Fill({ebee,jetbin,ptbin,isfakephoton,3},orig_bdt, chWorstRaw, eventweight);
            // signal region
            if ( isSignalRegion )
            {
                if      ( IsMC() && isMatched==1 )
                {
                    mySigSignalRegionBDT->Fill({ebee,jetbin,ptbin},bdt_score,eventweight);
                    mySigSignalRegionBDTOrig->Fill({ebee,jetbin,ptbin},orig_bdt,eventweight);
                }
                else if ( IsMC() && isMatched!=1 )
                    myQCDSignalRegionBDT->Fill({ebee,jetbin,ptbin},bdt_score,eventweight);
                else if (!IsMC() )
                    myExpSignalRegionBDT->Fill({ebee,jetbin,ptbin},bdt_score,eventweight);
            }
            // sideband region
            if ( isDataSideband )
            {
                if      ( IsMC() && isMatched==1 )
                    mySigSidebandRegionBDT->Fill({ebee,jetbin,ptbin},bdt_score,eventweight);
                else if ( IsMC() && isMatched!=1 )
                    myQCDSidebandRegionBDT->Fill({ebee,jetbin,ptbin},bdt_score,eventweight);
                else if (!IsMC() )
                    myExpSidebandRegionBDT->Fill({ebee,jetbin,ptbin},bdt_score,eventweight);
            }
        }

        if ( basicRecording && fiducialPhoton && HLTRequirement && jetSelAcquired )
        {
            jc_IsovsBDT    ->Fill({ebee,jetbin,ptbin,isfakephoton,0},bdt_score, chargedIsolation, eventweight);
            jc_IsovsBDT    ->Fill({ebee,jetbin,ptbin,isfakephoton,1},bdt_score, phoIsoRaw, eventweight);
            jc_IsovsBDT    ->Fill({ebee,jetbin,ptbin,isfakephoton,2},bdt_score, chargedIsolation+phoIsoRaw, eventweight);
            jc_IsovsBDT    ->Fill({ebee,jetbin,ptbin,isfakephoton,3},bdt_score, chWorstRaw, eventweight);
            jc_IsovsBDTorig->Fill({ebee,jetbin,ptbin,isfakephoton,0},orig_bdt, chargedIsolation, eventweight);
            jc_IsovsBDTorig->Fill({ebee,jetbin,ptbin,isfakephoton,1},orig_bdt, phoIsoRaw, eventweight);
            jc_IsovsBDTorig->Fill({ebee,jetbin,ptbin,isfakephoton,2},orig_bdt, chargedIsolation+phoIsoRaw, eventweight);
            jc_IsovsBDTorig->Fill({ebee,jetbin,ptbin,isfakephoton,3},orig_bdt, chWorstRaw, eventweight);


            h_btagDeepCSV_BvsAll_central    ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_BvsAll , chargedIsolation,btag_evtweight_central);
            h_btagDeepCSV_BvsAll_up         ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_BvsAll , chargedIsolation,btag_evtweight_up);
            h_btagDeepCSV_BvsAll_down       ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_BvsAll , chargedIsolation,btag_evtweight_down);
            h_btagDeepCSV_CvsL_central      ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_CvsL   , chargedIsolation,btag_evtweight_central);
            h_btagDeepCSV_CvsL_up           ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_CvsL   , chargedIsolation,btag_evtweight_up);
            h_btagDeepCSV_CvsL_down         ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_CvsL   , chargedIsolation,btag_evtweight_down);
            h_btagDeepCSV_CvsB_central      ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_CvsB   , chargedIsolation,btag_evtweight_central);
            h_btagDeepCSV_CvsB_up           ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_CvsB   , chargedIsolation,btag_evtweight_up);
            h_btagDeepCSV_CvsB_down         ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetDeepCSVDiscriminatorTags_CvsB   , chargedIsolation,btag_evtweight_down);
            h_btagDeepCSV_secVtxMass_central->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetSubVtxMass                      , chargedIsolation,btag_evtweight_central);
            h_btagDeepCSV_secVtxMass_up     ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetSubVtxMass                      , chargedIsolation,btag_evtweight_up);
            h_btagDeepCSV_secVtxMass_down   ->Fill({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx},
                jetSubVtxMass                      , chargedIsolation,btag_evtweight_down);
        }

    }

    fout->cd();
    h_phopt->Write();
    h_jetpt->Write();
    h_EB_HLT_all->Write();
    h_EE_HLT_all->Write();
    h_EB_HLTpass->Write();
    h_EE_HLTpass->Write();
    for ( int ibin = 0; ibin<_NPtBin; ++ibin )
    { h_HLTstat_EBPtBin[ibin]->Write(); h_HLTstat_EEPtBin[ibin]->Write(); }


    h_BDT     ->Write(h_BDT     ->MakeDirectory(fout));
    h_Pt_all  ->Write(h_Pt_all  ->MakeDirectory(fout));
    h_Pt      ->Write(h_Pt      ->MakeDirectory(fout));
    h_Ptspec  ->Write(h_Ptspec  ->MakeDirectory(fout));
    h_IsovsBDT->Write(h_IsovsBDT->MakeDirectory(fout));
    h_IsovsBDTorig->Write(h_IsovsBDTorig->MakeDirectory(fout));
    myExpSignalRegionBDT->Write(myExpSignalRegionBDT->MakeDirectory(fout));
    mySigSignalRegionBDT->Write(mySigSignalRegionBDT->MakeDirectory(fout));
    mySigSignalRegionBDTOrig->Write(mySigSignalRegionBDTOrig->MakeDirectory(fout));
    myQCDSignalRegionBDT->Write(myQCDSignalRegionBDT->MakeDirectory(fout));
    myExpSidebandRegionBDT->Write(myExpSidebandRegionBDT->MakeDirectory(fout));
    mySigSidebandRegionBDT->Write(mySigSidebandRegionBDT->MakeDirectory(fout));
    myQCDSidebandRegionBDT->Write(myQCDSidebandRegionBDT->MakeDirectory(fout));

    jc_IsovsBDT->Write(jc_IsovsBDT->MakeDirectory(fout));
    jc_IsovsBDTorig->Write(jc_IsovsBDTorig->MakeDirectory(fout));
    
    TDirectory* HLTdir =h_HLT_all ->MakeDirectory(fout);
    h_HLT_all ->Write(HLTdir);
    h_HLTpass ->Write(HLTdir);
    
    fout->cd();
    h_chiso_sg->Write();
    h_chworst_sg->Write();

    TDirectory* btagdir = h_btagDeepCSV_BvsAll_central->MakeDirectory(fout);
    h_btagDeepCSV_BvsAll_central    ->Write( btagdir );
    h_btagDeepCSV_BvsAll_up         ->Write( btagdir );
    h_btagDeepCSV_BvsAll_down       ->Write( btagdir );
    h_btagDeepCSV_CvsL_central      ->Write( btagdir );
    h_btagDeepCSV_CvsL_up           ->Write( btagdir );
    h_btagDeepCSV_CvsL_down         ->Write( btagdir );
    h_btagDeepCSV_CvsB_central      ->Write( btagdir );
    h_btagDeepCSV_CvsB_up           ->Write( btagdir );
    h_btagDeepCSV_CvsB_down         ->Write( btagdir );
    h_btagDeepCSV_secVtxMass_central->Write( btagdir );
    h_btagDeepCSV_secVtxMass_up     ->Write( btagdir );
    h_btagDeepCSV_secVtxMass_down   ->Write( btagdir );
    

    fout->Close();
}


Int_t MakeHisto::EBEE(Float_t eta)
{
    if ( TMath::Abs(eta)<1.5 )    return 0;
    else                          return 1;
}
Int_t MakeHisto::Ptbin(Float_t pt)
{
    std::vector<float> ptcut = ptbin_ranges();
    int ibin = ptcut.size();

    // returned ibin = 0 to size-1
    while ( ibin-- )
    { if ( pt >= ptcut[ibin] ) return ibin; }

    // nothing found.
    return -1;
}

// unused
Int_t MakeHisto::HLTbit(Float_t pt){

    float ptcut[30] = {22, 30, 36, 50, 75, 90, 120, 165, 175 };

    for(int ibin=0; ibin<8; ibin++){
        if(pt>=ptcut[ibin] && pt<ptcut[ibin+1] ) return ibin;
    }
    if(pt>175) return 8;
    if(pt<22.) return -1;
    return -1;
}

Int_t MakeHisto::JetEtaBin(Float_t pt, Float_t eta) {  
    if(pt< 1e-3) return 2;
    if(TMath::Abs(eta)<1.5) return 0;
    return 1;
}
Int_t MakeHisto::triggerbit( const std::string& dataera, Int_t ptbin){
    if ( dataera == "2016ReReco" )
    {
        if ( ptbin == 0 ) return 0;  //  25- 34 -> 25-34
        if ( ptbin == 1 ) return 1;  //  34- 40 -> 34-41
        if ( ptbin == 2 ) return 2;  //  40- 55 -> 41-56
        if ( ptbin == 3 ) return 3;  //  55- 70 -> 56-70?
        if ( ptbin == 4 ) return 3;  //  70- 85
        if ( ptbin == 5 ) return 4;  // 85-100
        if ( ptbin == 6 ) return 5;  // 100-115
        if ( ptbin == 7 ) return 5;  // 115-135
        if ( ptbin == 8 ) return 6;  // 135-155
        if ( ptbin == 9 ) return 6;  // 155-175
        if ( ptbin ==10 ) return 6;  // 175-190
        if ( ptbin ==11 ) return 7;  // 190-200
        if ( ptbin ==12 ) return 7;  // 200-300
        if ( ptbin ==13 ) return 7;  // 300-350
        if ( ptbin ==14 ) return 7;  // 350-400
        if ( ptbin ==15 ) return 7;  // 400-500
        if ( ptbin ==16 ) return 7;  // 500-750
        if ( ptbin ==17 ) return 7;  // 750-1000
        if ( ptbin ==18 ) return 7;  //1000-1500
        if ( ptbin ==19 ) return 7;  //1500-2000
        if ( ptbin ==20 ) return 7;  //2000-3000
        if ( ptbin ==21 ) return 7;  //3000-10000
        if ( ptbin ==22 ) return 7;  // to inf
    }
    if ( dataera == "UL2017" )
    {
        return 0;
    }
    if ( dataera == "UL2018" )
    {
        if ( ptbin == 0 ) return 0;  //  25- 34
        if ( ptbin == 1 ) return 0;  //  34- 40
        if ( ptbin == 2 ) return 0;  //  40- 55
        if ( ptbin == 3 ) return 1;  //  55- 70
        if ( ptbin == 4 ) return 1;  //  70- 85
        if ( ptbin == 5 ) return 2;  // 85-100
        if ( ptbin == 6 ) return 3;  // 100-115
        if ( ptbin == 7 ) return 3;  // 115-135
        if ( ptbin == 8 ) return 4;  // 135-155
        if ( ptbin == 9 ) return 5;  // 155-175
        if ( ptbin ==10 ) return 6;  // 175-190
        if ( ptbin ==11 ) return 6;  // 190-200
        if ( ptbin ==12 ) return 7;  // 200-300
        if ( ptbin ==13 ) return 8;  // 300-350
        if ( ptbin ==14 ) return 8;  // 350-400
        if ( ptbin ==15 ) return 8;  // 400-500
        if ( ptbin ==16 ) return 8;  // 500-750
        if ( ptbin ==17 ) return 8;  // 750-1000
        if ( ptbin ==18 ) return 8;  //1000-1500
        if ( ptbin ==19 ) return 8;  //1500-2000
        if ( ptbin ==20 ) return 8;  //2000-3000
        if ( ptbin ==21 ) return 8;  //3000-10000
        if ( ptbin ==22 ) return 8;  // to inf
    }

    return -1; // nothing
}
Int_t MakeHisto::JetFlavourBin( int jethadflvr )
{
    // 2 : b // 1 : c // 0 : light
    if     (fabs(jethadflvr)==5) return 2;
    else if(fabs(jethadflvr)==4) return 1;
    return 0;
}
Int_t MakeHisto::PhoMatchedStatus()
{
    Float_t chargedIsolation = IsMC() ? chIsoRaw : calib_chIso;
    bool inSignalRegion = PhoSignalRegion(chargedIsolation, recoEta);
    bool inDataSideband = PhoDataSideband(chargedIsolation, recoEta);

    if (!IsMC() && inSignalRegion ) return 0;
    if (!IsMC()                   ) return 1;

    if ( IsMC() &&!isQCD && isMatched==1 && inSignalRegion ) return 0;
    if ( IsMC() &&!isQCD                                   ) return 1;

    if ( IsMC() && isQCD && isMatched!=1 && inSignalRegion ) return 2;
    if ( IsMC() && isQCD && isMatched!=1 && inDataSideband ) return 3;
    if ( IsMC() && isQCD                                   ) return 4;
    return 0;
}
Int_t MakeHisto::EventParity(Long64_t evtidx)
{ return evtidx%2!=0; }
bool MakeHisto::PassJetAdditionalSelection(int cutIndicator)
{
    if ( jetPt < 30. ) return false;
    if ( fabs(jetEta) > 2.5 ) return false;
    if ( jetDeepCSVTags_c < -0.99 ) return false;
    if ( IsMC() && jetID != 1 ) return false;
    if ( IsMC() && jetPUIDbit != 7 ) return false;

    //if ( mcweight>3000. ) return false;
    if ( cutIndicator == 1 && jetSubVtxMass == 0 ) return false;
    if ( cutIndicator == 2 && jetDeepCSVDiscriminatorTags_CvsL < 0.155) return false;

    return true;
}

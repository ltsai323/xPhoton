#define MakeHisto_cxx
#include "MakeHisto.h"
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

const bool useNewSample = false;

std::vector<float> ptbin_ranges()
{
    // for 2016
    //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
    std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
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
    HistMgr1D _h_BDT_all ( "BDT_all.%d_%d_%d_%d",
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2});
    HistMgr1D _h_BDT     ( "BDT.%d_%d_%d_%d",
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2});
    HistMgr1D _h_Pt_all  ( "Pt_all.%d_%d_%d_%d",
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2});
    HistMgr1D _h_Pt      ( "Pt.%d_%d",
            {NUMBIN_PHOETA,2});
    HistMgr1D _h_Ptspec  ( "Pt_spec.%d_%d",
            {NUMBIN_PHOETA,2});
    HistMgr2D _h_IsovsBDT    ( "IsovsBDT.%d_%d_%d_%d_%d",
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR});
    HistMgr2D _h_IsovsBDTorig( "IsovsBDTorig.%d_%d_%d_%d_%d",
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR});
    HistMgr2D jc_IsovsBDT    ( "jetcut_IsovsBDT.%d_%d_%d_%d_%d",
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR});
    HistMgr2D jc_IsovsBDTorig( "jetcut_IsovsBDTorig.%d_%d_%d_%d_%d",
            {NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,2,NUMBIN_ISOVAR});
    HistMgr1D _h_HLT_all( "HLT_ebee.%d_bit%d",
            {NUMBIN_PHOETA,NUMBIT_HLT} );
    HistMgr1D _h_HLTpass( "HLT_ebee.%d_bit%d_pass",
            {NUMBIN_PHOETA,NUMBIT_HLT} );
    TH1F* _h_phopt = new TH1F("phoptDist", "overall pho pt distribution", 200, 0., 500.);
    TH1F* _h_jetpt = new TH1F("jetptDist", "overall jet pt distribution", 200, 0., 500.);

    _h_BDT_all .SetXaxis( 100,-1.,1.);
    _h_BDT     .SetXaxis( 100,-1.,1.);
    _h_Pt_all  .SetXaxis( 2000, 0., 2000.);
    _h_Pt      .SetXaxis( 200, 0., 2000.);
    _h_Ptspec  .SetXaxis( 200, 0., 2000.);
    _h_IsovsBDT.SetXYaxis( 100, -1., 1., 30, 0., 15);
    _h_IsovsBDTorig.SetXYaxis( 100, -1., 1., 30, 0., 15);
    
    if (useNewSample )
    {
    jc_IsovsBDT.SetXYaxis( 100, -1., 1., 30, 0., 15);
    jc_IsovsBDTorig.SetXYaxis( 100, -1., 1., 30, 0., 15);
    _h_HLT_all .SetXaxis(2000,0.,2000.);
    _h_HLTpass .SetXaxis(2000,0.,2000.);
    }

    TH1F *h_EB_HLTall = new TH1F("EB_HLTall","all HLT photon", 1000, 0., 1000.);
    TH1F *h_EE_HLTall = new TH1F("EE_HLTall","all HLT photon", 1000, 0., 1000.);

    TH1F *h_chiso_sg = new TH1F("chiso_sg","chiso signal region", 150, 0., 30);
    TH1F *h_chworst_sg = new TH1F("chworst_sg","chworst signal region", 150, 0., 30);



    HistMgr2D h_btagDeepCSV_BvsAll_central    ( "btagDeepCSV.0_0_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_BvsAll_up         ( "btagDeepCSV.1_0_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_BvsAll_down       ( "btagDeepCSV.2_0_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_CvsL_central      ( "btagDeepCSV.0_1_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_CvsL_up           ( "btagDeepCSV.1_1_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_CvsL_down         ( "btagDeepCSV.2_1_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_CvsB_central      ( "btagDeepCSV.0_2_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_CvsB_up           ( "btagDeepCSV.1_2_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_CvsB_down         ( "btagDeepCSV.2_2_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_secVtxMass_central( "btagDeepCSV.0_3_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_secVtxMass_up     ( "btagDeepCSV.1_3_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );
    HistMgr2D h_btagDeepCSV_secVtxMass_down   ( "btagDeepCSV.2_3_%d__%d_%d_%d__%d_%d",
                {NUMBIN_JETFLVR,NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT,NUMBIN_MATCHEDPHOTONSTATUS,NUM_PARITY} );

    if (useNewSample )
    {
    h_btagDeepCSV_BvsAll_central    .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_BvsAll_up         .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_BvsAll_down       .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_CvsL_central      .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_CvsL_up           .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_CvsL_down         .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_CvsB_central      .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_CvsB_up           .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_CvsB_down         .SetXYaxis( 10, 0., 1., 30, 0., 15.);
    h_btagDeepCSV_secVtxMass_central.SetXYaxis(100, 0., 5., 30, 0., 15.);
    h_btagDeepCSV_secVtxMass_up     .SetXYaxis(100, 0., 5., 30, 0., 15.);
    h_btagDeepCSV_secVtxMass_down   .SetXYaxis(100, 0., 5., 30, 0., 15.);
    }



    Long64_t nentries = fChain->GetEntries();
    printf("nentries %lli \n", nentries);
    printf("HLT option %d \n", HLTOPTION);

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++) {
        Long64_t ientry = LoadTree(jentry);
        if (ientry < 0) break;
        nb = fChain->GetEntry(jentry);   nbytes += nb;

        if (jentry % 100000 == 0){
            fprintf(stderr, "Processing event %lli of %lli (%.3f)\n", jentry+1, nentries, (jentry+1)*100./nentries);
          }


        // new
        Float_t eventweight = IsMC() ? mcweight * puwei : 1.;
        Float_t photonpt = recoPt;
        // old
        //Float_t eventweight = IsMC() ? xsweight * puwei : 1.;
        if (!IsMC() ) chIsoRaw = calib_chIso; // substitute with calib chIso.

        // if (Cut(ientry) < 0) continue;
        if(TMath::Abs(recoEta)>1.4442 && TMath::Abs(recoEta)<1.566) continue;
        if(TMath::Abs(recoEta)>2.5) continue;

        if(MET/photonpt > 0.7) continue;

        //test new mva with isolation smearing
        //if(isData!=1) 
        //Float_t bdt_score = mva;// norminall
        Float_t bdt_score = IsMC() ? calib_mva : mva; // for MC, use of weighted bdt score.
        Float_t orig_bdt = IsMC() ? mva : -999; // for MC, get use this to be syst err.
        // old
        //Float_t bdt_score = mva; // for MC, use of weighted bdt score.
        //Float_t orig_bdt = IsMC() ? mva_nocorr : -999.;
        // bdt_score = mva + trd->Gaus(0.025,0.05); //extra smearing for signal sys
        // bdt_score = mva - trd->Gaus(0.025,0.05);
        // float tmp_shift = 0.015; if(TMath::Abs(recoSCEta)>1.5) tmp_shift=0.03;
        // bdt_score = mva - tmp_shift;// - trd->Gaus(0.025,0.05);

        //jetY =jetEta;

        //printf("photon eta %.2f, bin %d,  pt %.2f, bin %d , hltbit %d\n", recoEta, EBEE(recoEta), photonpt, Ptbin(photonpt) , HLTbit(photonpt));
        int ebee = EBEE(recoEta);
        //if(recoEta>-1.8 && recoEta<-1.5) printf("ebee bin %d \n", ebee);
        int ptbin = IsMC() ? Ptbin(recoPt) : Ptbin(recoPtCalib); // only pt bin used calibrated pt in data
        //int ptbin = Ptbin(photonpt*0.99); //playing with photon energy scale
        int hltbit = HLTbit(photonpt);
        int jetbin = JetEtaBin(jetY);

        //smearing due to gain switching (G6->G1)    
        TLorentzVector phoP4Orig;
        TLorentzVector *phop4 = &phoP4Orig;
        phop4->SetPtEtaPhiM(photonpt, recoEta, recoPhi,0.);



        if ( eleVeto == 0 ) continue;



        if(ptbin<0) continue;
        //if(photon_jetID==1) continue;
        // if(isData==1 && ((phoFiredTrgs>>triggerbit(ptbin))&1)==0) continue;
        // if(isData==1 && !(((phoFiredTrgs>>8)&1)==1 || MTm>0) ) continue;
        //if(!(((phoFiredTrgs>>8)&1)==1 || MTm>0) ) continue;
        std::string dataera = "2016ReReco";
        if ( dataera == "2016ReReco" )
            if(HLTOPTION==1 && (((phoFiredTrgs>>8)&1)==0) ) continue; //asdf need to add ERA!
        if ( dataera == "UL2018" )
            if(HLTOPTION==1 && (((phoFiredTrgs>>8)&1)==0) ) continue; //asdf need to add ERA!


        int isfakephoton = 0;
        if( IsMC() &&  isMatched!=1 && isConverted!=1 && isMatchedEle!=1) isfakephoton=1; //fake

        _h_BDT_all.GetBin({ebee,jetbin,ptbin,isfakephoton})->Fill(bdt_score, eventweight);
        _h_Pt_all .GetBin({ebee,jetbin,ptbin,isfakephoton})->Fill(photonpt , eventweight);


        // asdf selections
        if ( TMath::Abs(recoEta)<1.5 && sieieFull5x5 > 0.015 ) continue;
        if ( TMath::Abs(recoEta)>1.5 && sieieFull5x5 > 0.045 ) continue;

        _h_IsovsBDT    .GetBin({ebee,jetbin,ptbin,isfakephoton,0})->Fill(bdt_score, chIsoRaw, eventweight);
        _h_IsovsBDT    .GetBin({ebee,jetbin,ptbin,isfakephoton,1})->Fill(bdt_score, phoIsoRaw, eventweight);
        _h_IsovsBDT    .GetBin({ebee,jetbin,ptbin,isfakephoton,2})->Fill(bdt_score, chIsoRaw+phoIsoRaw, eventweight);
        _h_IsovsBDT    .GetBin({ebee,jetbin,ptbin,isfakephoton,3})->Fill(bdt_score, chWorstRaw, eventweight);
        _h_IsovsBDTorig.GetBin({ebee,jetbin,ptbin,isfakephoton,0})->Fill(orig_bdt, chIsoRaw, eventweight);
        _h_IsovsBDTorig.GetBin({ebee,jetbin,ptbin,isfakephoton,1})->Fill(orig_bdt, phoIsoRaw, eventweight);
        _h_IsovsBDTorig.GetBin({ebee,jetbin,ptbin,isfakephoton,2})->Fill(orig_bdt, chIsoRaw+phoIsoRaw, eventweight);
        _h_IsovsBDTorig.GetBin({ebee,jetbin,ptbin,isfakephoton,3})->Fill(orig_bdt, chWorstRaw, eventweight);
if (useNewSample)
{
        // YiShou's code enabled and checking {{{
        // jet selections
        if ( jetPt < 30. ) continue;
        if ( fabs(jetEta) > 2.5 ) continue;
        if ( jetDeepCSVTags_c < -0.99 ) continue;
        if ( IsMC() && jetID != 1 ) continue;
        if ( IsMC() && jetPUIDbit != 7 ) continue;

        //if ( mcweight>3000. ) continue;
        if ( extracut == 1 ){
            if ( jetSubVtxMass == 0 ) continue;
        }else if ( extracut == 2 ){
            if ( jetDeepCSVDiscriminatorTags_CvsL < 0.155) continue;
        }
        // YiShou's code enabled and checking }}}
        jc_IsovsBDT    .GetBin({ebee,jetbin,ptbin,isfakephoton,0})->Fill(bdt_score, chIsoRaw, eventweight);
        jc_IsovsBDT    .GetBin({ebee,jetbin,ptbin,isfakephoton,1})->Fill(bdt_score, phoIsoRaw, eventweight);
        jc_IsovsBDT    .GetBin({ebee,jetbin,ptbin,isfakephoton,2})->Fill(bdt_score, chIsoRaw+phoIsoRaw, eventweight);
        jc_IsovsBDT    .GetBin({ebee,jetbin,ptbin,isfakephoton,3})->Fill(bdt_score, chWorstRaw, eventweight);
        jc_IsovsBDTorig.GetBin({ebee,jetbin,ptbin,isfakephoton,0})->Fill(orig_bdt, chIsoRaw, eventweight);
        jc_IsovsBDTorig.GetBin({ebee,jetbin,ptbin,isfakephoton,1})->Fill(orig_bdt, phoIsoRaw, eventweight);
        jc_IsovsBDTorig.GetBin({ebee,jetbin,ptbin,isfakephoton,2})->Fill(orig_bdt, chIsoRaw+phoIsoRaw, eventweight);
        jc_IsovsBDTorig.GetBin({ebee,jetbin,ptbin,isfakephoton,3})->Fill(orig_bdt, chWorstRaw, eventweight);




        if ( TMath::Abs(recoEta)<1.4442 )
            if(isfakephoton==1&&photonpt>100.){
                h_chiso_sg->Fill(chIsoRaw);
                h_chworst_sg->Fill(chWorstRaw+phoIsoRaw);
            }
        //jetflvr
        int jetflvBin = JetFlavourBin(jetHadFlvr);
        int phoMatchStatIdx = 0;
	int parityIdx = ( jentry % 2 == 0 ) ? 0 : 1;
        // need to be modified asdf
        if ( IsMC() )
        {
            if ( isQCD )
            {
                if ( isMatched!=1 && chIsoRaw < 2.0 ) phoMatchStatIdx = 2;
                else if ( isMatched!=1 && chIsoRaw > 5.0 && chIsoRaw < 10.0 ) phoMatchStatIdx = 3;
                else    phoMatchStatIdx = 4;
            }
            else
            {
                if ( isMatched==1 && chIsoRaw<2.0   ) phoMatchStatIdx = 0;
                else    phoMatchStatIdx = 1;
            }
        }
        else //data
        {
            if ( chIsoRaw<2.0 ) phoMatchStatIdx = 0;
            else    phoMatchStatIdx = 1;
        }

	

        float evtws=0.;
        float evtws_up=0.;
        float evtws_down=0.;

        if(jetflvBin==0){
            evtws      =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_central : 1.;
            evtws_up   =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_up_hf   : 1.;
            evtws_down =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_down_hf : 1.;
        }else if(jetflvBin==1){
            evtws      =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_central     : 1.;
            evtws_up   =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_up_cferr1   : 1.;
            evtws_down =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_down_cferr1 : 1.;
        }else {
            evtws      =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_central : 1.;
            evtws_up   =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_up_lf   : 1.;  
            evtws_down =  IsMC() ? puwei * mcweight* jetSF_DeepCSV_down_lf : 1.;
        }



        h_btagDeepCSV_BvsAll_central    .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_BvsAll , chIsoRaw,evtws);
        h_btagDeepCSV_BvsAll_up         .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_BvsAll , chIsoRaw,evtws_up);
        h_btagDeepCSV_BvsAll_down       .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_BvsAll , chIsoRaw,evtws_down);
        h_btagDeepCSV_CvsL_central      .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_CvsL   , chIsoRaw,evtws);
        h_btagDeepCSV_CvsL_up           .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_CvsL   , chIsoRaw,evtws_up);
        h_btagDeepCSV_CvsL_down         .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_CvsL   , chIsoRaw,evtws_down);
        h_btagDeepCSV_CvsB_central      .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_CvsB   , chIsoRaw,evtws);
        h_btagDeepCSV_CvsB_up           .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_CvsB   , chIsoRaw,evtws_up);
        h_btagDeepCSV_CvsB_down         .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetDeepCSVDiscriminatorTags_CvsB   , chIsoRaw,evtws_down);
        h_btagDeepCSV_secVtxMass_central.GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetSubVtxMass                      , chIsoRaw,evtws);
        h_btagDeepCSV_secVtxMass_up     .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetSubVtxMass                      , chIsoRaw,evtws_up);
        h_btagDeepCSV_secVtxMass_down   .GetBin({jetflvBin,ebee,jetbin,ptbin,phoMatchStatIdx,parityIdx})->
            Fill(jetSubVtxMass                      , chIsoRaw,evtws_down);
        _h_phopt->Fill(photonpt, eventweight);
        _h_jetpt->Fill(jetPt, eventweight);
}
    }

    fout->cd();
    _h_phopt->Write();
    _h_jetpt->Write();


    _h_BDT     .Write(_h_BDT     .MakeDirectory(fout));
    _h_Pt_all  .Write(_h_Pt_all  .MakeDirectory(fout));
    _h_Pt      .Write(_h_Pt      .MakeDirectory(fout));
    _h_Ptspec  .Write(_h_Ptspec  .MakeDirectory(fout));
    _h_IsovsBDT.Write(_h_IsovsBDT.MakeDirectory(fout));
    _h_IsovsBDTorig.Write(_h_IsovsBDTorig.MakeDirectory(fout));
if ( useNewSample )
{
    jc_IsovsBDT.Write(jc_IsovsBDT.MakeDirectory(fout));
    jc_IsovsBDTorig.Write(jc_IsovsBDTorig.MakeDirectory(fout));
    
    TDirectory* HLTdir =_h_HLT_all .MakeDirectory(fout);
    _h_HLT_all .Write(HLTdir);
    _h_HLTpass .Write(HLTdir);
    
    fout->cd();
    h_EB_HLTall->Write();
    h_EE_HLTall->Write();
    h_chiso_sg->Write();
    h_chworst_sg->Write();

    TDirectory* btagdir = h_btagDeepCSV_BvsAll_central.MakeDirectory(fout);
    h_btagDeepCSV_BvsAll_central    .Write( btagdir );
    h_btagDeepCSV_BvsAll_up         .Write( btagdir );
    h_btagDeepCSV_BvsAll_down       .Write( btagdir );
    h_btagDeepCSV_CvsL_central      .Write( btagdir );
    h_btagDeepCSV_CvsL_up           .Write( btagdir );
    h_btagDeepCSV_CvsL_down         .Write( btagdir );
    h_btagDeepCSV_CvsB_central      .Write( btagdir );
    h_btagDeepCSV_CvsB_up           .Write( btagdir );
    h_btagDeepCSV_CvsB_down         .Write( btagdir );
    h_btagDeepCSV_secVtxMass_central.Write( btagdir );
    h_btagDeepCSV_secVtxMass_up     .Write( btagdir );
    h_btagDeepCSV_secVtxMass_down   .Write( btagdir );
}
    

    fout->Close();
}


Int_t MakeHisto::EBEE(Float_t eta)
{
    if ( TMath::Abs(eta)<1.4442 ) return 0;
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

Int_t MakeHisto::JetEtaBin(Float_t eta) {  
    if(jetPt==0) return 2;
    if(TMath::Abs(eta)<1.5) return 0;
    return 1;
}
Int_t MakeHisto::triggerbit(Int_t ptbin){
    if ( ptbin == 0 ) return 0;  //  25- 34
    if ( ptbin == 1 ) return 1;  //  34- 40
    if ( ptbin == 2 ) return 2;  //  40- 55
    if ( ptbin == 3 ) return 3;  //  55- 70
    if ( ptbin == 4 ) return 3;  //  70- 85
    if ( ptbin == 5 ) return 4;  // 85-100
    if ( ptbin == 6 ) return 5;  // 100-115
    if ( ptbin == 7 ) return 5;  // 115-136
    if ( ptbin == 8 ) return 6;  // 135-155
    if ( ptbin == 9 ) return 6;  // 155-175
    if ( ptbin ==10 ) return 6;  // 175-190
    if ( ptbin ==11 ) return 7;  // 190-200
    if ( ptbin ==12 ) return 7;  // 200-220
    if ( ptbin ==13 ) return 7;  // 220-250
    if ( ptbin ==14 ) return 7;  // 250-300
    if ( ptbin ==15 ) return 7;  // 300-inf
    return 0;
}
Int_t MakeHisto::JetFlavourBin( int jethadflvr )
{
    if     (fabs(jethadflvr)==5) return 2;
    else if(fabs(jethadflvr)==4) return 1;
    return 0;
}

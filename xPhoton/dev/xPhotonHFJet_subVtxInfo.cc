#include "xPhoton/xPhoton/interface/xPhotonHFJet_subVtxInfo.h"
#include <vector>
#include <TH1D.h>
#include <TLorentzVector.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TMath.h>
#include <TH1.h>
#include <TH1F.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
using namespace std;
#include <iostream>
#include <TProfile.h>
#include <map>
#include <TNtuple.h>

#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/recoInfo.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include "xPhoton/xPhoton/interface/BTagCalibrationStandalone.h"
#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/JetIDMgr.h"


void xPhotonHFJet(vector<string> pathes, Char_t oname[200]){
    LOG_INFO("end of loading csv file");
    

    TreeReader data(pathes);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");

    TTree *outtree_;

    float ptcut[] = {
           15,    20,    40,    60,    75, // 0
           90,   105,   120,   135,   150, // 5

          160,   170,   180,   190,   200, //10
          220,   250,   300,   350,   400, //15

          500,   750,  1000,  1500,  2000, //20
         3000, 10000}; //22 bins

    float etabin[] = {0., 0.8, 1.5, 2.1, 2.5};

    TH1F* h_subVtxPt    = new TH1F("subVtxPt"   , "pt distribution of secondary vertex in bJet", 70, 0., 350. );
    TH1F* h_subVtxMass  = new TH1F("subVtxMass" , "mass spectrum of secondary vertex in bJet", 88, 0., 22. );
    TH1F* h_subVtx3DVal = new TH1F("subVtx3DVal", "flight distance between PV and SV", 60, 0., 120. );
    TH1F* h_subVtx3DErr = new TH1F("subVtx3DErr", "error of flight distance between PV and SV", 88, 0., 22. );
    TH1F* h_subVtxNtrks = new TH1F("subVtxNtrks", "number of tracks containing in SV", 18,0.,18. );

    TH1F *h_hasGoodVtx = new TH1F("h_hasGoodVtx","hasGoodVtx",2,0,2);
    TH1F *hpthat = new TH1F("hpthat","pt hat", 100, 0., 1000.);
    TH1F *hpthat_wide = new TH1F("hpthat_wide","pt hat wide window", 600, 0., 6000.);

    TH1F *hdpt = new TH1F("hdpt","dpt", 100, 0., 1.);
    TH1F *hdR = new TH1F("hdR","dR", 100, 0., 2.);

    TH1F *hdpt_ele = new TH1F("hdpt_ele","dpt", 100, 0., 1.);
    TH1F *hdR_ele = new TH1F("hdR_ele","dR", 100, 0., 2.);

    TH1F *hdR_genjet = new TH1F("hdR_genjet","dR", 100, 0., 2.);

    TH1F *hdR_pho_lep = new TH1F("hdR_pho_lep","dR pho and lepton", 150, 0., 3.);
    TH1F *hdR_fake_lep = new TH1F("hdR_fake_lep","dR fake and lepton", 150, 0., 3.);

    TH1F *hmcCalIso = new TH1F("hmcCalIso","mcCalIso", 100, 0., 20.);
    TH1F *hmcGenIso = new TH1F("hmcGenIso","mcGenIso", 100, 0., 20.);
    TH1F *hmcpartonIso = new TH1F("hmcpartonIso","mcpartonIso", 100, 0., 20.);
    TH1F *hgenphoEB_pt = new TH1F("hgenphoEB_pt","GenphoEB photon Pt", 3000, 0., 3000.);
    TH1F *hgenphoEB_eta = new TH1F("hgenphoEB_eta","GenphoEB photon eta", 600, -3., 3.);
    TH1F *hgenphoEE_pt = new TH1F("hgenphoEE_pt","GenphoEE photon Pt", 3000, 0., 3000.);
    TH1F *hgenphoEE_eta = new TH1F("hgenphoEE_eta","GenphoEE photon eta", 600, -3., 3.);

    TH1F *hgenphoEB_pt_vbin = new TH1F("hgenphoEB_pt_vbin","GenphoEB photon Pt var. bin", 25, ptcut);
    TH1F *hgenphoEE_pt_vbin = new TH1F("hgenphoEE_pt_vbin","GenphoEE photon Pt var. bin", 25, ptcut);

    TH1F *hgenphoEBEE0_pt_vbin = new TH1F("hgenphoEBEE0_pt_vbin","GenphoEBEE0 photon Pt var. bin", 25, ptcut);
    TH1F *hgenphoEBEE1_pt_vbin = new TH1F("hgenphoEBEE1_pt_vbin","GenphoEBEE1 photon Pt var. bin", 25, ptcut);
    TH1F *hgenphoEBEE2_pt_vbin = new TH1F("hgenphoEBEE2_pt_vbin","GenphoEBEE2 photon Pt var. bin", 25, ptcut);
    TH1F *hgenphoEBEE3_pt_vbin = new TH1F("hgenphoEBEE3_pt_vbin","GenphoEBEE3 photon Pt var. bin", 25, ptcut);

    TH1F *hgenphoEBEE0_pt_vbin_amcnlo = new TH1F("hgenphoEBEE0_pt_vbin_amcnlo","GenphoEBEE0 photon Pt var. bin_amcnlo", 25, ptcut);
    TH1F *hgenphoEBEE1_pt_vbin_amcnlo = new TH1F("hgenphoEBEE1_pt_vbin_amcnlo","GenphoEBEE1 photon Pt var. bin_amcnlo", 25, ptcut);
    TH1F *hgenphoEBEE2_pt_vbin_amcnlo = new TH1F("hgenphoEBEE2_pt_vbin_amcnlo","GenphoEBEE2 photon Pt var. bin_amcnlo", 25, ptcut);
    TH1F *hgenphoEBEE3_pt_vbin_amcnlo = new TH1F("hgenphoEBEE3_pt_vbin_amcnlo","GenphoEBEE3 photon Pt var. bin_amcnlo", 25, ptcut);

    TH1F *hgenphoEBjet0_pt_vbin_amcnlo = new TH1F("hgenphoEBjet0_pt_vbin_amcnlo","GenphoEB jet0 photon Pt var. bin_amcnlo", 25, ptcut);
    TH1F *hgenphoEBjet1_pt_vbin_amcnlo = new TH1F("hgenphoEBjet1_pt_vbin_amcnlo","GenphoEB jet1 photon Pt var. bin_amcnlo", 25, ptcut);
    TH1F *hgenphoEEjet0_pt_vbin_amcnlo = new TH1F("hgenphoEEjet0_pt_vbin_amcnlo","GenphoEB jet0 photon Pt var. bin_amcnlo", 25, ptcut);
    TH1F *hgenphoEEjet1_pt_vbin_amcnlo = new TH1F("hgenphoEEjet1_pt_vbin_amcnlo","GenphoEB jet1 photon Pt var. bin_amcnlo", 25, ptcut);

    hgenphoEB_pt->Sumw2();
    hgenphoEB_eta->Sumw2();
    hgenphoEE_pt->Sumw2();
    hgenphoEE_eta->Sumw2();
    hgenphoEB_pt_vbin->Sumw2();
    hgenphoEE_pt_vbin->Sumw2();
    hgenphoEBEE0_pt_vbin->Sumw2();
    hgenphoEBEE1_pt_vbin->Sumw2();
    hgenphoEBEE2_pt_vbin->Sumw2();
    hgenphoEBEE3_pt_vbin->Sumw2();

    hgenphoEBEE0_pt_vbin_amcnlo->Sumw2();
    hgenphoEBEE1_pt_vbin_amcnlo->Sumw2();
    hgenphoEBEE2_pt_vbin_amcnlo->Sumw2();
    hgenphoEBEE3_pt_vbin_amcnlo->Sumw2();  
    hgenphoEBjet0_pt_vbin_amcnlo->Sumw2(); 
    hgenphoEBjet1_pt_vbin_amcnlo->Sumw2(); 
    hgenphoEEjet0_pt_vbin_amcnlo->Sumw2(); 
    hgenphoEEjet1_pt_vbin_amcnlo->Sumw2(); 

    TH1F *hphoEB_pt_presel_nocsev = new TH1F("hphoEB_pt_presel_nocsev","pt of EB no csev", 25, ptcut);
    TH1F *hphoEB_pt_presel_csev = new TH1F("hphoEB_pt_presel_csev","pt of EB  csev", 25, ptcut);
    TH1F *hphoEE_pt_presel_nocsev = new TH1F("hphoEE_pt_presel_nocsev","pt of EE no csev", 25, ptcut);
    TH1F *hphoEE_pt_presel_csev = new TH1F("hphoEE_pt_presel_csev","pt of EE  csev", 25, ptcut);

    TH1F *hphoEB_pt_presel_den = new TH1F("hphoEB_pt_presel_den","pt of EB can", 25, ptcut);
    TH1F *hphoEB_pt_presel_num = new TH1F("hphoEB_pt_presel_num","pt of EB sel", 25, ptcut);
    TH1F *hphoEE_pt_presel_den = new TH1F("hphoEE_pt_presel_den","pt of EE can", 25, ptcut);
    TH1F *hphoEE_pt_presel_num = new TH1F("hphoEE_pt_presel_num","pt of EE sel", 25, ptcut);

    TH2F *h_phoPt_eta_Z_all = new TH2F("h_phoPt_eta_Z_all","pt eta of photon from Z all", 25, ptcut, 4, etabin);
    TH2F *h_phoPt_eta_Z_csev = new TH2F("h_phoPt_eta_Z_csev","pt eta of photon from Z all", 25, ptcut, 4, etabin);

    TH2F *hgenpho_eta_phi = new TH2F("hgenpho_eta_phi","gen photon eta phi", 500, -2.5, 2.5, 320, -3.2, 3.2);
    TH2F *hgenpho_eta_pt = new TH2F("hgenpho_eta_pt","gen photon eta pt", 50, -2.5, 2.5, 100, 0., 1000.);

    TH1F *h_ngenpho = new TH1F("h_ngenpho","n gen pho", 20, 0., 20);
    TH1F *h_npho = new TH1F("h_npho","n pho", 20, 0., 20);
    TH1F *h_nele = new TH1F("h_nele","n ele", 20, 0., 20);
    TH1F *h_nphoFiredTrgs = new TH1F("h_nphoFiredTrgs","n pho", 20, 0., 20);
    TH1F *h_truepho = new TH1F("h_truepho","true pho", 10, 0., 10.);
    TH1F *h_convpho = new TH1F("h_convpho","converted pho", 10, 0., 10.);
    TH1F *h_phoEt = new TH1F("h_phoEt","pho Et", 200, 0., 1000);
    TH1F *h_jetPt = new TH1F("h_jetPt","jet Pt", 200, 0., 1000);
    TH1F *h_npj = new TH1F("h_npj","n pho jet comb", 20, 0., 20.);
    TH1F *h_pjmass = new TH1F("h_pjmass","inv mass of pho jet", 1000, 0., 10000);
    TH1F *h_njet = new TH1F("h_njet","njet", 20, 0., 20);
    TH1F *h_nrecojet = new TH1F("h_nrecojet","n reco jet", 20, 0., 20);
    TH1F *h_ngenjet = new TH1F("h_ngenjet","n gen jet", 20, 0., 20);

    TH2F *h_detadpt_jet12 = new TH2F("h_detadpt_jet12","deta dpt jet12",3,-1,2,100,0., 1.);


    TH1F *h_dR_phojet = new TH1F("h_dR_phojet","dR of pho jet", 100, 0., 2.);
    TH1F *h_dR_phoele = new TH1F("h_dR_phoele","dR of pho ele", 100, 0., 2.);
    TH1F *h_dpt_phojet = new TH1F("h_dpt_phojet","dpt of pho jet", 100, 0., 4.);

    TH1F *h_jetID = new TH1F("h_jetID", "jetid", 2, 0., 2.);
    TH1F *h_jetIDv = new TH1F("h_jetIDv", "jetid v", 2, 0., 2.);


    TH1F *h_pho2Pt = new TH1F("h_pho2Pt","pho2 Pt", 200, 0., 1000);
    TH1F *h_npp = new TH1F("h_npp","pho pho comb", 20, 0., 20.);
    TH1F *h_ppmass = new TH1F("h_ppmass","inv mass of pho pho", 1000, 0., 10000);
    TH1F *h_ppmass_zoom = new TH1F("h_ppmass_zoom","inv mass of pho pho zoom", 200, 0., 200);
    TH1F *h_EBSeedTime = new TH1F("h_EBSeedTime","EBSeedTime from z",1000, -5., 5.);
    TH1F *h_EESeedTime = new TH1F("h_EESeedTime","EESeedTime from z",1000, -5., 5.);
    TH1F *h_EBSeedTimeW = new TH1F("h_EBSeedTimeW","EBSeedTime from W",1000, -5., 5.);
    TH1F *h_EESeedTimeW = new TH1F("h_EESeedTimeW","EESeedTime from W",1000, -5., 5.);

    TH1F *h_EB_bdt = new TH1F("h_EB_bdt","EB bdt output", 200, -1., 1.);
    TH1F *h_EE_bdt = new TH1F("h_EE_bdt","EE bdt output", 200, -1., 1.);

    TH1F *h_dphi_recoil = new TH1F("h_dphi_recoil","dphi recoil jet", 100., -4., 4.);
    TH1F *h_dpt_recoil = new TH1F("h_dpt_recoil","dpt recoil jet", 100.,-2., 2.);


    TProfile *tp_rho = new TProfile("tp_rho","tp_rho", 100, 0., 100.);
    TProfile *tp_rho_EB = new TProfile("tp_rho_EB","tp_rho_EB", 100, 0., 100.);
    TProfile *tp_rho_EE = new TProfile("tp_rho_EE","tp_rho_EE", 100, 0., 100.);
    TH2F *h2_nVtx_rho = new TH2F("h2_nVtx_rho","h2_nVtx_rho",100, 0., 100., 100., 0., 50.);; //= new TProfile();
    TH2F *h2_nVtx_iso = new TH2F("h2_nVtx_iso","h2_nVtx_iso",100, 0., 100., 1000., 0., 10.);; //= new TProfile();

    TProfile *tp_chIso[10]; //= new TProfile();
    TProfile *tp_phIso[10]; //= new TProfile();
    TProfile *tp_nhIso[10]; //= new TProfile();

    TProfile *tp_chIso_rho[10]; //= new TProfile();
    TProfile *tp_phIso_rho[10]; //= new TProfile();
    TProfile *tp_nhIso_rho[10]; //= new TProfile();

    TH1F *h_Zee_mass = new TH1F("h_Zee_mass","Zee mass", 100, 50., 250);
    TH1F *h_Zee_mass_csev = new TH1F("h_Zee_mass_csev","Zee mass photon CSEV", 100, 50., 250);
    TH1F *h_Zmm_mass = new TH1F("h_Zmm_mass","Zmm mass", 150, 0., 150);
    TH1F *h_MET = new TH1F("h_MET","MET", 100, 0., 200.);
    TH1F *h_Wen_mt = new TH1F("h_Wen_mt","W enue Mt", 150, 0., 150.); 
    TH1F *h_Wmn_mt = new TH1F("h_Wmn_mt","W mnue Mt", 150, 0., 150.); 

    TH2F *h2_mcPID_mcPt = new TH2F("h2_mcPID_mcPt","mcPID vs mcPt", 100, 0., 1000, 30, 0., 30);


    std::map<std::string, TH1F*> histMap;
    histMap["lheEnergy"] = new TH1F("lheEnergy", "hi", 100, 0., 4000.);

    char txt[50];

    for(int ii=0; ii<10; ii++){
        sprintf(txt,"tp_chIso_bin%d",ii);
        tp_chIso[ii] = new TProfile(txt,txt, 100, 0., 100.);
        sprintf(txt,"tp_phIso_bin%d",ii);
        tp_phIso[ii] = new TProfile(txt,txt, 100, 0., 100.);
        sprintf(txt,"tp_nhIso_bin%d",ii);
        tp_nhIso[ii] = new TProfile(txt,txt, 100, 0., 100.);

        sprintf(txt,"tp_chIso_rho_bin%d",ii);
        tp_chIso_rho[ii] = new TProfile(txt,txt, 100, 0., 100.);
        sprintf(txt,"tp_phIso_rho_bin%d",ii);
        tp_phIso_rho[ii] = new TProfile(txt,txt, 100, 0., 100.);
        sprintf(txt,"tp_nhIso_rho_bin%d",ii);
        tp_nhIso_rho[ii] = new TProfile(txt,txt, 100, 0., 100.);
    }


    outtree_ = new TTree("t", "mini tree");
    TNtuple* nt_sumupgenweight = new TNtuple("genweightsummary", "", "sumupgenweight:hasNon1Val");
    Float_t overallGenweight = 0;
    Float_t hasNon1Val = 0;

    // Float_t effArea[3][7] = { //[Ch,Nu,Pho][iPhof_eta]
    //   { 0.012 , 0.010 , 0.014 , 0.012 , 0.016 , 0.020 , 0.012 } ,
    //   { 0.030 , 0.057 , 0.039 , 0.015 , 0.024 , 0.039 , 0.072 } ,
    //   { 0.148 , 0.130 , 0.112 , 0.216 , 0.262 , 0.260 , 0.266 } 
    // } ;

    Float_t jetSubVtxPt_, jetSubVtxMass_, jetSubVtx3DVal_, jetSubVtx3DErr_;
    Int_t jetSubVtxNtrks_;
    Bool_t isData;
    Float_t pthat_, mcPt_, mcEta_, mcPhi_, recoPt, recoPtCalib, recoEta, recoPhi, recoSCEta, r9;
    Float_t mcCalIso04_, mcTrkIso04_;
    Float_t puwei_=1.;
    Float_t r9Full5x5;
    //Int_t   isMatched, isMatchedEle, idLoose, idMedium, idTight, nVtx, eleVeto, nPU;
    Int_t   isMatched, isMatchedEle,  nVtx, eleVeto, nPU;
    Float_t HoverE, chIsoRaw, phoIsoRaw, nhIsoRaw, chWorstIso;
    Float_t rho;
    Int_t phoFiredTrgs_, phohasPixelSeed_;

    Float_t e5x5, rawE, scEtaWidth, scPhiWidth, esRR, esEn, mva, mva_nocorr,  photonIDmva;
    Float_t sieieFull5x5, sipipFull5x5, sieipFull5x5, e2x2Full5x5,  e5x5Full5x5;
    Int_t isConverted;

    //Float_t mcCalIso04, mcTrkIso04;
    Float_t xsweight=XS;
    Float_t mygenweight;
    //Long64_t HLT, HLTIsPrescaled, HLT50ns, HLTIsPrescaled50ns;
    Long64_t HLT, HLTIsPrescaled;// HLT50ns, HLTIsPrescaled50ns;
    Float_t  MET,   METPhi;
    Int_t metFilters;
    Float_t jetPt_, jetEta_, jetPhi_, jetY_, jetJECUnc_;
    Float_t jetGenJetPt_, jetGenJetEta_, jetGenJetPhi_, jetGenJetY_, genHT_;
    Float_t jetCSV2BJetTags_, jetDeepCSVTags_b_, jetDeepCSVTags_bb_, jetDeepCSVTags_c_, jetDeepCSVTags_udsg_;
    Int_t jetPartonID_, jetHadFlvr_, jetGenPartonID_;
    Int_t jetGenPartonMomID_;
    Float_t jetDeepFlavourTags_b_;
    Float_t jetDeepFlavourTags_c_;
    Float_t jetDeepFlavourTags_g_;
    Float_t jetDeepFlavourTags_lepb_;
    Float_t jetDeepFlavourTags_bb_;
    Float_t jetDeepFlavourTags_uds_;
    Float_t jetDeepCSVDiscriminatorTags_BvsAll_;
    Float_t jetDeepCSVDiscriminatorTags_CvsB_;
    Float_t jetDeepCSVDiscriminatorTags_CvsL_;

    Float_t s4;
    Float_t calib_s4,calib_r9Full5x5,calib_scEtaWidth,calib_sieieFull5x5;

    Int_t    run;
    Long64_t event;

    Int_t photon_jetID_;
    Int_t phoIDbit_;
    Int_t jetID;
    Int_t jetPUIDbit;
    
    const unsigned MAX_LHEPARTICLE = 50;
    Int_t nLHE;
    Int_t lhePID[MAX_LHEPARTICLE];
    Float_t lheE[MAX_LHEPARTICLE], lhePx[MAX_LHEPARTICLE], lhePy[MAX_LHEPARTICLE], lhePz[MAX_LHEPARTICLE];


    Float_t SeedTime_, SeedEnergy_, MIPTotEnergy_;
    //if ( hasSubVtxInfo )
    //{
        outtree_->Branch("jetSubVtxPt"   , &jetSubVtxPt_   , "jetSubVtxPt/F"   );
        outtree_->Branch("jetSubVtxMass" , &jetSubVtxMass_ , "jetSubVtxMass/F" );
        outtree_->Branch("jetSubVtx3DVal", &jetSubVtx3DVal_, "jetSubVtx3DVal/F");
        outtree_->Branch("jetSubVtx3DErr"  , &jetSubVtx3DErr_  , "jetSubVtx3DErr/F"  );
        outtree_->Branch("jetSubVtxNtrks", &jetSubVtxNtrks_, "jetSubVtxNtrks/I");
    //}

    outtree_->Branch("run", &run, "run/I");
    outtree_->Branch("event", &event, "event/L");
    outtree_->Branch("isData",         &isData,        "isData/O");
    if (!data.HasMC() )
    {
    outtree_->Branch("HLT",         &HLT,        "HLT/L");
    outtree_->Branch("HLTIsPrescaled", &HLTIsPrescaled,        "HLTIsPrescaled/L");
    }
    outtree_->Branch("phoFiredTrgs", &phoFiredTrgs_,"phoFiredTrgs/I");
    if ( data.HasMC() )
    {
    outtree_->Branch("pthat",        &pthat_,       "pthat/F");
    outtree_->Branch("genHT",        &genHT_,       "genHT/F");
    outtree_->Branch("mcPt",         &mcPt_,        "mcPt/F");
    outtree_->Branch("mcEta",        &mcEta_,       "mcEta/F");
    outtree_->Branch("mcPhi",        &mcPhi_,       "mcPhi/F");
    outtree_->Branch("mcCalIso04",   &mcCalIso04_,   "mcCalIso04/F");
    outtree_->Branch("mcTrkIso04",   &mcTrkIso04_,   "mcTrkIso04/F");
    }
    outtree_->Branch("recoPt",       &recoPt,       "recoPt/F");
    outtree_->Branch("recoPtCalib",  &recoPtCalib,  "recoPtCalib/F");
    outtree_->Branch("recoEta",      &recoEta,      "recoEta/F");
    outtree_->Branch("recoPhi",      &recoPhi,      "recoPhi/F");
    outtree_->Branch("recoSCEta",    &recoSCEta,    "recoSCEta/F");
    outtree_->Branch("r9",           &r9,           "r9/F");
    outtree_->Branch( "s4"          , &s4             , "s4/F"               );
    if ( data.HasMC() )
    {
    outtree_->Branch("isMatched",    &isMatched,    "isMatched/I");
    outtree_->Branch("isMatchedEle", &isMatchedEle, "isMatchedEle/I");
    outtree_->Branch("isConverted",    &isConverted,    "isConverted/I");
    }
    outtree_->Branch("nVtx",         &nVtx,         "nVtx/I");
    if ( data.HasMC() )
    {
    outtree_->Branch("nPU",          &nPU,          "nPU/I");
    outtree_->Branch("puwei",        &puwei_,        "puwei/F");
    }
    outtree_->Branch("eleVeto",      &eleVeto,      "eleVeto/I");
    outtree_->Branch("HoverE",       &HoverE,       "HoverE/F");

    outtree_->Branch("chIsoRaw",     &chIsoRaw,     "chIsoRaw/F");
    outtree_->Branch("chWorstRaw",   &chWorstIso,   "chWorstIso/F");
    outtree_->Branch("phoIsoRaw",    &phoIsoRaw,    "phoIsoRaw/F");
    outtree_->Branch("nhIsoRaw",     &nhIsoRaw,     "nhIsoRaw/F");
    outtree_->Branch("rho",          &rho,          "rho/F"); 

    outtree_->Branch("rawE",         &rawE,         "rawE/F");
    outtree_->Branch("scEtaWidth",   &scEtaWidth,   "scEtaWidth/F");
    outtree_->Branch("scPhiWidth",   &scPhiWidth,   "scPhiWidth/F");
    outtree_->Branch("esRR",         &esRR,         "esRR/F");   
    outtree_->Branch("esEn",         &esEn,         "esEn/F");   
    outtree_->Branch("mva",          &mva,          "mva/F");  
    if ( data.HasMC() )
    {
    outtree_->Branch("mva_nocorr",   &mva_nocorr,   "mva_nocorr/F");  
    }
    outtree_->Branch("photonIDmva",       &photonIDmva,       "photonIDmva/F");  
    outtree_->Branch("phoIDbit",          &phoIDbit_,          "phoIDbit/I");  
    outtree_->Branch("MET",    &MET,    "MET/F");  
    if (!data.HasMC() )
    {
    outtree_->Branch("metFilters",    &metFilters,    "metFilters/I");  
    }
    outtree_->Branch("METPhi",    &METPhi,    "METPhi/F");  
    outtree_->Branch("phohasPixelSeed", &phohasPixelSeed_, "phohasPixelSeed/I");

    outtree_->Branch("sieieFull5x5",        &sieieFull5x5,        "sieieFull5x5/F");
    outtree_->Branch("sieipFull5x5",        &sieipFull5x5,        "sieipFull5x5/F");
    outtree_->Branch("sipipFull5x5",        &sipipFull5x5,        "sipipFull5x5/F");
    outtree_->Branch("r9Full5x5",        &r9Full5x5,        "r9Full5x5/F");
    outtree_->Branch("e2x2Full5x5",        &e2x2Full5x5,        "e2x2Full5x5/F");
    outtree_->Branch("e5x5Full5x5",        &e5x5Full5x5,        "e5x5Full5x5/F");

    outtree_->Branch("jetPt", &jetPt_, "jetPt/F");
    outtree_->Branch("jetEta", &jetEta_, "jetEta/F");
    outtree_->Branch("jetPhi", &jetPhi_, "jetPhi/F");
    outtree_->Branch("jetY", &jetY_, "jetY/F");
    outtree_->Branch("jetJECUnc", &jetJECUnc_, "jetJECUnc/F");
    if ( data.HasMC() )
    {
    outtree_->Branch("jetGenJetPt", &jetGenJetPt_, "jetGenJetPt/F");
    outtree_->Branch("jetGenJetEta", &jetGenJetEta_, "jetGenJetEta/F");
    outtree_->Branch("jetGenJetPhi", &jetGenJetPhi_, "jetGenJetPhi/F");
    outtree_->Branch("jetGenJetY", &jetGenJetY_, "jetGenJetY/F");
    }

    if ( testJetSF )
    {
        outtree_->Branch("jetCSV2BJetTags",             &jetCSV2BJetTags_, 	      "jetCSV2BJetTags/F"); 	        
        outtree_->Branch("jetDeepCSVTags_b",            &jetDeepCSVTags_b_,         "jetDeepCSVTags_b/F");
        outtree_->Branch("jetDeepCSVTags_bb",           &jetDeepCSVTags_bb_,        "jetDeepCSVTags_bb/F");
        outtree_->Branch("jetDeepCSVTags_c",            &jetDeepCSVTags_c_,         "jetDeepCSVTags_c/F");
        outtree_->Branch("jetDeepCSVTags_udsg",         &jetDeepCSVTags_udsg_,      "jetDeepCSVTags_udsg/F");
        outtree_->Branch("jetDeepFlavourTags_b", &jetDeepFlavourTags_b_, "jetDeepFlavourTags_b");
        outtree_->Branch("jetDeepFlavourTags_c", &jetDeepFlavourTags_c_, "jetDeepFlavourTags_c");
        outtree_->Branch("jetDeepFlavourTags_g", &jetDeepFlavourTags_g_, "jetDeepFlavourTags_g");
        outtree_->Branch("jetDeepFlavourTags_lepb", &jetDeepFlavourTags_lepb_, "jetDeepFlavourTags_lepb");
        outtree_->Branch("jetDeepFlavourTags_bb", &jetDeepFlavourTags_bb_, "jetDeepFlavourTags_bb");
        outtree_->Branch("jetDeepFlavourTags_uds", &jetDeepFlavourTags_uds_, "jetDeepFlavourTags_uds");
        outtree_->Branch("jetDeepCSVDiscriminatorTags_BvsAll", &jetDeepCSVDiscriminatorTags_BvsAll_, "jetDeepCSVDiscriminatorTags_BvsAll");
        outtree_->Branch("jetDeepCSVDiscriminatorTags_CvsB", &jetDeepCSVDiscriminatorTags_CvsB_, "jetDeepCSVDiscriminatorTags_CvsB");
        outtree_->Branch("jetDeepCSVDiscriminatorTags_CvsL", &jetDeepCSVDiscriminatorTags_CvsL_, "jetDeepCSVDiscriminatorTags_CvsL");
    }

    //btagCalibs.RegBranch(outtree_);


    if ( data.HasMC() )
    {
        outtree_->Branch("jetPartonID", 	          &jetPartonID_, 	      	      "jetPartonID/I"); 	        
        outtree_->Branch("jetGenPartonID", 	          &jetGenPartonID_, 	      	      "jetGenPartonID/I"); 	        
        outtree_->Branch("jetHadFlvr",                  &jetHadFlvr_,                  "jetHadFlvr/I");
        outtree_->Branch("jetGenPartonMomID",           &jetGenPartonMomID_, 	   	      "jetGenPartonMomID/I"); 	        
        outtree_->Branch( "calib_scEtaWidth"  , &calib_scEtaWidth     , "calib_scEtaWidth/F"       );
        outtree_->Branch( "calib_r9Full5x5"   , &calib_r9Full5x5      , "calib_r9Full5x5/F"        );
        outtree_->Branch( "calib_s4"          , &calib_s4             , "calib_s4/F"               );
        outtree_->Branch( "calib_sieieFull5x5", &calib_sieieFull5x5   , "calib_sieieFull5x5/F"     );

        outtree_->Branch("nLHE"               , &nLHE                 , "nLHE/I"                   );
        outtree_->Branch("lhePID"             ,  lhePID               , "lhePID[nLHE]/I"           );
        outtree_->Branch("lheE"               ,  lheE                 , "lheE  [nLHE]/F"           );
        outtree_->Branch("lhePx"              ,  lhePx                , "lhePx [nLHE]/F"           );
        outtree_->Branch("lhePy"              ,  lhePy                , "lhePy [nLHE]/F"           );
        outtree_->Branch("lhePz"              ,  lhePz                , "lhePz [nLHE]/F"           );
    outtree_->Branch("xsweight",  &xsweight, "xsweight/F");
    outtree_->Branch( "genWeight", &mygenweight, "genWeight/F");
    //outtree_->Branch("photon_jetID", &photon_jetID_, "photon_jetID/I");
    }


    outtree_->Branch("jetID", &jetID, "jetID/I");
    // PUbit : 0 -- loose, 1 -- medium, 2 -- tight
    outtree_->Branch("jetPUIDbit", &jetPUIDbit, "jetPUIDbit/I");

    if (!data.HasMC() )
    {
    outtree_->Branch("SeedTime", &SeedTime_, "SeedTime/F");
    outtree_->Branch("SeedEnergy", &SeedEnergy_, "SeedEnergy/F");
    outtree_->Branch("MIPTotEnergy", &MIPTotEnergy_, "MIPTotEnergy/F");
    }


    //get weight for gjetpt15to6000
    //TH2F *h2_xsweight = new TH2F("h2_xsweight","xs weight",8000, 0, 8000, 400, -10, 10);

    // TH1F *h_xs_projX = new TH1F("h_xs_projX","proj X", 8000, 0., 8000);
    // TH1F *h_xs_projY = new TH1F("h_xs_projY","proj Y", 400, -10., 10);
    TH1F *hist_measured = new TH1F("hist_measure","measure", 100, 0., 1000);
    TH1F *hist_reco = new TH1F("hist_reco","reco", 100, 0., 1000);

    // // pileup reweighting for MC
    PUWeightCalculator puCalc;
    TGraph *tgr[8];
    if(data.HasMC())
    {
        //puCalc.Init( ExternalFilesMgr::RooFile_PileUp() );
        puCalc.Init( ExternalFilesMgr::RooFile_PileUp_Run2016_69200nb_Moriond17() );
        TFile* f = TFile::Open( ExternalFilesMgr::RooFile_ShowerShapeCorrection() );
        LOG_INFO("--- shower correction : legacy 2016 use (need to be changed) ---");

        tgr[0] = (TGraph*) f->Get("transfEtaWidthEB");
        tgr[1] = (TGraph*) f->Get("transfS4EB");
        tgr[2] = (TGraph*) f->Get("transffull5x5R9EB");
        tgr[3] = (TGraph*) f->Get("transffull5x5sieieEB");

        tgr[4] = (TGraph*) f->Get("transfEtaWidthEE");
        tgr[5] = (TGraph*) f->Get("transfS4EE");
        tgr[6] = (TGraph*) f->Get("transffull5x5R9EE");
        tgr[7] = (TGraph*) f->Get("transffull5x5sieieEE");
    }

    TFile* f_showershapecorrection;
    //PUWeightCalculator pucalc;
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

    //pucalc.Init( ExternalFilesMgr::RooFile_PileUp() );
    }


    LOG_INFO(" processing entries %lli \n", data.GetEntriesFast());


    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
        TLorentzVector phoP4, lepP4[2], zllP4, electronP4, wlnP4, nueP4, trigger_jetP4, jetP4;

        data.GetEntry(ev);
        if ( data.HasMC() )
        {
            overallGenweight += data.GetFloat("genWeight");
            if ( hasNon1Val < 0.1 )
                if ( data.GetFloat("genWeight") != 1. )
                    hasNon1Val = 1;
        }

        Int_t run_     = data.GetInt("run");
        Long64_t event_   = data.GetLong64("event");
        Int_t nVtx_    = data.GetInt("nVtx");

        Int_t    nPho     = data.GetInt("nPho");
        Int_t nJet = data.GetInt("nJet");
        h_nrecojet->Fill(nJet);	  
        if(nJet <1 ) continue;

        if(!data.HasMC())
        {
            Int_t hasGoodVtx = data.GetInt("nGoodVtx");
            if(hasGoodVtx) h_hasGoodVtx->Fill(1.1);
            else h_hasGoodVtx->Fill(0.1);
            if(!hasGoodVtx) continue;
            int metFilters_ = data.GetInt("metFilters");
            if(metFilters_ != 0 ) continue;
        }



        Float_t  pthat = 0;
        Int_t    nMC   = 0;     
        Int_t*   mcPID =0;    
        Int_t*   mcMomPID=0;  
        Int_t*   mcGMomPID=0; 
        Float_t* mcPt      =0;
        Float_t* mcEta     =0;
        Float_t* mcPhi     =0;
        Float_t* mcE       =0;
        Float_t* mcMomPt   =0;
        Float_t* mcMomEta   =0;
        Float_t* mcMomPhi   =0;
        Float_t genHT      =0;
        Int_t    nPUInfo =0;
        Int_t*   puBX=0; 
        Float_t* puTrue=0;
        Float_t* mcCalIsoDR04=0;
        Float_t* mcTrkIsoDR04=0;
        Short_t* mcStatus=0;

        Float_t* jetGenJetPt = 0;
        Float_t* jetGenJetEn = 0;
        Float_t* jetGenJetEta = 0;
        Float_t* jetGenJetPhi = 0;

        Float_t      genWeight =1.;
        int nPU_ = 0;
        if( data.HasMC()) { 
            pthat     = data.GetFloat("pthat");
            hpthat->Fill(pthat,xsweight);
            hpthat_wide->Fill(pthat,xsweight);

            nMC       = data.GetInt("nMC");
            mcPID     = data.GetPtrInt("mcPID");
            mcMomPID  = data.GetPtrInt("mcMomPID");
            mcGMomPID = data.GetPtrInt("mcGMomPID");
            mcPt      = data.GetPtrFloat("mcPt");
            mcEta     = data.GetPtrFloat("mcEta");
            mcPhi     = data.GetPtrFloat("mcPhi");
            mcE       = data.GetPtrFloat("mcE");
            mcMomPt   = data.GetPtrFloat("mcMomPt");
            mcMomEta   = data.GetPtrFloat("mcMomEta");
            mcMomPhi   = data.GetPtrFloat("mcMomPhi");
            mcStatus = data.GetPtrShort("mcStatusFlag");

            genHT = data.GetFloat("genHT");
            //MG HT cut on inclusive sample
            //if(genHTcut>0. && genHT<100.) continue;

            jetGenJetPt = data.GetPtrFloat("jetGenJetPt");
            jetGenJetEn = data.GetPtrFloat("jetGenJetEn");
            jetGenJetEta = data.GetPtrFloat("jetGenJetEta");
            jetGenJetPhi = data.GetPtrFloat("jetGenJetPhi");


            nPUInfo = data.GetInt("nPUInfo");
            puBX    = data.GetPtrInt("puBX");
            puTrue  = data.GetPtrFloat("puTrue");

            for (Int_t i=0; i<nPUInfo; ++i) {
                if (puBX[i] == 0) nPU_ = puTrue[i];
            }      
            mcCalIsoDR04 = data.GetPtrFloat("mcCalIsoDR04");
            mcTrkIsoDR04 = data.GetPtrFloat("mcTrkIsoDR04");
            puwei_ = (float) puCalc.GetWeight(run_, puTrue[1]); // in-time PU

            genWeight = data.GetFloat("genWeight");      
            if(genWeight>0.) xsweight=XS;
            else xsweight=XS*-1.;
            if(gjet15to6000==1) xsweight=genWeight;

            //if in MC selecton only one GenJet
            float ngenjet=0;
            for(int j=0; j<nJet; j++){		         
                if(jetGenJetPt[j] > 40 && TMath::Abs(jetGenJetEta[j])<2.4)
                    ngenjet++;
            }
            h_ngenjet->Fill(ngenjet);      


            int ngenpho=0;
            //Get gjet gen photon denominator
            for (Int_t k=0; k<nMC; ++k) {
                if (mcPID[k] == 22 &&  mcPt[k]>15. && TMath::Abs(mcMomPID[k]) <= 22) {
                    if(mcPt[k]>150.) hmcGenIso->Fill(mcCalIsoDR04[k]);

                    float GENISO=0.;
                    for (Int_t nn=0; nn<nMC; ++nn) {
                        if(nn == k ) continue;
                        if(fabs(mcPID[nn])>22 || mcStatus[nn]>3) continue;
                        float dr = usefulFuncs::deltaR(mcEta[k], mcPhi[k], mcEta[nn], mcPhi[nn]);
                        if( dr < 0.4) GENISO += mcPt[nn];
                    }
                    if(mcPt[k]>150.) hmcpartonIso->Fill(GENISO);

                    if(mcCalIsoDR04[k]<5.0 ){ //for gammajet photon 	    
                        ngenpho++;
                        hgenpho_eta_phi->Fill(mcEta[k], mcPhi[k]);
                        hgenpho_eta_pt->Fill(mcEta[k], mcPt[k]);
                        if(TMath::Abs(mcEta[k])<1.4442) {
                            hgenphoEB_pt->Fill(mcPt[k],xsweight*puwei_);
                            //hgenphoEB_pt_vbin->Fill(mcPt[k]);
                            hgenphoEB_pt_vbin->Fill(mcPt[k],xsweight*puwei_); //madgraph
                            hgenphoEB_eta->Fill(mcEta[k]);
                        }else if(TMath::Abs(mcEta[k])>1.566 && TMath::Abs(mcEta[k])<2.5) {
                            hgenphoEE_pt->Fill(mcPt[k],xsweight*puwei_);
                            //hgenphoEE_pt_vbin->Fill(mcPt[k]);
                            hgenphoEE_pt_vbin->Fill(mcPt[k],xsweight*puwei_); //madgraph
                            hgenphoEE_eta->Fill(mcEta[k]);
                        }

                        if(TMath::Abs(mcEta[k])<0.8) hgenphoEBEE0_pt_vbin->Fill(mcPt[k],xsweight*puwei_);
                        else if(TMath::Abs(mcEta[k])<1.4442) hgenphoEBEE1_pt_vbin->Fill(mcPt[k],xsweight*puwei_);
                        else if(TMath::Abs(mcEta[k])>1.566 && TMath::Abs(mcEta[k])<2.1) hgenphoEBEE2_pt_vbin->Fill(mcPt[k],xsweight*puwei_);
                        else if(TMath::Abs(mcEta[k])>1.566 && TMath::Abs(mcEta[k])<2.5) hgenphoEBEE3_pt_vbin->Fill(mcPt[k],xsweight*puwei_);

                        if(TMath::Abs(mcEta[k])<0.8) hgenphoEBEE0_pt_vbin->Fill(mcPt[k]);
                        else if(TMath::Abs(mcEta[k])<1.4442) hgenphoEBEE1_pt_vbin->Fill(mcPt[k]);
                        else if(TMath::Abs(mcEta[k])>1.566 && TMath::Abs(mcEta[k])<2.1) hgenphoEBEE2_pt_vbin->Fill(mcPt[k]);
                        else if(TMath::Abs(mcEta[k])>1.566 && TMath::Abs(mcEta[k])<2.5) hgenphoEBEE3_pt_vbin->Fill(mcPt[k]);

                        break;
                    }
                }
            }
            h_ngenpho->Fill(ngenpho);
        } // isdata end


        if(nPho==0) continue; //skip entry if no recoPhoton
        Float_t *jetSubVtxPt = nullptr;
        Float_t *jetSubVtxMass = nullptr;
        Float_t *jetSubVtx3DVal = nullptr;
        Float_t *jetSubVtx3DErr = nullptr;
        Int_t   *jetSubVtxNtrks = nullptr;
        //if ( hasSubVtxInfo )
        //{
            jetSubVtxPt    = data.GetPtrFloat("jetSecVtxPt"   );
            jetSubVtxMass  = data.GetPtrFloat("jetSecVtxMass" );
            jetSubVtx3DVal = data.GetPtrFloat("jetSecVtx3DVal");
            if ( data.GetTree()->GetListOfBranches()->FindObject("jetSecVtx3DErr") )
                jetSubVtx3DErr = data.GetPtrFloat("jetSecVtx3DErr");
            else if ( data.GetTree()->GetListOfBranches()->FindObject("jetSecVtx3DSig") )
                jetSubVtx3DErr = data.GetPtrFloat("jetSecVtx3DSig");
            else
                LOG_FATAL("neigher 3DErr nor 3DSig not found in data, check it now!");
            jetSubVtxNtrks = data.GetPtrInt  ("jetSecVtxNtrks");
        //}

        Float_t pfMET = data.GetFloat("pfMET");
        Float_t pfMETPhi = data.GetFloat("pfMETPhi");
        Int_t    nEle     = data.GetInt("nEle");

        Float_t* jetPt = data.GetPtrFloat("jetPt");
        Float_t* jetEn = data.GetPtrFloat("jetEn");
        Float_t* jetEta = data.GetPtrFloat("jetEta");
        Float_t* jetPhi = data.GetPtrFloat("jetPhi");
        Long64_t*   jetFiredTrgs = data.GetPtrLong64("jetFiredTrgs");      

        vector<bool> &jetId             = *((vector<bool>*) data.GetPtr("jetPFLooseId"));
        Float_t *jetJECUnc = data.GetPtrFloat("jetJECUnc");
        Float_t* jetNHF = data.GetPtrFloat("jetNHF");
        Float_t* jetNEF = data.GetPtrFloat("jetNEF");

        Float_t *jetCSV2BJetTags = nullptr;
        Float_t *jetDeepCSVTags_b = nullptr;
        Float_t *jetDeepCSVTags_bb = nullptr;
        Float_t *jetDeepCSVTags_c = nullptr;
        Float_t *jetDeepCSVTags_udsg = nullptr;
        Float_t *jetDeepFlavourTags_b = nullptr;
        Float_t *jetDeepFlavourTags_c = nullptr;
        Float_t *jetDeepFlavourTags_g = nullptr;
        Float_t *jetDeepFlavourTags_lepb = nullptr;
        Float_t *jetDeepFlavourTags_bb = nullptr;
        Float_t *jetDeepFlavourTags_uds = nullptr;
        Float_t *jetDeepCSVDiscriminatorTags_BvsAll = nullptr;
        Float_t *jetDeepCSVDiscriminatorTags_CvsB = nullptr;
        Float_t *jetDeepCSVDiscriminatorTags_CvsL = nullptr;

        if ( testJetSF )
        {
            jetCSV2BJetTags = data.GetPtrFloat("jetCSV2BJetTags");
            jetDeepCSVTags_b = data.GetPtrFloat("jetDeepCSVTags_b");
            jetDeepCSVTags_bb = data.GetPtrFloat("jetDeepCSVTags_bb");
            jetDeepCSVTags_c = data.GetPtrFloat("jetDeepCSVTags_c");
            jetDeepCSVTags_udsg = data.GetPtrFloat("jetDeepCSVTags_udsg");
            jetDeepFlavourTags_b = data.GetPtrFloat("jetDeepFlavourTags_b");
            jetDeepFlavourTags_c = data.GetPtrFloat("jetDeepFlavourTags_c");
            jetDeepFlavourTags_g = data.GetPtrFloat("jetDeepFlavourTags_g");
            jetDeepFlavourTags_lepb = data.GetPtrFloat("jetDeepFlavourTags_lepb");
            jetDeepFlavourTags_bb = data.GetPtrFloat("jetDeepFlavourTags_bb");
            jetDeepFlavourTags_uds = data.GetPtrFloat("jetDeepFlavourTags_uds");
            jetDeepCSVDiscriminatorTags_BvsAll = data.GetPtrFloat("jetDeepCSVDiscriminatorTags_BvsAll");
            jetDeepCSVDiscriminatorTags_CvsB = data.GetPtrFloat("jetDeepCSVDiscriminatorTags_CvsB");
            jetDeepCSVDiscriminatorTags_CvsL = data.GetPtrFloat("jetDeepCSVDiscriminatorTags_CvsL");
        }


        Int_t *jetPartonID = nullptr;
        Int_t *jetGenPartonID = nullptr;
        Int_t *jetHadFlvr = nullptr;
        Int_t *jetGenPartonMomID = nullptr;

        if ( data.HasMC() )
        {
            jetPartonID = data.GetPtrInt("jetPartonID");
            jetGenPartonID = data.GetPtrInt("jetGenPartonID");
            jetHadFlvr = data.GetPtrInt("jetHadFlvr");
            jetGenPartonMomID = data.GetPtrInt("jetGenPartonMomID");
        }

        // Float_t* phoE   = data.GetPtrFloat("phoE");
        Float_t* phoEta   = data.GetPtrFloat("phoEta");
        Float_t* phoPhi   = data.GetPtrFloat("phoPhi");
        Float_t* phoEtCalib    = data.GetPtrFloat("phoCalibEt");
        Float_t* phoEt    = data.GetPtrFloat("phoEt");
        Float_t* phoR9    = data.GetPtrFloat("phoR9");
        Float_t* phoSCEta = data.GetPtrFloat("phoSCEta");
        // Float_t* phoSCPhi = data.GetPtrFloat("phoSCPhi");

        Int_t*   phoEleVeto          = data.GetPtrInt("phoEleVeto");
        Float_t* phoHoverE           = data.GetPtrFloat("phoHoverE");
        Float_t* phoPFChIso          = data.GetPtrFloat("phoPFChIso");
        Float_t* phoPFNeuIso         = data.GetPtrFloat("phoPFNeuIso");
        Float_t* phoPFPhoIso         = data.GetPtrFloat("phoPFPhoIso");
        Int_t* phohasPixelSeed     = data.GetPtrInt("phohasPixelSeed");

        Float_t rho_                = data.GetFloat("rho"); //kk

        Float_t* phoSCRawE         = data.GetPtrFloat("phoSCRawE");
        Float_t* phoSCEtaWidth     = data.GetPtrFloat("phoSCEtaWidth");
        Float_t* phoSCPhiWidth     = data.GetPtrFloat("phoSCPhiWidth");
        Float_t* phoESEnP1           = data.GetPtrFloat("phoESEnP1");
        Float_t* phoESEnP2           = data.GetPtrFloat("phoESEnP2");
        Float_t* phoESEffSigmaRR   = data.GetPtrFloat("phoESEffSigmaRR");
        Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso");

        Float_t* phoSigmaIEtaIEtaFull5x5  = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
        Float_t* phoSigmaIEtaIPhiFull5x5  = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
        Float_t* phoSigmaIPhiIPhiFull5x5  = data.GetPtrFloat("phoSigmaIPhiIPhiFull5x5");
        Float_t* phoR9Full5x5           = data.GetPtrFloat("phoR9Full5x5");
        Float_t* phoE2x2Full5x5            = data.GetPtrFloat("phoE2x2Full5x5");
        Float_t* phoE5x5Full5x5            = data.GetPtrFloat("phoE5x5Full5x5");
        Float_t* phoIDMVA = data.GetPtrFloat("phoIDMVA");

        Long64_t* phoFiredTrgs = data.GetPtrLong64("phoFiredSingleTrgs");
        Short_t* phoIDbit = data.GetPtrShort("phoIDbit");

        Float_t * phoSeedTime = 0;
        Float_t * phoSeedEnergy = 0;
        Float_t * phoMIPTotEnergy= 0;
        if(!data.HasMC()) { 
            phoSeedTime = data.GetPtrFloat("phoSeedTime");
            phoSeedEnergy = data.GetPtrFloat("phoSeedEnergy");
            phoMIPTotEnergy = data.GetPtrFloat("phoMIPTotEnergy");
        }


        std::map<int,int> match;
        std::map<int,int> converted;
        std::map<int,int> match_ele;
        std::map<int,float> mcpt;
        std::map<int,float> mceta;
        std::map<int,float> mcphi;
        std::map<int,float> mcCalIso04;
        std::map<int,float> mcTrkIso04;

        mcpt.clear();
        mceta.clear();
        mcphi.clear();

        //h_npho->Fill(nPho);
        int nmatch=0;
        int nmatch_EB=0;
        int nmatch_EE=0;
        int nconv=0;

        if(verbose) {
            LOG_DEBUG("-----------------------------------------------------------------------\n");
            LOG_DEBUG("event %lli, npho %d, nMC %d\n", event_, nPho, nMC);
        }

        //count number of true photon
        int ntruephoton=0;

        if( data.HasMC()) { 
            vector<int> mcid;
            int nnMC=0;
            for (Int_t k=0; k<nMC; ++k) {
                if (mcPID[k] == 22 &&  mcPt[k]>15. && (mcMomPID[k] <= 22 || mcMomPID[k] == 5100039)) {
                    if(verbose) LOG_DEBUG("   true photon in generator pt %.2f, eta %.2f, phi %.2f \n", mcPt[k], mcEta[k], mcPhi[k]);
                    mcid.push_back(k);
                    nnMC++;
                }
            }
            vector<int> muonmcid;
            int nnmuonMC=0;
            for (Int_t k=0; k<nMC; ++k) {
                if (fabs(mcPID[k])==13 && mcPt[k]>20.){
                    muonmcid.push_back(k);
                    nnmuonMC++;
                }
            }
            vector<int> elemcid;
            int nneleMC=0;
            for (Int_t k=0; k<nMC; ++k) {
                if (fabs(mcPID[k]) == 11 ){
                    elemcid.push_back(k);
                    nneleMC++;
                }
            }


            h_truepho->Fill(nnMC+0.001);
            h_convpho->Fill(nneleMC/2. + 0.001);
            ntruephoton= nnMC + nneleMC/2.;


            for (Int_t i=0; i<nPho; ++i) {
                if(phoEt[i]<15.) continue;
                int tmp_isMatched = -99;
                int tmp_isMatchedEle = -99;
                int tmp_isConverted = -99;

                double tmp_mcPt_ = -999.;
                double tmp_mcEta_ = -999.;
                double tmp_mcPhi_ = -999.;
                double tmp_mcCalIso04_ = -999.;
                double tmp_mcTrkIso04_ = -999.;
 
                if(verbose) LOG_DEBUG("pho Et %.2f, eta %.2f, phi %.2f ,CSEV %d \n", phoEt[i], phoEta[i], phoPhi[i], phoEleVeto[i]);
                for (int jj=0; jj<nnMC; ++jj) {
                    int k = mcid[jj];
                    float dr = usefulFuncs::deltaR(phoEta[i], phoPhi[i], mcEta[k], mcPhi[k]);
                    float dpt = fabs((phoEt[i] - mcPt[k])/mcPt[k]);
                    if(dpt<0.2)hdR->Fill(dr);
                    if(dr<0.2)hdpt->Fill(dpt);
                    hmcCalIso->Fill(mcCalIsoDR04[k]); 

                    if(verbose) LOG_DEBUG("  MCparticle %d, dr %.2f, dpt %.2f \n", k, dr, dpt);
                    if(verbose) LOG_DEBUG("     status %d, caliso %.2f, trkiso %.2f \n", mcStatus[k], mcCalIsoDR04[k], mcTrkIsoDR04[k]);
                    if (dr < 0.2 && dpt < 0.2){
                        float GENISO=0.;
                        for (Int_t nn=0; nn<nMC; ++nn) {
                            if(nn == k ) continue;
                            if(fabs(mcPID[nn])>22 || mcStatus[nn]>3) continue;	      
                            float dr = usefulFuncs::deltaR(mcEta[k], mcPhi[k], mcEta[nn], mcPhi[nn]);
                            if( dr < 0.4) GENISO += mcPt[nn];
                        }
                        if(dr < 0.2 && dpt < 0.2 && mcCalIsoDR04[k]<5.0 ){ //for gammajet photon pythia	      
                            tmp_isMatched = 1;
                            tmp_mcPt_  = mcPt[k];
                            tmp_mcEta_ = mcEta[k];
                            tmp_mcPhi_ = mcPhi[k];
                            tmp_mcCalIso04_ = mcCalIsoDR04[k];
                            tmp_mcTrkIso04_ = mcTrkIsoDR04[k];
                            if(verbose) LOG_DEBUG("  mc matched !!! \n");	    
                            break;
                        }

                    }
                }

                for (int jj=0; jj<nneleMC; ++jj) {	   
                    int k = elemcid[jj];	  
                    if(fabs(mcPID[k]) == 11){
                        if (usefulFuncs::deltaR(phoEta[i], phoPhi[i], mcEta[k], mcPhi[k]) < 0.2) {
                            if (fabs((phoEt[i] -mcPt[k])/mcPt[k]) < 0.2) {
                                tmp_isMatchedEle = 1;
                            }
                        }
                    }
                    if (fabs(mcPID[k]) == 11 && mcMomPID[k] == 22) {	    
                        float dr = usefulFuncs::deltaR(phoEta[i], phoPhi[i], mcEta[k], mcPhi[k]);
                        float dpt = fabs((phoEt[i] - mcMomPt[k])/mcMomPt[k]);
                        hdR_ele->Fill(dr);
                        hdpt_ele->Fill(dpt);
                        if (dr < 0.2 && dpt < 0.2 && (mcCalIsoDR04[k]+mcTrkIsoDR04[k])<5.0 ){
                            tmp_isConverted = 1;
                            tmp_mcPt_  = mcMomPt[k];
                            tmp_mcEta_ = mcMomEta[k];
                            tmp_mcPhi_ = mcMomPhi[k];	      
                            tmp_mcCalIso04_ = mcCalIsoDR04[k];
                            tmp_mcTrkIso04_ = mcTrkIsoDR04[k];
                        }
                    }
                }
                if(tmp_isMatched==1) {
                    nmatch++;
                    if(TMath::Abs(phoSCEta[i])<=1.4442) nmatch_EB++;
                    if(TMath::Abs(phoSCEta[i])>=1.566 && TMath::Abs(phoSCEta[i])<2.5) nmatch_EE++;
                }else{
                    if(tmp_isConverted==1){
                        nconv++;
                        //LOG_DEBUG(" event %d, photon Et %.2f,  tmp_isConverted \n", event, phoEt[i]);
                    }
                }


                mcpt[i]=tmp_mcPt_;
                mceta[i]=tmp_mcEta_;
                mcphi[i]=tmp_mcPhi_;
                mcCalIso04[i]=tmp_mcCalIso04_;
                mcTrkIso04[i]=tmp_mcTrkIso04_;
                match[i]=tmp_isMatched;
                match_ele[i]=tmp_isMatchedEle;
                converted[i]=tmp_isConverted;
            }

            if(gjet15to6000 == 0) {
                h_truepho->Fill(nmatch+0.001);
                h_convpho->Fill(nconv+0.001);
            }
        }


        int npj=0;
        int npp=0;
        tp_rho->Fill(nVtx_, rho_, xsweight);
        h2_nVtx_rho->Fill(nVtx_,rho_,xsweight);
        if( data.HasMC()) { 
            if(nmatch_EB==1 && nmatch_EE==0) tp_rho_EB->Fill(nVtx_, rho_, xsweight);
            if(nmatch_EB==0 && nmatch_EE==1) tp_rho_EE->Fill(nVtx_, rho_, xsweight);
        }
        int nphofiredtrgs=0;
        //look for 2nd photon back of HLT matched photon

        float* elePt  = data.GetPtrFloat("elePt");
        float* eleEta = data.GetPtrFloat("eleEta");
        float* elePhi = data.GetPtrFloat("elePhi");    


        h_MET->Fill(pfMET);


        vector <int> photon_list;
        //vector <int> photon_jetID;
        int jet_index=-1;


        //JETPD find leading jets fired trigger
        if(JETPD_PHOTONHLT==1) {
            for(int ijet=0; ijet<nJet; ijet++) {
                if(jetFiredTrgs!=0){
                    trigger_jetP4.SetPtEtaPhiE(jetPt[ijet], jetEta[ijet], jetPhi[ijet], jetEn[ijet]);
                    jet_index= ijet;
                    break;
                }
            }
        }
        //int nnjet=0;
        //int jet2_index=-1;
        if(!data.HasMC()) { 
            for (Int_t i=0; i<nPho; ++i) {  
                if(JETPD_PHOTONHLT==0 && phoFiredTrgs[i]==0) continue;
                if(PhotonPreselection(data, i, kFALSE) !=1) continue;

                for (Int_t j=i+1; j<nPho; ++j) {  
                    if(PhotonPreselection(data, j, kFALSE) !=1) continue;	  
                    TLorentzVector iphoP4, jphoP4;
                    iphoP4.SetPtEtaPhiM(phoEt[i], phoEta[i], phoPhi[i], 0.);	  
                    jphoP4.SetPtEtaPhiM(phoEt[j], phoEta[j], phoPhi[j], 0.);
                    TLorentzVector ppP4;
                    ppP4 = iphoP4;	  ppP4 += jphoP4;
                    h_ppmass->Fill(ppP4.M());
                    h_ppmass_zoom->Fill(ppP4.M());
                }
            }
        }


        for (Int_t i=0; i<nPho; ++i) {      
            if(phoEt[i]<15.) continue;       
            //if(phoEt[i]<100.) continue;
            if(TMath::Abs(phoSCEta[i])>1.4442 && TMath::Abs(phoSCEta[i])<1.566) continue;
            if(TMath::Abs(phoSCEta[i])>2.5) continue;
            if(!data.HasMC() && JETPD_PHOTONHLT==0 && phoFiredTrgs==0) continue;
            if(!data.HasMC() && JETPD_PHOTONHLT==0 ){
                if(phoFiredTrgs[i]==0) continue;
                if ( USEHLT )
                {
                    // in 2016 HLT Table
                    if((phoFiredTrgs[i]>>7)&1) nphofiredtrgs++; //HLT175  asdf note this trigger bit need to be modified once you have a newer ggAnalysis version.
                    //if(((phoFiredTrgs[i]>>4)&1)==1) nphofiredtrgs++; //HLT120
                    else 
                        continue;       
                }
            }

            phoP4.SetPtEtaPhiM(phoEt[i], phoEta[i], phoPhi[i], 0.);
            int pho_presel = 0;
            pho_presel = PhotonPreselection(data, i, kTRUE);
            //check CSEV eff vs pt
            if( data.HasMC()) { 
                if(i==0 && match[i]==1){

                    if(TMath::Abs(phoSCEta[i])<1.5) hphoEB_pt_presel_den->Fill(phoEt[i]);
                    else hphoEE_pt_presel_den->Fill(phoEt[i]);	
                    if(pho_presel == 1){
                        if(TMath::Abs(phoSCEta[i])<1.5) {
                            if(phoPFChIso[i]<2.) hphoEB_pt_presel_num->Fill(phoEt[i]);
                        }else {
                            if(phoPFChIso[i]<1.5) hphoEE_pt_presel_num->Fill(phoEt[i]);
                        }
                    }

                    if( PhotonPreselection(data, i, kFALSE) ==1){
                        if(TMath::Abs(phoSCEta[i])<1.5) hphoEB_pt_presel_nocsev->Fill(phoEt[i]);
                        else hphoEE_pt_presel_nocsev->Fill(phoEt[i]);

                        if(pho_presel == 1){
                            if(TMath::Abs(phoSCEta[i])<1.5) {
                                hphoEB_pt_presel_csev->Fill(phoEt[i]);
                            }else {
                                hphoEE_pt_presel_csev->Fill(phoEt[i]);
                            }
                        }
                    }
                }
            }



            if(pho_presel!=1) continue;
            if(JETPD_PHOTONHLT==1 && phoP4.DeltaR(trigger_jetP4)<0.7) continue;
            photon_list.push_back(i); 
            if(ONLY_LEADINGPHOTON==1 && photon_list.size()==1) break;


        }
        h_npho->Fill(photon_list.size());
        if(photon_list.size() < 1) continue;


        // find photon overlaps to electron
        TLorentzVector leadingPhoP4;
        leadingPhoP4.SetPtEtaPhiM(phoEt[photon_list[0]], phoEta[photon_list[0]], phoPhi[photon_list[0]], 0.);
        if ( ELECTRONVETO ) {
            vector<int> eleID;
            ElectronIDCutBased2015(data, 3, eleID); //0 veto, 1 loose, 2 medium, 3 tight  //asdf
            h_nele->Fill(eleID.size());
            for(unsigned int j=0; j<eleID.size(); j++){
                if(elePt[eleID[j]]<100) continue;
                TLorentzVector tmp_eP4;
                tmp_eP4.SetPtEtaPhiM(elePt[eleID[j]], eleEta[eleID[j]], elePhi[eleID[j]],  0.511*0.001);
                h_dR_phoele->Fill(leadingPhoP4.DeltaR(tmp_eP4));
                if(leadingPhoP4.DeltaR(tmp_eP4) < 0.3) {
                    photon_list.clear(); 
                }
            }
        }

        //find one jet in event
        for(int j=0; j<nJet; j++){
            float jetjecunc = 1.;
            if(TMath::Abs(jetEta[j])<2.4 && jetPt[j]*jetjecunc>30.) {
                if( jetId[j] ) h_jetIDv->Fill(1.);	else h_jetIDv->Fill(0.);       
                jetP4.SetPtEtaPhiE(jetPt[j]*jetjecunc, jetEta[j], jetPhi[j], jetEn[j]);


                if( jetId[j] ) {	  
                    h_dR_phojet->Fill(leadingPhoP4.DeltaR(jetP4));
                    if(leadingPhoP4.DeltaR(jetP4)>0.4){
                        if(jet_index<0) jet_index = j;
                        else LOG_DEBUG("more than 1 jet pass the selection. Please check!\n");
                        //nnjet++;
                        //if(nnjet==2) jet2_index = j;
                    }	    
                }    
            }  
        }







        //for (Int_t ii=0; ii< (int)photon_list.size(); ii++) {            
        for (Int_t ipho : photon_list ) {
            nPU=0; //ch
            HLT                = 0;
            HLTIsPrescaled     = 0;
            metFilters=0;
            isData = false;
            phoFiredTrgs_ = 0; //ch
            jetGenJetPt_ = 0.; //ch
            jetGenJetEta_ = 0.; //ch
            jetGenJetPhi_ = 0.; //ch
            jetGenJetY_ = 0.; //ch
            jetGenPartonID_ = 0; //ch

            jetPt_=0.; //ch
            jetEta_=0.; //ch
            jetPhi_=0.; //ch
            jetY_=0.; //ch
            jetJECUnc_=0.; //ch
            jetGenJetPt_ = 0.;
            jetGenJetEta_ = 0.;
            jetGenPartonMomID_ = 0; //ch
            jetPartonID_= jetHadFlvr_ = 0.; //ch
            isMatched = -99; //need
            isMatchedEle = -99; //need
            isConverted = -99; //need
            mva = -99.; //ch
            mva_nocorr = -99.; //ch
            genHT_ = 0.; //ch
            pthat_      = 0.; //ch
            mcPt_       = 0.;
            mcEta_      = 0.;
            mcPhi_      = 0.;
            mcCalIso04_ = 0.;
            mcTrkIso04_ = 0.;
            jetSubVtxPt_    = 0.;
            jetSubVtxMass_  = 0.;
            jetSubVtx3DVal_ = 0.;
            jetSubVtx3DErr_ = 0.;
            jetSubVtxNtrks_ = 0.;
            jetCSV2BJetTags_ = 0.; //ch
            jetDeepCSVTags_b_ = 0.; //ch
            jetDeepCSVTags_bb_ = 0.; //ch
            jetDeepCSVTags_c_ = 0.; //ch
            jetDeepCSVTags_udsg_ = 0.; //ch
            jetDeepFlavourTags_b_ = 0.;
            jetDeepFlavourTags_c_ = 0.;
            jetDeepFlavourTags_g_ = 0.;
            jetDeepFlavourTags_lepb_ = 0.;
            jetDeepFlavourTags_bb_ = 0.;
            jetDeepFlavourTags_uds_ = 0.;
            jetDeepCSVDiscriminatorTags_BvsAll_ = 0.;
            jetDeepCSVDiscriminatorTags_CvsB_ = 0.;
            jetDeepCSVDiscriminatorTags_CvsL_ = 0.;
            SeedTime_=0; //ch
            SeedEnergy_=0; //ch
            MIPTotEnergy_=0; //ch
            recoPt    =0.;          //ch
            recoPtCalib    =0.;          //ch
            recoEta   =0.;          //ch
            recoPhi   =0.;          //ch
            recoSCEta =0.;          //ch
            r9        =0.;          //ch
            eleVeto   =0.;          //ch
            HoverE    =0.;          //ch

            phohasPixelSeed_ =0.;    //ch
            chIsoRaw   =0.;         //ch
            phoIsoRaw  =0.;         //ch
            nhIsoRaw   =0.;         //ch


            rawE       =0.;          //ch
            scEtaWidth =0.;          //ch
            scPhiWidth =0.;          //ch
            esRR       =0.;          //ch
            esEn       =0.;          //ch
            chWorstIso =0.;         //ch

            sieieFull5x5     =0.;    //ch
            sieipFull5x5     =0.;    //ch
            sipipFull5x5     =0.;    //ch
            r9Full5x5        =0.;    //ch
            e2x2Full5x5       =0.;   //ch
            e5x5Full5x5       =0.;   //ch
            photon_jetID_ =0.;       //ch

            phoIDbit_ =0.;           //ch
            photonIDmva = -999.; //ch
            s4=0.;
            calib_s4=calib_r9Full5x5=calib_scEtaWidth=calib_sieieFull5x5 = 0.;
            mygenweight = 0;
            for ( unsigned i=0; i<MAX_LHEPARTICLE; ++i )
                lhePID[i] = lheE[i]   = lhePx[i]  = lhePy[i]  = lhePz[i]  = 0;
            jetID = 0;
            jetPUIDbit = 0;
            //btagCalibs.InitVars();
            rho = data.GetFloat("rho"); //kk
            MET = pfMET;
            METPhi = pfMETPhi;
            nPU=nPU_;
            run     = data.GetInt("run");
            event   = data.GetLong64("event");
            isData  = data.GetBool("isData");
            nVtx    = data.GetInt("nVtx");
            mygenweight = data.HasMC() ? data.GetFloat("genWeight") : 1;

            //int ipho = photon_list[ii];
            phoFiredTrgs_ = phoFiredTrgs[ipho];
            phoP4.SetPtEtaPhiM(phoEt[ipho], phoEta[ipho], phoPhi[ipho], 0.);
            if(jet_index>=0) {
                jetP4.SetPtEtaPhiE(jetPt[jet_index], jetEta[jet_index], jetPhi[jet_index], jetEn[jet_index]);

                jetPt_ = jetPt[jet_index];
                jetEta_ = jetEta[jet_index];
                jetPhi_ = jetPhi[jet_index];
                jetY_ = jetP4.Rapidity();
                jetJECUnc_ = jetJECUnc[jet_index];
                if ( testJetSF )
                {
                    jetCSV2BJetTags_ = jetCSV2BJetTags[jet_index];
                    jetDeepCSVTags_b_ = jetDeepCSVTags_b[jet_index];
                    jetDeepCSVTags_bb_ = jetDeepCSVTags_bb[jet_index];
                    jetDeepCSVTags_c_ = jetDeepCSVTags_c[jet_index];
                    jetDeepCSVTags_udsg_ = jetDeepCSVTags_udsg[jet_index];
                    jetDeepFlavourTags_b_ = jetDeepFlavourTags_b[jet_index];
                    jetDeepFlavourTags_c_ = jetDeepFlavourTags_c[jet_index];
                    jetDeepFlavourTags_g_ = jetDeepFlavourTags_g[jet_index];
                    jetDeepFlavourTags_lepb_ = jetDeepFlavourTags_lepb[jet_index];
                    jetDeepFlavourTags_bb_ = jetDeepFlavourTags_bb[jet_index];
                    jetDeepFlavourTags_uds_ = jetDeepFlavourTags_uds[jet_index];
                    jetDeepCSVDiscriminatorTags_BvsAll_ = jetDeepCSVDiscriminatorTags_BvsAll[jet_index];
                    jetDeepCSVDiscriminatorTags_CvsB_ = jetDeepCSVDiscriminatorTags_CvsB[jet_index];
                    jetDeepCSVDiscriminatorTags_CvsL_ = jetDeepCSVDiscriminatorTags_CvsL[jet_index];
                }
                jetID = JetIDMgr::IDPassed(&data, jet_index, JetIDMgr::JetIDCuts_ULRun2016_CHS) ? 1 : 0;
                if ( JetIDMgr::PUIDPassed(&data, jet_index, JetIDMgr::PUJetIDCuts_ULRun2016_CHS_Loose ) )
                    jetPUIDbit += 1<<0;
                if ( JetIDMgr::PUIDPassed(&data, jet_index, JetIDMgr::PUJetIDCuts_ULRun2016_CHS_Medium) )
                    jetPUIDbit += 1<<1;
                if ( JetIDMgr::PUIDPassed(&data, jet_index, JetIDMgr::PUJetIDCuts_ULRun2016_CHS_Tight ) )
                    jetPUIDbit += 1<<2;


                if( data.HasMC() ) {
                    TLorentzVector jetGenJetP4;
                    jetGenJetP4.SetPtEtaPhiE(jetGenJetPt[jet_index], jetGenJetEta[jet_index], jetGenJetPhi[jet_index], jetGenJetEn[jet_index]);   
                    jetGenJetPt_ = jetGenJetPt[jet_index];
                    jetGenJetEta_ = jetGenJetEta[jet_index];
                    jetGenJetPhi_ = jetGenJetPhi[jet_index];
                    jetGenJetY_ = jetGenJetP4.Rapidity();
                    jetGenPartonID_ = jetGenPartonID[jet_index];		
                    jetGenPartonMomID_ = jetGenPartonMomID[jet_index];
                    jetPartonID_ = jetPartonID[jet_index];
                    jetHadFlvr_ = jetHadFlvr[jet_index];
                    h2_mcPID_mcPt->Fill( jetGenJetPt_, jetGenPartonID_+0.01, xsweight);


                }

                //if (hasSubVtxInfo) {
                    jetSubVtxPt_    = jetSubVtxPt   [jet_index];
                    jetSubVtxMass_  = jetSubVtxMass [jet_index];
                    jetSubVtx3DVal_ = jetSubVtx3DVal[jet_index];
                    jetSubVtx3DErr_ = jetSubVtx3DErr[jet_index];
                    jetSubVtxNtrks_ = jetSubVtxNtrks[jet_index];
                    h_subVtxPt   ->Fill(jetSubVtxPt_   );
                    h_subVtxMass ->Fill(jetSubVtxMass_ );
                    h_subVtx3DVal->Fill(jetSubVtx3DVal_);
                    h_subVtx3DErr->Fill(jetSubVtx3DErr_);
                    h_subVtxNtrks->Fill(jetSubVtxNtrks_);
                //}

                //btagCalibs.FillWeightToEvt(jetPt_,jetEta_);

            } // has jet end




            if ( data.HasMC() )
            {
                isMatched = match[ipho];
                isMatchedEle = match_ele[ipho];
                isConverted = converted[ipho];

                pthat_    = pthat;
                mcPt_     = mcpt[ipho];
                mcEta_    = mceta[ipho];
                mcPhi_    = mcphi[ipho];
                mcCalIso04_ = mcCalIso04[ipho];
                mcTrkIso04_ = mcTrkIso04[ipho];
                genHT_ = genHT;
                
                nLHE   = data.GetInt("nLHE");
                for ( int i=0; i<nLHE; ++i )
                {
                    lhePID[i] = data.GetPtrInt  ("lhePID")[i];
                    lheE[i]   = data.GetPtrFloat("lheE")[i];
                    lhePx[i]  = data.GetPtrFloat("lhePx")[i];
                    lhePy[i]  = data.GetPtrFloat("lhePy")[i];
                    lhePz[i]  = data.GetPtrFloat("lhePz")[i];
                    histMap["lheEnergy"]->Fill(lheE[i]);
                }

                h2_mcPID_mcPt->Fill( mcPt_, 22.01, xsweight);
            }
            if (!data.HasMC() ) {
                SeedTime_ = phoSeedTime[ipho];
                SeedEnergy_ = phoSeedEnergy[ipho];
                MIPTotEnergy_ = phoMIPTotEnergy[ipho];
                HLT = data.GetLong64("HLTPho");
                HLTIsPrescaled  = data.GetLong64("HLTPhoIsPrescaled");
                metFilters = data.GetInt("metFilters");
            }



            recoPt    = phoEt[ipho];
            recoPtCalib    = phoEtCalib[ipho];
            recoEta   = phoEta[ipho];
            recoPhi   = phoPhi[ipho];
            recoSCEta = phoSCEta[ipho];
            r9        = phoR9[ipho];
            eleVeto   = phoEleVeto[ipho];
            HoverE    = phoHoverE[ipho];

            phohasPixelSeed_ = phohasPixelSeed[ipho];
            chIsoRaw   = phoPFChIso[ipho];
            phoIsoRaw  = phoPFPhoIso[ipho];
            nhIsoRaw   = phoPFNeuIso[ipho];


            rawE       = phoSCRawE[ipho];
            scEtaWidth = phoSCEtaWidth[ipho];
            scPhiWidth = phoSCPhiWidth[ipho];
            esRR       = phoESEffSigmaRR[ipho];
            esEn       = phoESEnP1[ipho] +phoESEnP2[ipho];
            chWorstIso = phoPFChWorstIso[ipho];

            sieieFull5x5     = phoSigmaIEtaIEtaFull5x5[ipho];
            sieipFull5x5     = phoSigmaIEtaIPhiFull5x5[ipho];
            sipipFull5x5     = phoSigmaIPhiIPhiFull5x5[ipho];
            r9Full5x5        = phoR9Full5x5[ipho];
            e2x2Full5x5       = phoE2x2Full5x5[ipho];
            e5x5Full5x5       = phoE5x5Full5x5[ipho];
            s4 = e2x2Full5x5 / e5x5Full5x5;

            phoIDbit_ = phoIDbit[ipho];
            if ( data.HasMC() )
            {
                    std::map<std::string, TGraph*>* corrections = recoInfo::IsEE(recoSCEta) ? &endcapCorrections : &barrelCorrections;
                    calib_s4            = recoInfo::CorrectedValue( corrections->at("s4")          , s4 );
                    calib_r9Full5x5     = recoInfo::CorrectedValue( corrections->at("r9Full5x5")   , r9Full5x5 );
                    calib_scEtaWidth    = recoInfo::CorrectedValue( corrections->at("scEtaWidth")  , scEtaWidth );
                    calib_sieieFull5x5  = recoInfo::CorrectedValue( corrections->at("sieieFull5x5"), sieieFull5x5 );
                    LOG_DEBUG("calibrated s4 %.6f and r9 %.6f", calib_s4, calib_r9Full5x5);
            }



            mva = select_photon_mvanoIso(data, ipho, tgr);
            mva_nocorr = select_photon_mvanoIso(data, ipho, nullptr);
            photonIDmva = phoIDMVA[ipho];

            h2_mcPID_mcPt->Fill( jetPt_, 9.01, xsweight);
            h2_mcPID_mcPt->Fill( phoEt[ipho], 10.09, xsweight);

            if(isMatched==1){
                if(TMath::Abs(phoEta[ipho])<1.5) h_EB_bdt->Fill(mva);
                else h_EE_bdt->Fill(mva);
            }




            if(MINITREE==1 ) 	{
                outtree_->Fill();
                if ( ONLY_LEADINGPHOTON ) break;
            }

        } // fill tree end

        h_nphoFiredTrgs->Fill(nphofiredtrgs);

    } // event loop end

    fout_->cd();
    outtree_->Write();

    if ( data.HasMC() )
    {
    	nt_sumupgenweight->Fill(overallGenweight,hasNon1Val);
    	nt_sumupgenweight->Write();
    }

    h_subVtxPt   ->Write();
    h_subVtxMass ->Write();
    h_subVtx3DVal->Write();
    h_subVtx3DErr->Write();
    h_subVtxNtrks->Write();

    h_hasGoodVtx->Write();
    hpthat->Write();
    hpthat_wide->Write();

    hdR->Write();
    hdpt->Write();
    hdR_ele->Write();
    hdpt_ele->Write();
    hdR_genjet->Write();
    hmcCalIso->Write();
    hmcGenIso->Write();
    hmcpartonIso->Write();
    h_truepho->Write();
    h_convpho->Write();
    h_ngenpho->Write();
    h_npho->Write();
    h_nele->Write();
    h_nphoFiredTrgs->Write();

    hgenphoEB_pt->Write();
    hgenphoEB_pt_vbin->Write();
    hgenphoEB_eta->Write();
    hgenphoEE_pt->Write();
    hgenphoEE_pt_vbin->Write();
    hgenphoEE_eta->Write();
    hgenpho_eta_phi->Write();
    hgenpho_eta_pt->Write();

    hgenphoEBEE0_pt_vbin->Write();
    hgenphoEBEE1_pt_vbin->Write();
    hgenphoEBEE2_pt_vbin->Write();
    hgenphoEBEE3_pt_vbin->Write();

    h_EB_bdt->Write();
    h_EE_bdt->Write();

    h_phoEt->Write();
    h_npj->Write();
    h_jetPt->Write();
    h_pjmass->Write();
    h_npp->Write();
    h_pho2Pt->Write();
    h_ppmass->Write();
    h_ppmass_zoom->Write();

    h_njet->Write();
    h_nrecojet->Write();
    h_ngenjet->Write();
    h_detadpt_jet12->Write();
    h_dR_phojet->Write();
    h_dR_phoele->Write();
    h_dpt_phojet->Write();

    h_dphi_recoil->Write();
    h_dpt_recoil->Write();

    tp_rho->Write();
    tp_rho_EB->Write();
    tp_rho_EE->Write();
    h2_nVtx_rho->Write();
    h2_nVtx_iso->Write();
    for(int ii=0; ii<7; ii++){
        tp_chIso[ii]->Write();
        tp_phIso[ii]->Write();
        tp_nhIso[ii]->Write();

        tp_chIso_rho[ii]->Write();
        tp_phIso_rho[ii]->Write();
        tp_nhIso_rho[ii]->Write();
    }

    h_Zee_mass->Write();
    h_Zee_mass_csev->Write();
    h_phoPt_eta_Z_all->Write();
    h_phoPt_eta_Z_csev->Write();

    h_Zmm_mass->Write();
    h_MET->Write();
    h_Wen_mt->Write();
    h_Wmn_mt->Write();

    hist_measured->Write();
    hist_reco->Write();  

    h_jetID->Write();
    h_jetIDv->Write();
    hdR_pho_lep->Write();
    hdR_fake_lep->Write();

    hphoEB_pt_presel_nocsev->Write();
    hphoEB_pt_presel_csev->Write();
    hphoEE_pt_presel_nocsev->Write();
    hphoEE_pt_presel_csev->Write();

    hphoEB_pt_presel_den->Write();
    hphoEB_pt_presel_num->Write();
    hphoEE_pt_presel_den->Write();
    hphoEE_pt_presel_num->Write();
    h_EBSeedTime->Write();
    h_EESeedTime->Write();
    h_EBSeedTimeW->Write();
    h_EESeedTimeW->Write();

    h2_mcPID_mcPt->Write();

    std::map<std::string, TH1F*>::const_iterator citer = histMap.cbegin();
    std::map<std::string, TH1F*>::const_iterator ciend = histMap.cend  ();
    while ( citer != ciend )
    { citer++->second->Write(); }

    fout_->Close();

    fprintf(stderr, "Processed all events\n");

}


void xPhotonHFJet(Int_t dataset) {
  Char_t fname[200];
  XS=1.;
  vector <string> pathes;


 
  sprintf(fname, "/home/ltsai/ggtree_mc_1.root");
   pathes.push_back(fname);
    XS = 1.;
    isMC=1;
    gjetSignal=1;
    gjet15to6000=1;

  Char_t oname[200];
  sprintf(oname, "output_job_PhotonHFJet_%d.root", dataset);

  xPhotonHFJet(pathes, oname);
  
}

void xPhotonHFJet(Char_t fname[200], Char_t oname[200], Double_t crosssection, int dowmnoption){
  //doWmn = dowmnoption;
  isMC=1;
  vector <string> pathes;
  pathes.push_back(fname);
  XS = crosssection;
  xPhotonHFJet(pathes, oname);
  
}

void xPhotonHFJet(std::string ipath, int outID)
{
   Char_t fname[200];
   XS=1.;
   vector <string> pathes;

   pathes.push_back(ipath);
   XS = 1.;
   isMC=1;
   gjetSignal=1;
   gjet15to6000=1;

   Char_t oname[200];
   sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

   xPhotonHFJet(pathes, oname);

}

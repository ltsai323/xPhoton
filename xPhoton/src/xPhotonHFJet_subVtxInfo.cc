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
//#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/JetIDMgr.h"
#include "xPhoton/xPhoton/interface/ShowerShapeCorrectionAdapter.h"
#include "xPhoton/xPhoton/interface/RhoCorrection.h"
// switches
static Int_t MINITREE=1;
static Double_t XS=1.;
static Bool_t verbose=false;
static Int_t JETPD_PHOTONHLT=0;
static Int_t ONLY_LEADINGPHOTON=0;

static bool hasSubVtxInfo = true;
static bool testJetSF = true;
static bool PUmaxInfo = true;
static bool ELECTRONVETO = false;
static bool USEHLT = false;

const float CUT_DELTAR  = 0.2;
const float CUT_DELTAPT = 0.35;
const float NOTHING = -1;
const int MAX_SINGLE_PHO_TRIG = 10;
namespace _xphotonFunc_{
std::vector<int> GenPhoIdxs( TreeReader* event );
std::vector<int> GenMuonIdxs( TreeReader* event );
std::vector<int> GenEleIdxs( TreeReader* event );
int TruthMatch_GenPhoton( TreeReader* event, int recoPhoIdx, std::vector<int> phomcid );
int TruthMatch_GenConvertedPho( TreeReader* event, int recoPhoIdx, std::vector<int> elemcid );
void FillStatus(TH1* hist, float val) { hist->Fill(val+0.001); }
};
using namespace _xphotonFunc_;

static TH1F* h_subVtxPt    ;
static TH1F* h_subVtxMass  ;
static TH1F* h_subVtx3DVal ;
static TH1F* h_subVtx3DErr ;
static TH1F* h_subVtxNtrks ;

static TH1F *h_hasGoodVtx ;
static TH1F *hpthat ;
static TH1F *hpthat_wide ;
static TH1F *hdpt ;
static TH1F *hdpt_signed ;
static TH1F *hdR ;

static TH1F *hdpt_ele_signed ;
static TH1F *hdpt_ele;
static TH1F *hdR_ele ;

static TH1F *hdR_genjet ;

static TH1F *hdR_pho_lep ;
static TH1F *hdR_fake_lep ;

static TH1F *hmcTrkIso ;
static TH1F *hmcTrkIsoMini ;
static TH1F *hmcTrkIsoMicro ;
static TH1F *hmcCalIso ;
static TH1F *hmcCalIsoMini ;
static TH1F *hmcCalIsoMicro ;
static TH1F *hmcGenIso ;
static TH1F *hmcpartonIso ;
static TH1F *hgenphoEB_pt ;
static TH1F *hgenphoEB_eta ;
static TH1F *hgenphoEE_pt ;
static TH1F *hgenphoEE_eta ;

static TH1F *hgenphoEB_pt_vbin ;
static TH1F *hgenphoEE_pt_vbin ;

static TH1F *hgenphoEBEE0_pt_vbin ;
static TH1F *hgenphoEBEE1_pt_vbin ;
static TH1F *hgenphoEBEE2_pt_vbin ;
static TH1F *hgenphoEBEE3_pt_vbin ;

static TH1F *hgenphoEBEE0_pt_vbin_amcnlo ;
static TH1F *hgenphoEBEE1_pt_vbin_amcnlo ;
static TH1F *hgenphoEBEE2_pt_vbin_amcnlo ;
static TH1F *hgenphoEBEE3_pt_vbin_amcnlo ;

static TH1F *hgenphoEBjet0_pt_vbin_amcnlo ;
static TH1F *hgenphoEBjet1_pt_vbin_amcnlo ;
static TH1F *hgenphoEEjet0_pt_vbin_amcnlo ;
static TH1F *hgenphoEEjet1_pt_vbin_amcnlo ;
static TH1F* hMCMatchingReport ;
static TH1F* hMCMatchingMultiplicity ;


static TH1F *hphoEB_pt_presel_nocsev ;
static TH1F *hphoEB_pt_presel_csev ;
static TH1F *hphoEE_pt_presel_nocsev ;
static TH1F *hphoEE_pt_presel_csev ;

static TH1F *hphoEB_pt_presel_den ;
static TH1F *hphoEB_pt_presel_num ;
static TH1F *hphoEE_pt_presel_den ;
static TH1F *hphoEE_pt_presel_num ;

static TH2F *h_phoPt_eta_Z_all ;
static TH2F *h_phoPt_eta_Z_csev ;

static TH2F *hgenpho_eta_phi ;
static TH2F *hgenpho_eta_pt ;

static TH1F *h_ngenpho ;
static TH1F *h_npho ;
static TH1F *h_nele ;
static TH1F *h_nphoFiredTrgs ;
static TH1F *h_truepho ;
static TH1F *h_convpho ;
static TH1F *h_phoEt ;
static TH1F *h_jetPt ;

static TH1F *h_pjmass ;
static TH1F *h_njet ;
static TH1F *h_nrecojet ;
static TH1F *h_ngenjet ;

static TH2F *h_detadpt_jet12 ;


static TH1F *h_dR_phojet ;
static TH1F *h_dR_phoele ;
static TH1F *h_dpt_phojet ;

static TH1F *h_jetID ;
static TH1F *h_jetIDv ;


static TH1F *h_pho2Pt ;

static TH1F *h_ppmass ;
static TH1F *h_ppmass_zoom ;
static TH1F *h_EBSeedTime ;
static TH1F *h_EESeedTime ;
static TH1F *h_EBSeedTimeW ;
static TH1F *h_EESeedTimeW ;

static TH1F *h_EB_bdt ;
static TH1F *h_EE_bdt ;

static TH1F *h_dphi_recoil ;
static TH1F *h_dpt_recoil ;


static TProfile *tp_rho ;
static TProfile *tp_rho_EB ;
static TProfile *tp_rho_EE ;
static TH2F *h2_nVtx_rho ;
static TH2F *h2_nVtx_iso ;

static TProfile *tp_chIso[10]; //;
static TProfile *tp_phIso[10]; //;
static TProfile *tp_nhIso[10]; //;

static TProfile *tp_chIso_rho[10]; //;
static TProfile *tp_phIso_rho[10]; //;
static TProfile *tp_nhIso_rho[10]; //;

static TH1F *h_Zee_mass ;
static TH1F *h_Zee_mass_csev ;
static TH1F *h_Zmm_mass ;
static TH1F *h_MET ;
static TH1F *h_Wen_mt ;
static TH1F *h_Wmn_mt ;

static TH2F *h2_mcPID_mcPt ;

void xPhotonHFJet(vector<string> pathes, Char_t oname[200], const std::string dataEra){

    TreeReader data(pathes);
    std::string totfile="";
    if ( pathes.size() > 1 ) for ( auto pathe : pathes ) totfile=totfile+","+pathe;
    else totfile = pathes[0];
    LOG_INFO("Loading files : %s", totfile.c_str());

    TFile *fout_;
    LOG_DEBUG("output name is %s" ,oname);
    fout_ = new TFile(oname,"recreate");
    LOG_DEBUG("output tfile is opened");

    TTree *outtree_;
    ShowerShapeCorrectionAdapter* SScorr = new ShowerShapeCorrectionAdapter( dataEra, data.HasMC() );


    float ptcut[] = {
           15,    20,    40,    60,    75, // 0
           90,   105,   120,   135,   150, // 5

          160,   170,   180,   190,   200, //10
          220,   250,   300,   350,   400, //15

          500,   750,  1000,  1500,  2000, //20
         3000, 10000}; //22 bins

    float etabin[] = {0., 0.8, 1.5, 2.1, 2.5};

    h_subVtxPt    = new TH1F("subVtxPt"   , "pt distribution of secondary vertex in bJet", 70, 0., 350. );
    h_subVtxMass  = new TH1F("subVtxMass" , "mass spectrum of secondary vertex in bJet", 88, 0., 22. );
    h_subVtx3DVal = new TH1F("subVtx3DVal", "flight distance between PV and SV", 60, 0., 120. );
    h_subVtx3DErr = new TH1F("subVtx3DErr", "error of flight distance between PV and SV", 88, 0., 22. );
    h_subVtxNtrks = new TH1F("subVtxNtrks", "number of tracks containing in SV", 18,0.,18. );
    
    h_hasGoodVtx = new TH1F("h_hasGoodVtx","hasGoodVtx",2,0,2);
    hpthat = new TH1F("hpthat","pt hat", 100, 0., 1000.);
    hpthat_wide = new TH1F("hpthat_wide","pt hat wide window", 600, 0., 6000.);
    
    hdpt = new TH1F("hdpt","dpt", 100, 0., 1.);
    hdpt_signed = new TH1F("hdpt_signed","dpt_signed", 200, -1., 1.);
    hdR = new TH1F("hdR","dR", 100, 0., 2.);
    
    hdpt_ele = new TH1F("hdpt_ele","dpt", 100, 0., 1.);
    hdpt_ele_signed = new TH1F("hdpt_ele_signed","dpt", 200, -1., 1.);
    hdR_ele = new TH1F("hdR_ele","dR", 100, 0., 2.);
    
    hdR_genjet = new TH1F("hdR_genjet","dR", 100, 0., 2.);
    
    hdR_pho_lep = new TH1F("hdR_pho_lep","dR pho and lepton", 150, 0., 3.);
    hdR_fake_lep = new TH1F("hdR_fake_lep","dR fake and lepton", 150, 0., 3.);
    
    hmcTrkIso = new TH1F("hmcTrkIso","mcTrkIso", 500, 0., 20.);
    hmcTrkIsoMini = new TH1F("hmcTrkIsoMini","mcTrkIsoMini", 500, 0., 10.);
    hmcTrkIsoMicro = new TH1F("hmcTrkIsoMicro","mcTrkIsoMicro", 500, 0., 2.);
    hmcCalIso = new TH1F("hmcCalIso","mcCalIso", 500, 0., 20.);
    hmcCalIsoMini = new TH1F("hmcCalIsoMini","mcCalIsoMini", 500, 0., 10.);
    hmcCalIsoMicro = new TH1F("hmcCalIsoMicro","mcCalIsoMicro", 500, 0., 2.);
    hmcGenIso = new TH1F("hmcGenIso","mcGenIso", 100, 0., 20.);
    hmcpartonIso = new TH1F("hmcpartonIso","mcpartonIso", 100, 0., 20.);
    hgenphoEB_pt = new TH1F("hgenphoEB_pt","GenphoEB photon Pt", 3000, 0., 3000.);
    hgenphoEB_eta = new TH1F("hgenphoEB_eta","GenphoEB photon eta", 600, -3., 3.);
    hgenphoEE_pt = new TH1F("hgenphoEE_pt","GenphoEE photon Pt", 3000, 0., 3000.);
    hgenphoEE_eta = new TH1F("hgenphoEE_eta","GenphoEE photon eta", 600, -3., 3.);
    
    hgenphoEB_pt_vbin = new TH1F("hgenphoEB_pt_vbin","GenphoEB photon Pt var. bin", 25, ptcut);
    hgenphoEE_pt_vbin = new TH1F("hgenphoEE_pt_vbin","GenphoEE photon Pt var. bin", 25, ptcut);
    
    hgenphoEBEE0_pt_vbin = new TH1F("hgenphoEBEE0_pt_vbin","GenphoEBEE0 photon Pt var. bin", 25, ptcut);
    hgenphoEBEE1_pt_vbin = new TH1F("hgenphoEBEE1_pt_vbin","GenphoEBEE1 photon Pt var. bin", 25, ptcut);
    hgenphoEBEE2_pt_vbin = new TH1F("hgenphoEBEE2_pt_vbin","GenphoEBEE2 photon Pt var. bin", 25, ptcut);
    hgenphoEBEE3_pt_vbin = new TH1F("hgenphoEBEE3_pt_vbin","GenphoEBEE3 photon Pt var. bin", 25, ptcut);
    
    hgenphoEBEE0_pt_vbin_amcnlo = new TH1F("hgenphoEBEE0_pt_vbin_amcnlo","GenphoEBEE0 photon Pt var. bin_amcnlo", 25, ptcut);
    hgenphoEBEE1_pt_vbin_amcnlo = new TH1F("hgenphoEBEE1_pt_vbin_amcnlo","GenphoEBEE1 photon Pt var. bin_amcnlo", 25, ptcut);
    hgenphoEBEE2_pt_vbin_amcnlo = new TH1F("hgenphoEBEE2_pt_vbin_amcnlo","GenphoEBEE2 photon Pt var. bin_amcnlo", 25, ptcut);
    hgenphoEBEE3_pt_vbin_amcnlo = new TH1F("hgenphoEBEE3_pt_vbin_amcnlo","GenphoEBEE3 photon Pt var. bin_amcnlo", 25, ptcut);
    
    hgenphoEBjet0_pt_vbin_amcnlo = new TH1F("hgenphoEBjet0_pt_vbin_amcnlo","GenphoEB jet0 photon Pt var. bin_amcnlo", 25, ptcut);
    hgenphoEBjet1_pt_vbin_amcnlo = new TH1F("hgenphoEBjet1_pt_vbin_amcnlo","GenphoEB jet1 photon Pt var. bin_amcnlo", 25, ptcut);
    hgenphoEEjet0_pt_vbin_amcnlo = new TH1F("hgenphoEEjet0_pt_vbin_amcnlo","GenphoEB jet0 photon Pt var. bin_amcnlo", 25, ptcut);
    hgenphoEEjet1_pt_vbin_amcnlo = new TH1F("hgenphoEEjet1_pt_vbin_amcnlo","GenphoEB jet1 photon Pt var. bin_amcnlo", 25, ptcut);
    hMCMatchingReport = new TH1F("hMCMatchingReport", "Selection bits for MC truth matching", 10,0.,10.);
    hMCMatchingMultiplicity = new TH1F("hMCMatchingMultiplicity", "MC truth matching multiplicity", 10, 0., 10.);

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

    hphoEB_pt_presel_nocsev = new TH1F("hphoEB_pt_presel_nocsev","pt of EB no csev", 25, ptcut);
    hphoEB_pt_presel_csev = new TH1F("hphoEB_pt_presel_csev","pt of EB  csev", 25, ptcut);
    hphoEE_pt_presel_nocsev = new TH1F("hphoEE_pt_presel_nocsev","pt of EE no csev", 25, ptcut);
    hphoEE_pt_presel_csev = new TH1F("hphoEE_pt_presel_csev","pt of EE  csev", 25, ptcut);

    hphoEB_pt_presel_den = new TH1F("hphoEB_pt_presel_den","pt of EB can", 25, ptcut);
    hphoEB_pt_presel_num = new TH1F("hphoEB_pt_presel_num","pt of EB sel", 25, ptcut);
    hphoEE_pt_presel_den = new TH1F("hphoEE_pt_presel_den","pt of EE can", 25, ptcut);
    hphoEE_pt_presel_num = new TH1F("hphoEE_pt_presel_num","pt of EE sel", 25, ptcut);

    h_phoPt_eta_Z_all = new TH2F("h_phoPt_eta_Z_all","pt eta of photon from Z all", 25, ptcut, 4, etabin);
    h_phoPt_eta_Z_csev = new TH2F("h_phoPt_eta_Z_csev","pt eta of photon from Z all", 25, ptcut, 4, etabin);

    hgenpho_eta_phi = new TH2F("hgenpho_eta_phi","gen photon eta phi", 500, -2.5, 2.5, 320, -3.2, 3.2);
    hgenpho_eta_pt = new TH2F("hgenpho_eta_pt","gen photon eta pt", 50, -2.5, 2.5, 100, 0., 1000.);

    h_ngenpho = new TH1F("h_ngenpho","n gen pho", 20, 0., 20);
    h_npho = new TH1F("h_npho","n pho", 20, 0., 20);
    h_nele = new TH1F("h_nele","n ele", 20, 0., 20);
    h_nphoFiredTrgs = new TH1F("h_nphoFiredTrgs","n pho", 20, 0., 20);
    h_truepho = new TH1F("h_truepho","true pho", 10, 0., 10.);
    h_convpho = new TH1F("h_convpho","converted pho", 10, 0., 10.);
    h_phoEt = new TH1F("h_phoEt","pho Et", 200, 0., 1000);
    h_jetPt = new TH1F("h_jetPt","jet Pt", 200, 0., 1000);
    //h_npj = new TH1F("h_npj","n pho jet comb", 20, 0., 20.);
    h_pjmass = new TH1F("h_pjmass","inv mass of pho jet", 1000, 0., 10000);
    h_njet = new TH1F("h_njet","njet", 20, 0., 20);
    h_nrecojet = new TH1F("h_nrecojet","n reco jet", 20, 0., 20);
    h_ngenjet = new TH1F("h_ngenjet","n gen jet", 20, 0., 20);

    h_detadpt_jet12 = new TH2F("h_detadpt_jet12","deta dpt jet12",3,-1,2,100,0., 1.);


    h_dR_phojet = new TH1F("h_dR_phojet","dR of pho jet", 100, 0., 2.);
    h_dR_phoele = new TH1F("h_dR_phoele","dR of pho ele", 100, 0., 2.);
    h_dpt_phojet = new TH1F("h_dpt_phojet","dpt of pho jet", 100, 0., 4.);

    h_jetID = new TH1F("h_jetID", "jetid", 2, 0., 2.);
    h_jetIDv = new TH1F("h_jetIDv", "jetid v", 2, 0., 2.);


    h_pho2Pt = new TH1F("h_pho2Pt","pho2 Pt", 200, 0., 1000);
    //h_npp = new TH1F("h_npp","pho pho comb", 20, 0., 20.);
    h_ppmass = new TH1F("h_ppmass","inv mass of pho pho", 1000, 0., 10000);
    h_ppmass_zoom = new TH1F("h_ppmass_zoom","inv mass of pho pho zoom", 200, 0., 200);
    h_EBSeedTime = new TH1F("h_EBSeedTime","EBSeedTime from z",1000, -5., 5.);
    h_EESeedTime = new TH1F("h_EESeedTime","EESeedTime from z",1000, -5., 5.);
    h_EBSeedTimeW = new TH1F("h_EBSeedTimeW","EBSeedTime from W",1000, -5., 5.);
    h_EESeedTimeW = new TH1F("h_EESeedTimeW","EESeedTime from W",1000, -5., 5.);

    h_EB_bdt = new TH1F("h_EB_bdt","EB bdt output", 200, -1., 1.);
    h_EE_bdt = new TH1F("h_EE_bdt","EE bdt output", 200, -1., 1.);

    h_dphi_recoil = new TH1F("h_dphi_recoil","dphi recoil jet", 100., -4., 4.);
    h_dpt_recoil = new TH1F("h_dpt_recoil","dpt recoil jet", 100.,-2., 2.);


    tp_rho = new TProfile("tp_rho","tp_rho", 100, 0., 100.);
    tp_rho_EB = new TProfile("tp_rho_EB","tp_rho_EB", 100, 0., 100.);
    tp_rho_EE = new TProfile("tp_rho_EE","tp_rho_EE", 100, 0., 100.);
    h2_nVtx_rho = new TH2F("h2_nVtx_rho","h2_nVtx_rho",100, 0., 100., 100., 0., 50.);; //= new TProfile();
    h2_nVtx_iso = new TH2F("h2_nVtx_iso","h2_nVtx_iso",100, 0., 100., 1000., 0., 10.);; //= new TProfile();


    h_Zee_mass = new TH1F("h_Zee_mass","Zee mass", 100, 50., 250);
    h_Zee_mass_csev = new TH1F("h_Zee_mass_csev","Zee mass photon CSEV", 100, 50., 250);
    h_Zmm_mass = new TH1F("h_Zmm_mass","Zmm mass", 150, 0., 150);
    h_MET = new TH1F("h_MET","MET", 100, 0., 200.);
    h_Wen_mt = new TH1F("h_Wen_mt","W enue Mt", 150, 0., 150.); 
    h_Wmn_mt = new TH1F("h_Wmn_mt","W mnue Mt", 150, 0., 150.); 

    h2_mcPID_mcPt = new TH2F("h2_mcPID_mcPt","mcPID vs mcPt", 100, 0., 1000, 30, 0., 30);


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
    Float_t calib_chIso;
    Float_t rho;
    Int_t phohasPixelSeed_;
    Long64_t phoFiredTrgs_;

    Float_t rawE, scEtaWidth, scPhiWidth, esRR, esEn, mva, calib_mva,  photonIDmva;
    Float_t sieieFull5x5, sipipFull5x5, sieipFull5x5, e2x2Full5x5,  e5x5Full5x5;
    Int_t isConverted;

    //Float_t mcCalIso04, mcTrkIso04;
    Float_t xsweight=XS;
    Float_t mygenweight;
    //Long64_t HLT, HLTIsPrescaled, HLT50ns, HLTIsPrescaled50ns;
    Long64_t HLT, HLTIsPrescaled;// HLT50ns, HLTIsPrescaled50ns;
    Float_t  MET,   METPhi;
    Float_t  puppiMET,   puppiMETPhi;
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

    Float_t esEnergyOverSCRawEnergy;
    Float_t s4Full5x5;
    Float_t calib_s4Full5x5,calib_r9Full5x5;
    Float_t calib_sieieFull5x5,calib_sieipFull5x5;
    Float_t calib_scEtaWidth,calib_scPhiWidth;
    Float_t calib_esEnergyOverSCRawEnergy;

    Int_t    run;
    Long64_t event;

    //Int_t photon_jetID_;
    Int_t phoIDbit_;
    Int_t jetID;
    Int_t jetPUIDbit;
    
    const unsigned MAX_LHEPARTICLE = 50;
    Int_t nLHE;
    Int_t lhePID[MAX_LHEPARTICLE];
    Float_t lheE[MAX_LHEPARTICLE], lhePx[MAX_LHEPARTICLE], lhePy[MAX_LHEPARTICLE], lhePz[MAX_LHEPARTICLE];
    Int_t mcMomPID_;

    Float_t mcTrkIso, mcCalIso, matchDR, matchDPT;

    Float_t SeedTime_, SeedEnergy_, MIPTotEnergy_;
    Float_t leadingPUPtHat;
    Float_t leadingLHEPt;
    Float_t genHT_pthatDef;


    Int_t phoFillIdx = 0;
    if ( hasSubVtxInfo )
    {
        outtree_->Branch("jetSubVtxPt"   , &jetSubVtxPt_   , "jetSubVtxPt/F"   );
        outtree_->Branch("jetSubVtxMass" , &jetSubVtxMass_ , "jetSubVtxMass/F" );
        outtree_->Branch("jetSubVtx3DVal", &jetSubVtx3DVal_, "jetSubVtx3DVal/F");
        outtree_->Branch("jetSubVtx3DErr"  , &jetSubVtx3DErr_  , "jetSubVtx3DErr/F"  );
        outtree_->Branch("jetSubVtxNtrks", &jetSubVtxNtrks_, "jetSubVtxNtrks/I");
    }

    if (!ONLY_LEADINGPHOTON )
        outtree_->Branch("phoFillIdx", &phoFillIdx, "phoFillIdx/I");
    outtree_->Branch("run", &run, "run/I");
    outtree_->Branch("event", &event, "event/L");
    outtree_->Branch("isData",         &isData,        "isData/O");
    if (!data.HasMC() )
    {
    outtree_->Branch("HLT",         &HLT,        "HLT/L");
    outtree_->Branch("HLTIsPrescaled", &HLTIsPrescaled,        "HLTIsPrescaled/L");
    }
    outtree_->Branch("phoFiredTrgs", &phoFiredTrgs_,"phoFiredTrgs/L");
    if ( data.HasMC() )
    {
    outtree_->Branch("pthat",        &pthat_,       "pthat/F");
    outtree_->Branch("genHT",        &genHT_,       "genHT/F");
    outtree_->Branch("mcPt",         &mcPt_,        "mcPt/F");
    outtree_->Branch("mcEta",        &mcEta_,       "mcEta/F");
    outtree_->Branch("mcPhi",        &mcPhi_,       "mcPhi/F");
    outtree_->Branch("mcCalIso04",   &mcCalIso04_,   "mcCalIso04/F");
    outtree_->Branch("mcTrkIso04",   &mcTrkIso04_,   "mcTrkIso04/F");
    outtree_->Branch("mcMomPID",     &mcMomPID_,     "mcMomPID/F");

    outtree_->Branch("mcTrkIso", & mcTrkIso, "mcTrkIso/F");
    outtree_->Branch("mcCalIso", & mcCalIso, "mcCalIso/F");
    outtree_->Branch("matchDR",  & matchDR , "matchDR/F");
    outtree_->Branch("matchDPT", & matchDPT, "matchDPT/F");
    }
    outtree_->Branch("recoPt",       &recoPt,       "recoPt/F");
    outtree_->Branch("recoPtCalib",  &recoPtCalib,  "recoPtCalib/F");
    outtree_->Branch("recoEta",      &recoEta,      "recoEta/F");
    outtree_->Branch("recoPhi",      &recoPhi,      "recoPhi/F");
    outtree_->Branch("recoSCEta",    &recoSCEta,    "recoSCEta/F");
    outtree_->Branch("r9",           &r9,           "r9/F");
    outtree_->Branch("s4Full5x5"          , &s4Full5x5             , "s4Full5x5/F"               );
    outtree_->Branch("esEnergyOverSCRawEnergy", &esEnergyOverSCRawEnergy, "esEnergyOverSCRawEnergy/F");
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
    if (!data.HasMC() )
    {
    outtree_->Branch("calib_chIso",  &calib_chIso, "calib_chIso/F");
    }

    outtree_->Branch("rawE",         &rawE,         "rawE/F");
    outtree_->Branch("scEtaWidth",   &scEtaWidth,   "scEtaWidth/F");
    outtree_->Branch("scPhiWidth",   &scPhiWidth,   "scPhiWidth/F");
    outtree_->Branch("esRR",         &esRR,         "esRR/F");   
    outtree_->Branch("esEn",         &esEn,         "esEn/F");   
    outtree_->Branch("mva",          &mva,          "mva/F");  
    if ( data.HasMC() )
    {
    outtree_->Branch("calib_mva",   &calib_mva,   "calib_mva/F");  
    }
    outtree_->Branch("photonIDmva",       &photonIDmva,       "photonIDmva/F");  
    outtree_->Branch("phoIDbit",          &phoIDbit_,          "phoIDbit/I");  
    if (!data.HasMC() )
    {
    outtree_->Branch("metFilters",    &metFilters,    "metFilters/I");  
    }
    outtree_->Branch("MET",    &MET,    "MET/F");  
    outtree_->Branch("METPhi",    &METPhi,    "METPhi/F");  
    outtree_->Branch("puppiMET",    &puppiMET,    "puppiMET/F");  
    outtree_->Branch("puppiMETPhi",    &puppiMETPhi,    "puppiMETPhi/F");  
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
        outtree_->Branch( "calib_scPhiWidth"  , &calib_scPhiWidth     , "calib_scPhiWidth/F"       );
        outtree_->Branch( "calib_r9Full5x5"   , &calib_r9Full5x5      , "calib_r9Full5x5/F"        );
        outtree_->Branch( "calib_s4Full5x5"          , &calib_s4Full5x5             , "calib_s4Full5x5/F"               );
        outtree_->Branch( "calib_sieieFull5x5", &calib_sieieFull5x5   , "calib_sieieFull5x5/F"     );
        outtree_->Branch( "calib_sieipFull5x5", &calib_sieipFull5x5   , "calib_sieipFull5x5/F"     );
        outtree_->Branch( "calib_esEnergyOverSCRawEnergy", &calib_esEnergyOverSCRawEnergy, "calib_esEnergyOverSCRawEnergy/F");

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
    if ( data.HasMC() && PUmaxInfo )
    {
    outtree_->Branch("leadingLHEPt", &leadingLHEPt);
    outtree_->Branch("genHT_pthatDef", &genHT_pthatDef, "genHT_pthatDef/F");
    outtree_->Branch("leadingPUPtHat" ,&leadingPUPtHat);
    }

    // mc efficiency check
    // GenPhoNumbering shows how much photon passed the Gen-selection.
    // One should only assigned 0 for mc selection. (0 is leading gen selected photon)
    TNtuple* selectionRes = new TNtuple("selRes", "monte carlo cut results",
            "passed:mcPt:mcEta:recoPt:recoEta:jetPt:jetEta:matchDeltaR:matchPt:matchGenIso:chIso:passedHLTbit:GenPhoNumbering");

            // 0 passed
            // 1 mcPt
            // 2 mcEta
            // 3 recoPt
            // 4 recoEta
            // 5 jetPt
            // 6 jetEta
            // 7 matchDeltaR
            // 8 matchPt
            // 9 matchGenIso
            //10 chIso
            //11 passedHLTbit
            //12 GenPhoNumbering



    TH1F *hist_measured = new TH1F("hist_measure","measure", 100, 0., 1000);
    TH1F *hist_reco = new TH1F("hist_reco","reco", 100, 0., 1000);

    // // pileup reweighting for MC
    PUWeightCalculator puCalc;
    //TGraph *tgr[8];
    if(data.HasMC())
    {
        puCalc.Init( ExternalFilesMgr::RooFile_PileUp(dataEra) );
    }
    PhotonMVACalculator mvaloader( &data, dataEra );



    LOG_INFO(" processing entries %lld \n", data.GetEntriesFast());


    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++) {
        if ( ev %10000 == 0 ) 
            LOG_INFO(" processing entries %lld in %lld \n", ev, data.GetEntriesFast());
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
        //Float_t* mcE       =0;
        Float_t* mcMomPt   =0;
        Float_t* mcMomEta   =0;
        Float_t* mcMomPhi   =0;
        Float_t genHT      =0;
        Int_t    nPUInfo =0;
        Int_t*   puBX=0; 
        Float_t* puTrue=0;
        Float_t* mcCalIsoDR04=0;
        Float_t* mcTrkIsoDR04=0;
        Int_t* mcStatus=0;
        //Short_t* mcStatusFlag=0;

        Float_t* jetGenJetPt = 0;
        Float_t* jetGenJetEn = 0;
        Float_t* jetGenJetEta = 0;
        Float_t* jetGenJetPhi = 0;

        Float_t      genWeight =1.;
        int nPU_ = 0;
        // gen histos {{{
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
            //mcE       = data.GetPtrFloat("mcE");
            mcMomPt   = data.GetPtrFloat("mcMomPt");
            mcMomEta   = data.GetPtrFloat("mcMomEta");
            mcMomPhi   = data.GetPtrFloat("mcMomPhi");
            mcStatus = data.GetPtrInt("mcStatus");
            //mcStatusFlag = data.GetPtrShort("mcStatusFlag");

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
            //if(gjet15to6000==1) xsweight=genWeight;

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
        } // is MC end
        // gen histos  end }}}


        if(nPho==0) continue; //skip entry if no recoPhoton
        Float_t *jetSubVtxPt = nullptr;
        Float_t *jetSubVtxMass = nullptr;
        Float_t *jetSubVtx3DVal = nullptr;
        Float_t *jetSubVtx3DErr = nullptr;
        Int_t   *jetSubVtxNtrks = nullptr;
        if ( hasSubVtxInfo )
        {
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
        }

        Float_t pfMET = data.GetFloat("pfMET");
        Float_t pfMETPhi = data.GetFloat("pfMETPhi");
        Float_t puppiMET = data.GetFloat("puppiMET");
        Float_t puppiMETPhi = data.GetFloat("puppiMETPhi");
        //Int_t    nEle     = data.GetInt("nEle");

        Float_t* jetPt = data.GetPtrFloat("jetPt");
        Float_t* jetEn = data.GetPtrFloat("jetEn");
        Float_t* jetEta = data.GetPtrFloat("jetEta");
        Float_t* jetPhi = data.GetPtrFloat("jetPhi");
        Long64_t*   jetFiredTrgs = data.GetPtrLong64("jetFiredTrgs");      

        vector<bool> &jetId             = *((vector<bool>*) data.GetPtr("jetPFLooseId"));
        Float_t *jetJECUnc = data.GetPtrFloat("jetJECUnc");
        //Float_t* jetNHF = data.GetPtrFloat("jetNHF");
        //Float_t* jetNEF = data.GetPtrFloat("jetNEF");

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
        std::map<int,int> mcmompid;

        mcpt.clear();
        mceta.clear();
        mcphi.clear();

        //h_npho->Fill(nPho);
        int nmatch=0;
        int nmatch_EB=0;
        int nmatch_EE=0;
        int nconv=0;

        if(verbose) {
            event_ = event_;
            LOG_DEBUG("-----------------------------------------------------------------------\n");
            LOG_DEBUG("event %lli, npho %d, nMC %d\n", event_, nPho, nMC);
        }


        if( data.HasMC()) { 
            /* find target gen particles */
            vector<int> phomcid = GenPhoIdxs(&data);
            vector<int> muonmcid = GenMuonIdxs(&data);
            vector<int> elemcid = GenEleIdxs(&data);


            FillStatus( h_truepho, phomcid.size() );
            FillStatus( h_convpho, elemcid.size()/2 );


            // find reco photon
            for (Int_t recoPhoIdx=0; recoPhoIdx<nPho; ++recoPhoIdx) {
                if(phoEt[recoPhoIdx]<15.) continue;
                int tmp_isMatched = 0;
                int tmp_isMatchedEle = 0;
                int tmp_isConverted = 0;

                double tmp_mcPt_ = -999.;
                double tmp_mcEta_ = -999.;
                double tmp_mcPhi_ = -999.;
                double tmp_mcCalIso04_ = -999.;
                double tmp_mcTrkIso04_ = -999.;
                int tmp_momid = 0;
 
                if(verbose)
                { LOG_DEBUG("pho Et %.2f, eta %.2f, phi %.2f ,CSEV %d \n", phoEt[recoPhoIdx], phoEta[recoPhoIdx], phoPhi[recoPhoIdx], phoEleVeto[recoPhoIdx]); }
                int mcIdx = TruthMatch_GenPhoton(&data, recoPhoIdx, phomcid);
                if ( mcIdx != -1 )
                {
                    tmp_isMatched = 1;
                    tmp_mcPt_  = mcPt[mcIdx];
                    tmp_mcEta_ = mcEta[mcIdx];
                    tmp_mcPhi_ = mcPhi[mcIdx];
                    tmp_mcCalIso04_ = mcCalIsoDR04[mcIdx];
                    tmp_mcTrkIso04_ = mcTrkIsoDR04[mcIdx];
                    tmp_momid = mcMomPID[mcIdx];
                }
                else
                {
                    mcIdx = TruthMatch_GenConvertedPho(&data, recoPhoIdx, elemcid);
                    if ( mcIdx != -1 )
                    {
                        tmp_isMatchedEle = 1;
                        tmp_isConverted = 1;
                        tmp_mcPt_  = mcMomPt[mcIdx];
                        tmp_mcEta_ = mcMomEta[mcIdx];
                        tmp_mcPhi_ = mcMomPhi[mcIdx];	      
                        tmp_mcCalIso04_ = mcCalIsoDR04[mcIdx];
                        tmp_mcTrkIso04_ = mcTrkIsoDR04[mcIdx];
                        tmp_momid = mcGMomPID[mcIdx];
                    }
                }
                
                if(tmp_isMatched==1) {
                    nmatch++;
                    if(TMath::Abs(phoSCEta[recoPhoIdx])<=1.4442) nmatch_EB++;
                    if(TMath::Abs(phoSCEta[recoPhoIdx])>=1.566 && TMath::Abs(phoSCEta[recoPhoIdx])<2.5) nmatch_EE++;
                }else{
                    if(tmp_isConverted==1){
                        nconv++;
                        //LOG_DEBUG(" event %d, photon Et %.2f,  tmp_isConverted \n", event, phoEt[recoPhoIdx]);
                    }
                }


                mcpt[recoPhoIdx]=tmp_mcPt_;
                mceta[recoPhoIdx]=tmp_mcEta_;
                mcphi[recoPhoIdx]=tmp_mcPhi_;
                mcCalIso04[recoPhoIdx]=tmp_mcCalIso04_;
                mcTrkIso04[recoPhoIdx]=tmp_mcTrkIso04_;
                match[recoPhoIdx]=tmp_isMatched;
                match_ele[recoPhoIdx]=tmp_isMatchedEle;
                converted[recoPhoIdx]=tmp_isConverted;
                mcmompid[recoPhoIdx]=tmp_momid;
            }

            //if(gjet15to6000 == 0) {
            //    h_truepho->Fill(nmatch+0.001);
            //    h_convpho->Fill(nconv+0.001);
            //}
        }


        //int npj=0;
        //int npp=0;
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
            if(!data.HasMC() && JETPD_PHOTONHLT==0 && phoFiredTrgs[i]==0) continue;
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
            //int pho_presel = 1;
            int pho_presel = PhotonPreselection(data, i, kFALSE);
            // Histogram filling section for checking  CSEV eff vs pt {{{
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

                    if( pho_presel == 1 ){
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
            // only for check CSEV eff vs pt end }}}



            if(pho_presel!=1) continue;
            if(JETPD_PHOTONHLT==1 && phoP4.DeltaR(trigger_jetP4)<0.7) continue;
            photon_list.push_back(i); 
            if(ONLY_LEADINGPHOTON==1 && photon_list.size()==1) break;
        }
        h_npho->Fill(photon_list.size());



        // find photon overlaps to electron
        if ( ELECTRONVETO && photon_list.size()>0 ) {
            TLorentzVector leadingPhoP4;
            leadingPhoP4.SetPtEtaPhiM(phoEt[photon_list[0]], phoEta[photon_list[0]], phoPhi[photon_list[0]], 0.);
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
        for(int j=0; j<nJet; j++) {
            if (photon_list.size() == 0 ) break;
            float jetjecunc = 1.;
            if(TMath::Abs(jetEta[j])<2.4 && jetPt[j]*jetjecunc>30.) {
                if( jetId[j] ) h_jetIDv->Fill(1.);	else h_jetIDv->Fill(0.);       
                jetP4.SetPtEtaPhiE(jetPt[j]*jetjecunc, jetEta[j], jetPhi[j], jetEn[j]);


                if( jetId[j] ) {
                    TLorentzVector leadingPhoP4;
                    leadingPhoP4.SetPtEtaPhiM(phoEt[photon_list[0]], phoEta[photon_list[0]], phoPhi[photon_list[0]], 0.);
                    h_dR_phojet->Fill(leadingPhoP4.DeltaR(jetP4));
                    if(leadingPhoP4.DeltaR(jetP4)>0.4){
                        if(jet_index<0) { jet_index = j; }
                        else { LOG_DEBUG("more than 1 jet pass the selection. Please check!\n"); }
                    }	    
                }    
            }  
        }

        // block to record preselection efficiency
        if ( data.HasMC() && nPho>0 )
        {
            // if no any photon selected, use leading photon
            // Check matching status : selRes->Draw("matchDeltaR", "GenPhoNumbering>0")
            // Check efficiency : calculate the number of selRes->Draw("mcPt", "GenPhoNumbering==0 && passed==1")
            //                                divided by  selRes->Draw("mcPt", "GenPhoNumbering==0").
            // Check Single photon HLT passing status
            int recoidx = photon_list.size()>0 ? photon_list[0] : 0;

            vector<int> phomcid = GenPhoIdxs(&data);
            for ( unsigned int midx = 0; midx < phomcid.size(); ++midx )
            {
                int mcIdx = phomcid[midx];

                float jet_pt_ = jet_index>=0 ? jetPt[jet_index] : -1;
                float jet_eta_= jet_index>=0 ? jetEta[jet_index]: -1;

                float dr = usefulFuncs::deltaR(phoEta[recoidx], phoPhi[recoidx], mcEta[mcIdx], mcPhi[mcIdx]);
                float dpt = (phoEt[recoidx] - mcPt[mcIdx])/mcPt[mcIdx];
                float mc_gen_iso_ = mcCalIsoDR04[mcIdx]+mcTrkIsoDR04[mcIdx];
                int hlt_bit_ = -1;

                for ( int iBit = 0; iBit < MAX_SINGLE_PHO_TRIG; ++iBit )
                    if ( ((phoFiredTrgs[recoidx]>>iBit)&1) == 1 )
                    { hlt_bit_ = iBit; break; }
                    
                selectionRes->Fill(
                        photon_list.size()>0,
                        mcPt[mcIdx],mcEta[mcIdx],
                        phoEt[recoidx],phoEta[recoidx],
                        jet_pt_,jet_eta_,
                        dr,dpt,mc_gen_iso_,
                        phoPFChIso[recoidx], hlt_bit_,
                        midx
                        );
            }
        }
        if(photon_list.size() < 1)
            continue;






        phoFillIdx = 0;
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
            calib_mva = -99.; //ch
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
            calib_chIso = 0.;


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
            //photon_jetID_ =0.;       //ch

            phoIDbit_ =0.;           //ch
            photonIDmva = -999.; //ch
            s4Full5x5=0.;
            leadingPUPtHat = 0;
            leadingLHEPt = 0;
            genHT_pthatDef = 0;
            calib_s4Full5x5=calib_r9Full5x5=calib_scPhiWidth=calib_scEtaWidth=calib_sieieFull5x5=calib_sieipFull5x5=calib_esEnergyOverSCRawEnergy = 0.;
            mygenweight = 0;
            for ( unsigned i=0; i<MAX_LHEPARTICLE; ++i )
                lhePID[i] = lheE[i]   = lhePx[i]  = lhePy[i]  = lhePz[i]  = 0;
            jetID = 0;
            jetPUIDbit = 0;
            //btagCalibs.InitVars();
            rho = data.GetFloat("rho"); //kk
            MET = pfMET;
            METPhi = pfMETPhi;
            puppiMET = puppiMET;
            puppiMETPhi = puppiMETPhi;
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
                LOG_DEBUG("JetIDMgr passed");


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
                LOG_DEBUG("Starting sec vtx info");

                if (hasSubVtxInfo) {
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
                }
                LOG_DEBUG("End of sec vtx info");

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
                mcMomPID_ = mcmompid[ipho];
                

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
                if ( PUmaxInfo && data.HasMC() )
                {
                    Float_t* pupthat_max = data.GetPtrFloat("pupthat_max");
                    Int_t    nPU = data.GetInt("nPUInfo");
                    Float_t maxpupthat = -1;
                    for ( int iPU = 0; iPU < nPU; ++iPU )
                        if ( maxpupthat < pupthat_max[iPU] )
                            maxpupthat = pupthat_max[iPU];
                    leadingPUPtHat = maxpupthat;

                    Float_t maxLHEPt = -1;
                    Float_t LHEPtSUM = 0.;
                    for ( int i = 0; i < nLHE; ++i )
                    {
                        float lhePt = sqrt( lhePx[i]*lhePx[i]+lhePy[i]*lhePy[i] );
                        LHEPtSUM += lhePt;
                        if ( maxLHEPt < lhePt )
                            maxLHEPt = lhePt;
                    }
                    leadingLHEPt = maxLHEPt;
                    genHT_pthatDef = LHEPtSUM / nLHE;
                }

                h2_mcPID_mcPt->Fill( mcPt_, 22.01, xsweight);
            }
            LOG_DEBUG("start to find seed time");
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
            calib_chIso = data.HasMC() ? -1 : CorrectedRho( chIsoRaw, rho, EffectiveArea_ChIso(recoSCEta,dataEra) );
            LOG_DEBUG("end of Rho Correction");


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
            s4Full5x5 = e2x2Full5x5 / e5x5Full5x5;
            esEnergyOverSCRawEnergy = esEn / rawE;

            phoIDbit_ = phoIDbit[ipho];
            LOG_DEBUG("start SScorr");
            if ( data.HasMC() && SScorr != nullptr )
            {

                    //SScorr->CalculateCorrections(&data, ipho);
                ShowerShapeCorrectionParameters_ggNtuple::loadVars(SScorr, &data, ipho);
                SScorr->CalculateCorrections();
                calib_r9Full5x5               = SScorr->Corrected(ShowerShapeCorrectionAdapter::r9                     );
                calib_s4Full5x5               = SScorr->Corrected(ShowerShapeCorrectionAdapter::s4                     );
                calib_sieieFull5x5            = SScorr->Corrected(ShowerShapeCorrectionAdapter::sieie                  );
                calib_sieipFull5x5            = SScorr->Corrected(ShowerShapeCorrectionAdapter::sieip                  );
                calib_scEtaWidth              = SScorr->Corrected(ShowerShapeCorrectionAdapter::etaWidth               );
                calib_scPhiWidth              = SScorr->Corrected(ShowerShapeCorrectionAdapter::phiWidth               );
                calib_esEnergyOverSCRawEnergy = SScorr->Corrected(ShowerShapeCorrectionAdapter::esEnergyOverSCRawEnergy);

                calib_mva = mvaloader.GetMVA_noIso(ipho,SScorr);
            }


            LOG_DEBUG("start load SScorr in mva");
            //mva = mvaloader.GetMVA_noIso(ipho, SScorr);
            //mva_nocorr = mvaloader.GetMVA_noIso(ipho);
            mva = mvaloader.GetMVA_noIso(ipho);
            //mva_nocorr = mvaloader.GetMVA_noIso(ipho,SScorr);
            LOG_DEBUG("start load SScorr in mva 1");
            LOG_DEBUG("end mva evaluation");
            
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
                else phoFillIdx++;
            }
        } // fill tree end

        h_nphoFiredTrgs->Fill(nphofiredtrgs);

    } // event loop end

    fout_->cd();
    outtree_->Write();

    if ( data.HasMC() )
    {
        selectionRes->Write();
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
    hdpt_signed->Write();
    hdR_ele->Write();
    hdpt_ele->Write();
    hdpt_ele_signed->Write();
    hdR_genjet->Write();
    hmcTrkIso->Write();
    hmcTrkIsoMini->Write();
    hmcTrkIsoMicro->Write();
    hmcCalIso->Write();
    hmcCalIsoMini->Write();
    hmcCalIsoMicro->Write();
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
    //h_npj->Write();
    h_jetPt->Write();
    h_pjmass->Write();
    //h_npp->Write();
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

void xPhotonHFJet(vector<string> pathes, Char_t oname[200] )
{ xPhotonHFJet(pathes, oname, "2016ReReco"); }


void xPhotonHFJet(Int_t dataset) {
  Char_t fname[200];
  XS=1.;
  vector <string> pathes;


 
  sprintf(fname, "/home/ltsai/ggtree_mc_1.root");
   pathes.push_back(fname);
    XS = 1.;
    //isMC=1;
    //gjetSignal=1;
    //gjet15to6000=1;

  Char_t oname[200];
  sprintf(oname, "output_job_PhotonHFJet_%d.root", dataset);

  xPhotonHFJet(pathes, oname);
  
}

void xPhotonHFJet(Char_t fname[200], Char_t oname[200], Double_t crosssection, int dowmnoption){
  //doWmn = dowmnoption;
  //isMC=1;
  vector <string> pathes;
  pathes.push_back(fname);
  XS = crosssection;
  xPhotonHFJet(pathes, oname);
  
}

//void xPhotonHFJet(std::string ipath, int outID)
void xPhotonHFJet(std::vector<std::string> ipath, int outID, const std::string dataEra)
{
   //Char_t fname[200];
   XS=1.;
   //vector <string> pathes;

   //pathes.push_back(ipath);
   XS = 1.;
   //isMC=1;
   //gjetSignal=1;
   //gjet15to6000=1;

   Char_t oname[200];
   sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

   xPhotonHFJet(ipath, oname, dataEra);

}
std::vector<int> _xphotonFunc_::GenPhoIdxs( TreeReader* event )
{
    Int_t* mcPID = event->GetPtrInt("mcPID");
    Float_t* mcPt = event->GetPtrFloat("mcPt");
    Int_t* mcMomPID = event->GetPtrInt("mcMomPID");
    Int_t nMC = event->GetInt("nMC");
    Float_t* mcEta  = event->GetPtrFloat("mcEta");
    Float_t* mcPhi  = event->GetPtrFloat("mcPhi");
    mcEta = mcEta; mcPhi = mcPhi; // prevent warning
    std::vector<int> phomcid;
    for (Int_t k=0; k<nMC; ++k) {
        if (mcPID[k] == 22 &&  mcPt[k]>15. && (mcMomPID[k] <= 22 || mcMomPID[k] == 5100039)) {
        if(verbose) { LOG_DEBUG("   true photon in generator pt %.2f, eta %.2f, phi %.2f \n", mcPt[k], mcEta[k], mcPhi[k]); }
        phomcid.push_back(k);
        }
    }
   return phomcid; 
}
std::vector<int> _xphotonFunc_::GenMuonIdxs( TreeReader* event )
{
    Int_t* mcPID = event->GetPtrInt("mcPID");
    Float_t* mcPt = event->GetPtrFloat("mcPt");
    //Int_t* mcMomPID = event->GetPtrInt("mcMomPID");
    Int_t nMC = event->GetInt("nMC");
    std::vector<int> muonmcid;
    for (Int_t k=0; k<nMC; ++k) {
        if (fabs(mcPID[k])==13 && mcPt[k]>20.){
            muonmcid.push_back(k);
        }
    }
    return muonmcid;
}
std::vector<int> _xphotonFunc_::GenEleIdxs( TreeReader* event )
{
    Int_t* mcPID = event->GetPtrInt("mcPID");
    //Float_t* mcPt = event->GetPtrFloat("mcPt");
    //Int_t* mcMomPID = event->GetPtrInt("mcMomPID");
    Int_t nMC = event->GetInt("nMC");
    std::vector<int> elemcid;
    for (Int_t k=0; k<nMC; ++k) {
        if (fabs(mcPID[k]) == 11 ){
            elemcid.push_back(k);
        }
    }
    return elemcid;
}

int _xphotonFunc_::TruthMatch_GenPhoton( TreeReader* event, int recoPhoIdx, std::vector<int> phomcid )
{
    Float_t* phoEt  = event->GetPtrFloat("phoEt");
    Float_t* phoEta = event->GetPtrFloat("phoEta");
    Float_t* phoPhi = event->GetPtrFloat("phoPhi");
    Float_t* mcPt   = event->GetPtrFloat("mcPt");
    Float_t* mcEta  = event->GetPtrFloat("mcEta");
    Float_t* mcPhi  = event->GetPtrFloat("mcPhi");
    Float_t* mcTrkIsoDR04 = event->GetPtrFloat("mcTrkIsoDR04");
    Float_t* mcCalIsoDR04 = event->GetPtrFloat("mcCalIsoDR04");
    //Int_t*   mcStatus     = event->GetPtrInt("mcStatus");
    Short_t* mcStatusFlag = event->GetPtrShort("mcStatusFlag");
    mcStatusFlag = mcStatusFlag; // prevent warning


    for ( int mcIdx : phomcid ) {
        float dr = usefulFuncs::deltaR(phoEta[recoPhoIdx], phoPhi[recoPhoIdx], mcEta[mcIdx], mcPhi[mcIdx]);
        float dpt = (phoEt[recoPhoIdx] - mcPt[mcIdx])/mcPt[mcIdx];
        if(dpt<CUT_DELTAPT)hdR->Fill(dr);
        if(dr<CUT_DELTAR)hdpt->Fill( fabs(dpt) );
        hmcCalIso->Fill(mcCalIsoDR04[mcIdx]); 
        hmcCalIsoMini->Fill(mcCalIsoDR04[mcIdx]); 
        hmcCalIsoMicro->Fill(mcCalIsoDR04[mcIdx]); 
        hmcTrkIso->Fill(mcTrkIsoDR04[mcIdx]); 
        hmcTrkIsoMini->Fill(mcTrkIsoDR04[mcIdx]); 
        hmcTrkIsoMicro->Fill(mcTrkIsoDR04[mcIdx]); 

        if(verbose) { LOG_DEBUG("  MCparticle %d, dr %.2f, dpt %.2f \n", mcIdx, dr, dpt); }
        if(verbose) { LOG_DEBUG("     status %d, caliso %.2f, trkiso %.2f \n", mcStatusFlag[mcIdx], mcCalIsoDR04[mcIdx], mcTrkIsoDR04[mcIdx]); }
        if (dr < CUT_DELTAR && dpt < CUT_DELTAPT){
            if ( mcCalIsoDR04[mcIdx]<5.0 ){ //for gammajet photon pythia	      
                if(verbose) { LOG_DEBUG("  mc matched !!! \n"); }
                return mcIdx;
            }
        }
    }
    return -1;
}
int _xphotonFunc_::TruthMatch_GenConvertedPho( TreeReader* event, int recoPhoIdx, std::vector<int> elemcid )
{
    Float_t* phoEt  = event->GetPtrFloat("phoEt");
    Float_t* phoEta = event->GetPtrFloat("phoEta");
    Float_t* phoPhi = event->GetPtrFloat("phoPhi");
    //Float_t* mcPt   = event->GetPtrFloat("mcPt");
    Float_t* mcEta  = event->GetPtrFloat("mcEta");
    Float_t* mcPhi  = event->GetPtrFloat("mcPhi");
    Float_t* mcTrkIsoDR04 = event->GetPtrFloat("mcTrkIsoDR04");
    Float_t* mcCalIsoDR04 = event->GetPtrFloat("mcCalIsoDR04");
    Float_t* mcMomPt      = event->GetPtrFloat("mcMomPt");
    Int_t*   mcMomPID     = event->GetPtrInt("mcMomPID");
    //Int_t*   mcStatus     = event->GetPtrInt("mcStatus");
    //Short_t* mcStatusFlag = event->GetPtrShort("mcStatusFlag");

    for ( int mcIdx : elemcid ) {
        if (mcMomPID[mcIdx] == 22) {
            float dr = usefulFuncs::deltaR(phoEta[recoPhoIdx], phoPhi[recoPhoIdx], mcEta[mcIdx], mcPhi[mcIdx]);
            float dpt = (phoEt[recoPhoIdx] - mcMomPt[mcIdx])/mcMomPt[mcIdx];
            hdR_ele->Fill(dr);
            hdpt_ele->Fill( fabs(dpt) );
            if (dr < CUT_DELTAR && dpt < CUT_DELTAPT && (mcCalIsoDR04[mcIdx]+mcTrkIsoDR04[mcIdx])<5.0 ){
                return mcIdx;
            }
        }
    }
    return -1;
}
void ShowInfo()
{
    printf("==================== Information for this run :       ==================\n");
    printf("== Only keep leading photon : %s                      ==================\n", ONLY_LEADINGPHOTON ? "Yes": "No ");
    printf("== Keep information to secondary vertex ? %3s         ==================\n", hasSubVtxInfo ? "Yes": "NO");
    printf("== Additional jet scale factor information ? %3s      ==================\n", testJetSF ? "Yes": "NO");
    printf("== Use select a specific Single photon HLT ? %3s      ==================\n", USEHLT ? "Yes": "NO");
    printf("== Veto electron in photon collection ? %3s           ==================\n", ELECTRONVETO ? "Yes": "NO" );
    printf("== I have told this run use Jet primary dataset ? %3s  =================\n", JETPD_PHOTONHLT? "Yes":"NO");
    printf("========================================================================\n");
}

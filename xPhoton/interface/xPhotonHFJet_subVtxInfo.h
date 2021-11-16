#ifndef __xphoton_anslysis__
#define __xphoton_anslysis__
#include <vector>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TProfile.h>

#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"

static Int_t MINITREE=1;
static Double_t XS=1.;
static Bool_t verbose=false;
static Int_t JETPD_PHOTONHLT=0;
static Int_t ONLY_LEADINGPHOTON=1;

static Int_t isMC=0;
static Int_t data25ns=1;
static Int_t data50ns=0;
static Int_t qstar=1;
static Int_t gjet15to6000=0;
static Int_t genHTcut=0;
static Int_t gjetSignal=0;

static bool hasSubVtxInfo = true;
static bool testJetSF = true;
static bool ELECTRONVETO = false;
static bool USEHLT = false;


void xPhotonHFJet(
        vector<string> pathes,
        Char_t oname[200]);


void xPhotonHFJet(
        Int_t dataset = 0);
void xPhotonHFJet(
        Char_t fname[200],
        Char_t oname[200],
        Double_t crosssection=1.,
        int dowmnoption=0);

void xPhotonHFJet(
        std::string ipath,
        int outID);

static TH1F* h_subVtxPt    ;
static TH1F* h_subVtxMass  ;
static TH1F* h_subVtx3DVal ;
static TH1F* h_subVtx3DErr ;
static TH1F* h_subVtxNtrks ;

static TH1F *h_hasGoodVtx ;
static TH1F *hpthat ;
static TH1F *hpthat_wide ;
static TH1F *hdpt ;
static TH1F *hdR ;

static TH1F *hdpt_ele ;
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
static TH1F *h_npj ;
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
static TH1F *h_npp ;
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


#endif

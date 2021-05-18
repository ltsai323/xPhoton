#ifndef __xphoton_anslysis__
#define __xphoton_anslysis__
#include <vector>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>

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

static bool hasSubVtxInfo = false;


Double_t deltaPhi(Double_t phi1, Double_t phi2);
Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);

void xPhotonHFJet(vector<string> pathes, Char_t oname[200]);


void xPhotonHFJet(Int_t dataset = 0);
void xPhotonHFJet(Char_t fname[200], Char_t oname[200], Double_t crosssection=1., int dowmnoption=0);

void xPhotonHFJet(std::string ipath, int outID);
#endif

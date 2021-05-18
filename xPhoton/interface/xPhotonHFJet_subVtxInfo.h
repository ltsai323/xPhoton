#ifndef __xphoton_anslysis__
#define __xphoton_anslysis__
#include <vector>
#include <TSystem.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
using namespace std;

#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/logger.h"


Int_t MINITREE=1;
Double_t XS=1.;
Bool_t verbose=false;
Int_t JETPD_PHOTONHLT=0;
Int_t ONLY_LEADINGPHOTON=1;

Int_t isMC=0;
Int_t data25ns=1;
Int_t data50ns=0;
Int_t qstar=1;
Int_t gjet15to6000=0;
Int_t genHTcut=0;
Int_t gjetSignal=0;

bool hasSubVtxInfo = false;

Double_t deltaPhi(Double_t phi1, Double_t phi2);
Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);

void xPhotonHFJet(vector<string> pathes, Char_t oname[200]);


void xPhotonHFJet(Int_t dataset = 0);
void xPhotonHFJet(Char_t fname[200], Char_t oname[200], Double_t crosssection=1., int dowmnoption=0);

void xPhotonHFJet(std::string ipath, int outID);
#endif

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


void ShowInfo();

void xPhotonHFJet(
        vector<string> pathes,
        Char_t oname[200],
        const std::string dataEra);
void xPhotonHFJet(
        vector<string> pathes,
        Char_t oname[200]
        );


void xPhotonHFJet(
        Int_t dataset = 0);
void xPhotonHFJet(
        Char_t fname[200],
        Char_t oname[200],
        Double_t crosssection=1.,
        int dowmnoption=0);

void xPhotonHFJet(
        std::vector<std::string> ipath,
        int outID,
        const std::string dataEra);



#endif

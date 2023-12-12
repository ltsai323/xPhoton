#ifndef __xphoton_anslysis_MCFirst__
#define __xphoton_anslysis_MCFirst__
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

void xPhotonHFJet_MCFirst(
        vector<string> pathes,
        Char_t oname[200],
        const std::string dataEra);
void xPhotonHFJet_MCFirst(
        vector<string> pathes,
        Char_t oname[200]
        );


void xPhotonHFJet_MCFirst(
        Int_t dataset = 0);
void xPhotonHFJet_MCFirst(
        Char_t fname[200],
        Char_t oname[200],
        Double_t crosssection=1.,
        int dowmnoption=0);

void xPhotonHFJet_MCFirst(
        std::vector<std::string> ipath,
        int outID,
        const std::string dataEra);



namespace _xphoton_MCFirstFunc_{
std::vector<int> GenPhoIdxs( TreeReader* event );
std::vector<int> GenMuonIdxs( TreeReader* event );
std::vector<int> GenEleIdxs( TreeReader* event );
int TruthMatch_GenPhoton( TreeReader* event, int recoPhoIdx, const std::vector<int>& phomcid );
int TruthMatch_GenConvertedPho( TreeReader* event, int recoPhoIdx, const std::vector<int>& elemcid );
void FillStatus(TH1* hist, float val) { hist->Fill(val+0.001); }
};
#endif

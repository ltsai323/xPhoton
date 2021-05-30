#ifndef photonpreselection
#define photonpreselection
#include <TMath.h>
#include <TMVA/Reader.h>
/* #include <TRandom3.h> */
#include <TFile.h>
#include <TGraph.h>
#include <string>
#include "xPhoton/xPhoton/interface/untuplizer.h"

        
// pre-selection of photon.
Int_t PhotonPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);

Int_t PhotonSkimPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);
Int_t HggPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);

void select_photon(Int_t iWP, TreeReader &data, std::vector<int>& accepted);

float select_photon_mva(TreeReader &data, Int_t i, TGraph *tgr[20]);

float select_photon_mvanoIso(TreeReader &data, Int_t i, TGraph *tgr[20]);


float select_photon_mva_hgg(TreeReader &data, Int_t i);
#endif

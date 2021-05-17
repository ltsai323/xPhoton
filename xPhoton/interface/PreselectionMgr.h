#ifndef __PRESELECTIONMGR_H__
#define __PRESELECTIONMGR_H__
#include "xPhoton/xPhoton/interface/untuplizer.h"

namespace PreselectionMgr {
    /*
    std::vector<int> ElectronIDCutBased2015(TreeReader &data, Int_t WP, vector<int> &accepted);
    void TightMuons2015(TreeReader &data, vector<int> &accepted);

    std::string MVAweightfile(int isEndcap, int year);
    Int_t       PhotonPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);
    Int_t       PhotonSkimPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);
    Int_t       HggPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto=kTRUE);
    void        select_photon(Int_t iWP, TreeReader &data, vector<int>& accepted);
    float       select_photon_mva(TreeReader &data, Int_t i, TGraph *tgr[20]);
    float       select_photon_mvanoIso(TreeReader &data, Int_t i, TGraph *tgr[20]);
    float       select_photon_mva_hgg(TreeReader &data, Int_t i);
    */

    bool passed(int ID);
    int _ElectronID_CutBased_2015(TreeReader& data, Int_t WP, int idx);
    int _MuonID_Tight_2015(TreeReader& data, int idx);
    int _PhotonID_CutBased_2015(TreeReader& data, int idx, bool eleVeto);

    std::vector<int> GetElectrons(TreeReader& data, Int_t WP);
    std::vector<int> GetElectronsVeto(TreeReader& data);
    std::vector<int> GetElectronsLoose(TreeReader& data);
    std::vector<int> GetElectronsMedium(TreeReader& data);
    std::vector<int> GetElectronsTight(TreeReader& data);

    std::vector<int> GetMuonsTight(TreeReader& data);
    std::vector<int> GetPhotons(TreeReader& data, bool eleVeto);
};

/*
namespace mvaMgr {
    std::string MVAweightfile(int isEndCap, int year);
};
*/
#endif

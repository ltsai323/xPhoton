#ifndef __PRESELECTIONMGR_H__
#define __PRESELECTIONMGR_H__

namespace PreselectionMgr {
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
};
#endif

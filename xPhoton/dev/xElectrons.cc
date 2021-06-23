#include "xPhoton/xPhoton/interface/xElectrons.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/MuonSelections.h"
#include "xPhoton/xPhoton/interface/ElectronSelections.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"


void xElectrons(
        std::vector<std::string> pathes,
        char oname[200] )
{
    TreeReader data(pathes);

    TFile *fout_;
    fout_ = new TFile(oname,"recreate");

    TTree *outtree_ = new TTree("t", "mini tree");
    
    /*
    enum varF {
        recoPt,
        recoEta,
        recoPhi,

    Float_t pthat_, mcPt_, mcEta_, mcPhi_, recoPt, recoPtCalib, recoEta, recoPhi, recoSCEta, r9;
    Float_t mcCalIso04_, mcTrkIso04_;
    Float_t puwei_=1.;
    Float_t r9Full5x5;
    Float_t HoverE, chIsoRaw, phoIsoRaw, nhIsoRaw, chWorstIso;
    Float_t rho;

    Float_t e5x5, rawE, scEtaWidth, scPhiWidth, esRR, esEn, mva, mva_nocorr,  photonIDmva;
    Float_t sieieFull5x5, sipipFull5x5, sieipFull5x5, e2x2Full5x5,  e5x5Full5x5;

    Float_t xsweight=XS;
    Float_t  MET,   METPhi;
    Float_t jetPt_, jetEta_, jetPhi_, jetY_, jetJECUnc_;
    Float_t jetGenJetPt_, jetGenJetEta_, jetGenJetPhi_, jetGenJetY_, genHT_;
    Float_t jetCSV2BJetTags_, jetDeepCSVTags_b_, jetDeepCSVTags_bb_, jetDeepCSVTags_c_, jetDeepCSVTags_udsg_;
    Float_t jetDeepFlavourTags_b_;
    Float_t jetDeepFlavourTags_c_;
    Float_t jetDeepFlavourTags_g_;
    Float_t jetDeepFlavourTags_lepb_;
    Float_t jetDeepFlavourTags_bb_;
    Float_t jetDeepFlavourTags_uds_;
    Float_t jetDeepCSVDiscriminatorTags_BvsAll_;
    Float_t jetDeepCSVDiscriminatorTags_CvsB_;
    Float_t jetDeepCSVDiscriminatorTags_CvsL_;
    */

    
    for (Long64_t ev = 0; ev < data.GetEntriesFast(); ev++)
    {
        data.GetEntry(ev);
        // do something
        outtree_->Fill();
    }


    fout_->cd();
    outtree_->Write();
    fout_->Close();
    LOG_INFO("All %lld Events processed", data.GetEntriesFast());
}
void xElectrons(std::string ipath, int outID)
{
   char fname[200];
   std::vector<std::string> pathes;

   pathes.push_back(ipath);

   char oname[200];
   sprintf(oname, "output_job_PhotonHFJet_%d.root", outID);

   xElectrons(pathes, oname);
}


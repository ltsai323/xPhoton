//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Mar  2 17:27:11 2023 by ROOT version 6.10/09
// from TTree t/mini tree
// found on file: /home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/sigMC_madgraph_ctagReshaped.root
//////////////////////////////////////////////////////////

#ifndef MakeHistoSIG_h
#define MakeHistoSIG_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class MakeHistoSIG {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         jetSubVtxPt;
   Float_t         jetSubVtxMass;
   Float_t         jetSubVtx3DVal;
   Float_t         jetSubVtx3DErr;
   Int_t           jetSubVtxNtrks;
   Int_t           run;
   Long64_t        event;
   Bool_t          isData;
   Long64_t        phoFiredTrgs;
   Float_t         pthat;
   Float_t         genHT;
   Float_t         mcPt;
   Float_t         mcEta;
   Float_t         mcPhi;
   Float_t         mcCalIso04;
   Float_t         mcTrkIso04;
   Float_t         mcMomPID;
   Float_t         mcTrkIso;
   Float_t         mcCalIso;
   Float_t         matchDR;
   Float_t         matchDPT;
   Float_t         recoPt;
   Float_t         recoPtCalib;
   Float_t         recoEta;
   Float_t         recoPhi;
   Float_t         recoSCEta;
   Float_t         r9;
   Float_t         s4Full5x5;
   Float_t         esEnergyOverSCRawEnergy;
   Int_t           isMatched;
   Int_t           isMatchedEle;
   Int_t           isConverted;
   Int_t           nVtx;
   Int_t           nPU;
   Float_t         puwei;
   Int_t           eleVeto;
   Float_t         HoverE;
   Float_t         chIsoRaw;
   Float_t         chWorstRaw;
   Float_t         phoIsoRaw;
   Float_t         nhIsoRaw;
   Float_t         rho;
   Float_t         calib_chIso;
   Float_t         rawE;
   Float_t         scEtaWidth;
   Float_t         scPhiWidth;
   Float_t         esRR;
   Float_t         esEn;
   Float_t         mva;
   Float_t         calib_mva;
   Float_t         photonIDmva;
   Int_t           phoIDbit;
   Float_t         MET;
   Float_t         METPhi;
   Int_t           phohasPixelSeed;
   Float_t         sieieFull5x5;
   Float_t         sieipFull5x5;
   Float_t         sipipFull5x5;
   Float_t         r9Full5x5;
   Float_t         e2x2Full5x5;
   Float_t         e5x5Full5x5;
   Float_t         jetPt;
   Float_t         jetEta;
   Float_t         jetPhi;
   Float_t         jetY;
   Float_t         jetJECUnc;
   Float_t         jetGenJetPt;
   Float_t         jetGenJetEta;
   Float_t         jetGenJetPhi;
   Float_t         jetGenJetY;
   Float_t         jetCSV2BJetTags;
   Float_t         jetDeepCSVTags_b;
   Float_t         jetDeepCSVTags_bb;
   Float_t         jetDeepCSVTags_c;
   Float_t         jetDeepCSVTags_udsg;
   Float_t         jetDeepFlavourTags_b;
   Float_t         jetDeepFlavourTags_c;
   Float_t         jetDeepFlavourTags_g;
   Float_t         jetDeepFlavourTags_lepb;
   Float_t         jetDeepFlavourTags_bb;
   Float_t         jetDeepFlavourTags_uds;
   Float_t         jetDeepCSVDiscriminatorTags_BvsAll;
   Float_t         jetDeepCSVDiscriminatorTags_CvsB;
   Float_t         jetDeepCSVDiscriminatorTags_CvsL;
   Int_t           jetPartonID;
   Int_t           jetGenPartonID;
   Int_t           jetHadFlvr;
   Int_t           jetGenPartonMomID;
   Float_t         calib_scEtaWidth;
   Float_t         calib_scPhiWidth;
   Float_t         calib_r9Full5x5;
   Float_t         calib_s4Full5x5;
   Float_t         calib_sieieFull5x5;
   Float_t         calib_sieipFull5x5;
   Float_t         calib_esEnergyOverSCRawEnergy;
   Int_t           nLHE;
   Int_t           lhePID[1];   //[nLHE]
   Float_t         lheE[1];   //[nLHE]
   Float_t         lhePx[1];   //[nLHE]
   Float_t         lhePy[1];   //[nLHE]
   Float_t         lhePz[1];   //[nLHE]
   Float_t         genWeight;
   Int_t           jetID;
   Int_t           jetPUIDbit;
   Float_t         xsweight;
   Float_t         crossSection;
   Float_t         integratedLuminosity;
   Float_t         integratedGenWeight;
   Float_t         mcweight;
   Int_t           isQCD;
   Float_t         jetSF_DeepCSV_central;
   Float_t         jetSF_DeepCSV_down_cferr1;
   Float_t         jetSF_DeepCSV_down_cferr2;
   Float_t         jetSF_DeepCSV_down_hf;
   Float_t         jetSF_DeepCSV_down_lf;
   Float_t         jetSF_DeepCSV_up_cferr1;
   Float_t         jetSF_DeepCSV_up_cferr2;
   Float_t         jetSF_DeepCSV_up_hf;
   Float_t         jetSF_DeepCSV_up_lf;
   Float_t         jetSF_DeepFlavour_central;
   Float_t         jetSF_DeepFlavour_down_cferr1;
   Float_t         jetSF_DeepFlavour_down_cferr2;
   Float_t         jetSF_DeepFlavour_down_hf;
   Float_t         jetSF_DeepFlavour_down_lf;
   Float_t         jetSF_DeepFlavour_up_cferr1;
   Float_t         jetSF_DeepFlavour_up_cferr2;
   Float_t         jetSF_DeepFlavour_up_hf;
   Float_t         jetSF_DeepFlavour_up_lf;
   Float_t         DeepCSV_CvsB;
   Float_t         DeepCSV_CvsL;
   Float_t         DeepCSV_bScore;
   Float_t         DeepCSV_ctagWeight_central;
   Float_t         DeepCSV_ctagWeight_PUWeightUp;
   Float_t         DeepCSV_ctagWeight_StatUp;
   //Float_t         DeepCSV_ctagWeight_TotalUncDown;
   Float_t         DeepCSV_ctagWeight_PUWeightDown;
   Float_t         DeepCSV_ctagWeight_StatDown;
   //Float_t         DeepCSV_ctagWeight_TotalUncDown;
   Float_t         DeepFlavour_CvsB;
   Float_t         DeepFlavour_CvsL;
   Float_t         DeepFlavour_bScore;
   Float_t         DeepFlavour_ctagWeight_central;
   Float_t         DeepFlavour_ctagWeight_PUWeightUp;
   Float_t         DeepFlavour_ctagWeight_StatUp;
   ////Float_t         DeepFlavour_ctagWeight_TotalUncDown;
   Float_t         DeepFlavour_ctagWeight_PUWeightDown;
   Float_t         DeepFlavour_ctagWeight_StatDown;
   //Float_t         DeepFlavour_ctagWeight_TotalUncDown;

   // List of branches
   TBranch        *b_jetSubVtxPt;   //!
   TBranch        *b_jetSubVtxMass;   //!
   TBranch        *b_jetSubVtx3DVal;   //!
   TBranch        *b_jetSubVtx3DErr;   //!
   TBranch        *b_jetSubVtxNtrks;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_phoFiredTrgs;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_genHT;   //!
   TBranch        *b_mcPt;   //!
   TBranch        *b_mcEta;   //!
   TBranch        *b_mcPhi;   //!
   TBranch        *b_mcCalIso04;   //!
   TBranch        *b_mcTrkIso04;   //!
   TBranch        *b_mcMomPID;   //!
   TBranch        *b_mcTrkIso;   //!
   TBranch        *b_mcCalIso;   //!
   TBranch        *b_matchDR;   //!
   TBranch        *b_matchDPT;   //!
   TBranch        *b_recoPt;   //!
   TBranch        *b_recoPtCalib;   //!
   TBranch        *b_recoEta;   //!
   TBranch        *b_recoPhi;   //!
   TBranch        *b_recoSCEta;   //!
   TBranch        *b_r9;   //!
   TBranch        *b_s4Full5x5;   //!
   TBranch        *b_esEnergyOverSCRawEnergy;   //!
   TBranch        *b_isMatched;   //!
   TBranch        *b_isMatchedEle;   //!
   TBranch        *b_isConverted;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_nPU;   //!
   TBranch        *b_puwei;   //!
   TBranch        *b_eleVeto;   //!
   TBranch        *b_HoverE;   //!
   TBranch        *b_chIsoRaw;   //!
   TBranch        *b_chWorstIso;   //!
   TBranch        *b_phoIsoRaw;   //!
   TBranch        *b_nhIsoRaw;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_calib_chIso;   //!
   TBranch        *b_rawE;   //!
   TBranch        *b_scEtaWidth;   //!
   TBranch        *b_scPhiWidth;   //!
   TBranch        *b_esRR;   //!
   TBranch        *b_esEn;   //!
   TBranch        *b_mva;   //!
   TBranch        *b_calib_mva;   //!
   TBranch        *b_photonIDmva;   //!
   TBranch        *b_phoIDbit;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_METPhi;   //!
   TBranch        *b_phohasPixelSeed;   //!
   TBranch        *b_sieieFull5x5;   //!
   TBranch        *b_sieipFull5x5;   //!
   TBranch        *b_sipipFull5x5;   //!
   TBranch        *b_r9Full5x5;   //!
   TBranch        *b_e2x2Full5x5;   //!
   TBranch        *b_e5x5Full5x5;   //!
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetY;   //!
   TBranch        *b_jetJECUnc;   //!
   TBranch        *b_jetGenJetPt;   //!
   TBranch        *b_jetGenJetEta;   //!
   TBranch        *b_jetGenJetPhi;   //!
   TBranch        *b_jetGenJetY;   //!
   TBranch        *b_jetCSV2BJetTags;   //!
   TBranch        *b_jetDeepCSVTags_b;   //!
   TBranch        *b_jetDeepCSVTags_bb;   //!
   TBranch        *b_jetDeepCSVTags_c;   //!
   TBranch        *b_jetDeepCSVTags_udsg;   //!
   TBranch        *b_jetDeepFlavourTags_b;   //!
   TBranch        *b_jetDeepFlavourTags_c;   //!
   TBranch        *b_jetDeepFlavourTags_g;   //!
   TBranch        *b_jetDeepFlavourTags_lepb;   //!
   TBranch        *b_jetDeepFlavourTags_bb;   //!
   TBranch        *b_jetDeepFlavourTags_uds;   //!
   TBranch        *b_jetDeepCSVDiscriminatorTags_BvsAll;   //!
   TBranch        *b_jetDeepCSVDiscriminatorTags_CvsB;   //!
   TBranch        *b_jetDeepCSVDiscriminatorTags_CvsL;   //!
   TBranch        *b_jetPartonID;   //!
   TBranch        *b_jetGenPartonID;   //!
   TBranch        *b_jetHadFlvr;   //!
   TBranch        *b_jetGenPartonMomID;   //!
   TBranch        *b_calib_scEtaWidth;   //!
   TBranch        *b_calib_scPhiWidth;   //!
   TBranch        *b_calib_r9Full5x5;   //!
   TBranch        *b_calib_s4Full5x5;   //!
   TBranch        *b_calib_sieieFull5x5;   //!
   TBranch        *b_calib_sieipFull5x5;   //!
   TBranch        *b_calib_esEnergyOverSCRawEnergy;   //!
   TBranch        *b_nLHE;   //!
   TBranch        *b_lhePID;   //!
   TBranch        *b_lheE;   //!
   TBranch        *b_lhePx;   //!
   TBranch        *b_lhePy;   //!
   TBranch        *b_lhePz;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_jetID;   //!
   TBranch        *b_jetPUIDbit;   //!
   TBranch        *b_xsweight;   //!
   TBranch        *b_crossSection;   //!
   TBranch        *b_integratedLuminosity;   //!
   TBranch        *b_integratedGenWeight;   //!
   TBranch        *b_mcweight;   //!
   TBranch        *b_isQCD;   //!
   TBranch        *b_jetSF_DeepCSV_central;   //!
   TBranch        *b_jetSF_DeepCSV_down_cferr1;   //!
   TBranch        *b_jetSF_DeepCSV_down_cferr2;   //!
   TBranch        *b_jetSF_DeepCSV_down_hf;   //!
   TBranch        *b_jetSF_DeepCSV_down_lf;   //!
   TBranch        *b_jetSF_DeepCSV_up_cferr1;   //!
   TBranch        *b_jetSF_DeepCSV_up_cferr2;   //!
   TBranch        *b_jetSF_DeepCSV_up_hf;   //!
   TBranch        *b_jetSF_DeepCSV_up_lf;   //!
   TBranch        *b_jetSF_DeepFlavour_central;   //!
   TBranch        *b_jetSF_DeepFlavour_down_cferr1;   //!
   TBranch        *b_jetSF_DeepFlavour_down_cferr2;   //!
   TBranch        *b_jetSF_DeepFlavour_down_hf;   //!
   TBranch        *b_jetSF_DeepFlavour_down_lf;   //!
   TBranch        *b_jetSF_DeepFlavour_up_cferr1;   //!
   TBranch        *b_jetSF_DeepFlavour_up_cferr2;   //!
   TBranch        *b_jetSF_DeepFlavour_up_hf;   //!
   TBranch        *b_jetSF_DeepFlavour_up_lf;   //!
   TBranch        *b_DeepCSV_CvsB;   //!
   TBranch        *b_DeepCSV_CvsL;   //!
   TBranch        *b_DeepCSV_bScore;   //!
   TBranch        *b_DeepCSV_ctagWeight_central;   //!
   TBranch        *b_DeepCSV_ctagWeight_PUWeightUp;   //!
   TBranch        *b_DeepCSV_ctagWeight_StatUp;   //!
   TBranch        *b_DeepCSV_ctagWeight_TotalUncUp;   //!
   TBranch        *b_DeepCSV_ctagWeight_PUWeightDown;   //!
   TBranch        *b_DeepCSV_ctagWeight_StatDown;   //!
   TBranch        *b_DeepCSV_ctagWeight_TotalUncDown;   //!
   TBranch        *b_DeepFlavour_CvsB;   //!
   TBranch        *b_DeepFlavour_CvsL;   //!
   TBranch        *b_DeepFlavour_bScore;   //!
   TBranch        *b_DeepFlavour_ctagWeight_central;   //!
   TBranch        *b_DeepFlavour_ctagWeight_PUWeightUp;   //!
   TBranch        *b_DeepFlavour_ctagWeight_StatUp;   //!
   TBranch        *b_DeepFlavour_ctagWeight_TotalUncUp;   //!
   TBranch        *b_DeepFlavour_ctagWeight_PUWeightDown;   //!
   TBranch        *b_DeepFlavour_ctagWeight_StatDown;   //!
   TBranch        *b_DeepFlavour_ctagWeight_TotalUncDown;   //!

   MakeHistoSIG(TTree *tree=0);
   virtual ~MakeHistoSIG();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MakeHistoSIG_cxx
MakeHistoSIG::MakeHistoSIG(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/sigMC_madgraph_ctagReshaped.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/sigMC_madgraph_ctagReshaped.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree);
}

MakeHistoSIG::~MakeHistoSIG()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MakeHistoSIG::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MakeHistoSIG::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void MakeHistoSIG::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("jetSubVtxPt", &jetSubVtxPt, &b_jetSubVtxPt);
   fChain->SetBranchAddress("jetSubVtxMass", &jetSubVtxMass, &b_jetSubVtxMass);
   fChain->SetBranchAddress("jetSubVtx3DVal", &jetSubVtx3DVal, &b_jetSubVtx3DVal);
   fChain->SetBranchAddress("jetSubVtx3DErr", &jetSubVtx3DErr, &b_jetSubVtx3DErr);
   fChain->SetBranchAddress("jetSubVtxNtrks", &jetSubVtxNtrks, &b_jetSubVtxNtrks);
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("phoFiredTrgs", &phoFiredTrgs, &b_phoFiredTrgs);
   fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
   fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
   fChain->SetBranchAddress("mcPt", &mcPt, &b_mcPt);
   fChain->SetBranchAddress("mcEta", &mcEta, &b_mcEta);
   fChain->SetBranchAddress("mcPhi", &mcPhi, &b_mcPhi);
   fChain->SetBranchAddress("mcCalIso04", &mcCalIso04, &b_mcCalIso04);
   fChain->SetBranchAddress("mcTrkIso04", &mcTrkIso04, &b_mcTrkIso04);
   fChain->SetBranchAddress("mcMomPID", &mcMomPID, &b_mcMomPID);
   fChain->SetBranchAddress("mcTrkIso", &mcTrkIso, &b_mcTrkIso);
   fChain->SetBranchAddress("mcCalIso", &mcCalIso, &b_mcCalIso);
   fChain->SetBranchAddress("matchDR", &matchDR, &b_matchDR);
   fChain->SetBranchAddress("matchDPT", &matchDPT, &b_matchDPT);
   fChain->SetBranchAddress("recoPt", &recoPt, &b_recoPt);
   fChain->SetBranchAddress("recoPtCalib", &recoPtCalib, &b_recoPtCalib);
   fChain->SetBranchAddress("recoEta", &recoEta, &b_recoEta);
   fChain->SetBranchAddress("recoPhi", &recoPhi, &b_recoPhi);
   fChain->SetBranchAddress("recoSCEta", &recoSCEta, &b_recoSCEta);
   fChain->SetBranchAddress("r9", &r9, &b_r9);
   fChain->SetBranchAddress("s4Full5x5", &s4Full5x5, &b_s4Full5x5);
   fChain->SetBranchAddress("esEnergyOverSCRawEnergy", &esEnergyOverSCRawEnergy, &b_esEnergyOverSCRawEnergy);
   fChain->SetBranchAddress("isMatched", &isMatched, &b_isMatched);
   fChain->SetBranchAddress("isMatchedEle", &isMatchedEle, &b_isMatchedEle);
   fChain->SetBranchAddress("isConverted", &isConverted, &b_isConverted);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   fChain->SetBranchAddress("nPU", &nPU, &b_nPU);
   fChain->SetBranchAddress("puwei", &puwei, &b_puwei);
   fChain->SetBranchAddress("eleVeto", &eleVeto, &b_eleVeto);
   fChain->SetBranchAddress("HoverE", &HoverE, &b_HoverE);
   fChain->SetBranchAddress("chIsoRaw", &chIsoRaw, &b_chIsoRaw);
   fChain->SetBranchAddress("chWorstRaw", &chWorstRaw, &b_chWorstIso);
   fChain->SetBranchAddress("phoIsoRaw", &phoIsoRaw, &b_phoIsoRaw);
   fChain->SetBranchAddress("nhIsoRaw", &nhIsoRaw, &b_nhIsoRaw);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("calib_chIso", &calib_chIso, &b_calib_chIso);
   fChain->SetBranchAddress("rawE", &rawE, &b_rawE);
   fChain->SetBranchAddress("scEtaWidth", &scEtaWidth, &b_scEtaWidth);
   fChain->SetBranchAddress("scPhiWidth", &scPhiWidth, &b_scPhiWidth);
   fChain->SetBranchAddress("esRR", &esRR, &b_esRR);
   fChain->SetBranchAddress("esEn", &esEn, &b_esEn);
   fChain->SetBranchAddress("mva", &mva, &b_mva);
   fChain->SetBranchAddress("calib_mva", &calib_mva, &b_calib_mva);
   fChain->SetBranchAddress("photonIDmva", &photonIDmva, &b_photonIDmva);
   fChain->SetBranchAddress("phoIDbit", &phoIDbit, &b_phoIDbit);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("METPhi", &METPhi, &b_METPhi);
   fChain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed, &b_phohasPixelSeed);
   fChain->SetBranchAddress("sieieFull5x5", &sieieFull5x5, &b_sieieFull5x5);
   fChain->SetBranchAddress("sieipFull5x5", &sieipFull5x5, &b_sieipFull5x5);
   fChain->SetBranchAddress("sipipFull5x5", &sipipFull5x5, &b_sipipFull5x5);
   fChain->SetBranchAddress("r9Full5x5", &r9Full5x5, &b_r9Full5x5);
   fChain->SetBranchAddress("e2x2Full5x5", &e2x2Full5x5, &b_e2x2Full5x5);
   fChain->SetBranchAddress("e5x5Full5x5", &e5x5Full5x5, &b_e5x5Full5x5);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetY", &jetY, &b_jetY);
   fChain->SetBranchAddress("jetJECUnc", &jetJECUnc, &b_jetJECUnc);
   fChain->SetBranchAddress("jetGenJetPt", &jetGenJetPt, &b_jetGenJetPt);
   fChain->SetBranchAddress("jetGenJetEta", &jetGenJetEta, &b_jetGenJetEta);
   fChain->SetBranchAddress("jetGenJetPhi", &jetGenJetPhi, &b_jetGenJetPhi);
   fChain->SetBranchAddress("jetGenJetY", &jetGenJetY, &b_jetGenJetY);
   fChain->SetBranchAddress("jetCSV2BJetTags", &jetCSV2BJetTags, &b_jetCSV2BJetTags);
   fChain->SetBranchAddress("jetDeepCSVTags_b", &jetDeepCSVTags_b, &b_jetDeepCSVTags_b);
   fChain->SetBranchAddress("jetDeepCSVTags_bb", &jetDeepCSVTags_bb, &b_jetDeepCSVTags_bb);
   fChain->SetBranchAddress("jetDeepCSVTags_c", &jetDeepCSVTags_c, &b_jetDeepCSVTags_c);
   fChain->SetBranchAddress("jetDeepCSVTags_udsg", &jetDeepCSVTags_udsg, &b_jetDeepCSVTags_udsg);
   fChain->SetBranchAddress("jetDeepFlavourTags_b", &jetDeepFlavourTags_b, &b_jetDeepFlavourTags_b);
   fChain->SetBranchAddress("jetDeepFlavourTags_c", &jetDeepFlavourTags_c, &b_jetDeepFlavourTags_c);
   fChain->SetBranchAddress("jetDeepFlavourTags_g", &jetDeepFlavourTags_g, &b_jetDeepFlavourTags_g);
   fChain->SetBranchAddress("jetDeepFlavourTags_lepb", &jetDeepFlavourTags_lepb, &b_jetDeepFlavourTags_lepb);
   fChain->SetBranchAddress("jetDeepFlavourTags_bb", &jetDeepFlavourTags_bb, &b_jetDeepFlavourTags_bb);
   fChain->SetBranchAddress("jetDeepFlavourTags_uds", &jetDeepFlavourTags_uds, &b_jetDeepFlavourTags_uds);
   fChain->SetBranchAddress("jetDeepCSVDiscriminatorTags_BvsAll", &jetDeepCSVDiscriminatorTags_BvsAll, &b_jetDeepCSVDiscriminatorTags_BvsAll);
   fChain->SetBranchAddress("jetDeepCSVDiscriminatorTags_CvsB", &jetDeepCSVDiscriminatorTags_CvsB, &b_jetDeepCSVDiscriminatorTags_CvsB);
   fChain->SetBranchAddress("jetDeepCSVDiscriminatorTags_CvsL", &jetDeepCSVDiscriminatorTags_CvsL, &b_jetDeepCSVDiscriminatorTags_CvsL);
   fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
   fChain->SetBranchAddress("jetGenPartonID", &jetGenPartonID, &b_jetGenPartonID);
   fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
   fChain->SetBranchAddress("jetGenPartonMomID", &jetGenPartonMomID, &b_jetGenPartonMomID);
   fChain->SetBranchAddress("calib_scEtaWidth", &calib_scEtaWidth, &b_calib_scEtaWidth);
   fChain->SetBranchAddress("calib_scPhiWidth", &calib_scPhiWidth, &b_calib_scPhiWidth);
   fChain->SetBranchAddress("calib_r9Full5x5", &calib_r9Full5x5, &b_calib_r9Full5x5);
   fChain->SetBranchAddress("calib_s4Full5x5", &calib_s4Full5x5, &b_calib_s4Full5x5);
   fChain->SetBranchAddress("calib_sieieFull5x5", &calib_sieieFull5x5, &b_calib_sieieFull5x5);
   fChain->SetBranchAddress("calib_sieipFull5x5", &calib_sieipFull5x5, &b_calib_sieipFull5x5);
   fChain->SetBranchAddress("calib_esEnergyOverSCRawEnergy", &calib_esEnergyOverSCRawEnergy, &b_calib_esEnergyOverSCRawEnergy);
   fChain->SetBranchAddress("nLHE", &nLHE, &b_nLHE);
   fChain->SetBranchAddress("lhePID", &lhePID, &b_lhePID);
   fChain->SetBranchAddress("lheE", &lheE, &b_lheE);
   fChain->SetBranchAddress("lhePx", &lhePx, &b_lhePx);
   fChain->SetBranchAddress("lhePy", &lhePy, &b_lhePy);
   fChain->SetBranchAddress("lhePz", &lhePz, &b_lhePz);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   fChain->SetBranchAddress("jetPUIDbit", &jetPUIDbit, &b_jetPUIDbit);
   fChain->SetBranchAddress("xsweight", &xsweight, &b_xsweight);
   fChain->SetBranchAddress("crossSection", &crossSection, &b_crossSection);
   fChain->SetBranchAddress("integratedLuminosity", &integratedLuminosity, &b_integratedLuminosity);
   fChain->SetBranchAddress("integratedGenWeight", &integratedGenWeight, &b_integratedGenWeight);
   fChain->SetBranchAddress("mcweight", &mcweight, &b_mcweight);
   fChain->SetBranchAddress("isQCD", &isQCD, &b_isQCD);
   fChain->SetBranchAddress("jetSF.DeepCSV.central", &jetSF_DeepCSV_central, &b_jetSF_DeepCSV_central);
   fChain->SetBranchAddress("jetSF.DeepCSV.down_cferr1", &jetSF_DeepCSV_down_cferr1, &b_jetSF_DeepCSV_down_cferr1);
   fChain->SetBranchAddress("jetSF.DeepCSV.down_cferr2", &jetSF_DeepCSV_down_cferr2, &b_jetSF_DeepCSV_down_cferr2);
   fChain->SetBranchAddress("jetSF.DeepCSV.down_hf", &jetSF_DeepCSV_down_hf, &b_jetSF_DeepCSV_down_hf);
   fChain->SetBranchAddress("jetSF.DeepCSV.down_lf", &jetSF_DeepCSV_down_lf, &b_jetSF_DeepCSV_down_lf);
   fChain->SetBranchAddress("jetSF.DeepCSV.up_cferr1", &jetSF_DeepCSV_up_cferr1, &b_jetSF_DeepCSV_up_cferr1);
   fChain->SetBranchAddress("jetSF.DeepCSV.up_cferr2", &jetSF_DeepCSV_up_cferr2, &b_jetSF_DeepCSV_up_cferr2);
   fChain->SetBranchAddress("jetSF.DeepCSV.up_hf", &jetSF_DeepCSV_up_hf, &b_jetSF_DeepCSV_up_hf);
   fChain->SetBranchAddress("jetSF.DeepCSV.up_lf", &jetSF_DeepCSV_up_lf, &b_jetSF_DeepCSV_up_lf);
   fChain->SetBranchAddress("jetSF.DeepFlavour.central", &jetSF_DeepFlavour_central, &b_jetSF_DeepFlavour_central);
   fChain->SetBranchAddress("jetSF.DeepFlavour.down_cferr1", &jetSF_DeepFlavour_down_cferr1, &b_jetSF_DeepFlavour_down_cferr1);
   fChain->SetBranchAddress("jetSF.DeepFlavour.down_cferr2", &jetSF_DeepFlavour_down_cferr2, &b_jetSF_DeepFlavour_down_cferr2);
   fChain->SetBranchAddress("jetSF.DeepFlavour.down_hf", &jetSF_DeepFlavour_down_hf, &b_jetSF_DeepFlavour_down_hf);
   fChain->SetBranchAddress("jetSF.DeepFlavour.down_lf", &jetSF_DeepFlavour_down_lf, &b_jetSF_DeepFlavour_down_lf);
   fChain->SetBranchAddress("jetSF.DeepFlavour.up_cferr1", &jetSF_DeepFlavour_up_cferr1, &b_jetSF_DeepFlavour_up_cferr1);
   fChain->SetBranchAddress("jetSF.DeepFlavour.up_cferr2", &jetSF_DeepFlavour_up_cferr2, &b_jetSF_DeepFlavour_up_cferr2);
   fChain->SetBranchAddress("jetSF.DeepFlavour.up_hf", &jetSF_DeepFlavour_up_hf, &b_jetSF_DeepFlavour_up_hf);
   fChain->SetBranchAddress("jetSF.DeepFlavour.up_lf", &jetSF_DeepFlavour_up_lf, &b_jetSF_DeepFlavour_up_lf);
   fChain->SetBranchAddress("DeepCSV.CvsB", &DeepCSV_CvsB, &b_DeepCSV_CvsB);
   fChain->SetBranchAddress("DeepCSV.CvsL", &DeepCSV_CvsL, &b_DeepCSV_CvsL);
   fChain->SetBranchAddress("DeepCSV.bScore", &DeepCSV_bScore, &b_DeepCSV_bScore);
   fChain->SetBranchAddress("DeepCSV.ctagWeight.central", &DeepCSV_ctagWeight_central, &b_DeepCSV_ctagWeight_central);
   fChain->SetBranchAddress("DeepCSV.ctagWeight.PUWeightUp", &DeepCSV_ctagWeight_PUWeightUp, &b_DeepCSV_ctagWeight_PUWeightUp);
   fChain->SetBranchAddress("DeepCSV.ctagWeight.StatUp", &DeepCSV_ctagWeight_StatUp, &b_DeepCSV_ctagWeight_StatUp);
   //fChain->SetBranchAddress("DeepCSV.ctagWeight.TotalUncDown", &DeepCSV_ctagWeight_TotalUncDown, &b_DeepCSV_ctagWeight_TotalUncUp);
   fChain->SetBranchAddress("DeepCSV.ctagWeight.PUWeightDown", &DeepCSV_ctagWeight_PUWeightDown, &b_DeepCSV_ctagWeight_PUWeightDown);
   fChain->SetBranchAddress("DeepCSV.ctagWeight.StatDown", &DeepCSV_ctagWeight_StatDown, &b_DeepCSV_ctagWeight_StatDown);
//    fChain->SetBranchAddress("DeepCSV.ctagWeight.TotalUncDown", &DeepCSV_ctagWeight_TotalUncDown, &b_DeepCSV_ctagWeight_TotalUncDown);
   fChain->SetBranchAddress("DeepFlavour.CvsB", &DeepFlavour_CvsB, &b_DeepFlavour_CvsB);
   fChain->SetBranchAddress("DeepFlavour.CvsL", &DeepFlavour_CvsL, &b_DeepFlavour_CvsL);
   fChain->SetBranchAddress("DeepFlavour.bScore", &DeepFlavour_bScore, &b_DeepFlavour_bScore);
   fChain->SetBranchAddress("DeepFlavour.ctagWeight.central", &DeepFlavour_ctagWeight_central, &b_DeepFlavour_ctagWeight_central);
   fChain->SetBranchAddress("DeepFlavour.ctagWeight.PUWeightUp", &DeepFlavour_ctagWeight_PUWeightUp, &b_DeepFlavour_ctagWeight_PUWeightUp);
   fChain->SetBranchAddress("DeepFlavour.ctagWeight.StatUp", &DeepFlavour_ctagWeight_StatUp, &b_DeepFlavour_ctagWeight_StatUp);
   //fChain->SetBranchAddress("DeepFlavour.ctagWeight.TotalUncDown", &DeepFlavour_ctagWeight_TotalUncDown, &b_DeepFlavour_ctagWeight_TotalUncUp);
   fChain->SetBranchAddress("DeepFlavour.ctagWeight.PUWeightDown", &DeepFlavour_ctagWeight_PUWeightDown, &b_DeepFlavour_ctagWeight_PUWeightDown);
   fChain->SetBranchAddress("DeepFlavour.ctagWeight.StatDown", &DeepFlavour_ctagWeight_StatDown, &b_DeepFlavour_ctagWeight_StatDown);
//    fChain->SetBranchAddress("DeepFlavour.ctagWeight.TotalUncDown", &DeepFlavour_ctagWeight_TotalUncDown, &b_DeepFlavour_ctagWeight_TotalUncDown);
   Notify();
}

Bool_t MakeHistoSIG::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MakeHistoSIG::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MakeHistoSIG::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MakeHistoSIG_cxx

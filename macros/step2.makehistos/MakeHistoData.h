//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Apr 20 15:12:18 2023 by ROOT version 6.22/09
// from TTree t/mini tree
// found on file: /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/UL16PreVFP_data.root
//////////////////////////////////////////////////////////

#ifndef MakeHistoData_h
#define MakeHistoData_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class MakeHistoData {
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
   Int_t           phoFillIdx;
   Int_t           run;
   Long64_t        event;
   Bool_t          isData;
   Long64_t        HLT;
   Long64_t        HLTIsPrescaled;
   Long64_t        phoFiredTrgs;
   Float_t         recoPt;
   Float_t         recoPtCalib;
   Float_t         recoEta;
   Float_t         recoPhi;
   Float_t         recoSCEta;
   Float_t         r9;
   Float_t         s4Full5x5;
   Float_t         esEnergyOverSCRawEnergy;
   Int_t           nVtx;
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
   Float_t         photonIDmva;
   Int_t           phoIDbit;
   Float_t         MET;
   Int_t           metFilters;
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
   Int_t           jetID;
   Int_t           jetPUIDbit;
   Float_t         SeedTime;
   Float_t         SeedEnergy;
   Float_t         MIPTotEnergy;
   Float_t         DeepCSV_CvsB;
   Float_t         DeepCSV_CvsL;
   Float_t         DeepCSV_bScore;
   Float_t         DeepFlavour_CvsB;
   Float_t         DeepFlavour_CvsL;
   Float_t         DeepFlavour_bScore;

   // List of branches
   TBranch        *b_jetSubVtxPt;   //!
   TBranch        *b_jetSubVtxMass;   //!
   TBranch        *b_jetSubVtx3DVal;   //!
   TBranch        *b_jetSubVtx3DErr;   //!
   TBranch        *b_jetSubVtxNtrks;   //!
   TBranch        *b_phoFillIdx;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_HLT;   //!
   TBranch        *b_HLTIsPrescaled;   //!
   TBranch        *b_phoFiredTrgs;   //!
   TBranch        *b_recoPt;   //!
   TBranch        *b_recoPtCalib;   //!
   TBranch        *b_recoEta;   //!
   TBranch        *b_recoPhi;   //!
   TBranch        *b_recoSCEta;   //!
   TBranch        *b_r9;   //!
   TBranch        *b_s4Full5x5;   //!
   TBranch        *b_esEnergyOverSCRawEnergy;   //!
   TBranch        *b_nVtx;   //!
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
   TBranch        *b_photonIDmva;   //!
   TBranch        *b_phoIDbit;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_metFilters;   //!
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
   TBranch        *b_jetID;   //!
   TBranch        *b_jetPUIDbit;   //!
   TBranch        *b_SeedTime;   //!
   TBranch        *b_SeedEnergy;   //!
   TBranch        *b_MIPTotEnergy;   //!
   TBranch        *b_DeepCSV_CvsB;   //!
   TBranch        *b_DeepCSV_CvsL;   //!
   TBranch        *b_DeepCSV_bScore;   //!
   TBranch        *b_DeepFlavour_CvsB;   //!
   TBranch        *b_DeepFlavour_CvsL;   //!
   TBranch        *b_DeepFlavour_bScore;   //!

   MakeHistoData(TTree *tree=0);
   virtual ~MakeHistoData();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef MakeHistoData_cxx
MakeHistoData::MakeHistoData(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/UL16PreVFP_data.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/UL16PreVFP_data.root");
      }
      f->GetObject("t",tree);

   }
   Init(tree);
}

MakeHistoData::~MakeHistoData()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MakeHistoData::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MakeHistoData::LoadTree(Long64_t entry)
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

void MakeHistoData::Init(TTree *tree)
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
   fChain->SetBranchAddress("phoFillIdx", &phoFillIdx, &b_phoFillIdx); // if no this branch, manually put the variable to 0
   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("HLT", &HLT, &b_HLT);
   fChain->SetBranchAddress("HLTIsPrescaled", &HLTIsPrescaled, &b_HLTIsPrescaled);
   fChain->SetBranchAddress("phoFiredTrgs", &phoFiredTrgs, &b_phoFiredTrgs);
   fChain->SetBranchAddress("recoPt", &recoPt, &b_recoPt);
   fChain->SetBranchAddress("recoPtCalib", &recoPtCalib, &b_recoPtCalib);
   fChain->SetBranchAddress("recoEta", &recoEta, &b_recoEta);
   fChain->SetBranchAddress("recoPhi", &recoPhi, &b_recoPhi);
   fChain->SetBranchAddress("recoSCEta", &recoSCEta, &b_recoSCEta);
   fChain->SetBranchAddress("r9", &r9, &b_r9);
   fChain->SetBranchAddress("s4Full5x5", &s4Full5x5, &b_s4Full5x5);
   fChain->SetBranchAddress("esEnergyOverSCRawEnergy", &esEnergyOverSCRawEnergy, &b_esEnergyOverSCRawEnergy);
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
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
   fChain->SetBranchAddress("photonIDmva", &photonIDmva, &b_photonIDmva);
   fChain->SetBranchAddress("phoIDbit", &phoIDbit, &b_phoIDbit);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   fChain->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
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
   fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   fChain->SetBranchAddress("jetPUIDbit", &jetPUIDbit, &b_jetPUIDbit);
   fChain->SetBranchAddress("SeedTime", &SeedTime, &b_SeedTime);
   fChain->SetBranchAddress("SeedEnergy", &SeedEnergy, &b_SeedEnergy);
   fChain->SetBranchAddress("MIPTotEnergy", &MIPTotEnergy, &b_MIPTotEnergy);
   fChain->SetBranchAddress("DeepCSV.CvsB", &DeepCSV_CvsB, &b_DeepCSV_CvsB);
   fChain->SetBranchAddress("DeepCSV.CvsL", &DeepCSV_CvsL, &b_DeepCSV_CvsL);
   fChain->SetBranchAddress("DeepCSV.bScore", &DeepCSV_bScore, &b_DeepCSV_bScore);
   fChain->SetBranchAddress("DeepFlavour.CvsB", &DeepFlavour_CvsB, &b_DeepFlavour_CvsB);
   fChain->SetBranchAddress("DeepFlavour.CvsL", &DeepFlavour_CvsL, &b_DeepFlavour_CvsL);
   fChain->SetBranchAddress("DeepFlavour.bScore", &DeepFlavour_bScore, &b_DeepFlavour_bScore);
   Notify();
}

Bool_t MakeHistoData::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MakeHistoData::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MakeHistoData::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef MakeHistoData_cxx

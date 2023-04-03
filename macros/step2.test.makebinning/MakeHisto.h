//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 16 15:02:11 2021 by ROOT version 6.10/09
// from TTree t/mini tree
// found on file: /home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root
//////////////////////////////////////////////////////////

#ifndef MakeHisto_h
#define MakeHisto_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <iostream>

#define LOG(format, args...)     fprintf(stderr, "[LOG]  %s  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)

// Header file for the classes stored in the TTree if any.

class MakeHisto {
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
   Long64_t        HLT;
   Long64_t        HLTIsPrescaled;
   Int_t           phoFiredTrgs;
   Float_t         pthat;
   Float_t         genHT;
   Float_t         mcPt;
   Float_t         mcEta;
   Float_t         mcPhi;
   Float_t         mcCalIso04;
   Float_t         mcTrkIso04;
   Float_t         recoPt;
   Float_t         recoPtCalib;
   Float_t         recoEta;
   Float_t         recoPhi;
   Float_t         recoSCEta;
   Float_t         r9;
   Float_t         s4Full5x5;
   Int_t           isMatched;
   Int_t           isMatchedEle;
   Int_t           isConverted;
   Int_t           nVtx;
   Int_t           nPU;
   Float_t         puwei;
   Int_t           eleVeto;
   Float_t         HoverE;
   Float_t         chIsoRaw;
   Float_t         calib_chIso;
   Float_t         chWorstRaw;
   Float_t         phoIsoRaw;
   Float_t         nhIsoRaw;
   Float_t         rho;
   Float_t         rawE;
   Float_t         scEtaWidth;
   Float_t         scPhiWidth;
   Float_t         esRR;
   Float_t         esEn;
   Float_t         mva;
   Float_t         calib_mva;
   //Float_t         mva_nocorr;
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
   Float_t         calib_r9Full5x5;
   Float_t         calib_s4Full5x5;
   Float_t         calib_sieieFull5x5;
   Int_t           nLHE;
   Int_t           lhePID[5];   //[nLHE]
   Float_t         lheE[5];   //[nLHE]
   Float_t         lhePx[5];   //[nLHE]
   Float_t         lhePy[5];   //[nLHE]
   Float_t         lhePz[5];   //[nLHE]
   Float_t         genWeight;
   Int_t           jetID;
   Int_t           jetPUIDbit;
   Float_t         SeedTime;
   Float_t         SeedEnergy;
   Float_t         MIPTotEnergy;
   Float_t         xsweight;
   Float_t         crossSection;
   Float_t         integratedLuminosity;
   Float_t         integratedGenWeight;
   Float_t         mcweight;
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
   // Float_t         jetSF_DeepFlavour_JESReduced_central;
   // Float_t         jetSF_DeepFlavour_JESReduced_down_cferr1;
   // Float_t         jetSF_DeepFlavour_JESReduced_down_cferr2;
   // Float_t         jetSF_DeepFlavour_JESReduced_down_hf;
   // Float_t         jetSF_DeepFlavour_JESReduced_down_lf;
   // Float_t         jetSF_DeepFlavour_JESReduced_up_cferr1;
   // Float_t         jetSF_DeepFlavour_JESReduced_up_cferr2;
   // Float_t         jetSF_DeepFlavour_JESReduced_up_hf;
   // Float_t         jetSF_DeepFlavour_JESReduced_up_lf;
   Int_t           isQCD = 0;
   Int_t           passMaxPUcut = 0;
   Float_t         weight_passMaxPUcut = 0;

   // List of branches
   TBranch        *b_jetSubVtxPt;   //!
   TBranch        *b_jetSubVtxMass;   //!
   TBranch        *b_jetSubVtx3DVal;   //!
   TBranch        *b_jetSubVtx3DErr;   //!
   TBranch        *b_jetSubVtxNtrks;   //!
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_HLT;   //!
   TBranch        *b_HLTIsPrescaled;   //!
   TBranch        *b_phoFiredTrgs;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_genHT;   //!
   TBranch        *b_mcPt;   //!
   TBranch        *b_mcEta;   //!
   TBranch        *b_mcPhi;   //!
   TBranch        *b_mcCalIso04;   //!
   TBranch        *b_mcTrkIso04;   //!
   TBranch        *b_recoPt;   //!
   TBranch        *b_recoPtCalib;   //!
   TBranch        *b_recoEta;   //!
   TBranch        *b_recoPhi;   //!
   TBranch        *b_recoSCEta;   //!
   TBranch        *b_r9;   //!
   TBranch        *b_s4Full5x5;   //!
   TBranch        *b_isMatched;   //!
   TBranch        *b_isMatchedEle;   //!
   TBranch        *b_isConverted;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_nPU;   //!
   TBranch        *b_puwei;   //!
   TBranch        *b_eleVeto;   //!
   TBranch        *b_HoverE;   //!
   TBranch        *b_chIsoRaw;   //!
   TBranch        *b_calib_chIso;   //!
   TBranch        *b_chWorstIso;   //!
   TBranch        *b_phoIsoRaw;   //!
   TBranch        *b_nhIsoRaw;   //!
   TBranch        *b_rho;   //!
   TBranch        *b_rawE;   //!
   TBranch        *b_scEtaWidth;   //!
   TBranch        *b_scPhiWidth;   //!
   TBranch        *b_esRR;   //!
   TBranch        *b_esEn;   //!
   TBranch        *b_mva;   //!
   //TBranch        *b_mva_nocorr;   //!
   TBranch        *b_calib_mva;   //!
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
   TBranch        *b_calib_r9Full5x5;   //!
   TBranch        *b_calib_s4Full5x5;   //!
   TBranch        *b_calib_sieieFull5x5;   //!
   TBranch        *b_nLHE;   //!
   TBranch        *b_lhePID;   //!
   TBranch        *b_lheE;   //!
   TBranch        *b_lhePx;   //!
   TBranch        *b_lhePy;   //!
   TBranch        *b_lhePz;   //!
   TBranch        *b_genWeight;   //!
   TBranch        *b_jetID;   //!
   TBranch        *b_jetPUIDbit;   //!
   TBranch        *b_SeedTime;   //!
   TBranch        *b_SeedEnergy;   //!
   TBranch        *b_MIPTotEnergy;   //!
   TBranch        *b_xsweight;   //!
   TBranch        *b_crossSection;   //!
   TBranch        *b_integratedLuminosity;   //!
   TBranch        *b_integratedGenWeight;   //!
   TBranch        *b_mcweight;   //!
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
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_central;   //!
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_down_cferr1;   //!
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_down_cferr2;   //!
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_down_hf;   //!
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_down_lf;   //!
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_up_cferr1;   //!
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_up_cferr2;   //!
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_up_hf;   //!
   //TBranch        *b_jetSF_DeepFlavour_JESReduced_up_lf;   //!
   TBranch        *b_isQCD;   //!
   TBranch        *b_weight_passMaxPUcut;   //!
   TBranch        *b_passMaxPUcut;   //!

   MakeHisto(Int_t option=0);
   MakeHisto(const char* fname, const char* outputlabel_, bool isMC, int HLTOPTION_ = 0);
   void fitVarsInit();
   virtual ~MakeHisto();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop(Int_t extracut);
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual Int_t    EBEE(Float_t eta);
   virtual Int_t    Ptbin(Float_t pt);
   virtual Int_t    HLTbit(Float_t pt);
   virtual Int_t    JetEtaBin(Float_t pt, Float_t eta);
   virtual Int_t    triggerbit(const std::string& dataera, Int_t ptbin);
   virtual Int_t    JetFlavourBin( int jetHadFlvr );

   bool PhoSignalRegion(Float_t isovar, Float_t eta);
   bool PhoDataSideband(Float_t isovar, Float_t eta);
   bool HLTPassed(int hltbit);
   Int_t PhoMatchedStatus();
   Int_t EventParity(Long64_t evtidx);
   bool PassJetAdditionalSelection(int cutIndicator);


   Float_t bTagWeight_Up(Int_t jetFLAVOURbin);
   Float_t bTagWeight_Central(Int_t jetFLAVOURbin);
   Float_t bTagWeight_Down(Int_t jetFLAVOURbin);


   void SetDataEra(const std::string& d) { _dataera = d; }

   bool IsMC();

   Int_t           OPTION;
   Int_t        HLTOPTION;
   bool fkMC;
   const char* _outputlabel;
   std::string _dataera;

   enum fitVar {
   _deepCSVTags_b,
   _deepCSVTags_bb,
   _deepCSVTags_c,
   _deepCSVTags_udsg,
   _deepFlavourTags_b,
   _deepFlavourTags_c,
   _deepFlavourTags_g,
   _deepFlavourTags_lepb,
   _deepFlavourTags_bb,
   _deepFlavourTags_uds,
   _deepCSVDiscriminatorTags_BvsAll,
   _deepCSVDiscriminatorTags_CvsB,
   _deepCSVDiscriminatorTags_CvsL,
   _subVtxMass,
   _totFitVar
   };
};

#endif

#ifdef MakeHisto_cxx
MakeHisto::MakeHisto(Int_t option) : fChain(0) , fkMC(true), OPTION(option), HLTOPTION(0)
{
  printf("option %d \n", option);
  TChain *tc = new TChain("t");

  //fkMC = tc->GetBranch("mcPt") ? kTRUE : kFALSE;
  if(option == 1) { // data
    tc->Add("/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root");
    fkMC = false;
  };
  if(option == 2) { // madgraph sig MC
    tc->Add("/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root");
    //HLTOPTION=1; // prevent to use HLT
  }
  if(option == 3) { // madgraph QCD MC
    tc->Add("/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root");
    //HLTOPTION=1; // prevent to use HLT
  }
  if(option == -5) { // test sample of QCD pythiasig MC
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/bin/step1.xsinfoAppended/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3-v2.root");
    //HLTOPTION=1; // prevent to use HLT
  }
  if(option == 5) { // pythia   QCD MC
    //HLTOPTION=1; // prevent to use HLT
  }

  if ( option == -100 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample0.root");
  }
  if ( option == -101 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample1.root");
  }
  if ( option == -102 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample2.root");
  }
  if ( option == -103 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample3.root");
  }
  if ( option == -104 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample4.root");
  }
  if ( option == -105 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample5.root");
  }
  if ( option == -106 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample6.root");
  }
  if ( option == -107 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample7.root");
  }
  if ( option == -108 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample8.root");
  }
  if ( option == -109 ) { // fake datasample 0
    tc->Add("/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step7.ClosureTest/storeroot/fakesample9.root");
  }

  _outputlabel="hi";
  Init(tc);
}
MakeHisto::MakeHisto(const char* fname, const char* outputlabel_, bool isMC, int HLTOPTION_) :
    fChain(0) , fkMC(isMC), OPTION(0), HLTOPTION(HLTOPTION_), _outputlabel(outputlabel_)
{
  printf("Input file name is : %s", fname);
  TChain *tc = new TChain("t");
  tc->Add(fname);

  Init(tc);
  std::cerr << "is MC ? " << fkMC << std::endl;
}

MakeHisto::~MakeHisto()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t MakeHisto::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t MakeHisto::LoadTree(Long64_t entry)
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

void MakeHisto::Init(TTree *tree)
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
   if (!IsMC() && fChain->GetListOfBranches()->FindObject("HLT") ) // for fake data, there is no HLT found
   {
   fChain->SetBranchAddress("HLT", &HLT, &b_HLT);
   fChain->SetBranchAddress("HLTIsPrescaled", &HLTIsPrescaled, &b_HLTIsPrescaled);
   }
   fChain->SetBranchAddress("phoFiredTrgs", &phoFiredTrgs, &b_phoFiredTrgs);
   if ( IsMC() )
   {
   fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
   fChain->SetBranchAddress("genHT", &genHT, &b_genHT);
   fChain->SetBranchAddress("mcPt", &mcPt, &b_mcPt);
   fChain->SetBranchAddress("mcEta", &mcEta, &b_mcEta);
   fChain->SetBranchAddress("mcPhi", &mcPhi, &b_mcPhi);
   fChain->SetBranchAddress("mcCalIso04", &mcCalIso04, &b_mcCalIso04);
   fChain->SetBranchAddress("mcTrkIso04", &mcTrkIso04, &b_mcTrkIso04);
   }
   fChain->SetBranchAddress("recoPt", &recoPt, &b_recoPt);
   fChain->SetBranchAddress("recoPtCalib", &recoPtCalib, &b_recoPtCalib);
   fChain->SetBranchAddress("recoEta", &recoEta, &b_recoEta);
   fChain->SetBranchAddress("recoPhi", &recoPhi, &b_recoPhi);
   fChain->SetBranchAddress("recoSCEta", &recoSCEta, &b_recoSCEta);
   fChain->SetBranchAddress("r9", &r9, &b_r9);
   fChain->SetBranchAddress("s4Full5x5", &s4Full5x5, &b_s4Full5x5);
   if ( IsMC() )
   {
   fChain->SetBranchAddress("isMatched", &isMatched, &b_isMatched);
   fChain->SetBranchAddress("isMatchedEle", &isMatchedEle, &b_isMatchedEle);
   fChain->SetBranchAddress("isConverted", &isConverted, &b_isConverted);
   }
   fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx);
   if ( IsMC() )
   {
   fChain->SetBranchAddress("nPU", &nPU, &b_nPU);
   fChain->SetBranchAddress("puwei", &puwei, &b_puwei);
   }
   fChain->SetBranchAddress("eleVeto", &eleVeto, &b_eleVeto);
   fChain->SetBranchAddress("HoverE", &HoverE, &b_HoverE);
   fChain->SetBranchAddress("chIsoRaw", &chIsoRaw, &b_chIsoRaw);
   if (!IsMC() )
   {
   fChain->SetBranchAddress("calib_chIso", &calib_chIso, &b_calib_chIso);
   }
   fChain->SetBranchAddress("chWorstRaw", &chWorstRaw, &b_chWorstIso);
   fChain->SetBranchAddress("phoIsoRaw", &phoIsoRaw, &b_phoIsoRaw);
   fChain->SetBranchAddress("nhIsoRaw", &nhIsoRaw, &b_nhIsoRaw);
   fChain->SetBranchAddress("rho", &rho, &b_rho);
   fChain->SetBranchAddress("rawE", &rawE, &b_rawE);
   fChain->SetBranchAddress("scEtaWidth", &scEtaWidth, &b_scEtaWidth);
   fChain->SetBranchAddress("scPhiWidth", &scPhiWidth, &b_scPhiWidth);
   fChain->SetBranchAddress("esRR", &esRR, &b_esRR);
   fChain->SetBranchAddress("esEn", &esEn, &b_esEn);
   fChain->SetBranchAddress("mva", &mva, &b_mva);
   if ( IsMC() )
   {
   //fChain->SetBranchAddress("mva_nocorr", &mva_nocorr, &b_mva_nocorr);
   fChain->SetBranchAddress("calib_mva", &calib_mva, &b_calib_mva);
   }
   fChain->SetBranchAddress("photonIDmva", &photonIDmva, &b_photonIDmva);
   fChain->SetBranchAddress("phoIDbit", &phoIDbit, &b_phoIDbit);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   if (!IsMC() )
   {
   fChain->SetBranchAddress("metFilters", &metFilters, &b_metFilters);
   }
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
   if ( IsMC() )
   {
   fChain->SetBranchAddress("jetGenJetPt", &jetGenJetPt, &b_jetGenJetPt);
   fChain->SetBranchAddress("jetGenJetEta", &jetGenJetEta, &b_jetGenJetEta);
   fChain->SetBranchAddress("jetGenJetPhi", &jetGenJetPhi, &b_jetGenJetPhi);
   fChain->SetBranchAddress("jetGenJetY", &jetGenJetY, &b_jetGenJetY);
   }
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
   if ( IsMC() )
   {
   fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
   fChain->SetBranchAddress("jetGenPartonID", &jetGenPartonID, &b_jetGenPartonID);
   fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
   fChain->SetBranchAddress("jetGenPartonMomID", &jetGenPartonMomID, &b_jetGenPartonMomID);
   fChain->SetBranchAddress("calib_scEtaWidth", &calib_scEtaWidth, &b_calib_scEtaWidth);
   fChain->SetBranchAddress("calib_r9Full5x5", &calib_r9Full5x5, &b_calib_r9Full5x5);
   fChain->SetBranchAddress("calib_s4Full5x5", &calib_s4Full5x5, &b_calib_s4Full5x5);
   fChain->SetBranchAddress("calib_sieieFull5x5", &calib_sieieFull5x5, &b_calib_sieieFull5x5);
   fChain->SetBranchAddress("nLHE", &nLHE, &b_nLHE);
   fChain->SetBranchAddress("lhePID", lhePID, &b_lhePID);
   fChain->SetBranchAddress("lheE", lheE, &b_lheE);
   fChain->SetBranchAddress("lhePx", lhePx, &b_lhePx);
   fChain->SetBranchAddress("lhePy", lhePy, &b_lhePy);
   fChain->SetBranchAddress("lhePz", lhePz, &b_lhePz);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   }
   fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   fChain->SetBranchAddress("jetPUIDbit", &jetPUIDbit, &b_jetPUIDbit);
   if (!IsMC() && fChain->GetListOfBranches()->FindObject("HLT") ) // for fake data, there is no HLT found
   {
   fChain->SetBranchAddress("SeedTime", &SeedTime, &b_SeedTime);
   fChain->SetBranchAddress("SeedEnergy", &SeedEnergy, &b_SeedEnergy);
   fChain->SetBranchAddress("MIPTotEnergy", &MIPTotEnergy, &b_MIPTotEnergy);
   }
   if ( IsMC() )
   {
   fChain->SetBranchAddress("xsweight", &xsweight, &b_xsweight);
   fChain->SetBranchAddress("crossSection", &crossSection, &b_crossSection);
   fChain->SetBranchAddress("integratedLuminosity", &integratedLuminosity, &b_integratedLuminosity);
   fChain->SetBranchAddress("integratedGenWeight", &integratedGenWeight, &b_integratedGenWeight);
   fChain->SetBranchAddress("mcweight", &mcweight, &b_mcweight);
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
   // fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.central", &jetSF_DeepFlavour_JESReduced_central, &b_jetSF_DeepFlavour_JESReduced_central);
   // fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.down_cferr1", &jetSF_DeepFlavour_JESReduced_down_cferr1, &b_jetSF_DeepFlavour_JESReduced_down_cferr1);
   //fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.down_cferr2", &jetSF_DeepFlavour_JESReduced_down_cferr2, &b_jetSF_DeepFlavour_JESReduced_down_cferr2);
   //fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.down_hf", &jetSF_DeepFlavour_JESReduced_down_hf, &b_jetSF_DeepFlavour_JESReduced_down_hf);
   //fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.down_lf", &jetSF_DeepFlavour_JESReduced_down_lf, &b_jetSF_DeepFlavour_JESReduced_down_lf);
   //fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.up_cferr1", &jetSF_DeepFlavour_JESReduced_up_cferr1, &b_jetSF_DeepFlavour_JESReduced_up_cferr1);
   //fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.up_cferr2", &jetSF_DeepFlavour_JESReduced_up_cferr2, &b_jetSF_DeepFlavour_JESReduced_up_cferr2);
   //fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.up_hf", &jetSF_DeepFlavour_JESReduced_up_hf, &b_jetSF_DeepFlavour_JESReduced_up_hf);
   //fChain->SetBranchAddress("jetSF.DeepFlavour_JESReduced.up_lf", &jetSF_DeepFlavour_JESReduced_up_lf, &b_jetSF_DeepFlavour_JESReduced_up_lf);
   fChain->SetBranchAddress("isQCD", &isQCD, &b_isQCD);

   }
   if ( IsMC() && fChain->GetListOfBranches()->FindObject("passMaxPUcut") )
   {
       std::cout << "shitttttttt\n";
       fChain->SetBranchAddress("passMaxPUcut", &passMaxPUcut, &b_passMaxPUcut);
       fChain->SetBranchAddress("weight_passMaxPUcut", &weight_passMaxPUcut, &b_weight_passMaxPUcut);
   }
   else
   //{ printf("FQQQQQQQQ!!!!! function works !!!!\n"); }
   { LOG("PUmax Pt hat selection is disabled."); passMaxPUcut = 1; weight_passMaxPUcut = 1.; }
   Notify();
}

Bool_t MakeHisto::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void MakeHisto::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t MakeHisto::Cut(Long64_t entry)
{
   return 1;
}

bool MakeHisto::IsMC()
{ return fkMC; }
bool MakeHisto::PhoSignalRegion(Float_t isovar, Float_t eta)
{
    int ebee = EBEE(eta);
    if ( ebee == 0 && fabs(isovar) < 2  ) return true;
    if ( ebee == 1 && fabs(isovar) < 1.5) return true;
    return false;
}
bool MakeHisto::PhoDataSideband(Float_t isovar, Float_t eta)
{
    int ebee = EBEE(eta);
    if ( ebee == 0 && fabs(isovar)>7 && fabs(isovar)<13 ) return true;
    if ( ebee == 1 && fabs(isovar)>6 && fabs(isovar)<12 ) return true;
    return false;
}
bool MakeHisto::HLTPassed(int hltbit)
{
    if ( HLTOPTION == 1 && !((phoFiredTrgs>>hltbit)&1) ) return false;
    return true;
}

Float_t MakeHisto::bTagWeight_Up(Int_t jetFLAVOURbin)
{
    if (!IsMC() ) return 1.;
    // good code
    //if ( jetFLAVOURbin == 2 ) return jetSF_DeepCSV_up_hf;
    //if ( jetFLAVOURbin == 1 ) return jetSF_DeepCSV_up_cferr1;
    //return jetSF_DeepCSV_up_lf;

    // problematic code to check whether fitting failed due to wrong error assignment
    if ( jetFLAVOURbin == 0 ) return jetSF_DeepCSV_up_hf;
    if ( jetFLAVOURbin == 1 ) return jetSF_DeepCSV_up_cferr1;
    return jetSF_DeepCSV_up_lf;
}
Float_t MakeHisto::bTagWeight_Central(Int_t jetFLAVOURbin)
{
    if (!IsMC() ) return 1.;
    return jetSF_DeepCSV_central;
}
Float_t MakeHisto::bTagWeight_Down(Int_t jetFLAVOURbin)
{
    if (!IsMC() ) return 1.;
    // good code
    //if ( jetFLAVOURbin == 2 ) return jetSF_DeepCSV_down_hf;
    //if ( jetFLAVOURbin == 1 ) return jetSF_DeepCSV_down_cferr1;
    //return jetSF_DeepCSV_down_lf;

    // problematic code to check whether fitting failed due to wrong error assignment
    if ( jetFLAVOURbin == 0 ) return jetSF_DeepCSV_down_hf;
    if ( jetFLAVOURbin == 1 ) return jetSF_DeepCSV_down_cferr1;
    return jetSF_DeepCSV_down_lf;
}

struct BinnedHist
{
    BinnedHist( const std::vector<int>& MIdxs, const char* nameTemplate ) :
        _nTemplate(nameTemplate), _MIdxs(MIdxs)
    {
        hists.reserve( total_size() );
        for ( int i=0; i< total_size(); ++i ) hists.emplace_back(nullptr);
    }
    TDirectory* MakeDirectory( TDirectory* origdir )
    {
        char kk[200];
        int i=0;
        while ( _nTemplate[i] != '\0' )
        {
            char k = _nTemplate[i];
            if ( k == '.' )
            { kk[i] = '\0'; break; }
            kk[i] = k;
            ++i;
        }
        return origdir->mkdir( kk );
    }
    //virtual void Fill(const std::vector<int>& idxs, float val, float val2=1, float val3=1 ) = 0;
    virtual void Fill(const std::vector<int>& idxs, float val, float val2=1, float val3=1) {};
    void Write( TDirectory* dir = nullptr )
    { if ( dir != nullptr ) dir->cd(); for ( auto h : hists ) h->Write(); }
        
protected:
    std::vector<int> decode_idx(int idx)
    {
        std::vector<int> outputidxs;
        for ( unsigned int i = 0; i < _MIdxs.size(); ++i )
        {
            int lPosition = idx_multiplier(i);
            int rPosition = idx_multiplier(i+1);
            outputidxs.emplace_back( (idx%lPosition) / rPosition );
        }
        return outputidxs;
    }
    const char* get_title( const std::vector<int>& iI )
    {
        switch ( _MIdxs.size() ) {
        case 0: throw "histogram failed to interpret\n"; return "";
        case 1: return Form(_nTemplate, iI[0]);
        case 2: return Form(_nTemplate, iI[0], iI[1]);
        case 3: return Form(_nTemplate, iI[0], iI[1], iI[2]);
        case 4: return Form(_nTemplate, iI[0], iI[1], iI[2], iI[3]);
        case 5: return Form(_nTemplate, iI[0], iI[1], iI[2], iI[3], iI[4]);
        case 6: return Form(_nTemplate, iI[0], iI[1], iI[2], iI[3], iI[4], iI[5]);
        case 7: return Form(_nTemplate, iI[0], iI[1], iI[2], iI[3], iI[4], iI[5], iI[6]);
        }
        throw "_MIdxs size exceeds the size provided from get_title(), please extend this function\n";
                return "";
    }
    int indexing( const std::vector<int>& inIdxs )
    {
        int idx = 0;
        for ( unsigned int i = 0; i < _MIdxs.size(); ++i )
        { idx += inIdxs[i] * idx_multiplier(i+1); }

        return idx;
    }
    int idx_multiplier( int fromIdx )
    {
        int idxMultiplier = 1;
        for ( unsigned int jdx = fromIdx; jdx < _MIdxs.size(); ++jdx )
            idxMultiplier *= _MIdxs.at(jdx);
        return idxMultiplier;
    }
    int total_size()
    { return idx_multiplier(0); }

    int num_idx() const { return _MIdxs.size(); }


    std::vector<int> _MIdxs;
    const char* _nTemplate;
    char tmpnaming[200];
    std::vector<TObject*> hists;
};

struct BinnedHist1D : public BinnedHist
{
    BinnedHist1D( const std::vector<int>& MIdxs, const char* nameTemplate) : BinnedHist(MIdxs,nameTemplate)
    { }
    void SetXaxis( int nbin, float xmin, float xmax )
    {
        for ( int idx = 0; idx < total_size(); ++idx )
        {
            TH1F* h = new TH1F( get_title( decode_idx(idx) ), "", nbin, xmin, xmax );
            h->Sumw2();
            hists[idx] = h;
        }
    }
    virtual void Fill( const std::vector<int>& idxs, float val, float weight=1, float nonvalue=1 ) override
    { ( (TH1F*)hists[indexing(idxs)] )->Fill(val, weight); }
    TH1F* GetBin( const std::vector<int>& idxs )
    { return (TH1F*) hists[ indexing(idxs) ]; }
};
struct BinnedHist1D_BDT : public BinnedHist1D
{
    BinnedHist1D_BDT( const std::vector<int>& MIdxs, const char* nameTemplate) : BinnedHist1D(MIdxs,nameTemplate)
    { SetXaxis(100,-1.,1.); }
};
struct BinnedHist1D_Pt : public BinnedHist1D
{
    BinnedHist1D_Pt( const std::vector<int>& MIdxs, const char* nameTemplate) : BinnedHist1D(MIdxs,nameTemplate)
    { SetXaxis(200,0.,2000.); }
};
struct BinnedHist1D_PtAll : public BinnedHist1D
{
    BinnedHist1D_PtAll( const std::vector<int>& MIdxs, const char* nameTemplate) : BinnedHist1D(MIdxs,nameTemplate)
    { SetXaxis(2000,0.,2000.); }
};
struct BinnedHist1D_HLT : public BinnedHist1D
{
    BinnedHist1D_HLT( const std::vector<int>& MIdxs, const char* nameTemplate) : BinnedHist1D(MIdxs,nameTemplate)
    { SetXaxis(2000,0.,2000.); }
};


struct BinnedHist2D : public BinnedHist
{
    BinnedHist2D( const std::vector<int>& MIdxs, const char* nameTemplate) : BinnedHist(MIdxs,nameTemplate)
    { }
    void SetXYaxis( int nbinx, float xmin, float xmax, int nbiny, float ymin, float ymax )
    {
        for ( int idx = 0; idx < total_size(); ++idx )
        {
            TH2F* h;
            h = new TH2F( get_title( decode_idx(idx) ), "", nbinx, xmin, xmax, nbiny, ymin, ymax );
            h->Sumw2();
            hists[idx] = h;
        }
    }
    TH2F* GetBin( const std::vector<int>& idxs )
    { return (TH2F*) hists[ indexing(idxs) ]; }
    virtual void Fill( const std::vector<int>& idxs, float val, float val2, float weight=1 ) override
    { ( (TH2F*)hists[indexing(idxs)] )->Fill(val,val2,weight); }
};

struct BinnedHist2D_ISOvsBDT : public BinnedHist2D
{
    BinnedHist2D_ISOvsBDT( const std::vector<int>&MIdxs, const char* nameTemplate) : BinnedHist2D(MIdxs,nameTemplate)
    { SetXYaxis(100,-1.,1., 30,0.,15.); }
};
struct BinnedHist2D_BTAGvsBDT : public BinnedHist2D
{
    BinnedHist2D_BTAGvsBDT( const std::vector<int>&MIdxs, const char* nameTemplate) : BinnedHist2D(MIdxs,nameTemplate)
    { SetXYaxis(10,0.,1., 30,0.,15.); }
}; 
struct BinnedHist2D_secVTXMASSvsBDT : public BinnedHist2D
{
    BinnedHist2D_secVTXMASSvsBDT( const std::vector<int>& MIdxs, const char* nameTemplate) : BinnedHist2D(MIdxs,nameTemplate)
    { SetXYaxis(100,0.,5., 30,0.,15.); }
}; 


#endif // #ifdef MakeHisto_cxx

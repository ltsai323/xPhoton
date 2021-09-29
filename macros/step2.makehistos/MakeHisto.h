//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Sep 17 21:03:02 2021 by ROOT version 6.10/09
// from TTree t/mini tree
// found on file: /home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root
//////////////////////////////////////////////////////////

#ifndef MakeHisto_h
#define MakeHisto_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

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
   Float_t         s4;
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
   Float_t         rawE;
   Float_t         scEtaWidth;
   Float_t         scPhiWidth;
   Float_t         esRR;
   Float_t         esEn;
   Float_t         mva;
   Float_t         mva_nocorr;
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
   Float_t         calib_s4;
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
   TBranch        *b_s4;   //!
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
   TBranch        *b_rawE;   //!
   TBranch        *b_scEtaWidth;   //!
   TBranch        *b_scPhiWidth;   //!
   TBranch        *b_esRR;   //!
   TBranch        *b_esEn;   //!
   TBranch        *b_mva;   //!
   TBranch        *b_mva_nocorr;   //!
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
   TBranch        *b_calib_s4;   //!
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

   //MakeHisto(TTree *tree=0);
   MakeHisto(Int_t option=0);
   virtual ~MakeHisto();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
   virtual Int_t    EBEE(Float_t eta);
   virtual Int_t    Ptbin(Float_t pt);
   virtual Int_t    HLTbit(Float_t pt);
   virtual Int_t    JetEtaBin(Float_t eta);
   virtual Int_t    triggerbit(Int_t ptbin);

   bool IsMC();

   Int_t           OPTION;
   Int_t        HLTOPTION;
   bool fkMC;

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
   std::vector<const char*> fitVarNames;
};

#endif

#ifdef MakeHisto_cxx
MakeHisto::MakeHisto(Int_t option) : fChain(0) , fkMC(true), fitVarNames( fitVar::_totFitVar )
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

  printf("option %d \n", option);
  HLTOPTION = 0;
  /* Init(tree); */
  TChain *tc = new TChain("t");
    //tc->Add("");

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

  if(option == 15) tc->Add("../qcd/job_spring*_qcd*.root");
  if(option == 8) tc->Add("../output_job_fall15_gjet_pt15to6000_miniAOD.root");
  if(option == 16) tc->Add("../gjet_MG.root");

  OPTION = option;

  fitVarNames[fitVar::_deepCSVTags_b]                      = "deepCSVTags_b";                   
  fitVarNames[fitVar::_deepCSVTags_bb]                     = "deepCSVTags_bb";
  fitVarNames[fitVar::_deepCSVTags_c]                      = "deepCSVTags_c";
  fitVarNames[fitVar::_deepCSVTags_udsg]                   = "deepCSVTags_udsg";
  fitVarNames[fitVar::_deepFlavourTags_b]                  = "deepFlavourTags_b";
  fitVarNames[fitVar::_deepFlavourTags_c]                  = "deepFlavourTags_c";
  fitVarNames[fitVar::_deepFlavourTags_g]                  = "deepFlavourTags_g";
  fitVarNames[fitVar::_deepFlavourTags_lepb]               = "deepFlavourTags_lepb";
  fitVarNames[fitVar::_deepFlavourTags_bb]                 = "deepFlavourTags_bb";
  fitVarNames[fitVar::_deepFlavourTags_uds]                = "deepFlavourTags_uds";
  fitVarNames[fitVar::_deepCSVDiscriminatorTags_BvsAll]    = "deepCSVDiscriminatorTags_BvsAll";
  fitVarNames[fitVar::_deepCSVDiscriminatorTags_CvsB]      = "deepCSVDiscriminatorTags_CvsB";
  fitVarNames[fitVar::_deepCSVDiscriminatorTags_CvsL]      = "deepCSVDiscriminatorTags_CvsL";
  fitVarNames[fitVar::_subVtxMass]                         = "subVtxMass";
   
  Init(tc);
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
   
   if (!IsMC() )
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
   // fChain->SetBranchAddress("s4", &s4, &b_s4);
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
   fChain->SetBranchAddress("mva_nocorr", &mva_nocorr, &b_mva_nocorr);
   }
   fChain->SetBranchAddress("photonIDmva", &photonIDmva, &b_photonIDmva);
   fChain->SetBranchAddress("phoIDbit", &phoIDbit, &b_phoIDbit);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   if ( IsMC() )
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
   fChain->SetBranchAddress("jetPartonID", &jetPartonID, &b_jetPartonID);
   if ( IsMC() )
   {
   fChain->SetBranchAddress("jetGenPartonID", &jetGenPartonID, &b_jetGenPartonID);
   fChain->SetBranchAddress("jetHadFlvr", &jetHadFlvr, &b_jetHadFlvr);
   fChain->SetBranchAddress("jetGenPartonMomID", &jetGenPartonMomID, &b_jetGenPartonMomID);
   fChain->SetBranchAddress("calib_scEtaWidth", &calib_scEtaWidth, &b_calib_scEtaWidth);
   fChain->SetBranchAddress("calib_r9Full5x5", &calib_r9Full5x5, &b_calib_r9Full5x5);
   fChain->SetBranchAddress("calib_s4", &calib_s4, &b_calib_s4);
   fChain->SetBranchAddress("calib_sieieFull5x5", &calib_sieieFull5x5, &b_calib_sieieFull5x5);
   fChain->SetBranchAddress("nLHE", &nLHE, &b_nLHE);
   fChain->SetBranchAddress("lhePID", lhePID, &b_lhePID);
   fChain->SetBranchAddress("lheE", lheE, &b_lheE);
   fChain->SetBranchAddress("lhePx", lhePx, &b_lhePx);
   fChain->SetBranchAddress("lhePy", lhePy, &b_lhePy);
   fChain->SetBranchAddress("lhePz", lhePz, &b_lhePz);
   fChain->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
   }
   // fChain->SetBranchAddress("jetID", &jetID, &b_jetID);
   // fChain->SetBranchAddress("jetPUIDbit", &jetPUIDbit, &b_jetPUIDbit);
   if (!IsMC() )
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
   }
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
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}

bool MakeHisto::IsMC()
{ return fkMC; }
#endif // #ifdef MakeHisto_cxx

//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Aug  4 19:11:38 2015 by ROOT version 5.32/04
// from TTree t/mini tree
// found on file: ../SinglePho_Run2015B_PR_Jul24.root
//////////////////////////////////////////////////////////

#ifndef MakeHisto_h
#define MakeHisto_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class MakeHisto {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           run;
   Long64_t        event;
   Bool_t          isData;
   Long64_t        HLT;
   Long64_t        HLTIsPrescaled;
   //Long64_t        HLT50ns;
   //Long64_t        HLTIsPrescaled50ns;
   Int_t           phoFiredTrg;
   Float_t         pthat;
   Float_t         mcPt;
   Float_t         mcEta;
   Float_t         mcPhi;
   Float_t         recoPt;
   Float_t         recoEta;
   Float_t         recoPhi;
   Float_t         recoSCEta;
   Float_t         r9;
   Int_t           isMatched;
   Int_t           isMatchedEle;
   Int_t           isConverted;
   //Int_t           idLoose;
   //Int_t           idMedium;
   //Int_t           idTight;
   Int_t           nVtx;
   Int_t           nPU;
   Int_t           eleVeto;
   Float_t         HoverE;
   //Float_t         sieie;
   //Float_t         sieip;
   //Float_t         sipip;
   //Float_t         chIso;
   //Float_t         phoIso;
   //Float_t         nhIso;
   Float_t         chIsoRaw;
   Float_t         chWorstRaw;
   Float_t         phoIsoRaw;
   Float_t         nhIsoRaw;
   Float_t         rho;
   //Float_t         e1x3;
   //Float_t         e2x2;
   //Float_t         e2x5;
   //Float_t         e5x5;
   Float_t         rawE;
   Float_t         scEtaWidth;
   Float_t         scPhiWidth;
   Float_t         esRR;
   Float_t         esEn;
   Float_t         mva;
   Float_t         mva_nocorr;
   Float_t         photonIDmva; // is overwritten in line149@.C file. So read value is disabled
   //Float_t         mva_hgg;
   //Int_t           HggPresel;
   Float_t         sieieFull5x5;
   Float_t         sieipFull5x5;
   Float_t         sipipFull5x5;
   //Float_t         e1x3Full5x5;
   Float_t         r9Full5x5;
   Float_t         e2x2Full5x5;
   //Float_t         e2x5Full5x5;
   Float_t         e5x5Full5x5;
   Float_t         mcCalIso04;
   Float_t         mcTrkIso04;
   Float_t         xsweight;
   Float_t         puwei;
   //Float_t         Mmm;
   //Float_t         Mee;
   //Float_t         MTm;
   Float_t         MET;
   Int_t           phohasPixelSeed;
   Float_t         jetPt;
   Float_t         jetEta;
   Float_t         jetPhi;
   Float_t         jetY;
   Int_t           OPTION;
   Int_t           photon_jetID;
   Int_t HLTOPTION;
   //Float_t   deta_wg;
   //Float_t   dphi_wg;

   Float_t SeedTime;
   Float_t SeedEnergy;
   Float_t MIPTotEnergy;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_HLT;   //!
   TBranch        *b_HLTIsPrescaled;   //!
   //TBranch        *b_HLT50ns;   //!
   //TBranch        *b_HLTIsPrescaled50ns;   //!
   TBranch        *b_phoFiredTrgs;   //!
   TBranch        *b_pthat;   //!
   TBranch        *b_mcPt;   //!
   TBranch        *b_mcEta;   //!
   TBranch        *b_mcPhi;   //!
   TBranch        *b_recoPt;   //!
   TBranch        *b_recoEta;   //!
   TBranch        *b_recoPhi;   //!
   TBranch        *b_recoSCEta;   //!
   TBranch        *b_r9;   //!
   TBranch        *b_isMatched;   //!
   TBranch        *b_isMatchedEle;   //!
   TBranch        *b_isConverted;   //!
   //TBranch        *b_idLoose;   //!
   //TBranch        *b_idMedium;   //!
   //TBranch        *b_idTight;   //!
   TBranch        *b_nVtx;   //!
   TBranch        *b_nPU;   //!
   TBranch        *b_eleVeto;   //!
   TBranch        *b_HoverE;   //!
   //TBranch        *b_sieie;   //!
   //TBranch        *b_sieip;   //!
   //TBranch        *b_sipip;   //!
   //TBranch        *b_chIso;   //!
   //TBranch        *b_phoIso;   //!
   //TBranch        *b_nhIso;   //!
   TBranch        *b_chIsoRaw;   //!
   TBranch        *b_chWorstIso;   //!
   TBranch        *b_phoIsoRaw;   //!
   TBranch        *b_nhIsoRaw;   //!
   TBranch        *b_rho;   //!
   //TBranch        *b_e1x3;   //!
   //TBranch        *b_e2x2;   //!
   //TBranch        *b_e2x5;   //!
   //TBranch        *b_e5x5;   //!
   TBranch        *b_rawE;   //!
   TBranch        *b_scEtaWidth;   //!
   TBranch        *b_scPhiWidth;   //!
   TBranch        *b_esRR;   //!
   TBranch        *b_esEn;   //!
   TBranch        *b_mva;   //!
   TBranch        *b_mva_nocorr;   //!
   TBranch        *b_photonIDmva;   //!
   //TBranch        *b_mva_hgg;   //!
   //TBranch        *b_HggPresel;   //!
   TBranch        *b_sieieFull5x5;   //!
   TBranch        *b_sieipFull5x5;   //!
   TBranch        *b_sipipFull5x5;   //!
   //TBranch        *b_e1x3Full5x5;   //!
   TBranch        *b_r9Full5x5;   //!
   TBranch        *b_e2x2Full5x5;   //!
   //TBranch        *b_e2x5Full5x5;   //!
   TBranch        *b_e5x5Full5x5;   //!
   TBranch        *b_mcCalIso04;   //!
   TBranch        *b_mcTrkIso04;   //!
   TBranch        *b_xsweight;   //!
   TBranch        *b_puwei;   //!
   TBranch        *b_Mmm;   //!
   TBranch        *b_MTm;   //!
   TBranch        *b_MET;   //!
   TBranch        *b_Mee;   //!
   TBranch        *b_phohasPixelSeed;   
   TBranch        *b_jetPt;   //!
   TBranch        *b_jetEta;   //!
   TBranch        *b_jetPhi;   //!
   TBranch        *b_jetY;
   TBranch        *b_photon_jetID;
   //TBranch   *b_deta_wg;
   //TBranch   *b_dphi_wg;
   TBranch *b_SeedTime;
   TBranch *b_SeedEnergy;
   TBranch *b_MIPTotEnergy;


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


};

#endif

#ifdef MakeHisto_cxx
MakeHisto::MakeHisto(Int_t option) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.

  printf("option %d \n", option);
  HLTOPTION = 0;
  /* Init(tree); */
  TChain *tc = new TChain("t");
    //tc->Add("");

  if(option == 1) { // data
    tc->Add("/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root");
  };
  if(option == 2) { // madgraph sig MC
    tc->Add("/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root");
    //HLTOPTION=1; // prevent to use HLT
  }
  if(option == 3) { // madgraph QCD MC
    tc->Add("/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root");
    //HLTOPTION=1; // prevent to use HLT
  }
  if(option == 4) { // pythia   sig MC
    tc->Add("");
    //HLTOPTION=1; // prevent to use HLT
  }
  if(option == 5) { // pythia   QCD MC
    //HLTOPTION=1; // prevent to use HLT
  }

  if(option == 15) tc->Add("../qcd/job_spring*_qcd*.root");
  if(option == 8) tc->Add("../output_job_fall15_gjet_pt15to6000_miniAOD.root");
  if(option == 16) tc->Add("../gjet_MG.root");

  OPTION = option;

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

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("HLT", &HLT, &b_HLT);
   fChain->SetBranchAddress("HLTIsPrescaled", &HLTIsPrescaled, &b_HLTIsPrescaled);
   //fChain->SetBranchAddress("HLT50ns", &HLT50ns, &b_HLT50ns);
   //fChain->SetBranchAddress("HLTIsPrescaled50ns", &HLTIsPrescaled50ns, &b_HLTIsPrescaled50ns);
   fChain->SetBranchAddress("phoFiredTrgs", &phoFiredTrg, &b_phoFiredTrgs);
   fChain->SetBranchAddress("pthat", &pthat, &b_pthat);
   /* fChain->SetBranchAddress("mcPt", &mcPt, &b_mcPt); */
   /* fChain->SetBranchAddress("mcEta", &mcEta, &b_mcEta); */
   /* fChain->SetBranchAddress("mcPhi", &mcPhi, &b_mcPhi); */
   //fChain->SetBranchAddress("recoPt", &recoPt, &b_recoPt); // turn to use calibrated Pt
   fChain->SetBranchAddress("recoPtCalib", &recoPt, &b_recoPt);
   fChain->SetBranchAddress("recoEta", &recoEta, &b_recoEta);
   fChain->SetBranchAddress("recoPhi", &recoPhi, &b_recoPhi);
   fChain->SetBranchAddress("recoSCEta", &recoSCEta, &b_recoSCEta);
   fChain->SetBranchAddress("r9", &r9, &b_r9);
   fChain->SetBranchAddress("isMatched", &isMatched, &b_isMatched);
   fChain->SetBranchAddress("isMatchedEle", &isMatchedEle, &b_isMatchedEle);
   fChain->SetBranchAddress("isConverted", &isConverted, &b_isConverted);
   /* fChain->SetBranchAddress("idLoose", &idLoose, &b_idLoose); */
   /* fChain->SetBranchAddress("idMedium", &idMedium, &b_idMedium); */
   /* fChain->SetBranchAddress("idTight", &idTight, &b_idTight); */
   /* fChain->SetBranchAddress("nVtx", &nVtx, &b_nVtx); */
   /* fChain->SetBranchAddress("nPU", &nPU, &b_nPU); */
   fChain->SetBranchAddress("eleVeto", &eleVeto, &b_eleVeto);
   fChain->SetBranchAddress("HoverE", &HoverE, &b_HoverE);
   //fChain->SetBranchAddress("sieie", &sieie, &b_sieie);
   /* fChain->SetBranchAddress("sieip", &sieip, &b_sieip); */
   /* fChain->SetBranchAddress("sipip", &sipip, &b_sipip); */
   /* fChain->SetBranchAddress("chIso", &chIso, &b_chIso); */
   /* fChain->SetBranchAddress("phoIso", &phoIso, &b_phoIso); */
   /* fChain->SetBranchAddress("nhIso", &nhIso, &b_nhIso); */
   fChain->SetBranchAddress("chIsoRaw", &chIsoRaw, &b_chIsoRaw);
   fChain->SetBranchAddress("chWorstRaw", &chWorstRaw, &b_chWorstIso);
   fChain->SetBranchAddress("phoIsoRaw", &phoIsoRaw, &b_phoIsoRaw);
   fChain->SetBranchAddress("nhIsoRaw", &nhIsoRaw, &b_nhIsoRaw);
   fChain->SetBranchAddress("rho", &rho, &b_rho); 
   /* fChain->SetBranchAddress("e1x3", &e1x3, &b_e1x3); */
   /* fChain->SetBranchAddress("e2x2", &e2x2, &b_e2x2); */
   /* fChain->SetBranchAddress("e2x5", &e2x5, &b_e2x5); */
   /* fChain->SetBranchAddress("e5x5", &e5x5, &b_e5x5); */
   fChain->SetBranchAddress("rawE", &rawE, &b_rawE);
   fChain->SetBranchAddress("scEtaWidth", &scEtaWidth, &b_scEtaWidth);
   fChain->SetBranchAddress("scPhiWidth", &scPhiWidth, &b_scPhiWidth);
   fChain->SetBranchAddress("esRR", &esRR, &b_esRR);
   fChain->SetBranchAddress("esEn", &esEn, &b_esEn);
   fChain->SetBranchAddress("mva", &mva, &b_mva);
   fChain->SetBranchAddress("mva_nocorr", &mva_nocorr, &b_mva_nocorr);
   //fChain->SetBranchAddress("photonIDmva", &photonIDmva, &b_photonIDmva);
   //fChain->SetBranchAddress("mva_hgg", &mva_hgg, &b_mva_hgg);
   //fChain->SetBranchAddress("HggPresel", &HggPresel, &b_HggPresel);
   fChain->SetBranchAddress("sieieFull5x5", &sieieFull5x5, &b_sieieFull5x5);
   fChain->SetBranchAddress("sieipFull5x5", &sieipFull5x5, &b_sieipFull5x5);
   /* fChain->SetBranchAddress("sipipFull5x5", &sipipFull5x5, &b_sipipFull5x5); */
   //fChain->SetBranchAddress("e1x3Full5x5", &e1x3Full5x5, &b_e1x3Full5x5);
   /* fChain->SetBranchAddress("r9Full5x5", &r9Full5x5, &b_r9Full5x5); */
   fChain->SetBranchAddress("e2x2Full5x5", &e2x2Full5x5, &b_e2x2Full5x5);
   //fChain->SetBranchAddress("e2x5Full5x5", &e2x5Full5x5, &b_e2x5Full5x5);
   fChain->SetBranchAddress("e5x5Full5x5", &e5x5Full5x5, &b_e5x5Full5x5);
    fChain->SetBranchAddress("mcCalIso04", &mcCalIso04, &b_mcCalIso04);
   /* fChain->SetBranchAddress("mcTrkIso04", &mcTrkIso04, &b_mcTrkIso04); */
   fChain->SetBranchAddress("xsweight", &xsweight, &b_xsweight);
   fChain->SetBranchAddress("puwei", &puwei, &b_puwei);
   //fChain->SetBranchAddress("Mmm", &Mmm, &b_Mmm);
   //fChain->SetBranchAddress("MTm", &MTm, &b_MTm);
   fChain->SetBranchAddress("MET", &MET, &b_MET);
   //fChain->SetBranchAddress("Mee", &Mee, &b_Mee);
   fChain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed, &b_phohasPixelSeed);
   fChain->SetBranchAddress("jetPt", &jetPt, &b_jetPt);
   fChain->SetBranchAddress("jetEta", &jetEta, &b_jetEta);
   fChain->SetBranchAddress("jetPhi", &jetPhi, &b_jetPhi);
   fChain->SetBranchAddress("jetY", &jetY, &b_jetY);
   fChain->SetBranchStatus("mcEta", 0);
   fChain->SetBranchStatus("mcPhi", 0);
   //fChain->SetBranchStatus("idLoose", 0);
   //fChain->SetBranchStatus("idMedium", 0);
   //fChain->SetBranchStatus("idTight", 0);
   fChain->SetBranchStatus("nVtx", 0);
   fChain->SetBranchStatus("nPU", 0);
   //fChain->SetBranchStatus("sieip", 0);
   //fChain->SetBranchStatus("sipip", 0);
   //fChain->SetBranchStatus("chIso", 0);
   //fChain->SetBranchStatus("phoIso", 0);
   //fChain->SetBranchStatus("nhIso", 0);
   /* fChain->SetBranchStatus("rho", 0); */
   //fChain->SetBranchStatus("e1x3", 0);
   //fChain->SetBranchStatus("e2x2", 0);
   //fChain->SetBranchStatus("e2x5", 0);
   //fChain->SetBranchStatus("e5x5", 0);
   /* fChain->SetBranchStatus("rawE", 0); */
   /* fChain->SetBranchStatus("scEtaWidth", 0); */
   /* fChain->SetBranchStatus("scPhiWidth", 0); */
   /* fChain->SetBranchStatus("esRR", 0); */
   /* fChain->SetBranchStatus("esEn", 0); */
   /* fChain->SetBranchStatus("sieipFull5x5", 0); */
   /* fChain->SetBranchStatus("sipipFull5x5", 0); */
   /* fChain->SetBranchStatus("e1x3Full5x5", 0); */
   fChain->SetBranchStatus("r9Full5x5", 0);
   /* fChain->SetBranchStatus("e2x2Full5x5", 0); */
   /* fChain->SetBranchStatus("e2x5Full5x5", 0); */
   /* fChain->SetBranchStatus("e5x5Full5x5", 0); */
   fChain->SetBranchStatus("mcCalIso04", 0);
   fChain->SetBranchStatus("mcTrkIso04", 0);
   //fChain->SetBranchAddress("photon_jetID", &photon_jetID, &b_photon_jetID);   
   //fChain->SetBranchAddress("deta_wg",&deta_wg, &b_deta_wg);
   //fChain->SetBranchAddress("dphi_wg",&dphi_wg, &b_dphi_wg);

   fChain->SetBranchAddress("SeedTime",&SeedTime, &b_SeedTime);
   fChain->SetBranchAddress("SeedEnergy",&SeedEnergy, &b_SeedEnergy);
   fChain->SetBranchAddress("MIPTotEnergy",&MIPTotEnergy, &b_MIPTotEnergy);

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
#endif // #ifdef MakeHisto_cxx

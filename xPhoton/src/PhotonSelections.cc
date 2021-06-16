#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include <TMath.h>
#include <TMVA/Reader.h>
#include <TFile.h>
#include <TGraph.h>
#include <string>

// pre-selection of photon.
Int_t PhotonPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto) {
  Int_t phoID=1;

  // load relevant branches from TTree/TChain
  //Int_t    nPho                = data.GetInt("nPho");
  Float_t* phoEt               = data.GetPtrFloat("phoEt");
  Float_t* phoSCEta            = data.GetPtrFloat("phoSCEta");
  Int_t*   phoEleVeto          = data.GetPtrInt("phoEleVeto");
  Float_t* phoSigmaIEtaIEta    = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  //Float_t* phoR9               = data.GetPtrFloat("phoR9");
  Float_t* phoHoverE           = data.GetPtrFloat("phoHoverE");
  Float_t* phoPFPhoIso         = data.GetPtrFloat("phoPFPhoIso");
  Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso");

  
  if (phoEt[ipho] < 10.) phoID = 0;
  if (TMath::Abs(phoSCEta[ipho]) > 1.4442 && TMath::Abs(phoSCEta[ipho]) < 1.566) phoID = 0;
  //if (TMath::Abs(phoSCEta[ipho]) > 2.5) phoID = 0;
  if (TMath::Abs(phoSCEta[ipho]) > 3.) phoID = 0;
  if (eleVeto && phoEleVeto[ipho] == 0) phoID = 0;  

  //return phoID; //for X750 analysis
  
  //for EB
  if (TMath::Abs(phoSCEta[ipho]) < 1.5) {
    if(phoPFChWorstIso[ipho] > 15.) phoID=0;
    if(phoPFPhoIso[ipho] > 15.) phoID=0;
    if(phoSigmaIEtaIEta[ipho] > 0.015) phoID=0;
    if(phoHoverE[ipho] > 0.08) phoID=0;
  }else{ //EE
    if(phoPFChWorstIso[ipho] > 15.) phoID=0;
    if(phoPFPhoIso[ipho] > 15.) phoID=0;
    if(phoSigmaIEtaIEta[ipho] > 0.045) phoID=0;
    if(phoHoverE[ipho] > 0.05) phoID=0;
    //if(phoR9[ipho] < 0.85) phoID=0; //disable this for Zg analysis
  }    
  return phoID; 

}

Int_t PhotonSkimPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto) {
  Int_t phoID=1;

  // load relevant branches from TTree/TChain
  //Int_t    nPho                = data.GetInt("nPho");
  Float_t* phoEt               = data.GetPtrFloat("phoEt");
  Float_t* phoSCEta            = data.GetPtrFloat("phoSCEta");
  Int_t*   phoEleVeto          = data.GetPtrInt("phoEleVeto");
  /* Float_t* phoSigmaIEtaIEta    = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5"); */
  /* Float_t* phoR9               = data.GetPtrFloat("phoR9"); */
  /* Float_t* phoHoverE           = data.GetPtrFloat("phoHoverE"); */
  /* Float_t* phoPFPhoIso         = data.GetPtrFloat("phoPFPhoIso"); */
  /* Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso"); */

  
  if (phoEt[ipho] < 15.) phoID = 0;
  //if (phoEt[ipho] > 200.) phoID = 0;
  if (TMath::Abs(phoSCEta[ipho]) > 1.4442 && TMath::Abs(phoSCEta[ipho]) < 1.566) phoID = 0;
  if (TMath::Abs(phoSCEta[ipho]) > 2.5) phoID = 0;
  if (eleVeto && phoEleVeto[ipho] == 0) phoID = 0;  

  //return phoID; //for X750 analysis
  /* if(phoPFChWorstIso[ipho] > 20.) phoID=0; */
  /* //if(phoPFPhoIso[ipho] > 20.) phoID=0; */
  /* if(phoPFPhoIso[ipho] > 50.) phoID=0; */
  /* if(phoHoverE[ipho] > 0.15) phoID=0;   */
  /* //for EB */
  /* if (TMath::Abs(phoSCEta[ipho]) < 1.5) { */
  /*   if(phoSigmaIEtaIEta[ipho] > 0.015) phoID=0; */
  /* }else{ //EE */
  /*   if(phoSigmaIEtaIEta[ipho] > 0.032) phoID=0; */
  /* }     */
  return phoID;

}


Int_t HggPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto) {

  Int_t phoID=1;

  // load relevant branches from TTree/TChain
  //Int_t    nPho                = data.GetInt("nPho");
  Float_t* phoEt               = data.GetPtrFloat("phoEt");
  Float_t* phoSCEta            = data.GetPtrFloat("phoSCEta");
  Int_t*   phoEleVeto          = data.GetPtrInt("phoEleVeto");
  Float_t* phoSigmaIEtaIEta    = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  Float_t* phoR9               = data.GetPtrFloat("phoR9");
  Float_t* phoHoverE           = data.GetPtrFloat("phoHoverE");
  Float_t* phoPFChIso        = data.GetPtrFloat("phoPFChIso");
  Float_t* phoPFPhoIso         = data.GetPtrFloat("phoPFPhoIso");
  //vector<float>* phoCiCPF4chgpfIso02 = data.GetPtrVectorFloat("phoCiCPF4chgpfIso02", nPho);
                              
  if (phoEt[ipho] < 15.) phoID = 0;
  //if (phoEt[ipho] > 200.) phoID = 0;
  if (TMath::Abs(phoSCEta[ipho]) > 1.4442 && TMath::Abs(phoSCEta[ipho]) < 1.566) phoID = 0;
  if (TMath::Abs(phoSCEta[ipho]) > 2.5) phoID = 0;
  if (eleVeto && phoEleVeto[ipho] == 0) phoID = 0;  

  // Hgg photon Preselection-------------
  if (phoHoverE[ipho] >= 0.08) phoID = 0;

  //for EB
  if (TMath::Abs(phoSCEta[ipho]) < 1.5) {
    if (phoR9[ipho] <= 0.5) phoID=0;
    if (phoSigmaIEtaIEta[ipho] >= 0.015) phoID = 0;
    if (phoR9[ipho] < 0.85) {
      if(phoPFPhoIso[ipho] > 4.) phoID=0;
      if(phoPFChIso[ipho] > 6.) phoID=0;
    }
  } else { //for EE
    if (phoR9[ipho] <= 0.8) phoID=0;
    if (phoSigmaIEtaIEta[ipho] >= 0.035) phoID = 0;
    if (phoR9[ipho] < 0.9) {
      if(phoPFPhoIso[ipho] > 4.) phoID=0;
      if(phoPFChIso[ipho] > 6.) phoID=0;
    }
  }
  //end of Hgg preselection----------
  
  return phoID;
}

void select_photon(Int_t iWP, TreeReader &data, std::vector<int>& accepted) {

  accepted.clear();
  // load relevant branches from TTree/TChain
  Int_t    nPho                = data.GetInt("nPho");
  Float_t* phoEt               = data.GetPtrFloat("phoEt");
  Float_t* phoSCEta            = data.GetPtrFloat("phoSCEta");
  Int_t*   phoEleVeto          = data.GetPtrInt("phoEleVeto");
  Float_t* phoSigmaIEtaIEta    = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  Float_t* phoHoverE           = data.GetPtrFloat("phoHoverE");
  Float_t* phoPFChIso          = data.GetPtrFloat("phoPFChIso");
  Float_t* phoPFNeuIso         = data.GetPtrFloat("phoPFNeuIso");
  Float_t* phoPFPhoIso         = data.GetPtrFloat("phoPFPhoIso");
  Float_t  rho                = data.GetFloat("rho");

  for (int iPho = 0; iPho < nPho; ++iPho) {

    if (phoEt[iPho] < 10. ) continue ;
    
    Int_t phoEB = 0 ;
    if (iWP == -1 ) continue ;
    if ( fabs(phoSCEta[iPho]) >= 1.566 ) phoEB = 1 ;
    if ( phoEleVeto[iPho] != 0 ) continue ;
    if ( phoHoverE[iPho] > 0.05 ) continue ;
    // left : cut for EB. right : cut for EE
    Float_t sIEIECut[3][2] = { { 0.012 , 0.034 } , { 0.011 , 0.033 } , { 0.011 , 0.031 } } ;
    if ( phoSigmaIEtaIEta[iPho] >= sIEIECut[iWP][phoEB] ) continue ;
    Float_t effArea[3][7] = { //[Ch,Nu,Pho][iPhof_eta]
      { 0.012 , 0.010 , 0.014 , 0.012 , 0.016 , 0.020 , 0.012 } ,
      { 0.030 , 0.057 , 0.039 , 0.015 , 0.024 , 0.039 , 0.072 } ,
      { 0.148 , 0.130 , 0.112 , 0.216 , 0.262 , 0.260 , 0.266 } 
    } ;
    Int_t i_effArea = 0 ; // effective area for pile up correction for DR04 combine rel. Iso
    if      ( fabs(phoSCEta[iPho]) < 1.0                                        ) i_effArea = 0 ;
    else if ( fabs(phoSCEta[iPho]) >= 1.0   && fabs(phoSCEta[iPho]) < 1.479  ) i_effArea = 1 ;
    else if ( fabs(phoSCEta[iPho]) >= 1.479 && fabs(phoSCEta[iPho]) < 2.0    ) i_effArea = 2 ;
    else if ( fabs(phoSCEta[iPho]) >= 2.0   && fabs(phoSCEta[iPho]) < 2.2    ) i_effArea = 3 ;
    else if ( fabs(phoSCEta[iPho]) >= 2.2   && fabs(phoSCEta[iPho]) < 2.3    ) i_effArea = 4 ;
    else if ( fabs(phoSCEta[iPho]) >= 2.3   && fabs(phoSCEta[iPho]) < 2.4    ) i_effArea = 5 ;
    else if ( fabs(phoSCEta[iPho]) >= 2.4                                       ) i_effArea = 6 ;
    Float_t chIsoCut[3][2] = { {2.6,2.3} , {1.5,1.2} , {0.7,0.5} } ; //[Loose,Medium,Tight][EB,EE]
    float corrIso = (float) TMath::Max( float(0.) , phoPFChIso[iPho] - ( effArea[0][i_effArea] * rho ) ) ;
    if ( corrIso >= chIsoCut[iWP][phoEB] ) continue ;
    Float_t neuIsoCut[3][2] = { { 3.5, 2.9 } , { 1.0, 1.5 } , { 0.4, 1.5 } } ; //[Loose,Medium,Tight][EB,EE]
    for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) neuIsoCut[i][j] += ( 0.04 * phoEt[iPho] );
    corrIso = TMath::Max( float(0.) , phoPFNeuIso[iPho] - ( effArea[1][i_effArea] * rho ) ) ;
    if ( corrIso >= neuIsoCut[iWP][phoEB] ) continue ;
    Float_t gammaIsoCut[3][2] = { {1.3,999.} , {0.7,1.0} , {0.5,1.0} } ; //[Loose,Medium,Tight][EB,EE]
    for (int i = 0; i < 3; i++) for (int j = 0; j < 2; j++) gammaIsoCut[i][j] += ( 0.005 * phoEt[iPho] ) ;
    corrIso = TMath::Max( float(0.) , phoPFPhoIso[iPho] - ( effArea[2][i_effArea] * rho ) ) ;
    if ( corrIso >= gammaIsoCut[iWP][phoEB] ) continue ;
    accepted.push_back(iPho);
  }

}

/*
float select_photon_mva(TreeReader &data, Int_t i, TGraph *tgr[20]) {
  // Photon identification with the Zgamma MVA. Returns the MVA evaluated value.
  //
  // Documentation:
  // https://indico.cern.ch/getFile.py/access?contribId=3&resId=0&materialId=slides&confId=298231
  //
  // data = handle providing access to an input event;
  // i = index of a photon candidate to consider.

  // load necessary tree branches
  Float_t* phoEt             = data.GetPtrFloat("phoEt");
  Float_t* phoEta            = data.GetPtrFloat("phoEta");
  Float_t* phoPhi            = data.GetPtrFloat("phoPhi");
  Float_t* phoR9             = data.GetPtrFloat("phoR9");
  //asdfFloat_t* phoSigmaIEtaIEta  = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  //asdfFloat_t* phoSigmaIEtaIPhi  = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
  //asdfFloat_t* phoE1x3           = data.GetPtrFloat("phoE1x3");
  Float_t* phoE2x2           = data.GetPtrFloat("phoE2x2");
  Float_t* phoE5x5           = data.GetPtrFloat("phoE5x5");
  //asdfFloat_t* phoE2x5Max        = data.GetPtrFloat("phoE2x5Max");
  Float_t* phoSCEta          = data.GetPtrFloat("phoSCEta");
  Float_t* phoSCRawE         = data.GetPtrFloat("phoSCRawE");
  Float_t* phoSCEtaWidth     = data.GetPtrFloat("phoSCEtaWidth");
  Float_t* phoSCPhiWidth     = data.GetPtrFloat("phoSCPhiWidth");
  Float_t  rho               = data.GetFloat("rho");
  Float_t* phoPFPhoIso       = data.GetPtrFloat("phoPFPhoIso");
  Float_t* phoPFChIso        = data.GetPtrFloat("phoPFChIso");
  Float_t* phoESEnP1           = data.GetPtrFloat("phoESEnP1");
  Float_t* phoESEnP2           = data.GetPtrFloat("phoESEnP2");

  Float_t* phoESEffSigmaRR   = data.GetPtrFloat("phoESEffSigmaRR");
  Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso");

  Float_t* phoSigmaIEtaIEtaFull5x5  = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  Float_t* phoSigmaIEtaIPhiFull5x5  = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
  //Float_t* phoSigmaIPhiIPhiFull5x5  = data.GetPtrFloat("phoSigmaIPhiIPhiFull5x5");  
  Float_t* phoE1x3Full5x5           = data.GetPtrFloat("phoE1x3Full5x5");
  Float_t* phoE2x2Full5x5            = data.GetPtrFloat("phoE2x2Full5x5");
  Float_t* phoE5x5Full5x5            = data.GetPtrFloat("phoE5x5Full5x5");
  Float_t* phoE2x5MaxFull5x5        = data.GetPtrFloat("phoE2x5MaxFull5x5");

  // classification variables
  static float phoEt_, phoEta_, phoPhi_, phoR9_;
  //asdfstatic float phoSigmaIEtaIEta_, phoSigmaIEtaIPhi_;
  //asdfstatic float phoS13_, phoS4_, phoS25_;
  static float phoSCEta_, phoSCRawE_;
  static float phoSCEtaWidth_, phoSCPhiWidth_, rho_;
  static float phoPFPhoIso_, phoPFChIso_, phoPFChIsoWorst_;
  static float phoESEnToRawE_, phoESEffSigmaRR_;

  static float sieieFull5x5, sieipFull5x5, s13Full5x5, s4Full5x5, s25Full5x5;


  // MVA classifiers for 0=ECAL barrel and 1=ECAL endcaps
  static TMVA::Reader* tmvaReader[2] = {NULL, NULL};

  // 0=ECAL barrel or 1=ECAL endcaps
  int iBE = (fabs(phoSCEta[i]) < 1.479) ? 0 : 1;

  // one-time MVA initialization
  if (!tmvaReader[iBE]) {
    tmvaReader[iBE] = new TMVA::Reader("!Color:Silent");

    // add classification variables
    tmvaReader[iBE]->AddVariable("recoPhi", &phoPhi_); // var0
    tmvaReader[iBE]->AddVariable("r9", &phoR9_); // var1
    tmvaReader[iBE]->AddVariable( "sieieFull5x5",       	      &sieieFull5x5 );      // var2
    tmvaReader[iBE]->AddVariable( "sieipFull5x5",       	      &sieipFull5x5 );      // var 3
    // tmvaReader[iBE]->AddVariable( "s13 := e1x3Full5x5/e5x5Full5x5",   &s13Full5x5 );	        // abandoned
    tmvaReader[iBE]->AddVariable( "s4 := e2x2Full5x5/e5x5Full5x5",    &s4Full5x5 );	       // var 4
    // tmvaReader[iBE]->AddVariable( "s25 := e2x5Full5x5/e5x5Full5x5",   &s25Full5x5 );	        // abandoned
    tmvaReader[iBE]->AddVariable("recoSCEta", &phoSCEta_); // var 5
    tmvaReader[iBE]->AddVariable("rawE", &phoSCRawE_); // var 6
    tmvaReader[iBE]->AddVariable("scEtaWidth", &phoSCEtaWidth_); // var 7
    tmvaReader[iBE]->AddVariable("scPhiWidth", &phoSCPhiWidth_); // var 8
    if (iBE == 1) {
      tmvaReader[iBE]->AddVariable("ESEn := esEn/rawE", &phoESEnToRawE_); // EE only : var 9*
      tmvaReader[iBE]->AddVariable("esRR", &phoESEffSigmaRR_); // EE only : var 10*
    }
    tmvaReader[iBE]->AddVariable("rho", &rho_); // var 9 or var 11*
    // tmvaReader[iBE]->AddVariable("phoIsoRaw", &phoPFPhoIso_);
    // tmvaReader[iBE]->AddVariable("chIsoRaw", &phoPFChIso_);
    // tmvaReader[iBE]->AddVariable("chWorstRaw", &phoPFChIsoWorst_);

    //tmvaReader[iBE]->AddVariable("recoPt", &phoEt_);
    // FIXME: why do we need this?
    tmvaReader[iBE]->AddSpectator("recoPt", &phoEt_);
    tmvaReader[iBE]->AddSpectator("recoEta", &phoEta_);

    // read weight files
    const char* xmlFile_MVAweight(int isEndcap, int year);
    std::cerr << ExternalFilesMgr::xmlFile_MVAweight(iBE, 2016) << std::endl;
    tmvaReader[iBE]->BookMVA("BDT", ExternalFilesMgr::xmlFile_MVAweight(iBE, 2016) );
  } // one-time initialization

  //get etawidth, s4, R9  reweighting for 76x

  // set MVA variables
  phoPhi_ = phoPhi[i];
  phoR9_ = phoR9[i];
  //asdfphoSigmaIEtaIEta_ = phoSigmaIEtaIEta[i];
  //asdfphoSigmaIEtaIPhi_ = phoSigmaIEtaIPhi[i];
  //asdfphoS4_ = phoE2x2[i]/phoE5x5[i];
  //asdfphoS13_ = phoE1x3[i]/phoE5x5[i];
  //asdfphoS25_ = phoE2x5Max[i]/phoE5x5[i];
  phoSCEta_ = phoSCEta[i];
  phoSCRawE_ = phoSCRawE[i];
  phoSCEtaWidth_ = phoSCEtaWidth[i];
  phoSCPhiWidth_ = phoSCPhiWidth[i];
  rho_ = rho;
  phoESEnToRawE_ = (phoESEnP1[i]+phoESEnP2[i])/phoSCRawE[i];
  phoESEffSigmaRR_= phoESEffSigmaRR[i];
  phoEt_ = phoEt[i];
  phoEta_ = phoEta[i];
  phoPFPhoIso_ = phoPFPhoIso[i];
  phoPFChIso_ = phoPFChIso[i];
  phoPFChIsoWorst_ = phoPFChWorstIso[i];
  
  sieieFull5x5 = phoSigmaIEtaIEtaFull5x5[i];
  sieipFull5x5 = phoSigmaIEtaIPhiFull5x5[i];

  s13Full5x5 = phoE1x3Full5x5[i]/phoE5x5Full5x5[i];
  s4Full5x5 = phoE2x2Full5x5[i]/phoE5x5Full5x5[i];
  s25Full5x5 = phoE2x5MaxFull5x5[i]/phoE5x5Full5x5[i];
  
  if(data.HasMC() && TMath::Abs(phoSCEta[i])<1.5) {
    phoSCEtaWidth_ = tgr[0]->Eval(phoSCEtaWidth[i]);
    s4Full5x5 = tgr[1]->Eval(phoE2x2[i]/phoE5x5[i]);
    phoR9_ = tgr[2]->Eval(phoR9[i]);
    // phoR9_		= tgr[1]->Eval(phoR9_);
    // s13Full5x5          = tgr[2]->Eval(s13Full5x5);
    // s4Full5x5           = tgr[3]->Eval(s4Full5x5);
    // s25Full5x5          = tgr[4]->Eval(s25Full5x5);
    // sieieFull5x5        = tgr[5]->Eval(sieieFull5x5);
    // sieipFull5x5        = tgr[6]->Eval(sieipFull5x5);
    // phoSCEtaWidth_	= tgr[9]->Eval(phoSCEtaWidth_);
    // phoSCPhiWidth_	= tgr[10]->Eval(phoSCPhiWidth_);

  }


  return tmvaReader[iBE]->EvaluateMVA("BDT");

}
*/

float select_photon_mvanoIso(TreeReader &data, Int_t i, TGraph *tgr[20]) {
  /* Photon identification with the Zgamma MVA. Returns the MVA evaluated value.
   *
   * Documentation:
   * https://indico.cern.ch/getFile.py/access?contribId=3&resId=0&materialId=slides&confId=298231
   *
   * data = handle providing access to an input event;
   * i = index of a photon candidate to consider.
   */
  Int_t run                  = data.GetInt("run");
  // load necessary tree branches
  Float_t* phoEt             = data.GetPtrFloat("phoEt");
  Float_t* phoEta            = data.GetPtrFloat("phoEta");
  Float_t* phoPhi            = data.GetPtrFloat("phoPhi");
  Float_t* phoR9             = data.GetPtrFloat("phoR9");
  Float_t* phoSCEta          = data.GetPtrFloat("phoSCEta");
  Float_t* phoSCRawE         = data.GetPtrFloat("phoSCRawE");
  Float_t* phoSCEtaWidth     = data.GetPtrFloat("phoSCEtaWidth");
  Float_t* phoSCPhiWidth     = data.GetPtrFloat("phoSCPhiWidth");
  Float_t  rho               = data.GetFloat("rho");
  /* Float_t* phoPFPhoIso       = data.GetPtrFloat("phoPFPhoIso"); */
  /* Float_t* phoPFChIso        = data.GetPtrFloat("phoPFChIso"); */
  /* Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso"); */
  Float_t* phoESEnP1           = data.GetPtrFloat("phoESEnP1");
  Float_t* phoESEnP2           = data.GetPtrFloat("phoESEnP2");
  Float_t* phoESEffSigmaRR   = data.GetPtrFloat("phoESEffSigmaRR");

  Float_t* phoSigmaIEtaIEtaFull5x5  = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  Float_t* phoSigmaIEtaIPhiFull5x5  = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
  Float_t* phoE2x2Full5x5            = data.GetPtrFloat("phoE2x2Full5x5");
  Float_t* phoE5x5Full5x5            = data.GetPtrFloat("phoE5x5Full5x5");

  // classification variables
  static float phoEt_, phoEta_, phoPhi_, phoR9_;
  static float phoSCEtaWidth_, phoSCPhiWidth_, rho_;
  static float phoSCEta_, phoSCRawE_;
  //static float phoPFPhoIso_, phoPFChIso_, phoPFChIsoWorst_;
  static float phoESEnToRawE_, phoESEffSigmaRR_;

  static float sieieFull5x5, sieipFull5x5, s13Full5x5, s4Full5x5, s25Full5x5;


  // MVA classifiers for 0=ECAL barrel and 1=ECAL endcaps
  static TMVA::Reader* tmvaReader[2] = {NULL, NULL};

  // 0=ECAL barrel or 1=ECAL endcaps
  int iBE = (fabs(phoSCEta[i]) < 1.479) ? 0 : 1;

  // one-time MVA initialization
  if (!tmvaReader[iBE]) {
    tmvaReader[iBE] = new TMVA::Reader("!Color:Silent");

    // add classification variables
    tmvaReader[iBE]->AddVariable("recoPhi", &phoPhi_);
    tmvaReader[iBE]->AddVariable("r9", &phoR9_);
    tmvaReader[iBE]->AddVariable( "sieieFull5x5",       	      &sieieFull5x5 );     
    tmvaReader[iBE]->AddVariable( "sieipFull5x5",       	      &sieipFull5x5 );     
    //tmvaReader[iBE]->AddVariable( "s13 := e1x3Full5x5/e5x5Full5x5",   &s13Full5x5 );	        
    tmvaReader[iBE]->AddVariable( "s4 := e2x2Full5x5/e5x5Full5x5",    &s4Full5x5 );	       
    //tmvaReader[iBE]->AddVariable( "s25 := e2x5Full5x5/e5x5Full5x5",   &s25Full5x5 );	        
    tmvaReader[iBE]->AddVariable("recoSCEta", &phoSCEta_);
    tmvaReader[iBE]->AddVariable("rawE", &phoSCRawE_);
    tmvaReader[iBE]->AddVariable("scEtaWidth", &phoSCEtaWidth_);
    tmvaReader[iBE]->AddVariable("scPhiWidth", &phoSCPhiWidth_);
    if (iBE == 1) {
      tmvaReader[iBE]->AddVariable("ESEn := esEn/rawE", &phoESEnToRawE_);
      tmvaReader[iBE]->AddVariable("esRR", &phoESEffSigmaRR_);
    }
    tmvaReader[iBE]->AddVariable("rho", &rho_);
    /* tmvaReader[iBE]->AddVariable("phoIsoRaw", &phoPFPhoIso_); */
    /* tmvaReader[iBE]->AddVariable("chIsoRaw", &phoPFChIso_); */
    /* tmvaReader[iBE]->AddVariable("chWorstRaw", &phoPFChIsoWorst_); */

    //tmvaReader[iBE]->AddVariable("recoPt", &phoEt_);
    // FIXME: why do we need this?
    //tmvaReader[iBE]->AddSpectator("recoPt", &phoEt_);
    //tmvaReader[iBE]->AddSpectator("recoEta", &phoEta_);

    std::cerr << ExternalFilesMgr::xmlFile_MVAweight(iBE, 2016) << std::endl;
    tmvaReader[iBE]->BookMVA("BDT", ExternalFilesMgr::xmlFile_MVAweight(iBE, 2016) );
  } // one-time initialization
  
  //get etawidth, s4, R9  reweighting for 76x

  // set MVA variables
  phoPhi_ = phoPhi[i];
  phoR9_ = phoR9[i];
  phoSCEta_ = phoSCEta[i];
  phoSCRawE_ = phoSCRawE[i];
  phoSCEtaWidth_ = phoSCEtaWidth[i];
  phoSCPhiWidth_ = phoSCPhiWidth[i];
  rho_ = rho;
  phoESEnToRawE_ = (phoESEnP1[i]+phoESEnP2[i])/phoSCRawE[i];
  phoESEffSigmaRR_= phoESEffSigmaRR[i];
  phoEt_ = phoEt[i];
  phoEta_ = phoEta[i];
  
  sieieFull5x5 = phoSigmaIEtaIEtaFull5x5[i];
  sieipFull5x5 = phoSigmaIEtaIPhiFull5x5[i];
  s4Full5x5 = phoE2x2Full5x5[i]/phoE5x5Full5x5[i];
  
  if(data.HasMC()) {
    if ( tgr ) {
      if(TMath::Abs(phoSCEta[i])<1.5) {
        phoSCEtaWidth_	= tgr[0]->Eval(phoSCEtaWidth_);
        s4Full5x5       = tgr[1]->Eval(s4Full5x5);
        phoR9_		    = tgr[2]->Eval(phoR9_);
        sieieFull5x5    = tgr[3]->Eval(sieieFull5x5);
      } else {
        phoSCEtaWidth_	= tgr[4]->Eval(phoSCEtaWidth_);
        s4Full5x5       = tgr[5]->Eval(s4Full5x5);
        phoR9_		    = tgr[6]->Eval(phoR9_);
        sieieFull5x5    = tgr[7]->Eval(sieieFull5x5);

      }      
    }
  }

  return tmvaReader[iBE]->EvaluateMVA("BDT");

}


/*
float select_photon_mva_hgg(TreeReader &data, Int_t i) {

  // load necessary tree branches
  Float_t* phoR9             = data.GetPtrFloat("phoR9");
  Float_t* phoSCEta          = data.GetPtrFloat("phoSCEta");
  Float_t* phoSCRawE         = data.GetPtrFloat("phoSCRawE");
  Float_t* phoSCEtaWidth     = data.GetPtrFloat("phoSCEtaWidth");
  Float_t* phoSCPhiWidth     = data.GetPtrFloat("phoSCPhiWidth");
  Float_t  rho               = data.GetFloat("rho");
  Float_t* phoPFPhoIso       = data.GetPtrFloat("phoPFPhoIso");
  Float_t* phoPFChIso        = data.GetPtrFloat("phoPFChIso");
  Float_t* phoESEffSigmaRR   = data.GetPtrFloat("phoESEffSigmaRR");
  Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso");

  Float_t* phoSigmaIEtaIEtaFull5x5  = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  Float_t* phoSigmaIEtaIPhiFull5x5  = data.GetPtrFloat("phoSigmaIEtaIPhiFull5x5");
  Float_t* phoE2x2Full5x5            = data.GetPtrFloat("phoE2x2Full5x5");
  Float_t* phoE5x5Full5x5            = data.GetPtrFloat("phoE5x5Full5x5");

  // classification variables
  static float phoR9_;
  static float phoSCEta_, phoSCRawE_;
  static float phoSCEtaWidth_, phoSCPhiWidth_, rho_;
  static float phoPFPhoIso_, phoPFChIso_, phoPFChIsoWorst_;
  static float phoESEffSigmaRR_;

  static float sieieFull5x5, sieipFull5x5, s4Full5x5;

  // MVA classifiers for 0=ECAL barrel and 1=ECAL endcaps
  static TMVA::Reader* tmvaReader[2] = {NULL, NULL};

  // 0=ECAL barrel or 1=ECAL endcaps
  int iBE = (fabs(phoSCEta[i]) < 1.479) ? 0 : 1;

  // one-time MVA initialization
  if (!tmvaReader[iBE]) {
    tmvaReader[iBE] = new TMVA::Reader("!Color:Silent");

    tmvaReader[iBE]->AddVariable("SCRawE",          &phoSCRawE_);
    tmvaReader[iBE]->AddVariable("r9",              &phoR9_);
    tmvaReader[iBE]->AddVariable("sigmaIetaIeta",   &sieieFull5x5);
    tmvaReader[iBE]->AddVariable("etaWidth",        &phoSCEtaWidth_);
    tmvaReader[iBE]->AddVariable("phiWidth",        &phoSCPhiWidth_);
    tmvaReader[iBE]->AddVariable("covIEtaIPhi",     &sieipFull5x5);
    tmvaReader[iBE]->AddVariable("s4",              &s4Full5x5);
    tmvaReader[iBE]->AddVariable("phoIso03",        &phoPFPhoIso_);
    tmvaReader[iBE]->AddVariable("chgIsoWrtChosenVtx", &phoPFChIso_);
    tmvaReader[iBE]->AddVariable("chgIsoWrtWorstVtx",  &phoPFChIsoWorst_);
    tmvaReader[iBE]->AddVariable("scEta",              &phoSCEta_);
    tmvaReader[iBE]->AddVariable("rho",                &rho_);

    // add classification variables
    if (iBE == 1) {
      tmvaReader[iBE]->AddVariable("esEffSigmaRR", &phoESEffSigmaRR_);
    }

    std::cerr << ExternalFilesMgr::xmlFile_MVAweight(iBE, 2016) << std::endl;
    tmvaReader[iBE]->BookMVA("BDT", ExternalFilesMgr::xmlFile_MVAweight(iBE, 2016) );
  } // one-time initialization

  // set MVA variables
  phoR9_ = phoR9[i];
  phoSCEta_ = phoSCEta[i];
  phoSCRawE_ = phoSCRawE[i];
  phoSCEtaWidth_ = phoSCEtaWidth[i];
  phoSCPhiWidth_ = phoSCPhiWidth[i];
  rho_ = rho;
  phoPFPhoIso_ = phoPFPhoIso[i];
  phoPFChIso_ = phoPFChIso[i];
  phoESEffSigmaRR_= phoESEffSigmaRR[i];
  phoPFChIsoWorst_ = phoPFChWorstIso[i];
  sieieFull5x5 = phoSigmaIEtaIEtaFull5x5[i];
  sieipFull5x5 = phoSigmaIEtaIPhiFull5x5[i];
  s4Full5x5 = phoE2x2Full5x5[i]/phoE5x5Full5x5[i];

  return tmvaReader[iBE]->EvaluateMVA("BDT");

}
*/

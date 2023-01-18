#include "xPhoton/xPhoton/interface/PhotonSelections.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include <TMath.h>
#include <TMVA/Reader.h>
#include <TFile.h>
#include <TGraph.h>
#include <string>

// pre-selection of photon.
Int_t PhotonPreselection(TreeReader &data, Int_t ipho, Bool_t eleVeto) {

  // load relevant branches from TTree/TChain
  Float_t* phoEt               = data.GetPtrFloat("phoEt");
  Float_t* phoSCEta            = data.GetPtrFloat("phoSCEta");
  Int_t*   phoEleVeto          = data.GetPtrInt("phoEleVeto");
  Float_t* phoSigmaIEtaIEta    = data.GetPtrFloat("phoSigmaIEtaIEtaFull5x5");
  //Float_t* phoR9               = data.GetPtrFloat("phoR9");
  Float_t* phoHoverE           = data.GetPtrFloat("phoHoverE");
  Float_t* phoPFPhoIso         = data.GetPtrFloat("phoPFPhoIso");
  Float_t* phoPFChWorstIso   = data.GetPtrFloat("phoPFChWorstIso");

  
  if (!passSelection_PhotonKinematicParameters(phoEt[ipho],phoSCEta[ipho]) ) return 0;
  if (eleVeto && phoEleVeto[ipho] == 0) return 0;

  
  if (TMath::Abs(phoSCEta[ipho]) < 1.5) { //for EB
    if(phoPFChWorstIso[ipho] > 15.)     return 0;
    if(phoPFPhoIso[ipho] > 15.)         return 0;
    if(phoSigmaIEtaIEta[ipho] > 0.015)  return 0;
    if(phoHoverE[ipho] > 0.08)          return 0;
  }else{ //EE
    if(phoPFChWorstIso[ipho] > 15.)     return 0;
    if(phoPFPhoIso[ipho] > 15.)         return 0;
    if(phoSigmaIEtaIEta[ipho] > 0.045)  return 0;
    if(phoHoverE[ipho] > 0.05)          return 0;
    //if(phoR9[ipho] < 0.85) phoID=0; //disable this for Zg analysis
  }    
  return 1;
}





bool passSelection_PhotonKinematicParameters( float pt, float eta )
{
    if ( pt < 10. ) return false;
    //if ( fabs(eta) > 2.5 ) return false;
    if ( fabs(eta) > 3. ) return false;
    if ( fabs(eta) > 1.4442 && fabs(eta) < 1.566 ) return false;
    return true;
}

PhotonMVACalculator::PhotonMVACalculator( TreeReader* data_, std::string dataEra_ ) :
        _data(data_), _dataEra(dataEra_), _isValid(true)
{
    // 0 : EB, 1 : EE
    for ( int iBE = 0; iBE < 2; ++iBE )
    {
        tmvaReader[iBE] = new TMVA::Reader("!Color:Silent");


        if ( dataEra_ == "2016ReReco" )
        {
            // add classification variables
            tmvaReader[iBE]->AddVariable("recoPhi", &phoPhi);
            tmvaReader[iBE]->AddVariable("r9", &phoR9Full5x5);
            tmvaReader[iBE]->AddVariable( "sieieFull5x5",                 &sieieFull5x5 );     
            tmvaReader[iBE]->AddVariable( "sieipFull5x5",                 &sieipFull5x5 );     
            tmvaReader[iBE]->AddVariable( "s4 := e2x2Full5x5/e5x5Full5x5",    &s4Full5x5 );        
            tmvaReader[iBE]->AddVariable("recoSCEta", &phoSCEta);
            tmvaReader[iBE]->AddVariable("rawE", &phoSCRawE);
            tmvaReader[iBE]->AddVariable("scEtaWidth", &phoSCEtaWidth);
            tmvaReader[iBE]->AddVariable("scPhiWidth", &phoSCPhiWidth);
            if (iBE == 1) {
                tmvaReader[iBE]->AddVariable("ESEn := esEn/rawE", &phoESEnToRawE);
                tmvaReader[iBE]->AddVariable("esRR", &phoESEffSigmaRR);
            }
            tmvaReader[iBE]->AddVariable("rho", &rho);


        }
        else
        // if ( dataEra_ == "UL2018" )
        {
            tmvaReader[iBE]->AddVariable("r9Full5x5", &phoR9Full5x5);
            tmvaReader[iBE]->AddVariable( "sieieFull5x5", &sieieFull5x5 );
            tmvaReader[iBE]->AddVariable( "sieipFull5x5", &sieipFull5x5 );     
            tmvaReader[iBE]->AddVariable( "s4Full5x5", &s4Full5x5 );	       
            tmvaReader[iBE]->AddVariable("rawE", &phoSCRawE );
            tmvaReader[iBE]->AddVariable("scEtaWidth", &phoSCEtaWidth );
            tmvaReader[iBE]->AddVariable("scPhiWidth", &phoSCPhiWidth );
            if (iBE == 1)
            {
                tmvaReader[iBE]->AddVariable("esEnergyOverSCRawEnergy", &phoESEnToRawE );
                tmvaReader[iBE]->AddVariable("esRR", &phoESEffSigmaRR );
            }
            tmvaReader[iBE]->AddVariable("recoPhi", &phoPhi );
            tmvaReader[iBE]->AddVariable("recoSCEta", &phoSCEta );
            tmvaReader[iBE]->AddVariable("rho", &rho);
        }





        const char* inputfile = ExternalFilesMgr::xmlFile_MVAweight(iBE, _dataEra);
        if ( inputfile == nullptr )
        { std::cout << "PhotonMVAcalculator : no mva file input! Disable mva\n"; _isValid = false; return; }
        std::cout << "PhotonMVAcalculator : using " << inputfile << std::endl;
        tmvaReader[iBE]->BookMVA("BDT", inputfile );
    }
}
PhotonMVACalculator::~PhotonMVACalculator()
{
    _data = nullptr;
    delete tmvaReader[0]; tmvaReader[0] = nullptr;
    delete tmvaReader[1]; tmvaReader[1] = nullptr;
}

float PhotonMVACalculator::GetMVA_noIso( Int_t iPho_, ShowerShapeCorrectionAdapter* SScorr_ )
{
    if ( _isValid == false ) return MVA_INVALID;
    LoadingVars( iPho_);
    ShowerShapeCorrectionParameters_ggNtuple::loadVars(SScorr_, _data, iPho_);
    SScorr_->CalculateCorrections();
    phoR9Full5x5    = SScorr_->Corrected( ShowerShapeCorrectionAdapter::r9       );
    s4Full5x5       = SScorr_->Corrected( ShowerShapeCorrectionAdapter::s4       );
    sieieFull5x5    = SScorr_->Corrected( ShowerShapeCorrectionAdapter::sieie    );
    sieipFull5x5    = SScorr_->Corrected( ShowerShapeCorrectionAdapter::sieip    );
    phoSCEtaWidth	= SScorr_->Corrected( ShowerShapeCorrectionAdapter::etaWidth );
    phoSCPhiWidth	= SScorr_->Corrected( ShowerShapeCorrectionAdapter::phiWidth );
    phoESEnToRawE   = SScorr_->Corrected( ShowerShapeCorrectionAdapter::esEnergyOverSCRawEnergy);

    return tmvaReader[isEE]->EvaluateMVA("BDT");
}
float PhotonMVACalculator::GetMVA_noIso( Int_t iPho_, TGraph* tgr[8] )
{
    if ( _isValid == false ) return MVA_INVALID;
    LoadingVars( iPho_);
    ShowerShapeCorrection( tgr );

    return tmvaReader[isEE]->EvaluateMVA("BDT");
}
float PhotonMVACalculator::GetMVA_noIso( Int_t iPho_ )
{
    if ( _isValid == false ) return MVA_INVALID;
    LoadingVars( iPho_);
    return tmvaReader[isEE]->EvaluateMVA("BDT");
}
void PhotonMVACalculator::LoadingVars( Int_t iPho_ )
{
  // load necessary tree branches
  Float_t  DATAphoPhi                    = _data->GetPtrFloat("phoPhi")[iPho_];
  Float_t  DATAphoR9Full5x5              = _data->GetPtrFloat("phoR9Full5x5")[iPho_]; // Use this for new training
  Float_t  DATAphoSCEta                  = _data->GetPtrFloat("phoSCEta")[iPho_];
  Float_t  DATAphoSCRawE                 = _data->GetPtrFloat("phoSCRawE")[iPho_];
  Float_t  DATAphoSCEtaWidth             = _data->GetPtrFloat("phoSCEtaWidth")[iPho_];
  Float_t  DATAphoSCPhiWidth             = _data->GetPtrFloat("phoSCPhiWidth")[iPho_];
  Float_t  DATArho                       = _data->GetFloat("rho");
  Float_t  DATAphoESEnP1                 = _data->GetPtrFloat("phoESEnP1")[iPho_];
  Float_t  DATAphoESEnP2                 = _data->GetPtrFloat("phoESEnP2")[iPho_];
  Float_t  DATAphoESEffSigmaRR           = _data->GetPtrFloat("phoESEffSigmaRR")[iPho_];

  Float_t  DATAphoSigmaIEtaIEtaFull5x5   = _data->GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[iPho_];
  Float_t  DATAphoSigmaIEtaIPhiFull5x5   = _data->GetPtrFloat("phoSigmaIEtaIPhiFull5x5")[iPho_];
  Float_t  DATAphoE2x2Full5x5            = _data->GetPtrFloat("phoE2x2Full5x5")[iPho_];
  Float_t  DATAphoE5x5Full5x5            = _data->GetPtrFloat("phoE5x5Full5x5")[iPho_];



  // set MVA variables
  phoPhi                = DATAphoPhi;
  phoR9Full5x5          = DATAphoR9Full5x5;
  sieieFull5x5          = DATAphoSigmaIEtaIEtaFull5x5;
  sieipFull5x5          = DATAphoSigmaIEtaIPhiFull5x5;

  s4Full5x5             = DATAphoE2x2Full5x5/DATAphoE5x5Full5x5;

  phoSCEta              = DATAphoSCEta;
  phoSCRawE             = DATAphoSCRawE;
  phoSCEtaWidth         = DATAphoSCEtaWidth;
  phoSCPhiWidth         = DATAphoSCPhiWidth;

  phoESEnToRawE         = (DATAphoESEnP1+DATAphoESEnP2)/DATAphoSCRawE;
  phoESEffSigmaRR       = DATAphoESEffSigmaRR;

  rho                   = DATArho;
  
  
  isEE = fabs(DATAphoSCEta) > 1.5;
}
void PhotonMVACalculator::ShowerShapeCorrection( TGraph* tgr[8] )
{
    float origS4 = s4Full5x5;
    if ( tgr ) {
        if(!isEE ) {
            phoSCEtaWidth	= tgr[0]->Eval(phoSCEtaWidth);
            s4Full5x5       = tgr[1]->Eval(s4Full5x5);
            phoR9Full5x5    = tgr[2]->Eval(phoR9Full5x5);
            sieieFull5x5    = tgr[3]->Eval(sieieFull5x5);
        } else {
            phoSCEtaWidth 	= tgr[4]->Eval(phoSCEtaWidth);
            s4Full5x5       = tgr[5]->Eval(s4Full5x5);
            phoR9Full5x5    = tgr[6]->Eval(phoR9Full5x5);
            sieieFull5x5    = tgr[7]->Eval(sieieFull5x5);
        }      
    }
    printf( "INFO::new func origS4 = %.7f and newS4 = %.7f.  isEB? %s\n", origS4, s4Full5x5, isEE?"False":"True" );
    return;
}
void PhotonMVACalculator::ShowerShapeCorrection( ShowerShapeCorrectionAdapter* SScorr_ )
{
    return;
}

#include "xPhoton/xPhoton/interface/ShowerShapeCorrectionAdapter.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"

// note: the variable ordering follows ShowerShapeCorrector

ShowerShapeCorrectionAdapter::ShowerShapeCorrectionAdapter(std::string era, bool isMC) : campaign(""), corr(nullptr)
{
    // note: the campaign naming follows ShowerShapeCorrector
    if ( era == "2016ReReco" ) campaign = "2016";
    if ( era == "2017ReReco" ) campaign = "2017";
    if ( era == "2018ReReco" ) campaign = "2018";
    if ( era == "UL2016"     ) campaign = "2016Legacy";
    if ( era == "UL2017"     ) campaign = "2017Legacy";
    if ( era == "UL2018"     ) campaign = "2018Legacy";
    if ( campaign == "" ) throw "ShowerShapeCorrectionAdapter : input data era is not valid!\n";


    corr = new ShowerShapeCorrector(campaign, isMC);
};
ShowerShapeCorrectionAdapter::~ShowerShapeCorrectionAdapter()
{ delete corr; }

void ShowerShapeCorrectionAdapter::loadVars(TreeReader* data, int varidx)
{
    float varpt = data->GetPtrFloat("phoCalibEt")[varidx];
    float varSCeta = data->GetPtrFloat("phoSCEta")[varidx];
    float varphi = data->GetPtrFloat("phoPhi")[varidx];
    float varrho = data->GetFloat("rho");
    float varr9Full5x5 = data->GetPtrFloat("phoR9Full5x5")[varidx];
    float vare2x2Full5x5 = data->GetPtrFloat("phoE2x2Full5x5")[varidx];
    float vare5x5Full5x5 = data->GetPtrFloat("phoE5x5Full5x5")[varidx];
    float varsieieFull5x5 = data->GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[varidx];
    float varsieipFull5x5 = data->GetPtrFloat("phoSigmaIEtaIPhiFull5x5")[varidx];
    float varetaWidth = data->GetPtrFloat("phoSCEtaWidth")[varidx];
    float varphiWidth = data->GetPtrFloat("phoSCPhiWidth")[varidx];
    float varSCRawE = data->GetPtrFloat("phoSCRawE")[varidx];
    float varESEnP1 = data->GetPtrFloat("phoESEnP1")[varidx];
    float varESEnP2 = data->GetPtrFloat("phoESEnP2")[varidx];
    
    origvar[SSvars::pt                       ] = varpt;
    origvar[SSvars::etaSC                    ] = varSCeta;
    origvar[SSvars::phi                      ] = varphi;
    origvar[SSvars::rho                      ] = varrho;
    origvar[SSvars::r9                       ] = varr9Full5x5;
    origvar[SSvars::s4                       ] = vare2x2Full5x5 / vare5x5Full5x5;
    origvar[SSvars::sieie                    ] = varsieieFull5x5;
    origvar[SSvars::sieip                    ] = varsieipFull5x5;
    origvar[SSvars::etaWidth                 ] = varetaWidth;
    origvar[SSvars::phiWidth                 ] = varphiWidth;
    origvar[SSvars::esEnergyOverSCRawEnergy  ] =(varESEnP1+varESEnP2) / varSCRawE;
    return;
}

void ShowerShapeCorrectionAdapter::CalculateCorrections(TreeReader* data, int varidx)
{
    Cleaning();
    loadVars(data,varidx);
    correctedvars = corr->GetSSCorr();
}
void ShowerShapeCorrectionAdapter::Cleaning()
{
    correctedvars.clear();
    for ( int i=0; i< SSvars::totvar; ++i )
    {
        origvar[i] = -999.;
    }
}
void ShowerShapeCorrectionAdapter::ShowInfo()
{
    printf("Showing the stored content of this ShowerShapeCorrectionAdapter :\n");
    printf(" -> origvar[SSvars::pt                       ] = %.3f\n",origvar[SSvars::pt                       ]);
    printf(" -> origvar[SSvars::etaSC                    ] = %.3f\n",origvar[SSvars::etaSC                    ]);
    printf(" -> origvar[SSvars::phi                      ] = %.3f\n",origvar[SSvars::phi                      ]);
    printf(" -> origvar[SSvars::rho                      ] = %.3f\n",origvar[SSvars::rho                      ]);
    printf(" -> origvar[SSvars::r9                       ] = %.3f\n",origvar[SSvars::r9                       ]);
    printf(" -> origvar[SSvars::s4                       ] = %.3f\n",origvar[SSvars::s4                       ]);
    printf(" -> origvar[SSvars::sieie                    ] = %.3f\n",origvar[SSvars::sieie                    ]);
    printf(" -> origvar[SSvars::sieip                    ] = %.3f\n",origvar[SSvars::sieip                    ]);
    printf(" -> origvar[SSvars::etaWidth                 ] = %.3f\n",origvar[SSvars::etaWidth                 ]);
    printf(" -> origvar[SSvars::phiWidth                 ] = %.3f\n",origvar[SSvars::phiWidth                 ]);
    printf(" -> origvar[SSvars::esEnergyOverSCRawEnergy  ] = %.3f\n",origvar[SSvars::esEnergyOverSCRawEnergy  ]);
    printf("\n\n");

    if ( correctedvars.size() == 0 ) { printf(" -> nothing in correctedvars\n"); return; }
    printf(" -> correctedvars[SSvars::pt                       ] = %.3f\n",correctedvars[SSvars::pt                       ]);
    printf(" -> correctedvars[SSvars::etaSC                    ] = %.3f\n",correctedvars[SSvars::etaSC                    ]);
    printf(" -> correctedvars[SSvars::phi                      ] = %.3f\n",correctedvars[SSvars::phi                      ]);
    printf(" -> correctedvars[SSvars::rho                      ] = %.3f\n",correctedvars[SSvars::rho                      ]);
    printf(" -> correctedvars[SSvars::r9                       ] = %.3f\n",correctedvars[SSvars::r9                       ]);
    printf(" -> correctedvars[SSvars::s4                       ] = %.3f\n",correctedvars[SSvars::s4                       ]);
    printf(" -> correctedvars[SSvars::sieie                    ] = %.3f\n",correctedvars[SSvars::sieie                    ]);
    printf(" -> correctedvars[SSvars::sieip                    ] = %.3f\n",correctedvars[SSvars::sieip                    ]);
    printf(" -> correctedvars[SSvars::etaWidth                 ] = %.3f\n",correctedvars[SSvars::etaWidth                 ]);
    printf(" -> correctedvars[SSvars::phiWidth                 ] = %.3f\n",correctedvars[SSvars::phiWidth                 ]);
    printf(" -> correctedvars[SSvars::esEnergyOverSCRawEnergy  ] = %.3f\n",correctedvars[SSvars::esEnergyOverSCRawEnergy  ]);
}


float ShowerShapeCorrectionAdapter::ptCalb() { return correctedvars[SSvars::pt]; }


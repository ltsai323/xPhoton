#include "xPhoton/xPhoton/interface/ShowerShapeCorrectionAdapter.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"

// note: the variable ordering follows ShowerShapeCorrector

bool same(float a, float b) { return fabs(a-b) < 1e-8; }
ShowerShapeCorrectionAdapter::ShowerShapeCorrectionAdapter(std::string era, bool isMC) : campaign(""), corr(nullptr),
    tmppt(-999.),tmpeta(-999.),tmpphi(-999.)
{
    // note: the campaign naming follows ShowerShapeCorrector
    if ( era == "2016ReReco" ) campaign = "2016";
    if ( era == "2017ReReco" ) campaign = "2017";
    if ( era == "2018ReReco" ) campaign = "2018";
    if ( era == "UL2016"     ) campaign = "2016_Legacy";
    if ( era == "UL2017"     ) campaign = "2017_Legacy";
    if ( era == "UL2018"     ) campaign = "2018_Legacy";
    if ( campaign == "" ) throw "ShowerShapeCorrectionAdapter : input data era is not valid!\n";


    corr = new ShowerShapeCorrector(campaign, isMC);
};
ShowerShapeCorrectionAdapter::~ShowerShapeCorrectionAdapter()
{ delete corr; }


void ShowerShapeCorrectionAdapter::CalculateCorrections() //asdf TreeReader* data, int varidx)
{
    //LOG_DEBUG("loading variables");
    //loadVars(data,varidx);
    LOG_DEBUG("input variables to corrector");
    corr->InputFeatures(
        origvar["pt"                      ],
        origvar["etaSC"                   ],
        origvar["phi"                     ],
        origvar["rho"                     ],
        origvar["r9"                      ],
        origvar["s4"                      ],
        origvar["sieie"                   ],
        origvar["sieip"                   ],
        origvar["etaWidth"                ],
        origvar["phiWidth"                ],
        origvar["esEnergyOverSCRawEnergy" ]
    );
    LOG_DEBUG("GetSSCorr functioning");
    correctedvars = corr->GetSSCorr();
    LOG_DEBUG("GetSSCorr functioned");
}
void ShowerShapeCorrectionAdapter::SetParameters(
float varpt           ,
float varSCeta        ,
float varphi          ,
float varrho          ,
float varr9Full5x5    ,
float vars4Full5x5    ,
float varsieieFull5x5 ,
float varsieipFull5x5 ,
float varetaWidth     ,
float varphiWidth     ,
float varesenergyoverscrawenergy )
{
    Cleaning();
    origvar["pt"                      ] = varpt;
    origvar["etaSC"                   ] = varSCeta;
    origvar["phi"                     ] = varphi;
    origvar["rho"                     ] = varrho;
    origvar["r9"                      ] = varr9Full5x5;
    origvar["s4"                      ] = vars4Full5x5;
    origvar["sieie"                   ] = varsieieFull5x5;
    origvar["sieip"                   ] = varsieipFull5x5;
    origvar["etaWidth"                ] = varetaWidth;
    origvar["phiWidth"                ] = varphiWidth;
    origvar["esEnergyOverSCRawEnergy" ] = varesenergyoverscrawenergy;
}

void ShowerShapeCorrectionAdapter::Cleaning()
{
    correctedvars.clear();
    for ( auto iter = origvar.begin(); iter != origvar.end(); ++iter )
        iter->second = -999.;
}
void ShowerShapeCorrectionAdapter::ShowInfo()
{
    printf("Showing the stored content of this ShowerShapeCorrectionAdapter :\n");
    printf(" -> origvar[pt                       ] = %.3f\n",origvar["pt"                      ]);
    printf(" -> origvar[etaSC                    ] = %.3f\n",origvar["etaSC"                   ]);
    printf(" -> origvar[phi                      ] = %.3f\n",origvar["phi"                     ]);
    printf(" -> origvar[rho                      ] = %.3f\n",origvar["rho"                     ]);
    printf(" -> origvar[r9                       ] = %.3f\n",origvar["r9"                      ]);
    printf(" -> origvar[s4                       ] = %.3f\n",origvar["s4"                      ]);
    printf(" -> origvar[sieie                    ] = %.3f\n",origvar["sieie"                   ]);
    printf(" -> origvar[sieip                    ] = %.3f\n",origvar["sieip"                   ]);
    printf(" -> origvar[etaWidth                 ] = %.3f\n",origvar["etaWidth"                ]);
    printf(" -> origvar[phiWidth                 ] = %.3f\n",origvar["phiWidth"                ]);
    printf(" -> origvar[esEnergyOverSCRawEnergy  ] = %.3f\n",origvar["esEnergyOverSCRawEnergy" ]);
    printf("\n\n");

    if ( correctedvars.size() == 0 ) { printf(" -> nothing in correctedvars\n"); return; }
    printf(" -> correctedvars[SSvars::r9                     ] = %.3f\n",correctedvars[SSvars::r9                     ]);
    printf(" -> correctedvars[SSvars::s4                     ] = %.3f\n",correctedvars[SSvars::s4                     ]);
    printf(" -> correctedvars[SSvars::sieie                  ] = %.3f\n",correctedvars[SSvars::sieie                  ]);
    printf(" -> correctedvars[SSvars::sieip                  ] = %.3f\n",correctedvars[SSvars::sieip                  ]);
    printf(" -> correctedvars[SSvars::etaWidth               ] = %.3f\n",correctedvars[SSvars::etaWidth               ]);
    printf(" -> correctedvars[SSvars::phiWidth               ] = %.3f\n",correctedvars[SSvars::phiWidth               ]);
    printf(" -> correctedvars[SSvars::esEnergyOverSCRawEnergy] = %.3f\n",correctedvars[SSvars::esEnergyOverSCRawEnergy]);
}


float ShowerShapeCorrectionAdapter::Corrected( ShowerShapeCorrectionAdapter::SSvars idx ) { return correctedvars[idx]; }
bool ShowerShapeCorrectionAdapter::sameEvt( float pt_, float eta_, float phi_ )
{
    if ( 
        same(tmppt ,pt_ ) &&
        same(tmpeta,eta_) &&
        same(tmpphi,phi_)
       ) return true;
    tmppt=pt_;
    tmpeta=eta_;
    tmpphi=phi_;
    return false;
}

bool ShowerShapeCorrectionParameters_ggNtuple::isSameEvent( ShowerShapeCorrectionAdapter* ssAdapter, TreeReader* data, int varidx )
{
    float loadpt  = data->GetPtrFloat("phoCalibEt")  [varidx];
    float loadeta = data->GetPtrFloat("phoEta")      [varidx];
    float loadphi = data->GetPtrFloat("phoPhi")      [varidx];
    return ssAdapter->sameEvt( loadpt, loadeta, loadphi );
}
void ShowerShapeCorrectionParameters_ggNtuple::loadVars(ShowerShapeCorrectionAdapter* ssAdapter, TreeReader* data, int varidx)
{
    if ( ShowerShapeCorrectionParameters_ggNtuple::isSameEvent(ssAdapter,data,varidx) ) return;

    float varpt             = data->GetPtrFloat("phoCalibEt")[varidx];
    float varSCeta          = data->GetPtrFloat("phoSCEta")[varidx];
    float varphi            = data->GetPtrFloat("phoPhi")[varidx];
    float varrho            = data->GetFloat("rho");
    float varr9Full5x5      = data->GetPtrFloat("phoR9Full5x5")[varidx];
    float vare2x2Full5x5    = data->GetPtrFloat("phoE2x2Full5x5")[varidx];
    float vare5x5Full5x5    = data->GetPtrFloat("phoE5x5Full5x5")[varidx];
    float varsieieFull5x5   = data->GetPtrFloat("phoSigmaIEtaIEtaFull5x5")[varidx];
    float varsieipFull5x5   = data->GetPtrFloat("phoSigmaIEtaIPhiFull5x5")[varidx];
    float varetaWidth       = data->GetPtrFloat("phoSCEtaWidth")[varidx];
    float varphiWidth       = data->GetPtrFloat("phoSCPhiWidth")[varidx];
    float varSCRawE         = data->GetPtrFloat("phoSCRawE")[varidx];
    float varESEnP1         = data->GetPtrFloat("phoESEnP1")[varidx];
    float varESEnP2         = data->GetPtrFloat("phoESEnP2")[varidx];
    
    ssAdapter->SetParameters(
            varpt,
            varSCeta,
            varphi,
            varrho,
            varr9Full5x5,
            vare2x2Full5x5 / vare5x5Full5x5,
            varsieieFull5x5,
            varsieipFull5x5,
            varetaWidth,
            varphiWidth,
           (varESEnP1+varESEnP2) / varSCRawE
        );
    return;
}
void ShowerShapeCorrectionParameters_xPhoton::loadVars(ShowerShapeCorrectionAdapter* ssAdapter, TreeReader* data)
{
    ssAdapter->SetParameters(
            data->GetFloat("recoPtCalib"),
            data->GetFloat("recoSCEta"),
            data->GetFloat("recoPhi"),
            data->GetFloat("rho"),
            data->GetFloat("r9Full5x5"),
            data->GetFloat("s4Full5x5"),
            data->GetFloat("sieieFull5x5"),
            data->GetFloat("sieipFull5x5"),
            data->GetFloat("scEtaWidth"),
            data->GetFloat("scPhiWidth"),
            data->GetFloat("esEnergyOverSCRawEnergy")
            );
    return;
}
bool ShowerShapeCorrectionParameters_xPhoton::isSameEvent( ShowerShapeCorrectionAdapter* ssAdapter, TreeReader* data )
{
    float loadpt  = data->GetFloat("recoPt");
    float loadeta = data->GetFloat("recoEta");
    float loadphi = data->GetFloat("recoPhi");
    return ssAdapter->sameEvt( loadpt, loadeta, loadphi );
}

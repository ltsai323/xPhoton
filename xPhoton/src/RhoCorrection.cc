#include <cmath>
#include "xPhoton/xPhoton/interface/RhoCorrection.h"
float CorrectedRho( float iso, float rho, float effectivearea )
{
    float cIso = iso - rho * effectivearea;
    return cIso > 0. ? cIso : 0.;
}
float EffectiveArea_ChIso(float eta, std::string era)
{
    if ( era == "2016ReReco" ) return EffectiveArea_ChIso_Spring2016(eta);
    if ( era == "UL2016PreVFP"  ) return EffectiveArea_ChIso_Spring2016(eta);
    if ( era == "UL2016PostVFP" ) return EffectiveArea_ChIso_Spring2016(eta);
    if ( era == "UL2017"     ) return EffectiveArea_ChIso_2017v2(eta);
    if ( era == "UL2018"     ) return EffectiveArea_ChIso_2017v2(eta);
    throw "error, input era is not defined";
    return -1;
}
float EffectiveArea_ChIso_2017v2(float eta)
{
    float abseta = fabs(eta);
    if      ( abseta < 1.0   ) return 0.0112;
    else if ( abseta < 1.479 ) return 0.0108;
    else if ( abseta < 2.0   ) return 0.0106;
    else if ( abseta < 2.2   ) return 0.01002;
    else if ( abseta < 2.3   ) return 0.0098;
    else if ( abseta < 2.4   ) return 0.0089;
    else                       return 0.0087;
    return 0;
}
float EffectiveArea_ChIso_Spring2016(float eta)
{
    float abseta = fabs(eta);
    if      ( abseta < 1.0   ) return 0.0360;
    else if ( abseta < 1.479 ) return 0.0377;
    else if ( abseta < 2.0   ) return 0.0306;
    else if ( abseta < 2.2   ) return 0.0283;
    else if ( abseta < 2.3   ) return 0.0254;
    else if ( abseta < 2.4   ) return 0.0217;
    else                       return 0.0167;
    return 0;
}

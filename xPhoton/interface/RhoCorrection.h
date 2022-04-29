#ifndef __RhoCorrection_H__
#define __RhoCorrection_H__
#include <string>

float CorrectedRho( float iso, float rho, float effectivearea );
float EffectiveArea_ChIso(float eta, std::string era);

// definitions is https://twiki.cern.ch/twiki/bin/view/CMS/CutBasedPhotonIdentificationRun2?fbclid=IwAR3OASIORLME28ucF2plP-dEoUzH-Oug6MGzobA1jjdGKydfXYXmZFs-c4o
float EffectiveArea_ChIso_2017v2(float eta);
float EffectiveArea_ChIso_Spring2016(float eta);

#endif

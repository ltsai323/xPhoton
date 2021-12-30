#ifndef __ShowerShapeCorrectionAdapter_H__
#define __ShowerShapeCorrectionAdapter_H__
#include <string>
#include <vector>
#include <map>
#include "ShowerShapeCorrection/CQR_framework/interface/ShowerShapeCorrector.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"


class ShowerShapeCorrectionAdapter
{
public:
    ShowerShapeCorrectionAdapter(std::string era, bool isMC);
    ~ShowerShapeCorrectionAdapter();

    // note: the variable ordering follows ShowerShapeCorrector
    enum SSvars
    {
        r9,
        s4,
        sieie,
        sieip,
        etaWidth,
        phiWidth,
        esEnergyOverSCRawEnergy
    };


    void CalculateCorrections(TreeReader* data, int varidx);
    void Cleaning();

    void ShowInfo();
    float Corrected( SSvars idx );
private:
    std::string campaign;

    ShowerShapeCorrector* corr;
    std::vector<float> correctedvars;
    void loadVars(TreeReader* data, int varidx);
    //float origvar[SSvars::totvar];
    std::map<const char*, float> origvar;
};



#endif

#ifndef __ShowerShapeCorrectionAdapter_H__
#define __ShowerShapeCorrectionAdapter_H__
#include <string>
#include <vector>
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
        pt,                       
        etaSC,                    
        phi,                      
        rho,                      
        r9,                       
        s4,                       
        sieie,                    
        sieip,                    
        etaWidth,                 
        phiWidth,                 
        esEnergyOverSCRawEnergy,
        totvar
    };


    void CalculateCorrections(TreeReader* data, int varidx);
    void Cleaning();

    void ShowInfo();
    float ptCalb();
private:
    std::string campaign;

    ShowerShapeCorrector* corr;
    std::vector<float> correctedvars;
    void loadVars(TreeReader* data, int varidx);
    float origvar[SSvars::totvar];
};



#endif

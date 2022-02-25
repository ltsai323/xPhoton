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
    void CalculateCorrections( // temp function
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
            float varesenergyoverscrawenergy );
    void Cleaning();

    void ShowInfo();
    float Corrected( SSvars idx );
private:
    std::string campaign;

    ShowerShapeCorrector* corr;
    std::vector<float> correctedvars;
    bool isSameEvent(TreeReader* data, int varidx);
    void loadVars(TreeReader* data, int varidx);
    //float origvar[SSvars::totvar];
    std::map<const char*, float> origvar;

    int tmpidx;
    float tmppt, tmpeta, tmpphi;
};



#endif

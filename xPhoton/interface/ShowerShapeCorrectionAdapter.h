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


    void CalculateCorrections();
    void SetParameters(
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
    bool sameEvt( float pt_, float eta_, float phi_);

private:
    std::string campaign;

    ShowerShapeCorrector* corr;
    std::vector<float> correctedvars;
    std::map<const char*, float> origvar;

    float tmppt, tmpeta, tmpphi;
};

namespace ShowerShapeCorrectionParameters_ggNtuple
{
    bool isSameEvent(ShowerShapeCorrectionAdapter* sscAdapter, TreeReader* data, int varidx);
    void loadVars   (ShowerShapeCorrectionAdapter* sscAdapter, TreeReader* data, int varidx);
};
namespace ShowerShapeCorrectionParameters_xPhoton
{
    bool isSameEvent(ShowerShapeCorrectionAdapter* sscAdapter, TreeReader* data);
    void loadVars   (ShowerShapeCorrectionAdapter* sscAdapter, TreeReader* data);
};


#endif

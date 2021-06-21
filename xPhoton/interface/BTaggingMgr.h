#ifndef __BTaggingMgr_h__
#define __BTaggingMgr_h__
#include <map>
#include <string>
#include <vector>
#include "xPhoton/xPhoton/interface/BTagCalibrationStandalone.h"


#define MAXSYSTS 100


class BTaggingMgr
{
    public:
        BTaggingMgr();
        void UseAlgorithm(std::string algorithmName);
        void RegisterSystTypes();


    enum quarkFlavors
    { flav_b = 0, flav_c, flav_l, totFlavs };
    
    std::vector< std::vector<std::string> > systematicTypes;
    std::vector< std::string > flavourNames;
    int calibReaderIdx( int ifile, int iflav ) const { return totFlavs * ifile + iflav; }
    int calibReaderIdx2( int ifile, int iflav ) const { return totFlavs * ifile + iflav; }

    private:
    std::vector<std::string> _usedAlgorithmNames;
    std::map<std::string, std::vector<const char*>> _usedSystTypes;
    bool _systTypeRegisted;
    std::vector<BTagCalibration> calibs;

};
#endif


#ifndef __BTaggingMgr_h__
#define __BTaggingMgr_h__
#include <map>
#include <string>
#include <vector>
#include "xPhoton/xPhoton/interface/BTagCalibrationStandalone.h"
#include <memory>
#include <map>
#include <TTree.h>


#define MAXNSYST 100
#define HADRONFLAV_B 5
#define HADRONFLAV_C 4
#define HADRONFLAV_L 0




class BTaggingMgr
{
public:
    BTaggingMgr();
    void UseAlgorithm(std::string algorithmName);
    void RegisterSystTypes();
    void InitVars();
    void RegBranch(TTree* t);
    void FillWeightToEvt(float pt_, float eta_, int hadFlav_, float bDis_ );


    
    std::vector< std::vector<std::string> > systematicTypes;
    int systVarIdx( int iAlgo, int iSyst ) const { return MAXNSYST * iAlgo + iSyst; } // no flav needed

private:
    std::vector<std::string> _usedAlgorithmNames;
    std::map<std::string, std::vector<std::string>> _usedSystTypes;
    bool _systTypeRegisted;
    std::vector< std::shared_ptr<BTagCalibration> > calibPTRs;
    std::vector< std::shared_ptr<BTagCalibrationReader> > calibReaderPTRs;
    std::map<int, Float_t> systVars;
};
#endif


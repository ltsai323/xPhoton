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
using funcptr__ = void(*)(int,int);


class BTaggingMgr
{
public:
    BTaggingMgr();
    void UseAlgorithm(std::string algorithmName);
    void RegisterSystTypes();
    void InitVars();
    void RegBranch(TTree* t);
    void FillWeightToEvt(float eta, float phi);
    /*
    void LoopVar(funcptr__ func);
    */


    
    std::vector< std::vector<std::string> > systematicTypes;
    //std::vector< std::string > flavourNames;
    int systVarIdx( int iFlav, int iAlgo, int iSyst ) const { return _usedAlgorithmNames.size() * MAXNSYST * iFlav + MAXNSYST * iAlgo + iSyst; }

private:
    std::vector<std::string> _usedAlgorithmNames;
    std::map<std::string, std::vector<std::string>> _usedSystTypes;
    bool _systTypeRegisted;
    std::vector< std::shared_ptr<BTagCalibration> > calibPTRs;
    std::vector< std::shared_ptr<BTagCalibrationReader> > calibReaderPTRs;
    std::map<int, float> systVars;

    /*
    void initvar(int i, int j);
    */

    /*
    static int   GetIAlgo( int varIdx ) const { return varIdx / MAXNSYST; }
    static int   GetISyst( int varIdx ) const { return varIdx % MAXNSYST; }
    */
};
#endif


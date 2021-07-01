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
//using funcptr__ = void(*)(int,int);
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
    void FillWeightToEvt(float pt_, float eta_, int hadFlav_ );
    /*
    void LoopVar(funcptr__ func);
    */


    
    std::vector< std::vector<std::string> > systematicTypes;
    //std::vector< std::string > flavourNames;
    //int systVarIdx( int iFlav, int iAlgo, int iSyst ) const { return _usedAlgorithmNames.size() * MAXNSYST * iFlav + MAXNSYST * iAlgo + iSyst; }
    int systVarIdx( int iAlgo, int iSyst ) const { return MAXNSYST * iAlgo + iSyst; } // no flav needed

private:
    std::vector<std::string> _usedAlgorithmNames;
    std::map<std::string, std::vector<std::string>> _usedSystTypes;
    bool _systTypeRegisted;
    std::vector< std::shared_ptr<BTagCalibration> > calibPTRs;
    std::vector< std::shared_ptr<BTagCalibrationReader> > calibReaderPTRs;
    std::map<int, Float_t> systVars;

    /*
    void initvar(int i, int j);
    */

    /*
    static int   GetIAlgo( int varIdx ) const { return varIdx / MAXNSYST; }
    static int   GetISyst( int varIdx ) const { return varIdx % MAXNSYST; }
    */
};
#endif


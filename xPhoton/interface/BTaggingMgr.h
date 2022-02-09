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
    BTaggingMgr(const char* dataera, const char* algoname, std::vector<std::string> name );
    void InitVars();
    void RegBranch(TTree* t);
    void FillWeightToEvt(float pt_, float eta_, int hadFlav_, float bDis_ );

private:
    const char* algorithm;
    const char* _dataEra;
    std::vector<std::string> _usedSystTypeNames;
    std::vector<Float_t> _systVars;
    BTagCalibration       _calib;
    BTagCalibrationReader _calibReader;

};

// input era check is done in bin/AppendBTagCalibration and src/ExternalFile
class BTaggingMgr_CSVv2       : public BTaggingMgr
{ public: BTaggingMgr_CSVv2       ( const char* dataEra ); };
class BTaggingMgr_DeepCSV     : public BTaggingMgr
{ public: BTaggingMgr_DeepCSV     ( const char* dataEra ); };
class BTaggingMgr_DeepFlavour : public BTaggingMgr
{ public: BTaggingMgr_DeepFlavour ( const char* dataEra ); };
#endif

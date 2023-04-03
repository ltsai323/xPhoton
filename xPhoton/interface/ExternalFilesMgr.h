#ifndef __ExternalFilesMgr_h__
#define __ExternalFilesMgr_h__
#include <string>

namespace ExternalFilesMgr
{
    // era = "2016ReReco", "2017ReReco", "2018ReReco", "UL2016", "UL2017", "UL2018"

    const char* xmlFile_MVAweight(int isEndcap, std::string era);
    const char* RooFile_PileUp(std::string era);
    const char* csvFile_BTagCalibs(std::string name, std::string era);
    const char* csvFile_BTagCalib_DeepFlavour(std::string era);
    const char* csvFile_BTagCalib_DeepCSV(std::string era);
    const char* RooFile_CTagCalibs(std::string name, std::string era);
    const char* RooFile_CTagCalib_DeepFlavour(std::string era);
    const char* RooFile_CTagCalib_DeepCSV(std::string era);
    //const char* RooFile_ShowerShapeCorrection(std::string era);
};
/*
class ExternalFilesMgr_
{
    ExternalFilesMgr_(const char* era)
    {
        switch ( era )
};
*/

#endif

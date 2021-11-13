#ifndef __ExternalFilesMgr_h__
#define __ExternalFilesMgr_h__
#include <string>

namespace ExternalFilesMgr
{
    const char* xmlFile_MVAweight(int isEndcap, int year);
    const char* RooFile_PileUp();
    const char* RooFile_PileUp(int year);
    const char* RooFile_PileUp_Run2016_69200nb_Moriond17();
    const char* RooFile_ShowerShapeCorrection();
    const char* csvFile_BTagCalib_CSVv2();
    const char* csvFile_BTagCalib_DeepCSV();
    const char* csvFile_BTagCalib_DeepFlavour();
    const char* csvFile_BTagCalib_DeepFlavour_JESreduced();
    const char* csvFile_BTagCalibs(std::string name);
    std::string csvFile_testing();

    // era = "2016ReReco", "2017ReReco", "2018ReReco", "UL2016", "UL2017", "UL2018"

    const char* xmlFile_MVAweight(int isEndcap, std::string era);
    const char* RooFile_PileUp(std::string era);
    const char* csvFile_BTagCalib_DeepFlavour(std::string era);
    const char* csvFile_BTagCalib_DeepCSV(std::string era);
    const char* RooFile_ShowerShapeCorrection(std::string era);
};

#endif

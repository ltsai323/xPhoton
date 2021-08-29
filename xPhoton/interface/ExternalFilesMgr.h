#ifndef __ExternalFilesMgr_h__
#define __ExternalFilesMgr_h__
#include <string>

namespace ExternalFilesMgr
{
    const char* xmlFile_MVAweight(int isEndcap, int year);
    const char* RooFile_PileUp();
    const char* RooFile_PileUp_Run2016_69200nb_Moriond17();
    const char* RooFile_ShowerShapeCorrection();
    const char* testchar();
    const char* csvFile_BTagCalib_CSVv2();
    const char* csvFile_BTagCalib_DeepCSV();
    const char* csvFile_BTagCalib_DeepFlavour();
    const char* csvFile_BTagCalib_DeepFlavour_JESreduced();
    const char* csvFile_BTagCalibs(std::string name);
    std::string csvFile_testing();
};

#endif

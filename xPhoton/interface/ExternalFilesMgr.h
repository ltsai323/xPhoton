#ifndef __ExternalFilesMgr_h__
#define __ExternalFilesMgr_h__
#include <string>

namespace ExternalFilesMgr
{
    const char* xmlFile_MVAweight(int isEndcap, int year);
    const char* RooFile_PileUp();
    const char* RooFile_ShowerShapeCorrection();
    const char* testchar();
};

#endif

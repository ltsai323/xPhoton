#ifndef __JetIDMgr_h__
#define __JetIDMgr_h__
#include "xPhoton/xPhoton/interface/readMgr.h"
#include <map>
#include <string>
#include <vector>


namespace JetIDMgr{

static const float NO_SELECTION(-999.);
    void etaisoutofrange();
    // -1 : skip this.
    // The bigger and smaller relation needs to check twiki.
    typedef std::map<std::string,std::pair<float,float>> (*JetIDCutsFPtr) (float);
    bool IDPassed( TreeReader* dataptr, int iJet, JetIDCutsFPtr cut_definition );
    bool FailedSelection( const std::pair<float,float>& selrange, float val );

    std::map<std::string,std::pair<float,float>> JetIDCuts_ULRun2016_CHS( float jetEta );
    std::map<std::string,std::pair<float,float>> JetIDCuts_ULRun2016_PUPPI( float jetEta );
};

#endif

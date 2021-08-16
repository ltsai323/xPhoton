#ifndef __JetIDMgr_h__
#define __JetIDMgr_h__
#include "xPhoton/xPhoton/interface/readMgr.h"
#include <map>
#include <string>
#include <vector>


namespace JetIDMgr{

    static const float NO_SELECTION(-999.);
    static const float FAILED_PUID( 999.);
    static const float PASSED_PUID(-999.);
    void etaisoutofrange();
    // -1 : skip this.
    // The bigger and smaller relation needs to check twiki.
    typedef std::map<std::string,std::pair<float,float>> (*JetIDCutsFPtr) (float);
    typedef float (*PUJetIDCutsFPtr) (float);
    bool IDPassed( TreeReader* dataptr, int iJet, JetIDCutsFPtr cut_definition );
    // if pass PUID : is signal jet. fail PUID : is PU
    bool PUIDPassed( TreeReader* dataptr, int iJet, PUJetIDCutsFPtr cut_definition );
    bool FailedSelection( const std::pair<float,float>& selrange, float val );

    std::map<std::string,std::pair<float,float>> JetIDCuts_ULRun2016_CHS( float jetEta );
    std::map<std::string,std::pair<float,float>> JetIDCuts_ULRun2016_PUPPI( float jetEta );

    float PUJetIDCuts_ULRun2016_CHS_Tight ( float jetPt, float jetEta );
    float PUJetIDCuts_ULRun2016_CHS_Medium( float jetPt, float jetEta );
    float PUJetIDCuts_ULRun2016_CHS_Loose ( float jetPt, float jetEta );
    float PUJetIDCuts_ULRun2017_CHS_Tight ( float jetPt, float jetEta );
    float PUJetIDCuts_ULRun2017_CHS_Medium( float jetPt, float jetEta );
    float PUJetIDCuts_ULRun2017_CHS_Loose ( float jetPt, float jetEta );
    float PUJetIDCuts_ULRun2018_CHS_Tight ( float jetPt, float jetEta );
    float PUJetIDCuts_ULRun2018_CHS_Medium( float jetPt, float jetEta );
    float PUJetIDCuts_ULRun2018_CHS_Loose ( float jetPt, float jetEta );
};

#endif

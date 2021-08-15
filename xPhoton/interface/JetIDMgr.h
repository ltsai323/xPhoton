#ifndef __JetIDMgr_h__
#define __JetIDMgr_h__
#include "xPhoton/xPhoton/interface/readMgr.h"
#include <map>
#include <string>
#include <vector>

#define NO_SELECTION -999.
void EtaIsOutOfRange();
// -1 : skip this.
// The bigger and smaller relation needs to check twiki.
typedef std::map<std::string,std::pair<float,float>> (*JetIDCutsFPtr) (float);

std::map<std::string,std::pair<float,float>> JetIDCuts_ULRun2016_CHS( float jetEta );
std::map<std::string,std::pair<float,float>> JetIDCuts_ULRun2016_PUPPI( float jetEta );
bool JetID( TreeReader* dataptr, int iJet );
bool SelectionFailed( const std::pair<float,float>& selrange, float val );

#endif

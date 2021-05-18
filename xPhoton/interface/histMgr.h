#ifndef __HISTMGR_H__
#define __HISTMGR_H__

#include <string>
#include <vector>
#include <map>
#include "TH1F.h"
#include "TH2F.h"
#include "TDirectory.h"
// #include "/home/ltsai/Work/github/xPhoton/interface/LogMgr.h"


class histMgr
{
    std::map< std::string, TH1F* > hMap;
    std::map< std::string, TH2F* > hMap2D;

public:
    // create TH1F & TH2F
    void Create( const std::string& name, int nbin, double min, double max );
    void Create( const std::string& name, int nbin, double min, double max , int nbin2, double min2, double max2);
    // search name and fill TH1F & TH2F
    void FillStatus( const std::string& name, double value );
    void Fill( const std::string& name, double value );
    void Fill( const std::string& name, double valueX, double valueY );

    void WriteTo(TDirectory* dir=nullptr);
    void DeleteAll();
};
#endif

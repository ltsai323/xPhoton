#ifndef __histMgr_h__
#define __histMgr_h__

#include <string>
#include <vector>
#include <map>
#include "TH1F.h"
#include "TH2F.h"
#include "TDirectory.h"
#include "/home/ltsai/Work/github/xPhoton/interface/logger.h"


namespace histMgr{
    std::map< std::string, TH1F* > hMap;
    std::map< std::string, TH2F* > hMap2D;
    TDirectory* _dir = nullptr;

    // create TH1F & TH2F
    void Create( const std::string& name, int nbin, double min, double max )
    {
        if ( hMap.find( name ) != hMap.end() )
        { LOG_WARNING( "%s histogram1D duplicated! Please check the createHisto function", name.c_str() ); return; }
        LOG_INFO( "In directory %s constructs histogram1D creating : %s", _dir?_dir->GetName():"current directory", name.c_str() );
        if ( _dir ) _dir->cd();
        // hMap[name] = new TH1F( name.c_str(), name.c_str(), nbin, min, max );
        hMap[name] = new TH1F( name.c_str(), "", nbin, min, max );
        hMap[name]->GetXaxis()->SetTitle(name.c_str());

        //LOG_INFO( "histogram1D append : %s", name.c_str() );
    }
    void Create( const std::string& name, int nbin, double min, double max , int nbin2, double min2, double max2)
    {
        if ( hMap2D.find( name ) != hMap2D.end() )
        { LOG_WARNING( "%s histogram2D duplicated! Please check the createHisto function", name.c_str() ); return; }
        LOG_INFO( "In directory %s constructs histogram2D creating : %s", _dir?_dir->GetName():"current directory", name.c_str() );
        if ( _dir ) _dir->cd();
        hMap2D[name] = new TH2F( name.c_str(), name.c_str(), nbin, min, max, nbin2, min2, max2 );
        //LOG_INFO( "histogram2D append : %s", name.c_str() );
    }
    // search name and fill TH1F & TH2F
    void FillStatus( const std::string& name, double value )
    {
        std::map<std::string,TH1F*>::iterator iter = hMap.find( name );
        std::map<std::string,TH1F*>::iterator iend = hMap.end();
        if ( iter == iend )
        { LOG_WARNING("%s not found in histograms. Nothing filled!", name.c_str()); return; }
        iter->second->Fill( value+0.001 );
        return;
    }
    void Fill( const std::string& name, double value )
    {
        std::map<std::string,TH1F*>::iterator iter = hMap.find( name );
        std::map<std::string,TH1F*>::iterator iend = hMap.end();
        if ( iter == iend )
        { LOG_WARNING("%s not found in histograms. Nothing filled!", name.c_str()); return; }
        iter->second->Fill( value );
        return;
    }
    void Fill( const std::string& name, double valueX, double valueY )
    {
        std::map<std::string,TH2F*>::iterator iter = hMap2D.find( name );
        std::map<std::string,TH2F*>::iterator iend = hMap2D.end();
        if ( iter == iend )
        { LOG_WARNING("%s not found in 2Dhistograms. Nothing filled!", name.c_str()); return; }
        iter->second->Fill( valueX, valueY );
        return;
    }

    void WriteAll()
    {
        LOG_INFO("writing all histograms in to file...");
        for ( auto& content : hMap )
            content.second->Write();
        for ( auto& content : hMap2D )
            content.second->Write();
    }
    void ClearAll()
    {
        LOG_INFO("cleaning all histograms...");
        for ( auto& content : hMap )
            delete content.second;
        hMap.clear();
        for ( auto& content : hMap2D )
            delete content.second;
        hMap2D.clear();
    }

};






#endif

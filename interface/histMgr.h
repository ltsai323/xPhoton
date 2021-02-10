#ifndef __histMgr_h__
#define __histMgr_h__

#include <string>
#include <vector>
#include <map>
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TFile.h"
#include "/home/ltsai/Work/workspaceGammaPlusJet/interface/logger.h"


namespace histMgr{
    std::map< std::string, TH1F* > hMap;
    std::map< std::string, TH2F* > hMap2D;

    // create TH1F & TH2F
    void Create( const std::string& name, int nbin, double min, double max )
    {
        if ( hMap.find( name ) != hMap.end() )
        { LOG_WARNING( "%s histogram1D duplicated! Please check the createHisto function", name.c_str() ); return; }
        // hMap[name] = new TH1F( name.c_str(), name.c_str(), nbin, min, max );
        hMap[name] = new TH1F( name.c_str(), "", nbin, min, max );
        hMap[name]->GetXaxis()->SetTitle(name.c_str());

        LOG_INFO( "histogram1D append : %s", name.c_str() );
    }
    void Create( const std::string& name, int nbin, double min, double max , int nbin2, double min2, double max2)
    {
        if ( hMap2D.find( name ) != hMap2D.end() )
        { LOG_WARNING( "%s histogram2D duplicated! Please check the createHisto function", name.c_str() ); return; }
        hMap2D[name] = new TH2F( name.c_str(), name.c_str(), nbin, min, max, nbin2, min2, max2 );
        LOG_INFO( "histogram2D append : %s", name.c_str() );
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
        for ( auto& content : hMap )
            content.second->Write();
        for ( auto& content : hMap2D )
            content.second->Write();
    }
    void ClearAll()
    {
        for ( auto& content : hMap )
            delete content.second;
        for ( auto& content : hMap2D )
            delete content.second;
    }

};






#endif

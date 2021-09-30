#include "xPhoton/xPhoton/interface/histMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"

void histMgr::Create( const std::string& name, int nbin, double min, double max )
{
    if ( hMap.find( name ) != hMap.end() )
    { LOG_WARNING( "%s histogram1D duplicated! Please check the createHisto function", name.c_str() ); return; }
    LOG_INFO( "Creating histogram1D : %s", name.c_str() );

    // hMap[name] = new TH1F( name.c_str(), name.c_str(), nbin, min, max );
    hMap[name] = new TH1F( name.c_str(), "", nbin, min, max );
    hMap[name]->GetXaxis()->SetTitle(name.c_str());

}
void histMgr::Create( const std::string& name, int nbin, double min, double max , int nbin2, double min2, double max2)
{
    if ( hMap2D.find( name ) != hMap2D.end() )
    { LOG_WARNING( "%s histogram2D duplicated! Please check the createHisto function", name.c_str() ); return; }
    LOG_INFO( "Creating histogram2D : %s", name.c_str() );

    hMap2D[name] = new TH2F( name.c_str(), name.c_str(), nbin, min, max, nbin2, min2, max2 );
}
// search name and fill TH1F & TH2F
void histMgr::FillStatus( const std::string& name, double value )
{
    std::map<std::string,TH1F*>::iterator iter = hMap.find( name );
    std::map<std::string,TH1F*>::iterator iend = hMap.end();
    if ( iter == iend )
    { LOG_WARNING("%s not found in histograms. Nothing filled!", name.c_str()); return; }
    iter->second->Fill( value+0.001 );
    return;
}
void histMgr::Fill( const std::string& name, double value )
{
    std::map<std::string,TH1F*>::iterator iter = hMap.find( name );
    std::map<std::string,TH1F*>::iterator iend = hMap.end();
    if ( iter == iend )
    { LOG_WARNING("%s not found in histograms. Nothing filled!", name.c_str()); return; }
    iter->second->Fill( value );
    return;
}
void histMgr::Fill( const std::string& name, double valueX, double valueY )
{
    std::map<std::string,TH2F*>::iterator iter = hMap2D.find( name );
    std::map<std::string,TH2F*>::iterator iend = hMap2D.end();
    if ( iter == iend )
    { LOG_WARNING("%s not found in 2Dhistograms. Nothing filled!", name.c_str()); return; }
    iter->second->Fill( valueX, valueY );
    return;
}

void histMgr::WriteTo(TDirectory* dir)
{
    if (dir) dir->cd();
    LOG_INFO( "write histograms In directory %s", dir ? dir->GetName() : "current directory" );
    for ( auto& content : hMap )
        content.second->Write();
    for ( auto& content : hMap2D )
        content.second->Write();
}
void histMgr::DeleteAll()
{
    LOG_INFO("deleting all histograms...");
    for ( auto& content : hMap )
        delete content.second;
    hMap.clear();
    for ( auto& content : hMap2D )
        delete content.second;
    hMap2D.clear();
}

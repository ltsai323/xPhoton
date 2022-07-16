#include <iostream>
#include <string>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;
const int ANNOUNSE_INTERVAL = 100000;



#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TROOT.h"

#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/bin/xPhotonBinning.h"
void PrintHelp()
{
    fprintf(stderr, "############### Usage ################\n");
    fprintf(stderr, "### input a json file as argument  ###\n");
    fprintf(stderr, "### content of json file:          ###\n");
    fprintf(stderr, "### 1. dataera : UL2018, UL2017    ###\n");
    fprintf(stderr, "###              UL2016,2016ReReco ###\n");
    fprintf(stderr, "### 2. OutputFileName              ###\n");
    fprintf(stderr, "### 3. list of InputFiles          ###\n");
    fprintf(stderr, "######################################\n");
    throw "";
}
JsonInfo::JsonInfo( const char* jsonfile )
{
    pt::ptree root;
    pt::read_json(jsonfile, root);
    dataEra                 = root.get<std::string>("dataera"           , "");

    outputfilename= root.get<std::string>("OutputFileName", "");
    for ( pt::ptree::value_type& ifile : root.get_child("InputFiles") )
        inputfiles.emplace_back( ifile.second.data() );
}

int main(int argc, char** argv)
{
    JsonInfo inputvars(argc,argv);

    TChain* ch = new TChain("t");
    for ( const std::string& ifile : inputvars.inputfiles )
        ch->Add(ifile.c_str());

    TFile* outfile = new TFile( inputvars.outputfilename.c_str(), "RECREATE" );
    outfile->cd();
    TTree* outtree = new TTree("binnedTree", "");
    record_BinnedXPhoton outdata;
    outdata.RegBranch(outtree);
    EventFragmentCollector process;
    process.PhoPtBinnings( BinningMethod::ptranges( inputvars.dataEra) );

    TreeReader data(ch, "calib_s4Full5x5");
    for ( const std::string& ifile : inputvars.inputfiles )
        printf("HasMC ? %6s in input file %s\n", data.HasMC()?"True":"False", ifile.c_str());

    LOG_INFO(" processing entries %lld \n", data.GetEntriesFast());
    for ( Long64_t evtIdx = 0; evtIdx != data.GetEntriesFast(); ++evtIdx )
    {
        
        if ( evtIdx % ANNOUNSE_INTERVAL == 0 ) LOG_INFO(" processing enty %llu / %llu = %.2f %% \n", evtIdx, data.GetEntriesFast(), float(10000*evtIdx/data.GetEntriesFast())/100.);
        
        ch->GetEntry(evtIdx);
        data.GetEntry(evtIdx);

        process.SetEvtIdx(evtIdx);
        if (!process.passedPhoSelection(&data) ) continue;
        process.recordEvent(&data, outdata);

        outtree->Fill();
    }

    outtree->Write();
    outfile->Close();
    return 0;
}
const char* GetJsonFromArg( int argc, char** argv )
{ 
    std::cout << " this code argc = " << argc << std::endl;
    if ( argc != 2 ) PrintHelp();
    // .json checker needed!
    return argv[1];
}
void record_BinnedXPhoton::RegBranch( TTree* t )
{
    t->Branch("region_pho"         ,&region_pho         , "region_pho/I");        
    t->Branch("bin_phopt"          ,&bin_phopt          , "bin_phopt/I");         
    //t->Branch("bin_phoptOrig"      ,&bin_phoptOrig      , "bin_phoptOrig/I");         
    t->Branch("bin_phoeta"         ,&bin_phoeta         , "bin_phoeta/I");        
    t->Branch("bin_jeteta"         ,&bin_jeteta         , "bin_jeteta/I");        
    t->Branch("bin_phoHLT"         ,&bin_phoHLT         , "bin_phoHLT/I");        
    t->Branch("bin_matchedphostat" ,&bin_matchedphostat , "bin_matchedphostat/I");
    t->Branch("bin_evtparity"      ,&bin_evtparity      , "bin_evtparity/I");     
    t->Branch("bin_jetflvr"        ,&bin_jetflvr        , "bin_jetflvr/I");       
    t->Branch("jetSel"             ,&jetSel             , "jetSel/I");
    t->Branch("isMatched"          ,&isMatched          , "isMatched/I");


    t->Branch("mva"                ,&mva                , "mva/F");               
    t->Branch("calib_mva"          ,&calib_mva          , "calib_mva/F");         
    t->Branch("phoIsoRaw"          ,&phoIsoRaw          , "phoIsoRaw/F");         
    t->Branch("chIsoRaw"           ,&chIsoRaw           , "chIsoRaw/F");          
    t->Branch("calib_chIsoRaw"     ,&calib_chIsoRaw     , "calib_chIsoRaw/F");    

    t->Branch("btag_BvsAll"        ,&btag_BvsAll        , "btag_BvsAll/F");       
    t->Branch("btag_CvsL"          ,&btag_CvsL          , "btag_CvsL/F");         
    t->Branch("btag_CvsB"          ,&btag_CvsB          , "btag_CvsB/F");         
    t->Branch("btag_secvtxmass"    ,&btag_secvtxmass    , "btag_secvtxmass/F");   
    t->Branch("w_evt"              ,&w_evt              , "w_evt/F");             
    t->Branch("w_central"          ,&w_central          , "w_central/F");         
    t->Branch("w_up"               ,&w_up               , "w_up/F");              
    t->Branch("w_down"             ,&w_down             , "w_down/F");            
    return;
}
bool EventFragmentCollector::passedPhoSelection(TreeReader* data)
{
    Int_t eleVeto   = data->GetInt("eleVeto");
    Float_t recoPt  = data->GetFloat("recoPt");
    Float_t recoEta = data->GetFloat("recoEta");
    Float_t MET     = data->GetFloat("MET");
    Float_t sieie   = data->GetFloat("sieieFull5x5");

    float abseta = fabs(recoEta);
    if ( abseta > 2.5 ) return false;
    if ( abseta > 1.4442 && abseta < 1.566 ) return false;
    if ( eleVeto == 0 ) return false;
    if ( MET / recoPt > 0.7 ) return false;

    if ( abseta > 1.5 && sieie > 0.045 ) return false;
    if ( abseta < 1.5 && sieie > 0.015 ) return false;
    
    return true;
}
bool EventFragmentCollector::passedJetSelection(TreeReader* data)
{
    Int_t   jetID            = data->GetInt  ("jetID"             );
    Int_t   jetPUIDbit       = data->GetInt  ("jetPUIDbit"        );
    Float_t jetPt            = data->GetFloat("jetPt"             );
    Float_t jetEta           = data->GetFloat("jetEta"            );
    Float_t jetDeepCSVTags_c = data->GetFloat("jetDeepCSVTags_c"  );
    if ( data->HasMC() )
    {
        if( jetPt<30. ) return false;;
        if( fabs(jetEta)>2.5 ) return false;;
        if( jetDeepCSVTags_c<-0.99 ) return false;;
        if( jetID != 1 ) return false;;
        if( jetPUIDbit != 7 ) return false;;
    }
    else
    {
        if( jetPt<30. ) return false;;
        if( fabs(jetEta)>2.5 ) return false;;
        if( jetDeepCSVTags_c<-0.99 ) return false;;
    }
    return true;
}
void EventFragmentCollector::recordEvent(TreeReader* data, record_BinnedXPhoton& ovar)
{
    Float_t phopt = data->HasMC() ? data->GetFloat("recoPt") : data->GetFloat("recoPtCalib");
    Float_t chIso = data->HasMC() ? data->GetFloat("chIsoRaw") : data->GetFloat("calib_chIso");
    if ( chIso < 0 ) chIso = 0;

    ovar.region_pho         = BinningMethod::SignalPhoton(chIso, data->GetFloat("recoEta"));
    ovar.bin_phopt          = BinningMethod::PtBin(_ptrange, phopt);
    ovar.bin_phoeta         = BinningMethod::EtaBin( data->GetFloat("recoEta") );
    ovar.bin_jeteta         = BinningMethod::JetBin( data->GetFloat("jetY"), data->GetFloat("jetPt") );
    ovar.bin_phoHLT         = 0; // need to be modified
    ovar.bin_matchedphostat = BinningMethod::PhoMatchStatus(data);
    ovar.bin_evtparity      = _eventRec % 2;
    ovar.bin_jetflvr        = data->HasMC() ? BinningMethod::JetFlavourBin( data->GetInt("jetHadFlvr") ) : -1; // -1 means useless

    ovar.jetSel             = passedJetSelection(data) ? 1 : 0;
    ovar.isMatched          = data->HasMC() ? data->GetInt("isMatched") : 0;


    ovar.mva                = data->GetFloat("mva");
    ovar.calib_mva          = data->HasMC() ? data->GetFloat("calib_mva") : 0;
    ovar.phoIsoRaw          = data->GetFloat("phoIsoRaw");
    ovar.chIsoRaw           = data->GetFloat("chIsoRaw");
    ovar.calib_chIsoRaw     = data->GetFloat("calib_chIso");
    ovar.w_evt              = data->HasMC() ? data->GetFloat("mcweight") * data->GetFloat("puwei") : 1.;

    ovar.btag_BvsAll        = data->GetFloat("jetDeepCSVDiscriminatorTags_BvsAll");
    ovar.btag_CvsL          = data->GetFloat("jetDeepCSVDiscriminatorTags_CvsL");
    ovar.btag_CvsB          = data->GetFloat("jetDeepCSVDiscriminatorTags_CvsB");
    ovar.btag_secvtxmass    = data->GetFloat("jetSubVtxMass");


    ovar.w_central          = data->HasMC() ? data->GetFloat("jetSF.DeepCSV.central") : 1.;

    if ( ovar.bin_jetflvr == 2 )
    {
        ovar.w_up           = data->GetFloat("jetSF.DeepCSV.up_hf");
        ovar.w_down         = data->GetFloat("jetSF.DeepCSV.down_hf");
    }
    else if ( ovar.bin_jetflvr == 1 )
    {
        ovar.w_up           = data->GetFloat("jetSF.DeepCSV.up_cferr1");
        ovar.w_down         = data->GetFloat("jetSF.DeepCSV.down_cferr1");
    }
    else if ( ovar.bin_jetflvr == 0 )
    {
        ovar.w_up           = data->GetFloat("jetSF.DeepCSV.up_lf");
        ovar.w_down         = data->GetFloat("jetSF.DeepCSV.down_lf");
    }
    else
    {
        ovar.w_up           = 1.;
        ovar.w_down         = 1.;
    }
    return;
}
std::vector<float> BinningMethod::ptranges( std::string dataera )
{
     return std::vector<float>({25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}); // size = 16. ptbin = [0,15]
}
Int_t BinningMethod::PtBin( const std::vector<float>& ptranges,float pt )
{
    int idx = ptranges.size();
    while ( idx-- )
    { if ( pt >= ptranges[idx] ) return idx; }
    return -1;
}
Int_t BinningMethod::EtaBin(float eta)
{ return fabs(eta) < 1.5 ? 0 : 1; }
Int_t BinningMethod::JetBin(float jetY, float jetpt)
{
    if ( jetpt == 0 ) return 2;
    if ( fabs(jetY) < 1.5 ) return 0;
    return 1;
}
Int_t BinningMethod::HLTBin(int ptbin, std::string dataera)
{ return 0; }
//Int_t BinningMethod::SignalPhoton(float isovar, bool isEndcap)
Int_t BinningMethod::SignalPhoton(float isovar, float eta )
{
    bool isEndcap = fabs(eta) > 1.5;
    // signal region : EB=chIso<2, EE=chIso<1.5
    // sideband region : EB=3.5<chIso<10 EE=3<chIso<10
    if ( isEndcap )
    {
        if ( isovar < 1.5 ) return PHOREGION_SIGNAL;
        if ( isovar > 6. && isovar < 12. ) return PHOREGION_SIDEBAND;
    }
    else
    {
        if ( isovar < 2.0 ) return PHOREGION_SIGNAL;
        if ( isovar > 7.&& isovar < 13. ) return PHOREGION_SIDEBAND;
    }
    return PHOREGION_NONE;
}
Int_t BinningMethod::JetFlavourBin( int jethadflvr )
{
    if     (fabs(jethadflvr)==5) return 2;
    else if(fabs(jethadflvr)==4) return 1;
    return 0;
}
Int_t BinningMethod::PhoMatchStatus( TreeReader* data )
{
    Float_t chIsoRaw = data->GetFloat("chIsoRaw");
    if (!data->HasMC() )
    {
        if ( chIsoRaw<2.0 ) return 0;
        return 1;
    }

    Int_t isMatched = data->GetInt("isMatched");

    if ( data->GetInt("isQCD") != 0 )
    {
        if ( isMatched != 1 )
        {
            if ( chIsoRaw < 2.0 ) return 2;
            else if ( chIsoRaw > 5.0 && chIsoRaw < 10.0 ) return 3;
        }
        return 4;
    }
    if ( isMatched==1 && chIsoRaw<2.0   ) return 0;
    return 1;
}

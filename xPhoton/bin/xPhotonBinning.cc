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
    fprintf(stderr, "############### Usage ###############\n");
    fprintf(stderr, "#####################################\n");
    throw "";
}
JsonInfo::JsonInfo( const char* jsonfile )
{
    // pt::ptree root;
    // pt::read_json(jsonfile, root);
    // nJobs                   = root.get<int> ("nJobs"                    , 4);
    // isMC                    = root.get<bool>("isMC"                     , true);
    // dataEra                 = root.get<std::string>("dataera"           , "");

    // outputfilename= root.get<std::string>("OutputFileName", "");
    // for ( pt::ptree::value_type& ifile : root.get_child("InputFiles") )
    //     inputfiles.emplace_back( ifile.second.data() );
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

    TreeReader data(ch);

    //LOG_INFO(" processing entries %lld \n", data.GetEntriesFast());
    //for ( Long64_t evtIdx = 0; evtIdx != data.GetEntriesFast(); ++evtIdx )
    //{
    //    
    //    if ( evtIdx % ANNOUNSE_INTERVAL == 0 ) LOG_INFO(" processing enty %llu / %llu = %.2f %% \n", evtIdx, data.GetEntriesFast(), float(10000*evtIdx/data.GetEntriesFast())/100.);
    //    
    //    ch->GetEntry(evtIdx);
    //    data.GetEntry(evtIdx);

    //    outtree->Fill();
    //}

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
    return;
}

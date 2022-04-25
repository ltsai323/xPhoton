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
#include "TMVA/Reader.h"

#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include "xPhoton/xPhoton/interface/ShowerShapeCorrectionAdapter.h"


void PrintHelp()
{
    fprintf(stderr, "############### Usage ###############\n");
    fprintf(stderr, "## Input a json file to configure  ##\n");
    fprintf(stderr, "## this file. To check the format, ##\n");
    fprintf(stderr, "## check $CMSSW_BASE/src/xPhoton/  ##\n");
    fprintf(stderr, "## xPhoton/python/                 ##\n");
    fprintf(stderr, "## xPhotonInfoUpdater.json         ##\n");
    fprintf(stderr, "#####################################\n");
    throw "";
}
const char* GetJsonFromArg( int argc, char** argv )
{ 
    std::cout << " this code argc = " << argc << std::endl;
    if ( argc != 2 ) PrintHelp();
    // .json checker needed!
    return argv[1];
}
struct JsonInfo
{
    JsonInfo( const char* jsonfile )
    {
        pt::ptree root;
        pt::read_json(jsonfile, root);
        nJobs                   = root.get<int> ("nJobs"                    , 4);
        updateMVA               = root.get<bool>("updateMVA"                , false);
        updatePU                = root.get<bool>("updatePU"                 , false);
        updateBTagCalibration   = root.get<bool>("updateBTagCalibration"    , false);
        isMC                    = root.get<bool>("isMC"                     , true);
        dataEra                 = root.get<std::string>("dataera"           , "");

        outputfilename= root.get<std::string>("OutputFileName", "");
        for ( pt::ptree::value_type& ifile : root.get_child("InputFiles") )
            inputfiles.emplace_back( ifile.second.data() );
    }
    JsonInfo( int argc, char** argv ) : JsonInfo( GetJsonFromArg(argc,argv) ) { }

    unsigned nJobs;
    bool updateMVA;
    bool updatePU;
    bool updateBTagCalibration;
    bool isMC;
    std::string dataEra;
    std::string outputfilename;
    std::vector<std::string> inputfiles;
};

//void UpdateMVA( const JsonInfo& jobInfo, TTree* inTree )
int main(int argc, char** argv)
{
    JsonInfo inputvars(argc,argv);

    TChain* ch = new TChain("t");
    for ( const std::string& ifile : inputvars.inputfiles )
        ch->Add(ifile.c_str());
    // init of main
    
    TTree* inTree = ch;
    const JsonInfo& jobInfo = inputvars;
    inTree->SetBranchStatus("*", 1);
    TreeReader data(inTree);

    // declare MVA {{{
    float 
        recoPhi,
        r9Full5x5,
        sieieFull5x5,
        sieipFull5x5,
        s4Full5x5,
        recoSCEta,
        rawE,
        scEtaWidth,
        scPhiWidth,

        esEnergyOverSCRawEnergy,
        esRR,
        rho;
    TMVA::Reader* tmvaReader[2];
    for ( int iBE = 0; iBE < 2; ++iBE )
    {
        tmvaReader[iBE] = new TMVA::Reader("!Color:Silent");

        // add classification variables
        tmvaReader[iBE]->AddVariable("recoPhi", &recoPhi);
        tmvaReader[iBE]->AddVariable("r9Full5x5", &r9Full5x5);
        tmvaReader[iBE]->AddVariable( "sieieFull5x5", &sieieFull5x5 );
        tmvaReader[iBE]->AddVariable( "sieipFull5x5", &sieipFull5x5 );     
        if ( jobInfo.dataEra == "2016ReReco" )
        {
            //tmvaReader[iBE]->AddVariable("r9", &r9Full5x5);
            tmvaReader[iBE]->AddVariable( "s4 := e2x2Full5x5/e5x5Full5x5", &s4Full5x5 );	       
        }
        if ( jobInfo.dataEra == "UL2018" )
        {
            tmvaReader[iBE]->AddVariable( "s4Full5x5", &s4Full5x5 );	       
        }
        tmvaReader[iBE]->AddVariable("recoSCEta", &recoSCEta );
        tmvaReader[iBE]->AddVariable("rawE", &rawE );
        tmvaReader[iBE]->AddVariable("scEtaWidth", &scEtaWidth );
        tmvaReader[iBE]->AddVariable("scPhiWidth", &scPhiWidth );
        if (iBE == 1)
        {
            if ( jobInfo.dataEra == "2016ReReco" )
                tmvaReader[iBE]->AddVariable("ESEn := esEn/rawE", &esEnergyOverSCRawEnergy );
            if ( jobInfo.dataEra == "UL2018" )
                tmvaReader[iBE]->AddVariable("esEnergyOverSCRawEnergy", &esEnergyOverSCRawEnergy );
            tmvaReader[iBE]->AddVariable("esRR", &esRR );
        }
        tmvaReader[iBE]->AddVariable("rho", &rho);


        std::cout << "PhotonMVAcalculator : using " << ExternalFilesMgr::xmlFile_MVAweight(iBE, jobInfo.dataEra) << std::endl;
        tmvaReader[iBE]->BookMVA("BDT", ExternalFilesMgr::xmlFile_MVAweight(iBE, jobInfo.dataEra) );
    }
    // declare MVA done }}}
    ShowerShapeCorrectionAdapter SScorr( jobInfo.dataEra, jobInfo.isMC );


    TFile* outfile = new TFile( jobInfo.outputfilename.c_str(), "RECREATE" );
    outfile->cd();
    TTree* outtree = inTree->CloneTree(0);
    outtree->SetAutoSave(ANNOUNSE_INTERVAL);

    float mva = 0;
    float calib_mva = 0;
    outtree->SetBranchStatus("mva", 0);
    outtree->SetBranchStatus("calib_mva", 0);
    outtree->Branch("mva", &mva, "mva/F");
    outtree->Branch("calib_mva", &calib_mva, "calib_mva/F");

    LOG_INFO(" processing entries %lld \n", data.GetEntriesFast());
    for ( Long64_t evtIdx = 0; evtIdx != data.GetEntriesFast(); ++evtIdx )
    {
        
        if ( evtIdx % ANNOUNSE_INTERVAL == 0 ) LOG_INFO(" processing enty %llu / %llu = %.2f %% \n", evtIdx, data.GetEntriesFast(), float(10000*evtIdx/data.GetEntriesFast())/100.);
        
        inTree->GetEntry(evtIdx);
        data.GetEntry(evtIdx);
        // variables declare and data loader {{{
        bool isEE = fabs(data.GetFloat("recoSCEta")) > 1.5 ? 1 : 0;

        if ( jobInfo.isMC )
        {
            ShowerShapeCorrectionParameters_xPhoton::loadVars(&SScorr, &data);
            SScorr.CalculateCorrections();
        }

        // TMVA used pars.
        recoPhi                  = data.GetFloat("recoPhi"                );
        r9Full5x5                = data.GetFloat("r9Full5x5"              );
        sieieFull5x5             = data.GetFloat("sieieFull5x5"           );
        sieipFull5x5             = data.GetFloat("sieipFull5x5"           );
        s4Full5x5                = data.GetFloat("s4Full5x5"              );
        recoSCEta                = data.GetFloat("recoSCEta"              );
        rawE                     = data.GetFloat("rawE"                   );
        scEtaWidth               = data.GetFloat("scEtaWidth"             );
        scPhiWidth               = data.GetFloat("scPhiWidth"             );

        esEnergyOverSCRawEnergy  = data.GetFloat("esEnergyOverSCRawEnergy");
        esRR                     = data.GetFloat("esRR"                   );
        rho                      = data.GetFloat("rho"                    );

        // variables declare and data loader end }}}
        
        mva = tmvaReader[isEE]->EvaluateMVA("BDT");
        if ( jobInfo.isMC )
        {
            r9Full5x5               = SScorr.Corrected( ShowerShapeCorrectionAdapter::r9       );
            s4Full5x5               = SScorr.Corrected( ShowerShapeCorrectionAdapter::s4       );
            sieieFull5x5            = SScorr.Corrected( ShowerShapeCorrectionAdapter::sieie    );
            sieipFull5x5            = SScorr.Corrected( ShowerShapeCorrectionAdapter::sieip    );
            scEtaWidth   	        = SScorr.Corrected( ShowerShapeCorrectionAdapter::etaWidth );
            scPhiWidth   	        = SScorr.Corrected( ShowerShapeCorrectionAdapter::etaWidth );
            esEnergyOverSCRawEnergy = SScorr.Corrected( ShowerShapeCorrectionAdapter::esEnergyOverSCRawEnergy);
        }
        calib_mva = tmvaReader[isEE]->EvaluateMVA("BDT");

        outtree->Fill();
    }

    outtree->Write();
    outfile->Close();
    return 0;
}


#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include <stdio.h>
//#include <stdexcept>

const char* ExternalFilesMgr::xmlFile_MVAweight(int isEndcap, int year)
{
    switch ( year )
    {
    case 2015:
        if ( isEndcap )
            return "";
        else
            return "";
    case 2016:
        if ( isEndcap )
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/spring16_80x_EE_TMVAnalysis_BDT.weights.xml";
        else
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/spring16_80x_EB_TMVAnalysis_BDT.weights.xml";
    case 2017:
        if ( isEndcap )
            return "";
        else
            return "";
    case 2018:
        if ( isEndcap )
            return "";
        else
            return "";
    default:
        return "";
    }
    return "";
}
const char* ExternalFilesMgr::RooFile_PileUp()
{
    return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/puweights/102X/autum18/PU_histo_13TeV_2018_GoldenJSON_69200nb.root";
}
const char* ExternalFilesMgr::RooFile_PileUp_Run2016_69200nb_Moriond17()
{
    return "/home/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/puweights/94X/summer16/PUweight_2016Legacy_forMoriond17_69200nb.root";
}
const char* ExternalFilesMgr::RooFile_ShowerShapeCorrection()
{
    //return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/transformation_76X_v2.root";
    return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/transformation5x5_Legacy2016_v1.root";
}

char tmpstr[200];
const char* ExternalFilesMgr::testchar()
{
    return "kkk";
    sprintf(tmpstr, "hiii");
    return tmpstr;
}

const char* ExternalFilesMgr::csvFile_BTagCalib_CSVv2()
{ return ""; }
const char* ExternalFilesMgr::csvFile_BTagCalib_DeepCSV()
{ return "/home/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2016Legacy/DeepCSV_2016LegacySF_V1_TuneCP5.csv"; }
const char* ExternalFilesMgr::csvFile_BTagCalib_DeepFlavour()
{ return "/home/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2016Legacy/DeepJet_2016LegacySF_V1_TuneCP5.csv"; }
const char* ExternalFilesMgr::csvFile_BTagCalib_DeepFlavour_JESreduced()
{ return "/home/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2016Legacy/DeepJet_2016LegacySF_V1_TuneCP5_JESreduced.csv"; }
const char* ExternalFilesMgr::csvFile_BTagCalibs(std::string name)
{
    if ( name == "CSVv2"                  ) return csvFile_BTagCalib_CSVv2();
    if ( name == "DeepCSV"                ) return csvFile_BTagCalib_DeepCSV();
    if ( name == "DeepFlavour"            ) return csvFile_BTagCalib_DeepFlavour();
    if ( name == "DeepFlavour_JESReduced" ) return csvFile_BTagCalib_DeepFlavour_JESreduced();
    LOG_FATAL( "Unknown input argument name '%s'", name.c_str() );
    //throw std::invalid_argument("ExternalFilesMgr : Unknown input argument name ");
    return "";
}
std::string ExternalFilesMgr::csvFile_testing()
{ return "/home/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/CSVv2_94XSF_V2_B_F.csv"; }

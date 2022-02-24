#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include <stdio.h>
//#include <stdexcept>

/*
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
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/fall17_94X_EE_TMVAnalysis_BDT.weights.xml";
        else
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/fall17_94X_EB_TMVAnalysis_BDT.weights.xml";
    case 2018:
        if ( isEndcap )
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/autumn18_EE_TMVAnalysis_BDT.weights.xml";
        else
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/autumn18_EB_TMVAnalysis_BDT.weights.xml";
    default:
        return "";
    }
    return "";
}
*/
/*
const char* ExternalFilesMgr::RooFile_PileUp()
{
    return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/puweights/102X/autum18/PU_histo_13TeV_2018_GoldenJSON_69200nb.root";
}
const char* ExternalFilesMgr::RooFile_PileUp_Run2016_69200nb_Moriond17()
{
    return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/puweights/94X/summer16/PUweight_2016Legacy_forMoriond17_69200nb.root";
}
*/
/*
const char* ExternalFilesMgr::RooFile_PileUp(int year)
{
    switch ( year )
    {
    case 2015:
        return "";
    case 2016:
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/puweights/94X/summer16/PUweight_2016Legacy_forMoriond17_69200nb.root";
    case 2017:
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/puweights/102X/fall17/PU_histo_13TeV_2018_GoldenJSON_69200nb.root";
    case 2018:
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/puweights/102X/autum18/PU_histo_13TeV_2018_GoldenJSON_69200nb.root";
    default:
        return "";
    }
    return "";
    
}
*/
/*
const char* ExternalFilesMgr::RooFile_ShowerShapeCorrection()
{
    //return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/transformation_76X_v2.root";
    return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/transformation5x5_Legacy2016_v1.root";
}
*/


/*
const char* ExternalFilesMgr::csvFile_BTagCalib_CSVv2()
{ return ""; }
const char* ExternalFilesMgr::csvFile_BTagCalib_DeepCSV()
{ return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2016Legacy/DeepCSV_2016LegacySF_V1_TuneCP5.csv"; }
const char* ExternalFilesMgr::csvFile_BTagCalib_DeepFlavour()
{ return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2016Legacy/DeepJet_2016LegacySF_V1_TuneCP5.csv"; }
const char* ExternalFilesMgr::csvFile_BTagCalib_DeepFlavour_JESreduced()
{ return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2016Legacy/DeepJet_2016LegacySF_V1_TuneCP5_JESreduced.csv"; }
*/



const char* ExternalFilesMgr::csvFile_BTagCalib_DeepFlavour(std::string era)
{
    if      ( era == "2016ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2016_94XReReco/DeepJet_2016LegacySF_V1_TuneCP5.csv";
    else if ( era == "2017ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2017_94XReReco/DeepFlavour_94XSF_V4_B_F.csv";
    else if ( era == "2018ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2018_102XReReco/reshaping_deepJet_106XUL17_v3.csv";
// https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation106XUL16postVFP
    else if ( era == "UL2016"     ) return ""; // waiting for update.
    else if ( era == "UL2017"     )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/UL2017/reshaping_deepJet_106XUL17_v3.csv";
    else if ( era == "UL2018"     )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/UL2018/reshaping_deepJet_106XUL18_v2.csv";
    return "";
}
const char* ExternalFilesMgr::csvFile_BTagCalib_DeepCSV(std::string era)
{
    if      ( era == "2016ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2016_94XReReco/DeepCSV_2016LegacySF_V1_TuneCP5.csv";
    else if ( era == "2017ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2017_94XReReco/DeepCSV_94XSF_V5_B_F.csv";
    else if ( era == "2018ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/2018_102XReReco/reshaping_deepCSV_106XUL17_v3.csv";
// https://twiki.cern.ch/twiki/bin/view/CMS/BtagRecommendation106XUL16postVFP
    else if ( era == "UL2016"     ) return ""; // waiting for update.
    else if ( era == "UL2017"     )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/UL2017/reshaping_deepCSV_106XUL17_v3.csv";
    else if ( era == "UL2018"     )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/UL2018/reshaping_deepCSV_106XUL18_v2.csv";
    return "";
}

const char* ExternalFilesMgr::csvFile_BTagCalibs(std::string name, std::string era)
{
    //if ( name == "CSVv2"                  ) return csvFile_BTagCalib_CSVv2(era);
    if ( name == "DeepCSV"                ) return csvFile_BTagCalib_DeepCSV(era);
    if ( name == "DeepFlavour"            ) return csvFile_BTagCalib_DeepFlavour(era);
    //if ( name == "DeepFlavour_JESReduced" ) return csvFile_BTagCalib_DeepFlavour_JESreduced(era);
    LOG_FATAL( "Unknown input argument name '%s'", name.c_str() );
    //throw std::invalid_argument("ExternalFilesMgr : Unknown input argument name ");
    return "";
}

/*
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
*/
std::string ExternalFilesMgr::csvFile_testing()
{ return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/csvfiles/CSVv2_94XSF_V2_B_F.csv"; }


const char* ExternalFilesMgr::RooFile_PileUp(std::string era)
{
    if      ( era == "2016ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/PileupWeight/2016ReReco_Moriond17/puweights_PileupHistogram-goldenJSON-13tev-2016-69200ub.root";
    else if ( era == "2017ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/PileupWeight/2017ReReco_WinterMC/puweights_PileupHistogram-goldenJSON-13tev-2017-69200ub.root";
    else if ( era == "2018ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/PileupWeight/2018ReReco_JuneProjectionFull18/puweights_PileupHistogram-goldenJSON-13tev-2018-69200ub.root";
    else if ( era == "UL2016"     )
        return "/wk_cms/ltsai/ReceivedFile/PileupWeight/UL2016_PoissonOOTPU/puweights_PileupHistogram-goldenJSON-13tev-2016-69200ub-99bins.root";
    else if ( era == "UL2017"     )
        return "/wk_cms/ltsai/ReceivedFile/PileupWeight/UL2017_PoissonOOTPU/puweights_PileupHistogram-goldenJSON-13tev-2017-69200ub-99bins.root";
    else if ( era == "UL2018"     )
        return "/wk_cms/ltsai/ReceivedFile/PileupWeight/UL2018_PoissonOOTPU/puweights_PileupHistogram-goldenJSON-13tev-2018-69200ub-99bins.root";
    return "";
}
const char* ExternalFilesMgr::RooFile_ShowerShapeCorrection(std::string era)
{
    if      ( era == "2016ReReco" )
        return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/rootfiles/external/transformation5x5_Legacy2016_v1.root";
    else if ( era == "2017ReReco" )
        return "";
    else if ( era == "2018ReReco" )
        return "";
    else if ( era == "UL2016"     )
        return "";
    else if ( era == "UL2017"     )
        return "";
    else if ( era == "UL2018"     )
        return "";
    return "";
}
const char* ExternalFilesMgr::xmlFile_MVAweight(int isEndcap, std::string era)
{
    if ( isEndcap )
    {
        if      ( era == "2016ReReco" )
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/spring16_80x_EE_TMVAnalysis_BDT.weights.xml";
        else if ( era == "2017ReReco" )
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/fall17_94X_EE_TMVAnalysis_BDT.weights.xml";
        else if ( era == "2018ReReco" )
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/autumn18_EE_TMVAnalysis_BDT.weights.xml";
        else if ( era == "UL2016"     )
            return "";
        else if ( era == "UL2017"     )
            return "";
        else if ( era == "UL2018"     )
            return "/home/ltsai/ReceivedFile/GJet/TMVATrainingResult/UL2018/BDT_EE/dataset/weights/TMVAnalysis_BDT.weights.xml";
    }
    else
    {
        if      ( era == "2016ReReco" )
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/spring16_80x_EB_TMVAnalysis_BDT.weights.xml";
        else if ( era == "2017ReReco" )
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/fall17_94X_EB_TMVAnalysis_BDT.weights.xml";
        else if ( era == "2018ReReco" )
            return "/wk_cms/ltsai/ReceivedFile/RSprocessedFiles/xmlfiles/external/autumn18_EB_TMVAnalysis_BDT.weights.xml";
        else if ( era == "UL2016"     )
            return "";
        else if ( era == "UL2017"     )
            return "";
        else if ( era == "UL2018"     )
            return "/home/ltsai/ReceivedFile/GJet/TMVATrainingResult/UL2018/BDT_EB/dataset/weights/TMVAnalysis_BDT.weights.xml";
    }
    return "";
}

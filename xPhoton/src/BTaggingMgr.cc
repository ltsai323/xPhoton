#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include <map>
#include <string>


namespace t
{
    // use std::string due to a equal sign is needed. first : algorithm, second : systType
    std::map<std::string, std::vector<std::string> > systTypeCollection;
    std::vector<const char*> flavourCollection;
    void SetContent(){
        if ( systTypeCollection.size() != 0 )  return;
        flavourCollection.push_back("Bquark");
        flavourCollection.push_back("Cquark");
        flavourCollection.push_back("Lights");

        systTypeCollection["CSVv2"] = {
            "central",
            "down_cferr1",
            "down_cferr2",
            "down_hf",
            "down_lf",
            "up_cferr1",
            "up_cferr2",
            "up_hf",
            "up_lf" 
                /* only use central for first galanced
            "central",
            "down_cferr1",
            "down_cferr2",
            "down_hf",
            "down_hfstats1",
            "down_hfstats2",
            "down_jes",
            "down_lf",
            "down_lfstats1",
            "down_lfstats2",
            "up_cferr1",
            "up_cferr2",
            "up_hf",
            "up_hfstats1",
            "up_hfstats2",
            "up_jes",
            "up_lf",
            "up_lfstats1",
            "up_lfstats2" 
            */
        };
        systTypeCollection["DeepCSV"] = {
            "central",
            "down_cferr1",
            "down_cferr2",
            "down_hf",
            "down_lf",
            "up_cferr1",
            "up_cferr2",
            "up_hf",
            "up_lf" 
                /* only use central value for first galanced
            "central",
            "down_cferr1",
            "down_cferr2",
            "down_hf",
            "down_hfstats1",
            "down_hfstats2",
            "down_jes",
            "down_jesAbsoluteMPFBias",
            "down_jesAbsoluteScale",
            "down_jesAbsoluteStat",
            "down_jesFlavorQCD",
            "down_jesFragmentation",
            "down_jesPileUpDataMC",
            "down_jesPileUpPtBB",
            "down_jesPileUpPtEC1",
            "down_jesPileUpPtEC2",
            "down_jesPileUpPtHF",
            "down_jesPileUpPtRef",
            "down_jesRelativeBal",
            "down_jesRelativeFSR",
            "down_jesRelativeJEREC1",
            "down_jesRelativeJEREC2",
            "down_jesRelativeJERHF",
            "down_jesRelativePtBB",
            "down_jesRelativePtEC1",
            "down_jesRelativePtEC2",
            "down_jesRelativePtHF",
            "down_jesRelativeStatEC",
            "down_jesRelativeStatFSR",
            "down_jesRelativeStatHF",
            "down_jesSinglePionECAL",
            "down_jesSinglePionHCAL",
            "down_jesTimePtEta",
            "down_lf",
            "down_lfstats1",
            "down_lfstats2",
            "up_cferr1",
            "up_cferr2",
            "up_hf",
            "up_hfstats1",
            "up_hfstats2",
            "up_jes",
            "up_jesAbsoluteMPFBias",
            "up_jesAbsoluteScale",
            "up_jesAbsoluteStat",
            "up_jesFlavorQCD",
            "up_jesFragmentation",
            "up_jesPileUpDataMC",
            "up_jesPileUpPtBB",
            "up_jesPileUpPtEC1",
            "up_jesPileUpPtEC2",
            "up_jesPileUpPtHF",
            "up_jesPileUpPtRef",
            "up_jesRelativeBal",
            "up_jesRelativeFSR",
            "up_jesRelativeJEREC1",
            "up_jesRelativeJEREC2",
            "up_jesRelativeJERHF",
            "up_jesRelativePtBB",
            "up_jesRelativePtEC1",
            "up_jesRelativePtEC2",
            "up_jesRelativePtHF",
            "up_jesRelativeStatEC",
            "up_jesRelativeStatFSR",
            "up_jesRelativeStatHF",
            "up_jesSinglePionECAL",
            "up_jesSinglePionHCAL",
            "up_jesTimePtEta",
            "up_lf",
            "up_lfstats1",
            "up_lfstats2" 
            */
        };
        systTypeCollection["DeepFlavour"] = {
            "central",
            "down_cferr1",
            "down_cferr2",
            "down_hf",
            "down_lf",
            "up_cferr1",
            "up_cferr2",
            "up_hf",
            "up_lf" 
                /* only use central value for first galance
            "central",
            "down_cferr1",
            "down_cferr2",
            "down_hf",
            "down_hfstats1",
            "down_hfstats2",
            "down_jes",
            "down_jesAbsoluteMPFBias",
            "down_jesAbsoluteScale",
            "down_jesAbsoluteStat",
            "down_jesFlavorQCD",
            "down_jesFragmentation",
            "down_jesPileUpDataMC",
            "down_jesPileUpPtBB",
            "down_jesPileUpPtEC1",
            "down_jesPileUpPtEC2",
            "down_jesPileUpPtHF",
            "down_jesPileUpPtRef",
            "down_jesRelativeBal",
            "down_jesRelativeFSR",
            "down_jesRelativeJEREC1",
            "down_jesRelativeJEREC2",
            "down_jesRelativeJERHF",
            "down_jesRelativePtBB",
            "down_jesRelativePtEC1",
            "down_jesRelativePtEC2",
            "down_jesRelativePtHF",
            "down_jesRelativeStatEC",
            "down_jesRelativeStatFSR",
            "down_jesRelativeStatHF",
            "down_jesSinglePionECAL",
            "down_jesSinglePionHCAL",
            "down_jesTimePtEta",
            "down_lf",
            "down_lfstats1",
            "down_lfstats2",
            "up_cferr1",
            "up_cferr2",
            "up_hf",
            "up_hfstats1",
            "up_hfstats2",
            "up_jes",
            "up_jesAbsoluteMPFBias",
            "up_jesAbsoluteScale",
            "up_jesAbsoluteStat",
            "up_jesFlavorQCD",
            "up_jesFragmentation",
            "up_jesPileUpDataMC",
            "up_jesPileUpPtBB",
            "up_jesPileUpPtEC1",
            "up_jesPileUpPtEC2",
            "up_jesPileUpPtHF",
            "up_jesPileUpPtRef",
            "up_jesRelativeBal",
            "up_jesRelativeFSR",
            "up_jesRelativeJEREC1",
            "up_jesRelativeJEREC2",
            "up_jesRelativeJERHF",
            "up_jesRelativePtBB",
            "up_jesRelativePtEC1",
            "up_jesRelativePtEC2",
            "up_jesRelativePtHF",
            "up_jesRelativeStatEC",
            "up_jesRelativeStatFSR",
            "up_jesRelativeStatHF",
            "up_jesSinglePionECAL",
            "up_jesSinglePionHCAL",
            "up_jesTimePtEta",
            "up_lf",
            "up_lfstats1",
            "up_lfstats2" 
                */
        };
        systTypeCollection["DeepFlavour_JESReduced"] = {
            "central",
            "down_cferr1",
            "down_cferr2",
            "down_hf",
            "down_lf",
            "up_cferr1",
            "up_cferr2",
            "up_hf",
            "up_lf" 
                /* only used central value for first galance
            "central",
            "down_cferr1",
            "down_cferr2",
            "down_hf",
            "down_hfstats1",
            "down_hfstats2",
            "down_jes",
            "down_jesAbsolute",
            "down_jesAbsolute_2017",
            "down_jesBBEC1",
            "down_jesBBEC1_2017",
            "down_jesEC2",
            "down_jesEC2_2017",
            "down_jesFlavorQCD",
            "down_jesHF",
            "down_jesHF_2017",
            "down_jesRelativeBal",
            "down_jesRelativeSample_2017",
            "down_lf",
            "down_lfstats1",
            "down_lfstats2",
            "up_cferr1",
            "up_cferr2",
            "up_hf",
            "up_hfstats1",
            "up_hfstats2",
            "up_jes",
            "up_jesAbsolute",
            "up_jesAbsolute_2017",
            "up_jesBBEC1",
            "up_jesBBEC1_2017",
            "up_jesEC2",
            "up_jesEC2_2017",
            "up_jesFlavorQCD",
            "up_jesHF",
            "up_jesHF_2017",
            "up_jesRelativeBal",
            "up_jesRelativeSample_2017",
            "up_lf",
            "up_lfstats1",
            "up_lfstats2"
            */
        };
    }
}; // end of namespace t
BTaggingMgr::BTaggingMgr() :

    _usedAlgorithmNames(),
    _systTypeRegisted(false)
{
}

void BTaggingMgr::UseAlgorithm(std::string algorithmName)
{
    t::SetContent();
    if ( t::systTypeCollection.find(algorithmName) == t::systTypeCollection.end() )
        LOG_FATAL("Input name '%s' cannot be recognized in BTaggingMgr", algorithmName);
    _usedAlgorithmNames.push_back(algorithmName);
}

void BTaggingMgr::RegisterSystTypes()
{
    if ( _systTypeRegisted )
        LOG_FATAL("This function cannot be used twice. Please use it after all algorithms assigned");

    _systTypeRegisted=true;
    for ( auto usedAlgorithm : _usedAlgorithmNames )
        _usedSystTypes[usedAlgorithm] = t::systTypeCollection[usedAlgorithm];

    calibPTRs.clear(); calibReaderPTRs.clear();
    calibPTRs.reserve(_usedSystTypes.size());
    calibReaderPTRs.reserve(_usedSystTypes.size());

    for ( auto usedAlgorithm : _usedAlgorithmNames )
    {
        calibPTRs.push_back(
                std::make_shared<BTagCalibration>( usedAlgorithm, ExternalFilesMgr::csvFile_BTagCalibs(usedAlgorithm) )
                );
        calibReaderPTRs.push_back(
                std::make_shared<BTagCalibrationReader>( BTagEntry::OP_RESHAPING, "central", _usedSystTypes[usedAlgorithm] )
                //std::make_shared<BTagCalibrationReader>( BTagEntry::OP_TIGHT, "central", _usedSystTypes[usedAlgorithm] )
                );
        BTagCalibration* calib = calibPTRs.back().get();

        std::shared_ptr<BTagCalibrationReader> calibReaderPTR = calibReaderPTRs.back();
        calibReaderPTR->load(*calib, BTagEntry::FLAV_B   , "iterativefit" );
        calibReaderPTR->load(*calib, BTagEntry::FLAV_C   , "iterativefit" );
        calibReaderPTR->load(*calib, BTagEntry::FLAV_UDSG, "iterativefit" );

        /*
        calibReaderPTR->load(*calib, BTagEntry::FLAV_B   , "comb" );
        calibReaderPTR->load(*calib, BTagEntry::FLAV_C   , "comb" );
        calibReaderPTR->load(*calib, BTagEntry::FLAV_UDSG, "comb" );
        */
    }
    InitVars();
}
void BTaggingMgr::InitVars()
{
    if ( !_systTypeRegisted )
        LOG_FATAL("You need to execute function RegisterSystTypes() before initialize variables.");

    if ( systVars.size() == 0 ) // create new variables
        for ( int iAlgo = 0; iAlgo < _usedAlgorithmNames.size(); ++iAlgo )
        {
            const std::string algoName = _usedAlgorithmNames[iAlgo];
            for ( int iSyst = 0; iSyst < _usedSystTypes[algoName].size(); ++iSyst )
            { systVars[ systVarIdx(iAlgo,iSyst) ] = 0; }
        }
    else
        for ( auto systVarIter = systVars.begin(); systVarIter != systVars.end(); ++systVarIter )
            systVarIter->second = 0;
}
void BTaggingMgr::RegBranch(TTree* t)
{
    if ( !_systTypeRegisted )
        LOG_FATAL("You need to execute function RegisterSystTypes() before register branch into tree.");
    char bname[200], bnameF[200];
    if ( t == nullptr || t->IsZombie() ) LOG_FATAL("input tree is invalid");

    for ( int iAlgo = 0; iAlgo < _usedAlgorithmNames.size(); ++iAlgo )
    {
        const std::string algorithm = _usedAlgorithmNames[iAlgo];
        for ( int iSyst = 0; iSyst < _usedSystTypes[algorithm].size(); ++iSyst )
        {
            const std::string systType = _usedSystTypes[algorithm][iSyst];
            sprintf(bname , "jetSF.%s.%s"  , algorithm.c_str(), systType.c_str());
            sprintf(bnameF, "jetSF.%s.%s/F", algorithm.c_str(), systType.c_str());
            t->Branch(bname, &systVars[ systVarIdx(iAlgo,iSyst) ], bnameF);
        }
    }
}
void BTaggingMgr::FillWeightToEvt(float pt_, float eta_, int hadFlav_, float bDis_)
{
    float bDis = bDis_;
    if ( bDis_ < 0.0 ) bDis = -0.05;
    else if ( bDis_ > 1.0 ) bDis = 1.0;
    for ( int iAlgo = 0; iAlgo < _usedAlgorithmNames.size(); ++iAlgo )
    {
        const std::string algorithm = _usedAlgorithmNames[iAlgo];
        for ( int iSyst = 0; iSyst < _usedSystTypes[algorithm].size(); ++iSyst )
        {
            if ( fabs(eta_) > 2.5 ) LOG_FATAL(" eta is out of range!!!");
            if      ( hadFlav_ == HADRONFLAV_L )
                systVars[ systVarIdx(iAlgo,iSyst) ] = calibReaderPTRs[iAlgo]->eval_auto_bounds( _usedSystTypes[algorithm][iSyst], BTagEntry::FLAV_UDSG,eta_,pt_, bDis);
            else if ( hadFlav_ == HADRONFLAV_C )
            {
                systVars[ systVarIdx(iAlgo,iSyst) ] = calibReaderPTRs[iAlgo]->eval_auto_bounds( _usedSystTypes[algorithm][iSyst], BTagEntry::FLAV_C   ,eta_,pt_, bDis);
                LOG_INFO(" C flavor gets weight : %.4f", systVars[ systVarIdx(iAlgo,iSyst) ] );
            }
            else if ( hadFlav_ == HADRONFLAV_B )
                systVars[ systVarIdx(iAlgo,iSyst) ] = calibReaderPTRs[iAlgo]->eval_auto_bounds( _usedSystTypes[algorithm][iSyst], BTagEntry::FLAV_B   ,eta_,pt_, bDis);
            else
                LOG_WARNING( "none of known hadron flavour input. Give a -999 for check" );

        }
    }
}



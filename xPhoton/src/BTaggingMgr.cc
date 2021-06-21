#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include <map>
#include <string>


namespace t
{
    // use std::string due to a equal sign is needed. first : algorithm, second : systType
    std::map<std::string, std::vector<const char*> > systTypeCollection;
    void SetContent(){
        if ( systTypeCollection.size() != 0 )  return;

    systTypeCollection["hi"] = {"jjj"};
systTypeCollection["CSVv2"] = {
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
"up_lfstats2" };
systTypeCollection["DeepCSV"] = {
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
"up_lfstats2" };
systTypeCollection["DeepFlavour"] = {
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
"up_lfstats2" };
systTypeCollection["DeepFlavour_JESReduced"] = {
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
};
}
};
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
    _systTypeRegisted=true;
    for ( auto usedAlgorithm : _usedAlgorithmNames )
        _usedSystTypes[usedAlgorithm] = t::systTypeCollection[usedAlgorithm];
    calibs.reserve(_usedSystTypes.size());
    for ( auto usedAlgorithm : _usedAlgorithmNames )
    { calibs.emplace_back( usedAlgorithm, ExternalFilesMgr::csvFile_BTagCalibs(usedAlgorithm) ); }
}

#include "xPhoton/xPhoton/interface/CTaggingMgr.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
#include <string>
CTagWeightHelper::CTagWeightHelper( const char* ifile ) : wtFile(nullptr)
{
    if ( ifile == nullptr ) return;
    wtFile = TFile::Open(ifile);
    cWtHist = (TH2F*)wtFile->Get("SFc_hist");   //For systematic variations, one can concatenate a string after "SFc_hist"
    bWtHist = (TH2F*)wtFile->Get("SFb_hist");
    lWtHist = (TH2F*)wtFile->Get("SFl_hist");
}
CTagWeightHelper::~CTagWeightHelper() { wtFile->Close(); wtFile = nullptr; }
TH2F* CTagWeightHelper::GetFlavourHist(int flav)
{
    if (flav == 4) return cWtHist;
    if (flav == 5) return bWtHist;
    return lWtHist;
}
float CTagWeightHelper::GetWeight(int flav,
        float CvsBval,
        float CvsLval
        )
{
    if ( wtFile == nullptr ) return -404;
    TH2* wtHist = GetFlavourHist(flav);
    int xbin = wtHist->GetXaxis()->FindBin(CvsLval);
    int ybin = wtHist->GetYaxis()->FindBin(CvsBval);
    //ctagWt *= wtHist->GetBinContent(xbin,ybin); // asdf If 2 jets are selected in one event, do I need to multiplied them?
    return wtHist->GetBinContent(xbin,ybin);
}






CTaggingMgr::CTaggingMgr(const char* dataera, const char* algoType) : _algoType(algoType)
{ helper = new CTagWeightHelper( ExternalFilesMgr::RooFile_CTagCalibs( std::string(dataera), std::string(algoType)) ); }

void CTaggingMgr::RegBranch(TTree* t)
{
    t->Branch( Form("%s.CvsB",_algoType), &cvsb, Form("%s.CvsB/F",_algoType) );
    t->Branch( Form("%s.CvsL",_algoType), &cvsl, Form("%s.CvsL/F",_algoType) );
    t->Branch( Form("%s.ctagWeight.central",_algoType), &weight_central, Form("%s.ctagWeight.central/F",_algoType) );
}

void CTaggingMgr::calculation(int flav, float bval, float cval, float lval, double normalization)
{
    InitVars();

    // algorithm according to https://twiki.cern.ch/twiki/bin/viewauth/CMS/CTaggerShapeCalibration?fbclid=IwAR1_BlK2OeoMwvU_w7niCAZrC2swm8OT23bOGXK_mq-ngF_C_7JAEot6EL0
    if ( (cval < 0) || ((cval+lval) == 0) || ((cval+bval) == 0 ) ) return;
    cvsb = cval/(cval+bval);
    cvsl = cval/(cval+lval);
    if ( normalization == NOTHING )
        weight_central = helper->GetWeight(flav, cvsb, cvsl);
    else
        weight_central = helper->GetWeight(flav, cvsb, cvsl) * normalization;
}

void CTaggingMgr::InitVars()
{
    cvsb = -1;
    cvsl = -1;
    weight_central = -404;
}








CTaggingMgr_DeepFlavour::CTaggingMgr_DeepFlavour(const char* dataera) : CTaggingMgr(dataera, "DeepFlavour") {}
void CTaggingMgr_DeepFlavour::SetBranchAddress(TTree* t)
{
    t->SetBranchAddress("jetDeepFlavourTags_b"  , &_bval);
    t->SetBranchAddress("jetDeepFlavourTags_c"  , &_cval);
    t->SetBranchAddress("jetDeepFlavourTags_uds", &_qval);
    t->SetBranchAddress("jetDeepFlavourTags_g"  , &_gval);
    t->SetBranchAddress("jetHadFlvr", &_hadflvr);
}
void CTaggingMgr_DeepFlavour::FillBranch(double normalization)
{
    this->calculation(_hadflvr, _bval, _cval, _qval+_gval, normalization);
}





CTaggingMgr_DeepCSV::CTaggingMgr_DeepCSV(const char* dataera) : CTaggingMgr(dataera, "DeepCSV") {}
void CTaggingMgr_DeepCSV::SetBranchAddress(TTree* t)
{
    t->SetBranchAddress("jetDeepCSVTags_b", &_bval);
    t->SetBranchAddress("jetDeepCSVTags_c", &_cval);
    t->SetBranchAddress("jetDeepCSVTags_udsg", &_lval);
    t->SetBranchAddress("jetHadFlvr", &_hadflvr);
}
void CTaggingMgr_DeepCSV::FillBranch(double normalization)
{
    this->calculation(_hadflvr, _bval, _cval, _lval, normalization);
}

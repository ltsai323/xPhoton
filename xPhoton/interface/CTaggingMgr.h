#ifndef __CTaggingMgr_h__
#define __CTaggingMgr_h__
#include <map>
#include <string>
#include <vector>
#include "xPhoton/xPhoton/interface/BTagCalibrationStandalone.h"
#include <memory>
#include <map>
#include <TTree.h>
#include "TFile.h"
#include "TH2F.h"


#define MAXNSYST 100
#define HADRONFLAV_B 5
#define HADRONFLAV_C 4
#define HADRONFLAV_L 0

#define NOTHING -99



struct CTagWeightHelper
{
    CTagWeightHelper( const char* ifile ); // : wtFile(nullptr)
    //{
    //    if ( ifile == nullptr ) return;
    //    wtFile = TFile::Open(ifile);
    //    cWtHist = (TH2F*)wtFile->Get("SFc_hist");   //For systematic variations, one can concatenate a string after "SFc_hist"
    //    bWtHist = (TH2F*)wtFile->Get("SFb_hist");
    //    lWtHist = (TH2F*)wtFile->Get("SFl_hist");
    //}
    ~CTagWeightHelper(); // { wtFile->Close(); wtFile = nullptr; }
    TH2F* GetFlavourHist(int flav);
    // {
    //     if (flav == 4) return cWtHist;
    //     if (flav == 5) return bWtHist;
    //     return lWtHist;
    // }
    float GetWeight(int flav,
            float CvsBval,
            float CvsLval
            );
    //{
    //    if ( wtFile == nullptr ) return -404;
    //    TH2* wtHist = GetFlavourHist(flav);
    //    int xbin = wtHist->GetXaxis()->FindBin(CvsLval);
    //    int ybin = wtHist->GetYaxis()->FindBin(CvsBval);
    //    //ctagWt *= wtHist->GetBinContent(xbin,ybin); // asdf If 2 jets are selected in one event, do I need to multiplied them?
    //    return wtHist->GetBinContent(xbin,ybin);
    //}



    TFile* wtFile;
    TH2F *cWtHist;
    TH2F *bWtHist;
    TH2F *lWtHist;
};

class CTaggingMgr
{
public:
    CTaggingMgr(const char* dataera, const char* algoType); // : _algoType(algoType)
    //{ helper = new CTagWeightHelper( ExternalFilesMgr::RooFile_CTagCalibs(dataera,algoType) ); }

    virtual void RegBranch(TTree* t) final;
    //{
    //    char bname[200], bnameF[200];

    //    t->Branch( Form("%s.CvsB",_algoType.c_str()), cvsb, Form("%s.CvsB/F",_algoType.c_str()) );
    //    t->Branch( Form("%s.CvsL",_algoType.c_str()), cvsl, Form("%s.CvsL/F",_algoType.c_str()) );
    //    t->Branch( Form("%s.ctagWeight.central",_algoType.c_str()), weight_central, Form("%s.ctagWeight.central/F",_algoType.c_str()) );
    //}
    virtual void FillBranch(double normalization = NOTHING) = 0;
    virtual void SetBranchAddress(TTree* t) = 0;
    virtual float GetWeight() { return weight_central; }
    //void DisableBranch(TTree* t); // if the input file is btagging calculated, you can use this function to clear previous result.

    virtual void calculation(int flav, float bval, float cval, float lval, double normalization) final;
    //{
    //    InitVars();

    //    // algorithm according to https://twiki.cern.ch/twiki/bin/viewauth/CMS/CTaggerShapeCalibration?fbclid=IwAR1_BlK2OeoMwvU_w7niCAZrC2swm8OT23bOGXK_mq-ngF_C_7JAEot6EL0
    //    if ( (cval < 0) || ((cval+lval) == 0) || ((cval+bval) == 0 ) ) return;
    //    cvsb = cval/(cval+bval);
    //    cvsl = cval/(cval+lval);
    //    weight_central = helper->GetWeight(flav, cvsb, cvsl);
    //}
    
private:
    CTagWeightHelper* helper;
    const char* _algoType;
    float cvsb, cvsl, weight_central;

    void InitVars();
    //{
    //    cvsb = -1;
    //    cvsl = -1;
    //    weight_central = -404;
    //}
};
class CTaggingMgr_DeepFlavour : public CTaggingMgr
{
    public:
    CTaggingMgr_DeepFlavour(const char* dataera); // : CTaggingMgr(dataera, "DeepFlavour") {}
    virtual void SetBranchAddress(TTree* t) override;
    //{
    //    t->SetBranchAddress("jetDeepFlavourTags_b"  , &_bval);
    //    t->SetBranchAddress("jetDeepFlavourTags_c"  , &_cval);
    //    t->SetBranchAddress("jetDeepFlavourTags_uds", &_qval);
    //    t->SetBranchAddress("jetDeepFlavourTags_g"  , &_gval);
    //    t->SetBranchAddress("jetHadFlvr", &_hadflvr);
    //}
    virtual void FillBranch(double normalization = NOTHING) override;
    //{
    //    this->calculation(_hadflvr, _bval, _cval, _qval+gval);
    //}
    private:
    float _bval, _cval, _qval, _gval;
    int _hadflvr;
};
class CTaggingMgr_DeepCSV : public CTaggingMgr
{
    public:
    CTaggingMgr_DeepCSV(const char* dataera); // : CTaggingMgr(dataera, "DeepCSV") {}
    virtual void SetBranchAddress(TTree* t) override;
    //{
    //    t->SetBranchAddress("jetDeepCSVTags_b", &_bval);
    //    t->SetBranchAddress("jetDeepCSVTags_c", &_cval);
    //    t->SetBranchAddress("jetDeepCSVTags_udsg", &_lval);
    //    t->SetBranchAddress("jetHadFlvr", &_hadflvr);
    //}
    virtual void FillBranch(double normalization = NOTHING) override;
    //{
    //    this->calculation(_hadflvr, _bval, _cval, _lval);
    //}
    private:
    float _bval, _cval, _lval;
    int _hadflvr;
};

#endif


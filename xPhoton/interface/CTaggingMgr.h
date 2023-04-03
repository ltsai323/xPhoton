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


struct FlavourTH2
{
    TH2F* b;
    TH2F* c;
    TH2F* l;

    TH2F* GetFlavourHist(int flav)
    {
        if (flav == 4) return c;
        if (flav == 5) return b;
        return l;
    }
};

struct CTagWeightHelper
{
    CTagWeightHelper( const char* ifile );
    ~CTagWeightHelper();

    double gethistcontent( FlavourTH2& hists, int flav, float CvsBval, float CvsLval )
    {
        TH2* wtHist = hists.GetFlavourHist(flav);
        int xbin = wtHist->GetXaxis()->FindBin(CvsLval);
        int ybin = wtHist->GetYaxis()->FindBin(CvsBval);
        return wtHist->GetBinContent(xbin,ybin);
    }

    double GetWeight(int flav, float CvsBval, float CvsLval)
    { return gethistcontent(h_central , flav, CvsBval, CvsLval); }
    double GetWeightErrUp(int flav, const std::string& uncNAME, float CvsBval, float CvsLval)
    { return gethistcontent(h_UncUp[uncNAME], flav, CvsBval, CvsLval); }
    double GetWeightErrDown(int flav, const std::string& uncNAME, float CvsBval, float CvsLval)
    { return gethistcontent(h_UncDn[uncNAME], flav, CvsBval, CvsLval); }



    TFile* wtFile;

    FlavourTH2 h_central;
    std::map<std::string, FlavourTH2> h_UncUp;
    std::map<std::string, FlavourTH2> h_UncDn;

    
};

class CTaggingMgr
{
public:
    CTaggingMgr(const char* dataera, const char* algoType, bool isMC = true); // : _algoType(algoType)

    virtual void RegBranch(TTree* t) final;
    virtual void FillBranch() = 0;
    virtual void SetBranchAddress(TTree* t) = 0;
    virtual float GetWeight() { return weight_central; }

    virtual void calculation(int flav, float bval, float cval, float lval) final;
    
    virtual ~CTaggingMgr() {}

    bool IsMC() const { return _isMC; }
private:
    CTagWeightHelper* helper;
    const char* _algoType;
    float cvsb, cvsl, bscore;
    float weight_central;

    //float weight_ExtrapUp             ;
    //float weight_InterpUp             ;
    //float weight_LHEScaleWeight_muFUp ;
    //float weight_LHEScaleWeight_muRUp ;
    //float weight_PSWeightFSRFixedUp   ;
    //float weight_PSWeightISRFixedUp   ;
    float weight_PUWeightUp           ;
    float weight_StatUp               ;
    float weight_TotalUncUp           ;
    //float weight_XSec_BRUnc_DYJets_bUp;
    //float weight_XSec_BRUnc_DYJets_cUp;
    //float weight_XSec_BRunc_WJets_cUp ;
    //float weight_jerUp                ;
    //float weight_jesTotalUp           ;

    //float weight_ExtrapDown             ;
    //float weight_InterpDown             ;
    //float weight_LHEScaleWeight_muFDown ;
    //float weight_LHEScaleWeight_muRDown ;
    //float weight_PSWeightFSRFixedDown   ;
    //float weight_PSWeightISRFixedDown   ;
    float weight_PUWeightDown           ;
    float weight_StatDown               ;
    float weight_TotalUncDown           ;
    //float weight_XSec_BRUnc_DYJets_bDown;
    //float weight_XSec_BRUnc_DYJets_cDown;
    //float weight_XSec_BRunc_WJets_cDown ;
    //float weight_jerDown                ;
    //float weight_jesTotalDown           ;

    void InitVars();
    bool _isMC;
};
class CTaggingMgr_DeepFlavour : public CTaggingMgr
{
    public:
    CTaggingMgr_DeepFlavour(const char* dataera, bool isMC); // : CTaggingMgr(dataera, "DeepFlavour") {}
    virtual void SetBranchAddress(TTree* t) override;
    virtual void FillBranch() override;
    virtual ~CTaggingMgr_DeepFlavour() {}
    private:
    float _bval, _bbval, _cval, _qval, _gval;
    int _hadflvr;
};
class CTaggingMgr_DeepCSV : public CTaggingMgr
{
    public:
    CTaggingMgr_DeepCSV(const char* dataera, bool isMC); // : CTaggingMgr(dataera, "DeepCSV") {}
    virtual void SetBranchAddress(TTree* t) override;
    virtual void FillBranch() override;
    virtual ~CTaggingMgr_DeepCSV() {}
    private:
    float _bval, _bbval, _cval, _lval;
    int _hadflvr;
};

#endif


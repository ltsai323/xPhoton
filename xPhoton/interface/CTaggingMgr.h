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
    //TH2F* GetFlavourHist(int flav);

    double gethistcontent( FlavourTH2& hists, int flav, float CvsBval, float CvsLval )
    {
        TH2* wtHist = hists.GetFlavourHist(flav);
        int xbin = wtHist->GetXaxis()->FindBin(CvsLval);
        int ybin = wtHist->GetYaxis()->FindBin(CvsBval);
        return wtHist->GetBinContent(xbin,ybin);
    }

    double GetWeight(int flav, float CvsBval, float CvsLval)
    { return gethistcontent(h_central , flav, CvsBval, CvsLval); }
    double GetWeightErrUp(int flav, float CvsBval, float CvsLval)
    { return gethistcontent(h_TotUncUp, flav, CvsBval, CvsLval); }
    double GetWeightErrDown(int flav, float CvsBval, float CvsLval)
    { return gethistcontent(h_TotUncDn, flav, CvsBval, CvsLval); }



    TFile* wtFile;
    FlavourTH2 h_central;
    FlavourTH2 h_TotUncUp;
    FlavourTH2 h_TotUncDn;

    
};

class CTaggingMgr
{
public:
    CTaggingMgr(const char* dataera, const char* algoType); // : _algoType(algoType)

    virtual void RegBranch(TTree* t) final;
    virtual void FillBranch() = 0;
    virtual void SetBranchAddress(TTree* t) = 0;
    virtual float GetWeight() { return weight_central; }

    virtual void calculation(int flav, float bval, float cval, float lval) final;
    
    virtual ~CTaggingMgr() {}
private:
    CTagWeightHelper* helper;
    const char* _algoType;
    float cvsb, cvsl, bscore;
    float weight_central,weight_totUp, weight_totDn;

    void InitVars();
};
class CTaggingMgr_DeepFlavour : public CTaggingMgr
{
    public:
    CTaggingMgr_DeepFlavour(const char* dataera); // : CTaggingMgr(dataera, "DeepFlavour") {}
    virtual void SetBranchAddress(TTree* t) override;
    virtual void FillBranch() override;
    virtual ~CTaggingMgr_DeepFlavour() {}
    private:
    float _bval, _cval, _qval, _gval;
    int _hadflvr;
};
class CTaggingMgr_DeepCSV : public CTaggingMgr
{
    public:
    CTaggingMgr_DeepCSV(const char* dataera); // : CTaggingMgr(dataera, "DeepCSV") {}
    virtual void SetBranchAddress(TTree* t) override;
    virtual void FillBranch() override;
    virtual ~CTaggingMgr_DeepCSV() {}
    private:
    float _bval, _cval, _lval;
    int _hadflvr;
};

#endif


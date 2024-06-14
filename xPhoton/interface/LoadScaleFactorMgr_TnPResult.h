#ifndef __LOADSCALEFACTORMGR_TNPRESULT_H__
#define __LOADSCALEFACTORMGR_TNPRESULT_H__
#include "TH2F.h"
#include "TFile.h"

class LoadScaleFactorMgr
{
public:
    LoadScaleFactorMgr(TFile* inFILE, TH2F* inHIST) :
        in_file(inFILE), in_hist(inHIST) {}
    ~LoadScaleFactorMgr() { if (in_file) in_file->Close(); }


    double ScaleFactor(float phoPT, float phoETA);
    double TotalUncertainties(float phoPT, float phoETA);
private:
    TFile* in_file;
    TH2F*  in_hist;
};

LoadScaleFactorMgr LoadScaleFactorMgr_TnPResult(const char* inputROOTsfRESULT, bool isMC);
#endif

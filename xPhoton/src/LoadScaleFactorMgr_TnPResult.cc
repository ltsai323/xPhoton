#include "xPhoton/xPhoton/interface/LoadScaleFactorMgr_TnPResult.h"


double LoadScaleFactorMgr::ScaleFactor(float phoPT, float phoETA)
{
    if ( in_hist == nullptr )
        return 0;

    int xbin = in_hist->GetXaxis()->FindBin(phoETA);
    int ybin = in_hist->GetYaxis()->FindBin(phoPT );
    return in_hist->GetBinContent(xbin,ybin);
}
double LoadScaleFactorMgr::TotalUncertainties(float phoPT, float phoETA)
{
    if ( in_hist == nullptr )
        return 0;

    int xbin = in_hist->GetXaxis()->FindBin(phoETA);
    int ybin = in_hist->GetYaxis()->FindBin(phoPT );
    return in_hist->GetBinError(xbin,ybin);
}



LoadScaleFactorMgr LoadScaleFactorMgr_TnPResult(const char* inputROOTsfRESULT, bool isMC)
{
    if (!isMC)
        return LoadScaleFactorMgr(nullptr, nullptr); // data: not to get scale factor

    auto infile = TFile::Open(inputROOTsfRESULT);
    auto inhist = (TH2F*) infile->Get("TnP_ScaleFactor");
    return LoadScaleFactorMgr(infile,inhist);
}

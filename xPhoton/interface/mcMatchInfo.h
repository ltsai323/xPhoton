#ifndef __MCMATCHINFO_H__
#define __MCMATCHINFO_H__
#include <vector>
#include "TTree.h"
#include "xPhoton/xPhoton/interface/readMgr.h"
#include "xPhoton/xPhoton/interface/histMgr.h"

class mcMatchInfo
{
    histMgr* importedHists;
public:
    explicit mcMatchInfo(histMgr* ptr);
    struct truthVal
    {
        std::vector<float> pt;
        std::vector<float> eta;
        std::vector<float> phi;
        std::vector<float> calIso04;
        std::vector<float> trkIso04;
        std::vector<int> isMatched;
        std::vector<int> isMatchedEle;
        std::vector<int> isConverted;
        void Clean()
        {
            pt.clear();
            eta.clear();
            phi.clear();
            calIso04.clear();
            trkIso04.clear();
            isMatched.clear();
            isMatchedEle.clear();
            isConverted.clear();
        };
        bool matched()
        { return pt.size()>0; }
        truthVal() { Clean(); }
    };
    Double_t deltaPhi(Double_t phi1, Double_t phi2);
    Double_t deltaR(Double_t eta1, Double_t phi1, Double_t eta2, Double_t phi2);
    truthVal findtruthPhoton(readMgr* evtInfo);
};
#endif


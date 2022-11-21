//#define DEBUGMODE
#ifdef DEBUGMODE
#define BUG( args...) fprintf(stderr, "---------------------debug-    %s  \n  >>  checkpoint %03d\n", __PRETTY_FUNCTION__,  ##args)
#else
#define BUG( args...)
#endif
#define LOG(format, args...) fprintf(stderr, "[Info] %s >> " format "\n", __PRETTY_FUNCTION__,  ##args)

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <list>

#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TH1F.h"
#include "TNtuple.h"
#include "TCanvas.h"

const char* OUTPUT_TEMPLATE = "xQCD3rd_ScaleFactorCalculationAndJetPtThreshold_cc_%s.root";
void PrintHelp()
{
    std::string errMesg;
    errMesg += "=====================================================\n";
    errMesg += "======================= Usage =======================\n";
    errMesg += "=== arg1: input file root file.                   ===\n";
    errMesg += "=== arg2: input left gen HT slice.                ===\n";
    errMesg += "=====================================================\n";
    errMesg += "=====================================================\n";
    throw errMesg;
}
const char*  GetArg_InputFile(int argc, const char* argv[])
{ if ( argc < 1+1 ) PrintHelp(); return argv[1]; }
int  GetArg_GenHTLow(int argc, const char* argv[])
{ if ( argc < 2+1 ) PrintHelp(); return std::stoi(argv[2]); }


class InputInfo
{
    public:
    InputInfo(const char* inFILE, int leftEDGE):
        _file0( TFile::Open(inFILE) ),
        ntuple( (TNtuple*) _file0->Get("nt") ),
        lEdge(leftEDGE), rEdge( right_edge() ) { }
    void CloseFile() { _file0->Close(); }
    const char* OutputFileName() const;
    void ReName(TH1*) const;

    TFile* _file0; TTree* ntuple;
    int lEdge; int rEdge;
private:
    int right_edge();
};

TH1F* WeightCalculation(TH1* hcut, TH1* hall, const char* histname);
TH1* HistFactory_AllSample(const InputInfo&);
TH1* HistFactory_Selection(const InputInfo& inputINFO, float ptcut);

bool LowStatEntryRemoval( int leftHT, int ibin );

struct HistCategory_JetPt : public TH1F
{ HistCategory_JetPt( const char* histname ); };
float GetThreshold_JetPt(TH1* h);
float Reweight_GenHT(float genHT, TH1* weightHIST);

int main(int argc, const char* argv[] )
{
    const char* infile = GetArg_InputFile(argc,argv);
    int leftHT = GetArg_GenHTLow(argc,argv);

    LOG("Processing GenHT:%4d at file: %s now...",leftHT, infile);
    InputInfo input(infile, leftHT);

    /* examples
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT50to100.root", 50);
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT100to200.root", 100);
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT200to300.root", 200);
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT300to500.root", 300);
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT500to700.root", 500);
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT700to1000.root", 700);
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT1000to1500.root", 1000);
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT1500to2000.root", 1500);
    InputInfo input("xphoton2nd_QCDReweightChecking_Madgraph_CC_QCD_HT2000toInf.root", 2000);
    */

    auto newfile = new TFile(input.OutputFileName(),"RECREATE");

    TH1* jetpt = new HistCategory_JetPt("jetpt_threshold");
    for ( int ibin = jetpt->GetNbinsX()+1; ibin != 0; --ibin )
        if ( LowStatEntryRemoval(leftHT,ibin) )  jetpt->SetBinContent(ibin, 0);
        else                                     jetpt->SetBinContent(ibin, 1);
    float ptThreshold = GetThreshold_JetPt(jetpt);


    TH1* h_all = HistFactory_AllSample( input );
    TH1* h_sel = HistFactory_Selection( input, ptThreshold );

    TH1* weight = WeightCalculation(h_sel,h_all, "genHT_reweight");

    jetpt->SetDirectory(newfile); jetpt->Write();
    weight->SetDirectory(newfile); weight->Write();
    
    delete h_all; delete h_sel;
    newfile->Close();
}








//////////////////////// function implements ////////////////////////



//////////////////////// class func implement////////////////////////
#define INF_VALUE 5000
static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000});
const char* InputInfo::OutputFileName() const
{
    const char* lTag = Form("%04d", lEdge);
    const char* rTag = rEdge != INF_VALUE ? Form("%04d", rEdge) : "Inf";
    return Form( OUTPUT_TEMPLATE, Form("%sTo%s",lTag,rTag) );
}
void InputInfo::ReName(TH1* hOUT) const
{ hOUT->SetName( Form("%s_%04d",hOUT->GetName(), lEdge) ); }

int InputInfo::right_edge()
{
    for ( auto i = genHTBin.size(); i!= 0; --i )
    {
        auto idx = i-1;
        if ( int(genHTBin[idx]) == lEdge )
        {
            if ( idx == genHTBin.size()-1 ) return INF_VALUE;
            return genHTBin[idx+1];
        }
    }
    return -1;
}

//////////////////////// class func implement////////////////////////

////////////////////////////////
// WeightCalculation function //
////////////////////////////////

TH1F* WeightCalculation(TH1* hcut, TH1* hall, const char* histname)
{
    TH1F* hout = (TH1F*) hcut->Clone();
    hout->SetName(histname);

    // overflow bin is meanful.
    for ( int ibin = 0; ibin <= hcut->GetNbinsX(); ++ibin )
    {
        float weight_up = hall->GetBinContent(ibin+1);
        float weight_dn = hcut->GetBinContent(ibin+1);
        const float zero_value = 1e-5;
        if ( fabs(weight_up) < zero_value && fabs(weight_dn) < zero_value )
            hout->SetBinContent(ibin+1, 1.);
        else if ( fabs(weight_dn) < zero_value )
            hout->SetBinContent(ibin+1, -999.);
        else
            hout->SetBinContent(ibin+1, weight_up / weight_dn);
    }
    hout->SetDirectory(0);
    return hout;
}


///////////////////////////////
// hist_factory_series function
///////////////////////////////

TH1* hist_factory(const InputInfo& inputINFO, std::pair<const char*,const char*> selection_pair )
{
    //auto selection_pair = cut_func();
    const char* name = selection_pair.first;
    const char* cuts = selection_pair.second;

    TH1* hist = new TH1F( name, "", 10, inputINFO.lEdge, inputINFO.rEdge );
    inputINFO.ntuple->Draw( Form("genHT>>%s",name), cuts );
    return hist;
}

TH1* HistFactory_AllSample(const InputInfo& inputINFO)
{ return hist_factory(inputINFO, std::make_pair("all", "jetPt>0")); }
TH1* HistFactory_Selection(const InputInfo& inputINFO, float ptcut)
{ return hist_factory(inputINFO, std::make_pair("sel", Form("jetPt>0 && genHT/nLHE > maxPUhat && maxPUhat>0 && jetPt<%f",ptcut))); }

///////////////////////////
// Reweighting functions //
///////////////////////////

#define NOTHINGFOUND -1
float Reweight_GenHT(float genHT, TH1* weightHIST)
{
    // from bin1 to overflow bin
    for ( int ibin = weightHIST->GetNbinsX()+1; ibin != 0; --ibin )
    {
        if ( genHT > weightHIST->GetBinLowEdge(ibin) )
            return weightHIST->GetBinContent(ibin);
    }
    return NOTHINGFOUND;
}

float GetThreshold_JetPt(TH1* h)
{
    for ( auto ibin = h->GetNbinsX()+1; ibin != 0; --ibin )
        // 1 or 0. If 1 found, pass threshold at high edge.
        if ( h->GetBinContent(ibin) == 1 ) return h->GetBinLowEdge(ibin+1);
    return NOTHINGFOUND;
}

////////////////////////////
// Low statistics removal //
////////////////////////////

/* copied from ../qcdCHECKER_plotMCWeightComposition.C */
const int NMCSEP = 9; // QCD madgraph samples are separated into 9 HT slices.
int mc_index( int leftHT )
{
    if ( leftHT ==  50)     return 0;
    if ( leftHT ==  100)    return 1;
    if ( leftHT ==  200)    return 2;
    if ( leftHT ==  300)    return 3;
    if ( leftHT ==  500)    return 4;
    if ( leftHT ==  700)    return 5;
    if ( leftHT ==  1000)   return 6;
    if ( leftHT ==  1500)   return 7;
    if ( leftHT ==  2000)   return 8;
    throw Form("mc_index() :: Wrong input gen HT value (%d)\n",leftHT);
}

int jetptBin_100CUT[NMCSEP] = {7,16,16,18,20,21,22,23,24};
int jetptBin_10CUT[NMCSEP] = {11,20,20,21,22,23,24,24,24};
int jetptBin_tenToMinusFiveCut[NMCSEP] = {10,10,15,17,20,20,22,23,24};
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
bool LowStatEntryRemoval( int leftHT, int ibin )
{
    int iMC = mc_index(leftHT);
    if ( ibin >= jetptBin_tenToMinusFiveCut[iMC] ) return true;
    return false;
}

//////////////////////////////////////////
// Implementation to HistCategory_JetPt //
//////////////////////////////////////////

HistCategory_JetPt::HistCategory_JetPt( const char* histname ) : TH1F(histname,"", jetptBin.size()-1, &(jetptBin.front())) {}

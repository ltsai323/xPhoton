//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Nov 16 15:02:11 2021 by ROOT version 6.10/09
// from TTree t/mini tree
// found on file: /home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root
//////////////////////////////////////////////////////////
#define EvtSelMgr_cxx
#define EventBinning_cxx
#define usefulfunctions_cxx

#ifndef makehisto_h
#define makehisto_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <iostream>
#include "ptbin_definitions.h"

#define LOG(format, args...)     fprintf(stderr, "[LOG]  %s  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)
#define BUG(format, args...)     fprintf(stderr, "[BUG]  %s  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)
#define NOTHING -999
#define ZERO_VAL 1e-8

#define NUMBIN_PHOETA 2
#define NUMBIN_JETETA 3
#define NUMBIT_HLT 9 // 0~8
#define NUMBIN_ISOVAR 4
#define NUMBIN_MATCHEDPHOTONSTATUS 5
#define NUMBIN_JETFLVR 3
#define NUM_BTAGVAR 4
#define NUM_PARITY 2

// Header file for the classes stored in the TTree if any.


enum JetFlavour
{ L=0, C=4, B=5 };

struct EventBinning
{
    EventBinning(int pETAbin, int jETAbin, int pPTbin) : pEtaBin(pETAbin),jEtaBin(jETAbin),pPtBin(pPTbin) {}
    EventBinning(float pPt, float pEta, float jPt, float jY, float isovar) :
        pEtaBin( IsEndcap(pEta) ),jEtaBin( JetEtaBin(jPt,jY) ),pPtBin( PtBin(pPt) ),
        isSignalRegion(phosignalregion(isovar)), isDataSideband(phodatasideband(isovar)) {}
    int pEtaBin,jEtaBin,pPtBin;
    int isSignalRegion, isDataSideband;

    int IsEndcap(float eta) const { if (TMath::Abs(eta)<1.5) return 0; return 1; }
    int PtBin(float pt) const;
    int JetEtaBin(float pt, float Y) const;
    int phosignalregion(float isovar) const;
    int phodatasideband(float isovar) const;
};
struct normalization_ctagreshaped
{
    normalization_ctagreshaped():
        entries(0),central(0),puweight_up(0),puweight_down(0),stat_up(0),stat_down(0)
    {}
    void Add(
        double central_, double puweight_up_, double puweight_down_, double stat_up_, double stat_down_
        )
    {
        ++entries;
        central+=central_;
        puweight_up+=puweight_up_;
        puweight_down+=puweight_down_;
        stat_up+=stat_up_;
        stat_down+=stat_down_;
    }

    int entries;
    double central;
    double puweight_up;
    double puweight_down;
    double stat_up;
    double stat_down;
};

struct Normalization_CTagReshaped
{ // the magic 30 number must be larger than NUMBIN_PHOPT
    Normalization_CTagReshaped() { }
    normalization_ctagreshaped binned_norm[NUMBIN_PHOETA][NUMBIN_JETETA][30];
};
struct EvtSelMgr
{
    EvtSelMgr(bool ismc, bool isqcd, bool hltoption) : isMC(ismc), isQCD(isqcd), HLTOPTION(hltoption)
    {}
    const bool isMC, isQCD;
    const bool HLTOPTION;
    int jethadflvr;
    void SetUsedVar_4(int jetHADflvr ) { jethadflvr = jetHADflvr; }
    bool isBJet() const { return jethadflvr == JetFlavour::B; }
    bool isCJet() const { return jethadflvr == JetFlavour::C; }
    bool isLJet() const { return jethadflvr == JetFlavour::L; }

    // match stat
    float chIso;
    float phoEta;
    float isMatched;
    void SetUsedVar_3( float chISO, float phoETA, float isMATCHED )
    { chIso = chISO; phoEta = phoETA; isMatched = isMATCHED; }
    int PhoMatchedStatus() const { return 1; } // asdf implement needed

    float jetPt;
    float jetEta;
    float cScore;
    int jetID;
    int jetPUIDbit;
    float jetSubVtxMass;
    float CvsL;
    int passMaxPUcut;
    void SetUsedVar_2( float jetPT, float jetETA, float cSCORE, int jetID_, int jetPUidBIT, float jetSUBvtxMASS, float CvsL_, int passMAXpuCUT )
    { jetPt = jetPT; jetEta = jetETA; cScore = cSCORE; jetID = jetID_; jetPUIDbit = jetPUidBIT; jetSubVtxMass = jetSUBvtxMASS; CvsL = CvsL_; passMaxPUcut = passMAXpuCUT; }
    bool PassJetAdditionalSelection(int cutIndicator) const;

    float recoSCEta;
    float sieieFull5x5;
    float HoverE;
    void SetUsedVar_1( float recoSCeta, float sieieFULL5x5, float hOVERe )
    { recoSCEta = recoSCeta; sieieFull5x5 = sieieFULL5x5; HoverE = hOVERe; }
    bool InFiducialRegion() const;

    float MET;
    float phoPt;
    int eleVeto;
    int phoFilledIdx;
    void SetUsedVar_0( float mET, float phoPT, int eleVETO, int phoFILLEDidx )
    { MET = mET; phoPt = phoPT; eleVeto = eleVETO; phoFilledIdx = phoFILLEDidx; }
    bool PassPhotonPreSelection(int ptbin) const;

    Long64_t phoFiredTrgs;
    void SetUsedVar__( Long64_t phoFIREDtrgs ) { phoFiredTrgs = phoFIREDtrgs; }
    bool PassHLT(int hltbit) const { if ( HLTOPTION==1 && !((phoFiredTrgs>>hltbit)&1) ) return false; return true; }

    private:
    EvtSelMgr() : isMC(false),isQCD(false),HLTOPTION(false) {}
};
struct Hists
{ // the magic 30 number must be larger than NUMBIN_PHOPT
    Hists(const char* naME, const char* varname, int nbin, float xmin, float xmax) : name(naME)
    {
        int idx=0;
        char histname[400];
        for ( int pEtaIdx = 0; pEtaIdx < NUMBIN_PHOETA; ++pEtaIdx )
            for ( int jEtaIdx = 0; jEtaIdx < NUMBIN_JETETA; ++jEtaIdx )
                for ( int pPtIdx = 0; pPtIdx < 30; ++pPtIdx )
                {
                    sprintf(histname, "%s_%04d",naME,idx++); // not to use Form. Unknown reason it failed
                    hists[pEtaIdx][jEtaIdx][pPtIdx] = new TH1F(histname, varname, nbin, xmin, xmax);
                }
    }
    const std::string name;
    TH1F* hists[NUMBIN_PHOETA][NUMBIN_JETETA][30];

    const char* GetName() { return name.c_str(); }
};
Hists* Hists_BDT(const char* histname, const char* varname)
{ return new Hists(histname, varname, 10, -1.,1.); }
Hists* Hists_CTags(const char* histname, const char* varname)
{ return new Hists(histname, varname, 10, 0.,1.); }
Hists* Hists_SubVtxMass(const char* histname, const char* varname)
{ return new Hists(histname, varname, 100, 0.,5.); }

struct Hists_CTagReshaped
{
    Hists_CTagReshaped(const char* naME, const char* varname):
        central     ( Hists_CTags( Form("%s_central"     ,naME), varname) ),
        PUweightUp  ( Hists_CTags( Form("%s_PUweightUp"  ,naME), varname) ),
        PUweightDown( Hists_CTags( Form("%s_PUweightDown",naME), varname) ),
        StatUp      ( Hists_CTags( Form("%s_StatUp"      ,naME), varname) ),
        StatDown    ( Hists_CTags( Form("%s_StatDown"    ,naME), varname) )
    {}
    virtual ~Hists_CTagReshaped() { delete central; delete PUweightUp; delete PUweightDown; delete StatUp; delete StatDown; }
    Hists* central;
    Hists* PUweightUp;
    Hists* PUweightDown;
    Hists* StatUp;
    Hists* StatDown;
};








inline void Fill( const EventBinning& bin,Hists* h, float val, float weight = NOTHING )
{
    if ( weight == NOTHING ) h->hists[bin.pEtaBin][bin.jEtaBin][bin.pPtBin]->Fill(val);
    else                     h->hists[bin.pEtaBin][bin.jEtaBin][bin.pPtBin]->Fill(val, weight);
}
void Fill_allctagreshaped_general( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight,
        float w_central, float w_puweightup, float w_puweightdown, float w_statup, float w_statdown );


inline void Write(const EventBinning& bin, Hists* h, double normalization = NOTHING)
{
    TH1* hh = h->hists[bin.pEtaBin][bin.jEtaBin][bin.pPtBin];
    if ( normalization != NOTHING ) 
        hh->Scale(1./normalization);

    hh->SetName(h->GetName());
    hh->Write();

    // Write PDF
    TH1* hhh = (TH1*) hh->Clone( Form("%s_norm",h->GetName()) );

    double normVal = hhh->GetEntries() > 0 ? 1. / hhh->Integral() : 0.; // check 0
    hhh->Scale( normVal );
    hhh->Write();

}
void Write_AllCTagReshaped_General(const EventBinning& bin, Hists_CTagReshaped* h,
        float norm_central, float norm_puweightup, float norm_puweightdown, float norm_statup, float norm_statdown );
void Write_AllCTagReshaped(const EventBinning& bin, Hists_CTagReshaped* h, const Normalization_CTagReshaped& N);
void WriteShapeUncDown(const EventBinning& bin, Hists* hCENTRAL, Hists* hSHAPEuncUP);

#endif // end of makehisto_h }}}




#ifdef EvtSelMgr_cxx // {{{
bool EvtSelMgr::PassJetAdditionalSelection(int cutIndicator) const
{
    if ( jetPt < 30. ) return false;
    if ( fabs(jetEta) > 2.5 ) return false;
    if ( cScore < -0.99 ) return false;
    if ( isMC && jetID != 1 ) return false;
    if ( isMC && jetPUIDbit != 7 ) return false;

    //if ( mcweight>3000. ) return false;
    if ( cutIndicator == 1 && jetSubVtxMass == 0 ) return false;
    if ( cutIndicator == 2 && CvsL < 0.155) return false;
    


    if ( isMC && isQCD ) if (!passMaxPUcut ) return false;

    return true;
}
bool EvtSelMgr::InFiducialRegion() const
{
    if ( TMath::Abs(recoSCEta)<1.5 && sieieFull5x5 > 0.012 ) return false;
    if ( TMath::Abs(recoSCEta)<1.5 && HoverE       > 0.08  ) return false;
    if ( TMath::Abs(recoSCEta)>1.5 && sieieFull5x5 > 0.027 ) return false;
    if ( TMath::Abs(recoSCEta)>1.5 && HoverE       > 0.05  ) return false;
    return true;
}
bool EvtSelMgr::PassPhotonPreSelection(int ptbin) const
{
    if(TMath::Abs(recoSCEta)>1.4442 && TMath::Abs(recoSCEta)<1.566) return false;
    if(TMath::Abs(recoSCEta)>2.5) return false;
    //if(MET/phoPt > 0.7) return false; // disabled for 2016. This effect not longer seen. And this cut cut out of lot events
    if ( eleVeto == 0 ) return false;
    if ( ptbin<0 ) return false;

    if ( phoFilledIdx != 0 ) return false; // only keep leading photon
    return true;
}
#endif // end of  EvtSelMgr_cxx }}}
#ifdef EventBinning_cxx // {{{
int EventBinning::PtBin(float pt) const
{
    std::vector<float> ptcut = ptbin_ranges();
    int ibin = ptcut.size();

    // returned ibin = 0 to size-1
    while ( ibin-- )
    { if ( pt >= ptcut[ibin] ) return ibin; }

    return NOTHING;
}
int EventBinning::JetEtaBin(float pt, float Y) const
{  
    if(pt< 1e-3) return 2;
    if(TMath::Abs(Y)<1.5) return 0;
    return 1;
}
int EventBinning::phosignalregion(float isovar) const
{
    if ( pEtaBin == 0 && fabs(isovar) < 2  ) return 1;
    if ( pEtaBin == 1 && fabs(isovar) < 1.5) return 1;
    return 0;
}
int EventBinning::phodatasideband(float isovar) const
{
    if ( pEtaBin == 0 && fabs(isovar)>7 && fabs(isovar)<13 ) return 1;
    if ( pEtaBin == 1 && fabs(isovar)>6 && fabs(isovar)<12 ) return 1;
    return 0;
}
#endif // end of define EventBinning_cxx }}}
#ifdef usefulfunctions_cxx // {{{









void Fill_allctagreshaped_general( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight,
        float w_central, float w_puweightup, float w_puweightdown, float w_statup, float w_statdown
        )
{
    // all ctag weights needs renormalization. See Write_AllCTagReshaped() for more detail
    Fill(bin,h->central     , val, evt_weight * w_central     );
    Fill(bin,h->PUweightUp  , val, evt_weight * w_puweightup  );
    Fill(bin,h->PUweightDown, val, evt_weight * w_puweightdown);
    Fill(bin,h->StatUp      , val, evt_weight * w_statup      );
    Fill(bin,h->StatDown    , val, evt_weight * w_statdown    );
}


void Write_AllCTagReshaped_General(const EventBinning& bin, Hists_CTagReshaped* h,
        float norm_central, float norm_puweightup, float norm_puweightdown, float norm_statup, float norm_statdown
        )
{
    Write(bin, h->central     , norm_central     );
    Write(bin, h->PUweightUp  , norm_puweightup  );
    Write(bin, h->PUweightDown, norm_puweightdown);
    Write(bin, h->StatUp      , norm_statup      );
    Write(bin, h->StatDown    , norm_statdown    );
}
void Write_AllCTagReshaped(const EventBinning& bin, Hists_CTagReshaped* h, const Normalization_CTagReshaped& N)
{
    // Normalization_CTagReShaped collects the event number and weight integration. Renormalization is done by #evt/integral(weight)
    const normalization_ctagreshaped& n = N.binned_norm[bin.pEtaBin][bin.jEtaBin][bin.pPtBin];
    Write_AllCTagReshaped_General(bin,h , n.central, n.puweight_up, n.puweight_down, n.stat_up, n.stat_down);
}

void WriteShapeUncDown(const EventBinning& bin, Hists* hCENTRAL, Hists* hSHAPEuncUP)
{
    TH1F* h_central    = hCENTRAL   ->hists[bin.pEtaBin][bin.jEtaBin][bin.pPtBin];
    TH1F* h_shapeUncUp = hSHAPEuncUP->hists[bin.pEtaBin][bin.jEtaBin][bin.pPtBin];

    TH1F* h_shapeUncDown = new TH1F( Form("%s_shapeUncDown", h_central->GetName()), h_shapeUncUp->GetTitle(),
                //h_central->GetNbinsX(), h_central->GetXaxis()->GetXbins()->GetArray() );
                h_central->GetNbinsX(), -1., 1.);
    for ( int ibin = h_central->GetNbinsX()+1; ibin != 0; --ibin )
    {
        double bincontent_central =  h_central   ->GetBinContent(ibin);
        double bincontent_uncUp   =  h_shapeUncUp->GetBinContent(ibin);
        double bincontent_uncDown =  2. * bincontent_central - bincontent_uncUp;
        if ( bincontent_central < ZERO_VAL && bincontent_uncUp < ZERO_VAL )
            bincontent_uncDown = ZERO_VAL;
        else if ( bincontent_uncDown < 0. )
        {
            LOG("--WARNING-- negative PDF found at bin%d in %s(%d,%d,%d) calculation. Forced them to 1e-8. central value and upper value : %.6f, %.6f",
                    ibin, h_shapeUncDown->GetName(), bin.pEtaBin, bin.jEtaBin, bin.pPtBin, bincontent_central, bincontent_uncUp);
            bincontent_uncDown = ZERO_VAL;
        }
        h_shapeUncDown->SetBinContent(ibin,bincontent_uncDown);
    }
    h_shapeUncDown->Write();

    // Write PDF
    TH1* hhh = (TH1*) h_shapeUncDown->Clone( Form("%s_norm",h_shapeUncDown->GetName()) );

    double normVal = hhh->GetEntries() > 0 ? 1. / hhh->Integral() : 0.;
    hhh->Scale(normVal);
    hhh->Write();
}
#endif // usefulfunctions_cxx end }}}

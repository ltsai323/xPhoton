#include <iostream>

#define MAXBIT 8

std::vector<float> GetPtRanges() {
    std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
    return vec_ptcut;
}
struct currentBit
{
    currentBit(const char* template0_, const char* template1_) :
        template0(template0_),template1(template1_)
    { }
    void SetBit(int ibit_) { ibit = ibit_;}
    int ibit;
    const char* template0;
    const char* template1;
};

const char* EventSelections()
{ return "chIsoRaw<2&&((phoIDbit>>2)&1) == 1 && photonIDmva > 0.9  && fabs(recoEta) > 1.5 && eleVeto == 1"; }
const char* PassTrg(int ibit)
{ return Form("( ((phoFiredTrgs>>%d)&1) == 1 )", ibit); }
void DrawingTo( TTree* t, const char* var, const char* cut )
{
    t->Draw( Form("recoPt >> %s",var), cut );
    TH1* h = (TH1*) gROOT->FindObject( var );
    h->SetTitle(cut);
}
void ShowTriggerResult(TTree* t, const currentBit& args)
{
    int ibit = args.ibit;
    const char* ll = Form(args.template0, ibit);
    //t->Draw( Form("recoPt >> %s", ll), Form("(phoFiredTrgs>>%d) &1 && %s", ibit, EventSelections()) );
    DrawingTo( t,ll, Form("%s && %s", PassTrg(ibit), EventSelections()) );
    for ( int jbit = ibit+1; jbit <= MAXBIT; ++jbit )
    {
        const char* kk = Form(args.template1, ibit, jbit);
        //t->Draw( Form("recoPt >> %s", kk), Form("(phoFiredTrgs>>%d)&1 && (phoFiredTrgs>>%d)&1 && %s", ibit, jbit, EventSelections()) );
        DrawingTo( t,kk, Form("%s && %s && %s", PassTrg(ibit), PassTrg(jbit), EventSelections()) );
    }
}
void ShowTriggerResult_Loop(TTree* t, const currentBit& args)
{
    int ibit = args.ibit;
    bool isEndcap = true;

    int phoIDbit = 0;
    float recoEta = 0;
    float recoPt = 0;
    int phoFiredTrgs = 0;

    t->SetBranchAddress("recoPt", &recoPt);
    t->SetBranchAddress("phoIDbit", &phoIDbit);
    t->SetBranchAddress("phoFiredTrgs", &phoFiredTrgs);
    t->SetBranchAddress("recoEta", &recoEta);

    TH1* hBase = (TH1*) gROOT->FindObject( Form(args.template0,ibit) );
    std::map<int,TH1*> hNumerator;
    for ( int jbit = ibit+1; jbit <= MAXBIT; ++jbit )
        hNumerator[jbit] = (TH1*) gROOT->FindObject( Form(args.template1,ibit,jbit) );
    
    
    for ( Long64_t ievt = 0; ievt != t->GetEntries(); ++ievt )
    {
        t->GetEntry(ievt);
        if (!isEndcap ) if ( fabs(recoEta) > 1.4442 ) continue; // barrel
        if ( isEndcap ) if ( fabs(recoEta) > 2.5 || fabs(recoEta) < 1.566 ) continue; // endcap
        if ( ((phoIDbit>>2)&1) == 0 ) continue;
        if ( ((phoFiredTrgs>>ibit)&1) == 0 ) continue;
        
        hBase->Fill(recoPt);
        for ( int jbit = ibit+1; jbit <= MAXBIT; ++jbit )
            if ( ((phoFiredTrgs>>jbit)&1) == 1 )
                hNumerator[jbit]->Fill(recoPt);
    }


    const char* ll = Form(args.template0, ibit);
    //t->Draw( Form("recoPt >> %s", ll), Form("(phoFiredTrgs>>%d) &1 && %s", ibit, EventSelections()) );
    DrawingTo( t,ll, Form("%s && %s", PassTrg(ibit), EventSelections()) );
    for ( int jbit = ibit+1; jbit <= MAXBIT; ++jbit )
    {
        const char* kk = Form(args.template1, ibit, jbit);
        //t->Draw( Form("recoPt >> %s", kk), Form("(phoFiredTrgs>>%d)&1 && (phoFiredTrgs>>%d)&1 && %s", ibit, jbit, EventSelections()) );
        DrawingTo( t,kk, Form("%s && %s && %s", PassTrg(ibit), PassTrg(jbit), EventSelections()) );
    }
}
struct HistDeclareHelper
{
    HistDeclareHelper() { }
    void MakeHist(const char* name, int narr, float* xarr)
    {
        if ( hists.find( std::string(name) ) != hists.end() )
            throw Form( "input name %s duplicated!\n", name );
        hists[std::string(name)] = new TH1F(name,"", narr, xarr);
        return;
    }
    void MakeHist(const char* name, int nbin, float xmin, float xmax)
    {
        if ( hists.find( std::string(name) ) != hists.end() )
            throw Form( "input name %s duplicated!\n", name );
        hists[std::string(name)] = new TH1F(name,"", nbin, xmin, xmax);
        return;
    }
    void Write(TDirectory* dir)
    {
        if ( dir ) dir->cd();
        for ( auto iter = hists.begin(); iter != hists.end(); ++iter )
            iter->second->Write();
    }

    std::map<std::string, TH1F*> hists;
};


void TriggerTurnOn()
{
    //TFile* fin = TFile::Open("/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/data.root");
    //TFile* fin = TFile::Open("/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/Runner_separateAndSubmitToBkg/UL2018.root");
    TFile* fin = TFile::Open("job_EGamma_Run2018D_UL.root");
    //TFile* fin = TFile::Open("/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/data.fromChip02.root");
    //TFile* fin = TFile::Open("/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root");
    TTree* tin = (TTree*) fin->Get("t");

    const char* HLTtemplate0 = "HLT_%d";
    const char* HLTtemplate1 = "HLTintersect_%d_%d";
    std::vector<float> ptranges = GetPtRanges();
    int narr = 20;
    float* xarr = &ptranges.front();
    HistDeclareHelper ptspectrum_singleHLTbit;
    for ( int ibit = 0; ibit <= MAXBIT; ++ibit )
        ptspectrum_singleHLTbit.MakeHist( Form(HLTtemplate0,ibit), narr, xarr );

    HistDeclareHelper ptspectrum_twoBitIntersect;
    for ( int ibit = 0; ibit <= MAXBIT; ++ibit )
        for ( int jbit = ibit+1; jbit <= MAXBIT; ++jbit )
            ptspectrum_twoBitIntersect.MakeHist( Form(HLTtemplate1,ibit,jbit), narr,xarr );

    currentBit bitinfo( HLTtemplate0, HLTtemplate1 );
    for ( int ibit = 0; ibit <= MAXBIT; ++ibit )
    {
        bitinfo.SetBit(ibit);
        ShowTriggerResult(tin, bitinfo);
        //ShowTriggerResult_Loop(tin, bitinfo);
    }

    TFile* fout = new TFile("output.root", "RECREATE");
    fout->cd();
    ptspectrum_singleHLTbit.Write(fout);
    ptspectrum_twoBitIntersect.Write(fout);
    fout->Close();
    printf("output file %s is stored\n", fout->GetName());
}

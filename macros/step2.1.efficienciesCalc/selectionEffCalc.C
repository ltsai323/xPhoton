#define MakeHistoData_cxx
#define MakeHistoSIG_cxx
#define MakeHistoQCD_cxx
#include "makehisto.h"
#include "MakeHistoSIG.h"
//#include "HLTTriggerBitSetting.cc"
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TRandom3.h>
#include <TMath.h>
#include <iostream>
#include <TLorentzVector.h>

// try to find selection efficiency and signal region efficiency.

struct efficiency_record
{ float eff; float err; };
struct OutputModule
{
    OutputModule(const char* oFILEname, const char* columnDEFINITION)
    {
        output.open(oFILEname);
        output << columnDEFINITION << "\n";
    }
    virtual void Write( int pETAbin, int jETAbin, int pPTbin, efficiency_record rec) = 0;
    virtual ~OutputModule() { output.close(); }
    
    std::ofstream output;
};
struct OutputModule_TreeText : OutputModule
{
    OutputModule_TreeText(const char* oFILEname) :
        OutputModule(oFILEname, "ptbin/I:EBEE/I:jetbin/I:efficiency/F:error/F") { }

    virtual void Write( int pETAbin, int jETAbin, int pPTbin, efficiency_record rec ) override
    { output << Form("%d %d %d %.10f %.10f\n", pPTbin,pETAbin,jETAbin, rec.eff, rec.err); }

};
struct Counter
{
    Counter() : passed(0.),overall(0.) {}
    Counter(const Counter& r)
    { passed = r.passed; overall = r.overall; }
    void record_this_event(bool isPassed, double evtWEIGHT)
    {
        overall += evtWEIGHT;
        if ( isPassed )
            passed += evtWEIGHT;
    }
    double get_ratio() const { if ( passed == 0 ) return 0; return passed / overall; }

    double passed, overall;
};


struct BinningCounter
{
    BinningCounter(int maxPETABIN, int maxJETABIN, int maxPPTBIN ) :
        _maxPEtaBin(maxPETABIN), _maxJEtaBin(maxJETABIN), _maxPPtBin(maxPPTBIN) { }

    void RecordThisEvent( int pETAbin, int jETAbin, int pPTbin,
            bool isPASSED, double evtWEIGHT )
    { _stat[pETAbin][jETAbin][pPTbin].record_this_event(isPASSED, evtWEIGHT); }
    void Add( const BinningCounter& r )
    {
        for ( int petabin = 0; petabin < _maxPEtaBin; ++petabin )
            for ( int jetabin = 0; jetabin < _maxJEtaBin; ++jetabin )
                for ( int pptbin = 0; pptbin < _maxPPtBin; ++pptbin )
        {
            _stat[petabin][jetabin][pptbin].passed = r._stat[petabin][jetabin][pptbin].passed;
            _stat[petabin][jetabin][pptbin].overall = r._stat[petabin][jetabin][pptbin].overall;
        }
    }
        
    void Print() const
    {
        printf("ptbin/I:EBEE/I:jetbin/I:passed/F:overall/F:ratio/F\n");
        for ( int petabin = 0; petabin < _maxPEtaBin; ++petabin )
            for ( int jetabin = 0; jetabin < _maxJEtaBin; ++jetabin )
                for ( int pptbin = 0; pptbin < _maxPPtBin; ++pptbin )
                    printf("%d %d %d %.8f %.8f %.8f\n",
                        pptbin,petabin,jetabin,
                        _stat[petabin][jetabin][pptbin].passed,
                        _stat[petabin][jetabin][pptbin].overall,
                        _stat[petabin][jetabin][pptbin].get_ratio()
                      );
    }


    const int _maxPEtaBin, _maxJEtaBin, _maxPPtBin;
    Counter _stat[2][3][25];
};
struct BinningCounterGroup
{
    BinningCounterGroup( int maxPETABIN, int maxJETABIN, int maxPPTBIN ) :
        selection(maxPETABIN,maxJETABIN,maxPPTBIN),
        sigregion(maxPETABIN,maxJETABIN,maxPPTBIN) {}
    BinningCounter selection, sigregion;

    void Add( const BinningCounterGroup& r )
    {
        this->selection.Add(r.selection);
        this->sigregion.Add(r.sigregion);
    }

    void SaveResult() const
    {
        OutputModule* out_jet = new OutputModule_TreeText("dat_jetSelections.dat");
        OutputModule* out_pho = new OutputModule_TreeText("dat_phoControlReg.dat");

        int _maxPEtaBin = this->selection._maxPEtaBin;
        int _maxJEtaBin = this->selection._maxJEtaBin;
        int _maxPPtBin  = this->selection._maxPPtBin;
        for ( int petabin = 0; petabin < _maxPEtaBin; ++petabin )
            for ( int jetabin = 0; jetabin < _maxJEtaBin; ++jetabin )
                for ( int pptbin = 0; pptbin < _maxPPtBin; ++pptbin )
                {
                    efficiency_record jetSelections;
                    jetSelections.eff =  
                        this->selection._stat[petabin][jetabin][pptbin].get_ratio();
                    jetSelections.err =  0.;
                    out_jet->Write(petabin,jetabin,pptbin,jetSelections);

                    efficiency_record phoControlReg;
                    phoControlReg.eff =  
                        this->sigregion._stat[petabin][jetabin][pptbin].get_ratio();
                    phoControlReg.err =  0.;
                    out_pho->Write(petabin,jetabin,pptbin,phoControlReg);
                }

        delete out_jet;
        delete out_pho;
    }
    void Print() const
    {
        int _maxPEtaBin = this->selection._maxPEtaBin;
        int _maxJEtaBin = this->selection._maxJEtaBin;
        int _maxPPtBin  = this->selection._maxPPtBin;
        printf("ptbin/I:EBEE/I:jetbin/I:sel_passed/F:sel_overall/F:sel_ratio/F:sig_passed/F:sig_overall/F:sig_ratio/F\n");
        for ( int petabin = 0; petabin < _maxPEtaBin; ++petabin )
            for ( int jetabin = 0; jetabin < _maxJEtaBin; ++jetabin )
                for ( int pptbin = 0; pptbin < _maxPPtBin; ++pptbin )
                    printf("%d %d %d \t %.8f %.8f %.8f \t %.8f %.8f %.8f\n",
                        pptbin,petabin,jetabin,
                        this->selection._stat[petabin][jetabin][pptbin].passed,
                        this->selection._stat[petabin][jetabin][pptbin].overall,
                        this->selection._stat[petabin][jetabin][pptbin].get_ratio(),
                        this->sigregion._stat[petabin][jetabin][pptbin].passed,
                        this->sigregion._stat[petabin][jetabin][pptbin].overall,
                        this->sigregion._stat[petabin][jetabin][pptbin].get_ratio()
                      );
    }
};



// sig section {{{
EvtSelMgr EvtSelFactory(const MakeHistoSIG& loadvar);
void Fill_AllCTagReshaped( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight, const MakeHistoSIG& loadvars);
void SumNormalization( const EventBinning& bin, Normalization_CTagReshaped& N,const MakeHistoSIG& loadvars );
BinningCounterGroup LoopSIG( Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename, int processNEvt );
EventBinning BinningFactory(const MakeHistoSIG & v) { return  EventBinning(v.recoPt     ,v.recoEta,v.jetPt,v.jetY,v.chIsoRaw   ); }

EvtSelMgr EvtSelFactory(const MakeHistoSIG& loadvar)
{
    bool isMC          = true;
    bool isQCD         = false;
    bool HLTOPTION     = false;
    EvtSelMgr output(isMC,isQCD,HLTOPTION);

    output.SetUsedVar_4(loadvar.jetHadFlvr);
    output.SetUsedVar_3(
        loadvar.chIsoRaw,
        loadvar.recoEta,
        loadvar.isMatched);

    output.SetUsedVar_2(
        loadvar.jetPt,
        loadvar.jetEta,
        loadvar.jetDeepCSVTags_c,
        loadvar.jetID,
        loadvar.jetPUIDbit,
        loadvar.jetSubVtxMass,
        loadvar.DeepCSV_CvsL,
        0); // passMaxPUcut

    output.SetUsedVar_1(
        loadvar.recoSCEta,
        loadvar.sieieFull5x5,
        loadvar.HoverE);
    output.SetUsedVar_0(
        loadvar.MET,
        loadvar.recoPt,
        loadvar.eleVeto,
        loadvar.phoFillIdx);

    output.SetUsedVar__(loadvar.phoFiredTrgs);
    return output;
}
void Fill_AllCTagReshaped( const EventBinning& bin,Hists_CTagReshaped* h, float val, float evt_weight, const MakeHistoSIG& loadvars)
{
    Fill_allctagreshaped_general(bin,h,val, evt_weight,
            loadvars.DeepCSV_ctagWeight_central,
            loadvars.DeepCSV_ctagWeight_PUWeightUp,
            loadvars.DeepCSV_ctagWeight_PUWeightDown,
            loadvars.DeepCSV_ctagWeight_StatUp,
            loadvars.DeepCSV_ctagWeight_StatDown
            );
}
void SumNormalization( const EventBinning& bin, Normalization_CTagReshaped& N,const MakeHistoSIG& loadvars )
{
    normalization_ctagreshaped& n = N.binned_norm[bin.pEtaBin][bin.jEtaBin][bin.pPtBin];
    n.Add(
            loadvars.DeepCSV_ctagWeight_central,
            loadvars.DeepCSV_ctagWeight_PUWeightUp,
            loadvars.DeepCSV_ctagWeight_PUWeightDown,
            loadvars.DeepCSV_ctagWeight_StatUp,
            loadvars.DeepCSV_ctagWeight_StatDown
            );
}


BinningCounterGroup LoopSIG( Int_t extracut, const char* dataERA, const char* dataTYPE, const char* inputfilename, int processNEvt )
{
    const int NUMBIN_PHOPT = ptbin_ranges().size();
    BinningCounterGroup counters(NUMBIN_PHOETA,NUMBIN_JETETA,NUMBIN_PHOPT);

    TRandom3 *trd = new TRandom3();


    TFile* iii = TFile::Open(inputfilename);
    TTree* ttt = (TTree*) iii->Get("t");
    MakeHistoSIG load_sig(ttt);

    Long64_t nentries = processNEvt > 0 ? processNEvt : load_sig.fChain->GetEntries();

    LOG("Looping in %lli entries", nentries);

    Long64_t nbytes = 0, nb = 0;
    for (Long64_t jentry=0; jentry<nentries;jentry++)
    {
        Long64_t ientry = load_sig.LoadTree(jentry);
        
        if (ientry < 0) break;
        nb = load_sig.GetEntry(jentry); nbytes += nb;


        Float_t eventweight = load_sig.mcweight * load_sig.puwei;

	
        const EventBinning evtbin = BinningFactory(load_sig);
        EvtSelMgr sel = EvtSelFactory(load_sig);

        // preselections
        if ( evtbin.pPtBin<0 ) continue;
        
        bool passSel = true;
        if (!sel.PassPhotonPreSelection(evtbin.pPtBin) ) passSel = false;
        if (!sel.InFiducialRegion() ) passSel = false;
        if (!sel.PassJetAdditionalSelection(extracut) ) passSel = false;

        counters.selection.RecordThisEvent(
                evtbin.pEtaBin,evtbin.jEtaBin,evtbin.pPtBin,
                passSel, eventweight );

        bool isFakePhoton =
            (load_sig.isMatched!=1 && load_sig.isConverted!=1 && load_sig.isMatchedEle!=1 )?
            1 : 0;
        if (!isFakePhoton )
        {
            bool inSignalRegion = false;
            if ( evtbin.isSignalRegion )
                inSignalRegion = true;
            counters.sigregion.RecordThisEvent(
                    evtbin.pEtaBin,evtbin.jEtaBin,evtbin.pPtBin,
                    inSignalRegion, eventweight );
        }
    }
    return counters;
}
// sig section end }}}


void Loop(Int_t extracut, const char* dataERA, const char* dataTYPE, const std::vector<const char*>& inputfilenames )
{
    const std::string dataType(dataTYPE);

    //int NEVENT = 10000; // testing event
    int NEVENT = -1; // all event

    std::vector<BinningCounterGroup> result_singlefile;
    result_singlefile.reserve(inputfilenames.size());
    for ( auto inputfilename : inputfilenames )
        result_singlefile.push_back(
            LoopSIG(extracut, dataERA, dataTYPE, inputfilename, NEVENT)
            );

    BinningCounterGroup& outresult = result_singlefile.front();
    
    if ( result_singlefile.size() > 1 )
        for ( unsigned int idx = 1; idx < result_singlefile.size(); ++idx )
            outresult.Add(result_singlefile[idx]);

    outresult.SaveResult();
}

void selectionEffCalc()
{
    Loop(0, "UL2016PreVFP", "gjet", {
            //"/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root",
            //"/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root",
            //"/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root",
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root",
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"
            } );
}
void selection_eff_calc(Int_t extracut, const std::vector<const char*>& inputfilenames )
{ Loop( extracut, "", "", inputfilenames ); }


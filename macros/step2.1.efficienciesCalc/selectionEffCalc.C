#define MakeHistoData_cxx
#define MakeHistoSIG_cxx
#define MakeHistoQCD_cxx
#include "makehisto.C"
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

struct value_and_error
{ double nominal_value; double std_error2; };
value_and_error value_init() { value_and_error a; a.nominal_value = 0; a.std_error2 = 0; return a; }
class efficiency_record
{
    public:
    value_and_error passed;
    value_and_error total;

    value_and_error get_efficiency() const
    {
        value_and_error eff = value_init();

        // passed values
        double pv = passed.nominal_value;
        double pe2= passed.std_error2;
        double tv = total.nominal_value;
        double te2= total.std_error2;
        // failed values
        double fv = tv - pv;
        double fe2= te2 - pe2;

        if ( pv == 0 ) return eff;
        eff.nominal_value = pv / tv;
        eff.std_error2 = pe2*(fv/tv/tv)*(fv/tv/tv) + fe2*(pv/tv/tv)*(pv/tv/tv);
        return eff;
    }
};
struct OutputModule
{
    OutputModule(const char* oFILEname, const char* columnDEFINITION)
    {
        output.open(oFILEname);
        output << columnDEFINITION << "\n";
    }
    virtual void Write( int pETAbin, int jETAbin, int pPTbin, value_and_error rec) = 0;
    virtual ~OutputModule() { output.close(); }
    
    std::ofstream output;
};
struct OutputModule_TreeText : OutputModule
{
    OutputModule_TreeText(const char* oFILEname) :
        OutputModule(oFILEname, "ptbin/I:EBEE/I:jetbin/I:efficiency/F:error/F") { }

    virtual void Write( int pETAbin, int jETAbin, int pPTbin, value_and_error rec ) override
    { output << Form("%d %d %d %.10f %.10f\n", pPTbin,pETAbin,jETAbin, rec.nominal_value, sqrt(rec.std_error2)); }

};
struct Counter
{
    Counter() : eff() {}
    void record_this_event(bool isPassed, double evtWEIGHT)
    {
        eff.total.nominal_value += evtWEIGHT;
        eff.total.std_error2 += evtWEIGHT*evtWEIGHT;
        if ( isPassed )
        {
            eff.passed.nominal_value += evtWEIGHT;
            eff.passed.std_error2 += evtWEIGHT*evtWEIGHT;
        }
    }
    double get_ratio() const { return eff.get_efficiency().nominal_value; }
    value_and_error get_efficiency() const { return eff.get_efficiency(); }

    efficiency_record eff;
};


struct BinningCounter
{
    BinningCounter(int maxPETABIN, int maxJETABIN, int maxPPTBIN ) :
        _maxPEtaBin(maxPETABIN), _maxJEtaBin(maxJETABIN), _maxPPtBin(maxPPTBIN) {}

    void RecordThisEvent( int pETAbin, int jETAbin, int pPTbin,
            bool isPASSED, double evtWEIGHT )
    { _stat[pETAbin][jETAbin][pPTbin].record_this_event(isPASSED, evtWEIGHT); }
    void Add( const BinningCounter& r )
    {
        for ( int petabin = 0; petabin < _maxPEtaBin; ++petabin )
            for ( int jetabin = 0; jetabin < _maxJEtaBin; ++jetabin )
                for ( int pptbin = 0; pptbin < _maxPPtBin; ++pptbin )
        {
            _stat[petabin][jetabin][pptbin].eff.passed.nominal_value  += r._stat[petabin][jetabin][pptbin].eff.passed.nominal_value;
            _stat[petabin][jetabin][pptbin].eff.passed.std_error2     += r._stat[petabin][jetabin][pptbin].eff.passed.std_error2;
            _stat[petabin][jetabin][pptbin].eff.total.nominal_value   += r._stat[petabin][jetabin][pptbin].eff.total.nominal_value;
            _stat[petabin][jetabin][pptbin].eff.total.std_error2      += r._stat[petabin][jetabin][pptbin].eff.total.std_error2;
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
                        _stat[petabin][jetabin][pptbin].eff.passed.nominal_value,
                        _stat[petabin][jetabin][pptbin].eff.total.nominal_value,
                        _stat[petabin][jetabin][pptbin].get_efficiency().nominal_value
                      );
    }


    const int _maxPEtaBin, _maxJEtaBin, _maxPPtBin;
    Counter _stat[2][3][30];
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

    //void SaveResult() const
    void SaveResult()
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
                    value_and_error jetSelections_ =
                        this->selection._stat[petabin][jetabin][pptbin].get_efficiency();
                    out_jet->Write(petabin,jetabin,pptbin,jetSelections_);

                    value_and_error phoControlReg_ =
                        this->sigregion._stat[petabin][jetabin][pptbin].get_efficiency();
                    out_pho->Write(petabin,jetabin,pptbin,phoControlReg_);
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
                        this->selection._stat[petabin][jetabin][pptbin].eff.passed.nominal_value,
                        this->selection._stat[petabin][jetabin][pptbin].eff.total.nominal_value,
                        this->selection._stat[petabin][jetabin][pptbin].get_efficiency().nominal_value,
                        this->sigregion._stat[petabin][jetabin][pptbin].eff.passed.nominal_value,
                        this->sigregion._stat[petabin][jetabin][pptbin].eff.total.nominal_value,
                        this->sigregion._stat[petabin][jetabin][pptbin].get_efficiency().nominal_value
                      );
    }
};



// sig section {{{
BinningCounterGroup selLoopSIG( Int_t extracut, const char* dataERA, const char* tagALGO, const char* inputfilename, int processNEvt = -1 )
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
        EvtSelMgr sel = EvtSelFactory(load_sig, tagALGO);

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


void selLoop(Int_t extracut, const char* dataERA, const char* tagALGO, const std::vector<const char*>& inputfilenames )
{

    //int NEVENT = 10000; // testing event
    int NEVENT = -1; // all event

    std::vector<BinningCounterGroup> result_singlefile;
    result_singlefile.reserve(inputfilenames.size());
    for ( auto inputfilename : inputfilenames )
        result_singlefile.push_back(
            selLoopSIG(extracut, dataERA, tagALGO, inputfilename, NEVENT)
            );

    BinningCounterGroup& outresult = result_singlefile.front();
    
    if ( result_singlefile.size() > 1 )
        for ( unsigned int idx = 1; idx < result_singlefile.size(); ++idx )
            outresult.Add(result_singlefile[idx]);

    outresult.SaveResult();
}

void selectionEffCalc()
{
    selLoop(0, "UL2016PreVFP", "DeepCSV", {
            //"/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root",
            //"/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root",
            //"/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root",
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root",
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"
            } );
}
void selection_eff_calc(Int_t extracut, const std::vector<const char*>& inputfilenames )
{ selLoop( extracut, "UL2016PreVFP", "DeepCSV", inputfilenames ); }



//#define BUG(format, args...)     fprintf(stderr, "---------------------debug-    %s  \n  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)
#define BUG(format, args...)
#define LOG(format, args...)     fprintf(stderr, "[LOG]  %s  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)

static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000,5000});
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
// list of mc weights ( mcweight ordered
// 0.155885 0.365085 2.86964 6.49481 18.5005 228.55 1053.94 12126.6 2.1248e+06
static std::vector<float> mcweightBins ({ 1e-3,0.15,0.16, 0.35,0.38, 2.8,2.9, 6.4,6.5, 18.,19.,228.,229., 1050.,1055., 12120.,12130.,2.e6,2.2e6, 2.3e6});

class HistCategory_mcweight : public TH1F
{
public:
    HistCategory_mcweight( const char* histname ) :
        TH1F(histname,"", mcweightBins.size()-1, &(mcweightBins.front())) {}
};
class HistCategory_jetpt : public TH1F
{
public:
    HistCategory_jetpt( const char* histname ) :
        TH1F(histname,"", jetptBin.size()-1, &(jetptBin.front())) {}
};

struct HistStorage
{
public:
    HistStorage(TDirectory* dir = nullptr ) : _dir(dir), _postfix( Counter() ) {}
    void Archive(TH1* hist)
    {
        hist->SetName( Form("%s_file%d", hist->GetName(), _postfix) );
        _dir->cd();
        hist->Write();
        delete hist;
    }
    ~HistStorage() {}

    static void counterplusplus() { counter++; }
private:
    TDirectory* _dir;
    const int _postfix;
    static int counter;
    static int Counter() { return counter; }

    // forbid copy
    HistStorage(const HistStorage&);
};
int HistStorage::counter = 0;

struct OutputManager
{
public:
    OutputManager( const char* output_filename ) :
        _file0( new TFile(output_filename, "RECREATE") )
    {
        _dirmap["allsample"] = _file0->mkdir("allsample");
        _dirmap["noLargePU"] = _file0->mkdir("noLargePU");
        _dirmap["noEvtWeig"] = _file0->mkdir("noEvtWeig");
    }
    virtual ~OutputManager() { _file0->Close(); }
    void GetHistFrom(const char* ifilename);
    //void gethistfrom(const char* ifilename);

    TFile* _file0;
    std::map<const char*, TDirectory*> _dirmap;
};
struct NTupleLoader
{
public:
    NTupleLoader(const char* ifilename) : _file0( TFile::Open(ifilename) )
    {
        ntuple = (TNtuple*) _file0->Get("nt");
        return; // variables are not loaded due to no event loop.
        /*

        ntuple->SetBranchAddress("jetPtBin",&jetPtBin);
        ntuple->SetBranchAddress("mcweight",&mcweight);
        ntuple->SetBranchAddress("jetPt",   &jetPt   );
        ntuple->SetBranchAddress("genHT",   &genHT   );
        ntuple->SetBranchAddress("maxPUhat",&maxPUhat);
        ntuple->SetBranchAddress("hadFlvr", &hadFlvr );
        */
    }
    //bool IsSelectedEvent() { return true; }

    TFile*   _file0;
    TNtuple* ntuple;

    /*
    Int_t   jetPtBin;
    Float_t mcweight;
    Float_t jetPt;
    Float_t genHT;
    Float_t maxPUhat;
    Int_t   hadFlvr;
    */
};
struct EventSelectionGenerater
{
    EventSelectionGenerater(const char* s, const char* w = nullptr): basicCut(s), evWeight(w)
    { if ( w == nullptr ) evWeight = "1"; }
    const char* TotalCut(const char* s = nullptr)
    {
        if ( s == nullptr ) return basicCut;
        return Form("%s * (%s && %s)", evWeight, basicCut, s);
    }
    const char* B( const char* s = nullptr )
    { return TotalCut( s==nullptr ? "hadFlvr==5" : Form("hadFlvr==5 && %s",s) ); }
    const char* C( const char* s = nullptr )
    { return TotalCut( s==nullptr ? "hadFlvr==4" : Form("hadFlvr==4 && %s",s) ); }
    const char* L( const char* s = nullptr )
    { return TotalCut( s==nullptr ? "hadFlvr==0" : Form("hadFlvr==0 && %s",s) ); }
    
    const char* basicCut;
    const char* evWeight;
};
void Drawing(NTupleLoader* data_loader, HistStorage* hist_coll, EventSelectionGenerater* sel )
{
    TH1* hstorage = nullptr;
    const char* var;
    const char* cut;

    for ( int ibin = 0; ibin < jetptBin.size()+1; ++ibin )
    {
        hstorage = new HistCategory_mcweight( Form("weight_ptbin%d",ibin) );
        var = Form("mcweight >> %s", hstorage->GetName());
        cut = Form("jetPtBin == %d", ibin);
        data_loader->ntuple->Draw( var,sel->TotalCut(cut) );
        hist_coll->Archive(hstorage);
    }
    hstorage = new HistCategory_jetpt("b_yield");
    var = Form("jetPt >> %s", hstorage->GetName());
    data_loader->ntuple->Draw(var,sel->B());
    BUG("Integral : %f with selection %s", hstorage->Integral(), sel->B() );

    hist_coll->Archive(hstorage);
    hstorage = new HistCategory_jetpt("c_yield");
    var = Form("jetPt >> %s", hstorage->GetName());
    data_loader->ntuple->Draw(var,sel->C());
    hist_coll->Archive(hstorage);

    hstorage = new HistCategory_jetpt("L_yield");
    var = Form("jetPt >> %s", hstorage->GetName());
    data_loader->ntuple->Draw(var,sel->L());
    hist_coll->Archive(hstorage);
}
void OutputManager::GetHistFrom(const char* ifilename)
{
    LOG("Start function %s", ifilename);
    NTupleLoader data_loader(ifilename);

    HistStorage hists_allsample(_dirmap["allsample"]);
    HistStorage hists_noLargePU(_dirmap["noLargePU"]);
    HistStorage hists_noEvtWeig(_dirmap["noEvtWeig"]);
    HistStorage::counterplusplus();


    EventSelectionGenerater allEvt("jetPt>0", "mcweight");
    EventSelectionGenerater puVeto("jetPt>0&& genHT_pthatDef > maxPUhat && maxPUhat>0", "mcweight");
    EventSelectionGenerater noweig("jetPt>0&& genHT_pthatDef > maxPUhat && maxPUhat>0");

    Drawing(&data_loader, &hists_allsample, &allEvt);
    Drawing(&data_loader, &hists_noLargePU, &puVeto);
    Drawing(&data_loader, &hists_noEvtWeig, &noweig);
}

void AddFiles_Old(OutputManager* output)
{
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT50to100.root");
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT100to200.root");
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT200to300.root");
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT300to500.root");
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT500to700.root");
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT700to1000.root");
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT1000to1500.root");
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT1500to2000.root");
    output->GetHistFrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT2000toInf.root");
}
void AddFiles_UL2016PreVFP(OutputManager* output)
{
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT50to100.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT100to200.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT200to300.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT300to500.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT500to700.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT700to1000.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT1000to1500.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT1500to2000.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT2000toInf.root");
}
void AddFiles_UL2016PostVFP(OutputManager* output)
{
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT50to100.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT100to200.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT200to300.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT300to500.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT500to700.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT700to1000.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT1000to1500.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT1500to2000.root");
    output->GetHistFrom("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/xQCD2nd_ReweightChecking_Madgraph_cc_HT2000toInf.root");
}
void qcdCHECKER_interestingHIST()
{
    OutputManager newfile("_qcdCHECKER_interestingHIST_C.root");

    //AddFiles_UL2016PreVFP(&newfile);
    AddFiles_UL2016PostVFP(&newfile);
}

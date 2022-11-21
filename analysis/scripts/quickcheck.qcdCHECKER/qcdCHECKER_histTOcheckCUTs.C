
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
    HistStorage(TDirectory* dir = nullptr, int fileIdx = Counter() ) : _dir(dir), _postfix(fileIdx) {}
    void Archive(TH1* hist)
    {
        hist->SetName( Form("%s_file%d", hist->GetName(), _postfix) );
        _dir->cd();
        hist->Write();
        //delete hist;
    }
    ~HistStorage() {}

    static void counterplusplus() { counter++; }
    int GetFileIdx() const { return _postfix; }
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
    { }
    virtual ~OutputManager() { for ( auto ifile : iFILEs ) ((TFile*) ifile)->Close(); _file0->Close(); }
    void GetHistFrom(const char* ifilename);
    void Add(const char* fileNAME) { iFILEs.push_back( (void*) TFile::Open(fileNAME) ); }
    void MakeHistWithSelection(const char* dirTITLE, const char* cut, const char* weight = nullptr, void (*histSHAPER)(TH1*,int) = NULL);

    TFile* _file0;
    std::map<const char*, TDirectory*> _dirmap;
    std::vector<TDirectory*> DIRs;
    std::vector<void*> iFILEs;
};
struct NTupleLoader
{
public:
    NTupleLoader(const char* ifilename) : _file0( TFile::Open(ifilename) )
    { ntuple = (TNtuple*) _file0->Get("nt"); }
    NTupleLoader(TFile* f ) : _file0(f)
    { ntuple = (TNtuple*) _file0->Get("nt"); }
    TFile*   _file0;
    TNtuple* ntuple;
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
void Drawing(NTupleLoader* data_loader, HistStorage* hist_coll, EventSelectionGenerater* sel, void (*histSHAPER)(TH1*,int) = NULL)
{
    TH1* hstorage = nullptr;
    const char* var;
    const char* cut;

    BUG("01");
    for ( int ibin = 0; ibin < jetptBin.size()+1; ++ibin )
    {
    BUG("01.1");
        hstorage = new HistCategory_mcweight( Form("weight_ptbin%d",ibin) );
        var = Form("mcweight >> %s", hstorage->GetName());
        cut = Form("jetPtBin == %d", ibin);
        data_loader->ntuple->Draw( var,sel->TotalCut(cut) );
        if ( histSHAPER != NULL ) histSHAPER(hstorage,hist_coll->GetFileIdx());
        hist_coll->Archive(hstorage);
    BUG("01.2");
    }
    BUG("02");
    hstorage = new HistCategory_jetpt("b_yield");
    BUG("02.1");
    var = Form("jetPt >> %s", hstorage->GetName());
    BUG("02.2");
    data_loader->ntuple->Draw(var,sel->B());
    BUG("02.3");
    if ( histSHAPER != NULL ) histSHAPER(hstorage,hist_coll->GetFileIdx());
    BUG("02.4");
    hist_coll->Archive(hstorage);
    BUG("Integral : %f with selection %s", hstorage->Integral(), sel->B() );
    BUG("03");

    hstorage = new HistCategory_jetpt("c_yield");
    var = Form("jetPt >> %s", hstorage->GetName());
    data_loader->ntuple->Draw(var,sel->C());
    if ( histSHAPER != NULL ) histSHAPER(hstorage,hist_coll->GetFileIdx());
    hist_coll->Archive(hstorage);
    BUG("04");

    hstorage = new HistCategory_jetpt("L_yield");
    var = Form("jetPt >> %s", hstorage->GetName());
    data_loader->ntuple->Draw(var,sel->L());
    if ( histSHAPER != NULL ) histSHAPER(hstorage,hist_coll->GetFileIdx());
    hist_coll->Archive(hstorage);
    BUG("05");
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
    EventSelectionGenerater puVeto("jetPt>0&& genHT/nLHE > maxPUhat && maxPUhat>0", "mcweight");
    EventSelectionGenerater noweig("jetPt>0&& genHT/nLHE > maxPUhat && maxPUhat>0");

    Drawing(&data_loader, &hists_allsample, &allEvt);
    Drawing(&data_loader, &hists_noLargePU, &puVeto);
    Drawing(&data_loader, &hists_noEvtWeig, &noweig);
}
void OutputManager::MakeHistWithSelection(const char* dirTITLE, const char* cut, const char* weight, void (*histSHAPER)(TH1*,int) = NULL)
{
    LOG("%s Processing...", dirTITLE);
    TDirectory* dir = _file0->mkdir(dirTITLE);
    DIRs.push_back(dir);
    
    dir->cd();
    EventSelectionGenerater evtsel(cut,weight);
    std::list< std::pair<HistStorage,NTupleLoader*>> hists;

    for ( int iMC = 0; iMC < iFILEs.size(); ++iMC )
    {
        HistStorage hist(dir, iMC);
        NTupleLoader data((TFile*)iFILEs[iMC]);
        Drawing(&data, &hist, &evtsel, histSHAPER);
    }
}

void DisableBin(TH1* h, int iMC, int maxBIN[])
{
    for ( auto ibin = h->GetNbinsX()+1; ibin != 0; --ibin )
    {
        if ( ibin >= maxBIN[iMC] ) h->SetBinContent(ibin, 0);
        if ( ibin < maxBIN[iMC] )
        {
            BUG("program stop at bin ibin%d with cut edge %5.0f at %s\n", ibin, h->GetBinLowEdge(ibin+1), h->GetName());
            break;
        }
    }
}

// result from qcdCHECKER_jetPtBinCutDecider.C
const int NMCSEP=9;
int jetptBin_100CUT[NMCSEP] = {7,16,16,18,20,21,22,23,24};
int jetptBin_10CUT[NMCSEP] = {11,20,20,21,22,23,24,24,24};
int jetptBin_tenToMinusFiveCut[NMCSEP] = {10,10,15,17,20,20,22,23,24};
void NoBin_100Entries(TH1* h, int iMC)
{ DisableBin(h,iMC, jetptBin_100CUT); }
void NoBin_10Entries(TH1* h, int iMC)
{ DisableBin(h,iMC, jetptBin_10CUT); }
void NoBin_tenToMinusFive(TH1* h, int iMC)
{ DisableBin(h,iMC, jetptBin_tenToMinusFiveCut); }



void qcdCHECKER_histTOcheckCUTs()
{
    OutputManager newfile("_qcdCHECKER_histTOcheckCUTs_C.root");

    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT50to100.root");
    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT100to200.root");
    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT200to300.root");
    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT300to500.root");
    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT500to700.root");
    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT700to1000.root");
    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT1000to1500.root");
    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT1500to2000.root");
    newfile.Add("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT2000toInf.root");

    newfile.MakeHistWithSelection("allSample", "jetPt>0", "mcweight");
    newfile.MakeHistWithSelection("noLargePU", "jetPt>0&& genHT/nLHE > maxPUhat && maxPUhat>0", "mcweight");
    newfile.MakeHistWithSelection("noGenWeig", "jetPt>0&& genHT/nLHE > maxPUhat && maxPUhat>0");
    
    //// result from qcdCHECKER_jetPtBinCutDecider.C
    newfile.MakeHistWithSelection("PUvetoAndPtBin10", "jetPt>0&& genHT/nLHE > maxPUhat && maxPUhat>0", "mcweight", NoBin_10Entries);
    newfile.MakeHistWithSelection("PUvetoAndPtBin100", "jetPt>0&& genHT/nLHE > maxPUhat && maxPUhat>0", "mcweight", NoBin_100Entries);
    newfile.MakeHistWithSelection("PUvetoAndPtBintenTOminusFIVE", "jetPt>0&& genHT/nLHE > maxPUhat && maxPUhat>0", "mcweight", NoBin_tenToMinusFive);
}


//#define BUG(format, args...)     fprintf(stderr, "---------------------debug-    %s  \n  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)
#define BUG(format, args...)
#define LOG(format, args...)     fprintf(stderr, "[LOG]  %s  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)

static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000,5000});
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
// list of mc weights
// 2.1248e+06 12126.6 1053.94 228.55 18.5005 6.49481 2.86964 0.365085 0.155885
static std::vector<float> mcweightBins ({ 1e-1,0.15,0.16, 0.35,0.38, 2.8,2.9, 6.4,6.5, 18.,19.,228.,229., 1050.,1055., 12120.,12130.,2.e6,2.2e6, 2.3e6});
struct HistStorage
{
    HistStorage( const char* histname )
    { hist = new TH1F(histname, "", mcweightBins.size()-1, &(mcweightBins.front())); }
    HistStorage() : hist(nullptr) {}
    virtual ~HistStorage() { if ( hist ) delete hist; }
    void Fill(float inval) { hist->Fill(inval); }
    void Write( TDirectory* dir )
    { dir->cd(); hist->Write(); delete hist; hist = nullptr; }

    TH1* hist;
    int  hbin;
};
struct HistStorage_mcweight : public HistStorage
{
    HistStorage_mcweight( const char* histname )
    { hist = new TH1F(histname, "", mcweightBins.size()-1, &(mcweightBins.front())); }
};
struct HistStorage_jetpt : public HistStorage
{
    HistStorage_jetpt( const char* histname )
    { hist = new TH1F(histname, "", jetptBin.size()-1, &(jetptBin.front())); }
};
struct HistStorage_genHT : public HistStorage
{
    HistStorage_genHT( const char* histname, int binIdx )
    {
        float lEdge = genHTBin.at(binIdx);
        float rEdge = genHTBin.at(binIdx+1);
        hist = new TH1F(histname, "", 10, lEdge, rEdge); }
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
struct FileStorage
{
    FileStorage( const char* output_filename ) :
        _file0( new TFile(output_filename, "RECREATE") )
    {
        _dirmap["orig"] = _file0;
    }
    virtual ~FileStorage() { _file0->Close(); }
    //TH1* GetHistFrom(const char* ifilename);
    TH1* gethistfrom(const char* ifilename, const char* tag);
    void UsedCut(EventSelectionGenerater* inn) { evtsel = inn; }

    TFile* _file0;
    std::map<const char*, TDirectory*> _dirmap;
    EventSelectionGenerater* evtsel;
};
#define STAT_THRESHOLD 10
void ShowCutEdge(TH1* h)
{
    for ( auto ibin = h->GetNbinsX(); ibin != 0; --ibin )
    {
        double val = h->GetBinContent(ibin);
        //if ( val > STAT_THRESHOLD )
        if ( val > h->Integral() * 1e-5 )
        {
            // show previous bin
            printf("%20s cut off bin : %d. Content of this bin = %5.0f and next bin = %5.0f. The cut edge should be %5.0f\n",
                    h->GetName(), ibin+1, h->GetBinContent(ibin), h->GetBinContent(ibin+1), h->GetBinLowEdge(ibin+1));
            break;
        }
    }
}



TH1* FileStorage::gethistfrom(const char* ifilename, const char* tag)
{
    auto ifile = TFile::Open(ifilename);
    auto itree = (TTree*) ifile->Get("nt");

    BUG("hi %d",1);
    auto jetspectrum = new TH1F( Form("jetpt_%s",tag), "", jetptBin.size()-1, &(jetptBin.front()) );
    BUG("hi %d",2);
    itree->Draw( Form("jetPt>>%s",jetspectrum->GetName()), evtsel->TotalCut() );
    BUG("hi %d",3);
    ShowCutEdge(jetspectrum);
    BUG("hi %d",4);
    _dirmap["orig"]->cd();
    jetspectrum->Write();
    ifile->Close();
    return jetspectrum;
}

void qcdCHECKER_jetPtBinCutDecider()
{
    EventSelectionGenerater puVeto("jetPt>0&& genHT_pthatDef > maxPUhat && maxPUhat>0");

    FileStorage newfile("_qcdCHECKER_jetPtBinCutDecider_C.root");
    newfile.UsedCut(&puVeto);

    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT50to100.root"       ,"50to100");
    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT100to200.root"      ,"100to200");
    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT200to300.root"      ,"200to300");
    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT300to500.root"      ,"300to500");
    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT500to700.root"      ,"500to700");
    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT700to1000.root"     ,"700to1000");
    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT1000to1500.root"    ,"1000to1500");
    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT1500to2000.root"    ,"1500to2000");
    newfile.gethistfrom("/home/ltsai/Work/github/xPhoton/xPhoton/bin/xQCD2nd_ReweightChecking_Madgraph_cc_HT2000toInf.root"     ,"2000toInf");
}

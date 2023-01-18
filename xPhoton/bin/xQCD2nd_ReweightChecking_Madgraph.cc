#include <iostream>
#include <vector>
#include <map>

#include "TTree.h"
#include "TFile.h"
#include "TBranch.h"
#include "TH1F.h"
#include "TNtuple.h"
#include "TCanvas.h"

using namespace std;
static std::vector<float> genHTBin({50,100,200,300,500,700,1000,1500,2000});
static std::vector<float> jetptBin({25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000});
float* xaxis() { return &(genHTBin.front()); }
int    nbins() { return genHTBin.size()-1; }
int    getbin( const std::vector<float>& binningVector, float var )
{
    // underflow bin : 0
    // overflow bin : size()
    int binidx = binningVector.size();
    while ( binidx-- != 0 )
        if ( var > binningVector[binidx] ) return binidx+1;
    return 0; // underflow bin
}

class MyHist : public TH1F
{
public:
    MyHist( string name, string xtitle, int nbin, float xmin, float xmax ) :
        TH1F( name.c_str(), "", nbin, xmin, xmax )
    { this->Sumw2(); this->SetStats(false); this->GetXaxis()->SetTitle( xtitle.c_str() ); }
    MyHist( string name, string xtitle, int nbin, float* arrs ) :
        TH1F( name.c_str(), "", nbin, arrs )
    { this->Sumw2(); this->SetStats(false); this->GetXaxis()->SetTitle( xtitle.c_str() ); }
};
struct HistCollector
{
public:
    HistCollector() { postfix = HistCollector::GetPostFix(); }
    void Create( string name, int nbin, float xmin, float xmax )
    {
        if ( hists.find(name) == hists.end() )
            hists[name] = new MyHist(_n(name), name, nbin, xmin, xmax);
        else throw Form("error : HistCollector collects duplicated histogram %s\n", name.c_str() );
    }
    void Create( string name)
    {
        if ( hists.find(name) == hists.end() )
            hists[name] = new MyHist(_n(name), name, nbins(), xaxis());
        else throw Form("error : HistCollector collects duplicated histogram %s\n", name.c_str() );
    }
    void MakeGlobal() 
    {
        for ( auto iter = hists.begin(); iter != hists.end(); ++iter )
            iter->second->SetDirectory(0);
    }
    MyHist* at(const std::string& n) { return hists.find(n)->second; }
    void Fill(std::string n, float v) { hists.find(n)->second->Fill(v); }
    void SaveHistTo(TCanvas* c1)
    {
        for ( auto hpair : hists )
        { hpair.second->Draw(); c1->SaveAs( Form("h_%s.png", hpair.first.c_str()) ); }
    }
    
    static int numIdx;
private:
    std::map<std::string, MyHist*> hists;
    std::string postfix;
    std::string _n( std::string name) { return name + postfix; }

    static std::string GetPostFix() { return "."+std::to_string(HistCollector::numIdx++); }
};
int HistCollector::numIdx = 0;

struct MyTreeAccess
{
    MyTreeAccess(const char* filename) :
        f( TFile::Open(filename) ),
        t( (TTree*) f->Get("t") ),
        lhePt (nullptr),
        lhePID (nullptr),
        lheDeltaR (nullptr),
        lhePtDiff (nullptr),
        leadingJetRawE(0),
        leadingJetPt (0),
        leadingJetHadFlvr (0),
        leadingJetPartonID (0),
        leadingJetGenPartonID (0),
        genHT(0),
        genHT_pthatDef(0),
        nLHE(0),
        puweight(0.),
        MET(0),
        pthat_PU(nullptr)
    { SetBranchAddress(t);}
    ~MyTreeAccess() { f->Close(); }
    void SetBranchAddress(TTree* tin)
    {
        tin->SetBranchAddress("lhePt", &lhePt);
        tin->SetBranchAddress("lhePID", &lhePID);
        tin->SetBranchAddress("lheDeltaR", &lheDeltaR);
        tin->SetBranchAddress("lhePtDiff", &lhePtDiff);
        //tin->SetBranchAddress("leadingJetRawE", &leadingJetRawE); //asdf temporally disabled.
        tin->SetBranchAddress("leadingJetPt", &leadingJetPt);
        tin->SetBranchAddress("leadingJetHadFlvr", &leadingJetHadFlvr);
        tin->SetBranchAddress("leadingJetPartonID", &leadingJetPartonID);
        tin->SetBranchAddress("leadingJetGenPartonID", &leadingJetGenPartonID);
        tin->SetBranchAddress("GenHT", &genHT);
        tin->SetBranchAddress("genHT_pthatDef", &genHT_pthatDef);
        tin->SetBranchAddress("lheNum", &nLHE);
        //tin->SetBranchAddress("puwei", &puweight); // asdf temporarlly disabled.
        tin->SetBranchAddress("pthat_PU", &pthat_PU);
        tin->SetBranchAddress("MET", &MET);
    }
    Long64_t GetEntries() const { return t->GetEntries(); }
    void GetEntry(Long64_t ievt) { t->GetEntry(ievt); }
    
    
private:
    TFile* f;
    TTree* t;

public:
    vector<Float_t>* lhePt;
    vector<Int_t>* lhePID;
    vector<Float_t>* lheDeltaR;
    vector<Float_t>* lhePtDiff;

    float leadingJetRawE;
    float leadingJetPt;
    int leadingJetHadFlvr;
    int leadingJetPartonID;
    int leadingJetGenPartonID;
    float genHT;
    float genHT_pthatDef;
    int nLHE;
    float puweight;
    float MET;
    vector<Float_t>* pthat_PU;
    
};
struct TreeContent
{
    void Register(TTree* t)
    {
        t->Branch("jetRawE", &jetRawE, "jetRawE/F");
        t->Branch("jetPt", &jetPt, "jetPt/F");
        t->Branch("lhePt", &lhePt, "lhePt/F");
        t->Branch("genHT", &genHT, "genHT/F");
        t->Branch("genHT_pthatDef", &genHT_pthatDef, "genHT_pthatDef/F");
        t->Branch("mcweight", &mcweight, "mcweight/F");
        t->Branch("puweight", &puweight, "puweight/F");
        t->Branch("MET", &MET, "MET/F");
        t->Branch("maxPUhat", &maxPUhat, "maxPUhat/F");

        t->Branch("nLHE", &nLHE, "nLHE/I");
        t->Branch("hadFlvr", &hadFlvr, "hadFlvr/I");
        t->Branch("partonID", &partonID, "partonID/I");
        t->Branch("genpartonID", &genpartonID, "genpartonID/I");
        t->Branch("lhePID", &lhePID, "lhePID/I");
        t->Branch("lheIdx", &lheIdx, "lheIdx/I");
        t->Branch("lheIdxInv", &lheIdxInv, "lheIdxInv/I");
        t->Branch("jetPtBin", &jetPtBin, "jetPtBin/I");
        t->Branch("lhePtBin", &lhePtBin, "lhePtBin/I");
    }
    float jetRawE, jetPt, lhePt, genHT, genHT_pthatDef, mcweight, puweight, maxPUhat, MET;
    int nLHE, hadFlvr, partonID, genpartonID, lhePID, lheIdx, lheIdxInv, jetPtBin, lhePtBin;
};
void AnalyzeFile( const char* outtag, const char* ifilename, float assignedmcweight )
{
    printf("loading file %s\n",ifilename);
    MyTreeAccess data(ifilename);


    TFile* fout = new TFile( Form("xQCD2nd_ReweightChecking_Madgraph_cc_%s.root",outtag), "RECREATE");
    TTree* tout = new TTree("nt", "");

    TreeContent o;
    o.Register(tout);
    
    printf("total entries : %10lld\n", data.GetEntries());
    for ( auto ievtInv = data.GetEntries(); ievtInv != 0; --ievtInv )
    {
        data.GetEntry(ievtInv-1);
        if ( ievtInv % 100000 == 0 ) printf("evt : %10lld\r", ievtInv );
        memset(&o, 0x00, sizeof(o));

        // sorting deltaR of lheParticle and recoJet. Find minimum deltaR event.
        std::map<float, int> dRSorting;
        for ( unsigned idx = 0; idx < data.lheDeltaR->size(); ++idx )
            dRSorting[ data.lheDeltaR->at(idx) ] = idx;
        int dR1st_idx =  -1;
        int dR1st_idxInv =  -1;
        int lhePID =  -999;
        int rPtBin = getbin( jetptBin, data.leadingJetPt);
        int lPtBin =  -1;
        float lhePt =  -999;
        if ( dRSorting.size() > 0 )
        {
            dR1st_idx =  dRSorting.begin()->second;
            dR1st_idxInv =  dRSorting.size() - 1 - dRSorting.begin()->second;
            lhePID =  data.lhePID->at(dR1st_idx);

            lPtBin =  getbin(genHTBin, data.lhePt->at(dR1st_idx));
            lhePt =  data.lhePt->at(dR1st_idx);
        }
        

        // find max PU hat.
        float maxPUhat = -1.;
        for ( unsigned idx = 0; idx < data.pthat_PU->size(); ++idx )
            if ( maxPUhat < data.pthat_PU->at(idx) ) maxPUhat = data.pthat_PU->at(idx);
        
        o.jetRawE = data.leadingJetRawE;
        o.jetPt = data.leadingJetPt;
        o.lhePt = lhePt;
        o.genHT = data.genHT;
        o.genHT_pthatDef = data.genHT_pthatDef;
        o.mcweight = assignedmcweight;
        o.puweight = data.puweight;
        o.MET = data.MET;

        o.nLHE = data.nLHE;
        o.hadFlvr = data.leadingJetHadFlvr;
        o.partonID = data.leadingJetPartonID;
        o.genpartonID = data.leadingJetGenPartonID;
        o.lhePID = lhePID;
        o.lheIdx = dR1st_idx;
        o.lheIdxInv = dR1st_idxInv;
        o.jetPtBin = rPtBin;
        o.lhePtBin = lPtBin;
        o.maxPUhat = maxPUhat;
        tout->Fill();
    }
    
    tout->Write();
    fout->Close();
    printf("\ncomplete process!\n");
    return;
}

void PrintHelp()
{
    fprintf(stderr, "======================================================\n");
    fprintf(stderr, "== Input tree and store some specific branches. And ==\n");
    fprintf(stderr, "== make a new branch by looping event. For this     ==\n");
    fprintf(stderr, "== code, select maximum value of PU pt hat in event ==\n");
    fprintf(stderr, "==   arg1: output tag.                              ==\n");
    fprintf(stderr, "==   arg2: input filename.                          ==\n");
    fprintf(stderr, "==   arg3: integrated luminosity weight. (mcweight) ==\n");
    fprintf(stderr, "==         (=xs weight * event pu weight...)        ==\n");
    fprintf(stderr, "======================================================\n");
    throw;
}
const char* GetArg_OutTag(int argc, const char* argv[])
{
    if ( argc < 1+1 ) PrintHelp();
    return argv[1];
}
const char* GetArg_InFile(int argc, const char* argv[])
{
    if ( argc < 2+1 ) PrintHelp();
    return argv[2];
}
double GetArg_IntegratedLuminosityWeight(int argc, const char* argv[])
{
    if ( argc < 3+1 ) PrintHelp();
    return std::stod(argv[3]);
}

int main(int argc, const char* argv[])
{
    const char* ifile = GetArg_InFile(argc,argv);
    const char* tag = GetArg_OutTag(argc,argv);
    double filled_mcweight = GetArg_IntegratedLuminosityWeight(argc,argv);

    AnalyzeFile(tag, ifile, filled_mcweight);
    return 0;
    /*
    // tag, input_file, xs weight
    AnalyzeFile("QCD_HT50to100",    "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"              , 2.1248e+6);
    AnalyzeFile("QCD_HT100to200",   "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"             , 12126.6);
    AnalyzeFile("QCD_HT200to300",   "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"             , 1053.94);
    AnalyzeFile("QCD_HT300to500",   "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"             , 228.55);
    AnalyzeFile("QCD_HT500to700",   "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"             , 18.5005);
    AnalyzeFile("QCD_HT700to1000",  "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"            , 6.49481);
    AnalyzeFile("QCD_HT1000to1500", "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"           , 2.86964);
    AnalyzeFile("QCD_HT1500to2000", "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"           , 0.365085);
    AnalyzeFile("QCD_HT2000toInf",  "/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver3.hasJetE/QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root"            , 0.155885);
    */
}

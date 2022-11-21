#ifndef __xPhotonBinning_h__
#define __xPhotonBinning_h__
void PrintHelp();

const char* GetJsonFromArg( int argc, char** argv );
struct JsonInfo
{
    JsonInfo( const char* jsonfile );
    JsonInfo( int argc, char** argv ) : JsonInfo( GetJsonFromArg(argc,argv) ) {}

    std::string dataEra;
    std::string outputfilename;
    std::vector<std::string> inputfiles;
};

struct record_BinnedXPhoton
{
    Int_t bin_phopt, bin_phoeta, bin_jeteta, bin_phoHLT, region_pho;
    Int_t bin_matchedphostat, bin_evtparity, bin_jetflvr;
    Int_t jetSel;
    Int_t isMatched;


    Float_t mva, calib_mva, phoIsoRaw, chIsoRaw, calib_chIsoRaw, 
            btag_BvsAll, btag_CvsL, btag_CvsB, btag_secvtxmass;
    Float_t w_evt, w_central, w_up, w_down;
    void RegBranch( TTree* t );
    void Clear() { memset( this, 0x00, sizeof(record_BinnedXPhoton) ); }
};


const char* GetJsonFromArg( int argc, char** argv );
int main(int argc, char** argv);

#include <string>
#include <vector>
#define PHOREGION_NONE      0
#define PHOREGION_SIGNAL    1
#define PHOREGION_SIDEBAND -1
namespace BinningMethod
{
    std::vector<float> ptranges( std::string dataera );
    Int_t PtBin(const std::vector<float>& ptranges, float pt);
    Int_t EtaBin(float eta);
    Int_t JetBin(float jetY, float jetpt);
    Int_t HLTBin(int ptbin, std::string dataera);
    // jetflvr bin : 0=light, 1=c-jet, 2=b-jet
    Int_t JetFlavourBin( int jethadflvr );

    // -1 : sideband region, 1 : signal region, 0 : others
    //Int_t SignalPhoton(float isovar, bool isEndcap);
    Int_t SignalPhoton(float isovar, float eta);
    // 2: fake contribution in signal region of QCD sample.
    // 3: fake contribution in sideband region of QCD sample.
    // 4: all other contribution in QCD sample.
    // 0: contribution in signal region in data OR
    //    signal contribution in signal region in signal MC.
    // 1: trash can from other index.
    Int_t PhoMatchStatus( TreeReader* data );
};

class EventFragmentCollector
{
    public:
    EventFragmentCollector() {}
    void PhoPtBinnings(const std::vector<float>& pts) { _ptrange = pts; }
    //int phoPtBin( float pt ) { return BinningMethod::PtBin(pt, _ptrange); }
    
    bool passedPhoSelection(TreeReader* data); // building
    bool passedJetSelection(TreeReader* data); // building
    void recordEvent(TreeReader* data, record_BinnedXPhoton& ovar); // building
    void SetEvtIdx(Long64_t ev) { _eventRec = ev; }
    
    std::vector<float> _ptrange;
    private:
    int _eventRec;
};
#endif

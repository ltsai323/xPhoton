#ifndef __xPhotonBinning_h__
#define __xPhotonBinning_h__
void PrintHelp();

const char* GetJsonFromArg( int argc, char** argv );
struct JsonInfo
{
    JsonInfo( const char* jsonfile );
    JsonInfo( int argc, char** argv ) : JsonInfo( GetJsonFromArg(argc,argv) ) {}

    unsigned nJobs;
    std::string dataEra;
    std::string outputfilename;
    std::vector<std::string> inputfiles;
};

struct record_BinnedXPhoton
{
    Int_t hi;

    Float_t jj;
    void RegBranch( TTree* t );
    void Clear() { memset( this, 0x00, sizeof(record_BinnedXPhoton) ); }
};


const char* GetJsonFromArg( int argc, char** argv );
int main(int argc, char** argv);
#endif

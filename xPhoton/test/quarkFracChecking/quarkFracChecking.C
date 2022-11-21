#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"

#include <iostream>
#include <vector>


using namespace std;

void quarkFracChecking(const char* filename, const char* ofname)
{
    TFile* fin = TFile::Open(filename);
    TTree* tin = (TTree*) fin->Get("ggNtuplizer/EventTree");

    TFile* fout = new TFile(ofname, "RECREATE");
    fout->cd();

    
}
void quarkFracChecking()
{
    quarkFracChecking("/wk_cms2/ltsai/CRABdata/bkg_QCD_madgraph/QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8/crab_crab_bkgMC_QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2/210620_030459/0000/ggtree_mc_18.root");
}

#include <TTree.h>
#include <TFile.h>
#include <TKey.h>
#include <TROOT.h>
#include <TH1.h>
#include <TH2.h>
#include <TNtupleD.h>
#include <TNtuple.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/puweicalc.h"
#include "xPhoton/xPhoton/interface/ExternalFilesMgr.h"
// usage :
//   ./exec_thisfile 3.14e5 200 35.9 input.root outfile.root

void PrintHelp()
{
    printf("--------------------------------------------------\n");
    printf("------ Used to update cross section.      --------\n");
    printf("------ Arguments :                        --------\n");
    printf("------ 1. input root file                 --------\n");
    printf("------ 2. output root file                --------\n");
    printf("--------------------------------------------------\n");
}
const char* GetInputFile(const char* argv[])
{ return argv[1]; }
const char* GetOutputFile(const char* argv[])
{ return argv[2]; }
    
void CheckArgs(int argc, const char* argv[])
{
    if ( argc < 2+1 )
    { PrintHelp(); throw std::invalid_argument(" --- Need at least 2 input arguments ---\n"); }
}


void CloneOtherObjects(TFile* iF)
{
    TIter keyList(iF->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)keyList())) {
        if ( key->GetName() == std::string("t") ) continue;
        if ( key->ReadObj()->IsZombie() ) continue;
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if      (cl->InheritsFrom("TNtupleD"))
            ((TNtupleD*)key->ReadObj())->CloneTree(-1)->Write();
        else if (cl->InheritsFrom("TNtuple"))
            ((TNtuple* )key->ReadObj())->CloneTree(-1)->Write();
        else if (cl->InheritsFrom("TTree"))
            continue;
        else
            key->ReadObj()->Write();
    }
}


//#define BUG(format, args...)     fprintf(stderr, "---------------------debug-    %s  \n  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)
#define BUG(format, args...)
#define INFO(format, args...)     fprintf(stderr, "---------------------info -    %s  \n  >>  " format "\n", __PRETTY_FUNCTION__,  ##args)
bool JetPtSel_RemoveLowStatSample(TH1* h, float pt);
float ReweightedHT(TH1* h, float gen_ht);
int main(int argc, const char* argv[])
{
    CheckArgs(argc,argv);
    const char* iFile               = GetInputFile(argv);
    const char* oFile               = GetOutputFile(argv);

    // used variables
    Float_t puwei=1.;
    

    TFile* iF = TFile::Open(iFile);
    TTree* iT = (TTree*) iF->Get("t");

    // disable branch
    iT->SetBranchStatus("puwei", 0);

    Int_t invar_run = 0;
    iT->SetBranchAddress("run", &invar_run);
    
    TFile* oF = new TFile(oFile,"recreate");
    oF->cd();
    TTree* oT = (TTree*) iT->CloneTree(0);
    oT->Branch("puwei", &puwei, "puwei/F");

    PUWeightCalculator puCalc;
    const std::string dataEra = "UL2016PreVFP";
    const char* pufile = ExternalFilesMgr::RooFile_PileUp(dataEra);
    INFO("Using PU file : %s",pufile);
    puCalc.Init(pufile);

    unsigned int nevt = iT->GetEntries();
    for ( unsigned int ievt = 0; ievt <= nevt; ++ievt )
    {
        iT->GetEntry(ievt);

        
        //// abandoned. Because there is no puTrue in formation in xPhoton.
        //puwei = puCalc.GetWeight(run_, puTrue[1]); // in-time PU
        // not exit the code
        //if ( puwei > 5. ) { std::cout << Form("at entry %llu. Here finds weird puwei = %f\n", ev, puwei); }

        oT->Fill();
    }

    oF->cd();
    oT->Write();
    CloneOtherObjects(iF);

    oF->Close();
    iF->Close();

    return 0;
}

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
#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
// usage :
//   ./exec_thisfile 3.14e5 200 35.9 input.root outfile.root

void PrintHelp()
{
    printf("--------------------------------------------------\n");
    printf("------ Used to update cross section.      --------\n");
    printf("------ Arguments :                        --------\n");
    printf("------ 1. cross section value of MC       --------\n");
    printf("------ 2. integrated gen weights in MC    --------\n");
    printf("------ 3. input integrated luminosity     --------\n");
    printf("------ 4. input root file                 --------\n");
    printf("------ 5. output root file                --------\n");
    printf("--------------------------------------------------\n");
    printf("------ Feature : 1. Add Xsec info         --------\n");
    printf("------           2. xsweight = xs         --------\n");
    printf("------           3. overall genweight =   --------\n");
    printf("------              integrated gen weight --------\n");
    printf("------           4. lumi = data luminosity--------\n");
    printf("------           5. mcweight = luminosity --------\n");
    printf("------              * cross section of MC --------\n");
    printf("------              * gen weight each evt --------\n");
    printf("------              / integrated gen W    --------\n");
    printf("--------------------------------------------------\n");
}
float GetWeight(const char* argv[])
{ return atof(argv[1]); }
float GetIntegratedGenWeight(const char* argv[])
{ return atof(argv[2]); }
float GetIntegratedLuminosity(const char* argv[])
{ return atof(argv[3]); }
const char* GetInputFile(const char* argv[])
{ return argv[4]; }
const char* GetOutputFile(const char* argv[])
{ return argv[5]; }
void CheckArgs(int argc, const char* argv[])
{
    if ( argc != 6 )
    { PrintHelp(); throw std::invalid_argument(" --- Need 5 input arguments ---\n"); }
}




int main(int argc, const char* argv[])
{
    CheckArgs(argc,argv);
    const char* iFile = GetInputFile(argv);
    const char* oFile = GetOutputFile(argv);
    const float new_xs = GetWeight(argv);
    const float integratedGenWeight = GetIntegratedGenWeight(argv);
    const float integratedLumi = GetIntegratedLuminosity(argv);
    std::cout << "in file : " << iFile << std::endl;
    std::cout << "out file : " << oFile << std::endl;
    std::cout << "in x-sec : " << new_xs << std::endl;
    std::cout << "input integrated genweights : " << integratedGenWeight << std::endl;
    std::cout << "input integrated luminosity : " << integratedLumi << std::endl;
    

    TFile* iF = TFile::Open(iFile);
    TTree* iT = (TTree*) iF->Get("t");
    iT->SetBranchStatus("xsweight", 0);

    
    TFile* oF = new TFile(oFile,"recreate");
    oF->cd();
    TTree* oT = (TTree*) iT->CloneTree(0);

    Float_t xsweight;
    Float_t lumi;
    Float_t xs;
    Float_t mcweight;
    Float_t sumGenWeight;
    oT->Branch("xsweight", &xsweight, "xsweight/F"); // xsweight is the variable serve for original RS code.
    oT->Branch("crossSection", &xs, "crossSection/F");
    oT->Branch("integratedLuminosity", &lumi, "integratedLuminosity/F");
    oT->Branch("integratedGenWeight", &sumGenWeight, "integratedGenWeight/F");
    oT->Branch("mcweight", &mcweight, "mcweight/F");

    Float_t genweight;

    iT->SetBranchAddress("genWeight", &genweight);

    xs = new_xs;
    lumi = integratedLumi;
    sumGenWeight = integratedGenWeight;
    
    
    unsigned int nevt = iT->GetEntries();
    for ( unsigned int ievt = 0; ievt <= nevt; ++ievt )
    {
        iT->GetEntry(ievt);

        xsweight = genweight > 0 ? new_xs : -1.*new_xs;
        mcweight = new_xs * lumi * genweight / integratedGenWeight;

        oT->Fill();
    }

    oT->Write();
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
    oF->Close();
    iF->Close();

    return 0;
}

#include <TTree.h>
#include <TFile.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
// usage :
//   ./exec_thisfile input.root outfile.root 3.283
void PrintHelp()
{
    printf("---------------------------------------------\n");
    printf("------ Used to update cross section. --------\n");
    printf("------ Arguments :                   --------\n");
    printf("------ 1. cross section value of MC  --------\n");
    printf("------ 2. input root file            --------\n");
    printf("------ 3. output root file           --------\n");
    printf("---------------------------------------------\n");
    printf("------ Feature : 1. Add Xsec info    --------\n");
    printf("------           2. Scale Factor of  --------\n");
    printf("------              jet to calibrate --------\n");
    printf("------              BTagging.        --------\n");
    printf("---------------------------------------------\n");
}
float GetWeight(const char* argv[])
{ return atof(argv[1]); }
const char* GetInputFile(const char* argv[])
{ return argv[2]; }
const char* GetOutputFile(const char* argv[])
{ return argv[3]; }
void CheckArgs(int argc, const char* argv[])
{
    if ( argc != 4 )
    { PrintHelp(); throw std::invalid_argument(" --- Need 3 input arguments ---\n"); }
}



int main(int argc, const char* argv[])
{
    CheckArgs(argc,argv);
    const char* iFile = GetInputFile(argv);
    const char* oFile = GetOutputFile(argv);
    const float new_xsweight = GetWeight(argv);
    std::cout << "in file : " << iFile << std::endl;
    std::cout << "out file : " << oFile << std::endl;
    std::cout << "in xs weight : " << new_xsweight << std::endl;
    

    TFile* iF = TFile::Open(iFile);
    TTree* iT = (TTree*) iF->Get("t");
    
    TFile* oF = new TFile(oFile,"recreate");
    oF->cd();
    TTree* oT = (TTree*) iT->CloneTree(0);
    BTaggingMgr btagCalibs;
    btagCalibs.UseAlgorithm( "CSVv2" );
    btagCalibs.UseAlgorithm( "DeepCSV" );
    btagCalibs.UseAlgorithm( "DeepFlavour" );
    btagCalibs.UseAlgorithm( "DeepFlavour_JESReduced" );
    btagCalibs.RegisterSystTypes();

    float xsweight;
    oT->SetBranchStatus("xsweight", 0);
    oT->Branch("xsweight", &xsweight, "xsweight/F");

    float jetPt, jetEta;
    oT->SetBranchAddress("recoPt" , &jetPt);
    oT->SetBranchAddress("recoEta", &jetEta);
    btagCalibs.RegBranch(oT);

    xsweight = new_xsweight;
    
    unsigned int nevt = iT->GetEntries();
    for ( unsigned int ievt = 0; ievt <= nevt; ++ievt )
    {
        btagCalibs.InitVars();
        iT->GetEntry(ievt);
        btagCalibs.FillWeightToEvt(jetPt,jetEta);
        
        oT->Fill();
    }

    oT->Write();
    oF->Close();
    iF->Close();

    return 0;
}

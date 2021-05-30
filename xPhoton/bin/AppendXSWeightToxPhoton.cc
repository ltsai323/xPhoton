#include <TTree.h>
#include <TFile.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdexcept>
// usage :
//   ./exec_thisfile input.root outfile.root 3.283
void PrintHelp()
{
    printf("---------------------------------------------\n");
    printf("------ Used to update cross section. --------\n");
    printf("------ Arguments :                   --------\n");
    printf("------ 1. input root file            --------\n");
    printf("------ 2. output root file           --------\n");
    printf("-------3. cross section value of MC  --------\n");
    printf("---------------------------------------------\n");
}
float GetWeight(const char* argv[])
{ return atof(argv[3]); }
const char* GetInputFile(const char* argv[])
{ return argv[1]; }
const char* GetOutputFile(const char* argv[])
{ return argv[2]; }
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

    float xsweight;
    oT->SetBranchStatus("xsweight", 0);
    oT->Branch("xsweight", &xsweight, "xsweight/F");
    xsweight = new_xsweight;
    
    
    for ( unsigned int ievt = 0; ievt <= iT->GetEntries(); ++iT )
    { iT->GetEntry(ievt); oT->Fill(); }

    oT->Write();
    oF->Close();
    iF->Close();

    return 0;
}

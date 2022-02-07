#include <TTree.h>
#include <TFile.h>
#include <stdlib.h>
#include <stdio.h>
#include <TKey.h>
#include <TROOT.h>
#include <TH2.h>
#include <TH1.h>
#include <TNtuple.h>
#include <TNtupleD.h>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <memory>
#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
// usage :
//   ./exec_thisfile 2016ReReco input.root outfile.root
bool useDeepCSV = true;
bool useDeepJet = true;
std::vector<const char*> validEra = {
    "2016ReReco",
    "2017ReReco",
    "2018ReReco",
    "UL2016"    ,
    "UL2017"    ,
    "UL2018"    ,
};

void PrintHelp()
{
    printf("---------------------------------------------\n");
    printf("------ Used to update BTag scale factor -----\n");
    printf("------ Arguments :                   --------\n");
    printf("------ 2. data era. Supported words: --------\n");
    for ( const char* validera : validEra )
        printf("------    %20s       --------\n", validera);
    printf("------ 3. input root file            --------\n");
    printf("------ 4. output root file           --------\n");
    printf("---------------------------------------------\n");
    printf("------ Feature :    Scale Factor of  --------\n");
    printf("------              jet to calibrate --------\n");
    printf("------              BTagging.        --------\n");
    printf("---------------------------------------------\n");
}
const char* Arg_DataEra(const char* argv[])
{ return argv[1]; }
const char* Arg_InputFile(const char* argv[])
{ return argv[2]; }
const char* Arg_OutputFile(const char* argv[])
{ return argv[3]; }
bool EraCheck(const char* inputera)
{
    for ( const char* validera : validEra )
        if ( strcmp(inputera,validera) == 0 ) return true;
    return false;
}
void CheckArgs(int argc, const char* argv[])
{
    if ( argc != 4 )
    { PrintHelp(); throw std::invalid_argument(" --- Need 4 input arguments ---\n"); }
    if (!EraCheck( Arg_DataEra(argv) ) ) { PrintHelp(); throw std::invalid_argument("\n\n### input data era is invalid ###\n"); }
}



int main(int argc, const char* argv[])
{
    CheckArgs(argc,argv);
    const char* iFile = Arg_InputFile(argv);
    const char* oFile = Arg_OutputFile(argv);
    const char* era   = Arg_DataEra(argv);

    std::cout << "in file : " << iFile << std::endl;
    std::cout << "out file : " << oFile << std::endl;
    std::cout << "updating BTagging scale factors" << std::endl;
    

    TFile* iF = TFile::Open(iFile);
    TTree* iT = (TTree*) iF->Get("t");
    
    TFile* oF = new TFile(oFile,"recreate");
    oF->cd();
    TTree* oT = (TTree*) iT->CloneTree(0);
    

    std::map<const char*, std::shared_ptr<BTaggingMgr>> btagCalibs;
    if ( useDeepCSV ) btagCalibs["deepcsv"] = std::unique_ptr<BTaggingMgr>(new BTaggingMgr_DeepCSV    ("2016ReReco"));
    if ( useDeepJet ) btagCalibs["deepjet"] = std::unique_ptr<BTaggingMgr>(new BTaggingMgr_DeepFlavour("2016ReReco"));


    Float_t jetPt, jetEta;
    Float_t deepcsv_b, deepcsv_bb;
    Float_t deepjet_b, deepjet_bb, deepjet_lepb;
    Int_t flavour;
    iT->SetBranchAddress("jetPt",     &jetPt);
    iT->SetBranchAddress("jetEta",    &jetEta);
    iT->SetBranchAddress("jetHadFlvr", &flavour);
    iT->SetBranchAddress("jetDeepCSVTags_b" ,&deepcsv_b);
    iT->SetBranchAddress("jetDeepCSVTags_bb",&deepcsv_bb);

    iT->SetBranchAddress("jetDeepFlavourTags_b"   ,&deepjet_b);
    iT->SetBranchAddress("jetDeepFlavourTags_bb"  ,&deepjet_bb);
    iT->SetBranchAddress("jetDeepFlavourTags_lepb",&deepjet_lepb);

    if ( useDeepCSV ) btagCalibs["deepcsv"]->RegBranch(oT);
    if ( useDeepJet ) btagCalibs["deepjet"]->RegBranch(oT);

    
    unsigned int nevt = iT->GetEntries();
    for ( unsigned int ievt = 0; ievt <= nevt; ++ievt )
    {
        iT->GetEntry(ievt);

        if ( jetPt > 10 )
        {
            if ( useDeepCSV ) btagCalibs["deepcsv"]->InitVars();
            if ( useDeepJet ) btagCalibs["deepjet"]->InitVars();
            if ( useDeepCSV ) btagCalibs["deepcsv"]->FillWeightToEvt(jetPt,jetEta, flavour, deepcsv_b+deepcsv_bb);
            if ( useDeepJet ) btagCalibs["deepjet"]->FillWeightToEvt(jetPt,jetEta, flavour, deepjet_b+deepjet_bb+deepjet_lepb);
        }

        oT->Fill();
    }
    std::cout << "end of evt loop\n";

    std::cout << "       tree writing\n";
    oT->Write();
    std::cout << "end of tree writing\n";
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

    std::cout << "end of main function\n";
    return 0;
}

#include <TTree.h>
#include <TFile.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <stdexcept>
#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
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
    iT->SetBranchStatus("xsweight", 0);
    
    TFile* oF = new TFile(oFile,"recreate");
    oF->cd();
    TTree* oT = (TTree*) iT->CloneTree(0);
    //BTaggingMgr btagCalibsDeepCSV;
    //BTaggingMgr btagCalibsDeepFlavour;
    //BTaggingMgr btagCalibsDeepFlavour_JESReduced;;

    //btagCalibsDeepCSV.UseAlgorithm( "DeepCSV" );
    //btagCalibsDeepFlavour.UseAlgorithm( "DeepFlavour" );
    //btagCalibsDeepFlavour_JESReduced.UseAlgorithm( "DeepFlavour_JESReduced" );


    //btagCalibsDeepCSV.RegisterSystTypes();
    //btagCalibsDeepFlavour.RegisterSystTypes();
    //btagCalibsDeepFlavour_JESReduced.RegisterSystTypes();

    Float_t xsweight;
    //oT->SetBranchStatus("xsweight", 0);
    oT->Branch("xsweight", &xsweight, "xsweight/F");

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
    //btagCalibsDeepCSV.RegBranch(oT);
    //btagCalibsDeepFlavour.RegBranch(oT);
    //btagCalibsDeepFlavour_JESReduced.RegBranch(oT);

    xsweight = new_xsweight;
    
    unsigned int nevt = iT->GetEntries();
    for ( unsigned int ievt = 0; ievt <= nevt; ++ievt )
    {
        //btagCalibsDeepCSV.InitVars();
        //btagCalibsDeepFlavour.InitVars();
        //btagCalibsDeepFlavour_JESReduced.InitVars();
        iT->GetEntry(ievt);
        if ( jetPt < 10 )
        {
            oT->Fill();
            continue;
            // in this case, you cannot pass any event without Fill().
        }
        //btagCalibsDeepCSV.FillWeightToEvt(jetPt,jetEta, flavour, deepcsv_b+deepcsv_bb);
        //btagCalibsDeepFlavour.FillWeightToEvt(jetPt,jetEta, flavour, deepjet_b+deepjet_bb+deepjet_lepb);
        //btagCalibsDeepFlavour_JESReduced.FillWeightToEvt(jetPt,jetEta, flavour, deepjet_b+deepjet_bb+deepjet_lepb);

        oT->Fill();
    }

    oT->Write();
    oF->Close();
    iF->Close();

    return 0;
}

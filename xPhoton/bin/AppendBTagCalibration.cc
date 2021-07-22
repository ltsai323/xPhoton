#include <TTree.h>
#include <TFile.h>
#include <stdlib.h>
#include <stdio.h>
#include <TKey.h>
#include <TROOT.h>
#include <TH2.h>
#include <TH1.h>
#include <TNtuple.h>
#include <iostream>
#include <stdexcept>
#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
// usage :
//   ./exec_thisfile input.root outfile.root 3.283
bool useDeepCSV = false;
bool useDeepJet = false;

void PrintHelp()
{
    printf("---------------------------------------------\n");
    printf("------ Used to update BTag scale factor -----\n");
    printf("------ Arguments :                   --------\n");
    printf("------ 2. input root file            --------\n");
    printf("------ 3. output root file           --------\n");
    printf("---------------------------------------------\n");
    printf("------ Feature :    Scale Factor of  --------\n");
    printf("------              jet to calibrate --------\n");
    printf("------              BTagging.        --------\n");
    printf("---------------------------------------------\n");
}
/*
float GetWeight(const char* argv[])
{ return atof(argv[1]); }
*/
const char* GetInputFile(const char* argv[])
{ return argv[1]; }
const char* GetOutputFile(const char* argv[])
{ return argv[2]; }
void CheckArgs(int argc, const char* argv[])
{
    if ( argc != 3 )
    { PrintHelp(); throw std::invalid_argument(" --- Need 3 input arguments ---\n"); }
}



int main(int argc, const char* argv[])
{
    CheckArgs(argc,argv);
    const char* iFile = GetInputFile(argv);
    const char* oFile = GetOutputFile(argv);

    std::cout << "in file : " << iFile << std::endl;
    std::cout << "out file : " << oFile << std::endl;
    std::cout << "updating BTagging scale factors" << std::endl;
    

    TFile* iF = TFile::Open(iFile);
    TTree* iT = (TTree*) iF->Get("t");
    
    TFile* oF = new TFile(oFile,"recreate");
    oF->cd();
    TTree* oT = (TTree*) iT->CloneTree(0);
    BTaggingMgr btagCalibsDeepCSV;
    BTaggingMgr btagCalibsDeepFlavour;
    BTaggingMgr btagCalibsDeepFlavour_JESReduced;;

    if ( useDeepCSV ) btagCalibsDeepCSV.UseAlgorithm( "DeepCSV" );
    if ( useDeepJet ) btagCalibsDeepFlavour.UseAlgorithm( "DeepFlavour" );
    if ( useDeepJet ) btagCalibsDeepFlavour_JESReduced.UseAlgorithm( "DeepFlavour_JESReduced" );


    if ( useDeepCSV ) btagCalibsDeepCSV.RegisterSystTypes();
    if ( useDeepJet ) btagCalibsDeepFlavour.RegisterSystTypes();
    if ( useDeepJet ) btagCalibsDeepFlavour_JESReduced.RegisterSystTypes();


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
    if ( useDeepCSV ) btagCalibsDeepCSV.RegBranch(oT);
    if ( useDeepJet ) btagCalibsDeepFlavour.RegBranch(oT);
    if ( useDeepJet ) btagCalibsDeepFlavour_JESReduced.RegBranch(oT);

    
    unsigned int nevt = iT->GetEntries();
    for ( unsigned int ievt = 0; ievt <= nevt; ++ievt )
    {
        iT->GetEntry(ievt);

        if ( jetPt > 10 )
        {
            if ( useDeepCSV ) btagCalibsDeepCSV.InitVars();
            if ( useDeepJet ) btagCalibsDeepFlavour.InitVars();
            if ( useDeepJet ) btagCalibsDeepFlavour_JESReduced.InitVars();
            if ( useDeepCSV ) btagCalibsDeepCSV.FillWeightToEvt(jetPt,jetEta, flavour, deepcsv_b+deepcsv_bb);
            if ( useDeepJet ) btagCalibsDeepFlavour.FillWeightToEvt(jetPt,jetEta, flavour, deepjet_b+deepjet_bb+deepjet_lepb);
            if ( useDeepJet ) btagCalibsDeepFlavour_JESReduced.FillWeightToEvt(jetPt,jetEta, flavour, deepjet_b+deepjet_bb+deepjet_lepb);
        }

        oT->Fill();
    }

    oT->Write();
    TIter keyList(iF->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)keyList())) {
        if ( (key->GetName()) == "t" ) continue;
        if ( key->ReadObj()->IsZombie() ) continue;
        TClass *cl = gROOT->GetClass(key->GetClassName());
        if (cl->InheritsFrom("TH1"))
            ((TH1*     )key->ReadObj())->Write();
        /*
        if (cl->InheritsFrom("TNtupleD"))
            ((TNtupleD*)key->ReadObj())->Write();
            */
        if (cl->InheritsFrom("TNtuple"))
            ((TNtuple* )key->ReadObj())->Write();
        if (cl->InheritsFrom("TH2"))
            ((TH2*     )key->ReadObj())->Write();
    }
    oF->Close();
    iF->Close();

    return 0;
}

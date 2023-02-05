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
#include <algorithm>
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/BTaggingMgr.h"
#include "xPhoton/xPhoton/interface/CTaggingMgr.h"
// usage :
//   ./exec_thisfile 2016ReReco input.root outfile.root
bool useDeepCSV = true;
bool useDeepJet = true;
std::vector<const char*> validEra = {
    "2016ReReco",
    "2017ReReco",
    "2018ReReco",
    // UL2016 is invalid
    "UL2016PostVFP",
    "UL2016PreVFP",
    "UL2017",
    "UL2018"
};

void PrintHelp()
{
    printf("---------------------------------------------\n");
    printf("------ Used to update CTag scale factor -----\n");
    printf("------ Arguments :                   --------\n");
    printf("------ 2. data era. Supported words: --------\n");
    for ( const char* validera : validEra )
        printf("------    %20s       --------\n", validera);
    printf("------ 3. input root file            --------\n");
    printf("------ 4. output root file           --------\n");
    printf("------ 5. need to clean up branch    --------\n");
    printf("---------------------------------------------\n");
    printf("------ Feature :    Scale Factor of  --------\n");
    printf("------              jet to calibrate --------\n");
    printf("------              CTagging.        --------\n");
    printf("---------------------------------------------\n");
}
const char* Arg_DataEra(const char* argv[])
{ return argv[1]; }
const char* Arg_InputFile(const char* argv[])
{ return argv[2]; }
const char* Arg_OutputFile(const char* argv[])
{ return argv[3]; }
bool Arg_CleanUpBranch(int argc, const char* argv[])
{
    if ( argc < 5 ) return false;
    std::string words(argv[4]);
    std::for_each( words.begin(), words.end(), [](char& c) {c = ::tolower(c);} );
    if ( words == "true" || words == "1" ) return true;
    return false;
}
bool EraCheck(const char* inputera)
{
    for ( const char* validera : validEra )
        if ( strcmp(inputera,validera) == 0 ) return true;
    return false;
}
void CheckArgs(int argc, const char* argv[])
{
    if ( argc < 4 )
    { PrintHelp(); throw std::invalid_argument(" --- Need at least 4 input arguments ---\n"); }
    if (!EraCheck( Arg_DataEra(argv) ) ) { PrintHelp(); throw std::invalid_argument("\n\n### input data era is invalid ###\n"); }
}
// ReReco : old format csv file. UL : new format csv file
bool UseNewFormat(const char* inputera)
{
    int eraIdx = -1;
    for ( unsigned int idx = 0; idx < validEra.size() ; ++idx )
        if ( strcmp(inputera,validEra[idx]) == 0 ) eraIdx = idx;
    return eraIdx > 2;
}



int main(int argc, const char* argv[])
{
    CheckArgs(argc,argv);
    const char* iFile = Arg_InputFile(argv);
    const char* oFile = Arg_OutputFile(argv);
    const char* era   = Arg_DataEra(argv);
    //bool CleanUpNeeded = Arg_CleanUpBranch(argc,argv);

    std::cout << "data era : " << era << std::endl;
    std::cout << "in file : " << iFile << std::endl;
    std::cout << "out file : " << oFile << std::endl;
    std::cout << "updating CTagging scale factors" << std::endl;
    

    TFile* iF = TFile::Open(iFile);
    TTree* iT = (TTree*) iF->Get("t");

    Float_t jetPt = 0;
    iT->SetBranchAddress("jetPt", &jetPt);
    
    

    std::map<const char*, std::shared_ptr<CTaggingMgr>> ctagCalibs;
    if ( useDeepCSV )
    {
        ctagCalibs["deepcsv"] = std::unique_ptr<CTaggingMgr>(new CTaggingMgr_DeepCSV    (era));
        //if ( CleanUpNeeded ) { printf("old branch cleaned\n"); ctagCalibs["deepcsv"]->DisableBranch(iT); }
    }
    if ( useDeepJet )
    {
        ctagCalibs["deepjet"] = std::unique_ptr<CTaggingMgr>(new CTaggingMgr_DeepFlavour(era));
        //if ( CleanUpNeeded ) { printf("old branch cleaned\n"); ctagCalibs["deepjet"]->DisableBranch(iT); }
    }



    TFile* oF = new TFile(oFile,"recreate");
    oF->cd();
    TTree* oT = (TTree*) iT->CloneTree(0);

    if ( useDeepCSV ) ctagCalibs["deepcsv"]->SetBranchAddress(iT);
    if ( useDeepJet ) ctagCalibs["deepjet"]->SetBranchAddress(iT);
    if ( useDeepCSV ) ctagCalibs["deepcsv"]->RegBranch(oT);
    if ( useDeepJet ) ctagCalibs["deepjet"]->RegBranch(oT);


    
    unsigned int nevt = iT->GetEntries();
    float totevtnum = 0.;
    float totweig_DeepCSV = 0.;
    float totweig_DeepJet = 0.;
    for ( unsigned int ievt = 0; ievt <= nevt; ++ievt )
    {
        iT->GetEntry(ievt);

        if ( jetPt > 10 )
        {
            if ( useDeepCSV )
            { ctagCalibs["deepcsv"]->FillBranch(); totweig_DeepCSV += ctagCalibs["deepcsv"]->GetWeight(); }
            if ( useDeepJet )
            { ctagCalibs["deepjet"]->FillBranch(); totweig_DeepJet += ctagCalibs["deepcsv"]->GetWeight(); }
            totevtnum++;
        }

    }

    double overallweight_DeepCSV = double(totevtnum) / double(totweig_DeepCSV);
    double overallweight_DeepJet = double(totevtnum) / double(totweig_DeepJet);
    for ( unsigned int ievt = 0; ievt <= nevt; ++ievt )
    {
        iT->GetEntry(ievt);

        if ( jetPt > 10 )
        {
            if ( useDeepCSV ) ctagCalibs["deepcsv"]->FillBranch(overallweight_DeepCSV);
            if ( useDeepJet ) ctagCalibs["deepjet"]->FillBranch(overallweight_DeepJet);
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



// float CTaggingWeight()
// {
//     TFile *wtFile = new TFile(SFrootfilename);
//     TH2F *cWtHist = (TH2F*)wtFile->Get("SFc_hist");   //For systematic variations, one can concatenate a string after "SFc_hist"
//     TH2F *bWtHist = (TH2F*)wtFile->Get("SFb_hist");
//     TH2F *lWtHist = (TH2F*)wtFile->Get("SFl_hist");
// 
//     float ctagWt = 1.;
//     int flav, xbin, ybin;
//     float CvsLval,CvsBval,jetpT;
//     TH2F *wtHist;
//     for (int ij=0; ij<jet_nJet;ij++) {
//         flav = int(jet_hadronFlv[ij]);
//         CvsLval = jet_CvsL[ij];
//         CvsBval = jet_CvsB[ij];
//         jetpT = jet_Pt[ij];
//         if (flav == 4) {
//             wtHist = cWtHist;
//         }
//         else if (flav == 5) {
//             wtHist = bWtHist;
//         }
//         else {
//             wtHist = lWtHist;
//         }
// 
//         xbin = wtHist->GetXaxis()->FindBin(CvsLval);
//         ybin = wtHist->GetYaxis()->FindBin(CvsBval);
//         ctagWt *= wtHist->GetBinContent(xbin,ybin); // asdf 
//     }
//     return ctagWt;
// }



// note:
//   weight -404 : input file not found
//
//
// question:
//   * If I used a TotalUp error to calculate up weight. w_err * w or w_err used?
//   * If 2 jets are selected in one event, do I need to multiplied them? (asdf)
//   * Is the weight normalization able to be calculated slice by slice?

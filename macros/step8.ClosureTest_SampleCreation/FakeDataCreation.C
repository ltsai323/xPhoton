#include <stdio.h>
#include <exception>
#include "TTree.h"
#include "TFile.h"
const int nFile = 10;

const char* GJet_madgraph()
{ return "/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root"; }
const char* QCD_madgraph()
{ return "/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root"; }

bool SigPhotonSelection(int isMatched, float chIso)
{ return isMatched == 1 && chIso<2; }
bool BkgPhotonSelection(int isMatched, float chIso)
{ return isMatched != 1; }
typedef bool (*FunctionalSelection) (int, float);

TTree* skim( TTree* tree, Long64_t fromEvt_, Long64_t toEvt_, FunctionalSelection InterestedEvt) {
    if ( toEvt_ < 0 ) toEvt_ = tree->GetEntries();

    int isMatched;
    Float_t chIso;
    tree->SetBranchAddress("isMatched", &isMatched);
    tree->SetBranchAddress("chIsoRaw", &chIso);
    tree->SetBranchStatus("*",1);

    TTree *newtree = tree->CloneTree(0);

    for (Long64_t n=fromEvt_; n<toEvt_; n++) {
        tree->GetEntry(n);

        if ( InterestedEvt(isMatched, chIso) ) newtree->Fill();
    }

    return newtree;
}

enum catIdx { sig, bkg, totnum };
const char* cattag[] = { "sig", "bkg" };
const int totnumC = 2;

const char* Generalized_LoadFile( int cat )
{
    switch ( cat )
    {
        case catIdx::sig: return GJet_madgraph();
        case catIdx::bkg: return  QCD_madgraph();
    }
    char mesg[150];
    sprintf( mesg, "Generalized_LoadFile(). Generalization failed. Input category %d is out of range\n", cat );
    throw std::range_error(mesg);
}
FunctionalSelection Generalized_EvtCriteria( int cat )
{
    switch ( cat )
    {
        case catIdx::sig : return SigPhotonSelection;
        case catIdx::bkg : return BkgPhotonSelection;
    }
    char mesg[150];
    sprintf( mesg, "Generalized_EvtCriteria(). Generalization failed. Input category %d is out of range\n", cat );
    throw std::range_error(mesg);
}



void FakeDataCreation()
{
    for ( int icat=0; icat<catIdx::totnum; ++icat )
    {
        TFile* fdata = TFile::Open( Generalized_LoadFile(icat) );
        TTree* tdata = (TTree*) fdata->Get("t");

        char outputfile[100];
        Long64_t totevt = tdata->GetEntries();
        Long64_t evtUnit = totevt / nFile;
        for ( int ifile = 0; ifile < nFile; ++ifile )
        {
            Long64_t fromevt = evtUnit * ifile;
            Long64_t   toevt = evtUnit * (ifile+1);

            sprintf( outputfile, "fakesample%d_%s.root", ifile, cattag[icat] );
            TFile* tnew = new TFile(outputfile, "recreate");
            TTree* tsig = skim(tdata, fromevt, toevt, Generalized_EvtCriteria(icat));
            printf( "fakesample %s @ bin%d gets entries = %lld\n", cattag[icat], ifile, tsig->GetEntries() );
            tsig->Write();
            tnew->Close();
        }
    }
}

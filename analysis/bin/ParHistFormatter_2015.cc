#include <iostream>
#include <vector>
#include <string>
//#include "/home/ltsai/Work/github/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/usefulFuncs.h"
#include "xPhoton/xPhoton/interface/LogMgr.h"
#include "xPhoton/xPhoton/interface/histMgr.h"
#include "xPhoton/xPhoton/interface/readMgr.h"
#include "xPhoton/xPhoton/interface/readContent_xPhoton.h"


#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <TH1F.h>
#include <string.h>

// usage : 
//   ./exec_this data myinputxPhoton.root hihi
//   which will get your ouptut as outputParHists_data_hihi.root

const int BINNING = 100;
// WARNING // HLT BIT needs to be checked at each file.
const int HLT_PHOTON_BIT=8; // For 2015



const char* ofiletemplate = "outputParHists_%s_%s.root";
char ofile[200];

bool selectedEvt(readMgr* data, const char* datatype)
{
    if ( strncmp(datatype, "data",  4) == 0 )                                        return true;
    if ( strncmp(datatype, "sigmc", 5) == 0 ) if ( data->Int(var::isMatched) == 1 )  return true;
    if ( strncmp(datatype, "bkgmc", 5) == 0 ) if ( data->Int(var::isMatched) ==-1 )  return true;
    return false;
}
//bool addPreselection

int main( int argc, char* argv[])
{
    if ( argc<3 ) LOG_FATAL("This program needs to have 2 arguments. First allows 'data'/'sigmc'/'bkgmc'. And second is input file path. Third one is output filename");

    const char* ifile = argv[2];
    if ( argc==4 ) sprintf( ofile, ofiletemplate, argv[1], argv[3] );
    else           sprintf( ofile, ofiletemplate, argv[1], "testsample");

    readMgr data(ifile, "t", varBRANCHES);
    TFile* fout = new TFile(ofile, "RECREATE");

    LOG_DEBUG("creating histograms");
    histMgr hists;
    hists.Create("HoverE"       ,      30, 0.,    0.15);
    hists.Create("sieieFull5x5" , BINNING, 0.,    0.05);
    hists.Create("sieipFull5x5" , BINNING, -0.20, 0.2 );
    hists.Create("phoIsoRaw"    , BINNING, 0.,   30.  );
    hists.Create("pt"           , BINNING, 0., 1000.  );
    hists.Create("phi"          , BINNING, -3.14, 3.14);
    hists.Create("eta"          , BINNING, -3.14, 3.14);
    hists.Create("chIsoRaw"     , BINNING, 0.,   15.  );
    hists.Create("nVtx"         , BINNING, 0.,   50.  );
    hists.Create("MET_pt"       , BINNING, 0.,    2.  );
    hists.Create("SCeta"        , BINNING, -3.14, 3.14);
    hists.Create("r9"           , BINNING, 0.,    1.1 );
    hists.Create("s4"           , BINNING, 0.,    1.1 );
    hists.Create("rawE"         , BINNING, 0., 2000.  );
    hists.Create("SCetaWidth"   , BINNING, 0.,    0.10);
    hists.Create("SCphiWidth"   , BINNING, 0.,    0.10);
    hists.Create("rho"          , BINNING, 0.,   50.  );
    hists.Create("mva"          ,      10,-1.,    1.  );
    hists.Create("mva_past"     ,     100,-1.,    1.  );


    hists.Create("MET_ptOVERphi", BINNING, -3.14, 3.14, BINNING, 0., 2.);

float binning[10]={0,200,300, 400, 500, 100000};
TH1F *h_gainCorr = new TH1F("h_gainCorr","correction due to gain switch", 5, binning);
h_gainCorr->SetBinContent(1,1.);      h_gainCorr->SetBinError(1,0.001);
h_gainCorr->SetBinContent(2,1./1.0199);	  h_gainCorr->SetBinError(2,0.001);
h_gainCorr->SetBinContent(3,1./1.052);	  h_gainCorr->SetBinError(3,0.003);
h_gainCorr->SetBinContent(4,1./1.015);	  h_gainCorr->SetBinError(4,0.006);
h_gainCorr->SetBinContent(5,1.);      h_gainCorr->SetBinError(5,0.001);  

    LOG_DEBUG("start looping event");
    
    bool checkevt = false;
    for (Long64_t ievt = 0; ievt < data.GetEntriesFast(); ievt++) 
    {
        data.GetEntry(ievt);

        // preselection start
        if (!usefulFuncs::isBarrel(data.Float(var::recoEta)) ) continue;
        //if ( data.Float(var::recoEta) > 1.4442 ) continue;
        //if ( data.Float(var::recoEta) <-1.4442 ) continue; // choose barrel only

        if ( data.GetBool("isData") )
            if (!(data.GetInt("phoFiredTrgs")>>HLT_PHOTON_BIT&1) ) continue;
        //if ( data.Float(var::chIsoRaw) > 2 ) continue;
        if ( data.Float(var::MET)/data.Float(var::recoPt) > 0.7 ) continue;
        if ( data.GetInt("run") == 256729 ) continue;
        if ( data.GetInt("run") == 256734 ) continue;

        float pt=data.Float(var::recoPt);
        hists.Fill("pt", pt);
        
if ( usefulFuncs::isBarrel(data.Float(var::recoEta)) )
{ // only for data and barrel
int bin1 =  h_gainCorr->FindBin( data.GetFloat("SeedEnergy") );
float factor = h_gainCorr->GetBinContent(bin1);
float calibPt = pt*1./factor;
if ( !(calibPt > 185. && calibPt < 190.) ) continue;
}




        // preselection end

        if (!selectedEvt(&data, argv[1]) ) continue;
        if (!checkevt ) checkevt=true;
        if ( ievt%10000 == 0 ) LOG_DEBUG("At evt %d", ievt);
        data.GetEntry(ievt);

        hists.Fill("HoverE"      , data.Float(var::HoverE            ));
        hists.Fill("sieieFull5x5", data.Float(var::sieieFull5x5      ));
        hists.Fill("sieipFull5x5", data.Float(var::sieipFull5x5      ));
        hists.Fill("phoIsoRaw"   , data.Float(var::phoIsoRaw         ));
        hists.Fill("phi"         , data.Float(var::recoPhi           ));
        hists.Fill("eta"         , data.Float(var::recoEta           ));
        hists.Fill("chIsoRaw"    , data.Float(var::chIsoRaw          ));
        hists.Fill("nVtx"        , data.Int  (var::nVtx              ));
        hists.Fill("MET_pt"      , data.Float(var::MET)/data.Float(var::recoPt));
        hists.Fill("SCeta"       , data.Float(var::recoSCEta         ));
        hists.Fill("r9"          , data.Float(var::r9                ));
        hists.Fill("s4"          , data.Float(var::e2x2Full5x5)/data.Float(var::e5x5Full5x5));
        hists.Fill("rawE"        , data.Float(var::rawE              ));
        hists.Fill("SCetaWidth"  , data.Float(var::scEtaWidth        ));
        hists.Fill("SCphiWidth"  , data.Float(var::scPhiWidth        ));
        hists.Fill("rho"         , data.Float(var::rho               ));
        hists.Fill("mva"         , data.Float(var::mva               ));
        hists.Fill("mva_past"    , data.Float(var::mva               ));

        hists.Fill("MET_ptOVERphi", data.Float(var::recoPhi),
                                       data.Float(var::MET)/data.Float(var::recoPt));
    }
    if (!checkevt ) LOG_WARNING("no event filled! Your input arg setting is '%s'. Please check", argv[1] );

    LOG_DEBUG("end of loopging event, start to fill everything into root file");
    hists.WriteTo(fout);

    fout->Write();
    fout->Close();
}

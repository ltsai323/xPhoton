#include <iostream>
#include <vector>
#include <string>
//#include "/home/ltsai/Work/github/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/untuplizer.h"
#include "xPhoton/xPhoton/interface/logger.h"
#include "xPhoton/xPhoton/interface/histMgr.h"
#include "xPhoton/xPhoton/interface/readMgr.h"
#include "xPhoton/xPhoton/interface/readContent_xPhoton.h"


#include <TFile.h>
#include <TTree.h>
#include <TH1.h>
#include <string.h>
const int BINNING = 100;




const char* ofiletemplate = "outputParHists_%s_%s.root";
char ofile[200];

bool passedEvt(readMgr* data, const char* datatype)
{
    if ( strcmp(datatype, "data") == 0 ) return true;
    if ( strcmp(datatype, "mcsig")== 0 )
        if ( data->Int(var::isMatched == 1 ) )  return true;
    if ( strcmp(datatype, "mcbkg")== 0 )
        if ( data->Int(var::isMatched ==-1 ) )  return true;
    return false;
}

int main( int argc, char* argv[])
{
    if ( argc<3 ) LOG_FATAL("This program needs to have 2 arguments. First allows 'data'/'mcsig'/'mcbkg'. And second is input file path. Third one is output filename");

    const char* ifile = argv[2];
    if ( argc==4 ) sprintf( ofile, ofiletemplate, argv[1], argv[3] );
    else           sprintf( ofile, ofiletemplate, argv[1], "testsample");

    readMgr data(ifile, "t", varBRANCHES);
    TFile* fout = new TFile(ofile, "RECREATE");

    LOG_DEBUG("creating histograms");
    histMgr::Create("HoverE"       , BINNING, 0.,    0.15);
    histMgr::Create("sieieFull5x5" , BINNING, 0.,    0.05);
    histMgr::Create("sieipFull5x5" , BINNING, -0.20, 0.2 );
    histMgr::Create("phoIsoRaw"    , BINNING, 0.,   30.  );
    histMgr::Create("pt"           , BINNING, 0., 1000.  );
    histMgr::Create("phi"          , BINNING, -3.14, 3.14);
    histMgr::Create("eta"          , BINNING, -3.14, 3.14);
    histMgr::Create("chIsoRaw"     , BINNING, 0.,   15.  );
    histMgr::Create("nVtx"         , BINNING, 0.,   50.  );
    histMgr::Create("MET_pt"       , BINNING, 0.,    2.  );
    histMgr::Create("SCeta"        , BINNING, -3.14, 3.14);
    histMgr::Create("r9"           , BINNING, 0.,    1.1 );
    histMgr::Create("s4"           , BINNING, 0.,    1.1 );
    histMgr::Create("rawE"         , BINNING, 0., 2000.  );
    histMgr::Create("SCetaWidth"   , BINNING, 0.,    0.10);
    histMgr::Create("SCphiWidth"   , BINNING, 0.,    0.10);
    histMgr::Create("rho"          , BINNING, 0.,   50.  );
    histMgr::Create("mva"          , BINNING,-1.,    1.  );


    histMgr::Create("MET_ptOVERphi", BINNING, -3.14, 3.14, BINNING, 0., 2.);

    LOG_DEBUG("start looping event");
    
    bool checkevt = false;
    for (Long64_t ievt = 0; ievt < data.GetEntriesFast(); ievt++) 
    {
        if (!passedEvt(&data, argv[1]) ) continue;
        if (!checkevt ) checkevt=true;
        // checkpassedevt(
        if ( ievt%10000 == 0 ) LOG_DEBUG("At evt %d", ievt);
        data.GetEntry(ievt);

        histMgr::Fill("HoverE"      , data.Float(var::HoverE            ));
        histMgr::Fill("sieieFull5x5", data.Float(var::sieieFull5x5      ));
        histMgr::Fill("sieipFull5x5", data.Float(var::sieipFull5x5      ));
        histMgr::Fill("phoIsoRaw"   , data.Float(var::phoIsoRaw         ));
        histMgr::Fill("pt"          , data.Float(var::recoPt            ));
        histMgr::Fill("phi"         , data.Float(var::recoPhi           ));
        histMgr::Fill("eta"         , data.Float(var::recoEta           ));
        histMgr::Fill("chIsoRaw"    , data.Float(var::chIsoRaw          ));
        histMgr::Fill("nVtx"        , data.Int  (var::nVtx              ));
        histMgr::Fill("MET_pt"      , data.Float(var::MET)/data.Float(var::recoPt));
        histMgr::Fill("SCeta"       , data.Float(var::recoSCEta         ));
        histMgr::Fill("r9"          , data.Float(var::r9                ));
        histMgr::Fill("s4"          , data.Float(var::e2x2Full5x5)/data.Float(var::e5x5Full5x5));
        histMgr::Fill("rawE"        , data.Float(var::rawE              ));
        histMgr::Fill("SCetaWidth"  , data.Float(var::scEtaWidth        ));
        histMgr::Fill("SCphiWidth"  , data.Float(var::scPhiWidth        ));
        histMgr::Fill("rho"         , data.Float(var::rho               ));
        histMgr::Fill("mva"         , data.Float(var::mva               ));

        histMgr::Fill("MET_ptOVERphi", data.Float(var::recoPhi),
                                       data.Float(var::MET)/data.Float(var::recoPt));
    }
    if (!checkevt ) LOG_WARNING("no event filled! Your input arg setting is '%s'. Please check", argv[1] );

    LOG_DEBUG("end of loopgin event, start to fill everything into root file");
    histMgr::WriteTo(fout);

    fout->Write();
    fout->Close();
}

#include "TMVA/Reader.h"
#include "TMVA/Config.h"
#include "TMVA/Tools.h"
#include "TMVA/MethodCuts.h"

#include <vector>
#include <iostream>
#include <map>
#include <string>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;


#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "xPhoton/xPhoton/interface/untuplizer.h"

void PrintHelp()
{
    fprintf(stderr, "############### Usage ###############\n");
    fprintf(stderr, "## Input a json file to configure  ##\n");
    fprintf(stderr, "## this file. To check the format, ##\n");
    fprintf(stderr, "## check $CMSSW_BASE/src/xPhoton/  ##\n");
    fprintf(stderr, "## phoIDMVA_noIsoCut/data/         ##\n");
    fprintf(stderr, "## TMVAValidationSample.json       ##\n");
    fprintf(stderr, "#####################################\n");
    throw "Undefined input\n";
}
const char* GetJsonFromArg( int argc, char** argv )
{ if ( argc != 2 ) PrintHelp(); return argv[1]; }
struct JsonInfo
{
    JsonInfo( const char* jsonfile )
    {
        pt::ptree root;
        pt::read_json(jsonfile, root);
        
        EBCUT       = root.get<float>("cut_barrel", 0.);
        EECUT       = root.get<float>("cut_endcap", 0.);
        USEISO      = root.get<bool>("usevar_Isolation", false);
        USESHAPE    = root.get<bool>("usevar_ShowerShape", false);
        testsample  = root.get<std::string>("testsample", "");
        xmlfile_EB  = root.get<std::string>("xmlfile_EB", "");
        xmlfile_EE  = root.get<std::string>("xmlfile_EE", "");
    }
    JsonInfo( int argc, char** argv ) : JsonInfo( GetJsonFromArg(argc,argv) ) { }

    float EBCUT;
    float EECUT;
    bool  USEISO;
    bool USESHAPE;
    std::string testsample;
    std::string xmlfile_EB;
    std::string xmlfile_EE;
};
class MyHist : public TH1F
{
    public:
    MyHist( const char* name, const char* title, int xbin, float xmin, float xmax ) :
        TH1F(name, title, xbin, xmin, xmax)
    { this->Sumw2(); }
};

int main(int argc, char** argv)
{
    JsonInfo args(argc,argv);

    TMVA::Reader* readerEB = new TMVA::Reader("!Color:!Silent");
    TMVA::Reader* readerEE = new TMVA::Reader("!Color:!Silent");

    Float_t r9Full5x5 = 0;
    Float_t sieieFull5x5 = 0;
    Float_t sieipFull5x5 = 0;
    Float_t s4Full5x5 = 0;
    Float_t rawE = 0;
    Float_t scEtaWidth = 0;
    Float_t scPhiWidth = 0;
    Float_t recoPhi = 0;
    Float_t recoSCEta = 0;
    Float_t rho = 0;
    Float_t ESEn = 0;
    Float_t esRR = 0;

    readerEB->AddVariable( "r9Full5x5",&r9Full5x5 );
    readerEB->AddVariable( "sieieFull5x5", &sieieFull5x5 );     
    readerEB->AddVariable( "sieipFull5x5", &sieipFull5x5 );     
    readerEB->AddVariable( "s4Full5x5", &s4Full5x5 );	       
    readerEB->AddVariable( "rawE", &rawE );	     
    readerEB->AddVariable( "scEtaWidth", &scEtaWidth );
    readerEB->AddVariable( "scPhiWidth", &scPhiWidth );
    readerEB->AddVariable( "recoPhi", &recoPhi );   
    readerEB->AddVariable( "recoSCEta", &recoSCEta ); 
    readerEB->AddVariable( "rho", &rho );


    readerEE->AddVariable( "r9Full5x5", &r9Full5x5 );
    readerEE->AddVariable( "sieieFull5x5", &sieieFull5x5 );     
    readerEE->AddVariable( "sieipFull5x5", &sieipFull5x5 );     
    readerEE->AddVariable( "s4Full5x5", &s4Full5x5 );	       
    readerEE->AddVariable( "rawE", &rawE );	     
    readerEE->AddVariable( "scEtaWidth", &scEtaWidth );
    readerEE->AddVariable( "scPhiWidth", &scPhiWidth );
    readerEE->AddVariable( "esEnergyOverSCRawEnergy", &ESEn );	            
    readerEE->AddVariable( "esRR", &esRR );
    readerEE->AddVariable( "recoPhi", &recoPhi );   
    readerEE->AddVariable( "recoSCEta", &recoSCEta ); 
    readerEE->AddVariable( "rho", &rho );

    readerEB->BookMVA( "BDT method", args.xmlfile_EB.c_str() );
    readerEE->BookMVA( "BDT method", args.xmlfile_EE.c_str() );


    TreeReader data( args.testsample.c_str(), "tt" );
    TTree* tin = data.GetTree();

    TFile* fout = new TFile("TMVApp.root", "RECREATE");
    TTree* tout = tin->CloneTree(0);

    Float_t bdtscore = 0;
    tout->Branch("BDT", &bdtscore, "BDT/F");

    MyHist* hBDT       = new MyHist("hBDT"    , "BDTscore in full region"                      , 20, -1., 1.);
    MyHist* hBDT_w     = new MyHist("hBDT_w"  , "BDTscore in full region with weight"          , 20, -1., 1.);
    MyHist* hBDT_w_s   = new MyHist("hBDT_w_s", "BDTscore in full region with weight (signal)" , 20, -1., 1.);
    MyHist* hBDT_w_f   = new MyHist("hBDT_w_f", "BDTscore in full region with weight (fake  )" , 20, -1., 1.); 
    MyHist* hEB_BDT       = new MyHist("hEB_BDT"    , "BDTscore in Barrel"                      , 20, -1., 1.);
    MyHist* hEB_BDT_w     = new MyHist("hEB_BDT_w"  , "BDTscore in Barrel with weight"          , 20, -1., 1.);
    MyHist* hEB_BDT_w_s   = new MyHist("hEB_BDT_w_s", "BDTscore in Barrel with weight (signal)" , 20, -1., 1.);
    MyHist* hEB_BDT_w_f   = new MyHist("hEB_BDT_w_f", "BDTscore in Barrel with weight (fake  )" , 20, -1., 1.); 
    MyHist* hEE_BDT       = new MyHist("hEE_BDT"    , "BDTscore in Endcap"                      , 20, -1., 1.);
    MyHist* hEE_BDT_w     = new MyHist("hEE_BDT_w"  , "BDTscore in Endcap with weight"          , 20, -1., 1.);
    MyHist* hEE_BDT_w_s   = new MyHist("hEE_BDT_w_s", "BDTscore in Endcap with weight (signal)" , 20, -1., 1.);
    MyHist* hEE_BDT_w_f   = new MyHist("hEE_BDT_w_f", "BDTscore in Endcap with weight (fake  )" , 20, -1., 1.); 
    for ( Long64_t ievt = 0; ievt != data.GetEntriesFast(); ++ievt )
    {

        if ( ievt % 10000 == 0 ) printf("event processing : %lld / %lld ( %.0f %% ) \n", ievt, data.GetEntriesFast(), 100.*float(ievt) / float(data.GetEntriesFast()) );
        if ( ievt % 10 != 0 ) continue; // only take 1/10 data
        tin->GetEntry(ievt);
        data.GetEntry(ievt);

        r9Full5x5   = data.GetFloat("r9Full5x5");
        sieieFull5x5= data.GetFloat("sieieFull5x5");
        sieipFull5x5= data.GetFloat("sieipFull5x5");
        s4Full5x5   = data.GetFloat("s4Full5x5");
        rawE        = data.GetFloat("rawE");
        scEtaWidth  = data.GetFloat("scEtaWidth");
        scPhiWidth  = data.GetFloat("scPhiWidth");
        recoPhi     = data.GetFloat("recoPhi");
        recoSCEta   = data.GetFloat("recoSCEta");
        rho         = data.GetFloat("rho");
        ESEn        = data.GetFloat("esEnergyOverSCRawEnergy");
        esRR        = data.GetFloat("esRR");

        Float_t mcweight  = data.GetFloat("mcweight");
        Float_t puwei     = data.GetFloat("puwei");
        Float_t weight2d  = data.GetFloat("weight2d");
        Int_t isMatched   = data.GetInt("isMatched");
        Int_t isConverted = data.GetInt("isConverted");
        if ( isConverted == 1 ) isMatched = 1;
        
        if ( data.GetInt("isMatchedEle") == 1 ) continue;
        if ( fabs(recoSCEta) >1.4442 && fabs(recoSCEta) < 1.566 ) continue;
        if ( fabs(recoSCEta) > 2.5 ) continue;
        if ( data.GetFloat("recoPt") < 15. ) continue;

        float evtweight = puwei * mcweight * weight2d;

        if (fabs(recoSCEta) < 1.5 )
        {
            bdtscore = readerEB->EvaluateMVA("BDT method");
            hEB_BDT->Fill(bdtscore);
            hEB_BDT_w->Fill(bdtscore,evtweight);
            if ( isMatched == 1 )
                hEB_BDT_w_s->Fill(bdtscore,evtweight);
            else
                hEB_BDT_w_f->Fill(bdtscore,evtweight);
        }
        else
        {
            bdtscore = readerEE->EvaluateMVA("BDT method");
            hEE_BDT->Fill(bdtscore);
            hEE_BDT_w->Fill(bdtscore,evtweight);
            if ( isMatched == 1 )
                hEE_BDT_w_s->Fill(bdtscore,evtweight);
            else
                hEE_BDT_w_f->Fill(bdtscore,evtweight);
        }

        // all distribution
        hBDT->Fill(bdtscore);
        hBDT_w->Fill(bdtscore,evtweight);
        if ( isMatched == 1 )
            hBDT_w_s->Fill(bdtscore,evtweight);
        else
            hBDT_w_f->Fill(bdtscore,evtweight);

        tout->Fill();
    }

    fout->cd();
    tout->Write();

    hBDT       ->Write();
    hBDT_w     ->Write();
    hBDT_w_s   ->Write();
    hBDT_w_f   ->Write();
    hEB_BDT    ->Write();
    hEB_BDT_w  ->Write();
    hEB_BDT_w_s->Write();
    hEB_BDT_w_f->Write();
    hEE_BDT    ->Write();
    hEE_BDT_w  ->Write();
    hEE_BDT_w_s->Write();
    hEE_BDT_w_f->Write();
    
    return 1;
}

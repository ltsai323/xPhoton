#include <iostream>
#include <stdio.h>

#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;

struct JsonInfo
{
    JsonInfo( const char* jsonfile )
    {
        pt::ptree root;
        pt::read_json(jsonfile, root);
        ebee         = root.get<int>("phoEtaBin"  , 0 );
        jetbin       = root.get<int>("jetEtaBin"  , 0 );
        ptbin        = root.get<int>("phoPtBin"   , 0 );

        ifile        = root.get<std::string>("inputfile", "");
        nhtemp_BDT   = root.get<std::string>("histnameTemplate_BDT", "");
        nhtemp_BDTup = root.get<std::string>("histnameTemplate_BDTerr", "");
        out_template = root.get<std::string>("outputname_template" , "systUpAndDown");

    }
    int ebee, jetbin, ptbin;
    std::string ifile, hname_BDT, hname_BDTup;
    std::string out_template;
};

struct BinInfo
{
    BinInfo( const JsonInfo& args )
    {
        ebee        = args.ebee        ;
        jetbin      = args.jetbin      ;
        ptbin       = args.ptbin       ;
        rebinoption = args.rebinoption ;
        tag="";
        file=nullptr;
    }
    BinInfo(const BinInfo& input)
    {
        this->ebee =          input.ebee ;
        this->jetbin =        input.jetbin ;
        this->ptbin =         input.ptbin ;
        this->rebinoption =   input.rebinoption ;
        this->tag =           input.tag;
        this->file =          input.file;
    }
    BinInfo() {} 
    int ebee, jetbin, ptbin, rebinoption; 
    std::string tag;
    TFile* file;


    const char* BinnedName(const char* nTemplate) const { return Form(nTemplate, ebee, jetbin, ptbin); }
    TObject* Get(const char* varTemplate) { if ( tag=="") throw std::runtime_error("TFile not loaded!\n"); return file->Get( BinnedName(varTemplate) ); }
    void SetFile(TFile* f) { file=f; }
    void SetOutputHistTemplate( const std::string& t ) { tag = t; }
};

void MakeSystupAndDown( const char* jsonname )
{
}

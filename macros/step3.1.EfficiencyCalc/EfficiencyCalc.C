#include <iostream>
#include <stdio.h>
#include <stdlib.h>

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
        maxpEtaBin  = root.get<int>("maxpEtaBin" ,  1 );
        maxjEtaBin  = root.get<int>("maxjEtaBin" ,  2 );
        maxpPtBin   = root.get<int>("maxpPtBin"  , 20 );


        f_sigRegion = root.get<std::string>("file_signalRegion", "");
        f_selection = root.get<std::string>("file_selection", "");
        nametag     = root.get<std::string>("outputTag", "output");
    }

    int maxpEtaBin, maxjEtaBin, maxpPtBin;
    std::string f_sigRegion, f_selection;
    std::string nametag;
};
struct BinInfoRec
{
    BinInfoRec( int petabin, int jetabin, int pptbin, TFile* f = nullptr ) :
        pEtaBin(petabin), jEtaBin(jetabin), pPtBin(pptbin),
        efficiency(-1.), error(-1.),
        infile(f)
    { }
    BinInfoRec( const BinInfoRec& b )
    {
        pEtaBin    = b.pEtaBin;
        jEtaBin    = b.jEtaBin;
        pPtBin     = b.pPtBin ;
        efficiency = b.efficiency;
        error      = b.error;
        infile     = b.infile;
    }
    int pEtaBin, jEtaBin, pPtBin;
    float efficiency, error;
    TFile* infile;

    const char* BinnedName(const char* nTemplate) const { return Form(nTemplate, pEtaBin, jEtaBin, pPtBin); }
    const char* Show() const { return Form("%2d %2d %2d %12.8f %12.8f\n", pEtaBin, jEtaBin, pPtBin, efficiency, error); }
    static const char* ShowInfo() { return Form("pEtaBin/I:jEtaBin/I:pPtBin/I:efficiency/F:error/F\n"); }
    void* GetObjFromFile(const char* nTemplate) { return infile->Get( this->BinnedName(nTemplate) ); }
};

void FillEfficiency_SignalRegion(BinInfoRec& bin)
{
    TH1* sigRegion = (TH1*) bin.GetObjFromFile("gjet_%d_%d_%d_px1_chIso");
    TH2* allRegion = (TH2*) bin.GetObjFromFile("gjet_%d_%d_%d_all");
    float num = sigRegion->Integral();
    float den = allRegion->Integral();
    
    if ( allRegion->GetEntries() > 1 )
    {
        bin.efficiency = num / den;
        bin.error = sqrt( bin.efficiency * (1.-bin.efficiency) / den );
    }
    else
    {
        bin.efficiency = -99.;
        bin.error      = -99.;
    }
}
void writeto( FILE* f, const char* mesg )
{ fprintf( f, "%s", mesg ); }

void EfficiencyCalc(const char* jsonfilename)
{
    JsonInfo args(jsonfilename);
    TFile* ifile = TFile::Open( args.f_sigRegion.c_str() );

    // container building
    std::vector<BinInfoRec> bins;
    bins.reserve( (args.maxjEtaBin+1) * (args.maxpEtaBin+1) * (args.maxpPtBin+1) );
    for ( int jEtaBin = 0; jEtaBin <= args.maxjEtaBin; ++jEtaBin )
        for ( int pEtaBin = 0; pEtaBin <= args.maxpEtaBin; ++pEtaBin )
            for ( int pPtBin = 0; pPtBin <= args.maxpPtBin; ++pPtBin )
                bins.emplace_back(pEtaBin,jEtaBin,pPtBin,ifile);

    for ( auto& bin : bins )
        FillEfficiency_SignalRegion(bin);

    FILE* fout = fopen( Form("%s_%s.dat",args.nametag.c_str(),"signalRegion"), "w");
    writeto(fout, BinInfoRec::ShowInfo());
    for ( const auto& bin : bins )
        writeto(fout, bin.Show());
}

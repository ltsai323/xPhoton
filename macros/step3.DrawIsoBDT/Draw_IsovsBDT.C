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
// target : 
//    input data / sigMC / bkgMC and return binning histogram with all and sideband BDT distribution.
//    which all distribution is 2D histogram. But sideband is 1D.

const bool useNewSample = true;


struct JsonInfo
{
    JsonInfo( const char* jsonfile )
    {
        pt::ptree root;
        pt::read_json(jsonfile, root);
        ebee        = root.get<int>("phoEtaBin"  , 0 );
        jetbin      = root.get<int>("jetEtaBin"  , 0 );
        ptbin       = root.get<int>("phoPtBin"   , 0 );
        rebinoption = root.get<int>("rebinOption", 5 );
        //sb1         = root.get<int>("sidebandlower", 14);
        //sb2         = root.get<int>("sidebandupper", 20);

        datafile    = root.get<std::string>("data", "");
        sig_file    = root.get<std::string>("sig" , "");
        bkg_file    = root.get<std::string>("bkg" , "");
        out_template= root.get<std::string>("out_template" , "");

    }
    int ebee, jetbin, ptbin, rebinoption; //, sb1, sb2;
    std::string datafile, sig_file, bkg_file;
    std::string out_template;

    const char* Data()  const { return datafile.c_str(); }
    const char* SigMC() const { return sig_file.c_str(); }
    const char* BkgMC() const { return bkg_file.c_str(); }
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
std::vector<float> ptbin_ranges()
{
    // for 2016
    //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
    std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
    return vec_ptcut;
}
bool IsPhoBarrel( int phoEtaBin )
{ return phoEtaBin == 0; }
bool IsPhoEndcap( int phoEtaBin )
{ return phoEtaBin == 1; }
bool IsJetBarrel( int jetEtaBin )
{ return jetEtaBin == 0; ;}
bool IsJetEndcap( int jetEtaBin )
{ return jetEtaBin == 1; ;}

TH2F* GetHist(BinInfo args, const char* histNameTemplate )
{
    const int EXCLUSIVE_PHOTON = 2;

    TH2F* hout = (TH2F*) args.Get( histNameTemplate );
    if ( args.jetbin != EXCLUSIVE_PHOTON ) return hout;

    while ( args.jetbin-- )
    {
        TH2F* htemp = (TH2F*) args.Get(histNameTemplate);
        hout->Add(htemp);
    }
    return hout;
}

struct HistsNeedStored
{
    TH1D* hpx0;
    TH1D* hpx1;
    TH2F* hall;

    void Write( TDirectory* dir = nullptr )
    {
        if ( dir ) dir->cd();
        hpx0->Write();
        hpx1->Write();
        hall->Write();
    }
};


void PrintSigAndSideBandBasicInfo( const HistsNeedStored& hists )
{
    printf("In hist %s\n", hists.hall->GetName());
    printf("sig fraction : %5.2f %% and fake fraction %5.2f %%\n", 100.*hists.hpx0->Integral()/hists.hall->Integral(), 100.*hists.hpx1->Integral()/hists.hall->Integral() );
}

HistsNeedStored SigAndSidebandHistCalc( const BinInfo& args, const char* histNameTemplate, const char* errhistTemplate = nullptr )
{
    TH2F* hdata = GetHist( args, histNameTemplate );
    bool hasErr = errhistTemplate != nullptr;
    TH2F* herrs = hasErr ? GetHist( args, errhistTemplate ) : nullptr;

    TH2F* hdata_all = (TH2F*) hdata->Clone(); 
    //std::string allname = args.tag + "_all_%d_%d_%d";
    std::string allname = args.tag + "_all";
    hdata_all->SetName( args.BinnedName(allname.c_str()) );
    hdata->Rebin2D(args.rebinoption,2);
    if ( hasErr ) herrs->Rebin2D(args.rebinoption,2);

    int nbinx = hdata->GetNbinsX();

    int zone1_low = 1;
    int zone1_high = 4; 
    int IsoOption=0; //0 chIso, 1 phoIso, 2 combIso, 3 chWorst
    // EB = [0,2] and EE=[0,1.5]
    if( IsPhoEndcap(args.ebee) ) { //EE
        if     (IsoOption==0) zone1_high=3;
        else if(IsoOption==1) zone1_high=5;
        else if(IsoOption==2) zone1_high=7;
        else if(IsoOption==3) zone1_high=6;
    }

    int zone2_low = 10;
    int zone2_high = 20;
    //for production 
    //if(args.ebee<=1) {zone2_low=14; zone2_high=26;} //EB
    //else {zone2_low=12; zone2_high=24;}
    //else if(args.ebee==2) {zone2_low=7; zone2_high=20;}

    // This formula shows the characteristics of the binning.
    // upper limit and lower limit calculation is not the same
    // SB region from 2~10 means 2 = (x-1) * 0.5 and 10 = (x) * 0.5
    //if( IsPhoBarrel(args.ebee) ) {zone2_low=7; zone2_high=20;} // EE = [3.0, 10]
    //if( IsPhoEndcap(args.ebee) ) {zone2_low=6; zone2_high=20;} // EE = [2.5, 10]
    if( IsPhoBarrel(args.ebee) ) {zone2_low=15; zone2_high=26;} // EE = [7.0, 13]
    if( IsPhoEndcap(args.ebee) ) {zone2_low=13; zone2_high=24;} // EE = [6.0, 12]

    //for chIso SB

    std::string zone1name = args.tag + "_px1_chIso";
    TH1D *h_data_zone1 = (TH1D*)hdata->ProjectionX(args.BinnedName(zone1name.c_str()),zone1_low, zone1_high);
    if ( hasErr )
    {
        TH1D* HDATA = h_data_zone1;
        int bin_l = zone1_low;
        int bin_r = zone1_high;
        TH1D *HDATA_ERR = (TH1D*)herrs->ProjectionX("hi", bin_l, bin_r);
        for ( int ibin = HDATA->GetNbinsX()+1; ibin != 0; --ibin )
            HDATA->SetBinError( ibin, fabs(HDATA->GetBinContent(ibin)-HDATA_ERR->GetBinContent(ibin)) );
            //HDATA->SetBinError( ibin, HDATA->GetBinContent(ibin) );
    }


    std::string zone2name = args.tag + "_px2_chIso";
    TH1D *h_data_zone2 = (TH1D*)hdata->ProjectionX(args.BinnedName(zone2name.c_str()),zone2_low, zone2_high);
    if ( hasErr )
    {
        TH1D* HDATA = h_data_zone2;
        int bin_l = zone2_low;
        int bin_r = zone2_high;
        TH1D *HDATA_ERR = (TH1D*)herrs->ProjectionX("hj", bin_l, bin_r);
        for ( int ibin = HDATA->GetNbinsX()+1; ibin != 0; --ibin )
            HDATA->SetBinError( ibin, fabs(HDATA->GetBinContent(ibin)-HDATA_ERR->GetBinContent(ibin)) );
            //HDATA->SetBinError( ibin, HDATA->GetBinContent(ibin) );
        //std::cerr << "the error bar has been updated!\n";
    }


    HistsNeedStored out;
    out.hpx0 = h_data_zone1;
    out.hpx1 = h_data_zone2;
    out.hall = hdata_all;

    //PrintSigAndSideBandBasicInfo(out);
    return out;
}


void Draw_IsovsBDT(const char* jsonName){
    JsonInfo args(jsonName);

    TFile *fdata = TFile::Open( args.Data()  );
    TFile *fqcd  = TFile::Open( args.BkgMC() );
    TFile *fgjet = TFile::Open( args.SigMC() );

    BinInfo arg_data(args), arg_gjet(args), arg_qcd(args);
    arg_data.SetFile(fdata);
    arg_gjet.SetFile(fgjet);
    arg_qcd .SetFile(fqcd );

    std::vector<HistsNeedStored> outputHists;
    /* check for mva syst error
    TFile *fgjet2= TFile::Open( args.SigMC() );
    BinInfo arg_gjet2(args);
    arg_gjet2.SetFile(fgjet2);
    arg_gjet2.SetOutputHistTemplate("gjetChecking_%d_%d_%d");
    outputHists.push_back(SigAndSidebandHistCalc(arg_gjet2, "IsovsBDT/IsovsBDT.%d_%d_%d_0_0") );
    */
    arg_gjet.SetOutputHistTemplate("gjet_%d_%d_%d");
    //outputHists.push_back(SigAndSidebandHistCalc(arg_gjet, "IsovsBDT/IsovsBDT.%d_%d_%d_0_0", "IsovsBDTorig/IsovsBDTorig.%d_%d_%d_0_0")); // add error bar
    outputHists.push_back(SigAndSidebandHistCalc(arg_gjet, "IsovsBDT/IsovsBDT.%d_%d_%d_0_0") );
    arg_data.SetOutputHistTemplate("data_%d_%d_%d");
    outputHists.push_back(SigAndSidebandHistCalc(arg_data, "IsovsBDT/IsovsBDT.%d_%d_%d_0_0") );
    arg_qcd .SetOutputHistTemplate("qcd_%d_%d_%d" );
    //outputHists.push_back(SigAndSidebandHistCalc(arg_qcd , "IsovsBDT/IsovsBDT.%d_%d_%d_1_0", "IsovsBDTorig/IsovsBDTorig.%d_%d_%d_1_0"));
    outputHists.push_back(SigAndSidebandHistCalc(arg_qcd , "IsovsBDT/IsovsBDT.%d_%d_%d_1_0") );

    // after jet selection
    arg_gjet.SetOutputHistTemplate("jetSel_gjet_%d_%d_%d");
    outputHists.push_back(SigAndSidebandHistCalc(arg_gjet, "jetcut_IsovsBDT/jetcut_IsovsBDT.%d_%d_%d_0_0") );
    arg_data.SetOutputHistTemplate("jetSel_data_%d_%d_%d");
    outputHists.push_back(SigAndSidebandHistCalc(arg_data, "jetcut_IsovsBDT/jetcut_IsovsBDT.%d_%d_%d_0_0") );
    arg_qcd .SetOutputHistTemplate("jetSel_qcd_%d_%d_%d" );
    outputHists.push_back(SigAndSidebandHistCalc(arg_qcd , "jetcut_IsovsBDT/jetcut_IsovsBDT.%d_%d_%d_1_0") );
    if ( useNewSample ) {
        for ( int systType = 0; systType < 3; ++systType ) {
        for ( int btagvar = 0; btagvar < 4; ++btagvar ) {
        for ( int jetflav = 0; jetflav < 3; ++jetflav ) {
        for ( int matchedPhoStat = 0; matchedPhoStat < 5; ++matchedPhoStat ) {
        for ( int parityIdx = 0; parityIdx < 2; ++parityIdx )
        {
            const char* histname = Form( "btagDeepCSV/btagDeepCSV.%d_%d_%d__%s__%d_%d",
                    systType, btagvar, jetflav, "%d_%d_%d", matchedPhoStat, parityIdx );
            std::string  outname = Form(             "btagDeepCSV.%d_%d_%d__%s__%d_%d",
                    systType, btagvar, jetflav, "%d_%d_%d", matchedPhoStat, parityIdx );
            arg_gjet.SetOutputHistTemplate("gjet_"+outname);
            outputHists.push_back(SigAndSidebandHistCalc(arg_gjet, histname));
            arg_data.SetOutputHistTemplate("data_"+outname);
            outputHists.push_back(SigAndSidebandHistCalc(arg_data, histname));
            arg_qcd .SetOutputHistTemplate("qcd_" +outname);
            outputHists.push_back(SigAndSidebandHistCalc(arg_qcd , histname));
        } } } } }
    }


    TFile* fout = new TFile( arg_data.BinnedName("iso_%d_%d_%d.root"), "RECREATE" );
    for ( auto outhists : outputHists )
        outhists.Write(fout);

    fout->Close();
}


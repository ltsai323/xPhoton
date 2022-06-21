#include <iostream>
#include <stdio.h>
#include <stdexcept>

#include <TFile.h>
#include <TH1F.h>
#include <TH2F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TGraph.h>
#include <TString.h>
#include <TGraphAsymmErrors.h>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;


// hist0 : hist before selection
// hist1 : hist after  selection
// scale hist0 to hist1. And check the shape
template<typename HIST>
bool HistComp( HIST* hist0, HIST* hist1 , double minChi2 = 2 )
{
    double sumH0 = hist0->Integral();
    //double sumH1 = hist1->Integral();
    if ( sumH0 < 1e-6 ) throw std::runtime_error("Nothing in histogram. Comparison failed\n");

    //double scalefactor = sumH1 / sumH0;
    //hist0->Scale(scalefactor);

    return hist1->Chi2Test(hist0, "UW P") < minChi2;
}
template<typename HIST>
double HistComp( HIST* hist0, HIST* hist1 )
{
    double sumH0 = hist0->Integral();
    //double sumH1 = hist1->Integral();
    if ( sumH0 < 1e-6 ) throw std::runtime_error("Nothing in histogram. Comparison failed\n");

    //double scalefactor = sumH1 / sumH0;
    //hist0->Scale(scalefactor);

    return hist1->Chi2Test(hist0, "UW P");
}
struct Chi2Check
{
    Chi2Check( TH1* HEXP, TH1* HCMP, Double_t chi2 ) : _h0(HEXP), _h1(HCMP), _chi2(chi2)
    { }
    TH1* _h0;
    TH1* _h1;
    Double_t _chi2;
};


//double HistComp( TH2* hist0, TH2* hist1 )
Chi2Check HistComp( TH2* hist0, TH2* hist1 )
{
    double sumH0 = hist0->Integral();
    if ( sumH0 < 1e-6 ) throw std::runtime_error("Nothing in histogram. Comparison failed\n");


    TH1* h0 = (TH1*)hist0->ProjectionX();
    TH1* h1 = (TH1*)hist1->ProjectionX();

    return Chi2Check( h0, h1, h1->Chi2Test(h0, "UU CHI2/NDF") );
}
struct  JsonInfo
{
    JsonInfo( const char* ifile )
    {
        pt::ptree root;
        pt::read_json(ifile, root);

        showRes = root.get<bool>("ShowOnScreen", true);
        inputfile = root.get<std::string>("inputfile", "");
    }
    bool showRes;
    std::string inputfile;
};

void DrawResult( Chi2Check& res, TCanvas* c1, const char* oname )
{
    TH1* h0 = res._h0;
    TH1* h1 = res._h1;
    Double_t nChi2 = res._chi2;

    double sumH0 = h0->Integral();
    double sumH1 = h1->Integral();
    // no need to scale for chi2 test
    double scalefactor = sumH1 / sumH0;
    h0->Scale(scalefactor);

    h0->SetLineColor(2);
    h0->SetLineWidth(4);
    h0->SetMarkerSize(3);
    h0->SetMarkerColor(2);
    
    h1->SetLineColor(1);
    h1->SetLineWidth(2);
    h1->SetMarkerColor(1);
    h1->SetMarkerSize(1);
    
    h0->GetYaxis()->SetRangeUser(0., h0->GetMaximum()*1.4);
    h0->Draw("ep");
    h1->Draw("ep same");

    TLegend leg(0.2,0.72,0.8,0.85);
    leg.SetHeader(Form("Chi2/DOF = %.2f", nChi2));
    leg.AddEntry(h0, "data", "p");
    leg.AddEntry(h1, "data with jet selections", "p");

    leg.SetBorderSize(0);
    leg.SetFillColor(4000);
    leg.SetFillStyle(4000);
    leg.Draw();
    c1->SaveAs(oname);
}
void DrawResult(TH2* H0, TH2* H1, TCanvas* c1, const char* oname )
{
    TH1* h0 = (TH1*) H0->ProjectionX();
    TH1* h1 = (TH1*) H1->ProjectionX();

    h0->SetLineColor(2);
    h0->SetLineWidth(4);
    h0->SetMarkerSize(3);
    h0->SetMarkerColor(2);
    
    h1->SetLineColor(1);
    h1->SetLineWidth(2);
    h1->SetMarkerColor(1);
    h1->SetMarkerSize(1);
    
    h0->GetYaxis()->SetRangeUser(0., h0->GetMaximum()*1.4);
    h0->Draw("ep");
    h1->Draw("ep same");
    c1->SaveAs(oname);
}

    
void checkHistShape_JetSel( const char* jsonname )
{
    JsonInfo arg(jsonname);

    TFile* fin = TFile::Open( arg.inputfile.c_str() );
    TCanvas* c1 = new TCanvas("c","", 800,800);

    std::vector<double> chi2Coll;

    int isovar = 0; // chIso
    for ( int isSigPho = 0; isSigPho < 2; ++isSigPho )
    {
        for ( int pEtaBin = 0; pEtaBin < 2; ++pEtaBin)
        {
            for ( int jEtaBin = 0; jEtaBin < 2; ++jEtaBin )
            {
                for ( int pPtBin = 0; pPtBin < 20; ++pPtBin )
                //for ( int pPtBin = 0; pPtBin < 5; ++pPtBin )
                {
                    TString binning = Form(".%d_%d_%d_%d_%d", pEtaBin,jEtaBin,pPtBin,isSigPho,isovar);

                    TH2* hexp = (TH2*) fin->Get("IsovsBDT/IsovsBDT"+binning);
                    TH2* hcut = (TH2*) fin->Get("jetcut_IsovsBDT/jetcut_IsovsBDT"+binning);
                    //printf("Bin %s  with entries : orig %.1f and cut %.1f\n", binning.Data(), hexp->Integral(), hcut->Integral() );

                    if ( hexp->GetEntries() == 0 )
                    {
                        printf("At Bin %s, no entry before cut. skip this\n",binning.Data() );
                        continue;
                    }

                    //Double_t chi2Val = HistComp( hexp, hcut );
                    Chi2Check res = HistComp( hexp, hcut );

                    chi2Coll.push_back(res._chi2);
                    if ( arg.showRes )
                        printf("At Binning (%s), chi2 value = %10.2f\n", binning.Data(), res._chi2);
                    //DrawResult(hexp,hcut,c1, Form("h_cutComp%s.png",binning.Data()));
                    DrawResult( res,c1, Form("h_cutComp%s.png",binning.Data()));
                } } } }

    double xarr[ chi2Coll.size() ];
    for ( int i=0; i<chi2Coll.size(); ++i ) xarr[i] = i+1;

    TGraph* g = new TGraph(chi2Coll.size(), xarr, &chi2Coll.front() );
    g->Draw("AC");
    c1->SaveAs("h_chi2Coll.png");
    
    return;
}

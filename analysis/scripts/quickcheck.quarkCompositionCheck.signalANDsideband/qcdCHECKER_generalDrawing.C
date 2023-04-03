#include "commonVars.h"
class MyLegend : public TLegend
{
public:
    MyLegend(double x1, double y1, double x2, double y2) : TLegend(x1,y1,x2,y2)
    {
        SetFillColor(4000);
        SetFillStyle(4000);
        SetBorderSize(1);
    }
};
class MyCanvas : public TCanvas
{
    public:
    MyCanvas(const char* n, const char* t, int w, int d ) : TCanvas(n,t,w,d)
    {
        SetTopMargin(0.2);
        SetBottomMargin(0.2);
        SetLeftMargin(0.15);
        SetRightMargin(0.15);
        SetFillColor(4000);
        SetFillStyle(4000);
    }
};


const int comp_color[] = { 46, 38, 2,4};
//const int comp_markcolor[] = { comp_color[0],comp_color[1], 1,1 };
const int comp_markcolor[] = { comp_color[0],comp_color[1], comp_color[2],comp_color[3]};
//const int comp_markstyle[] = {27,28, 33,34};
const int comp_markstyle[] = {33,34, 27,28};
const int comp_marksize[] = { 2,2,2,2 };
void VisualizationSetup(const vector<TH1*>& hists)
{
    for ( int idx = 0; idx < hists.size(); ++idx )
    {
        TH1* hist = hists[idx];
        hist->SetLineColor( comp_color[idx] );
        hist->SetMarkerStyle( comp_markstyle[idx] );
        hist->SetMarkerSize( comp_marksize[idx]);
        hist->SetMarkerColor( comp_markcolor[idx] );
        hist->SetLineWidth(1);
        hist->SetFillColor(0);
        hist->SetFillStyle(1001);
        hist->SetStats(false);

        hist->GetXaxis()->SetTitleSize( hist->GetYaxis()->GetTitleSize() );
        hist->GetXaxis()->SetTitleOffset(1.1);

        for ( auto ibin = hist->GetNbinsX()+1; ibin !=0; --ibin )
            hist->SetBinError(ibin, 1e-8);
    }
}
TGraph* TranslateToTGraph(TH1* h)
{
    const int nArr = h->GetNbinsX();
    double bincontents[nArr];
    for ( int iArr = nArr; iArr!=0; --iArr )
        bincontents[iArr-1] = h->GetBinContent(iArr);
    auto newgraph = new TGraph(nArr,h->GetXaxis()->GetXbins()->GetArray(), bincontents);
    newgraph->SetLineColor( h->GetLineColor() );
    newgraph->SetLineWidth( h->GetLineWidth() );
    newgraph->SetMarkerSize( h->GetMarkerSize() );
    newgraph->SetMarkerColor( h->GetMarkerColor() );
    newgraph->SetMarkerStyle( h->GetMarkerStyle() );
    return newgraph;
}
    
void qcdCHECKER_compositionDrawing(const char* ifilename)
{
    TFile* ifile = TFile::Open(ifilename);

    auto canv = new MyCanvas("canv", "", 1200,1200);
    std::vector<TH1*> bHists;
    bHists.push_back( (TH1*) ifile->Get("rawSign_bComposition") );
    bHists.push_back( (TH1*) ifile->Get("rawFake_bComposition") );
    bHists.push_back( (TH1*) ifile->Get("cutSign_bComposition") );
    bHists.push_back( (TH1*) ifile->Get("cutFake_bComposition") );
    VisualizationSetup(bHists);

    std::vector<TH1*> cHists;
    cHists.push_back( (TH1*) ifile->Get("rawSign_cComposition") );
    cHists.push_back( (TH1*) ifile->Get("rawFake_cComposition") );
    cHists.push_back( (TH1*) ifile->Get("cutSign_cComposition") );
    cHists.push_back( (TH1*) ifile->Get("cutFake_cComposition") );
    VisualizationSetup(cHists);

    std::vector<TH1*> LHists;
    LHists.push_back( (TH1*) ifile->Get("rawSign_LComposition") );
    LHists.push_back( (TH1*) ifile->Get("rawFake_LComposition") );
    LHists.push_back( (TH1*) ifile->Get("cutSign_LComposition") );
    LHists.push_back( (TH1*) ifile->Get("cutFake_LComposition") );
    VisualizationSetup(LHists);

    const char* titles[] = {
        "original signal region", "original sideband region",
        "selected signal region", "selected sideband region"
    };

    std::vector<TH1*>* hists = nullptr;
    MyLegend* leg = nullptr;
    canv->SetLogx();
    std::vector<TGraph*> gr;
    

    hists = &bHists;
    leg = new MyLegend(0.4,0.7,0.75,0.80);
    hists->at(0)->Draw("axis");
    for ( int idx = 0; idx < hists->size(); ++idx )
    {
        gr.push_back( TranslateToTGraph(hists->at(idx)) );
        gr.back()->Draw("lp");
        leg->AddEntry(hists->at(idx), titles[idx], "lp");
    }
    leg->Draw();
    canv->SaveAs("qcdCHECKER_compositionDrawing_C_b.pdf");
    for ( auto ptr : gr ) delete ptr; gr.clear();
    delete leg;


    hists = &cHists;
    leg = new MyLegend(0.20,0.65,0.55,0.75);
    hists->at(0)->Draw("axis");
    for ( int idx = 0; idx < hists->size(); ++idx )
    {
        gr.push_back( TranslateToTGraph(hists->at(idx)) );
        gr.back()->Draw("lp");
        leg->AddEntry(hists->at(idx), titles[idx], "lp");
    }
    leg->Draw();
    canv->SaveAs("qcdCHECKER_compositionDrawing_C_c.pdf");
    for ( auto ptr : gr ) delete ptr; gr.clear();
    delete leg;


    hists = &LHists;
    leg = new MyLegend(0.5,0.70,0.85,0.80);
    hists->at(0)->Draw("axis");
    for ( int idx = 0; idx < hists->size(); ++idx )
    {
        gr.push_back( TranslateToTGraph(hists->at(idx)) );
        gr.back()->Draw("lp");
        leg->AddEntry(hists->at(idx), titles[idx], "lp");
    }
    leg->Draw();
    canv->SaveAs("qcdCHECKER_compositionDrawing_C_L.pdf");
    for ( auto ptr : gr ) delete ptr; gr.clear();
    delete leg;
}
void qcdCHECKER_yieldDrawing(const char* ifilename)
{
    TFile* ifile = TFile::Open(ifilename);

    auto canv = new MyCanvas("canv", "", 1200,1200);
    std::vector<TH1*> bHists;
    bHists.push_back( (TH1*) ifile->Get("rawSign_bYield") );
    bHists.push_back( (TH1*) ifile->Get("rawFake_bYield") );
    bHists.push_back( (TH1*) ifile->Get("cutSign_bYield") );
    bHists.push_back( (TH1*) ifile->Get("cutFake_bYield") );
    VisualizationSetup(bHists);
    bHists[2]->SetMarkerSize(3);
    bHists[3]->SetMarkerSize(3);

    std::vector<TH1*> cHists;
    cHists.push_back( (TH1*) ifile->Get("rawSign_cYield") );
    cHists.push_back( (TH1*) ifile->Get("rawFake_cYield") );
    cHists.push_back( (TH1*) ifile->Get("cutSign_cYield") );
    cHists.push_back( (TH1*) ifile->Get("cutFake_cYield") );
    VisualizationSetup(cHists);
    cHists[2]->SetMarkerSize(3);
    cHists[3]->SetMarkerSize(3);

    std::vector<TH1*> LHists;
    LHists.push_back( (TH1*) ifile->Get("rawSign_LYield") );
    LHists.push_back( (TH1*) ifile->Get("rawFake_LYield") );
    LHists.push_back( (TH1*) ifile->Get("cutSign_LYield") );
    LHists.push_back( (TH1*) ifile->Get("cutFake_LYield") );
    VisualizationSetup(LHists);
    LHists[2]->SetMarkerSize(3);
    LHists[3]->SetMarkerSize(3);

    const char* titles[] = {
        "original signal region", "original sideband region",
        "selected signal region", "selected sideband region"
    };

    std::vector<TH1*>* hists = nullptr;
    MyLegend* leg = nullptr;
    canv->SetLogx();
    canv->SetLogy();
    std::vector<TGraph*> gr;
    

    hists = &bHists;
    leg = new MyLegend(0.5,0.70,0.85,0.80);
    hists->at(1)->Draw("axis");
    for ( int idx = 0; idx < hists->size(); ++idx )
    {
        gr.push_back( TranslateToTGraph(hists->at(idx)) );
        gr.back()->Draw("lp");
        leg->AddEntry(hists->at(idx), titles[idx], "lp");
    }
    leg->Draw();
    canv->SaveAs("qcdCHECKER_yieldDrawing_C_b.pdf");
    for ( auto ptr : gr ) delete ptr; gr.clear();
    delete leg;


    hists = &cHists;
    leg = new MyLegend(0.5,0.70,0.85,0.80);
    hists->at(1)->Draw("axis");
    for ( int idx = 0; idx < hists->size(); ++idx )
    {
        gr.push_back( TranslateToTGraph(hists->at(idx)) );
        gr.back()->Draw("lp");
        leg->AddEntry(hists->at(idx), titles[idx], "lp");
    }
    leg->Draw();
    canv->SaveAs("qcdCHECKER_yieldDrawing_C_c.pdf");
    for ( auto ptr : gr ) delete ptr; gr.clear();
    delete leg;


    hists = &LHists;
    leg = new MyLegend(0.5,0.70,0.85,0.80);
    hists->at(1)->Draw("axis");
    for ( int idx = 0; idx < hists->size(); ++idx )
    {
        gr.push_back( TranslateToTGraph(hists->at(idx)) );
        gr.back()->Draw("lp");
        leg->AddEntry(hists->at(idx), titles[idx], "lp");
    }
    leg->Draw();
    canv->SaveAs("qcdCHECKER_yieldDrawing_C_L.pdf");
    for ( auto ptr : gr ) delete ptr; gr.clear();
    delete leg;
}
void qcdCHECKER_generalDrawing()
{
    qcdCHECKER_compositionDrawing("qcdCHECKER_plotQuarkCompositionSep_differentSelection_C.root");
    qcdCHECKER_yieldDrawing("qcdCHECKER_plotQuarkCompositionSep_differentSelection_C.root");
}

#include "commonVars.h"

void LowStatEntryRemoval(TH1* hh, int iMC)
{
    for ( int ibin = hh->GetNbinsX(); ibin >= jetptBin_tenToMinusFiveCut[iMC]; --ibin )
        hh->SetBinContent(ibin,0.);
}
TH1* histFactory_MergeMCSlices(TDirectoryFile* ifile, const char* nameTEMPLATE)
{
    std::vector<TH1*> loadhists(NMCSEP, nullptr);
    for ( int i=0;i<NMCSEP;++i )
        loadhists.at(i) = (TH1*) ifile->Get( Form(nameTEMPLATE,i) );
    TH1* l = loadhists.at(0);
    TH1F* outhist = new TH1F( "tmp", "", l->GetNbinsX(), l->GetXaxis()->GetXbins()->GetArray() );

    for ( int iMC = 0; iMC < loadhists.size(); ++iMC )
        LowStatEntryRemoval(loadhists[iMC], iMC);
    for ( int ibin = outhist->GetNbinsX()+1; ibin !=0; --ibin )
    {
        double bin_integral = 0.;
        for ( TH1* h : loadhists )
            bin_integral += h->GetBinContent(ibin);
        outhist->SetBinContent(ibin, bin_integral);
    }
    return outhist;
}
TH1* histFactory_MergePtBinning(TFile* ifile, const char* nameTEMPLATE)
{
    std::vector<TH1*> loadhists(NUMBIN, nullptr);
    for ( int i = 0; i < NUMBIN; ++i )
        loadhists.at(i) = (TH1*) ifile->Get( Form(nameTEMPLATE,i) );

    TH1F* outhist = new TH1F( "tmp", "", jetptBin.size()-1, &(jetptBin.front()) );

    for ( int ibin = outhist->GetNbinsX()+1; ibin !=0; --ibin )
        outhist->SetBinContent( ibin, loadhists[ibin-1]->Integral() );
    return outhist;
}
TH1* histFactory_jetPt_TreeSelection(TDirectoryFile* ifile, const char* cut)
{
    TTree* t = (TTree*) ifile->Get("t");
    TH1F* outhist = new TH1F( "tmp", "", jetptBin.size()-1, &(jetptBin.front()) );
    outhist->Sumw2();
    t->Draw("jetPt>>tmp", cut);
    return outhist;
}
void SetHistProperty(TH1* h, int fillcolor, const char* name, const char* illustration)
{
    h->SetName(name);
    h->SetTitle(illustration); // title is only used to be the label of TLegend
    h->SetTitleSize(0); // to hide title
    h->SetLineColor(13);
    h->SetLineWidth(1);
    h->SetFillColor(fillcolor);
    h->SetFillStyle(1001);
    h->GetXaxis()->SetTitle("reco jet Pt (GeV)");
    h->GetYaxis()->SetTitle("Quark Composition");
}
void normalization_eachBinBackToOne(std::vector<TH1*>& hists)
{
    TH1* h = hists.front();
    for ( auto ibin = h->GetNbinsX(); ibin != 0; --ibin )
    {
        double integral = 0.;
        for ( TH1* hist : hists )
            integral += hist->GetBinContent(ibin);
        for ( TH1* hist : hists )
            hist->SetBinContent(ibin, hist->GetBinContent(ibin)/integral);
    }
}
std::vector<TH1*> normalizeToOne(const std::vector<TH1*>& hists)
{
    std::vector<TH1*> normalizedhists(hists.size(), nullptr);
    for ( int idx = 0; idx < hists.size(); ++idx )
        normalizedhists[idx] = (TH1*) hists[idx]->Clone();
    normalizedhists[quarks::b]->SetName("bComposition");
    normalizedhists[quarks::c]->SetName("cComposition");
    normalizedhists[quarks::L]->SetName("LComposition");


    TH1* h = hists.front();
    for ( auto ibin = h->GetNbinsX(); ibin != 0; --ibin )
    {
        double integral = 0.;
        for ( TH1* hist : hists )
            integral += hist->GetBinContent(ibin);
        for ( int idx = 0; idx < hists.size(); ++idx )
            normalizedhists[idx]->SetBinContent(ibin, hists[idx]->GetBinContent(ibin)/integral);
    }
    return normalizedhists;
}


std::vector<TH1*> GetQuarkYields(TDirectoryFile* ifile, const std::string& selection_, const std::string& weight_)
{
    const char* selection = selection_.c_str();
    const char* weight = weight_.c_str();
    std::vector<TH1*> quark_hists(quarks::totNum,nullptr);
    // load b
    quark_hists[quarks::b] =
        histFactory_jetPt_TreeSelection(ifile, Form("(%s&&%s) * %s",selection, "jetHadFlvr==5", weight) );
    SetHistProperty(quark_hists[quarks::b], colors[0], "bYield", "b quark");
    // load c
    quark_hists[quarks::c] =
        histFactory_jetPt_TreeSelection(ifile, Form("(%s&&%s) * %s",selection, "jetHadFlvr==4", weight) );
    SetHistProperty(quark_hists[quarks::c], colors[1], "cYield", "c quark");
    // load L
    quark_hists[quarks::L] =
        histFactory_jetPt_TreeSelection(ifile, Form("(%s&&%s) * %s",selection, "jetHadFlvr==0", weight) );
    SetHistProperty(quark_hists[quarks::L], colors[2], "LYield", "light quark");

    return quark_hists;
}

std::vector<TH1*> GetQuarkCompositions(TDirectoryFile* ifile, const std::string& selection_, const std::string& weight_)
{
    const char* selection = selection_.c_str();
    const char* weight = weight_.c_str();
    std::vector<TH1*> quark_hists(quarks::totNum,nullptr);
    // load b
    quark_hists[quarks::b] =
        histFactory_jetPt_TreeSelection(ifile, Form("(%s&&%s) * %s",selection, "jetHadFlvr==5", weight) );
    SetHistProperty(quark_hists[quarks::b], colors[0], "bComposition", "b quark");
    // load c
    quark_hists[quarks::c] =
        histFactory_jetPt_TreeSelection(ifile, Form("(%s&&%s) * %s",selection, "jetHadFlvr==4", weight) );
    SetHistProperty(quark_hists[quarks::c], colors[1], "cComposition", "c quark");
    // load L
    quark_hists[quarks::L] =
        histFactory_jetPt_TreeSelection(ifile, Form("(%s&&%s) * %s",selection, "jetHadFlvr==0", weight) );
    SetHistProperty(quark_hists[quarks::L], colors[2], "LComposition", "light quark");

    normalization_eachBinBackToOne(quark_hists);

    return quark_hists;
}
class MyLegend : public TLegend
{
public:
    MyLegend(double x1, double y1, double x2, double y2) : TLegend(x1,y1,x2,y2)
    {
        SetFillColor(4000);
        SetFillStyle(4000);
        SetBorderSize(0);
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
    }
};
void qcdCHECKER_plotQuarkCompositionSep_differentSelection()
{
    TFile* ifile = TFile::Open("/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root");

    TFile* ofile = new TFile("_qcdCHECKER_plotQuarkCompositionSep_differentSelection_C.root", "RECREATE");
    TCanvas* canv = new TCanvas("canv", "", 1000,1000);

    std::list< std::pair<const char*, std::vector<TH1*>> > recordedHists;
    
    std::string tag;
    std::string cut;
    std::string weight;
    std::string basicCuts = "(fabs(recoSCEta)<1.4442||(fabs(recoSCEta)<2.5&&fabs(recoSCEta)>1.566) && MET/recoPt<0.7 && eleVeto!=0 && ( (fabs(recoSCEta)<1.5&&sieieFull5x5<0.012&&HoverE<0.08) || (fabs(recoSCEta)>1.5&&sieieFull5x5<0.027&&HoverE<0.05) )";

    {
        tag = "rawSign";
        cut = "fabs(chIsoRaw)<2";
        weight="puwei*mcweight";
        //recordedHists.push_back( std::make_pair(tag.c_str(),GetQuarkCompositions(ifile,cut,weight)) );
        std::vector<TH1*> yields = GetQuarkYields(ifile,cut,weight);
        std::vector<TH1*> compositions = normalizeToOne(yields);
        yields.insert(yields.end(), compositions.begin(), compositions.end());

        recordedHists.push_back( std::make_pair(tag.c_str(),yields) );
        for ( TH1* hist : recordedHists.back().second )
        { hist->SetName( Form("%s_%s", tag.c_str(), hist->GetName()) ); hist->Write(); }
    }

    {
        tag = "rawFake";
        cut = "fabs(chIsoRaw)>6 && fabs(chIsoRaw)<13";
        weight="puwei*mcweight";
        //recordedHists.push_back( std::make_pair(tag.c_str(),GetQuarkCompositions(ifile,cut,weight)) );
        std::vector<TH1*> yields = GetQuarkYields(ifile,cut,weight);
        std::vector<TH1*> compositions = normalizeToOne(yields);
        yields.insert(yields.end(), compositions.begin(), compositions.end());

        recordedHists.push_back( std::make_pair(tag.c_str(),yields) );
        for ( TH1* hist : recordedHists.back().second )
        { hist->SetName( Form("%s_%s", tag.c_str(), hist->GetName()) ); hist->Write(); }
    }

    {
        tag = "cutSign";
        cut = "passMaxPUcut && fabs(chIsoRaw)<2";
        weight="weight_passMaxPUcut*puwei*mcweight";
        //recordedHists.push_back( std::make_pair(tag.c_str(),GetQuarkCompositions(ifile,cut,weight)) );
        std::vector<TH1*> yields = GetQuarkYields(ifile,cut,weight);
        std::vector<TH1*> compositions = normalizeToOne(yields);
        yields.insert(yields.end(), compositions.begin(), compositions.end());

        recordedHists.push_back( std::make_pair(tag.c_str(),yields) );
        for ( TH1* hist : recordedHists.back().second )
        { hist->SetName( Form("%s_%s", tag.c_str(), hist->GetName()) ); hist->Write(); }
    }

    {
        tag = "cutFake";
        cut = "passMaxPUcut && fabs(chIsoRaw)>6 && fabs(chIsoRaw)<13";
        weight="weight_passMaxPUcut*puwei*mcweight";
        //recordedHists.push_back( std::make_pair(tag.c_str(),GetQuarkCompositions(ifile,cut,weight)) );
        std::vector<TH1*> yields = GetQuarkYields(ifile,cut,weight);
        std::vector<TH1*> compositions = normalizeToOne(yields);
        yields.insert(yields.end(), compositions.begin(), compositions.end());

        recordedHists.push_back( std::make_pair(tag.c_str(),yields) );
        for ( TH1* hist : recordedHists.back().second )
        { hist->SetName( Form("%s_%s", tag.c_str(), hist->GetName()) ); hist->Write(); }
    }

    ofile->Close();
    return;
}

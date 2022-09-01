#include "CompareYields.h"

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
namespace pt = boost::property_tree;
bool InclusivePhoton(int jetbin) { return jetbin == 2; }
bool IsPhoEndCap    (int phobin) { return phobin == 1; }
bool IsJetEndCap    (int jetbin) { return (!InclusivePhoton(jetbin)) && jetbin == 1; }
std::vector<float> ptbin_ranges()
{
  // for 2016
  //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,100000}; // size = 16. ptbin = [0,15]
  //std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15] // old
    std::vector<float> vec_ptcut{25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
  return vec_ptcut;
}
struct LumiRecorder
{
    LumiRecorder() {}
    LumiRecorder( const char* jsonfile )
    { LoadFile(jsonfile); }

    void LoadFile( const char* jsonfile )
    {
        pt::ptree root;
        pt::read_json(jsonfile, root);
        
        _ptbins.clear();
        _HLTName.clear();
        _lumi.clear();
        for ( pt::ptree::value_type& item : root.get_child("bin") )
            _ptbins. push_back( std::stoi(item.second.data()) );
        for ( pt::ptree::value_type& item : root.get_child("HLTNames") )
            _HLTName.push_back( item.second.data() );
        for ( pt::ptree::value_type& item : root.get_child("effectiveLuminosity") )
            _lumi.   push_back( std::stof(item.second.data()) );
    }

    float GetLumi(int ptbin) const
    {
        for ( int ibin = 0; ibin < _ptbins.size(); ++ibin )
            if ( ptbin == _ptbins[ibin] )
                return _lumi[ibin];
        return -1.;
    }
    float GetLumiSafe(int ptbin) const
    {
        float lumi = GetLumi(ptbin);
        if ( lumi < 0. ) throw Form(" -> pt bin %d not found. please check...\n", ptbin);
        return lumi;
    }

    std::vector<int> _ptbins;
    std::vector<std::string> _HLTName;
    std::vector<float> _lumi;
};
struct JsonInfo
{
    JsonInfo( const char* jsonfile )
    {
        pt::ptree root;
        pt::read_json(jsonfile, root);
        markerstyle = root.get<int>("MarkerStyle", 1);
        markercolor = root.get<int>("MarkerColor", 1);

        label   = root.get<std::string>("Label", "");
        TString tester = label;
        if ( tester.Contains(".") ) throw " -> Label contains '.', which is a preserved word.";
        title   = root.get<std::string>("Title", "");
        datfile = root.get<std::string>("DATfile", "");
        lumifile= LumiRecorder(jsonfile);
    }
    JsonInfo()
    {
        markerstyle = 8;
        markercolor = 38;

        label   = "2015";
        title   = "2015 ReReco from RS result";
        datfile = "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/15yield_noInclusivePho_newformat.dat";
        lumifile= LumiRecorder("effLumi_2016.json");
    }
    float GetLumiForPtBin(int ptbin) const
    { return lumifile.GetLumiSafe(ptbin); }
    std::string datfile;
    std::string label;
    std::string title;
    LumiRecorder lumifile;
    int markerstyle;
    int markercolor;
    //const char* Naming(const char* nTemplate) const { return Form(nTemplate, ebee, jetbin, ptbin); }
};

NewHistInSquareMatrix1D* FilledHists( const JsonInfo& args )
{
    DATTree* data_base = new DATTree( args.datfile.c_str() );
    //NewHistInSquareMatrix1D* binnedHists = new NewHistInSquareMatrix1D( args.histnaming.c_str(), {data_base->MaxBin_EtaBin(), data_base->MaxBin_JetBin()} );
    NewHistInSquareMatrix1D* binnedHists = new NewHistInSquareMatrix1D( (args.label+".%d_%d").c_str(), {data_base->MaxBin_EtaBin(), data_base->MaxBin_JetBin()} );
    std::vector<float> ptranges = ptbin_ranges();
    float* ptcut = &ptranges.front();
    int nbin = ptranges.size()-1;
    nbin=22;
    binnedHists->SetXaxis( nbin, ptcut );

    for ( Long64_t ievt = 0; ievt != data_base->GetEntries(); ++ievt )
    {
        data_base->GetEntry(ievt);
        TH1* hist = binnedHists->get({data_base->etabin, data_base->jetbin});
        int ibin = data_base->ptbin + 1;
        float denuminator = args.GetLumiForPtBin(data_base->ptbin) * hist->GetBinWidth(ibin);
        hist->SetBinContent( ibin, data_base->fityield / denuminator );

        float staterr = sqrt(data_base->fityield) / denuminator;
        hist->SetBinError( ibin, staterr );
        printf("-- checking -- ptbin %2d got luminosity : %10.4f\n", data_base->ptbin, args.GetLumiForPtBin(data_base->ptbin) );
    }
    delete data_base;
    return binnedHists;
}
TString Label( TH1* h )
{
    TString hname( h->GetName() );
    hname.Remove( hname.Index(".") );
    return hname;
}



void HistSetup(NewHistInSquareMatrix1D* hists, const JsonInfo& args)
{
    for ( unsigned iHist = 0; iHist != hists->size(); ++iHist )
    {
        TH1F* hist = hists->at(iHist);

        hist->SetMaximum( hist->GetMaximum() * 1e2 );
        hist->SetNdivisions(505,"XY");
        hist->SetXTitle("p_{T} (GeV)");
        hist->SetYTitle("Entries / Lumi / GeV");
        hist->GetXaxis()->SetRangeUser(0,1000);
        hist->SetMarkerColor(args.markercolor);
        hist->SetMarkerStyle(args.markerstyle);
        hist->SetLineColor(args.markercolor);
        hist->SetLineWidth(2);
        hist->GetYaxis()->SetTitleOffset(1.29);
        hist->GetYaxis()->SetTitleSize(0.035);
        hist->SetTitle( args.title.c_str() );
        hist->SetStats(false);
    }
}

void DrawCmpPlot( NewHistInSquareMatrix1D const * hist_ref, NewHistInSquareMatrix1D const * hist_new )
{
    printf("Entering DrawCmpPlot() block\n");
    TCanvas* c1 = new TCanvas("c1", "", 1000,1200);
    c1->SetFillColor(4000);
    c1->SetFillStyle(4000);
    TPad *pad1 = new TPad("pad1","pad1",0,0.25,1,1);
    pad1->SetBottomMargin(0);
    pad1->SetFillColor(4000);
    pad1->SetFillStyle(4000);
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy();

    c1->cd();
    TPad *pad2 = new TPad("pad2","pad2",0,0.0,1,0.25);
    pad2->SetTopMargin(0);
    pad2->SetFillColor(4000);
    pad2->SetFillStyle(4000);
    pad2->Draw();
    pad2->cd();
    pad2->SetGridy();
    if ( hist_new->size() != hist_ref->size() ) throw std::runtime_error( Form("input histgroms size mismatched! (%d and %d)\n", hist_new->size(), hist_ref->size()) );
    printf("Main Loops in DrawCmpPlot()\n");
    for ( unsigned histidx = 0; histidx != hist_new->size() ; ++histidx )
    {
        const std::vector<unsigned>& bins = hist_new->DecodeIdx(histidx);
        unsigned etabin = bins.at(0);
        unsigned jetbin = bins.at(1);

        TH1F* const h1 = hist_new->at(histidx);
        TH1F* const h2 = hist_ref->at(histidx);
        TH1* axis = h1->GetMaximum() > h2->GetMaximum() ? (TH1*)h1->Clone() : (TH1*)h2->Clone();
        axis->SetTitle("");


        pad1->cd();
        axis->Draw("axis");
        h1->Draw("p e0 SAME");
        h2->Draw("p e0 SAME");

        const char* phoEBmesg = "|#eta_{#gamma}|<1.4442";
        const char* phoEEmesg = "1.566<|#eta_{#gamma}|<2.5";
        const char* jetEBmesg = "|#eta_{jet}|<1.5";
        const char* jetEEmesg = "1.5<|#eta_{jet}|<2.4";

        char title[200];
        if ( InclusivePhoton(jetbin) )
            sprintf(title, "CMS 13TeV, %s", IsPhoEndCap(etabin) ? phoEEmesg : phoEBmesg);
        else
            sprintf(title, "CMS 13TeV, %s, %s",
                    IsPhoEndCap(etabin) ? phoEEmesg : phoEBmesg,
                    IsJetEndCap(jetbin) ? jetEEmesg : jetEBmesg
                   );

        TLegend *tleg = new TLegend(0.3, 0.68, 0.85, 0.88);

        tleg->SetHeader(title);
        tleg->SetFillColor(0);
        tleg->SetShadowColor(0);
        tleg->SetBorderSize(0);

        tleg->AddEntry(h1,h1->GetTitle(),"pl");
        tleg->AddEntry(h2,h2->GetTitle(),"pl");
        tleg->Draw();
        c1->Update();

        pad2->cd();
        TH1* ratioplot = (TH1*) h1->Clone();
        ratioplot->Divide(h2);
        ratioplot->SetMarkerStyle(21);


        ratioplot->GetYaxis()->SetTitle( Form("%s / %s", Label(h1).Data(), Label(h2).Data()) );
        ratioplot->GetYaxis()->SetTitleSize(0.10);
        ratioplot->GetYaxis()->SetTitleOffset(0.45);
        ratioplot->GetYaxis()->SetLabelSize(0.09);
        //ratioplot->GetXaxis()->SetTitle( h1->GetXaxis()->GetTitle() );
        ratioplot->GetXaxis()->SetTitleOffset(1.2);
        //ratioplot->GetXaxis()->SetTitleOffset(0.);
        ratioplot->GetXaxis()->SetTitleSize(0.10);
        ratioplot->GetXaxis()->SetLabelSize(0.09);
        ratioplot->GetXaxis()->SetTickSize(0.12);
        ratioplot->SetTitle("");
        ratioplot->Draw("ep");
        ratioplot->GetYaxis()->SetRangeUser(0.5,1.5);
        ratioplot->GetXaxis()->SetRangeUser(0,1000);


        char phoEBEE[10], jetEBEE[10];
        if ( etabin==0 ) sprintf(phoEBEE,"phoEB");
        if ( etabin==1 ) sprintf(phoEBEE,"phoEE");
        if ( jetbin==0 ) sprintf(jetEBEE,"jetEB");
        if ( jetbin==1 ) sprintf(jetEBEE,"jetEE");
        if ( jetbin==2 ) sprintf(jetEBEE,"jetAll");
        c1->SaveAs(Form("ratio_%s_%s.png",phoEBEE, jetEBEE));
        c1->SaveAs(Form("ratio_%s_%s.pdf",phoEBEE, jetEBEE));
        delete ratioplot;
        delete tleg;
    }
    printf("Deleting declared pads and canvas\n");
    delete pad1;
    delete pad2;
    delete c1;
    printf("DrawCmpPlots function ended...\n");
}

void CompareYields( const JsonInfo& info_ref, const JsonInfo& info_new )
{
    NewHistInSquareMatrix1D* binnedHists_ref = FilledHists( info_ref );
    NewHistInSquareMatrix1D* binnedHists_new = FilledHists( info_new );
    HistSetup( binnedHists_ref, info_ref );
    HistSetup( binnedHists_new, info_new );
    DrawCmpPlot( binnedHists_ref, binnedHists_new );

    delete binnedHists_ref;
    delete binnedHists_new;
}

void CompareYields( const char* arg_ref, const char* arg_new )
{
    JsonInfo info_ref(arg_ref);
    JsonInfo info_new(arg_new);
    CompareYields(info_ref, info_new);
}
void CompareYields( const char* newDATfile )
{
    JsonInfo info_ref;
    JsonInfo info_new;
    info_new.markerstyle = 22;
    info_new.markercolor = 39;
    info_new.title = "testing 2016";
    info_new.label = "New";
    info_new.datfile = newDATfile;

    CompareYields(info_ref, info_new);
}
void tester()
{
    JsonInfo a;
    for ( int i=0; i<10; ++i )
        std::cout << "lumi : " << a.lumifile.GetLumiSafe(i) <<std::endl;
}

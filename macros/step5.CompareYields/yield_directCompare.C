#include "DrawYield.h"

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
  std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 16. ptbin = [0,15]
  return vec_ptcut;
}
struct JsonInfo
{
    JsonInfo( const char* jsonfile )
    {
        pt::ptree root;
        pt::read_json(jsonfile, root);
        luminosity  = root.get<float>("luminosity", 0.);
        markerstyle = root.get<int>("MarkerStyle", 1);
        markercolor = root.get<int>("MarkerColor", 1);

        label   = root.get<std::string>("Label", "");
        datfile     = root.get<std::string>("DATfile", "");
        histnaming  = root.get<std::string>("histnaming", "");
    }
    //JsonInfo(const JsonInfo& input) {}
    JsonInfo() {} 
    std::string datfile;
    std::string histnaming;
    std::string label;
    float luminosity;
    int markerstyle;
    int markercolor;
    //const char* Naming(const char* nTemplate) const { return Form(nTemplate, ebee, jetbin, ptbin); }
};
struct DATTree
{
    DATTree( const char* datfile ) :
        _tree( new TTree() )
    {
        _tree->ReadFile(datfile);

        // asdf no matter signal or fake photon, all sample uses "bkg" and "bkg_err". (needed to be modified
        if (!_tree->FindBranch("fitvalue") ) throw std::runtime_error("DATTree::DATTree(); input dat file is not loaded or not fake yield. Please check input dat file\n");
        _tree->SetBranchAddress("ptbin"  , &ptbin);
        _tree->SetBranchAddress("EBEE"   , &etabin);
        _tree->SetBranchAddress("jetbin" , &jetbin);
        _tree->SetBranchAddress("fitvalue"    , &fityield);
        _tree->SetBranchAddress("fiterror", &fityield_err);

        _ptmax  = _tree->GetMaximum("ptbin" ) + 1;
        _etamax = _tree->GetMaximum("EBEE"  ) + 1;
        _jetmax = _tree->GetMaximum("jetbin") + 1;
    }
    ~DATTree()
    { delete _tree; printf("~DATTree() : Loaded Tree Closed\n"); }
    void GetEntry( Long64_t ievt ) { _tree->GetEntry(ievt); }
    Long64_t GetEntries() { return _tree->GetEntries(); }

    Int_t MaxBin_PtBin () { return _ptmax;  }
    Int_t MaxBin_EtaBin() { return _etamax; }
    Int_t MaxBin_JetBin() { return _jetmax; }

    TTree* GetTree() { return _tree; }

    TTree *_tree;
    Int_t   ptbin;
    Int_t   etabin;
    Int_t   jetbin;
    Float_t fityield;
    Float_t fityield_err;

    Int_t  _ptmax;
    Int_t  _etamax;
    Int_t  _jetmax;
};

NewHistInSquareMatrix1D* FilledHists( const JsonInfo& args )
{
    DATTree* data_base = new DATTree( args.datfile.c_str() );
    NewHistInSquareMatrix1D* binnedHists = new NewHistInSquareMatrix1D( args.histnaming.c_str(), {data_base->MaxBin_EtaBin(), data_base->MaxBin_JetBin()} );
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
        float denuminator = args.luminosity * hist->GetBinWidth(ibin);
        hist->SetBinContent( ibin, data_base->fityield / denuminator );

        float staterr = sqrt(data_base->fityield) / denuminator;
        hist->SetBinError( ibin, staterr );
    }
    delete data_base;
    return binnedHists;
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
        hist->GetYaxis()->SetTitleOffset(1.2);
        hist->SetTitle( args.label.c_str() );
        hist->SetStats(false);
    }
}

void DrawCmpPlot( NewHistInSquareMatrix1D const * hist1, NewHistInSquareMatrix1D const * hist2 )
{
    printf("Entering DrawCmpPlot() block\n");
    TCanvas* c1 = new TCanvas("c1", "", 1000,1200);
    TPad *pad1 = new TPad("pad1","pad1",0,0.2,1,1);
    pad1->SetBottomMargin(0);
    pad1->Draw();
    pad1->cd();
    pad1->SetLogy();

    c1->cd();
    TPad *pad2 = new TPad("pad2","pad2",0,0.00,1,0.2);
    pad2->SetTopMargin(0);
    pad2->Draw();
    pad2->cd();
    pad2->SetGridy();
    if ( hist1->size() != hist2->size() ) throw std::runtime_error( Form("input histgroms size mismatched! (%d and %d)\n", hist1->size(), hist2->size()) );
    printf("Main Loops in DrawCmpPlot()\n");
    for ( unsigned histidx = 0; histidx != hist1->size() ; ++histidx )
    {
        const std::vector<unsigned>& bins = hist1->DecodeIdx(histidx);
        unsigned etabin = bins.at(0);
        unsigned jetbin = bins.at(1);

        TH1F* const h1 = hist1->at(histidx);
        TH1F* const h2 = hist2->at(histidx);
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

        TLegend *tleg = new TLegend(0.4, 0.68, 0.88, 0.88);

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


        ratioplot->GetYaxis()->SetTitle( Form("%s / %s", h1->GetTitle(), h2->GetTitle()) ); //asdf
        ratioplot->GetYaxis()->SetTitleSize(0.15);
        ratioplot->GetYaxis()->SetTitleOffset(0.3);
        ratioplot->GetYaxis()->SetLabelSize(0.12);
        ratioplot->GetXaxis()->SetTitleOffset(1.2);
        ratioplot->GetXaxis()->SetTitleSize(0.15);
        ratioplot->GetXaxis()->SetLabelSize(0.15);
        ratioplot->GetXaxis()->SetTickSize(0.12);
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

void yield_directCompare( const char* arg1, const char* arg2 )
{
    JsonInfo inputarg1(arg1);
    JsonInfo inputarg2(arg2);
    NewHistInSquareMatrix1D* binnedHists_2015 = FilledHists( inputarg1 );
    NewHistInSquareMatrix1D* binnedHists_2016 = FilledHists( inputarg2 );
    HistSetup( binnedHists_2015, inputarg1 );
    HistSetup( binnedHists_2016, inputarg2 );
    DrawCmpPlot( binnedHists_2015, binnedHists_2016 );

    delete binnedHists_2015;
    delete binnedHists_2016;
}


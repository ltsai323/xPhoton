#include <exception>
//#include "../ComparisonPlot_FitOverTruth.C"
#include "../hi.h"
#include <memory>
// ROOT default fillStyle = 1001
static
void Visualization( TH1* h, const char* xtitle, int color=2, int fillstyle=0, int markersize=0 )
{
    h->SetStats(false);
    h->SetTitle("");
    h->GetXaxis()->SetTitle(xtitle);
    h->GetYaxis()->SetTitle("Entries");
    if ( markersize != 0 )
    {
        h->SetLineWidth(4);
        h->SetLineColor(color);
        h->SetMarkerSize(markersize);
        h->SetMarkerColor(color);
        h->SetMarkerStyle(33);
        return;
    }
    if ( fillstyle != 0 )
    {
        h->SetFillColor(color);
        h->SetFillStyle(fillstyle);
        return;
    }
    std::cerr << "nothing setup in " << h->GetName() << std::endl;
    return;
}

std::vector<float> ptbin_ranges()
{
    // for 2016
    std::vector<float> vec_ptcut{25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000}; // size = 25. ptbin = [0,24]
    return vec_ptcut;
}
class LoadedWorkspace
{
public:
    LoadedWorkspace( const char* ifile, const char* spacename = "space" );
    ~LoadedWorkspace();
    void SetVar(const char* varname);
    RooRealVar* UseVar();
    void Cleaning();
    void GenerateFakeDataset(MyBin thebin);
    void PerformFit(MyBin thebin);
    void DrawFitRes(MyBin thebin);
    void DrawTruthComparison(MyBin thebin);

    RooExtendPdf GetExtended(const char* histname, int integral);
    

    int truth_sig, truth_bkg;
    float fitval_sig, fitval_bkg;
    float fiterr_sig, fiterr_bkg;
private:
    TFile* _infile;
    RooWorkspace* _space;
    TCanvas* _canv;
    RooRealVar* _MYvarObj;

    RooDataSet* _MYtargetObj;

    RooRealVar*   numvar;
    //RooAbsPdf*    numpdf;
    RooHistPdf*    numpdf;
};
const char* PhoEtaRegion(int etabin);
const char* JetEtaRegion(int etabin);

void FakeSampleCreation()
{
    LoadedWorkspace lspace("fitres_workspace.root");
    lspace.SetVar("BDTscore");

    const int NUM_PHOPT  = 20;
    const int NUM_PHOETA = 2;
    const int NUM_JETETA = 2;

    TH1* hsig_fit  [NUM_PHOETA][NUM_JETETA];
    TH1* hsig_truth[NUM_PHOETA][NUM_JETETA];
    TH1* hbkg_fit  [NUM_PHOETA][NUM_JETETA];
    TH1* hbkg_truth[NUM_PHOETA][NUM_JETETA];
    std::vector<float> ptranges = ptbin_ranges();


    TCanvas* c = new TCanvas("maincanv", "", 1200,1000);
    c->SetFillColor(4000);
    c->SetFillStyle(4000);
    for ( int phoeta = 0; phoeta < NUM_PHOETA; ++phoeta )
        for ( int jeteta = 0; jeteta < NUM_JETETA; ++jeteta )
        {
            hsig_fit  [phoeta][jeteta] = new TH1F( Form("hsigfit_%d_%d"  ,phoeta,jeteta), "", NUM_PHOPT, &(ptranges.front()) );
            hsig_truth[phoeta][jeteta] = new TH1F( Form("hsigtruth_%d_%d",phoeta,jeteta), "", NUM_PHOPT, &(ptranges.front()) );
            hbkg_fit  [phoeta][jeteta] = new TH1F( Form("hbkgfit_%d_%d"  ,phoeta,jeteta), "", NUM_PHOPT, &(ptranges.front()) );
            hbkg_truth[phoeta][jeteta] = new TH1F( Form("hbkgtruth_%d_%d",phoeta,jeteta), "", NUM_PHOPT, &(ptranges.front()) );
            Visualization( hsig_fit  [phoeta][jeteta], "BDT score", 46, 0, 2);
            Visualization( hsig_truth[phoeta][jeteta], "BDT score", 44, 1001);
            Visualization( hbkg_fit  [phoeta][jeteta], "BDT score",  9, 0, 2);
            Visualization( hbkg_truth[phoeta][jeteta], "BDT score", 40, 1001);
            for ( int phopt = 0; phopt < NUM_PHOPT; ++phopt )
            {
                MyBin thisbin(phoeta, jeteta, phopt);
                lspace.GenerateFakeDataset(thisbin);
                lspace.PerformFit(thisbin);
                //lspace.DrawFitRes(thisbin);
                //lspace.DrawTruthComparison(thisbin);

                hsig_fit   [phoeta][jeteta]->SetBinContent(phopt+1, lspace.fitval_sig);
                hsig_fit   [phoeta][jeteta]->SetBinError  (phopt+1, lspace.fiterr_sig);
                hsig_truth [phoeta][jeteta]->SetBinContent(phopt+1, lspace.truth_sig);
                hbkg_fit   [phoeta][jeteta]->SetBinContent(phopt+1, lspace.fitval_bkg);
                hbkg_fit   [phoeta][jeteta]->SetBinError  (phopt+1, lspace.fiterr_bkg);
                hbkg_truth [phoeta][jeteta]->SetBinContent(phopt+1, lspace.truth_bkg);
            }
            c->cd();
            c->SetFillColor(4000);
            c->SetFillStyle(4000);


            MyLegend leg(0.35, 0.65, 0.85, 0.85);
            leg.SetHeader( Form("%s, %s", PhoEtaRegion(phoeta), JetEtaRegion(jeteta)) );
            leg.AddEntry(hsig_fit  [phoeta][jeteta], "Yield from fitting"  , "lp");
            leg.AddEntry(hsig_truth[phoeta][jeteta], "Yield from Truth", "f");
            leg.AddEntry(hbkg_fit  [phoeta][jeteta], "Fake from fitting"  , "lp");
            leg.AddEntry(hbkg_truth[phoeta][jeteta], "Fake from truth", "f");

            MyRatioPlot ptSIGspectrum( hsig_fit[phoeta][jeteta], hsig_truth[phoeta][jeteta] );
            MyRatioPlot ptBKGspectrum( hbkg_fit[phoeta][jeteta], hbkg_truth[phoeta][jeteta] );


            ptSIGspectrum.UseLogy(true);
            ptSIGspectrum.OptimizePlots();
            ptBKGspectrum.OptimizePlots();
            //ptSIGspectrum.PlotOn(c);
            TPad* upperpad = ptSIGspectrum.PlotUpperAxis(c);
            upperpad->cd();
            ptSIGspectrum.PlotUpperContent( upperpad );
            ptBKGspectrum.PlotUpperContent( upperpad, leg.PassLegend() );

            TPad* lowerpad = ptSIGspectrum.PlotLowerAxis(c);
            lowerpad->cd();
            ptSIGspectrum.PlotLowerContent( lowerpad );
            ptBKGspectrum.PlotLowerContent( lowerpad );
            c->SaveAs( Form("ptspectrum_%d_%d.C",phoeta,jeteta) );
            c->SaveAs( Form("ptspectrum_%d_%d.pdf",phoeta,jeteta) );
        }
}







/// function definitions {{{
LoadedWorkspace::LoadedWorkspace( const char* ifile, const char* spacename ) :
    truth_sig(0), truth_bkg(0), fitval_sig(0.), fitval_bkg(0.), fiterr_sig(0.),fiterr_bkg(0.),
    _MYtargetObj(nullptr),
    numvar(nullptr),numpdf(nullptr)
{
    _infile = TFile::Open( ifile );
    _space = (RooWorkspace*) _infile->Get(spacename);
    _canv = new TCanvas("_canv","", 1200,1000);
    _canv->SetFillColor(4000);
    _canv->SetFillStyle(4000);
}
LoadedWorkspace::~LoadedWorkspace()
{
    if ( _MYtargetObj != nullptr ) delete _MYtargetObj;
    if ( numvar != nullptr ) delete numvar;
    if ( numpdf != nullptr ) delete numpdf;
    delete _canv;
    _infile->Close();
}
void LoadedWorkspace::SetVar(const char* varname)
{ _MYvarObj = (RooRealVar*) _space->var(varname); }
RooRealVar* LoadedWorkspace::UseVar()
{ if ( _MYvarObj == nullptr ) throw "You need to execute 'SetVar()' first\n"; return _MYvarObj; }
void LoadedWorkspace::Cleaning()
{
    if ( _MYtargetObj == nullptr ) return;
    delete _MYtargetObj;
    _MYtargetObj = nullptr;
    truth_sig = truth_bkg = 0;
    fitval_sig = fitval_bkg = fiterr_sig = fiterr_bkg = 0.;
}
void LoadedWorkspace::GenerateFakeDataset(MyBin thebin)
{
    RooRealVar* MYvarObj = this->UseVar();
    this->Cleaning();
    auto origdata_sig = (RooHistPdf*)_space->pdf( thebin.naming("pdf_sig.%d_%d_%d") );
    auto origdata_bkg = (RooHistPdf*)_space->pdf( thebin.naming("pdf_bkg.%d_%d_%d") );
    auto origvar_sig = (RooRealVar*)_space->var( thebin.naming("num_sig.%d_%d_%d") );
    auto origvar_bkg = (RooRealVar*)_space->var( thebin.naming("num_bkg.%d_%d_%d") );
    
    auto newdata_sig = (RooDataSet*) origdata_sig->generate(*MYvarObj, origvar_sig->getVal() );
    auto newdata_bkg = (RooDataSet*) origdata_bkg->generate(*MYvarObj, origvar_bkg->getVal() );

    _MYtargetObj = newdata_sig;
    _MYtargetObj->append(*newdata_bkg);
    truth_sig = origvar_sig->getVal();
    truth_bkg = origvar_bkg->getVal();
    delete newdata_bkg;
}
void LoadedWorkspace::PerformFit(MyBin thebin)
{
    auto fitpdf = (RooAbsPdf*) _space->pdf( thebin.naming("fitpdf.%d_%d_%d") );
    auto sigvar = (RooRealVar*)_space->var( thebin.naming("num_sig.%d_%d_%d") );
    auto bkgvar = (RooRealVar*)_space->var( thebin.naming("num_bkg.%d_%d_%d") );
    
    fitpdf->fitTo(*_MYtargetObj, RooFit::PrintLevel(-1) );
    fitval_sig = sigvar->getVal(); fiterr_sig = sigvar->getError();
    fitval_bkg = bkgvar->getVal(); fiterr_bkg = bkgvar->getError();
    printf("ptbin %d etabin %d jetbin %d fakefit result : SIG fit %.1f +- %.1f and Orig %d\n",
            thebin.phoPbin, thebin.phoEbin, thebin.jetEbin,
            fitval_sig, fiterr_sig, truth_sig);
    printf("ptbin %d etabin %d jetbin %d fakefit result : BKG fit %.1f +- %.1f and Orig %d\n",
            thebin.phoPbin, thebin.phoEbin, thebin.jetEbin,
            fitval_bkg, fiterr_bkg, truth_bkg);
}
void LoadedWorkspace::DrawFitRes(MyBin thebin)
{
    _canv->Clear();
    _canv->cd();
    RooPlot* xaxis = _MYvarObj->frame();

    _MYtargetObj->plotOn(xaxis, RooFit::Binning(10));
    auto fitpdf = (RooAddPdf*) _space->pdf( thebin.naming("fitpdf.%d_%d_%d") );
    fitpdf->plotOn(xaxis, RooFit::Name("fitpdf"),
            RooFit::LineWidth(4), RooFit::LineColor(2) );
    fitpdf->plotOn(xaxis, RooFit::Name("sigpdf"), RooFit::Components( thebin.naming("epdf_sig.%d_%d_%d") ),
            RooFit::LineWidth(3), RooFit::LineColor(38) );
    fitpdf->plotOn(xaxis, RooFit::Name("bkgpdf"), RooFit::Components( thebin.naming("epdf_bkg.%d_%d_%d") ),
            RooFit::LineWidth(3), RooFit::LineColor(43) );
    _MYtargetObj->plotOn(xaxis, RooFit::Binning(10), RooFit::MarkerSize(2));
    xaxis->Draw();
    _canv->SaveAs( thebin.naming("plots/fitterRes.%d_%d_%d.png") );
}
void LoadedWorkspace::DrawTruthComparison(MyBin thebin)
{ // modifing
    std::cerr << "hi01\n";
    _canv->Clear();
    _canv->cd();
    //TPad* upperpad = UpperPad(); upperpad->Draw();
    //TPad* lowerpad = LowerPad(); lowerpad->Draw();
    //upperpad->cd();
    std::cerr << "hi02\n";
    RooExtendPdf truthsig = GetExtended( thebin.naming("pdf_sig.%d_%d_%d"), truth_sig );
    std::cerr << "hi03\n";

    //TH1* h_truth = truthsig.createHistogram( "BDTscore", 10 );
    std::unique_ptr<TH1> h_truth( truthsig.createHistogram( "BDTscore", 10 ) );
    std::cerr << "hi04\n";
    float maxval = h_truth->GetMaximum() * 1.5;
    h_truth->SetMaximum(maxval);
    h_truth->SetMinimum(1e-3);
    h_truth->SetFillColor(38);
    h_truth->SetTitle("");
    h_truth->SetLineWidth(0);
    h_truth->SetStats(false);

    std::cerr << "hi04.1\n";
    std::cerr << "loaded pdf name " << thebin.naming("fitpdf.%d_%d_%d") << std::endl;
    //std::unique_ptr<RooAddPdf> fitpdf( (RooAddPdf*) _space->pdf( thebin.naming("fitpdf.%d_%d_%d") ) );
    std::cerr << "hi04.2\n";
    //asdf auto fitsig = (RooExtendPdf*) _space->pdf( fitpdf->pdfList()[0].GetName() );
    //asdf TH1* h_fit = fitsig->createHistogram( "BDTscore", 10 );
    //asdf std::unique_ptr<TH1> h_fit( fitsig->createHistogram( "BDTscore", 10 ) );
    //asdf std::cerr << "hi05\n";
    //asdf h_fit->SetMaximum(maxval);
    //asdf h_fit->SetMinimum(0.);
    //asdf h_fit->SetTitle("");
    //asdf h_fit->SetStats(false);
    //asdf h_fit->SetLineColor(2);
    //asdf h_fit->SetLineWidth(4);


    //asdf MyLegend leg(0.3,0.5,0.7,0.85);
    //asdf double fitval = sumEntries(h_fit.get());
    //asdf double chi2val = Chi2(h_fit.get(), h_truth.get());
    //asdf double absval = fabs( fitval - sumEntries(h_truth.get()) ) / sqrt(fitval);

    //asdf leg.SetHeader( Form("#chi^{2}/nDoF = %.2f / %d. Significance = %.1f", chi2val,h_fit->GetNbinsX()-1, absval) );
    //asdf leg.AddEntry(h_fit  , Form("Fitted val %.3g", fitval), "lp");
    //asdf leg.AddEntry(h_truth, Form("Truth val %.3g", sumEntries(h_truth)), "f");
    std::cerr << "hi06\n";
    //asdf MyRatioPlot ratios( h_fit.get(), h_truth.get(), leg.PassLegend() );
    std::cerr << "hi07\n";
    //asdf ratios.PlotOn(_canv);
    std::cerr << "hi08\n";


    /*
    RooPlot* xaxis = _MYvarObj->frame();
    truthsig.plotOn(xaxis, RooFit::Name("truthpdf"), RooFit::FillStyle(1),RooFit::FillColor(43),RooFit::DrawOption("F") );


    auto fitpdf = (RooAddPdf*) _space->pdf( thebin.naming("fitpdf.%d_%d_%d") );
    //fitpdf->plotOn(xaxis, RooFit::Name("fitpdf"),
    //        RooFit::LineWidth(4), RooFit::LineColor(2) );
    fitpdf->plotOn(xaxis, RooFit::Name("sigpdf"), RooFit::Components( thebin.naming("epdf_sig.%d_%d_%d") ),
            RooFit::DrawOption("EP"),
            RooFit::MarkerSize(2) );
            //RooFit::LineWidth(4), RooFit::LineColor(2) );
    //fitpdf->plotOn(xaxis, RooFit::Name("bkgpdf"), RooFit::Components( thebin.naming("epdf_bkg.%d_%d_%d") ),
    //        RooFit::LineWidth(3), RooFit::LineColor(43) );
    //_MYtargetObj->plotOn(xaxis, RooFit::Binning(10), RooFit::MarkerSize(2));
    xaxis->Draw();
    */
    //asdf _canv->SaveAs( thebin.naming("plots/sigtruth.%d_%d_%d.png") );
    std::cerr << "hi01\n";
}
RooExtendPdf LoadedWorkspace::GetExtended( const char* histname, int integral )
{
    if ( numvar != nullptr )
    { delete numvar; numvar = nullptr; }
    if ( numpdf != nullptr )
    { delete numpdf; numpdf = nullptr; }
    char numname[100];
    char epdfname[100];
    sprintf( numname, "truthnum_%s", histname );
    sprintf( epdfname, "truth_e%s", histname );

    numvar = new RooRealVar(numname,numname, integral);
    numpdf = (RooHistPdf*) _space->pdf(histname);

    return RooExtendPdf(epdfname, epdfname, *numpdf, *numvar);
}

const char* PhoEtaRegion( int etabin )
{
    if ( etabin == 1 )
        return "1.566 < | #eta_{#gamma} | < 2.5";
    else if ( etabin == 0 )
        return "| #eta_{#gamma} | < 1.4442";
    return Form("failed to find photon eta region. input phoeta bin is %d", etabin);
}
const char* JetEtaRegion( int etabin )
{
    if ( etabin == 1 )
        return "1.566 < | #eta_{jet} | < 2.5";
    else if ( etabin == 0 )
        return "| #eta_{jet} | < 1.4442";
    return Form("failed to find jet eta region. input jet eta bin is %d", etabin);
}
// function definitions end }}}

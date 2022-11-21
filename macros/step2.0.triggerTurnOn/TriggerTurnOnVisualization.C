#define MAXBIN 8
struct NamingTool
{
    NamingTool( int rangeidx_ ) : rangeidx(rangeidx_)
    { }
    const char* Name(const char* nametemplate, int idx0 = -1, int idx1 = -1)
    {
        if      ( idx0 < 0 )
            output.Form(nametemplate, rangeidx);
        else if ( idx1 < 0 )
            output.Form(nametemplate, rangeidx, idx0 );
        else
            output.Form(nametemplate, rangeidx, idx0, idx1 );
        return output.Data();
    }
    int rangeidx;
    TString output;
};
struct HLTbin
{
    HLTbin(int rangeidx_ )
    {
        hltbin = rangeidx_ == MAXBIN ? rangeidx_-1 : rangeidx_;
    }
    int Low() const { return hltbin; }
    int High() const { return hltbin + 1; }
    int hltbin;
};

void TriggerTurnOnVisualization( TFile* fin, int inbin )
{

    bool setTitle = true;
    const char* cuttitle = "phoPFChIso<2&&((phoIDbit>>2)&1) == 1 && phoIDMVA > 0.9  && fabs(phoEta) > 1.5 && phoEleVeto == 1";
    
    HLTbin hlt(inbin);
    NamingTool n(inbin);


    TH1* hLOW = (TH1*) fin->Get( n.Name("Range%d_passingHLT%d",hlt.Low()) );
    if ( setTitle) hLOW->SetTitle(cuttitle);
    hLOW->SetLineColor(43);
    hLOW->SetLineWidth(2);
    hLOW->SetStats(false);

    TH1* hHIGH = (TH1*) fin->Get( n.Name("Range%d_passingHLT%d",hlt.High()) );
    if ( setTitle) hHIGH->SetTitle(cuttitle);
    hHIGH->SetLineColor(38);
    hHIGH->SetLineWidth(2);
    hHIGH->SetStats(false);
    
    TH1* hHIGHOnly = (TH1*) fin->Get( n.Name("Range%d_passingHLT%dOnly",hlt.High()) );
    if ( setTitle) hHIGHOnly->SetTitle(cuttitle);
    hHIGHOnly->SetLineColor(46);
    hHIGHOnly->SetLineWidth(2);
    hHIGHOnly->SetStats(false);

    TH1* hTurnOn = (TH1*) fin->Get( n.Name("Range%d_triggerTurnOn") );
    if ( setTitle) hTurnOn->SetTitle(cuttitle);
    hTurnOn->SetLineColor(2);
    hTurnOn->SetLineWidth(4);
    hTurnOn->SetStats(false);


    TCanvas* c1 = new TCanvas("canv", "", 1000, 1000);
    TH1* hAxis = hHIGH;
    hAxis->GetXaxis()->SetTitle("Pt_#gamma (GeV)");
    hAxis->Draw("AXIS");

    hHIGH    ->Draw("SAME HIST");
    hHIGHOnly->Draw("SAME HIST");
    hLOW     ->Draw("SAME HIST");

    c1->Update();

    
    float rightAxisMax = 1.1 * hTurnOn->GetMaximum();
    float scale = gPad->GetUymax() / rightAxisMax;
    hTurnOn->Scale(scale);
    hTurnOn->Draw("SAME HIST");

    TGaxis* rightAxis = new TGaxis(
            gPad->GetUxmax(), gPad->GetUymin(), gPad->GetUxmax(), gPad->GetUymax(),
            0, rightAxisMax, 510, "+L" );
    rightAxis->SetLineColor(kRed);
    rightAxis->SetTextColor(kRed);
    rightAxis->Draw();

    TLegend* leg = new TLegend(0.15, 0.5, 0.55, 0.85);
    leg->AddEntry(hLOW       , Form("Passing HLT %d", hlt.Low())  , "l");
    leg->AddEntry(hHIGH      , Form("Passing HLT %d", hlt.High()) , "l");
    leg->AddEntry(hHIGHOnly  , Form("Passing HLT %d ONLY", hlt.High()), "l");
    leg->AddEntry(hTurnOn    , "Trigger Turn On curve", "l");
    leg->SetBorderSize(0);
    leg->SetFillColor(4000);
    leg->SetFillStyle(4000);
    leg->Draw();
    c1->SaveAs( n.Name("turnOnStat_Range%d.pdf") );

    delete c1;
    delete leg;
    delete rightAxis;
}
void TriggerTurnOnVisualization()
{
    TFile* fin = TFile::Open("HLTTurnOnChecking.root");
    for ( int i=0; i<=MAXBIN; ++i )
        TriggerTurnOnVisualization(fin, i);
}

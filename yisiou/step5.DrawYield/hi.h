#ifndef __MyLegend_H__
#define __MyLegend_H__

#define MAXPTBIN 25
TPad* UpperPad()
{
    TPad* pad = new TPad("Pad","Pad",0.,0.245,1.,0.98);
    pad->SetFillColor(4000);
    pad->SetFillStyle(4000);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.05);
    //pad->SetBottomMargin(0.019);
    pad->SetBottomMargin(0.021);
    pad->SetLeftMargin(0.135);//0.12
    pad->SetRightMargin(0.06);//0.12

    return pad;
}


TPad* LowerPad()
{
    TPad* pad = new TPad("Pad1","Pad1",0.,0.0,1.,0.250);
    pad->SetFillColor(4000);
    pad->SetFillStyle(4000);
    pad->SetTicks(1.,1.);
    pad->SetTopMargin(0.0);
    pad->SetBottomMargin(0.35);
    pad->SetLeftMargin(0.135);
    pad->SetRightMargin(0.06);

    return pad;
}
double FindMinimum(TH1* h)
{
    double val = h->GetBinContent(1);
    int ibin = h->GetNbinsX()+1;
    while (--ibin)
        if ( val > h->GetBinContent(ibin) ) val = h->GetBinContent(ibin);
    return val;
}
        

double FindMaximum(TH1* h)
{
    double val = h->GetBinContent(1);
    int ibin = h->GetNbinsX()+1;
    while (--ibin)
        if ( val < h->GetBinContent(ibin) ) val = h->GetBinContent(ibin);
    return val;
}
struct MyBin
{
public:
    MyBin( int phoeta, int jeteta, int phopt )
        : phoEbin(phoeta), jetEbin(jeteta), phoPbin(phopt) {}
    const char* naming( const char* nametemplate )
    { return Form(nametemplate, phoEbin, jetEbin, phoPbin); }
    int EncodedBin()
    { return MAXPTBIN * 2 * jetEbin + MAXPTBIN * phoEbin + phoPbin; }
    static int EncodedBin( int phoeta, int jeteta, int phopt )
    { return MAXPTBIN * 2 * jeteta + MAXPTBIN * phoeta + phopt; }

    int phoEbin, jetEbin, phoPbin;
};

class MyRatioPlot
{
public:
    MyRatioPlot( TH1* numeratorhist, TH1* denominatorhist, TLegend* legend = nullptr ) :
        _numeratorHist(numeratorhist),_denominatorHist(denominatorhist),
        _upperpad( UpperPad() ), _lowerpad( LowerPad() ),
        logy(false)
    {
        _numeratorHist->SetStats(false);
        _denominatorHist->SetStats(false);
        GetDividedHist();
    }
    ~MyRatioPlot()
    {
        delete _ratioHist;
        delete _upperpad;
        delete _lowerpad;
        delete _centerline;
    }
    void UseLogy(bool val = true)
    {
        logy=val;

        float M0 = FindMaximum(_numeratorHist);
        float M1 = FindMaximum(_denominatorHist);
        float MVal = M0 > M1 ? M0 * 1000. : M1 * 1000.;
        _denominatorHist->SetMinimum(1e-1);
        _denominatorHist->SetMaximum(MVal);

        _numeratorHist->SetMinimum(1e-1);
        _numeratorHist->SetMaximum(MVal);
    }

    void PlotUpperContent(TPad* p, TLegend* leg = nullptr)
    {
        p->cd();
        _denominatorHist->Draw("hist same");
        _numeratorHist->Draw("ep same");
        if ( leg ) leg->Draw();
    }
    void PlotLowerContent(TPad* p)
    {
        p->cd();
        _ratioHist->Draw("e0p same");
        _centerline->Draw();
    }
    TPad* PlotUpperAxis(TCanvas* c1)
    {
        c1->cd();
        _upperpad->Draw();
        _upperpad->cd();
        _numeratorHist->Draw("axis");

        return _upperpad;
    }
    TPad* PlotLowerAxis(TCanvas* c1)
    {
        c1->cd();
        _lowerpad->Draw();
        _lowerpad->cd();
        _ratioHist->Draw("axis");

        return _lowerpad;
    }


    void OptimizePlots()
    {
        float M0 = FindMaximum(_numeratorHist);
        float M1 = FindMaximum(_denominatorHist);
        float maxScaler = logy ? 1000. : 1.5;
        float MVal = M0 > M1 ? M0 * maxScaler : M1 * maxScaler;
        if ( MVal < 1. ) MVal = 2.;
        _denominatorHist->SetMinimum(1e-1);
        _denominatorHist->SetMaximum(MVal);

        _numeratorHist->SetMinimum(1e-1);
        _numeratorHist->SetMaximum(MVal);

        _denominatorHist->GetXaxis()->SetLabelSize(0);
        _denominatorHist->GetYaxis()->SetTitleOffset(0.95);
        _denominatorHist->GetYaxis()->SetTitleSize(0.06);

        _numeratorHist->GetXaxis()->SetLabelSize(0);
        _numeratorHist->GetYaxis()->SetTitleOffset(0.95);
        _numeratorHist->GetYaxis()->SetTitleSize(0.06);

        _centerline = GetLine(1.00);
        _upperpad->SetLogy(1);
    }
    void PlotOn(TCanvas* p, TLegend* leg = nullptr)
    {
        p->cd();

        OptimizePlots();
        _upperpad->Draw();
        _lowerpad->Draw();


        TPad* upperpad = PlotUpperAxis(p);
        upperpad->cd();

        PlotUpperContent( upperpad, leg );

        TPad* lowerpad = PlotLowerAxis(p);
        lowerpad->cd();
        PlotLowerContent( lowerpad );

        /*
        _lowerpad->cd();
        _ratioHist->Draw("e0p");
        _centerline->Draw();
        */
        p->Modified();
    }

private:
    TH1* _numeratorHist;
    TH1* _denominatorHist;
    TH1*   _ratioHist;
    TPad*  _upperpad;
    TPad*  _lowerpad;
    TLine* _centerline;
    bool logy;

    void GetDividedHist()
    {
        _ratioHist = (TH1*) _numeratorHist->Clone();
        int ibin = _ratioHist->GetNbinsX() + 1;

        double maxVal = 0.;
        double minVal = 1.;
        while ( --ibin )
        {
            double val_nu = _numeratorHist->GetBinContent(ibin);
            double val_de = _denominatorHist->GetBinContent(ibin);
            double err_nu = _numeratorHist->GetBinError(ibin);

            if ( val_de < 1e-3 )
            {
                _ratioHist->SetBinContent(ibin, 0.);
                _ratioHist->SetBinError  (ibin, 0.);
            }
            else
            {
                _ratioHist->SetBinContent(ibin, val_nu/val_de);
                _ratioHist->SetBinError  (ibin, err_nu/val_de);
            }
            
            double _v = val_de > 1e-3 ? val_nu / val_de : 0.;
            if ( _v > maxVal ) maxVal = _v;
            if ( _v < minVal ) minVal = _v;
        }

        auto yranges = findSuitableYrange(minVal,maxVal);
        _ratioHist->SetMinimum(yranges.first );
        _ratioHist->SetMaximum(yranges.second);

        // _ratioHist->SetMarkerColor(1);
        // _ratioHist->SetLineColor(1);
        // _ratioHist->SetMarkerSize(2);
        _ratioHist->GetXaxis()->SetLabelSize(0.1);
        _ratioHist->GetXaxis()->SetTitleSize(0.2);
        _ratioHist->GetXaxis()->SetTitleOffset(0.70);

        _ratioHist->GetYaxis()->SetNdivisions(505);
        _ratioHist->GetYaxis()->SetLabelSize(0.1);
        _ratioHist->GetYaxis()->SetTitle("ratio");
        _ratioHist->GetYaxis()->SetTitleOffset(0.3);
        _ratioHist->GetYaxis()->SetTitleSize(0.2);
    }
    TLine* GetLine(double yval_ = 1.0, int color_ = 1, int width_ = 1)
    {
        TLine* line = new TLine(
                _numeratorHist->GetBinLowEdge(1), yval_,
                _numeratorHist->GetBinLowEdge(_numeratorHist->GetNbinsX()+1), yval_ );
        line->SetLineColor(color_);
        line->SetLineWidth(width_);
        line->SetLineStyle(7);

        return line;
    }
    std::pair<float,float> findSuitableYrange(float minVal, float maxVal)
    {
        bool keepgoingon = true;
        if ( minVal > maxVal ) keepgoingon = false;
        if ( maxVal < 1e-3 || maxVal > 100. ) keepgoingon = false;
        if ( minVal < 1e-3 || minVal > 100. ) keepgoingon = false;
        if (!keepgoingon ) return std::pair<float,float>(0.,1.);

        float separator = 20.;

        float Mval = float(int(separator*maxVal)+2)/separator - 0.1/separator; // to avoid upper y label at lower pad
        float mval = float(int(separator*minVal)  )/separator;
        return std::pair<float,float>(mval,Mval);
    }
};

class MyLegend : public TLegend
{
public :
    MyLegend(float p0x, float p0y, float p1x, float p1y) : TLegend(p0x,p0y,p1x,p1y,"", "brNDC")
    {
        this->SetFillColor(4000);
        this->SetFillStyle(4000);
        this->SetBorderSize(0);
    }
    TLegend* PassLegend() { return this; }
};

#endif


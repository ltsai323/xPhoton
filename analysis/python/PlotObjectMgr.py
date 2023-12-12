#!/usr/bin/env python3
import ROOT

def UpperPad(name='upperpad'):
    pad=ROOT.TPad(name, name, 0., 0.245, 1., 0.98)
    pad.SetTicks(1,1)
    pad.SetTopMargin(0.05)
    pad.SetBottomMargin(0.019)
    pad.SetLeftMargin(0.135)
    pad.SetRightMargin(0.06)
    Transparent(pad)
    return pad
def LowerPad(name='lowerpad'):
    pad=ROOT.TPad(name, name, 0.,0.,1.,0.258)
    pad.SetTicks(1,1)
    pad.SetTopMargin(0.0)
    pad.SetBottomMargin(0.35)
    pad.SetLeftMargin(0.135)
    pad.SetRightMargin(0.06)
    Transparent(pad)
    return pad
def Transparent(pad):
    pad.SetFillColor(4000)
    pad.SetFillStyle(4000)
def Pad(name='pad'):
    pad=ROOT.TPad(name, name, 0.,0.,1.,0.98)
    pad.SetTicks(1,1)
    pad.SetTopMargin(0.05)
    pad.SetBottomMargin(0.12)
    pad.SetLeftMargin(0.135)
    pad.SetRightMargin(0.06)
    return pad
def Legend( p0_=(0.5,0.3), p1_=(0.89,0.89), title='', useNDC=True ):
    leg=ROOT.TLegend(p0_[0],p0_[1], p1_[0],p1_[1], title, 'NDC' if useNDC else '')
    leg.SetFillStyle(0)
    leg.SetBorderSize(0)
    leg.SetTextFont(62)
    return leg


def HistFraming( h, xLABEL='', yLABEL='', minFACTOR = 0.1, maxFACTOR = 1.5 ):
    h.SetMinimum( h.GetMinimum() * minFACTOR)
    h.SetMaximum( h.GetMaximum() * maxFACTOR)
    h.GetXaxis().SetTitle(xLABEL)
    h.GetXaxis().SetTitleSize(0.05)
    h.GetXaxis().SetLabelSize(0.03)

    h.GetYaxis().SetTitle(yLABEL)
    #h.GetYaxis().SetTitleSize(0.11)
    h.GetYaxis().SetTitleSize(0.04)
    h.GetYaxis().SetTitleOffset(0.8)
    h.GetYaxis().SetLabelSize(0.03)
    h.GetYaxis().SetNdivisions(905)
    #h.GetYaxis().CenterTitle(True)
    #h.GetYaxis().SetMaxDigits(3)
    # h.SetStats(False)
    ROOT.TGaxis.SetMaxDigits(3)

def HistSetting_GeneralStyling_( hist_, xlabel_='', ylabel_=''):
    hist_.GetYaxis().SetRangeUser( 1e-1, hist_.GetMaximum()*1.5 )
    hist_.GetXaxis().SetTitle(xlabel_)
    hist_.GetXaxis().SetTitleSize(0.05)
    hist_.GetXaxis().SetLabelSize(0.03)

    hist_.GetYaxis().SetTitle(ylabel_)
    hist_.GetYaxis().SetTitleSize(0.11)
    hist_.GetYaxis().SetTitleOffset(0.4)
    hist_.GetYaxis().SetLabelSize(0.03)
    hist_.GetYaxis().SetNdivisions(905)
    #hist_.GetYaxis().CenterTitle(True)
    #hist_.GetYaxis().SetMaxDigits(3)
    ROOT.TGaxis.SetMaxDigits(3)

    hist_.SetStats(False)
def HistSetting_GeneralStyling( hist_, xlabel_='', ylabel_=''):
    HistSetting_UpperStyling(hist_,xlabel_,ylabel_)
def HistSetting_UpperStyling( hist_, xlabel_='', ylabel_=''):
    hist_.GetYaxis().SetRangeUser( 1e-1, hist_.GetMaximum()*1.5 )
    hist_.GetXaxis().SetTitle(xlabel_)
    hist_.GetXaxis().SetTitleSize(0.05)
    hist_.GetXaxis().SetLabelSize(0.03)

    hist_.GetYaxis().SetTitle(ylabel_)
    hist_.GetYaxis().SetTitleSize(0.06)
    hist_.GetYaxis().SetTitleOffset(0.6)
    hist_.GetYaxis().SetLabelSize(0.03)
    hist_.GetYaxis().SetNdivisions(905)
    #hist_.GetYaxis().CenterTitle(True)
    #hist_.GetYaxis().SetMaxDigits(3)
    ROOT.TGaxis.SetMaxDigits(3)

    hist_.SetStats(False)

def HistSetting_Visualization_MC( hist, LineColor_=3, LineWidth_=4, FillColor_=1, FillStyle_=0 ):
    hist.SetLineColor(LineColor_)
    hist.SetLineWidth(LineWidth_)
    hist.SetFillColor(FillColor_)
    hist.SetFillStyle(FillStyle_)
def HistSetting_Visualization_data( hist, LineWidth_=1, LineColor_=1,  MarkerSize_=2, MarkerColor_=1):
    print('hist name : ' + hist.GetName() )
    hist.SetLineColor(LineColor_)
    hist.SetLineWidth(LineWidth_)
    hist.SetMarkerSize(MarkerSize_)
    hist.SetMarkerColor(MarkerColor_)
    hist.SetMarkerStyle(20)
def HistSetting_Visualization( hist, LineColor_=3, LineWidth_=4, FillColor_=1, FillStyle_=0 ):
    HistSetting_Visualization_MC(hist,LineColor_,LineWidth_,FillColor_,FillStyle_)
def HistSetting_YRangeExtendforLegend( hist, logscale=False ):
    multiplier= 1000. if logscale else 1.5
    hist.SetMaximum( hist.GetMaximum()*multiplier )
    hist.SetMinimum( 0.)

def HistSetting_Clone( hist, histsource ):
    hist.SetLineColor( histsource.GetLineColor() )
    hist.SetLineWidth( histsource.GetLineWidth() )
    hist.SetFillColor( histsource.GetFillColor() )
    hist.SetFillStyle( histsource.GetFillStyle() )
    hist.SetMarkerStyle( histsource.GetMarkerStyle() )
    hist.SetMarkerColor( histsource.GetMarkerColor() )
    hist.SetMarkerSize ( histsource.GetMarkerSize()  )


def VarOptimizedRange(var, tree, threshold_=0.95, maxMultiplier_=1.5):
    maxval=tree.GetMaximum(var)
    minval=tree.GetMinimum(var)
    nbin=100
    canv=ROOT.TCanvas('ctemp','',10,10)
    canv.cd()
    htemp=ROOT.TH1F('htemp', 'hi',nbin, minval, maxval)

    tree.Draw('%s >> htemp' % var)

    for ibin in range(nbin):
        if htemp.Integral(1,ibin+1) > threshold_ * float(htemp.GetEntries()):
            return (minval, htemp.GetBinLowEdge(ibin+1)*maxMultiplier_)
    return (minval, maxval)

def RatioPlot( hNumerator, hDenominator):
    th1_rp=hNumerator.Clone()
    th1_rp.SetName('ratio_'+hDenominator.GetName())
    #th1_rp.Sumw2()
    th1_rp.GetXaxis().SetTitleSize(0.11)
    th1_rp.GetXaxis().SetLabelSize(0.11)
    th1_rp.GetYaxis().SetTitleSize(0.11)
    th1_rp.GetYaxis().SetLabelSize(0.11)
    th1_rp.GetYaxis().SetTitleOffset(0.4)
    th1_rp.GetYaxis().SetNdivisions(905)
    th1_rp.GetYaxis().CenterTitle(True)
    th1_rp.SetLineColor(1)
    th1_rp.SetXTitle( hNumerator.GetXaxis().GetTitle() )
    th1_rp.SetYTitle('Data/MC')
    th1_rp.Divide(hNumerator,hDenominator,1.,1.)
    th1_rp.SetMinimum(0.7)
    th1_rp.SetMaximum(1.3)
    th1_rp.SetStats(False)

    th1_rp.SetMarkerSize(4)
    th1_rp.SetLineWidth(3)
    th1_rp.SetTitle('')
    th1_rp.SetMarkerStyle(34)
    th1_rp.SetLineStyle(1)

    HistSetting_Clone( th1_rp, hDenominator)
    return th1_rp
def DivPlot( hNumerator, hDenominator ):
    return RatioPlot( hNumerator, hDenominator )

class DisplayOnScreen(object):
    def __init__(self, displayed=True):
        self._waitforscreenoutput=displayed

        if not self._waitforscreenoutput:
            ROOT.gROOT.SetBatch(True)
    def __del__(self):
        if self._waitforscreenoutput:
            raw_input('code terminated for displaying, press ENTER to leave code')

def myratioplot():
    import sys

    var=sys.argv[1]
    fdata=ROOT.TFile.Open('/home/ltsai/job_DoubleEG_Run2016_Legacy.root')
    fsimu=ROOT.TFile.Open('/home/ltsai/job_summer16_DYJetsToLL_m50_aMCatNLO_ext2.root')

    tdata=fdata.Get('t')
    tsimu=fsimu.Get('t')

    minval,maxval=VarOptimizedRange( var,tdata )

    from libs.Selections import SelStr_data_PurifyZ, MassWidowStr_Z
    hists={}
    hists['data']=ROOT.TH1F('data','', 40, minval, maxval)
    hists['orig']=ROOT.TH1F('orig','', 40, minval, maxval)
    hists['calb']=ROOT.TH1F('calb','', 40, minval, maxval)
    for key,val in hists.iteritems(): val.Sumw2()

    tdata.Draw('%s      >>data'%var, '&&'.join( [MassWidowStr_Z(), SelStr_data_PurifyZ()] ))
    tsimu.Draw('%s      >>orig'%var, '&&'.join( [MassWidowStr_Z(), SelStr_data_PurifyZ()] ))
    tsimu.Draw('calib_%s>>calb'%var, '&&'.join( [MassWidowStr_Z(), SelStr_data_PurifyZ()] ))

    scaling = lambda hist : hist.Scale( float(hists['data'].GetEntries()) / float(hist.GetEntries()) )
    scaling( hists['orig'] )
    scaling( hists['calb'] )

    hists['ratio_orig']=RatioPlot( hists['data'],hists['orig'])
    hists['ratio_calb']=RatioPlot( hists['data'],hists['calb'])
    for key,val in hists.iteritems(): val.Sumw2()

    HistSetting_data( hists['data'], MarkerSize_=1.3 )
    HistSetting( hists['orig'], LineColor_=47, LineWidth_=3)
    HistSetting( hists['calb'], LineColor_=38, LineWidth_=3)
    HistSetting( hists['ratio_orig'], LineColor_=47, LineWidth_=3)
    HistSetting( hists['ratio_calb'], LineColor_=38, LineWidth_=3)

    canv=ROOT.TCanvas('c1','',1200,1000)
    canv.cd()
    upperpad=UpperPad()
    lowerpad=LowerPad()
    upperpad.Draw()
    lowerpad.Draw()

    upperpad.cd()

    hists['data'].Draw('axis')
    hists['calb'].Draw('same hist')
    hists['orig'].Draw('same hist')
    hists['data'].Draw('same e0 p0')


    lowerpad.cd()
    hists['ratio_calb'].Draw('axis')
    hists['ratio_calb'].Draw('same')
    hists['ratio_orig'].Draw('same')

    canv.Update()
    raw_input('hi')

def _quicktest():
    canv=ROOT.TCanvas('c1','',800,800)
    canv.cd()
    hdata=ROOT.TH1F('data','', 40, 0., 40.)
    HistSetting_data( hdata )
    for idx in range(1000):
        hdata.Fill(20)

    hdata.Draw()
    hdata.SetDrawOption('e0 p0')
    canv.Update()

    raw_input('hi')
if __name__ == '__main__':
    myratioplot()

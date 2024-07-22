#!/usr/bin/env python2

import ROOT
import json
import sys

def PrintHelp():
    print '##############################################'
    print '##############################################'
    print '##############################################'
    print '##############################################'
    print '##############################################'
    print '##############################################'
    print '##############################################'
    print '##############################################'
    print '##############################################'
    print '##############################################'
    raise IOError('Input arg failed')

class JsonInfo(object):
    def __init__(self, jsonname):
        infile=open(jsonname, 'r')
        data=json.load(infile)

        if not 'mcFile' in data: PrintHelp()
        if not 'dataFile' in data: PrintHelp()
        if not 'tag' in data: PrintHelp()

        self.file_data = data['dataFile']
        self.file_simu = data['mcFile']
        self.tag = data['tag']

import xPhoton.analysis.PlotObjectMgr as PlotObjectMgr

def Chi2(histname_data_, histname_simu_):
    hdata = ROOT.gROOT.FindObject( histname_data_ )
    hsimu = ROOT.gROOT.FindObject( histname_simu_ )
    return sum( [( ( hdata.GetBinContent(ibin)-hsimu.GetBinContent(ibin) )/hdata.GetBinError(ibin) )**2 for ibin in range(1,hdata.GetNbinsX()+1) if hdata.GetBinError(ibin) > 1e-2 ] )
def Ndof(histname_):
    return ROOT.gROOT.FindObject( histname_ ).GetNbinsX() - 1
class FigPartContainer(object):
    ''' To prevent objects are deleted. Use it to keep plotable '''
    def __init__(self):
        self.plotable=[]
    def KeepPlotable(self, obj):
        self.plotable.append(obj)
def HistSetting_Visualization_LowerStyling(hist):
    hist.SetTitle('')
    hist.GetYaxis().SetRangeUser(0.7,1.3)
    hist.GetXaxis().SetTitleSize(0.11)
    hist.GetXaxis().SetLabelSize(0.11)
    hist.GetYaxis().SetTitleSize(0.15)
    hist.GetYaxis().SetLabelSize(0.11)
    hist.GetYaxis().SetTitleOffset(0.25)
    hist.GetYaxis().SetNdivisions(905)
    hist.GetYaxis().CenterTitle(True)
    hist.SetYTitle('Data/MC')
    hist.SetStats(False)

def ShowRatioPlot(pad, etaregion, varname, figFrags=FigPartContainer()):
    hdata = ROOT.gROOT.FindObject( 'hdata.'+'_'.join([etaregion,varname]) )
    hsimu = ROOT.gROOT.FindObject( 'hsimu.'+'_'.join([etaregion,varname]) )
    hcalb = ROOT.gROOT.FindObject( 'hcalb.'+'_'.join([etaregion,varname]) )

    ratio_simu = hdata.Clone()
    ratio_simu.Divide(hsimu)
    ratio_simu.SetName( 'ratio.%s'%hsimu.GetName() )
    PlotObjectMgr.HistSetting_Clone(ratio_simu, hsimu)
    #ratio_simu.SetMarkerStyle(32)
    ratio_simu.SetMarkerStyle(0)
    ratio_simu.SetMarkerColor( ratio_simu.GetLineColor() )
    ratio_simu.SetMarkerSize(4)
    ratio_simu.SetFillStyle(0)
    HistSetting_Visualization_LowerStyling(ratio_simu)



    ratio_calb = hdata.Clone()
    ratio_calb.Divide(hcalb)
    ratio_calb.SetName( 'ratio.%s'%hcalb.GetName() )
    PlotObjectMgr.HistSetting_Clone(ratio_calb, hcalb)
    #ratio_calb.SetMarkerStyle(24)
    ratio_calb.SetMarkerStyle(0)
    ratio_calb.SetMarkerColor( ratio_calb.GetLineColor() )
    ratio_calb.SetMarkerSize(4)
    ratio_calb.SetFillStyle(0)

    # put 100x error to check error bar is printed or not.
    #[ ratio_calb.SetBinError( ibin, ratio_calb.GetBinError(ibin) * 100.) for ibin in range(1, ratio_calb.GetNbinsX()+1) ]

    pad.cd()
    ratio_simu.Draw('e0 p')
    ratio_calb.Draw('ep 0 same')

    figFrags.KeepPlotable(ratio_simu)
    figFrags.KeepPlotable(ratio_calb)
    return figFrags

def ShowOriginalDist(pad, etaregion, varname, figFrags=FigPartContainer()):
    hdata = ROOT.gROOT.FindObject( 'hdata.'+'_'.join([etaregion,varname]) )
    hsimu = ROOT.gROOT.FindObject( 'hsimu.'+'_'.join([etaregion,varname]) )
    hcalb = ROOT.gROOT.FindObject( 'hcalb.'+'_'.join([etaregion,varname]) )

    PlotObjectMgr.HistSetting_Visualization_data( hdata, LineWidth_ =2 )
    PlotObjectMgr.HistSetting_GeneralStyling    ( hdata, xlabel_=varname, ylabel_='Entries / %.1e' % hdata.GetBinWidth(1) )

    PlotObjectMgr.HistSetting_Visualization_MC  ( hsimu, LineColor_ = 38 )
    PlotObjectMgr.HistSetting_GeneralStyling    ( hsimu, xlabel_=varname, ylabel_='Entries / %.1e' % hsimu.GetBinWidth(1) )
    hsimu.Scale( hdata.Integral() / hsimu.Integral() )

    PlotObjectMgr.HistSetting_Visualization_MC  ( hcalb, LineColor_ = 30 )
    PlotObjectMgr.HistSetting_GeneralStyling    ( hcalb, xlabel_=varname, ylabel_='Entries / %.1e' % hcalb.GetBinWidth(1) )
    hcalb.Scale( hdata.Integral() / hcalb.Integral() )

    leg=ROOT.TLegend( 0.2, 0.67, 0.8, 0.85 )
    leg.SetTextAlign(32)
    leg.AddEntry( hdata, 'UL2018 data sample', 'lp' )
    leg.AddEntry( hsimu, 'original MC. #chi^{2} = %.2e / %.0f = %.2e' % (
        Chi2(hdata.GetName(),hsimu.GetName()), Ndof(hdata.GetName()), Chi2(hdata.GetName(),hsimu.GetName()) / Ndof(hdata.GetName())
        ), 'l')
    leg.AddEntry( hcalb, 'calibrated MC. #chi^{2} = %.2e / %.0f = %.2e' % (
        Chi2(hdata.GetName(),hcalb.GetName()), Ndof(hdata.GetName()), Chi2(hdata.GetName(),hcalb.GetName()) / Ndof(hdata.GetName())
        ), 'l')

    leg.SetBorderSize(0)
    leg.SetFillColor(4000)
    leg.SetFillStyle(4000)

    pad.cd()
    hdata.GetXaxis().SetLabelSize(0)
    hdata.Draw('axis')
    hsimu.Draw('hist same')
    hcalb.Draw('hist same')
    hdata.Draw('e0 p same')
    leg.Draw()

    figFrags.KeepPlotable(hdata)
    figFrags.KeepPlotable(hsimu)
    figFrags.KeepPlotable(hcalb)
    figFrags.KeepPlotable( leg )
    return figFrags


if __name__ == "__main__":
    args = JsonInfo(sys.argv[1])
    fdata = ROOT.TFile.Open( args.file_data )
    tdata = fdata.Get('t')

    fsimu = ROOT.TFile.Open( args.file_simu )
    tsimu = fsimu.Get('t')

    from xPhoton.analysis.MyCanvas import MyCanvas
    canv=MyCanvas('canv',1600,1200)

    import xPhoton.analysis.SelectionsMgr as Selections
    pre_selections=(
        Selections.DrawCutStr_ZmassWindow(),
        Selections.DrawCutStr_data_PurifyZ(),
        )
    listofvars=[]

    for eta in ('barrel','endcap'):
        varname='mva'
        selections=[ Selections.DrawCutStr_EtaRegion(eta) ]
        selections.extend(pre_selections)
        cut='&&'.join( selections )

    canv.Clear()
    upperpad=PlotObjectMgr.UpperPad()
    lowerpad=PlotObjectMgr.LowerPad()
    canv.cd()
    upperpad.Draw()
    lowerpad.Draw()

    for vname, etaregion in listofvars:
        canv.cd()
        #figFrag=FigPartContainer()
        #ShowOriginalDist(upperpad, etaregion, vname, figFrag)
        #ShowRatioPlot(lowerpad, etaregion, vname, figFrag)

        canv.SaveAs('ratioplot.%s_%s.pdf' % (etaregion,vname) )

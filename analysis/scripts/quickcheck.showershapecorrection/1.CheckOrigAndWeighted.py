#!/usr/bin/env python2

import ROOT
import json
import sys

def PrintHelp():
    print '##############################################'
    print '## Use TTree::Draw() feature to plot the    ##'
    print '## compairson of data / MC plot. The canvas ##'
    print '## is separated in upper and lower pads for ##'
    print '## comparison. Comparison between original  ##'
    print '## MC and re-weighted MC will be shown in   ##'
    print '## one plot.                                ##'
    print '## Usage :                                  ##'
    print '##   ./this.py input.json                   ##'
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
    def Write(self, odir=None):
        if odir:odir.cd()
        for obj in self.plotable:
            obj.Write()
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
    HistSetting_Visualization_LowerStyling(ratio_calb)
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
    leg.AddEntry( hcalb, 'weighted MC. #chi^{2} = %.2e / %.0f = %.2e' % (
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


def ShowRatioPlot_1(pad, etaregion, varname, figFrags=FigPartContainer()):
    hdata = ROOT.gROOT.FindObject( 'hdata.'+'_'.join([etaregion,varname]) )
    hcalb = ROOT.gROOT.FindObject( 'hcalb.'+'_'.join([etaregion,varname]) )

    ratio_calb = hdata.Clone()
    ratio_calb.Divide(hcalb)
    ratio_calb.SetName( 'ratio.%s'%hcalb.GetName() )
    PlotObjectMgr.HistSetting_Clone(ratio_calb, hcalb)
    #ratio_calb.SetMarkerStyle(24)
    ratio_calb.SetMarkerColor( 1 )
    ratio_calb.SetMarkerSize(4)
    #ratio_calb.SetFillStyle(0)
    ratio_calb.SetTitle('')
    ratio_calb.GetYaxis().SetRangeUser(0.7,1.3)
    HistSetting_Visualization_LowerStyling(ratio_calb)

    # put 100x error to check error bar is printed or not.
    #[ ratio_calb.SetBinError( ibin, ratio_calb.GetBinError(ibin) * 100.) for ibin in range(1, ratio_calb.GetNbinsX()+1) ]

    pad.cd()
    ratio_calb.Draw('e0 p')

    figFrags.KeepPlotable(ratio_calb)
    return figFrags

def ShowOriginalDist_1(pad, etaregion, varname, figFrags=FigPartContainer()):
    hdata = ROOT.gROOT.FindObject( 'hdata.'+'_'.join([etaregion,varname]) )
    hcalb = ROOT.gROOT.FindObject( 'hcalb.'+'_'.join([etaregion,varname]) )

    PlotObjectMgr.HistSetting_Visualization_data( hdata, LineWidth_ =2, MarkerSize_=4 )
    PlotObjectMgr.HistSetting_GeneralStyling    ( hdata, xlabel_=varname, ylabel_='Entries / %.1e' % hdata.GetBinWidth(1) )

    PlotObjectMgr.HistSetting_Visualization_MC  ( hcalb, LineColor_ = 30, FillColor_=30, FillStyle_=1 )
    PlotObjectMgr.HistSetting_GeneralStyling    ( hcalb, xlabel_=varname, ylabel_='Entries / %.1e' % hcalb.GetBinWidth(1) )
    hcalb.Scale( hdata.Integral() / hcalb.Integral() )
    hcalb.SetFillColor(hcalb.GetLineColor())
    hcalb.SetFillStyle(1001)

    leg=ROOT.TLegend( 0.2, 0.67, 0.8, 0.85 )
    leg.SetTextAlign(32)
    leg.AddEntry( hdata, 'UL2018 data sample', 'lp' )
    leg.AddEntry( hcalb, 'MC. #chi^{2} = %.2e / %.0f = %.2e' % (
        Chi2(hdata.GetName(),hcalb.GetName()), Ndof(hdata.GetName()), Chi2(hdata.GetName(),hcalb.GetName()) / Ndof(hdata.GetName())
        ), 'l')

    leg.SetBorderSize(0)
    leg.SetFillColor(4000)
    leg.SetFillStyle(4000)

    pad.cd()
    hdata.GetXaxis().SetLabelSize(0)
    hdata.Draw('axis')
    hcalb.Draw('hist same')
    hdata.Draw('e0 p same')
    leg.Draw()

    figFrags.KeepPlotable(hdata)
    figFrags.KeepPlotable(hcalb)
    figFrags.KeepPlotable( leg )
    return figFrags

class Mgr_1RatioPlot(object):
    def __init__(self, upperpad, lowerpad):
        self._upperpad = upperpad
        self._lowerpad = lowerpad
        self._frag = FigPartContainer()
    def DrawToCanvas(self, canv, etaregion, varname):
        canv.cd()
        ShowOriginalDist_1(self._upperpad, etaregion, vname, self._frag)
        ShowRatioPlot_1   (self._lowerpad, etaregion, vname, self._frag)
class Mgr_2RatioPlot(object):
    def __init__(self, upperpad, lowerpad):
        self._upperpad = upperpad
        self._lowerpad = lowerpad
        self._frag = FigPartContainer()
    def DrawToCanvas(self, canv, etaregion, varname):
        canv.cd()
        ShowOriginalDist(self._upperpad, etaregion, vname, self._frag)
        ShowRatioPlot   (self._lowerpad, etaregion, vname, self._frag)

if __name__ == "__main__":
    args = JsonInfo(sys.argv[1])
    fdata = ROOT.TFile.Open( args.file_data )
    tdata = fdata.Get('t')

    fsimu = ROOT.TFile.Open( args.file_simu )
    tsimu = fsimu.Get('t')

    from xPhoton.analysis.MyCanvas import MyCanvas
    canv=MyCanvas('canv',1600,1200)

    import xPhoton.analysis.SelectionsMgr as Selections
    pre_selections=[
        Selections.DrawCutStr_ZmassWindow(),
        Selections.DrawCutStr_data_PurifyZ(),
        ]
    listofvars=[]
    for eta in ('barrel','endcap'):
        selections=[ Selections.DrawCutStr_EtaRegion(eta) ]
        selections.extend(pre_selections)
        cut='&&'.join( selections )

        hsetting='(10,-1.,1.)'
        varname='mva'
        listofvars.append( (varname, eta) )
        print 'hdata.%s_%s'%(eta,varname)
        tdata.Draw('mva                           >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('mva_nocorr                    >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('mva                           >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.,0.05)'
        varname='scEtaWidth'
        listofvars.append( (varname, eta) )
        tdata.Draw('scEtaWidth                    >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('scEtaWidth                    >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_scEtaWidth              >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.,0.2)'
        varname='scPhiWidth'
        listofvars.append( (varname, eta) )
        tdata.Draw('scPhiWidth                    >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('scPhiWidth                    >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_scPhiWidth              >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.,1.2)'
        varname='r9Full5x5'
        listofvars.append( (varname, eta) )
        tdata.Draw('r9Full5x5                     >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('r9Full5x5                     >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_r9Full5x5               >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.2,1.)'
        varname='s4Full5x5'
        listofvars.append( (varname, eta) )
        tdata.Draw('s4Full5x5                     >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('s4Full5x5                     >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_s4Full5x5               >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.002,0.045)'
        varname='sieieFull5x5'
        listofvars.append( (varname, eta) )
        tdata.Draw('sieieFull5x5                  >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('sieieFull5x5                  >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_sieieFull5x5            >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,-0.0015,0.0015)' if eta == 'endcap' else '(40,-0.0002,0.0002)'
        varname='sieipFull5x5'
        listofvars.append( (varname, eta) )
        tdata.Draw('sieipFull5x5                  >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('sieipFull5x5                  >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_sieipFull5x5            >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

        hsetting='(40,0.,1.)'
        varname='esEnergyOverSCRawEnergy'
        listofvars.append( (varname, eta) )
        tdata.Draw('esEnergyOverSCRawEnergy       >> hdata.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('esEnergyOverSCRawEnergy       >> hsimu.%s_%s%s'%(eta,varname, hsetting), cut)
        tsimu.Draw('calib_esEnergyOverSCRawEnergy >> hcalb.%s_%s%s'%(eta,varname, hsetting), cut)

    print("figure saving...");
    canv.Clear()
    upperpad=PlotObjectMgr.UpperPad()
    lowerpad=PlotObjectMgr.LowerPad()
    canv.cd()
    upperpad.Draw()
    lowerpad.Draw()

    plots=Mgr_2RatioPlot(upperpad,lowerpad)
    #plots=Mgr_1RatioPlot(upperpad,lowerpad)
    for vname, etaregion in listofvars:
        plots.DrawToCanvas(canv, etaregion, vname)

        canv.SaveAs('ratioplot.%s.%s_%s.pdf' % (args.tag,etaregion,vname) )

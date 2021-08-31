#!/usr/bin/env python2
import ROOT
import xPhoton.analysis.PlotObjectMgr as PlotObject
import xPhoton.analysis.SelectionsMgr as Selections
from   xPhoton.analysis.histMgr       import histMgr
from   xPhoton.xPhoton.Managers.HistMgr import HistMgr1D
#def chi2perDoF(h_data_, h_simu_,frombin=1):
def chi2perDoF(h_data_, h_simu_,frombin=40/4):
    sum_chi2=0.
    for binidx in range(frombin,h_data_.GetNbinsX()+1):
        ibin=binidx # ignore overflow and underflow bin
        binval0=h_simu_.GetBinContent(ibin)
        binval1=h_data_.GetBinContent(ibin)
        err=h_data_.GetBinError(ibin) if h_data_.GetBinError(ibin) > 1e-3 else 1
        sum_chi2+=( (binval0-binval1)/err )**2
    return sum_chi2 / h_data_.GetNbinsX()


def myratioplot(ndata,nsimu, display):
    import sys
    hi=PlotObject.DisplayOnScreen(display)

    var=sys.argv[1]
    fdata=ROOT.TFile.Open(ndata)
    fsimu=ROOT.TFile.Open(nsimu)

    tdata=fdata.Get('t')
    tsimu=fsimu.Get('t')

    minval,maxval=PlotObject.VarOptimizedRange( var,tdata )


    canv=ROOT.TCanvas('c1','',1200,1000)
    canv.cd()
    PlotObject.Transparent(canv)
    '''
    upperpad=PlotObject.UpperPad()
    lowerpad=PlotObject.LowerPad()
    '''

    for region in ['barrel','endcap']:
        hists=histMgr(region+'_')
        binning=40
        hists.Create1D('data', binning, minval, maxval)
        hists.Create1D('orig', binning, minval, maxval)
        hists.Create1D('calb', binning, minval, maxval)

        tdata.Draw('%s      >> %s'%(var,hists.FullName('data')), '&&'.join( [Selections.DrawCutStr_ZmassWindow(), Selections.DrawCutStr_data_PurifyZ(), Selections.DrawCutStr_EtaRegion(region)] ))
        tsimu.Draw('%s      >> %s'%(var,hists.FullName('orig')), '&&'.join( [Selections.DrawCutStr_ZmassWindow(), Selections.DrawCutStr_data_PurifyZ(), Selections.DrawCutStr_EtaRegion(region)] ))
        tsimu.Draw('calib_%s>> %s'%(var,hists.FullName('calb')), '&&'.join( [Selections.DrawCutStr_ZmassWindow(), Selections.DrawCutStr_data_PurifyZ(), Selections.DrawCutStr_EtaRegion(region)] ))

        scaling = lambda hist : hist.Scale( float(hists['data'].GetEntries()) / float(hist.GetEntries()) )
        scaling( hists['orig'] )
        scaling( hists['calb'] )

        hists['ratio_orig']=PlotObject.RatioPlot( hists['data'],hists['orig'])
        hists['ratio_calb']=PlotObject.RatioPlot( hists['data'],hists['calb'])

        PlotObject.HistSetting_Visualization_data( hists['data'], MarkerSize_=1.3 )
        PlotObject.HistSetting_Visualization( hists['orig'], LineColor_=44, LineWidth_=3)
        PlotObject.HistSetting_Visualization( hists['calb'], LineColor_=38, LineWidth_=3)
        PlotObject.HistSetting_Visualization( hists['ratio_orig'], LineColor_=44, LineWidth_=3)
        PlotObject.HistSetting_Visualization( hists['ratio_calb'], LineColor_=38, LineWidth_=3)

        canv.Clear()
        upperpad=PlotObject.UpperPad()
        lowerpad=PlotObject.LowerPad()
        upperpad.Draw()
        lowerpad.Draw()

        upperpad.cd()

        fy_max=hists['data'].GetMaximum()
        fx_min=hists['data'].GetBinLowEdge(1)
        fx_max=hists['data'].GetBinLowEdge( hists['data'].GetNbinsX()+1 )
        fx_range=fx_max-fx_min

        hists['data'].SetMaximum( fy_max*1.5 )
        hists['data'].SetMinimum( 0.)


        hists['data'].Draw('axis')
        hists['calb'].Draw('same hist')
        hists['orig'].Draw('same hist')
        hists['data'].Draw('same e0 p0')

        leg=PlotObject.Legend( (fx_min+fx_range*0.05,fy_max*1.1), (fx_max-fx_range*0.3, fy_max*1.48), title='', useNDC=False )
        leg.SetTextAlign(32)
        leg.AddEntry( hists['ratio_orig'], 'origin val, chi2 / nDoF={:6.2f}'.format( chi2perDoF(hists['data'],hists['orig']) ), 'l')
        leg.AddEntry( hists['ratio_calb'], 'calibrated, chi2 / nDoF={:6.2f}'.format( chi2perDoF(hists['data'],hists['calb']) ), 'l')
        leg.Draw()


        lowerpad.cd()
        hists['ratio_calb'].Draw('axis')
        hists['ratio_calb'].Draw('same')
        hists['ratio_orig'].Draw('same')

        canv.Update()
        canv.SaveAs('ratioplot_%s_%s.pdf' % (region,var))
def mva_ratioplot(ndata,nsimu, display):
    import sys
    hi=PlotObject.DisplayOnScreen(display)

    var='mva'
    fdata=ROOT.TFile.Open(ndata)
    fsimu=ROOT.TFile.Open(nsimu)
    print ndata

    tdata=fdata.Get('t')
    tsimu=fsimu.Get('t')

    minval,maxval=PlotObject.VarOptimizedRange( var,tdata )


    canv=ROOT.TCanvas('c1','',1200,1000)
    canv.cd()
    PlotObject.Transparent(canv)
    '''
    upperpad=PlotObject.UpperPad()
    lowerpad=PlotObject.LowerPad()
    '''

    for region in ['barrel','endcap']:
        canv.Clear()
        hists=histMgr(region)
        binning=40
        hists.Create1D('data', binning, minval, maxval)
        hists.Create1D('orig', binning, minval, maxval)
        hists.Create1D('calb', binning, minval, maxval)

        tdata.Draw('mva       >> %s'%(hists.FullName('data')), '&&'.join( [Selections.DrawCutStr_ZmassWindow(), Selections.DrawCutStr_data_PurifyZ(), Selections.DrawCutStr_EtaRegion(region)] ))
        tsimu.Draw('mva_nocorr>> %s'%(hists.FullName('orig')), '&&'.join( [Selections.DrawCutStr_ZmassWindow(), Selections.DrawCutStr_data_PurifyZ(), Selections.DrawCutStr_EtaRegion(region)] ))
        tsimu.Draw('mva       >> %s'%(hists.FullName('calb')), '&&'.join( [Selections.DrawCutStr_ZmassWindow(), Selections.DrawCutStr_data_PurifyZ(), Selections.DrawCutStr_EtaRegion(region)] ))
        canv.Clear()

        scaling = lambda hist : hist.Scale( float(hists['data'].GetEntries()) / float(hist.GetEntries()) )
        #scaling = lambda hist : hist.Scale( float(hists['data'].Integral(binning/10,binning+1)) / float(hist.Integral(binning/10, binning+1)) )
        scaling( hists['orig'] )
        scaling( hists['calb'] )

        PlotObject.HistSetting_Visualization_data( hists['data'], MarkerSize_=1.3 )
        PlotObject.HistSetting_Visualization( hists['orig'], LineColor_=44, LineWidth_=3)
        PlotObject.HistSetting_Visualization( hists['calb'], LineColor_=38, LineWidth_=3)

        ratiohists=histMgr('ratio', region)
        ratiohists['orig']=PlotObject.RatioPlot( hists['data'],hists['orig'] )
        ratiohists['calb']=PlotObject.RatioPlot( hists['data'],hists['calb'] )

        leg=_updownplots(hists,ratiohists)

        canv.Update()
        canv.SaveAs('ratioplot_%s_%s.pdf' % (region,var))


def _updownplots(upperhists,lowerhists):
    #_drawratio( upperhists, lowerhists)
    #return

    return _drawratio_2( upperhists['data'],
            upperhists={ 'orig': upperhists['orig'], 'calb': upperhists['calb'] },
            lowerhists={ 'orig': lowerhists['orig'], 'calb': lowerhists['calb'] }
            )

def _drawratio_2(hdata, upperhists={}, lowerhists={}):
        upperpad=PlotObject.UpperPad()
        lowerpad=PlotObject.LowerPad()
        upperpad.Draw()
        lowerpad.Draw()

        upperpad.cd()

        fy_max=hdata.GetMaximum()
        fx_min=hdata.GetBinLowEdge(1)
        fx_max=hdata.GetBinLowEdge( hdata.GetNbinsX()+1 )
        fx_range=fx_max-fx_min

        PlotObject.HistSetting_YRangeExtendforLegend(hdata)
        #hdata.SetMaximum( fy_max*1.5 )
        #hdata.SetMinimum( 0.)


        hdata.Draw('axis')
        for name,hist in upperhists.iteritems():
            hist.Draw('same hist')
        hdata.Draw('same e0 p0')

        leg=PlotObject.Legend( (fx_min+fx_range*0.05,fy_max*1.1), (fx_max-fx_range*0.3, fy_max*1.48), title='', useNDC=False )
        leg.SetTextAlign(32)
        leg.AddEntry( lowerhists['orig'], 'origin val, chi2 / nDoF={:6.2f}'.format( chi2perDoF(hdata,upperhists['orig']) ), 'l')
        leg.AddEntry( lowerhists['calb'], 'calibrated, chi2 / nDoF={:6.2f}'.format( chi2perDoF(hdata,upperhists['calb']) ), 'l')
        leg.Draw()


        lowerpad.cd()
        lowerhists.values()[0].Draw('axis')
        for name,h in lowerhists.iteritems():
            h.Draw('same')
        return leg

def _histscaling(hdata, hsimu):
    hsimu.Scale( float(hdata.GetEntries()) / float(hsimu.GetEntries()) )
def _histscaling_ignorefirstbins(hdata, hsimu):
    hist.Scale( float(hdata.GetEntries()) / float(hsimu.GetEntries()) )


if __name__ == '__main__':
    datafile='/home/ltsai/ReceivedFile/job_DoubleEG_Run2016_Legacy.root'
    mcfile='/home/ltsai/ReceivedFile/job_summer16_DYJetsToLL_m50_aMCatNLO_ext2.root'
    #myratioplot(datafile,mcfile, False)
    mva_ratioplot(datafile,mcfile,False)

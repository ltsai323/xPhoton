#!/usr/bin/env python2
import ROOT

class treeloader(object):
    def __init__(self, ifilename):
        self._file=ROOT.TFile.Open(ifilename)
        self._tree=self._file.Get('t')
        return
    def __del__(self):
        self._file.Close()
        return

def chi2Calc(hdata, hsimu):
    sumchi2=0.
    for ibin in range(hdata.GetNbinsX()):
        valdata=hdata.GetBinContent(ibin+1)
        errdata=hdata.GetBinError(ibin+1)
        valsimu=hsimu.GetBinContent(ibin+1)
        if valdata < 1e-8 and errdata < 1e-8: continue
        print 'valdata = %.6f and errdata = %.6f' % (valdata,errdata)
        sumchi2+=(valdata-valsimu)**2 / errdata
    return sumchi2
def chi2CalcNormalize(hdata, hsimu):
    sumchi2=0.
    idata=float(hdata.Integral())
    isimu=float(hsimu.Integral())

    for ibin in range(hdata.GetNbinsX()):
        valdata=float(hdata.GetBinContent(ibin+1))
        errdata=float(hdata.GetBinError(ibin+1))
        valsimu=float(hsimu.GetBinContent(ibin+1))
        val=(valdata/idata-valsimu/isimu)
        err=(errdata/idata)
        sumchi2+=(val**2) / (err**2)
    return sumchi2

class Configs(object):
    def __init__(self):
        self.kwargs={}
        self.kwargs['logscale'] = False
        return
    def Get(self, name):
        if not name in self.kwargs: raise KeyError('input key "%s" not found in Configs. Please check input' % name)
        return self.kwargs[name]
    def XTitle(self, val): # val = string
        self.kwargs['xtitle'] = val
    def Title(self, val): # val = string
        self.kwargs['title'] = val
        return
    def Canvas(self, val): # val = TCanvas
        self.kwargs['canv'] = val
        return
    def LogScale(self, val): # val = bool
        self.kwargs['logscale'] = val
        return
    def OutputName(self, val): # val = string
        self.kwargs['outname'] = val
        return

def TreeComparison(nameTrg, nameFit,confs):

    hTrg=ROOT.gROOT.FindObject(nameTrg)
    hCmp=ROOT.gROOT.FindObject(nameFit)
    hTrg.Sumw2()
    hTrg.Scale( 1./hTrg.Integral() )
    #hTrg.SetMarkerSize(8)
    hTrg.SetMarkerColor(9)
    hTrg.SetLineColor(9)
    hTrg.SetLineWidth(4)
    hTrg.SetFillColor(0)
    hTrg.SetStats(False)
    hTrg.GetXaxis().SetTitle( confs.Get('xtitle') )
    hTrg.SetTitle( confs.Get('title') )

    hCmp.Sumw2()
    hCmp.Scale( 1./hCmp.Integral() )
    hCmp.SetMarkerSize(0)
    #hCmp.SetLineColor(0)
    hCmp.SetLineWidth(0)
    hCmp.SetFillColor(7)
    hCmp.SetStats(False)
    hCmp.GetXaxis().SetTitle( confs.Get('xtitle') )
    hCmp.SetTitle( confs.Get('title') )

    chi2val=chi2Calc(hTrg, hCmp)

    from xPhoton.analysis.PlotObjectMgr import UpperPad, LowerPad, DivPlot
    divplot=DivPlot(hTrg,hCmp)

    text=ROOT.TText()
    canv=confs.Get('canv')
    #canv.Clear()
    canv.cd()
    upperpad=UpperPad()
    lowerpad=LowerPad()
    upperpad.Draw()
    lowerpad.Draw()
    upperpad.cd()
    upperpad.SetLogy(confs.Get('logscale'))
    hCmp.Draw('hist')
    hTrg.Draw('ep same')
    text.SetText( 0.2,0.8, '#splitline{chi2 value / nDoF = }{%.1f / %d = %.2f}'%(chi2val,hTrg.GetNbinsX(), chi2val/hTrg.GetNbinsX()) )
    text.Draw()


    lowerpad.cd()
    divplot.Draw('e0p')

    canv.SaveAs( confs.Get('outname') )








if __name__ == "__main__":
    tdata=treeloader("/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/Run2016_94XReReco.root")
    tsimu=treeloader("/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/testing_2016Madgraph.root")

    from xPhoton.xPhoton.Managers.HistMgr import HistMgr1D
    datahists=HistMgr1D('data')
    datahists.CreateHist('bScore', '', 20, 0., 1.)

    simuhists=HistMgr1D('simu')
    simuhists.CreateHist('bScore', '', 20, 0., 1.)


    selection='(jetDeepCSVTags_b+jetDeepCSVTags_bb != -2 && recoPt > 175.)'
    jetSFweight='* jetSF.DeepFlavour_JESReduced.central'
    tdata._tree.Draw('jetDeepCSVTags_b+jetDeepCSVTags_bb >> %s'%datahists.FullName('bScore'), selection)
    tsimu._tree.Draw('jetDeepCSVTags_b+jetDeepCSVTags_bb >> %s'%simuhists.FullName('bScore'), selection)
    #tsimu._tree.Draw('jetDeepCSVTags_b+jetDeepCSVTags_bb >> hsimW', selection + jetSFweight)

    '''
    from xPhoton.xPhoton.Managers.PlotMgr import MyCanvas
    canv=MyCanvas('canv','',1200,1000)
    config_lackjetSF=Configs()
    config_lackjetSF.XTitle('bScore #equiv jetDeepCSVTags_b+jetDeepCSVTags_bb')
    config_lackjetSF.Title('Lack of jet scale factor')
    config_lackjetSF.Canvas(canv)
    config_lackjetSF.LogScale(False)
    config_lackjetSF.OutputName( 'hi.pdf' )
    #TreeComparison(datahists.FullName('bScore'),simuhists.FullName('bScore'), config_lackjetSF)
    '''

    ofile=ROOT.TFile('output.root', 'recreate')
    datahists.WriteTo(ofile)
    simuhists.WriteTo(ofile)
    ofile.Close()

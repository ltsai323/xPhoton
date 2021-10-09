#!/usr/bin/env python2

import ROOT

mydir='plots/'
def figsetting( ratioplot, refhist ):
    ratioplot.GetLowYaxis().SetNdivisions(501)
    ratioplot.GetLowerRefYaxis().SetTitle('FakeSample/Truth')
    ratioplot.GetUpperRefYaxis().SetTitle('Entries per GeV')
def legendsetting( refhist, cmphistdict ):
    leg=ROOT.TLegend( 0.2, 0.7, 0.75, 0.85, 'Components', 'NDC' )
    leg.AddEntry( refhist, 'signal + background','l')
    return leg
def ignore0(hist):
    for ibin in range(hist.GetNbinsX()):
        binIdx=ibin+1
        if hist.GetBinContent(binIdx) < 1e-3: hist.SetBinContent(binIdx,1e-3)
def DrawComp(outputfigname, h_sig,h_bkg,h_tot):
    sighist=h_sig.Clone()
    bkghist=h_bkg.Clone()
    tothist=h_tot.Clone()

    ignore0(sighist)
    ignore0(bkghist)
    ignore0(tothist)

    sighist.SetFillColor(43)
    bkghist.SetFillColor(38)
    cmphist=ROOT.THStack('integral','')
    cmphist.Add(sighist)
    cmphist.Add(bkghist)

    canv=ROOT.TCanvas('c1','',600,500)

    import xPhoton.xPhoton.PlotLib.Ratioplot as RatioPlotMgr

    RatioPlotMgr.ExportRatioPlot(
            datahist=cmphist,
            cmphists={'data':tothist},
            output=mydir+outputfigname+'.png',
            canv=canv,
            ratioframe=(0.95,1.05),
            frameplotfunc=figsetting,
            legsetupfunc=legendsetting
            )
    del canv



if __name__ == '__main__':
    import os
    os.system( 'touch {d} ; /bin/rm -r {d}; mkdir {d}'.format(d=mydir) )

    sigfile=ROOT.TFile.Open('../step7.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_sig.root')
    bkgfile=ROOT.TFile.Open('../step7.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_bkg.root')
    totfile=ROOT.TFile.Open('../step7.ClosureTest_SampleCreation/storeroot/iso_fakesample0.root')
    canv=ROOT.TCanvas('c','',600,500)
    for etabin in range(2):
        for jetbin in range(3):
            for ptbin in range(20):
                histname='data_%d_%d_%d_px1_chIso' % (etabin,jetbin,ptbin)
                figname='cmp_%d_%d_%d' % (etabin,jetbin,ptbin)

                '''
                DrawComp(
                        figname,
                    sigfile.Get(histname),
                    bkgfile.Get(histname),
                    totfile.Get(histname),
                    )
                '''
                hhname='gjet_%d_%d_%d_px1_chIso' % (etabin,jetbin,ptbin)
                figname='%s/sigmodel_%d_%d_%d.png' % (mydir,etabin,jetbin,ptbin)
                h=totfile.Get(hhname)
                h.Draw()
                canv.SaveAs(figname)


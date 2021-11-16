#!/usr/bin/env python2
# check histogram is valid or not.
# Ideally, fake data is needed to be exactly the same as sig component and bkg component.

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

    sigfile=ROOT.TFile.Open('../step8.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_sig.root')
    bkgfile=ROOT.TFile.Open('../step8.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_bkg.root')
    totfile=ROOT.TFile.Open('../step8.ClosureTest_SampleCreation/storeroot/iso_fakesample0.root')
    canv=ROOT.TCanvas('c','',600,500)

    for etabin in range(2):
        for jetbin in range(2):
            for ptbin in range(20):
                totname='data_%d_%d_%d_px1_chIso' % (etabin,jetbin,ptbin)
                signame='gjet_%d_%d_%d_px1_chIso' % (etabin,jetbin,ptbin)
                bkgname='data_%d_%d_%d_px2_chIso' % (etabin,jetbin,ptbin)
                figname='%s/sigmodel_%d_%d_%d.png' % (mydir,etabin,jetbin,ptbin)
                hsigTruth=sigfile.Get(totname)
                hbkgTruth=bkgfile.Get(totname)

                htot=totfile.Get(totname)
                for ibin in range(htot.GetNbinsX()):
                    bincontT=htot.GetBinContent(ibin+1)
                    bincontS=hsigTruth.GetBinContent(ibin+1)
                    bincontB=hbkgTruth.GetBinContent(ibin+1)
                    netval=abs((bincontS+bincontB)-bincontT)
                    if abs((bincontS+bincontB)-bincontT) > 1e-2:
                        print 'error : bin info is not matched in %s -- val=%f @ bin %d'%(totname,netval, ibin)

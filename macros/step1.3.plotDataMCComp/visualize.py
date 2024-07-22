#!/usr/bin/env python

import sys,os
from math import sqrt
import ROOT as rt
import libPython.CMS_lumi, libPython.tdrstyle

LOG_Y_SCALE = False

#libPython.tdrstyle.setTDRStyle()


def show_bins(h):
    print(f'hist {h.GetName()} has # bins {h.GetNbinsX()} with edge {h.GetBinLowEdge(1)} and {h.GetBinLowEdge(h.GetNbinsX()+2)}')

infile = 'dataMCcomp.root'
#variables = [ 'phoPt', 'phoEta', 'phoPhi', 'chiso', 'nVtx', 'jetPt' ]
variables = [ 'phoEta' ]

tfile = rt.TFile.Open(infile)
for var in variables:
    c = rt.TCanvas( 'canv', 'hi', 800, 1000)
    libPython.CMS_lumi.lumi_13TeV = "36.33 fb^{-1}"
    libPython.CMS_lumi.CMS_lumi(c, 4, 10)
    c.SetTopMargin(0.10)
    c.SetBottomMargin(0.30)
    c.SetLeftMargin(0.12)
    legend = rt.TLegend(0.15,0.80,0.95,0.90)
    legend.SetFillColor(4000)
    legend.SetFillStyle(4000)
    legend.SetBorderSize(0)
    legend.SetNColumns(3)

    datahist = tfile.Get(f'expdata/{var}')
    datahist.SetMarkerSize(1)
    datahist.SetMarkerStyle(34)
    datahist.SetLineWidth(2)
    datahist.SetLineColor(1)

    signhist = tfile.Get(f'signALL/{var}')
    signhist.Sumw2()
    signhist.SetFillColor(46)
    signhist.SetLineColor(0)

    fakehist = tfile.Get(f'fakeALL/{var}')
    fakehist.Sumw2()
    fakehist.SetFillColor(14)
    fakehist.SetLineColor(0)

    sumhist = signhist.Clone()
    sumhist.Add(fakehist)
    chi2_ndf = datahist.Chi2Test(sumhist, "UW OF P CHI2/NDF")
    chi2_per_ndof = f'{chi2_ndf:.1f}'.replace('.', 'p')
    if LOG_Y_SCALE:
        c.SetLogy()
        maxY = datahist.GetMaximum() * 1e2
        minY = datahist.GetMinimum()
    else:
        maxY = datahist.GetMaximum() * 1.4
        minY = datahist.GetMinimum()

    #datahist.GetYaxis.SetRangeUser(minY,maxY)
    #signhist.GetYaxis.SetRangeUser(minY,maxY)
    #fakehist.GetYaxis.SetRangeUser(minY,maxY)




    k_factor = datahist.Integral() / (signhist.Integral()+fakehist.Integral())
    k2_factor = (datahist.Integral()-signhist.Integral())/fakehist.Integral()
    print(f'k factor = {datahist.Integral()} / ({signhist.Integral()}+{fakehist.Integral()}) = {k_factor}')
    print(f'k factor algorithm2 : Ndata = Nsig+ Nqcd*k-factor2 =  {k2_factor}')
    signhist.Scale(k_factor)
    fakehist.Scale(k_factor)

    stackplot = rt.THStack('hs', f'\chi^{2}/DoF = {chi2_ndf:.1f}')
    stackplot.Add(fakehist)
    stackplot.Add(signhist)
    stackplot.SetMaximum(maxY)



    ratioplot = rt.TRatioPlot(stackplot, datahist)
    ratioplot.Draw()

    ratioplot.GetLowYaxis().SetNdivisions(505)
    ratioplot.GetLowerRefYaxis().SetRangeUser(0.5,1.5)

    ratioplot.GetXaxis().SetTitle('aasdfasdlf')
    ratioplot.GetLowerRefXaxis().SetTitle('aasdfasdlf')

    legend.AddEntry(datahist, 'data', 'p')
    legend.AddEntry(signhist, 'signal', 'f')
    legend.AddEntry(fakehist, 'QCD', 'f')

    legend.SetHeader(f'k-factor {k_factor:.3f}')
    legend.Draw()


    c.Print(f'checkplot_{var}.pdf')
    #c.Print(f'checkplot_{var}.C')

    del c





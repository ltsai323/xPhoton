#!/usr/bin/env python2

import ROOT
import sys
def GetHist(fname):
    file=ROOT.TFile.Open(fname)

    hdpt=file.Get('hdpt')
    hdpt.SetTitle("#DeltaR < 0.2")
    hdpt.GetXaxis().SetTitle('#Delta p_{t}')
    hdpt.SetStats(False)
    hdpt.SetDirectory(0)
    return hdpt

files=sys.argv[1:]

hists=[ GetHist(file) for file in files ]

canv=ROOT.TCanvas('c1','',1200,1000)
canv.SetLogy()
canv.SetFillColor(4000)
canv.SetFillStyle(4000)

[ hist.SetLineWidth(3) for hist in hists ]
hists[1].SetLineColor(2)

hists[0].Draw("AXIS")
[ hist.Draw("same") for hist in hists ]

leg=ROOT.TLegend(0.4,0.5, 0.8,0.7)
leg.SetBorderSize(0)
leg.AddEntry(hists[0], '2016 94X ReReco')
leg.AddEntry(hists[1], '2015 76X ReReco')
leg.Draw()



canv.SaveAs('deltaPt.pdf')



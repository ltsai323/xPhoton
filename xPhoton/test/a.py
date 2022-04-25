#!/usr/bin/env python2

import ROOT


if __name__ == "__main__":
    import sys
    ifile = ROOT.TFile.Open(sys.argv[1])
    itree = ifile.Get("t")

    canv=ROOT.TCanvas('c1', '', 1600,1000)
    canv.SetFillColor(4000)
    canv.SetFillStyle(4000)
    canv.SetFrameFillColor(4000)
    canv.SetFrameFillStyle(4000)
    itree.SetLineWidth(3)
    itree.Draw('photonIDmva >> cmsmva', 'recoPt > 200 && recoPt < 300')
    itree.SetLineColor(2)
    itree.Draw('mva >> selfmva'       , 'recoPt > 200 && recoPt < 300', "SAME")

    leg=ROOT.TLegend(0.25,0.4, 0.7,0.89)
    leg.SetBorderSize(0)
    leg.AddEntry( 'selfmva', 'New BDT score', 'l' )
    leg.AddEntry( 'cmsmva',  'cms offical mva', 'l' )
    leg.Draw()
    canv.SaveAs('hi.pdf')



#!/usr/bin/env python2

import ROOT

if __name__ == '__main__':
    fin=ROOT.TFile.Open('reducedTree.root')
    tin=fin.Get('t')
    canv=ROOT.TCanvas('c1','',1200,1000)
    canv.SetFillColor(4000)
    canv.SetFillStyle(4000)
    tin.Draw('mva>>calb', 'chIsoCalb>5 && recoPtCalib>25&&recoPtCalib<34 && fabs(recoEta)<1.4442')
    tin.Draw('mva>>orig', 'chIsoRaw>5  && recoPtCalib>25&&recoPtCalib<34 && fabs(recoEta)<1.4442')

    horig=ROOT.gROOT.FindObject('orig')
    hcalb=ROOT.gROOT.FindObject('calb')

    hcalb.SetLineColor(2)
    hcalb.SetMarkerColor(2)

    horig.GetXaxis().SetTitle("BDT output")
    hcalb.GetXaxis().SetTitle("BDT output")
    ratioplot=ROOT.TRatioPlot(hcalb, horig)
    ratioplot.Draw()

    ratioplot.GetLowerRefYaxis().SetRangeUser(0.95,1.0)
    ratioplot.GetLowerRefYaxis().SetNdivisions(501)
    ratioplot.GetUpperPad().cd()
    leg=ROOT.TLegend(0.3, 0.4, 0.75, 0.8)
    leg.AddEntry(horig, 'Raw Data', 'pl')
    leg.AddEntry(hcalb, 'Rho Corrected ChIso', 'pl')
    leg.Draw()

    canv.SaveAs('hi.pdf')

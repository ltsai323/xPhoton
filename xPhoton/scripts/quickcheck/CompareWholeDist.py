#!/usr/bin/env python2

import ROOT


f0=ROOT.TFile.Open('output_job_PhotonHFJet_mcorig.root')
f1=ROOT.TFile.Open('output_job_PhotonHFJet_1.root')
t0=f0.Get('t')
t1=f1.Get('t')

h0=ROOT.TH1F('h0','',10,-1.,1.)
h1=ROOT.TH1F('h1','',10,-1.,1.)


canv=ROOT.TCanvas('c1','',800,800)
canv.SetFillColor(4000)
canv.SetFillStyle(4000)

t0.Draw('mva>>h0')
t1.Draw('mva>>h1')

h0.SetFillColor(40)

h1.SetFillColor(30)


hs=ROOT.THStack('hs','BDT output')
hs.Add(h0)
hs.Add(h1)

hs.Draw('nostackb')

leg=ROOT.TLegend(0.2,0.6,0.65,0.80)
leg.AddEntry(h0,'2015 Correction','f')
leg.AddEntry(h1,'2016 legacy Correction (for test)','f')
leg.Draw()



canv.SaveAs('mva.pdf')

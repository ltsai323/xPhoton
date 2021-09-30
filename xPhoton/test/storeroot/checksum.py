#!/usr/bin/env python2

import ROOT
dframe = ROOT.ROOT.Experimental.TDataFrame('genweightsummary', 'crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root')

h=dframe.Histo1D('sumupgenweight')
print h.Integral(1,h.GetNbinsX()-1)
canv=ROOT.TCanvas('c1','',1200,1000)
h.Draw()

canv.SaveAs('hi.png')

#!/usr/bin/env python2

import ROOT

if __name__ == '__main__':
    import sys
    file=ROOT.TFile.Open(sys.argv[1])
    newname=sys.argv[1].split('/')[-1] + '.png'
    tree=file.Get('t')

    canv=ROOT.TCanvas('c1','',1200,1000)

    hist=ROOT.TH1F('h', 'photon pt', 500, 0.,500.)
    tree.Draw('recoPt>>h', 'mcweight')
    canv.SetLogy()
    canv.SaveAs( newname )




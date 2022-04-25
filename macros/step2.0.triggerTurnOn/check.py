#!/usr/bin/env python2

import ROOT

if __name__ == '__main__':
    fin = ROOT.TFile.Open('output.root')
    hUp = fin.Get('HLTintersect_5_6')
    hDn = fin.Get('HLT_5')
    for ibin in range(1,hUp.GetNbinsX()+1):
        if hDn.GetBinContent(ibin)!=0:
            print('at bin %d : up = %.1e and dn = %.1e. ratio = %.2e' % (ibin,
            hUp.GetBinContent(ibin),hDn.GetBinContent(ibin),
            hUp.GetBinContent(ibin)/hDn.GetBinContent(ibin) ) )

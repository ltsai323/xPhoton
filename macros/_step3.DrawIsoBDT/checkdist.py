#!/usr/bin/env python2
# not completed!
#

import ROOT
def EventExist(hist1, hist2):
    if hist1.GetEntries() / hist2.GetEntries() > 1e-3: print 'exist!'
def SameDistribution(hist1,hist2):
    pass

if __name__ == '__main__':
    infile=ROOT.TFile.Open('storeroot/isovsbdt_template.root')
    h_sig_signal  =infile.Get('data_0_0_0_px1')
    h_sig_sideband=infile.Get('data_0_0_0_px2')
    signal={
            'data':infile.Get('data_0_0_0_px1_chIso'),
            'sig' :infile.Get('gjet_0_0_0_px1_chIso'),
            'bkg' :infile.Get( 'qcd_0_0_0_px1_chIso'),
        }
    sideband={
            'data':infile.Get('data_0_0_0_px2_chIso'),
            'sig' :infile.Get('gjet_0_0_0_px2_chIso'),
            'bkg' :infile.Get( 'qcd_0_0_0_px2_chIso'),
        }

    EventExist(sideband['sig'])

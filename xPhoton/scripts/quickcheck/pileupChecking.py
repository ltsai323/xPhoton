#!/usr/bin/env python2

import ROOT
def RootFile_Data():
    return '/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root'
def RootFile_Target():
    import sys
    import os
    if len(sys.argv) < 2: raise IOError('input a root file')
    if not os.path.isfile(sys.argv[1]): raise IOError('input file does not exist')
    return sys.argv[1]
def OpenTree(filename,treename='t'):
    file=ROOT.TFile.Open(filename)
    tree=file.Get(treenaem)
    return (file,tree)
def Entries_data(hist):
    return hist.GetEntries()
def Entries_MC(hist):
    return sum( [hist.GetBinContent(ibin+1) for ibin in hist.GetNbinsX()] )

if __name__ == '__main__':
    file_data,tree_data = OpenTree( RootFile_Data() )
    f_targets,t_targets = OpenTree( RootFile_Target() )

    import xPhoton.xPhoton.Managers.PlotMgr as PlotMgr
    import xPhoton.xPhoton.Managers.LogMgr as LogMgr
    canv=PlotMgr.MyCanvas(smallsize=True)
    canv.SetOutputFormats('png')

    

#!/usr/bin/env python2
import ROOT
#import xPhoton.xPhoton.Managers.HistMgr as HistMgr
from  xPhoton.xPhoton.Managers.HistMgr import HistMgr1D
import xPhoton.xPhoton.Managers.LogMgr as LogMgr

def findDataSideBand( fname, oname ):
    file=ROOT.TFile.Open(fname)
    tree=file.Get('t')

    #newfile=ROOT.TFile(oname,'recreate')
    sidebandchecks=HistMgr1D('sideband')
    sidebandchecks.CreateHist('pt', 100,0.,1000.)
    tree.Draw( 'recoPt >> {}'.format(sidebandchecks.FullName('pt')) )

    canv=ROOT.TCanvas('c1','',1000,1000)
    sidebandchecks['pt'].Draw()
    canv.SaveAs('hi.png')

    '''
    newfile.cd()
    for chname,checkplot in sidebandchecks.iteritems():
        checkplot.Write()
    '''

if __name__ == '__main__':
    import sys

    mylog=LogMgr.InitLogger(level='debug')
    findDataSideBand( sys.argv[1], '' )

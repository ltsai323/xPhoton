#!/usr/bin/env python2

import ROOT

class MyDataHist(ROOT.TH1F):
    pass

class MyMCHist(ROOT.TH1F):
    def __init__(self, *args):
        super(MyHist, self).__init__(self, *args)
    def SetColorStyle(self, color=2, style=1001):
        self.SetLineColor(0)
        self.SetLineStyle(0)
        self.SetFillColor(color)
        self.SetFillStyle(style)

def InFile_SigPythia():
    return ''
def InFile_SigMadgraph():
    return ''
def InFile_QCDPythia():
    return ''
def InFile_QCDMadgraph():
    return ''
def InFile_Data():
    return ''

class GetTreeObj(object):
    def __init__(self, ifile):
        self._tfile=ROOT.TFile.Open(ifile)
        self._ttree=self._tfile.Get('t')
    def __del__(self):
        print 'deleting input file'
        self._tfile.Close()
    def Draw(self,*args):
        self._ttree.Draw(*args)
class HistCompare(object):
    def __init__(self, name, title, nbin, xmin, xmax):
        self.hExp=ROOT.TH1F( 'exp_'+name, title, nbin, xmin, xmax )
        self.hSig=ROOT.TH1F( 'sig_'+name, title, nbin, xmin, xmax )
        self.hBkg=ROOT.TH1F( 'bkg_'+name, title, nbin, xmin, xmax )
    def plotOn(self, canv, setlogy=False):
        canv.cd()
        canv.SetLogy(setlogy)
        self.hExp.Draw('axis')
        self.hSig.Draw('AC same')
        self.hBkg.Draw('AC same')
        self.hExp.Draw('p  same')
    def ExpName(self): return self.hExp.GetName()
    def SigName(self): return self.hSig.GetName()
    def BkgName(self): return self.hBkg.GetName()

calibrationVariables=[
    ('scEtaWidth',             'calib_scEtaWidth', ),
    ('scPhiWidth',             'calib_scPhiWidth', ),
    ('r9Full5x5',              'calib_r9Full5x5', ),
    ('s4Full5x5',              'calib_s4Full5x5', ),
    ('sieieFull5x5',           'calib_sieieFull5x5', ),
    ('sieipFull5x5',           'calib_sieipFull5x5', ),
    ('esEnergyOverSCRawEnergy','calib_esEnergyOverSCRawEnergy', ),
]


if __name__ == "__main__":
    tSig=GetTreeObj( InFile_SigPythia() )
    tQCD=GetTreeObj( InFile_QCDPythia() )
    tExp=GetTreeObj( InFile_Data()      )

    histset_S4=HistCompare('s4', 's4 distribution', 100, 0., 1.)

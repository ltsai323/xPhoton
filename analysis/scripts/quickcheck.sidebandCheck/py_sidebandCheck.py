#!/usr/bin/env python2

import ROOT
from array import array

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
    return '/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/SigPythia.root'
def InFile_SigMadgraph():
    return '/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root'
def InFile_QCDPythia():
    return '/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/QCDPythia.root'
def InFile_QCDMadgraph():
    return '/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root'
def InFile_Data():
    return ''
#/home/ltsai/ReceivedFile/GJet/noMCIsoCut/sigMC_pythia.root
#/home/ltsai/ReceivedFile/GJet/noMCIsoCut/sigMC_madgraph.root

class GetTreeObj(object):
    def __init__(self, ifile):
        self._tfile=ROOT.TFile.Open(ifile)
        self._ttree=self._tfile.Get('t')
    def __del__(self):
        print 'deleting input file'
        self._tfile.Close()
    def Draw(self,*args):
        self._ttree.Draw(*args)
class SigBkgHists(object):
    def __init__(self, name, title, nbin, xmin, xmax):
        self.hSig=ROOT.TH1F( 'sig_'+name, title, nbin, xmin, xmax )
        self.hBkg=ROOT.TH1F( 'bkg_'+name, title, nbin, xmin, xmax )

    def plotOn(self, canv, setlogy=False):
        canv.cd()
        canv.SetLogy(setlogy)
        h0Max=self.hSig.GetMaximum()
        h1Max=self.hBkg.GetMaximum()
        hMax= 1000.*h0Max if h0Max > h1Max else 1000.*h1Max
        h0Min=self.hSig.GetMinimum()
        h1Min=self.hBkg.GetMinimum()
        hMin= 0.1*h0Min if h0Min < h1Min else 0.1*h1Min
        self.hSig.SetMaximum(hMax)
        self.hSig.SetMinimum(hMin)
        self.hSig.GetXaxis().SetTitle('chIso')
        self.hSig.GetYaxis().SetTitle('Entries')
        self.hSig.SetLineColor(2)
        self.hSig.SetLineWidth(3)
        self.hSig.SetStats(False)
        self.hBkg.SetMaximum(hMax)
        self.hBkg.SetMinimum(hMin)
        self.hBkg.GetXaxis().SetTitle('chIso')
        self.hBkg.GetYaxis().SetTitle('Entries')
        self.hBkg.SetLineColor(4)
        self.hBkg.SetLineWidth(3)
        self.hBkg.SetStats(False)

        self.hSig.Draw('hist')
        self.hBkg.Draw('hist same')
    def SigName(self): return self.hSig.GetName()
    def BkgName(self): return self.hBkg.GetName()
class MyCanv(ROOT.TCanvas):
    def __init__(self, *args):
        super(MyCanv, self).__init__(*args)
        #self.SetFillColor(4000)
        #self.SetFillStyle(4000)


# Integral x-bin : from 1 to N
def CompareIntegral(hist_):
    val_integral=hist_.Integral(11, hist_.GetNbinsX()+1)
    val_sumethod=sum( [hist_.GetBinContent(ibin+1) for ibin in range(10,hist_.GetNbinsX())] )
    print 'the entries of %s : sum up = %.1f and integral = %.1f' % (hist_.GetName(), val_sumethod, val_integral)

def GetGraph(xarr,yarr):
    yval=array('f', yarr)
    xval=array('f', xarr)
    graph=ROOT.TGraph( len(yarr), xval, yval )
    return graph
def SigRatio_signalregion(hSigBkg_): # integrated from bin 1 to bin i
    xvalue=[ hSigBkg_.hSig.GetBinLowEdge( ibin+1 ) for ibin in range(hSigBkg_.hSig.GetNbinsX()) ]
    sumSig=[ hSigBkg_.hSig.Integral( 1, ibin+1                         ) for ibin in range(hSigBkg_.hSig.GetNbinsX()) ]
    sumBkg=[ hSigBkg_.hBkg.Integral( 1, ibin+1                         ) for ibin in range(hSigBkg_.hBkg.GetNbinsX()) ]
    sumAll=[ sig+bkg for sig,bkg in zip(sumSig, sumBkg) ]
    sigRatio=[ sig/All for sig,All in zip(sumSig,sumAll) ]
    return GetGraph(xvalue,sigRatio)

def SigRatio_datasideband(hSigBkg_): # integrated from bin i to bin N
    xvalue=[ hSigBkg_.hSig.GetBinLowEdge( ibin+1 ) for ibin in range(hSigBkg_.hSig.GetNbinsX()) ]
    sumSig=[ hSigBkg_.hSig.Integral( ibin+1, hSigBkg_.hSig.GetNbinsX() ) for ibin in range(hSigBkg_.hSig.GetNbinsX()) ]
    sumBkg=[ hSigBkg_.hBkg.Integral( ibin+1, hSigBkg_.hBkg.GetNbinsX() ) for ibin in range(hSigBkg_.hBkg.GetNbinsX()) ]
    sumAll=[ sig+bkg for sig,bkg in zip(sumSig, sumBkg) ]
    sigRatio=[ sig/All for sig,All in zip(sumSig,sumAll) ]

    return GetGraph(xvalue,sigRatio)

if __name__ == "__main__":
    #tSig=GetTreeObj( InFile_SigPythia() )
    #tQCD=GetTreeObj( InFile_QCDPythia() )
    tSig=GetTreeObj( InFile_SigMadgraph() )
    tQCD=GetTreeObj( InFile_QCDMadgraph() )
    #tExp=GetTreeObj( InFile_Data()      )

    h_sigbkg=SigBkgHists('chIso', 'chIso distribution', 100, 0., 15.)

    tSig.Draw('chIsoRaw >> '+ h_sigbkg.SigName(), '(recoPt > 175.&& (isMatched==1&&mcCalIso04<5) )*mcweight*puwei')
    tQCD.Draw('chIsoRaw >> '+ h_sigbkg.BkgName(), '(recoPt > 175.&&!(isMatched==1&&mcCalIso04<5) )*mcweight*puwei')

    CompareIntegral(h_sigbkg.hSig)
    CompareIntegral(h_sigbkg.hBkg)

    canv=MyCanv('canv','',1200,1000)
    h_sigbkg.plotOn(canv, setlogy=True)
    canv.SaveAs('chIsoDistribution.pdf')

    graph_signalregion=SigRatio_signalregion(h_sigbkg)
    #canv.SetLogy(False)
    graph_signalregion.SetTitle('Signal Ratio #equiv Nsig/Nbkg cumulated from chIso = [0,val]')
    graph_signalregion.GetXaxis().SetTitle('chIso')
    graph_signalregion.GetYaxis().SetTitle('ratio')
    #graph_signalregion.GetYaxis().SetNdivisions(50520)
    graph_signalregion.Draw('AC*')
    canv.SaveAs('signalregion.pdf')
    graph_datasideband=SigRatio_datasideband(h_sigbkg)
    graph_datasideband.SetTitle('Signal Ratio #equiv Nsig/Nbkg cumulated from chIso = [val,15]')
    graph_datasideband.GetXaxis().SetTitle('chIso')
    graph_datasideband.GetYaxis().SetTitle('ratio')
    graph_datasideband.GetYaxis().SetNdivisions(512)
    graph_datasideband.Draw('AC*')
    canv.SaveAs('datasideband.pdf')

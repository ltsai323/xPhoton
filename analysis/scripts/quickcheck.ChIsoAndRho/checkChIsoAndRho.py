#!/usr/bin/env python2
import ROOT
from array import array
# use TH2F::ProfileX() to get avgChIso:rho plot


def GetProfile(infile, extracut='', prefix=''):
    infile=ROOT.TFile.Open(infile)
    intree=infile.Get('t')

    histname=prefix+'_hist'
    cuts=['rho<50']
    if extracut: cuts.append(extracut)
    hist2d=ROOT.TH2D(histname,'', 50,0.,50., 150,0.,15.)
    intree.Draw( 'chIsoRaw:rho >> '+histname, '&&'.join(cuts) )
    prof=hist2d.ProfileX(prefix+'_profile')
    prof.SetDirectory(0)
    prof.SetTitle('')
    prof.GetXaxis().SetTitle('#rho')
    prof.GetYaxis().SetTitle('Averaged charge isolation')
    return prof

def GetBinAvg(hist2d):
    ''' double check by myself algorithm'''
    chIsoSum=[
            sum( [hist2d.GetYaxis().GetBinLowEdge(ybin+1)*hist2d.GetBinContent(xbin+1,ybin+1) for ybin in range(hist2d.GetNbinsY())] )
            for xbin in range(hist2d.GetNbinsX()) ]
    binentries=[
            sum( [                                        hist2d.GetBinContent(xbin+1,ybin+1) for ybin in range(hist2d.GetNbinsY())] )
            for xbin in range(hist2d.GetNbinsX()) ]

    chIsoAvg=[ sumIso/binentry if binentry>1e-4 else sumIso for sumIso,binentry in zip(chIsoSum,binentries) ]
    return chIsoAvg

def GetGraph(infile, isSig, prefix):
    ''' double check by myself algorithm'''
    infile=ROOT.TFile.Open(infile)
    intree=infile.Get('t')

    histname=prefix+'_hist'
    intree.Draw( 'chIsoRaw:rho >> '+histname, 'rho<50 && isMatched %s 1'%('==' if isSig else '!=') )
    hist2d=ROOT.gROOT.FindObject(histname)

    yvals=GetBinAvg(hist2d)
    xvals=[ hist2d.GetXaxis().GetBinLowEdge(xbin+1) for xbin in range(hist2d.GetNbinsX()) ]

    graph=ROOT.TGraph(len(xvals), array('f',xvals), array('f',yvals))
    #graph.SetDirectory(0)
    return graph
    ''' example usage
    prof_sig=GetGraph('/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root',
            isSig=True, prefix='sig')
    prof_bkg=GetGraph('/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root',
            isSig=False, prefix='bkg')
    canv.Clear()
    prof_bkg.SetMarkerColor(39)
    prof_bkg.SetMarkerSize(2)
    prof_bkg.SetLineColor(39)
    prof_bkg.Draw('AP')
    prof_sig.Draw('P same')
    '''



if __name__ == '__main__':
    ROOT.gROOT.SetBatch(True)
    canv=ROOT.TCanvas('canv','',1200,1000)
    canv.SetFillColor(4000)
    canv.SetFillStyle(4000)

    '''
    prof_bkg=GetProfile('/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root',
            extracut='isMatched!=1', prefix='bkg')
    '''
    prof_sig=GetProfile('/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root',
            extracut='isMatched==1', prefix='sig')

    prof_dat=GetProfile('/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root',
            prefix='data')
    '''
    prof_bkg.SetMaximum( prof_bkg.GetMaximum()*1.5 )
    prof_bkg.SetMinimum( 0.)

    prof_bkg.SetMarkerColor(39)
    prof_bkg.SetLineColor(39)
    prof_sig.SetMarkerColor(46)
    prof_sig.SetLineColor(46)
    prof_bkg.Draw('l')
    prof_sig.Draw('l same')
    prof_dat.Draw('p same')
    '''
    #prof_dat.SetMaximum( prof_bkg.GetMaximum()*1.5 )
    prof_dat.SetMinimum( 0.)

    prof_sig.SetMarkerColor(46)
    prof_sig.SetMarkerStyle(4)
    prof_sig.SetLineColor(46)
    #pref_sig.SetLineStyle(4)
    prof_dat.Draw('pe')
    prof_sig.Draw('pe same')



    #leg=ROOT.TLegend(0.2,0.2, 0.75, 0.4)
    leg=ROOT.TLegend(0.15,0.65, 0.75, 0.85)
    leg.AddEntry(prof_dat, 'Leading photon candidates in data', 'pe')
    leg.AddEntry(prof_sig, 'Signal photon from #gamma+jet sample', 'pe')

    leg.SetBorderSize(0)
    leg.SetFillColor(4000)
    leg.SetFillStyle(4000)
    leg.Draw()

    canv.SaveAs('k.pdf')

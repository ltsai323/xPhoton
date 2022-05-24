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
def ProfiledVar( th2name, profilename ):
    hist2d=ROOT.gROOT.FindObject(th2name)
    prof=hist2d.ProfileX(profilename)
    prof.SetDirectory(0)
    prof.SetTitle('')
    prof.GetXaxis().SetTitle('#rho')
    prof.GetYaxis().SetTitle('Averaged charge isolation')
    prof.SetStats(False)
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

class MyTree(object):
    def __init__(self, fname, tname='t'):
        self.fname=fname
        self.tfile=ROOT.TFile.Open(fname)
        self.ttree=self.tfile.Get(tname)
    def __del__(self):
        self.tfile.Close()
    def Draw(self, *args):
        self.ttree.Draw(*args)


if __name__ == '__main__':
    ROOT.gROOT.SetBatch(True)
    canv=ROOT.TCanvas('canv','',1200,1000)
    canv.SetFillColor(4000)
    canv.SetFillStyle(4000)

    tdata=MyTree('/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/scripts/updatingusedvars/updated_data.root')
    tdata.Draw("   chIsoRaw:rho >> orig2d(50,0.,50.,150,0.,15.)", "rho<50 && mva > 0")
    tdata.Draw("calib_chIso:rho >> calb2d(50,0.,50.,150,0.,15.)", "rho<50 && mva > 0")

    profileChIsoRaw=ProfiledVar('orig2d', 'raw_AvgChIso')
    profileClbChIso=ProfiledVar('calb2d', 'clb_AvgChIso')
    profileChIsoRaw.GetYaxis().SetRangeUser(1.2, 2.2)


    #tdata.Draw("   chIsoRaw:rho >> orig2d(50,0.,50.,150,0.,15.)", "rho<50")
    #tdata.Draw("calib_chIso:rho >> calb2d(50,0.,50.,150,0.,15.)", "rho<50")

    #profileChIsoRaw=ProfiledVar('orig2d', 'raw_AvgChIso')
    #profileClbChIso=ProfiledVar('calb2d', 'clb_AvgChIso')
    #profileChIsoRaw.GetYaxis().SetRangeUser(2.2, 3.4)

    profileChIsoRaw.SetMarkerStyle(26)
    profileClbChIso.SetMarkerStyle(5)
    profileClbChIso.SetMarkerColor(2)
    profileClbChIso.SetLineColor(2)



    profileChIsoRaw.Draw('pe')
    profileClbChIso.Draw('pe same')



    #leg=ROOT.TLegend(0.2,0.2, 0.75, 0.4)
    leg=ROOT.TLegend(0.15,0.65, 0.75, 0.85)
    leg.SetHeader('UL2018 data')
    leg.AddEntry(profileChIsoRaw, 'original averaged chIso', 'pe')
    leg.AddEntry(profileClbChIso, 'calibrated averaged chIso', 'pe')

    leg.SetBorderSize(0)
    leg.SetFillColor(4000)
    leg.SetFillStyle(4000)
    leg.Draw()

    canv.SaveAs('k.pdf')

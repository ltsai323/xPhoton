#!/usr/bin/env python2 
import ROOT


def SidebandRatio(hist):
    signalEvts=0.
    sidebandEvts=0.
    for idx in range(2): signalEvts+=hist.GetBinContent(idx+1)
    for idx in range(5,15):
        sidebandEvts+=hist.GetBinContent(idx+1)
    return (signalEvts,sidebandEvts)


fileM=ROOT.TFile('/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root')
fileP=ROOT.TFile('test/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root')
treeM=fileM.Get('t')
treeP=fileP.Get('t')
canv=ROOT.TCanvas('c1','',1200,1000)
canv.SetLogy()
canv.SetFillColor(4000)
canv.SetFillStyle(4000)

histM=ROOT.TH1F('histM', '', 30, 0., 15.)
histP=ROOT.TH1F('histP', '', 30, 0., 15.)
treeM.Draw('chIsoRaw>>histM', 'isMatched==1')
treeP.Draw('chIsoRaw>>histP', 'isMatched==1')

histM.Scale( 1./float(histM.GetEntries()) )
histM.SetLineWidth(2)
histM.SetStats(False)
histM.GetXaxis().SetTitle('charge isolation (GeV)')

histP.Scale( 1./float(histP.GetEntries()) )
histP.SetLineColor(2)
histP.SetLineWidth(2)
histP.SetStats(False)
histP.GetXaxis().SetTitle('charge isolation (GeV)')


leg=ROOT.TLegend(0.3,0.6, 0.85,0.85)
leg.AddEntry(histM, '2016 #gamma + jet Madgraph generator', 'l')
leg.AddEntry(histP, '2016 #gamma + jet pythia generator (Pt20to40)', 'l')
leg.SetBorderSize(0)

histP.Draw()
histM.Draw('same')
leg.Draw()
canv.SaveAs('chIso.noweight.pdf')
#sig, bkg = SidebandRatio(hist)
#print 'No weight : sideband %.0f / signal %.0f = %.2f%%' % ( bkg, sig, bkg/sig*100. )


'''
tree.Draw('chIsoRaw>>hist', 'mcweight*puwei && isMatched==1')
#canv.SaveAs('chIso.withweight.png')

sig, bkg = SidebandRatio(hist)
print 'No weight : sideband %.0f / signal %.0f = %.5f' % ( bkg, sig, bkg/sig )
'''

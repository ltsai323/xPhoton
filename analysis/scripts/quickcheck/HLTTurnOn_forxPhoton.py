#!/usr/bin/env python2

import ROOT
from array import array
def triggerNames_():
    return [
            "hltEG22HEFilter", "hltEG30HEFilter", "hltEG36HEFilter", "hltEG50HEFilter",
            "hltEG75HEFilter", "hltEG90HEFilter", "hltEG120HEFilter", "hltEG175HEFilter",
            "hltEG300erEtFilter"
        ]
def xAxis_():
    return array('d',
            #[ 22, 30, 36, 50, 60, 85, 100, 115, 135, 155, 175, 200, 250, 300, 400, 500, 750, 1000, 1200 ]
            #[ 22, 30, 36, 50, 60, 85, 100, 115, 135, 155, 175, 200, 250, 300, 400, 500, 750, 1000 ]
            [ 25,34,40,55,70,85,100,115,135,155,175,200,220,250,300,1000 ]
            )
def getTree_(tfile):
    t=tfile.Get('t') # for xphoton
    # t=tfile.Get('EventTree') # for ggtree
    return t
outputdir='storefig'
outfignametemplate='%s/hltcompare_{0}over{1}' % outputdir



if __name__ == '__main__':
    import sys
    inputfile=sys.argv[1]
    hltbit_goal=int(sys.argv[3])
    hltbit_base=int(sys.argv[2])


    import os
    if not os.path.isdir(outputdir): os.mkdir(outputdir)
    print hltbit_goal
    print hltbit_base
    outfigname=outfignametemplate.format(hltbit_goal,hltbit_base) + '.png'



    triggers=triggerNames_()
    xaxis=xAxis_()
    '''
    yaxis_goal=array( 'd', [0]*(len(xaxis)-1) )
    yaxis_base=array( 'd', [0]*(len(xaxis)-1) )
    yaxis_both=array( 'd', [0]*(len(xaxis)-1) )
    '''

    file=ROOT.TFile.Open(inputfile)
    tree=getTree_(file)

    hist_goal=ROOT.TH1F('bit%d'%hltbit_goal,triggers[hltbit_goal], len(xaxis)-1, xaxis)
    hist_base=ROOT.TH1F('bit%d'%hltbit_base,triggers[hltbit_base], len(xaxis)-1, xaxis)
    hist_both=ROOT.TH1F('intersection','&&'.join([triggers[hltbit_goal],triggers[hltbit_base]]), len(xaxis)-1, xaxis)
    hlt_ratio=ROOT.TH1F('ratio','turn on curve', len(xaxis)-1, xaxis)

    tree.Draw( 'recoPt>>bit%d'%hltbit_goal, '(phoFiredTrgs>>%d)&1' % (hltbit_goal) )
    tree.Draw( 'recoPt>>bit%d'%hltbit_base, '(phoFiredTrgs>>%d)&1' % (hltbit_base) )
    tree.Draw( 'recoPt>>intersection'     , '(phoFiredTrgs>>%d)&1 && (phoFiredTrgs>>%d)&1' % (hltbit_goal, hltbit_base) )
    hlt_ratio.Add   (hist_both)
    hlt_ratio.Divide(hist_base)



    canv=ROOT.TCanvas('cc','',1000,1000)
    canv.cd()
    canv.Divide(2,2)
    canv.cd(1)
    hist_base.Draw()
    canv.cd(2)
    hist_goal.Draw()
    canv.cd(3)
    hist_both.Draw()
    canv.cd(4)

    #hlt_ratio.Sumw2()
    hlt_ratio.SetStats(False)
    hlt_ratio.SetMinimum(-0.1)
    hlt_ratio.SetMaximum( 1.2)
    #hlt_ratio.SetGridx(True)
    hlt_ratio.SetMarkerSize(5)
    hlt_ratio.SetMarkerStyle(33)
    hlt_ratio.SetMarkerColor(46)
    hlt_ratio.Draw('P')

    text=ROOT.TPaveText(0.2,0.11,0.89,0.6,"NDC")
    text.AddText('goal : %s'% triggers[hltbit_goal])
    text.AddText('base : %s'% triggers[hltbit_base])
    text.SetFillColor(4000)
    text.SetFillStyle(4000)
    text.SetBorderSize(0)
    text.Draw()

    canv.SaveAs(outfigname)

    canv.Clear()
    canv.cd()
    hlt_ratio.Draw('P')

    text=ROOT.TPaveText(0.2,0.11,0.89,0.6,"NDC")
    text.AddText('goal : %s'% triggers[hltbit_goal])
    text.AddText('base : %s'% triggers[hltbit_base])
    text.SetFillColor(4000)
    text.SetFillStyle(4000)
    text.SetBorderSize(0)
    text.Draw()
    canv.SaveAs(outfignametemplate.format(hltbit_goal,hltbit_base) + '_summary.png' )

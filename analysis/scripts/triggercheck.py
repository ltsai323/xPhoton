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
            [ 22, 30, 36, 50, 60, 85, 100, 115, 135, 155, 175, 200, 250, 300, 400, 500, 750, 1000, 99999999 ]
            )
def getTree_(tfile):
    t=tfile.Get('t')
    # t=tfile.Get('EventTree')
    return t




if __name__ == '__main__':
    import sys
    hltbit_goal=int(sys.argv[2])
    hltbit_base=int(sys.argv[1])



    triggers=triggerNames_()
    xaxis=xAxis_()
    yaxis_goal=array( 'd', [0]*(len(xaxis)-1) )
    yaxis_base=array( 'd', [0]*(len(xaxis)-1) )
    yaxis_both=array( 'd', [0]*(len(xaxis)-1) )

    file=ROOT.TFile.Open('/home/ltsai/Work/workspaceGammaPlusJet/totdata.root')
    tree=getTree_(file)

    print 'evt start'
    for i,evt in enumerate(tree):
        if i%10000==0:
            print 'event in {0} / {1}'.format(i,tree.GetEntries())
        if i==50000:
            break
        for idx,nothing in enumerate(yaxis_goal):
            if evt.recoPt > xaxis[idx] and evt.recoPt < xaxis[idx+1]:
                if evt.phoFiredTrgs>>hltbit_goal&1:
                    yaxis_goal[idx]+=1
                if evt.phoFiredTrgs>>hltbit_base&1:
                    yaxis_base[idx]+=1
                if evt.phoFiredTrgs>>hltbit_goal&1 and evt.phoFiredTrgs>>hltbit_base&1:
                    yaxis_both[idx]+=1
    print 'evt end'
    g_goal=ROOT.TGraph(len(yaxis_goal), xaxis, yaxis_goal)
    g_base=ROOT.TGraph(len(yaxis_base), xaxis, yaxis_base)
    g_both=ROOT.TGraph(len(yaxis_both), xaxis, yaxis_both)

    canv=ROOT.TCanvas('c1','',1000,1000)
    canv.Divide(4)

    canv.cd(1)
    g_goal.Draw('AC')

    canv.cd(2)
    g_base.Draw('AC')

    canv.cd(3)
    g_both.Draw('AC')

    canv.cd(4)
    g_goal.Draw('AC')

    canv.SaveAs('test.png')

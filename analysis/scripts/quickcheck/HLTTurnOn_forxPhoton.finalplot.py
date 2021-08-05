#!/usr/bin/env python2
# work left : separate eb and ee

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
            [ 25,34,40,55,70,85,100,115,135,155,175,200,220,250,300,1000 ]
            )
outputdir='storefig'
outfignametemplate='%s/hltcompare_{0}over{1}' % outputdir


def GetInputFile(argv):
    inputfile=argv[1]

    file=ROOT.TFile.Open(inputfile)
    tree=file.Get('t')
    return (file,tree)

def FillContent( tree, hltbit_goal, hltbit_base ):
    tree.Draw( 'recoPt>>goalbit', '(phoFiredTrgs>>%d)&1' % (hltbit_goal) )
    tree.Draw( 'recoPt>>basebit', '(phoFiredTrgs>>%d)&1' % (hltbit_base) )
    tree.Draw( 'recoPt>>intersection'     , '(phoFiredTrgs>>%d)&1 && (phoFiredTrgs>>%d)&1' % (hltbit_goal, hltbit_base) )
    hlt_ratio=hist_both.Clone('ratio')
    hlt_ratio.Sumw2()
    hlt_ratio.Divide(hist_base)

    #hlt_ratio.SetStats(False)
    hlt_ratio.SetMinimum( 0   )
    hlt_ratio.SetMaximum( 1.1 )
    hlt_ratio.SetMarkerSize(3)
    hlt_ratio.SetMarkerStyle(33)
    #hlt_ratio.SetMarkerColor(46)
    #hlt_ratio.SetLineColor(46)
    hlt_ratio.SetLineWidth(3)
    hlt_ratio.GetXaxis().SetTitle('Pt_{#gamma} (GeV)')
    #hlt_ratio.Draw('PE')
    return hlt_ratio

def SaveCheckerPlots( hists, plotname, canv ):
    hlt_ratio.SetTitle( '%s / %s' % (triggers[hltbit_goal],triggers[hltbit_base]) )

    canv.Clear()
    canv.SetGridx(False)
    canv.SetGridy(False)
    canv.Divide(2,2)
    for idx, hist in enumerate(hists):
        canv.cd(idx+1)
        hist.Draw()
    canv.SaveAs(plotname)
def SaveOutputPlots( hist, plotname, canv ):
    hist.SetTitle('')
    hist.GetYaxis().SetTitle( '%s efficiency' % triggers[hltbit_goal] )

    canv.Clear()
    canv.SetGridx(True)
    canv.SetGridy(True)
    hist.Draw()
    canv.SaveAs(plotname)




if __name__ == '__main__':
    import sys
    #hltbit_goal=int(sys.argv[3])
    #hltbit_base=int(sys.argv[2])


    import os
    if not os.path.isdir(outputdir): os.mkdir(outputdir)
    #outfigname=outfignametemplate.format(hltbit_goal,hltbit_base) + '.png'



    triggers=triggerNames_()
    xaxis=xAxis_()


    file, tree = GetInputFile( sys.argv )

    hist_goal=ROOT.TH1F('goalbit','', len(xaxis)-1, xaxis)
    hist_base=ROOT.TH1F('basebit','', len(xaxis)-1, xaxis)
    hist_both=ROOT.TH1F('intersection','', len(xaxis)-1, xaxis)
    hist_goal .Sumw2()
    hist_base .Sumw2()
    hist_both .Sumw2()

    for hltbit in range(8):
        hltbit_base=hltbit
        hltbit_goal=hltbit+1
        hlt_ratio=FillContent( tree, hltbit_goal, hltbit_base )



        canv=ROOT.TCanvas('cc','',1200,1000)
        canv.SetFillColor(4000)
        canv.SetFillStyle(4000)
        SaveCheckerPlots( [hist_base,hist_goal,hist_both,hlt_ratio],
                'storefig/checkplot_goalbit%d_basebit%d.pdf' %(hltbit_goal,hltbit_base),
                canv)
        SaveOutputPlots( hlt_ratio,
                'storefig/output_efficiency_%s.pdf' %triggers[hltbit_goal],
                canv)


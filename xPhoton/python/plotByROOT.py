#!/usr/bin/env python2

from types import MethodType
import ROOT


def loadTH1(self, file, objname, xLabel=None, yLabel=None, title=None, lineColor=39, lineWidth=4, fillStyle=0, fillColor=0, drawOpt=''):
    h=file.Get(objname)

    if xLabel: h.GetXaxis().SetTitle(xLabel)
    if yLabel: h.GetYaxis().SetTitle(yLabel)
    if title : h.SetTitle(title)

    h.SetLineColor(lineColor)
    h.SetLineWidth(lineWidth)
    h.SetFillStyle(fillStyle)
    h.SetFillColor(fillColor)

    h.Draw(drawOpt)
    return h


if __name__ == '__main__':
    rootfile=ROOT.TFile.Open('output_job_PhotonHFJet_1.root')

    objnamesDR=[
    'SIGConvPhodeltaR_recoPhoton_genElectron',
    'SIGPhodeltaR_recoPhoton_genPhoton',
    'TOTdeltaR_recoPhoton_genElectron',
    'TOTdeltaR_recoPhoton_genPhoton',
    'WRONGRECOPhodeltaR_recoPhoton_genElectron',
    ]

    objnamesDPT=[
    'SIGPhodPt_recoPhoton_genPhoton',
    'SIGConvPhodPt_recoPhoton_genElectron',
    'TOTdPt_recoPhoton_genElectron',
    'TOTdPt_recoPhoton_genMomPhoton',
    'TOTdPt_recoPhoton_genPhoton',
    'WRONGRECOPhodPt_recoPhoton_genElectron',
    'dPt_recoPhoton_genMomPhoton',
    ]


    from python.PlotMgr import DrawingMgr
    DrawingMgr.GeneralSetting()

    dRplots=[ DrawingMgr() for i in objnamesDR ]
    for plot,objname in zip(dRplots,objnamesDR):
        trg1=objname.split('_')[1]
        trg2=objname.split('_')[2]

        plot.AddPlotContent(
                function=loadTH1,
                drawOpt='',
                file=rootfile,
                objname=objname,
                xLabel="#Delta R",
                title="matching parameter to %s - %s" % (trg1, trg2),
                #lineColor=8,
                #lineWidth=4,
                #fillStyle=0,
                #fillColor=0,
                )
        plot.ExportFig('storefig/%s.png' %(objname), logScale=True)

    dPtplots=[ DrawingMgr() for i in objnamesDR ]
    for plot,objname in zip(dPtplots,objnamesDR):
        trg1=objname.split('_')[1]
        trg2=objname.split('_')[2]

        plot.AddPlotContent(
                function=loadTH1,
                drawOpt='',
                file=rootfile,
                objname=objname,
                xLabel="#Delta Pt / Pt(Gen)",
                title="matching parameter to %s - %s" % (trg1, trg2),
                #lineColor=8,
                #lineWidth=4,
                #fillStyle=0,
                #fillColor=0,
                )
        plot.ExportFig('storefig/%s.png' %(objname), logScale=True)

    statplot=DrawingMgr()
    statplot.AddPlotContent(
                function=loadTH1,
                drawOpt='',
                file=rootfile,
                objname='matchingStatus',
                xLabel="",
                title="matching status",
                #lineColor=8,
                #lineWidth=4,
                #fillStyle=0,
                #fillColor=0,
                )
    statplot.ExportFig('storefig/matchingstat.png', logScale=True)





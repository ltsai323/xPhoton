#!/usr/bin/env python2
import ROOT
from types import MethodType
import os
from Managers.LogMgr import GetLogger, LoadLoggerConfig
LoadLoggerConfig('/home/ltsai/local/mylib/data/logger_debug.config')
logger=GetLogger(__name__)


from Managers.AdditionalFunctionMgr import ImportAddFunc
from myfit.RooFitSpaceMgr import RooFitSpaceMgr
from myfit.WorkspaceContents import *


factory_extendpdf='ExtendPdf::{name}({pdf},{num})'
factory_histpdf='HistPdf::{name}({var},{datahist})'
factory_var='{name}({xmin},{xval})'
factory_num='{name}({xdef},{xmin},{xmax})'
factory_addpdf='SUM::{name}({num1}*{pdf1},{num2}*{pdf2})'



if __name__ == '__main__':
    from array import array

    space=ROOT.RooWorkspace('space',False)
    myspace=RooFitSpaceMgr(space)

    var='mva'
    inputinfo=[
    ('data' , '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_data_Run2016G.root'),
    ('mcbkg', '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcbkg_Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
    ('mcsig', '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
    ]
    inputfile=[ ROOT.TFile.Open(p) for t,p in inputinfo ]
    inputhist=[ f.Get(var) for f in inputfile ]

    CreateVar( myspace, var, inputhist[0].GetXaxis().GetXmin(), inputhist[0].GetXaxis().GetXmax() )

    creategaussianpdf(myspace)
    hist_data=None
    for (label,p), hist in zip(inputinfo,inputhist):
        if label=='data':
            hist_data=GetDataHist( myspace, hist, label )
            logger.debug( hist_data[1].GetName() )
            continue
        CreateHistPDF( myspace, hist, label )
        #factorycreatehistpdf( myspace, hist, label )

    totnum=inputhist[0].GetEntries()
    CreateNum(myspace, 'numsig', totnum/2., 0., totnum)
    CreateNum(myspace, 'numbkg', totnum/2., 0., totnum)
    myspace.Factory( factory_addpdf.format(
        name='extpdf',
        num1='numsig',
        pdf1='histPDF_mcsig',
        num2='numbkg',
        pdf2='histPDF_mcbkg',
        ) )
    extpdf=myspace.LoadPdf('extpdf')
    roovar=myspace.LoadVar(var)

    datahist=hist_data[1]
    #extpdf.fitTo(datahist, ROOT.RooFit.Minos(False))
    extpdf.fitTo(datahist)

    plotframe=roovar.frame( ROOT.RooFit.Title('') )
    datahist.plotOn(plotframe)

    extpdf.plotOn(plotframe, ROOT.RooFit.LineColor(3), ROOT.RooFit.LineWidth(4), ROOT.RooFit.Name('Kdata' ))
    extpdf.plotOn(plotframe, ROOT.RooFit.LineColor(4), ROOT.RooFit.LineWidth(4), ROOT.RooFit.Name('Kmcsig'),ROOT.RooFit.Components('histPDF_mcsig'))
    extpdf.plotOn(plotframe, ROOT.RooFit.LineColor(5), ROOT.RooFit.LineWidth(4), ROOT.RooFit.Name('Kmcbkg'),ROOT.RooFit.Components('histPDF_mcbkg'))

    contentList=[
            ('Kdata',   'data'),
            ('Kmcsig', 'mcsig'),
            ('Kmcbkg', 'mcbkg'),
            ]

    leg=ROOT.TLegend(0.60,0.70,0.89,0.89)
    for content in contentList:
        leg.AddEntry(plotframe.findObject(content[0]),content[1],'l')
    leg.SetFillColor(0)
    #leg.SetFillStyle(4000)
    leg.SetBorderSize(0)
    leg.Draw()




    canv=ROOT.TCanvas('c1','c1',1000,1000)
    plotframe.Draw()
    canv.SaveAs('asdftest.png')







    myspace.AddToSpace(plotframe)

    logger.debug('writing to root file')
    myspace.Write('newfile.root')
    for ifile in inputfile:
        ifile.Close()
        logger.debug(ifile.GetName() + ' is closed')

    logger.debug('successfully done')


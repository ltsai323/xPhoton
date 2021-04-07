#!/usr/bin/env python2
import ROOT
from types import MethodType
import os
from Managers.LogMgr import GetLogger, LoadLoggerConfig
LoadLoggerConfig('/home/ltsai/local/mylib/data/logger_debug.config')
logger=GetLogger(__name__)
FIGTEMPLATE='parfit_{0}.png'


from Managers.AdditionalFunctionMgr import ImportAddFunc
from myfit.RooFitSpaceMgr import RooFitSpaceMgr
from myfit.RooFitFittingMgr import RooFitFittingMgr
from myfit.WorkspaceContents import *


factory_extendpdf='ExtendPdf::{name}({pdf},{num})'
factory_histpdf='HistPdf::{name}({var},{datahist})'
factory_var='{name}({xmin},{xval})'
factory_num='{name}({xdef},{xmin},{xmax})'
factory_addpdf='SUM::{name}({num1}*{pdf1},{num2}*{pdf2})'


def AddPdf(spaceMGR, pdfinfos, totentries, pdfname):
    num1=pdfinfos[0][0]
    num2=pdfinfos[1][0]
    pdf1=pdfinfos[0][1].GetName()
    pdf2=pdfinfos[1][1].GetName()

    CreateNum(myspace, num1, totentries/2., 0., totentries)
    CreateNum(myspace, num2, totentries/2., 0., totentries)
    myspace.Factory( factory_addpdf.format(
        name=pdfname,
        num1=num1,
        pdf1=pdf1,
        num2=num2,
        pdf2=pdf2,
        ) )
    return myspace.LoadPdf(pdfname)

def BuildHistPdf(self, spaceMGR, hist, label):
    return CreateHistPDF(spaceMGR,hist,label,'mva')

# input objname_desc_opts is a list contains objname and its description
#def CreateLegend_findObject(self, objname_desc_opts, title=None,p0=(0.60,0.70),p1=(0.89,0.89)):
def CreateLegend_findObject( rooplot, objname_desc_opts, title=None,p0=(0.60,0.70),p1=(0.89,0.89), nColumn=1):
    leg=ROOT.TLegend(p0[0],p0[1],p1[0],p1[1])
    for objname, desc, drawopt in objname_desc_opts:
        leg.AddEntry(rooplot.findObject(objname),desc,drawopt)
    leg.SetHeader(title,'c')
    leg.SetNColumns(nColumn)
    leg.SetFillColor(0)
    #leg.SetFillStyle(4000)
    leg.SetBorderSize(0)
    return leg

def fit2Comps(spacemgr, mfit, name, inputinfo, inputhist):
    var='mva'

    roovar=CreateVar( myspace, var, inputhist[0].GetXaxis().GetXmin(), inputhist[0].GetXaxis().GetXmax() )

    hist_data=None
    fitpdfs=[]
    for (label,p), hist in zip(inputinfo,inputhist):
        if label=='data':
            hist_data=GetDataHist( myspace, hist, label )
            logger.debug( hist_data[1].GetName() )
            continue
        #pdf=CreateHistPDF(myspace,hist,label)
        pdf=CreateHistPDF(myspace,hist,label, 'mva')
        fitpdfs.append( (label,pdf) )


    data_=inputhist[0]
    totnum=data_.GetEntries()
    extpdf=AddPdf(spacemgr, fitpdfs, totnum, 'extpdf')
    for label,pdf in fitpdfs:
        mfit.AddPDFComponents(label,pdf)

    datahist=hist_data[1]
    mfit.SetFitTarget(datahist,roovar)
    #mfit.BuildPDFComponent(asdf)
    mfit.AddPDFFit(extpdf)
    mfit.PerformFitting()

    drawingcontent=mfit.CalculateDrawingContent()

    constituents=[
            ('data'  , 'data',              'pl'),
            ('totFit', 'total fit',         'l'),
            ('mcsig' , 'sigal photon',      'l'),
            ('mcbkg' , 'background photon', 'l'),
            ]

    leg=CreateLegend_findObject(
            rooplot=drawingcontent,
            objname_desc_opts=constituents,
            title='Components',
            p0=(0.2,0.7),
            nColumn=2
            )





    myspace.ReserveItem(drawingcontent)
    canv=ROOT.TCanvas('c1','c1',1000,1000)
    drawingcontent.Draw()
    leg.Draw()
    if name:
        canv.SaveAs(FIGTEMPLATE.format(name))
    return drawingcontent


def Fit2Comps(self, name):
    self.LoadObjects(
            filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_data_data_Run2016G_94XReReco_v1.root',
            loadinfo=('data', 'mva'),
            saveItem=False
            )
    self.LoadObjects(
            filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
            loadinfo=('mcsig', 'mva'),
            saveItem=True
            )
    self.LoadObjects(
            filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcbkg_Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
            loadinfo=('mcbkg', 'mva'),
            saveItem=True
            )

    ipfile=[ (info['label'],info['file']) for info in self.loadinfos ]
    iphist=[ info['obj']   for info in self.loadinfos ]

    fit2Comps(self._workspace, self, name, ipfile, iphist)






if __name__ == '__main__':
    from array import array

    space=ROOT.RooWorkspace('space',False)
    myspace=RooFitSpaceMgr(space)
    fitmgr=RooFitFittingMgr(myspace)

    var='mva'
    inputinfo=[
        ('data' , '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_data_data_Run2016G_94XReReco_v1.root'),
        ('mcbkg', '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcbkg_Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
        ('mcsig', '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
    ]
    inputfile=[ ROOT.TFile.Open(p) for t,p in inputinfo ]
    inputhist=[ f.Get(var) for f in inputfile ]


    #fitmgr.BuildPDFTotal( function=Fit2Comps, name='test' )
    from types import MethodType
    fitmgr.myfunc=MethodType(Fit2Comps, fitmgr)
    fitmgr.myfunc(name='test')
    #fitmgr.BuildPDFTotal( function=Fit2Comps, name='test' )
    #fitmgr.CalculateDrawingContent()
    #fit2Comps(myspace,'test', inputinfo, inputhist)


    logger.debug('writing to root file')
    myspace.Write('newfile.root')
    for ifile in inputfile:
        ifile.Close()
        logger.debug(ifile.GetName() + ' is closed')

    logger.debug('successfully done')


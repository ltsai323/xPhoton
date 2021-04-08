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


def AddPdf(spaceMGR, extpdfnames, outname):
    extpdfs = [ spaceMGR.LoadPdf(pdfname) for pdfname in extpdfnames ]
    extpdf0=spaceMGR.LoadPdf(extpdfnames[0])
    extpdf1=spaceMGR.LoadPdf(extpdfnames[1])

    outpdf=ROOT.RooAddPdf(outname,outname,
            ROOT.RooArgList(*extpdfs)
            )
    spaceMGR.ReserveItem(outpdf)
    return outpdf


'''
def BuildHistPdf(self, spaceMGR, hist, label):
    return CreateHistPDF(spaceMGR,hist,label,'mva')
'''

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


def extractinfo(self): ## refactoring
    datahist=None
    fitpdfs=[]
    for info in self.loadinfos:
        label=info['label']
        p=info['file']
        hist=info['obj']
        if label=='data':
            datahist=CreateDataHist( self._workspace, hist, self.GetObservableName(), '_'.join(['datahist', 'data', self.GetObservableName()]) )
            continue
        print hist.GetName()
        datahist=CreateDataHist( self._workspace, hist, self.GetObservableName(), '_'.join(['datahist', label,self.GetObservableName()]) )
        pdf=CreateHistPDF(self._workspace, datahist, self.GetObservableName(), '_'.join(['histPDF',label,self.GetObservableName()]))
        fitpdfs.append( (label,pdf) )
    return (datahist,fitpdfs)

def Fit2Comps(self, name):
    self.exfunc=MethodType(extractinfo,self)
    datahist, fitpdfs = self.exfunc() ## refactoring


    data_=self.loadinfos[0]['obj']
    totnum=data_.GetEntries()
    extpdf=AddPdf(self._workspace, fitpdfs, totnum, 'extpdf')
    for label,pdf in fitpdfs:
        self.AddPDFComponents(label,pdf)

    self.AddPDFFit(extpdf)
    self.PerformFitting()

    drawingcontent=self.CalculateDrawingContent()

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





    self._workspace.ReserveItem(drawingcontent)
    canv=ROOT.TCanvas('c1','c1',1000,1000)
    drawingcontent.Draw()
    leg.Draw()
    if name:
        canv.SaveAs(FIGTEMPLATE.format(name))
    return drawingcontent









if __name__ == '__main__':
    from array import array

    space=ROOT.RooWorkspace('space',False)
    myspace=RooFitSpaceMgr(space)
    fitmgr=RooFitFittingMgr(myspace)

    obs='mva'

    varhist=fitmgr.LoadObjects(
            filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_data_data_Run2016G_94XReReco_v1.root',
            loadinfo=('data', 'mva'),
            saveANDrenameToworkspace=False
            )
    hfitSources=[]
    hfitSources.append( [ 'mcsig',
            fitmgr.LoadObjects(
                filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
                loadinfo=('mcsig', 'mva'),
                saveANDrenameToworkspace=True
            )
        ] )
    hfitSources.append( [ 'mcbkg',
            fitmgr.LoadObjects(
                filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcbkg_Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
                loadinfo=('mcbkg', 'mva'),
                saveANDrenameToworkspace=True
            )
        ] )


    varrange=( varhist.GetXaxis().GetXmin(), varhist.GetXaxis().GetXmax() )

    roobsv=CreateVar(fitmgr._workspace, obs, varrange)
    target=CreateDataHist(fitmgr._workspace, varhist, obs, '_'.join(['datahist','data',obs]) )
    fitmgr.SetFitTarget( target,roobsv )

    fitfrags=[]
    for label,histsource in hfitSources:
        datahist=CreateDataHist( fitmgr._workspace, histsource, obs, '_'.join(['datahist', label, obs]) )
        histpdf =CreateHistPDF ( fitmgr._workspace, datahist,   obs, '_'.join(['histPDF' , label, obs]) )
        yieldrange=[0.0, 0.0, varhist.GetEntries() ]
        yieldrange[0] = (yieldrange[2]-yieldrange[1])*0.8
        yieldvar=CreateYield   ( fitmgr._workspace, '_'.join(['yield',label,obs]), yieldrange )
        yname=yieldvar.GetName()
        extpdf  =CreateExtPDF  ( fitmgr._workspace, histpdf.GetName(), yname , '_'.join(['extPDF'  , label, obs]) )
        fitmgr.AddPDFComponents( label, extpdf )
        fitfrags.append(extpdf.GetName())
    totpdf=AddPdf(fitmgr._workspace, fitfrags, 'totfit')

    fitmgr.AddPDFFit(totpdf)
    fitmgr.PerformFitting()

    drawingcontent=fitmgr.CalculateDrawingContent()
    constituents=[
            ('data'  , 'data',              'pl'),
            ('totFit', 'total fit',         'l'),
            ('mcsig' , 'sigal photon',      'l'),
            ('mcbkg' , 'background photon', 'l'),
            ]

    leg=CreateLegend_findObject(
            rooplot=drawingcontent,
            objname_desc_opts=[
                ('data'  , 'data',              'pl'),
                ('totFit', 'total fit',         'l'),
                ('mcsig' , 'sigal photon',      'l'),
                ('mcbkg' , 'background photon', 'l'),
            ],
            title='Components',
            p0=(0.2,0.7),
            nColumn=2
            )

    fitmgr._workspace.ReserveItem(drawingcontent)
    canv=ROOT.TCanvas('c1','c1',1000,1000)
    drawingcontent.Draw()
    leg.Draw()
    name='test'
    if name:
        canv.SaveAs(FIGTEMPLATE.format(name))

    #fitmgr.exfunc=MethodType(Fit2Comps, fitmgr)
    #fitmgr.exfunc(name='test')


    logger.debug('writing to root file')
    myspace.Write('newfile.root')

    logger.debug('successfully done')


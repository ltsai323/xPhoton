#!/usr/bin/env python2
import ROOT
from types import MethodType
import os
from xPhoton.xPhoton.Managers.LogMgr import GetLogger, LoadLoggerConfig
LoadLoggerConfig('/home/ltsai/local/mylib/data/logger_debug.config')
logger=GetLogger(__name__)
FIGTEMPLATE='parfit_{0}.png'


from xPhoton.xPhoton.Managers.AdditionalFunctionMgr import ImportAddFunc
from xPhoton.xPhoton.myfit.RooFitSpaceMgr import RooFitSpaceMgr
from xPhoton.xPhoton.myfit.RooFitFittingMgr import RooFitFittingMgr
from xPhoton.xPhoton.myfit.WorkspaceContents import *


factory_extendpdf='ExtendPdf::{name}({pdf},{num})'
factory_histpdf='HistPdf::{name}({var},{datahist})'
factory_var='{name}({xmin},{xval})'
factory_num='{name}({xdef},{xmin},{xmax})'
factory_addpdf='SUM::{name}({num1}*{pdf1},{num2}*{pdf2})'




'''
def BuildHistPdf(self, spaceMGR, hist, label):
    return CreatePDF_Hist(spaceMGR,hist,label,'mva')
'''

# input objname_desc_opts is a list contains objname and its description
#def CreateLegend_findObject(self, objname_desc_opts, title=None,p0=(0.60,0.70),p1=(0.89,0.89)):
def CreateLegend_findObject( rooplot, objname_desc_opts, title=None,p0=(0.60,0.70),p1=(0.89,0.89), nColumn=1):
    leg=ROOT.TLegend(p0[0],p0[1],p1[0],p1[1])
    for objname, desc, drawopt in objname_desc_opts:
        leg.AddEntry(rooplot.findObject(objname),desc,drawopt)
    leg.SetHeader(title,'c')
    leg.SetNColumns(nColumn)
    leg.SetFillColor(4000)
    leg.SetFillStyle(4000)
    #leg.SetFillStyle(4000)

    leg.SetBorderSize(0)
    return leg


'''
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
        pdf=CreatePDF_Hist(self._workspace, datahist, self.GetObservableName(), '_'.join(['histPDF',label,self.GetObservableName()]))
        fitpdfs.append( (label,pdf) )
    return (datahist,fitpdfs)

def Fit2Comps(self, name):
    self.exfunc=MethodType(extractinfo,self)
    datahist, fitpdfs = self.exfunc() ## refactoring


    data_=self.loadinfos[0]['obj']
    totnum=data_.GetEntries()
    extpdf=CreatePDF_Add(self._workspace, fitpdfs, totnum, 'extpdf')
    for label,pdf in fitpdfs:
        self.SetPDF_Components(label,pdf)

    self.SetPDF_Target(extpdf)
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
'''









if __name__ == '__main__':
    from array import array

    #space=ROOT.RooWorkspace('space',False)
    myspace=RooFitSpaceMgr('space')

    obs='mva'
    fitmgr=RooFitFittingMgr(myspace)


    varhist=fitmgr.LoadObjects(
            filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_data_data_Run2016G_94XReReco_v1.root',
            loadinfo=('data', obs),
            saveANDrenameToworkspace=False
            )
    hfitSources=[]
    hfitSources.append( [ 'mcsig',
            fitmgr.LoadObjects(
                filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
                loadinfo=('mcsig', obs),
                saveANDrenameToworkspace=True
            )
        ] )
    hfitSources.append( [ 'mcbkg',
            fitmgr.LoadObjects(
                filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcbkg_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
                loadinfo=('mcbkg', obs),
                saveANDrenameToworkspace=True
            )
        ] )


    varrange=( varhist.GetXaxis().GetXmin(), varhist.GetXaxis().GetXmax() )

    roobsv=fitmgr._workspace.CreateVar( obs, varrange)
    target=fitmgr._workspace.CreateDataHist( varhist, obs, '_'.join(['datahist','data',obs]) )
    fitmgr.SetFitTarget( target,roobsv )

    fitfrags=[]
    for label,histsource in hfitSources:
        datahist=fitmgr._workspace.CreateDataHist(  histsource, obs, '_'.join(['datahist', label, obs]) )
        histpdf =fitmgr._workspace.CreatePDF_Hist (  datahist,   obs, '_'.join(['histPDF' , label, obs]) )

        yieldvar=fitmgr._workspace.CreateVar_Yield   (  '_'.join(['yield',label,obs]), varhist.GetEntries() )
        yname=yieldvar.GetName()
        extpdf  =fitmgr._workspace.CreatePDF_Extended  (  histpdf.GetName(), yname , '_'.join(['extPDF'  , label, obs]) )
        fitmgr.SetPDF_Components( label, extpdf )
        fitfrags.append(extpdf.GetName())
    totpdf=fitmgr._workspace.CreatePDF_Add( fitfrags, 'totfit')

    fitmgr.SetPDF_Target(totpdf)
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
    canv.SaveAs(FIGTEMPLATE.format(obs))




    logger.debug('writing to root file')
    myspace.Write('ParFitFindYield.{0}.root'.format(obs))

    logger.debug('successfully done')


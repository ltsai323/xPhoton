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

    CreateNum(spaceMGR, num1, totentries/2., 0., totentries)
    CreateNum(spaceMGR, num2, totentries/2., 0., totentries)
    spaceMGR.Factory( factory_addpdf.format(
        name=pdfname,
        num1=num1,
        pdf1=pdf1,
        num2=num2,
        pdf2=pdf2,
        ) )
    return spaceMGR.LoadPdf(pdfname)

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
            #datahist=GetDataHist( self._workspace, hist, label ) # prev ver
            datahist=GetDataHist( self._workspace, hist, self.GetObservableName(), '_'.join(['datahist', 'data', self.GetObservableName()]) )
            #logger.debug( datahist[1].GetName() )
            continue
        print hist.GetName()
        #pdf=CreateHistPDF(self._workspace,hist,label, self.GetObservableName())
        datahist=GetDataHist( self._workspace, hist, self.GetObservableName(), '_'.join(['datahist', label,self.GetObservableName()]) )
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

    #datahist=hist_data[1]
    #self.SetFitTarget( datahist, self._workspace.LoadVar(self.GetObservableName()) ) # need to added outside
    #self.BuildPDFComponent(asdf)
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
    fitmgr.LoadObjects(
            filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
            loadinfo=('mcsig', 'mva'),
            saveANDrenameToworkspace=True
            )
    fitmgr.LoadObjects(
            filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcbkg_Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
            loadinfo=('mcbkg', 'mva'),
            saveANDrenameToworkspace=True
            )

    varrange=( varhist.GetXaxis().GetXmin(), varhist.GetXaxis().GetXmax() )

    roobsv=CreateVar(fitmgr._workspace, obs, varrange)
    target=GetDataHist(fitmgr._workspace, varhist, obs, '_'.join(['datahist','data',obs]) )
    fitmgr.SetFitTarget( target,roobsv )


    fitmgr.exfunc=MethodType(Fit2Comps, fitmgr)
    fitmgr.exfunc(name='test')


    logger.debug('writing to root file')
    myspace.Write('newfile.root')

    logger.debug('successfully done')


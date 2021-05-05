#!/usr/bin/env python2
import ROOT
from types import MethodType
import os
from xPhoton.xPhoton.Managers.LogMgr import GetLogger, LoadLoggerConfig
LoadLoggerConfig('/home/ltsai/local/mylib/data/logger_debug.config')
logger=GetLogger(__name__)
FIGTEMPLATE='storefig/parfit_{0}.png'


from xPhoton.xPhoton.Managers.AdditionalFunctionMgr import ImportAddFunc
from xPhoton.analysis.myfit.RooFitSpaceMgr import RooFitSpaceMgr
from xPhoton.analysis.myfit.RooFitFittingMgr import RooFitFittingMgr
from xPhoton.analysis.myfit.WorkspaceContents import *


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


def SetFittingObserv(fitmgr, name_obs, range_obs):
    roobs=fitmgr._workspace.CreateVar( name_obs, range_obs)
    fitmgr.SetObservable(roobs)
    return roobs
def SetFittingTarget(fitmgr, name_obs, hist_obs):
    target=fitmgr._workspace.CreateDataHist( hist_obs, name_obs, '_'.join(['datahist','data',name_obs]) )
    fitmgr.SetFitTarget(target)
    return target


def ImportFitFragments(fitmgr, hfitSources):
    fitfrags=[]
    obsname_=fitmgr.GetObservableName()
    for label,histsource in hfitSources:
        datahist=fitmgr._workspace.CreateDataHist(  histsource, obsname_, '_'.join(['datahist', label, obsname_]) )
        histpdf =fitmgr._workspace.CreatePDF_Hist(  datahist,   obsname_, '_'.join(['histPDF' , label, obsname_]) )

        yieldvar=fitmgr._workspace.CreateVar_Yield   (  '_'.join(['yield',label,obsname_]), varhist.GetEntries() )
        yname=yieldvar.GetName()
        extpdf  =fitmgr._workspace.CreatePDF_Extended  (  histpdf.GetName(), yname , '_'.join(['extPDF'  , label, obsname_]) )
        fitmgr.SetPDF_Components( label, extpdf )
        fitfrags.append(extpdf.GetName())

    return fitfrags







if __name__ == '__main__':
    from array import array

    myspace=RooFitSpaceMgr('space')

    name_obs='mva'
    fitmgr=RooFitFittingMgr(myspace)


    '''  ##########  loading  ##########  '''
    varhist=fitmgr.LoadObjects(
        filepath='outputParHists_alldata.root',
        loadinfo=('data', name_obs),
        saveANDrenameToworkspace=False
        )
    varrange=( varhist.GetXaxis().GetXmin(), varhist.GetXaxis().GetXmax() )

    hfitSources=[]
    hfitSources.append( [ 'mcsig',
        fitmgr.LoadObjects(
        filepath='outputParHists_sigmc_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
        loadinfo=('mcsig', name_obs),
        saveANDrenameToworkspace=True
        )
        ] )
    hfitSources.append( [ 'mcbkg',
        fitmgr.LoadObjects(
        filepath='outputParHists_bkgmc_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
        loadinfo=('mcbkg', name_obs),
        saveANDrenameToworkspace=True
        )
        ] )


    '''  ###### prepare pdf frags #####  '''
    SetFittingObserv( fitmgr, name_obs, varrange )
    SetFittingTarget( fitmgr, name_obs, varhist  )
    fitfrags=ImportFitFragments(fitmgr,hfitSources)
    totpdf=fitmgr._workspace.CreatePDF_Add( fitfrags, 'totfit')
    fitmgr.SetPDF_Target(totpdf)

    fitmgr.PerformFitting()

    '''  #### basic visulaization  ####  '''
    drawingcontent=fitmgr.CalculateDrawingContent()
    leg=CreateLegend_findObject(
            rooplot=drawingcontent,
            objname_desc_opts=[
                ('data'  , 'data',              'pl'),
                ('totFit', 'total fit',         'l'),
                ('mcsig' , 'sigal photon',      'l'),
                ('mcbkg' , 'background photon', 'l'),
            ],
            title='Components',
            p0=(0.2,0.4), p1=(0.6, 0.85),
            nColumn=1
            )

    canv=ROOT.TCanvas('c1','c1',1000,1000)
    drawingcontent.Draw()
    leg.Draw()
    canv.SaveAs(FIGTEMPLATE.format(name_obs))
    myspace.AdditionalWrite(canv)





    logger.debug('writing to root file')
    myspace.Write('ParFitFindYield.{0}.root'.format(name_obs))

    logger.debug('successfully done')

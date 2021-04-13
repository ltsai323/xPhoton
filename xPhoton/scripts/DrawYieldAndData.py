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

import ROOT
def drawObservable(obs, sigYield, bkgYield):
        spacemgr=RooFitSpaceMgr('drawspace')

        fitmgr=RooFitFittingMgr(spacemgr)
        fitmgr._workspace.CreateVar_const( sigYield.GetName(), sigYield.getVal())
        fitmgr._workspace.CreateVar_const( bkgYield.GetName(), bkgYield.getVal())

        varhist=fitmgr.LoadObjects(
                filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_data_data_Run2016G_94XReReco_v1.root',
                loadinfo=('data', obs),
                saveANDrenameToworkspace=False
                )
        hfitSources=[]
        hfitSources.append( { 'label':'mcsig',
                'obj':fitmgr.LoadObjects(
                    filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
                    loadinfo=('mcsig', obs),
                    saveANDrenameToworkspace=False
                )
            } )
        hfitSources.append( { 'label':'mcbkg',
                'obj':fitmgr.LoadObjects(
                    filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_mcbkg_Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
                    loadinfo=('mcbkg', obs),
                    saveANDrenameToworkspace=False
                )
            } )

        varange=(varhist.GetXaxis().GetXmin(),varhist.GetXaxis().GetXmax())
        roobs=fitmgr._workspace.CreateVar( obs, varange)
        dh_data=fitmgr._workspace.CreateDataHist(varhist,obs, '_'.join(['datahist','data',obs]))
        dh_part=[]
        for hfit in hfitSources:
            datahist=fitmgr._workspace.CreateDataHist(hfit['obj'], obs, '_'.join(['datahist',hfit['label'],obs]))
            histpdf=fitmgr._workspace.CreatePDF_Hist( datahist,obs, '_'.join(['histPdf',hfit['label'],obs]))
            extpdf=fitmgr._workspace.CreatePDF_Extended( histpdf.GetName(), sigYield.GetName(), '_'.join(['extpdf',hfit['label'],obs]))
            hfit.update( {'datahist':datahist, 'histpdf':histpdf, 'extpdf':extpdf} )
        print hfitSources

        totpdf=fitmgr._workspace.CreatePDF_Add( [hfit.get('extpdf').GetName() for hfit in hfitSources], 'totfit')

        frame=roobs.frame()
        dh_data.plotOn(frame)
        totpdf.plotOn(frame, ROOT.RooFit.LineColor(2), ROOT.RooFit.LineWidth(4))
        #hfitSources[0]['extpdf'].plotOn(frame, ROOT.RooFit.LineColor(4), ROOT.RooFit.LineWidth(4))
        #hfitSources[0]['extpdf'].plotOn(frame, ROOT.RooFit.LineColor(4), ROOT.RooFit.LineWidth(4))
        totpdf.plotOn(frame, ROOT.RooFit.LineColor(6), ROOT.RooFit.LineWidth(4),ROOT.RooFit.Components(hfitSources[0]['extpdf'].GetName()))
        totpdf.plotOn(frame, ROOT.RooFit.LineColor(7), ROOT.RooFit.LineWidth(4),ROOT.RooFit.Components(hfitSources[1]['extpdf'].GetName()))

        canv=ROOT.TCanvas('c1','',1000,1000)
        frame.Draw()
        canv.SaveAs(FIGTEMPLATE.format(obs))
if __name__ == '__main__':
    loadspacemgr=RooFitSpaceMgr('space','ParFitFindYield.mva.root')

    sigYield=loadspacemgr.LoadVar('yield_mcsig_mva')
    bkgYield=loadspacemgr.LoadVar('yield_mcbkg_mva')

    obss=['mva','pt','r9', 'HoverE', 'MET_pt', 'SCeta', 'SCetaWidth', 'chIsoRaw', 'eta', 'phi', 'phoIsoRaw', 'rawE', 'rho', 'sieieFull5x5','sieipFull5x5']
    for obs in obss:
        drawObservable(obs, sigYield, bkgYield)





    print 'done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'




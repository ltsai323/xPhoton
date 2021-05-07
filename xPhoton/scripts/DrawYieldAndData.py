#!/usr/bin/env python2
import ROOT
from types import MethodType
import os
from xPhoton.xPhoton.Managers.LogMgr import GetLogger, LoadLoggerConfig
LoadLoggerConfig('/home/ltsai/local/mylib/data/logger_debug.config')
logger=GetLogger(__name__)
FIGTEMPLATE='parfit_{0}.png'


from xPhoton.xPhoton.Managers.AdditionalFunctionMgr import ImportAddFunc
from xPhoton.analysis.myfit.RooFitSpaceMgr import RooFitSpaceMgr
from xPhoton.analysis.myfit.RooFitFittingMgr import RooFitFittingMgr
from xPhoton.analysis.myfit.WorkspaceContents import *

import ROOT

class UpDnPadMgr(object):
    def __init__(self, yaxisSeparator=0.3,margin=0.05):
        self._marginwidth=margin
        self._yseparator=yaxisSeparator
        if margin>0.5 or margin <0:
            raise Exception('Wait, wait, wait !!! The margin is too big! Keep margin in [0,0.5]')
        self._row=2

        self._pads=[
                ROOT.TPad('padUp','padUp',0., yaxisSeparator+margin, 1., 1.),
                ROOT.TPad('padDn','padDn',0., 0., 1., yaxisSeparator-margin)
                ]
        self._uppercontent=[]
        self._lowercontent=[]
        self._upperdrawopt=[]
        self._lowerdrawopt=[]
    def __del__(self):
        pass
    def gotoPad(self, num):
        self._pads[num].cd()
    def SetUpperContent(self, obj, drawOpt=''):
        self._uppercontent.append(obj)
        self._upperdrawopt.append(drawOpt)
    def SetLowerContent(self, obj, drawOpt=''):
        self._lowercontent.append(obj)
        self._lowerdrawopt.append(drawOpt)
    def PlotOn(self, canv):
        self.gotoPad(0)
        for obj,opt in zip(self._uppercontent,self._upperdrawopt):
            obj.Draw(opt)
        self.gotoPad(1)
        for obj,opt in zip(self._lowercontent,self._lowerdrawopt):
            obj.Draw(opt)

        canv.cd()
        self._pads[0].Draw()
        self._pads[1].Draw()


    def SetFilling(self, **kwargs):
        if 'style' in kwargs:
            self._pads[0].SetFillStyle(kwargs['style'])
            self._pads[1].SetFillStyle(kwargs['style'])
        if 'color' in kwargs:
            self._pads[0].SetFillColor(kwargs['color'])
            self._pads[1].SetFillColor(kwargs['color'])




def drawObservable(obs, sigYield, bkgYield):
        spacemgr=RooFitSpaceMgr('drawspace')

        fitmgr=RooFitFittingMgr(spacemgr)
        fitmgr._workspace.CreateVar_const( sigYield.GetName(), sigYield.getVal())
        fitmgr._workspace.CreateVar_const( bkgYield.GetName(), bkgYield.getVal())

        varhist=fitmgr.LoadObjects(
                filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_alldata.root',
                loadinfo=('data', obs),
                saveANDrenameToworkspace=False
                )
        hfitSources=[]
        hfitSources.append( { 'label':'mcsig',
                'obj':fitmgr.LoadObjects(
                    filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_sigmc_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
                    loadinfo=('mcsig', obs),
                    saveANDrenameToworkspace=False
                )
            } )
        hfitSources.append( { 'label':'mcbkg',
                'obj':fitmgr.LoadObjects(
                    filepath='/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists/outputParHists_bkgmc_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
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
        padmgr=UpDnPadMgr(0.4,0.05)
        padmgr.SetUpperContent(frame)
        padmgr.PlotOn(canv)


        canv.SaveAs(FIGTEMPLATE.format(obs))



if __name__ == '__main__':
    loadspacemgr=RooFitSpaceMgr('space','ParFitFindYield.mva.root')

    sigYield=loadspacemgr.LoadVar('yield_mcsig_mva')
    bkgYield=loadspacemgr.LoadVar('yield_mcbkg_mva')

    #obss=['mva','pt','r9', 'HoverE', 'MET_pt', 'SCeta', 'SCetaWidth', 'chIsoRaw', 'eta', 'phi', 'phoIsoRaw', 'rawE', 'rho', 'sieieFull5x5','sieipFull5x5']
    obss=['mva','pt']
    for obs in obss:
        drawObservable(obs, sigYield, bkgYield)





    print 'done!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!'




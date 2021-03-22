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



if __name__ == '__main__':
    from array import array

    space=ROOT.RooWorkspace('space',False)
    myspace=RooFitSpaceMgr(space)

    var='r9'
    inputinfo=[
    ('data' , '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists_data_Run2016G.root'),
    ('mcbkg', '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists_mcbkg_Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
    ('mcsig', '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
    ]
    inputfile=[ ROOT.TFile.Open(p) for t,p in inputinfo ]
    inputhist=[ f.Get(var) for f in inputfile ]

    CreateVar( myspace, var, inputhist[0].GetXaxis().GetXmin(), inputhist[0].GetXaxis().GetXmax() )

    creategaussianpdf(myspace)
    for (label,p), hist in zip(inputinfo,inputhist):
        if label=='data': continue
        CreateHistPDF( myspace, hist, label )
        #factorycreatehistpdf( myspace, hist, label )

    totnum=inputhist[0].GetEntries()
    CreateNum(myspace, 'numsig', totnum/2., 0., totnum)
    CreateNum(myspace, 'numbkg', totnum/2., 0., totnum)
    Create



    logger.debug('writing to root file')
    myspace.Write('newfile.root')
    for ifile in inputfile:
        ifile.Close()
        logger.debug(ifile.GetName() + ' is closed')

    logger.debug('successfully done')


#!/usr/bin/env python2
summaryfile='../data/summaryJson/summary_sigMC_madgraph.json'
madgraphfilelist=[
'updated/GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root',
'updated/GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root',
'updated/GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root',
'updated/GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root',
'updated/GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8.root',
        ]
import os
from xPhoton.xPhoton.AppendEventInfo import FindXSInfo, nodir, ShowPD, ShowDetail
from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger

newdir='SFcalced'
def executeCommand( inputfile ):
    execfile='./exe.AppendBTagCalibration'
    os.system( '%s %s %s/%s' %( execfile, inputfile, newdir, nodir(inputfile) ) )

if __name__ == '__main__':
    InitLogger(level='info')
    mylog=GetLogger(__name__)
    if not os.path.exists(newdir) or not os.path.isdir(newdir): os.mkdir(newdir)

    ShowPD(summaryfile)
    ShowDetail(summaryfile)
    version=''
    for rootfile in madgraphfilelist:
            executeCommand( rootfile )

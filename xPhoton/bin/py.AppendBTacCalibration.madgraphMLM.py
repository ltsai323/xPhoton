#!/usr/bin/env python2
summaryfile='../data/summaryJson/summary_sigMC_madgraph.json'
madgraphfilelist=[
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
        ]
import os
from xPhoton.xPhoton.AppendEventInfo import FindXSInfo, nodir, ShowPD, ShowDetail
from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger

def executeCommand( inputfile ):
    execfile='./exe.AppendBTagCalibration'
    os.system( '%s %s updated/%s' %( execfile, inputfile, nodir(inputfile) ) )

if __name__ == '__main__':
    InitLogger(level='info')
    mylog=GetLogger(__name__)
    newdir='updated'
    if not os.path.exists(newdir) or not os.path.isdir(newdir): os.mkdir(newdir)

    ShowPD(summaryfile)
    ShowDetail(summaryfile)
    version=''
    for rootfile in madgraphfilelist:
            executeCommand( rootfile )

#!/usr/bin/env python2
#arg_summaryfile='../data/summaryJson/summary_UL18MadgraphMLM.json'
arg_summaryfile='../data/summaryJson/summary_UL18Pythia.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDMadgraphMLM.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDPythia.json'

arg_dataera=2018
arg_isQCD=False

fDict={
  "GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8": {
    "v11_L1v1-v1":
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/UL18/sigPythia/AllPhotonSample/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root'
    },

  "GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8": {
    "v11_L1v1-v2":
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/UL18/sigPythia/AllPhotonSample/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root'
    },

  "GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8": {
    "v11_L1v1-v2":
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/UL18/sigPythia/AllPhotonSample/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root'
    },
}

if __name__ == '__main__':
    from AppendEventInfoPythonHelper import *
    from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger
    InitLogger(level='warning')
    mylog=GetLogger(__name__)
    CheckWorkingDir()

    targetDict=fDict
    integratedgenweights = { pd:sum( [IntegratedGenWeights(fpath) for ver,fpath in info.iteritems()] )
            for pd, info in targetDict.iteritems() }

    for pd, info in targetDict.iteritems():
        for ver, rootfile in info.iteritems():
            print rootfile
            xs=GetXS(pd, ver, arg_summaryfile)
            executeCommandToTmp( xs, integratedgenweights[pd], arg_dataera, arg_isQCD, rootfile )
        MergeOutputs(pd, info)

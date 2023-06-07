#!/usr/bin/env python3
#arg_summaryfile='../data/summaryJson/summary_UL18MadgraphMLM.json'
#arg_summaryfile='../data/summaryJson/summary_UL18Pythia.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDMadgraphMLM.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDPythia.json'
arg_summaryfile='../data/summaryJson/summary_UL16PostVFP_GJetPythia.json'
#arg_summaryfile='../data/summaryJson/summary_UL16PreVFP_GJetPythia.json'

arg_dataera='UL2016PostVFP'
arg_isQCD=False

fDict={
  "GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8": {
    "v17-v6":
'/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/step0.xphoton/UL16Post_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root',
  },
  "GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8": {
    "v13-v3":
'/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/step0.xphoton/UL16Post_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root',
  },
  "GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8": {
    "v17-v4":
'/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/step0.xphoton/UL16Post_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root',
  }
}



if __name__ == '__main__':
    from AppendEventInfoPythonHelper import *
    from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger
    InitLogger(level='warning')
    mylog=GetLogger(__name__)
    CheckWorkingDir()

    targetDict=fDict
    integratedgenweights = { pd:sum( [IntegratedGenWeights(fpath) for ver,fpath in info.items()] )
            for pd, info in targetDict.items() }

    for pd, info in targetDict.items():
        for ver, rootfile in info.items():
            xs=GetXS(pd, ver, arg_summaryfile)
            executeCommandToTmp( xs, integratedgenweights[pd], arg_dataera, arg_isQCD, rootfile )
        MergeOutputs(pd, info)

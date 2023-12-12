#!/usr/bin/env python3
#arg_summaryfile='../data/summaryJson/summary_UL18MadgraphMLM.json'
#arg_summaryfile='../data/summaryJson/summary_UL18Pythia.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDMadgraphMLM.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDPythia.json'
#jarg_summaryfile='../data/summaryJson/summary_UL16PostVFP_GJetPythia.json'
arg_summaryfile='../data/summaryJson/summary_UL16PostVFP_GJetMadgraph.json'

arg_dataera='UL2016PostVFP'
arg_isQCD=False

fDict={
  "GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
  },
  "GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
  },
  "GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
  },
  "GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
  },
  "GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
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

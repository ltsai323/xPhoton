#!/usr/bin/env python2
arg_summaryfile='../data/summaryJson/summary_UL18MadgraphMLM.json'
#arg_summaryfile='../data/summaryJson/summary_UL18Pythia.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDMadgraphMLM.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDPythia.json'

arg_dataera=2018
arg_isQCD=False

fDict={
  "GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v1":
'../test/storeroot/UL18/sigMadgraph/GJets_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8.root',
    },

  "GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v1":
'../test/storeroot/UL18/sigMadgraph/GJets_HT-600ToInf_TuneCP5_13TeV-madgraphMLM-pythia8.root',
    },

  "GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v1":
'../test/storeroot/UL18/sigMadgraph/GJets_HT-40To100_TuneCP5_13TeV-madgraphMLM-pythia8.root',
    },

  "GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v1":
'../test/storeroot/UL18/sigMadgraph/GJets_HT-100To200_TuneCP5_13TeV-madgraphMLM-pythia8.root',
    },

  "GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v1":
'../test/storeroot/UL18/sigMadgraph/GJets_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8.root',
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

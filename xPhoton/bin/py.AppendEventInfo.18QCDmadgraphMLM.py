#!/usr/bin/env python2
arg_summaryfile='../data/summaryJson/summary_18QCDMadgraph.json'
arg_dataera=2018
arg_isQCD=True

fDict={
  "QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT100to200_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
  "QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT200to300_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
  "QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT2000toInf_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
  "QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT1000to1500_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
  "QCD_HT50to100_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT50to100_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT50to100_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
  "QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT1500to2000_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
  "QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT700to1000_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
  "QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT500to700_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
  "QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1": 
"../test/QCD18/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8.root",

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

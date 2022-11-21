#!/usr/bin/env python2
arg_summaryfile='../data/summaryJson/summary_bkgMC_madgraph.json'
arg_Reweig_file='../data/Reweighing/GenHT_QCDMadgraphMLM/AppendEventInfoPythonHelper.json'
arg_dataera=2016
arg_isQCD=True
# modified at 221116. PtHat signal > PtHat PU cut selected.

fDict={
  "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root",
    "v3_ext1-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root",
  },
  "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root",
    "v3_ext1-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root",
  },
  "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root",
    "v3_ext1-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root",
  },
  "QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v1":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v1.root",
  },
  "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root",
    "v3_ext1-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root",
  },
  "QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root",
  },
  "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root",
    "v3_ext1-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root",
  },
  "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root",
    "v3_ext1-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root",
  },
  "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    "v3-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root",
    "v3_ext1-v2":
"/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root",
  }
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
            weightfile=FindWeightFile(pd, arg_Reweig_file)
            executeCommandToTmp( xs, integratedgenweights[pd], arg_dataera, arg_isQCD, rootfile, weightfile )
        MergeOutputs(pd, info)

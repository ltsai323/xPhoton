#!/usr/bin/env python2
arg_summaryfile='../data/summaryJson/summary_bkgMC_madgraph.json'
arg_dataera=2016
arg_isQCD=True

fDict={
  "QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT50to100.root',
  "QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT100to200.root',
  "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT200to300.root',
  "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT300to500.root',
  "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT500to700.root',
  "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT700to1000.root',
  "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT1000to1500.root',
  "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT1500to2000.root',
  "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":
'/home/ltsai/Work/github/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhover1.addPUptHAT/QCDHT2000toInf.root',
}
wFile={
  "QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

  "QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

  "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

  "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

  "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

  "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

  "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

  "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

  "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8":

        }


if __name__ == '__main__':
    from AppendEventInfoPythonHelper import *
    from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger
    InitLogger(level='warning')
    mylog=GetLogger(__name__)
    CheckWorkingDir()

    targetDict=fDict
    integratedgenweights = { pd:IntegratedGenWeights(fpath) for pd, fpath in targetDict.iteritems() }

    for pd, info in targetDict.iteritems():
        for ver, rootfile in info.iteritems():
            print rootfile
            xs=GetXS(pd, ver, arg_summaryfile)
            executeCommandToTmp( xs, integratedgenweights[pd], arg_dataera, arg_isQCD, rootfile )
        MergeOutputs(pd, info)

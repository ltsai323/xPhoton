#!/usr/bin/env python2
#arg_summaryfile='../data/summaryJson/summary_UL18MadgraphMLM.json'
#arg_summaryfile='../data/summaryJson/summary_UL18Pythia.json'
#arg_summaryfile='../data/summaryJson/summary_UL18QCDMadgraphMLM.json'
arg_summaryfile='../data/summaryJson/summary_UL18QCDPythia.json'

arg_dataera=2018
arg_isQCD=True

fDict={
  "QCD_Pt_170to300_TuneCP5_13TeV_pythia8": {
    "v11_L1v1_ext1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_170to300_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_600to800_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_600to800_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_2400to3200_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_50to80_TuneCP5_13TeV_pythia8": {
    "v11_L1v1_ext1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_50to80_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_1000to1400_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_80to120_TuneCP5_13TeV_pythia8": {
    "v11_L1v1_ext1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_80to120_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_1800to2400_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_3200toInf_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_30to50_TuneCP5_13TeV_pythia8": {
    "v11_L1v1_ext1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_30to50_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_300to470_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_300to470_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_800to1000_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_800to1000_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_1400to1800_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_15to30_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_15to30_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_120to170_TuneCP5_13TeV_pythia8": {
    "v11_L1v1_ext1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_120to170_TuneCP5_13TeV_pythia8.root",
    },

  "QCD_Pt_470to600_TuneCP5_13TeV_pythia8": {
    "v11_L1v1-v2":
"../test/storeroot/UL18/QCDPythia/QCD_Pt_470to600_TuneCP5_13TeV_pythia8.root",
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

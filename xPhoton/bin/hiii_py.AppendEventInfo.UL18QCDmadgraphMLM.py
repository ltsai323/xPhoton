#!/usr/bin/env python2
arg_summaryfile='../data/summaryJson/summary_UL18QCDMadgraphMLM.json'
arg_Reweig_file=''
arg_dataera=2018
arg_isQCD=True

fDict={
  "QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},

  "QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},

  "QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},

  "QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},

  "QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1_ext1-v1":
'/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8_ext1v1.root',

    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},

  "QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},

  "QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},

  "QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},

  "QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v11_L1v1-v2":
"../scripts/RUNbkgSumbit/bkgRunning/xPhoton.UL18QCDMadgraphMLM/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root"},
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
            #weightfile=FindWeightFile(pd, arg_Reweig_file)
            #executeCommandToTmp( xs, integratedgenweights[pd], arg_dataera, arg_isQCD, rootfile, weightfile )
            executeCommandToTmp( xs, integratedgenweights[pd], arg_dataera, arg_isQCD, rootfile )
        MergeOutputs(pd, info)

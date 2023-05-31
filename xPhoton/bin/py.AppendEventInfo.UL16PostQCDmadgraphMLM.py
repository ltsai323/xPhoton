#!/usr/bin/env python3
arg_summaryfile='../data/summaryJson/summary_UL16PostVFP_QCDMadgraph.json'
arg_Reweig_file='../data/Reweighing/GenHT_QCDMadgraphMLM/AppendEventInfoPythonHelper.json' ## old 2016 rereco infomation
arg_dataera=2016
arg_isQCD=True

fDict={
  "QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
  }, 
  "QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
  }, 
  "QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
  }, 
  "QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
  }, 
  "QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
  }, 
  "QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
  }, 
  "QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
  }, 
  "QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
  }, 
  "QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8": {
    "v17-v1":
    '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.0th/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
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
            print(rootfile)
            xs=GetXS(pd, ver, arg_summaryfile)
            #weightfile=FindWeightFile(pd, arg_Reweig_file)
            executeCommand( xs, integratedgenweights[pd], arg_dataera, arg_isQCD, rootfile )
        MergeOutputs(pd, info)


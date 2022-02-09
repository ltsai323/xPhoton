#!/usr/bin/env python2
arg_summaryfile='../data/summaryJson/summary_bkgMC_pythia.json'
arg_dataera=2016
arg_isQCD=True

fDict={
  "QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v1":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3v1.root',
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
  },
  "QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v1":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v1.root',
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
    "v3-v2_backup":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8": {
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_15to30_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_15to6500_FwdEnriched_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_15to6500_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8": {
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8": {
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-ext1-v2.root',
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8": {
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8v3_ext1-v2.root',
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8": {
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_30to50_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_3200toInf_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
    "v3-v2_backup":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2_backup.root',
  },
  "QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_50to80_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
  },
  "QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
    "v3-v2_backup":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2_backup.root',
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
  },
  "QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
    "v3_ext1-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
  },
  "QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8": {
    "v3-v1":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3-v1.root',
    "v3_ext2-v2":
    '/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/pythia_qcd/crab_bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3_ext2-v2.root',
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

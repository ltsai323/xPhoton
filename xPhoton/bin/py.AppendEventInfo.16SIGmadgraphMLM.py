#!/usr/bin/env python2
arg_summaryfile='../data/summaryJson/summary_sigMC_madgraph.json'
arg_dataera=2016
arg_isQCD=False
fDict={
  "GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  }
}

if __name__ == '__main__':
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

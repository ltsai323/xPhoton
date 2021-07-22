#!/usr/bin/env python2
summaryfile='../data/summaryJson/summary_sigMC_madgraph.json'
fileDict={
  "GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  }
}
processedDict={
  "GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  }
}
testDict={
  "GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
  'v3-v2'      :'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
  'v3_ext1-v2' :'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  }
}
import os
from xPhoton.xPhoton.AppendEventInfo import FindXSInfo, nodir, ShowPD, ShowDetail
from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger
mylog=GetLogger(__name__)

#from xPhoton.xPhoton.AppendEventInfo_IntegratedGenWeights import IntegratedGenWeights
import ROOT
def IntegratedGenWeights(filename):
    f=ROOT.TFile.Open(filename)
    nt=f.Get('genweightsummary')

    Sum=0
    for a in nt:
        Sum+=a.sumupgenweight
    return Sum

def MergeNeeded( filedict ):
    if len( filedict.keys() ) > 1:
        return True
    return False


def MergeOutputs( primarydataset, inputlist ):
    inputfiles=[ fpath for ver, fpath in inputlist.iteritems() ]
    if len(inputfiles) == 1:
        os.system('mv tmp/%s updated/%s.root' % nodir(inputfiles[0]), primarydataset )
    elif len(inputfiles) > 1:
        os.system('hadd -f updated/%s.root %s' % (primarydataset, ' '.join( ['tmp/'+ nodir(fpath) for fpath in inputfiles] )))
    else:
        mylog.warning('nothing found in category %s' % primarydataset)

def executeCommandToTmp( xsweight_, integratedGenWeight_, inputfile_ ):
    execfile='./exe.AppendEventInfo'
    os.system( '%s %.10f %f %s tmp/%s' %( execfile, xsweight_, integratedGenWeight_, inputfile_, nodir(inputfile_) ) )

if __name__ == '__main__':
    InitLogger(level='info')
    mylog=GetLogger(__name__)
    newdir='updated'
    if not os.path.exists(newdir) or not os.path.isdir(newdir): os.mkdir(newdir)
    if not os.path.exists('tmp') or not os.path.isdir('tmp'): os.mkdir('tmp')

    ShowPD(summaryfile)
    ShowDetail(summaryfile)
    version=''

    targetDict=processedDict
    #targetDict=testDict
    integratedgenweights = { pd:sum( [IntegratedGenWeights(fpath) for ver,fpath in info.iteritems()] )
            for pd, info in targetDict.iteritems() }

    for pd, info in targetDict.iteritems():
        for ver, rootfile in info.iteritems():
            xs,xserr,xsunit=FindXSInfo(pd,ver,summaryfile)
            if   xsunit=='pb':
                xs *= 1000.
            elif xsunit=='fb':
                pass
            else :
                mylog.error( 'recorded Xsection in "%s" unit in file %s. Which is not "pb" or "fb". Need to convert it manually!' % (xsunit, summaryfile) )
            #print xs
            executeCommandToTmp( xs, integratedgenweights[pd], rootfile )
        MergeOutputs(pd, info)

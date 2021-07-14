#!/usr/bin/env python2
summaryfile='../data/summaryJson/summary_sigMC_madgraph.json'
fileDict={
  "GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
#    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
#    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
#    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root',
#    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
#    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root',
#    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
#    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root',
#    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  },
  "GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
#    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
#    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/origfiles/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
  }
}
testDict={
  "GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
    }
  }
import os
from xPhoton.xPhoton.AppendEventInfo import FindXSInfo, nodir, ShowPD, ShowDetail
from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger

def executeCommand( xsweight, inputfile ):
    execfile='./exe.AppendEventInfo'
    os.system( '%s %.10f %s updated/%s' %( execfile, xsweight, inputfile, nodir(inputfile) ) )

if __name__ == '__main__':
    InitLogger(level='info')
    mylog=GetLogger(__name__)
    newdir='updated'
    if not os.path.exists(newdir) or not os.path.isdir(newdir): os.mkdir(newdir)
    ShowPD(summaryfile)
    ShowDetail(summaryfile)
    version=''
    for pd, info in fileDict.iteritems():
    #for pd, info in testDict.iteritems():
        for ver, rootfile in info.iteritems():
            xs,xserr,xsunit=FindXSInfo(pd,ver,summaryfile)
            if   xsunit=='pb':
                xs *= 1000.
            elif xsunit=='fb':
                pass
            else :
                mylog.error( 'recorded Xsection in "%s" unit in file %s. Which is not "pb" or "fb". Need to convert it manually!' % (xsunit, summaryfile) )
            #print xs
            executeCommand( xs, rootfile )

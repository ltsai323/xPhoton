#!/usr/bin/env python2
fileList=[
{'pd':'GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'path':'hi.root'}
]

summaryfile='../data/mcInformation/summary_sigMC_madgraph.json'
import os
from xPhoton.xPhoton.AppendEventInfo import GetXS, nodir, ShowPD, ShowDetail
if __name__ == '__main__':
    newdir='updated'
    if not os.path.exists(newdir) or not os.path.isdir(newdir):
        os.mkdir(newdir)
    ShowPD(summaryfile)
    ShowDetail(summaryfile)
    '''
    for fileinfo in fileList:
        os.system('echo ./exe.AppendXSWeightToxPhoton %.10f %s %s/%s' %(
            GetXS(fileinfo['pd'], SummaryFile=summaryfile),
            fileinfo['path'],
            newdir, nodir(fileinfo['path']) ))
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root'},
{'pd':  , 'path':/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root'},
'''
'GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'
'GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8'

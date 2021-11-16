#!/usr/bin/env python2
summaryfile='../data/summaryJson/summary_sigMC_madgraph.json'
workingpath='step1.xsinfoAppended'
destinypath='step2.mergePDversion'
datalumi={ 2016: 35.9, 2017:20, 2018:30 }
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
testDict={
  "GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8": {
    'v3-v2'     :
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
    'v3_ext1-v2':
'/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test/storeroot/madgraph_sigMC/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
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
    movecommand='mv {oldfolder}/%s {newfolder}/%s.root'.format(oldfolder=workingpath,newfolder=destinypath)
    haddcommand='hadd -f {newfolder}/%s.root %s'.format(newfolder=destinypath)
    print haddcommand % (primarydataset, ' '.join( [ workingpath+'/'+ nodir(fpath) for fpath in inputfiles] ))
    if len(inputfiles) == 1:
        os.system( movecommand % (nodir(inputfiles[0]), primarydataset) )
    elif len(inputfiles) > 1:
        os.system( haddcommand % (primarydataset, ' '.join( [ workingpath+'/'+ nodir(fpath) for fpath in inputfiles] )))
    else:
        mylog.warning('nothing found in category %s' % primarydataset)

def executeCommandToTmp( xsweight_, integratedGenWeight_, inputfile_ ):
    execfile='./exe.AppendEventInfo'
    execcommand='%s {xs:.10e} {integratedGenWeight:.2e} {integratedLuminosity:.3e} {inputfile} %s/{outputfile} ' % (execfile,workingpath)
    #execcommand='{exefile %.10f %f %s {outfolder}/%s'.format(exefile=execfile, outfolder=oldfolder)
    #os.system( '%s %.10f %f %s tmp/%s' %( xsweight_, integratedGenWeight_, inputfile_, nodir(inputfile_) ) )
    print inputfile_
    print nodir(inputfile_)
    print type(xsweight_)
    print type(integratedGenWeight_)
    print type(datalumi[2016])
    print type(inputfile_)
    print type(nodir(inputfile_))
    execcommand.format(
        xs=xsweight_,
        integratedGenWeight=integratedGenWeight_,
        integratedLuminosity=datalumi[2016],
        inputfile=inputfile_,
        outputfile=nodir(inputfile_)
    )
    os.system( execcommand.format(
        xs=xsweight_,
        integratedGenWeight=integratedGenWeight_,
        integratedLuminosity=datalumi[2016],
        inputfile=inputfile_,
        outputfile=nodir(inputfile_)
    ) )

if __name__ == '__main__':
    InitLogger(level='info')
    mylog=GetLogger(__name__)
    if not os.path.exists(workingpath) or not os.path.isdir(workingpath): os.mkdir(workingpath)
    if not os.path.exists(destinypath) or not os.path.isdir(destinypath): os.mkdir(destinypath)

    ShowPD(summaryfile)
    ShowDetail(summaryfile)
    version=''

    targetDict=fDict
    #targetDict=testDict
    integratedgenweights = { pd:sum( [IntegratedGenWeights(fpath) for ver,fpath in info.iteritems()] )
            for pd, info in targetDict.iteritems() }

    for pd, info in targetDict.iteritems():
        for ver, rootfile in info.iteritems():
            xs,xserr,xsunit=FindXSInfo(pd,ver,summaryfile)
            if   xsunit=='pb': xs *= 1000.
            elif xsunit=='fb': pass
            else :             mylog.error( 'recorded Xsection in "%s" unit in file %s. Which is not "pb" or "fb". Need to convert it manually!' % (xsunit, summaryfile) )
            executeCommandToTmp( xs, integratedgenweights[pd], rootfile )
        MergeOutputs(pd, info)


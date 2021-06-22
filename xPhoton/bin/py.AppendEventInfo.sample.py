fileList=[
{'pd':'GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'path':'hi.root'}
]

summaryfile='../data/mcInformation/summary_sigMC_amcatnlo.json'
import os
from xPhoton.xPhoton.AppendEventInfo import GetXS, nodir
if __name__ == '__main__':
    newdir='updated'
    if not os.path.exists(newdir) or not os.path.isdir(newdir):
        os.mkdir(newdir)
    ShowPD(summaryfile)
    '''
    for fileinfo in fileList:
        os.system('echo ./exe.AppendXSWeightToxPhoton %.10f %s %s/%s' %(
            GetXS(fileinfo['pd'], SummaryFile=summaryfile),
            fileinfo['path'],
            newdir, nodir(fileinfo['path']) ))
    '''

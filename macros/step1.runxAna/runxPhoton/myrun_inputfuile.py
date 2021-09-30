#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import commands

# usage :
#    ./this.py filepath.txt

# my new code
lines=[
#'root://se01.grid.nchc.org.tw//cms/store/user/ltsai/ggAnalysis/2016miniAODv3/jetSubVtxInfo/SinglePhoton/crab_UL2016RunH_wrongConfigs/210209_210824/0001/ggtree_data_1187.root',
'root://se01.grid.nchc.org.tw//cms/store/user/ltsai/ggAnalysis/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic__TuneCUETP8M1_13TeV_Pythia8/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8/crab_GJet_Pt20toInf_DoubleEMEnriched_MGG40to80/210226_095031/0000/ggtree_mc_151.root'
]

#commandCONTENT  = 'root -b -q xPhoton/macros/run.C\(\\\"%s\\\",%d\)'
commandCONTENT  = 'sh runxPhoton/myrun_singlefile.sh %s %d' # second argument is useless
nchcPrefix='root://se01.grid.nchc.org.tw/'
def fileID(rootpath): return int(rootpath.split('_')[-1].split('.')[0])
def nameonly(fullfilepath): return fullfilepath.strip().split('/')[-1].split('.')[0]
def cleanworkspace():
    if os.path.isfile('output_job_PhotonHFJet_1.root'):
        print 'cleaning temporary files'
        os.system('/bin/rm output_job_PhotonHFJet*.root')
    else:
        print 'You have a clean workspace'
def checkarg(inputArg):
    if len(inputArg) > 1:
        return inputArg[1]
    return None

def showfile( filepath ): print '----- At file : %s' % (filepath)
def execCommand(path, isRemote=False):
    fullpath = nchcPrefix + path if isRemote else path
    stripath = fullpath.strip()
    cmdStr=commandCONTENT % ( stripath, fileID(path) )
    #print cmdStr
    status, content = commands.getstatusoutput(cmdStr)
    if status:
        showfile( stripath )
        #print content
        raise RuntimeError(content)
    else:
        currentstat=open('running.log','w')
        currentstat.write(content)
        currentstat.close()
def nlines(filepath): return sum( 1 for line in open(filepath,'r') )


if __name__ == '__main__':
    filename = checkarg(argv)
    if filename:
        with open(filename, 'r') as ifile:
            tot=nlines(filename)
            for i, remoteDir in enumerate( ifile.readlines() ):
                if i%100 == 0: print '-- %d th / %d -- file processed' % (i, tot)
                execCommand( remoteDir, True )
        os.system('hadd storeroot/%s.root output*.root' % (nameonly(filename)) )
        cleanworkspace()
    else:
        for rootFile in lines:
            execCommand( rootFile )

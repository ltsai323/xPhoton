#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser
from xPhoton.xPhoton.Managers.ExecuteMgr import ExecMgr, FileNameConverter
from xPhoton.xPhoton.Managers import LogMgr

import os
import commands

# usage :
#    ./this.py filepath.txt
#    ./this.py filepath.txt path.txt
prefix_nchc='root://se01.grid.nchc.org.tw/'
prefix_local=''

exeFile='/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/bin/exe.xPhotonRunner'

bashcommand='xrdcp -f %s running.root && {exefile} running.root %d'.format(exefile=exeFile) # download file first
fileprefix=prefix_nchc
'''
bashcommand='{exefile} %s %d'.format(exefile=exeFile)
fileprefix=prefix_local
'''

#bashcommand='exec_xPhotonRunner %s %d'


def checkarg(inputArg):
    if len(inputArg) < 2:               raise IOError('Input a text path!')
    if '.root' == inputArg[1][-5:]:     raise IOError('Wrong input : root file is not supported')
    if not os.path.isfile(inputArg[1]): raise IOError('input file not found')
def InputFileName(inputArg):
    return inputArg[1]
def CleanOutputs(inputArg):
    if len(inputArg) > 2:
        stat=inputArg[2].lower()
        if stat == 'false' or stat == 'true': return True if stat=='true' else False
        raise IOError('second argument only accepts true or false')
    return False


def ExecSample(execmgr, pathmgr):
    print 'no input file detected. Use internal example'
    # my new code
    lines=[
'/cms/store/user/ltsai/ggAnalysis/2016miniAODv3/jetSubVtxInfo/SinglePhoton/crab_data_Run2016B_94XReReco_ver2v1/210308_080300/0000/ggtree_data_1.root',
        #'~/ReceivedFile/GJet/test/ggtree_datasample.root'
    ]
    for rootFile in lines:
        execmgr.execCommand( pathmgr.GetPath(rootFile),pathmgr.GetFileID(rootFile) )
def ExecByInputPath(execmgr,pathmgr, textpath):
    print 'input file used : ' + textpath
    with open(textpath, 'r') as ifile:
        tot=sum( 1 for line in open(textpath, 'r') )
        for i, remoteDir in enumerate( ifile.readlines() ):
            if i%100 == 0: print '-- %d th / %d -- file processed' % (i, tot)
            mylog.debug(' orig file : %s' % remoteDir )
            fullpath=pathcontroller.GetPath(remoteDir)
            fileid=pathcontroller.GetFileID(remoteDir)
            cmd.execCommand( fullpath, fileid )


if __name__ == '__main__':
    LogMgr.InitLogger(level='warning')
    mylog=LogMgr.GetLogger(__name__)

    checkarg(argv)
    txtpath=InputFileName(argv)
    needToClean=CleanOutputs(argv)

    cmd=ExecMgr()
    cmd.SetGeneralCommand(bashcommand)
    pathcontroller=FileNameConverter(fileprefix)

    if txtpath:
        ExecByInputPath(cmd, pathcontroller, txtpath)
    else:
        ExecSample(cmd, pathcontroller)

    if needToClean:
        os.system('hadd %s.root output_job_PhotonHLJet*.root' % (FileNameConverter.ExtractName(txtpath)) )
        ExecMgr.CleanWorkspace(
                target='output_job_PhotonHFJet_1.root',allfiles='output_job_PhotonHLJet*.root')

#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser
from xPhoton.xPhoton.Managers.ExecuteMgr import ExecMgr, FileNameConverter
from xPhoton.xPhoton.Managers.ExecuteMgr import prefix_local
from xPhoton.xPhoton.Managers import LogMgr

import os
import commands

# usage :
#    ./this.py filepath.txt
#    ./this.py filepath.txt path.txt


def checkarg(inputArg): return inputArg[1] if len(inputArg) > 1 else None

def nlines(filepath): return sum( 1 for line in open(filepath,'r') )
def ExecSample(execmgr, pathmgr):
    print 'no input file detected. Use internal example'
    # my new code
    lines=[
        '~/ReceivedFile/GJet/test/ggtree_datasample.root'
    ]
    for rootFile in lines:
        execmgr.execCommand( pathmgr.GetPath(rootFile),pathmgr.GetFileID(rootFile) )

def ExecByFile(execmgr,pathmgr, textpath):
    print 'input file used : ' + textpath
    with open(textpath, 'r') as ifile:
        tot=nlines(filename)
        for i, remoteDir in enumerate( ifile.readlines() ):
            if i%100 == 0: print '-- %d th / %d -- file processed' % (i, tot)
            mylog.debug(' orig file : %s' % remoteDir )
            fullpath=pathcontroller.GetPath(remoteDir)
            fileid=pathcontroller.GetFileID(remoteDir)
            cmd.execCommand( fullpath, fileid )
        cmd.CleanWorkspace(
                target='output_job_PhotonHFJet_1.root',
                allfiles='output_job_PhotonHFJet*.root')


if __name__ == '__main__':
    LogMgr.InitLogger(level='warning')
    mylog=LogMgr.GetLogger(__name__)

    txtpath = checkarg(argv)
    cmd=ExecMgr()
    cmd.SetGeneralCommand('exec_xPhotonRunner %s %d')
    pathcontroller=FileNameConverter(prefix_local)
    #pathcontroller=FileNameConverter('root://se01.grid.nchc.org.tw/')

    if txtpath:
        ExecByInputPath(cmd, pathcontroller, txtpath)
    else:
        ExecSample(cmd, pathcontroller)

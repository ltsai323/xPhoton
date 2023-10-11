#!/usr/bin/env python3
### usage example
# ./py.AppendCTagCalibration.GeneralPath.py `ls ~/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/GJet_Pt-*` step3.btagSFappended/
dataera='UL2016PreVFP'

DATAERA_OPTION = [ '2016ReReco', 'UL2016PreVFP', 'UL2016PostVFP', 'UL2017', 'UL2018' ]
import os
from xPhoton.xPhoton.AppendEventInfo import FindXSInfo, nodir, ShowPD, ShowDetail
from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger

def GetArg_IFiles(argv) -> list :
    # from 1~N-1. But arguments are 1~N
    maxNUM = len(argv) -1
    return argv[1:maxNUM]
def GetArg_OFolder(argv):
    return argv[-1]
def LOG(mesg): print('[LOG] '+ mesg)
def WARNING(mesg):
    print('================== WARNING ===========================')
    print('')
    print(mesg)
    print('')
    print('======================================================')

def executeCommand( inputfile_, newfolder ):
    #execfile='./exe.AppendBTagCalibration' # use makefile
    execfile='exec_AppendCTagCalibration' # use CMSSW

    ifile = inputfile_
    newfile = newfolder + '/' + nodir(inputfile_)
    era = dataera
    command=f'{execfile} {era} {ifile} {newfile}'
    LOG      (command)
    os.system(command)

if __name__ == '__main__':
    InitLogger(level='info')
    mylog=GetLogger(__name__)

    import sys
    iFileList = GetArg_IFiles (sys.argv)
    newfolder = GetArg_OFolder(sys.argv)

    iFileSample = iFileList[0]
    sendwarning = False
    if dataera not in iFileSample:
        for d in DATAERA_OPTION:
            if d in iFileSample:
                sendwarning = True
    if sendwarning:
        WARNING(f'dataera "{dataera}" is set but initial path but\n input file containes another name \n -> {iFileSample}')

    for rootfile in iFileList:
        executeCommand( rootfile,newfolder )

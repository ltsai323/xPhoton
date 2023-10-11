#!/usr/bin/env python3
oldfolder='step2.mergePDversion'
newfolder='step3.btagSFappended'
dataera='UL2016PreVFP'

import os
from xPhoton.xPhoton.AppendEventInfo import FindXSInfo, nodir, ShowPD, ShowDetail
from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger

def executeCommand( inputfile_ ):
    #execfile='./exe.AppendBTagCalibration' # use makefile
    execfile='exec_AppendCTagCalibration' # use CMSSW
    command='%s {era} {ifile} %s/{newfile}' %(execfile,newfolder)
    os.system( command.format( era=dataera, ifile=inputfile_, newfile=nodir(inputfile_) ) )

def LOG(mesg): print('[LOG] '+ mesg)

def executeCommand_(
        dataERA:str,
        cmdEXEC:str,
        outputDIR:str,
        inputFILE:str ) -> None:
    command='%s {era} {ifile} %s/{newfile}' %(cmdEXEC,outputDIR)
    LOG      ( command.format( era=dataERA, ifile=inputFILE, newfile=nodir(inputFILE) ) )
    os.system( command.format( era=dataERA, ifile=inputFILE, newfile=nodir(inputFILE) ) )
def exec_AppendCTagCalibration(
        dataERA:str,
        outputDIR:str,
        inputFILE:str ) -> None:
    cmdEXEC = 'exec_AppendCTagCalibration'
    command = '%s {era} {ifile} %s/{newfile}' %(cmdEXEC,outputDIR)
    LOG      ( command.format( era=dataERA, ifile=inputFILE, newfile=nodir(inputFILE) ) )
    os.system( command.format( era=dataERA, ifile=inputFILE, newfile=nodir(inputFILE) ) )

if __name__ == '__main__':
    InitLogger(level='info')
    mylog=GetLogger(__name__)
    if not os.path.exists(newfolder) or not os.path.isdir(newfolder): os.mkdir(newfolder)

    #for item in os.listdir(oldfolder):
    #    rootfile='%s/%s' % (oldfolder,item)
    #    executeCommand( rootfile )

    #era='UL2016PreVFP'
    era='UL2016PostVFP'

    #for item in os.listdir(oldfolder):
    #    rootfile='%s/%s' % (oldfolder,item)
    #    executeCommand_(
    #            dataERA=era,
    #            outputDIR=newfolder,
    #            inputFILE=rootfile
    #            )

    exec_AppendCTagCalibration(
            dataERA=era,
            outputDIR='.',
            inputFILE='/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/step0.xphoton/UL16PostVFP_data.root'
            )

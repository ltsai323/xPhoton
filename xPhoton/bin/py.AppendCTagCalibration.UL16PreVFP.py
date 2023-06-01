#!/usr/bin/env python2
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

if __name__ == '__main__':
    InitLogger(level='info')
    mylog=GetLogger(__name__)
    if not os.path.exists(newfolder) or not os.path.isdir(newfolder): os.mkdir(newfolder)

    for item in os.listdir(oldfolder):
        rootfile='%s/%s' % (oldfolder,item)
        executeCommand( rootfile )

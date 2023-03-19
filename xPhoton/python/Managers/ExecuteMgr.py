#!/usr/bin/env python2
from __future__ import print_function
import os
import commands
from xPhoton.xPhoton.Managers import LogMgr
mylogger=LogMgr.GetLogger(__name__)


prefix_nchc='root://se01.grid.nchc.org.tw/'
#prefix_local='file:'
#prefix_localabs='file://'

class ExecMgr(object):
    def __init__(self, cmd='echo "welcome to use ExecMgr. Please put some bash command"'):
        self.SetGeneralCommand(cmd)
    def SetGeneralCommand(self, cmd):
        self._cmd=cmd
    def execCommand(self, *cmdArgs):
        status, mesg = commands.getstatusoutput( self._cmd % cmdArgs )
        if status:
            raise RuntimeError('Job failed : %s\n%s' % (self._cmd % cmdArgs, mesg))
        else:
            logfile=open('running.log','w')
            logfile.write(mesg)
            logfile.close()
    @staticmethod
    def CleanWorkspace(target='output_job_PhotonHFJet_1.root', allfiles='output_job_PhotonHFJet*.root'):
        if os.path.isfile(target):
            print('cleaning temporary files')
            os.system('/bin/rm %s' % allfiles)
        else:
            print('You have a clean workspace')

class FileNameConverter(object):
    def __init__(self, prefix=''):
        self._prefix=prefix
        '''
    def __init__(self, isRemote=False,remoteprefix=prefix_nchc):
        self._prefix=''
        if isRemote: self.SetPrefix(remoteprefix)
        '''
    def GetPath(self, inpath):
        p1=inpath.strip()
        p2=FileNameConverter.convertifHOMEused(p1)
        p3=self.fullpath(p2)
        return p3
    def fullpath(self, p):
        return self._prefix+p

    @staticmethod
    def GetFileID(inpath):
        try:
            return int(inpath.split('_')[-1].split('.')[0])
        except ValueError:
            mylogger.warning('No number included in input root file, force output number to ZERO.')
            return 0
    @staticmethod
    def convertifHOMEused(oldname):
        if '~' in oldname:
            seps=oldname.split('~')
            if len(seps) > 2:
                raise SyntaxError('path recognize failed, there are %d "~" in %s'%(len(seps)-1, oldname) )
            newname=os.getenv('HOME').join(seps)
            return newname
        return oldname
    @staticmethod
    def ExtractName(filepath):
        return filepath.strip().split('/')[-1].split('.')[0]

if __name__ == '__main__':
    LogMgr.InitLogger()
    a=ExecMgr('ls -lh')
    '''
    a.cleanworkspace(
            check='hi.root',
            allfiles='hi*.root'
            )
    '''

    a.SetGeneralCommand('echo hi %s %d')
    mylist=['hi',1]
    a.execCommand( *mylist )


    b=FileNameConverter('hi')
    print(b.GetPath('---QQ'))
    ExecMgr.CleanWorkspace(
            target='hi.root',
            allfiles='hi*.root'
            )


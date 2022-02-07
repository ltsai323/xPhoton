#!/usr/bin/env python2

DEFAULT_EXECUTABLE='exec_xElectronRunner'
LOCAL_FILE=True

def GetArg_PrintHelp():
    raise IOError('''This code manages assigns the number of thread used.
            arg1: input a text path.
            arg2: number of thread (default is 4)
            ''')
    pass
def GetArg_TextPath(argv):
    if len(argv) < 2: GetArg_PrintHelp()
    return argv[1]
def GetArg_NumThread(argv):
    if len(argv) < 2+1: return 4
    return int(argv[2])

def CheckENV_X509():
    if not os.environ.get('X509_USER_PROXY'):
        raise KeyError('VO not set! Please refresh VO first')
    return os.environ['X509_USER_PROXY']
def ExtractFileName(filepath_):
    idx0 = -1 if filepath_[-1] == '/' else len(filepath_)
    temppath0=filepath_[:idx0]
    idx1 = temppath0.rfind('/')+1 if '/' in temppath0 else 0
    temppath1=temppath0[idx1:]
    idx2 = temppath1.rfind('.')   if '.' in temppath1 else len(temppath1)
    return temppath1[:idx2]

def ReIndexing(threadNum_,idx_):
    return 100000*(threadNum_)+idx_

def CreateWorkspace(abspath_):
    os.system( 'mkdir -p %s' % abspath_ )
def CleanUpWorkspace(abspath_):
    os.system( 'touch %s ; /bin/rm -rf %s' % (abspath_,abspath_) )



if __name__ == '__main__':
    import os
    import sys
    import json
    if not LOCAL_FILE: CheckENV_X509()
    pathsfile=GetArg_TextPath(sys.argv)
    nCoresSep=GetArg_NumThread(sys.argv)
    exeCmdStr=DEFAULT_EXECUTABLE

    #path=pathsfile
    workspacepath=os.getcwd()
    newpath=ExtractFileName(pathsfile)
    workingfolder='/'.join( [workspacepath,'mytest',newpath] )

    CleanUpWorkspace(workingfolder)
    CreateWorkspace(workingfolder)

    with open( pathsfile, 'r' ) as fin:
        allfiles_=fin.readlines()
        allfiles=[ file.strip() for file in allfiles_ ]
        for iThread in range(nCoresSep):
            threadfile=allfiles[iThread::nCoresSep]

            jsonname='seplist_%s_%d.json'%(newpath, iThread)
            fout=open(jsonname,'w' )

            content={
                    'directory':workingfolder,
                    'paths':threadfile
                    }
            jsoncontent=json.dumps( content, indent=2 )
            fout.write(jsoncontent)
            fout.close()

            if LOCAL_FILE:
                os.system( 'python sepRunnerFrag_localFile.py  %s %s %d &'%(jsonname,exeCmdStr,iThread) )
            else:
                os.system( 'python sepRunnerFrag_remoteFile.py %s %s %d &'%(jsonname,exeCmdStr,iThread) )

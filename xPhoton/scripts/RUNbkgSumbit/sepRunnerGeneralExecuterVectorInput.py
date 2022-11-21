#!/usr/bin/env python2

def GetArg_PrintHelp():
    raise IOError('''This code manages assigns the number of thread used.
            arg1: input a text path.
            arg2: executable command (a string)
            arg3: number of thread
            arg4: useRemote? (default use local file)
            ''')
    pass
def GetArg_TextPath(argv):
    if len(argv) < 4: GetArg_PrintHelp()
    return argv[1]
def GetArg_Executable(argv):
    return argv[2]
def GetArg_NumThread(argv):
    return int(argv[3])
def GetArg_UseRemote(argv):
    if len(argv) >= 5:
        if argv[4] == '1' or argv[4].lower() == 'true': return True
    return False

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
    CreateWorkspace(abspath_)
    os.system( 'touch %s ; /bin/rm -rf %s' % (abspath_,abspath_) )



if __name__ == '__main__':
    import os
    import sys
    import json
    pathsfile=GetArg_TextPath(sys.argv)
    nCoresSep=GetArg_NumThread(sys.argv)
    exeCmdStr=GetArg_Executable(sys.argv)
    useRemote=GetArg_UseRemote(sys.argv)

    #path=pathsfile
    workspacepath=os.getcwd()
    newpath=ExtractFileName(pathsfile)
    workingfolder='/'.join( [workspacepath,'bkgRunning',newpath] )

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

            if useRemote:
                CheckENV_X509()
                os.system( 'python sepRunnerFrag_remoteFileVectorInput.py %s %s %d &'%(jsonname,exeCmdStr,iThread) )
            else:
                os.system( 'python sepRunnerFrag_localFileVectorInput.py  %s %s %d &'%(jsonname,exeCmdStr,iThread) )

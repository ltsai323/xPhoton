#!/usr/bin/env python2
exeCMD='exec_xPhotonRunner2018ReReco'
nThread=4


def GetArg_PrintHelp():
    raise IOError('''This code runnes "{exefile}" command in "{nCPU}" threads.
            This executer requires a path list recording the location to root files.
            arg1: input a text path.
            '''.format(exefile=exeCMD, nCPU=nThread))
def GetArg_TextPath(argv):
    if len(argv) < 2: GetArg_PrintHelp()
    return argv[1]

if __name__ == '__main__':
    import sys
    textpath=GetArg_TextPath(sys.argv)
    f=open(textpath,'r')
    useRemote='True' if 'root://' in f.read() else 'False' # read first line
    f.close()

    #os.system( 'python sepRunnerGeneralExecuter.py %s %s %d &'%(textpath,exeCMD,nThread, useRemote) )
    print( 'python sepRunnerGeneralExecuter.py %s %s %d %s&'%(textpath,exeCMD,nThread, useRemote) )

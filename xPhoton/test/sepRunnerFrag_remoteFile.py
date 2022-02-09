#!/usr/bin/env python2
def GetArg_PrintHelp():
    raise IOError('''Minor running code for xphoton.
            Arg1 : Input a json file which is generated by sepRunner.py
            Arg2 : Provide an executable, which is a bash recognizable command.
            Opt3 : thread index, whichi is needed to be a int.
            ''')
def GetArg_JsonFile(argv):
    if len(argv) < 3: GetArg_PrintHelp()
    return argv[1]
def GetArg_Executable(argv):
    if len(argv) < 3: GetArg_PrintHelp()
    return argv[2]
def GetOpt_ThreadIdx(argv):
    if len(argv) > 3: return int(argv[3])
    return 0


def ReIndexing(threadNum_,idx_):
    return 100000*(threadNum_)+idx_

if __name__ == '__main__':
    import sys
    import json
    import os

    jsonfile=GetArg_JsonFile(sys.argv)
    execfile=GetArg_Executable(sys.argv)
    generalidx=GetOpt_ThreadIdx(sys.argv)

    fin=open(jsonfile,'r')
    inputdic=json.load(fin)

    workpath=inputdic['directory']
    inpaths=inputdic['paths']

    os.chdir(workpath)
    for fIdx, inputpath in enumerate(inpaths):
        os.system( 'xrdcp -f {file} running_{idx}.root ; {exe} running_{idx}.root {idx} > logging_{idx} 2>&1; /bin/rm running_{idx}.root'.format(file=inputpath, idx=ReIndexing(generalidx,fIdx),exe=execfile ) )

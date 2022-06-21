#!/usr/bin/env python2

import json
class JsonInterpretor(object):
    def printhelp(self):
        print('''############# input argument #############''')
        print('''##### ./this.py info.json            #####''')
        print('''##### where info.json should contain #####''')
        print('''##### 1. summaryFile                 #####''')
        print('''##### 2. dataera                     #####''')
        print('''##### 3. isQCD                       #####''')
        print('''##### 4. fileDict                    #####''')
        print('''############# input argument #############''')
    def __init__(self, jsonname):
        infile=open(jsonname,'r')
        data=json.load(infile)
        self.check(data)

        self.arg_summaryfile=data['summaryfile']
        self.arg_dataera=data['dataera']
        self.arg_isQCD=data['isQCD']
        self.fDict=data['fileDict']
    def check(self, data):
        if not 'summaryfile'    in data: self.printhelp()
        if not 'dataera'        in data: self.printhelp()
        if not 'isQCD'          in data: self.printhelp()
        if not 'fileDict'       in data: self.printhelp()
    def printLoaing(self):
        print('loaded info...')
        print('summary file : %s'% self.arg_summaryfile)



if __name__ == '__main__':
    from AppendEventInfoPythonHelper import *
    from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger
    import sys
    arg=JsonInterpretor(sys.argv[1])
    arg.printLoaing()


    InitLogger(level='warning')
    mylog=GetLogger(__name__)
    CheckWorkingDir()

    targetDict=arg.fDict
    integratedgenweights = { pd:sum( [IntegratedGenWeights(fpath) for ver,fpath in info.iteritems()] )
            for pd, info in targetDict.iteritems() }

    for pd, info in targetDict.iteritems():
        for ver, rootfile in info.iteritems():
            print rootfile
            xs=GetXS(pd, ver, arg.arg_summaryfile)
            #print( 'input information :\n  ->  xs:%20.10f\n  ->  int weight:%20.10f\n  ->  dataera: %d\n  ->  isQCD? %s\n  ->  rootfile : %s\n' %( xs, integratedgenweights[pd], arg.arg_dataera, 'True' if arg.arg_isQCD else 'False', rootfile ) )
            executeCommandToTmp( xs, integratedgenweights[pd], arg.arg_dataera, arg.arg_isQCD, rootfile )
        MergeOutputs(pd, info)


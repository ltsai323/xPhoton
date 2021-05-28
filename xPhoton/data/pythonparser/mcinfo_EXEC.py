#!/usr/bin/env python2
from xPhoton.xPhoton.Managers.LogMgr import GetLogger, LoadLoggerConfig
LoadLoggerConfig(confPath='/home/ltsai/local/mylib/data/logger_debug.config',fromCurrentDir=False)
mylog=GetLogger(__name__)

from extractMCInfo import ExtractMCInfo
from primarydatasetMatching import PrimaryDataseatMatching
import os
import json

class keyinfo(object):
    def __init__(self, pd, isext):
        self.pd=pd
        self.isext=isext
    def GetKey(self):
        if self.isext == True:
            return self.pd + '_' + 'extended'
        return self.pd

def assertinfo(collector, pd, info, printWarning=False):
    if pd in collector.keys():
        if printWarning:
            print '--- Warning --- Ignoring duplicated information. Primary dataset {0} duplicated!'.format(pd)
    else:
        collector.update( {pd:info} )




if __name__ == '__main__':

    crabfiles=[
            ('bkgMC_pythia', '../mcInformation/crabExecHistory/bkgMC_TuneCUETP8M1_py_crabConfig.py'),
            ('sigMC_pythia', '../mcInformation/crabExecHistory/sigMC_GJetPythia_py_crabConfig.py'),
            ('sigMC_amcatnlo', '../mcInformation/crabExecHistory/sigMC_amcatnlo_py_crabConfig.py'),
            ('sigMC_madgraph', '../mcInformation/crabExecHistory/sigMC_madgraph_py_crabConfig_25ns.py'),
            ('sigMC_pythiaFlat', '../mcInformation/crabExecHistory/sigMC_pythiaFlat_py_crabConfig_25ns.py'),
            ]

    for inputlabel, crabfile in crabfiles:
        print ' -> processing file '+crabfile
        datacollector={}
        for primarydataset, filename_mcinfo, isext in PrimaryDataseatMatching(crabfile):
            if not os.path.isfile(filename_mcinfo):
                raise IOError( '!!! file %s not found !!!' %filename_mcinfo )

            pd,info=ExtractMCInfo(filename_mcinfo, primarydataset)
            if info:
                assertinfo(datacollector, pd, info)

        '''
        for key,val in datacollector.iteritems():
            print key +' '+ repr(val)
        '''

        fout=open('../mcInformation/summary_%s.json'%inputlabel,'w')
        json.dump(datacollector, fout)
        fout.close()



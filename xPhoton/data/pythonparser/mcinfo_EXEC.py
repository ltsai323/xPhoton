#!/usr/bin/env python2
from xPhoton.xPhoton.Managers.LogMgr import GetLogger, LoadLoggerConfig
LoadLoggerConfig(confPath='/home/ltsai/local/mylib/data/logger_debug.config',fromCurrentDir=False)
mylog=GetLogger(__name__)

from mcinfo_extractMCInfo import ExtractMCInfo
from mcinfo_primarydatasetMatching import PrimaryDataseatMatching
import os
import json

if __name__ == '__main__':

    crabfiles=[
            ('bkgMC_pythia', '../mcInformation/crabExecHistory/bkgMC_TuneCUETP8M1_py_crabConfig.py'),
            ('sigMC_pythia', '../mcInformation/crabExecHistory/sigMC_GJetPythia_py_crabConfig.py'),
            ('sigMC_amcatnlo', '../mcInformation/crabExecHistory/sigMC_amcatnlo_py_crabConfig.py'),
            ('sigMC_madgraph', '../mcInformation/crabExecHistory/sigMC_madgraph_py_crabConfig_25ns.py'),
            ('sigMC_pythiaFlat', '../mcInformation/crabExecHistory/sigMC_pythiaFlat_py_crabConfig_25ns.py'),
            ]

    for inputlabel, crabfile in crabfiles:
        print 'processing file '+crabfile
        datacollector=[]
        for primarydataset, filename_mcinfo in PrimaryDataseatMatching(crabfile):
            if not os.path.isfile(filename_mcinfo):
                raise IOError( '!!! file %s not found !!!' %filename_mcinfo )

            outinfo=ExtractMCInfo(filename_mcinfo, primarydataset)
            if outinfo:
                datacollector.append(ExtractMCInfo(filename_mcinfo, primarydataset))

        fout=open('../mcInformation/summary_%s.json'%inputlabel,'w')
        json.dump(datacollector, fout)
        fout.close()



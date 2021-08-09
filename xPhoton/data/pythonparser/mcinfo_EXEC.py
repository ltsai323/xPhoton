#!/usr/bin/env python2
# usage : ./this.py
# format of ouptut json file
#   { pd: { version : { 'xs':[val,err,unit], 'fracofevt':[val,err], 'lumiper1Mevt':[val,err,unit] } } }
template_summaryoutput='../mcInformation/summary_%s.json'

from xPhoton.xPhoton.Managers.LogMgr import GetLogger, LoadLoggerConfig
LoadLoggerConfig(confPath='/home/ltsai/local/mylib/data/logger_debug.config',fromCurrentDir=False)
mylog=GetLogger(__name__)


from mcinfo_extractMCInfo import ExtractMCInfo
from mcinfo_primarydatasetMatching import PrimaryDataseatMatching, GetFileNameFromPD, _version, _primarydataset, _secondarydataset
import os
import json

class keyinfo(object):
    def __init__(self, pd, ver):
        self.pd=pd
        self.ver=ver
    def primarydataset(self): return self.pd
    def version(self): return self.ver
    def Key(self): return self.pd

def assertinfo(collector, pd, info):
    if pd.Key() in collector.keys():
        if pd.version() in collector[ pd.Key() ]:
            print '--- Warning --- Ignoring duplicated information. Primary dataset {0} {1} duplicated!'.format(pd.primarydataset(), pd.version() )
        collector[ pd.Key() ].update( {pd.version():info} )
    else:
        collector[ pd.Key() ]= {pd.version():info}




if __name__ == '__main__':

    crabfiles=[
            ('bkgMC_pythia', '../mcInformation/crabExecHistory/bkgMC_TuneCUETP8M1_py_crabConfig.py'),
            ('sigMC_pythia', '../mcInformation/crabExecHistory/sigMC_GJetPythia_py_crabConfig.py'),
            ('sigMC_amcatnlo', '../mcInformation/crabExecHistory/sigMC_amcatnlo_py_crabConfig.py'),
            ('sigMC_madgraph', '../mcInformation/crabExecHistory/sigMC_madgraph_py_crabConfig_25ns.py'),
            ('sigMC_pythiaFlat', '../mcInformation/crabExecHistory/sigMC_pythiaFlat_py_crabConfig_25ns.py'),
            ]
    datalist=[
            ('bkgMC_madgraph',  '../mcInformation/datasets/dataset.QCDmadgraph.txt')
                ]

    mesg_outputs=[]
    for inputlabel, crabfile in crabfiles:
        print ' -> processing file '+crabfile
        datacollector={}
        for primarydataset, filename_mcinfo, v_ in PrimaryDataseatMatching(crabfile):
            if not os.path.isfile(filename_mcinfo):
                raise IOError( '!!! file %s not found !!!' %filename_mcinfo )

            p_,info=ExtractMCInfo(filename_mcinfo, primarydataset)
            pd=keyinfo(primarydataset, v_)

            if info:
                assertinfo(datacollector, pd, info)

        mesg_outputs.append( template_summaryoutput % inputlabel )
        fout=open((template_summaryoutput%inputlabel),'w')
        json.dump(datacollector, fout, indent=2)
        fout.close()

    for inputlabel, datasetfile in datalist:
        print ' -> processing file '+crabfile
        with open(datasetfile,'r') as ifile:
            datacollector={}
            for line in ifile.readlines():
                if line.strip() == '': continue

                datasetname=line.strip()
                primarydataset=_primarydataset(datasetname)
                secondarydataset=_secondarydataset(datasetname)
                filename_mcinfo=GetFileNameFromPD(primarydataset,secondarydataset)

                v_=_version(datasetname)

                p_, info=ExtractMCInfo(filename_mcinfo, primarydataset)
                pd=keyinfo(primarydataset, v_)
                print pd.Key()


                if info:
                    assertinfo(datacollector, pd, info)


            mesg_outputs.append(template_summaryoutput%inputlabel)
            fout=open((template_summaryoutput%inputlabel),'w')
            json.dump(datacollector, fout, indent=2)
            fout.close()

    print 'output files are : '
    for f in mesg_outputs:
        print f


#!/usr/bin/env python2
from __future__ import print_function
fileList=[
{'pd':'GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8', 'path':'hi.root'}
]



#testSummaryFile='../data/mcInformation/summary_bkgMC_pythia.json'
#testSummaryFile='../data/mcInformation/summary_sigMC_amcatnlo.json'
testSummaryFile='../data/mcInformation/summary_sigMC_madgraph.json'
#testSummaryFile='../data/mcInformation/summary_sigMC_pythia.json'
#testSummaryFile='../data/mcInformation/summary_sigMC_pythiaFlat.json'

def GetXsection(db): return db['xs'][0]

import json
def FindXSInfo( primarydataset_, version_ ,summaryjson_):
    with open(summaryjson_,'r') as ifile:
        xsinfo=json.load(ifile)
        if primarydataset_ in xsinfo:
            if version_ in xsinfo[primarydataset_]:
                return xsinfo[primarydataset_][version_]['xs']
            else:
                raise IOError( 'version %s not found in primary dataset %s at file %s' % (version_, primarydataset_, summaryjson_) )
        else:
            raise IOError( 'primary dataset %s is not found at file %s' % (primarydataset_, summaryjson_) )


import os
def nodir(path):
    return path.split('/')[-1]
def ShowPD(SummaryFile):
    with open(SummaryFile,'r') as f:
        #for db in json.load(f): print db['pd']
        for pd, info in json.load(f).iteritems(): print(pd)
def ShowDetail(SummaryFile):
    with open(SummaryFile,'r') as f:
        for db in json.load(f): print(db)

if __name__ == '__main__':
    for fileinfo in fileList:
        print( GetXS(fileinfo['pd']) )

def ValidFile(filepath):
    if ( os.path.exists(filepath) ): return filepath
    raise IOError("Input file not found : %s" % filepath)

def FindWeightFile( primarydataset_, jsonFILE_ ):
    with open(jsonFILE_,'r') as ifile:
        aaaa=json.load(ifile)
        return ValidFile(aaaa[primarydataset_])

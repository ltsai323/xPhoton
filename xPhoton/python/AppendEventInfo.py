#!/usr/bin/env python2
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
def GetXS(primarydataset, SummaryFile=testSummaryFile):
    with open(SummaryFile,'r') as f:
        database=json.load(f)
        for db in database:
            if primarydataset == db['pd']:
                return GetXsection(db)
    raise ValueError('primary dataset {%s} is not found in database\nIs file corrected? {%s}'%(primarydataset, fileinfo['path']))

import os
def nodir(path):
    return path.split('/')[-1]
def ShowPD(SummaryFile):
    with open(SummaryFile,'r') as f:
        for db in json.load(f): print db['pd']
def ShowDetail(SummaryFile):
    with open(SummaryFile,'r') as f:
        for db in json.load(f): print db

if __name__ == '__main__':
    for fileinfo in fileList:
        print GetXS(fileinfo['pd'])

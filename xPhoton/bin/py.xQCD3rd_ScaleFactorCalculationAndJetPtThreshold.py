#!/usr/bin/env python2
from __future__ import print_function


def PrintHelp():
    print('===================================')
    print('== Executing helper for xQCD3rd. ==')
    print('==   Arg1: output folder. If     ==')
    print('==         nothing put. Use "."  ==')
    print('===================================')

DEFAULT_DESTINYFOLDER='.'
def GetArg_dest(argv):
    if len(argv) < 1+1: return DEFAULT_DESTINYFOLDER
    return argv[1]


def LOG(printstr):
    print('\n====================================================')
    print(printstr)
    print('====================================================\n')


PD_DICT={
        50:     "QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        100:    "QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        200:    "QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        300:    "QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        500:    "QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        700:    "QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        1000:   "QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        1500:   "QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8",
        2000:   "QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8"
        }
class InputConnector(object):
    ofile_template='xQCD3rd_ScaleFactorCalculationAndJetPtThreshold_cc_%s.root'
    HTranges=[50,100,200,300,500,700,1000,1500,2000,'Inf']
    def __init__(self,leftHT,fileNAME):
        if not leftHT in InputConnector.HTranges:
            LOG('InputConnector::Failed to find HT %d in HTranges. Terminate the program' % leftHT)
            exit()
        self._lHT = leftHT
        self._if = os.getcwd()+'/'+fileNAME # translate to absolute path
        self._PD = PD_DICT[leftHT]
        idx=InputConnector.HTranges.index(leftHT)+1
        tagL='%04d'%leftHT
        tagR=InputConnector.HTranges[idx]
        tagR='%04d'%tagR if type(tagR) is int else tagR
        self._outtag=tagL+"To"+tagR
    @property
    def HT(self): return self._lHT
    @property
    def FileName(self): return self._if
    @property
    def PrimaryDataset(self): return self._PD
    @property
    def OutputFileName(self): return InputConnector.ofile_template % self._outtag


if __name__ == "__main__":
    import sys
    import os

    destFolder = GetArg_dest(sys.argv)


    executable='xQCD3rd_ScaleFactorCalculationAndJetPtThreshold'
    inputs=[
            InputConnector(50   , "xQCD2nd_ReweightChecking_Madgraph_cc_HT50to100.root"),
            InputConnector(100  , "xQCD2nd_ReweightChecking_Madgraph_cc_HT100to200.root"),
            InputConnector(200  , "xQCD2nd_ReweightChecking_Madgraph_cc_HT200to300.root"),
            InputConnector(300  , "xQCD2nd_ReweightChecking_Madgraph_cc_HT300to500.root"),
            InputConnector(500  , "xQCD2nd_ReweightChecking_Madgraph_cc_HT500to700.root"),
            InputConnector(700  , "xQCD2nd_ReweightChecking_Madgraph_cc_HT700to1000.root"),
            InputConnector(1000 , "xQCD2nd_ReweightChecking_Madgraph_cc_HT1000to1500.root"),
            InputConnector(1500 , "xQCD2nd_ReweightChecking_Madgraph_cc_HT1500to2000.root"),
            InputConnector(2000 , "xQCD2nd_ReweightChecking_Madgraph_cc_HT2000toInf.root"),
            ]

    LOG('executing path : %s'%destFolder)
    os.chdir(destFolder)
    for input_info in inputs:
        #LOG('%s %s %d'%( executable, input_info.FileName, input_info.HT))
        os.system('%s %s %d'%( executable, input_info.FileName, input_info.HT))

    oDict={}
    for input_info in inputs:
        oDict[input_info.PrimaryDataset] = os.getcwd() + '/' + input_info.OutputFileName
    import json
    json_object = json.dumps(oDict, indent=2)
    with open('AppendEventInfoPythonHelper.json','w') as outfile:
        outfile.write(json_object)
    LOG('executed. json file is stored to \n -> %s'% os.getcwd()+"/"+'AppendEventInfoPythonHelper.json')

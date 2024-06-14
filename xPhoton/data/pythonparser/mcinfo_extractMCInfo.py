#!/usr/bin/env python2
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
mylog=GetLogger(__name__)

unitList=['1/fb', 'pb', 'fb']

def UnitRecognize(line):
    for unit in unitList:
        if unit in line:
            return unit
    return None

def findnumber(word):
    numstr=word.split('=')[1].strip()
    numbers=numstr.split(' ')
    output=[ float(numbers[0]), float(numbers[2]), UnitRecognize(word) ]
    return [ content for content in output if content != None ]
def numberinterpreter(lines):
    if len(lines) < 2:
        mylog.warning( 'input lines: {0}'.format(lines) )
        return None
    return {'xs': lines[0], 'fracofevt': lines[1], 'lumiper1Mevt':lines[2]}

def ExtractMCInfo(filename,primarydataset):
    ifile=open(filename,'r')
    reslines=[ findnumber(line) for line in ifile.readlines()
               if 'After' in line and 'final' in line ]
    outputdict=numberinterpreter(reslines)
    if not outputdict:
        mylog.warning( '   nothing is extracted from file %s. Please Check!' % filename )
        return (None, None)

    return (primarydataset, outputdict)

if __name__ == '__main__':
    print '-------- checking code -------'
    fname='../mcInformation/mcInfo_sigMC_Pt650ToInf_13TeV-amcatnlo-pythia8_v3-v2_sub01.txt'

    pd='myprimarydataset'
    print ExtractMCInfo(fname,pd)

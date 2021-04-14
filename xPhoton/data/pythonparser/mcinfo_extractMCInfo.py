#!/usr/bin/env python2
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
mylog=GetLogger(__name__)
def findnumber(word):
    numstr=word.split('=')[1].strip()
    numbers=numstr.split(' ')
    return (float(numbers[0]), float(numbers[2]))
def numberinterpreter(lines):
    if len(lines) < 2:
        print 'input lines: {0}'.format(lines)
        return None
    return {'xs': lines[0], 'fracofevt': lines[1], 'lumiper1Mevt':lines[2]}

def ExtractMCInfo(filename,primarydataset):
    ifile=open(filename,'r')
    reslines=[]
    for line in ifile.readlines():

        if 'After' in line:
            if 'final' in line:
                reslines.append( findnumber(line) )
    outputdict=numberinterpreter(reslines)
    if not outputdict:
        mylog.warning( '  is extracted from file %s. Please Check!' % filename )
        return None

    outputdict.update({'pd':primarydataset})
    return outputdict

if __name__ == '__main__':
    fname='../mcInformation/mcInfo_sigMC_Pt650ToInf_13TeV-amcatnlo-pythia8_v3-v2_sub01.txt'

    pd='myprimarydataset'
    print ExtractMCInfo(fname,pd)

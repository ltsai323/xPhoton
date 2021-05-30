#!/usr/bin/env python2

def filenamefinder(word):
    mainword=word.split(':')[1].split("'")[1]
    return '../mcInformation/mcInfo_'+mainword+'.txt'
def primarydatasetfinder(word):
    return word.split(':')[2].split("/")[1]
def isExt(word):
    return 'ext1' in word or 'ext2' in word
# return a tuple in ( primary dataset, associated filename )
def PrimaryDataseatMatching(filename):
    ifile=open(filename,'r')
    return [ (primarydatasetfinder(line),filenamefinder(line), isExt(line))
            for line in ifile.readlines() if 'dataset' in line and ':' in line ]

if __name__ == '__main__':
    filename='../mcInformation/crabExecHistory/bkgMC_TuneCUETP8M1_py_crabConfig.py'

    for obs in PrimaryDataseatMatching(filename):
        print obs

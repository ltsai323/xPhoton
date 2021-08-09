#!/usr/bin/env python2

defaultpath='../mcInformation/mcInfo_'
def filename(word):
    mainword=word.split(':')[1].split("'")[1]
    return defaultpath+mainword+'.txt'
def primarydataset(word):
    return word.split(':')[2].split("/")[1]
def secondarydataset(word):
    if ':' in word:
        return word.split(':')[2].split("/")[2]
    elif '/' in word:
        return word.split('/')[2]
    raise NameError(' input word "%s" does not contain any primary dataset information' % word)
def version(word):
    sd=secondarydataset(word)
    output=sd[ sd.find('_v3')+1: ] if sd.find('_v3')>0 else 'noVer'
    return output+'_backup' if 'backup' in word else output
def isExt(word):
    return 'ext1' in word or 'ext2' in word

# return a tuple in ( primary dataset, associated filename, version )
def PrimaryDataseatMatching(inputfile):
    ifile=open(inputfile,'r')
    return [ ( primarydataset(line),filename(line), version(line) )
            for line in ifile.readlines() if 'dataset' in line and ':' in line ]
def GetFileNameFromPD(pd):
    return defaultpath+'__'.join( pd.split('/')[1:3] )+'.txt'


if __name__ == '__main__':
    ifile='../mcInformation/crabExecHistory/bkgMC_TuneCUETP8M1_py_crabConfig.py'

    for obs in PrimaryDataseatMatching(ifile):
        print obs

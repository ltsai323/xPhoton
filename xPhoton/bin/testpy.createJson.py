#!/usr/bin/env python2

import json

class DataSetInfo(object):
    def __init__(self, pd, ver):
        self._pd=pd
        self._ver=ver
    def ConnectedFile(self,file):
        self._file=file
    def __repr__(self):
        return 'ver:%14s, PD=%s' % (self._ver,self._pd)
def GetFileDict(datasetInfoList_):
    return { dInfo._pd:{dInfo._ver:dInfo._file} for dInfo in datasetInfoList_ }

SKIPIDX=-1
def FileIDFromKeyboard(filelist_):
    looping=0
    # Try again if weird input selected
    while True:
        inputID=raw_input(' -> listed file belongs to idx?  (skip for n/N)')
        if inputID.lower() == 'n': return SKIPIDX
        try:
            inputIdx=int(inputID)
            if inputIdx in filelist_: return inputIdx
        except ValueError:
            pass

        if looping > 0: break
        looping+=1
        print '=== FAILED TO FOUND ID IN LIST, TRY AGAIN ==='
    raise IOError('failed')
def IsQCDfromKeyboard():
    looping=0
    # Try again if weird input selected
    while True:
        res=raw_input(' -> isQCD sample ? (y/n)' ).lower()
        if res == 'n': return False
        if res == 'y': return True

        if looping > 0: break
        looping+=1
        print '=== FAILED TO FOUND ID VALID INFORMATION, TRY AGAIN ==='
    return 'TBD'
def DataErafromKeyboard():
    looping=0
    # Try again if weird input selected
    while True:
        res=raw_input(' -> input dataera: (2016/2017/2018)')
        try:
            idx=int(res)
            if idx == 2016 or idx == 2017 or idx == 2018: return idx
        except ValueError:
            pass
        if looping > 0: break
        looping+=1
        print '=== FAILED TO FOUND ID VALID INFORMATION, TRY AGAIN ==='
    return 0

def FileListFromCmd(cmd_):
    # once no space found in the command, regard it as a directory path needed to be listed.
    execCmd=cmd_ if ' ' in cmd_ else 'ls ' + cmd_

    raw_input(' > %s  --> Is it a valid shell command?' % execCmd)
    import commands
    error, filelist=commands.getstatusoutput( execCmd )
    if error != 0: raise IOError('### ERROR ON COMMAND EXECUTION, ABORT ###')
    return filelist.split()

class OutputJsonContent(object):
    def __init__(self,ifile):
        self.dataera=0
        self.isQCD=False
        self.summaryfile=ifile
        self.fileDict={}
    def result(self):
        dataera=DataErafromKeyboard()
        isqcd=IsQCDfromKeyboard()
        return {
            'summaryfile':self.summaryfile,
            'dataera':dataera,
            'isQCD':isqcd,
            'fileDict':self.fileDict
            }

if __name__ == '__main__':
    import sys
    import json

    outfname=sys.argv[1]
    loadData=sys.argv[2]
    listCmds=sys.argv[3]

    loadFile=open(loadData, 'r')
    loadJson=json.load(loadFile)
    encodeIdx=lambda idxPair: idxPair[0]*10+idxPair[1]
    decodeIdx=lambda idx: ( int(idx/10), int(idx%10) )

    allOptions={ }
    for idx0, PD_ in enumerate(loadJson.keys()):
        for idx1, ver_ in enumerate( loadJson[PD_].keys() ):
                allOptions[encodeIdx( (idx0,idx1) )] = DataSetInfo(PD_,ver_)

    print '=== OVERALL LOADED PRIMARY DATASETS ========='
    for key,val in allOptions.iteritems(): print val
    print '=== OVERALL LOADED PRIMARY DATASETS ========='


    filelist=FileListFromCmd(listCmds)
    PD_file_connection=[]
    for file_ in filelist:
        print '=== Primary dataset codes : ================='
        if len(allOptions) == 0 :
            print('run out of all options, break the other files')
            break
        for loadID, datasetInfo in allOptions.iteritems():
            print '-- ID: %4d ---- %s'%(loadID,datasetInfo)
        print '=== Primary dataset codes : ================='

        print ' -> File ' + file_
        inputIdx=FileIDFromKeyboard(allOptions)
        if inputIdx == SKIPIDX: continue
        selectedDatasetInfo=allOptions.pop(inputIdx)
        selectedDatasetInfo.ConnectedFile(file_)
        PD_file_connection.append(selectedDatasetInfo)

    ### fill missing entry from loaded json file
    for idx, selectedDatasetInfo in allOptions.iteritems():
        selectedDatasetInfo.ConnectedFile('')
        PD_file_connection.append(selectedDatasetInfo)

    print '=== Checking recorded result ================'
    fDict=GetFileDict(PD_file_connection)
    for key,val in fDict.iteritems():
        print '%s -- %s' %(key,val)
    raw_input( '=== Press to continue =======================')

    infoRec=OutputJsonContent(loadData)
    infoRec.fileDict=fDict
    with open(outfname,'w') as ofile:
        json.dump(infoRec.result(),ofile, indent=2)


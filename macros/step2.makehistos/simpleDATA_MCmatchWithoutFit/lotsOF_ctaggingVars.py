#!/usr/bin/env python3

_testing = False

class BinningMgr:
    def __init__(self, pETAbin, jETAbin, pPTrange):
        self.pEtaBin = pETAbin
        self.jEtaBin = jETAbin
        self.pPtRangeL = pPTrange[0]
        self.pPtRangeR = pPTrange[1]
    def __str__(self):
        return f'binning : ({self.pEtaBin},{self.jEtaBin}) and pt range ({self.pPtRangeL}-{self.pPtRangeR})'


if __name__ == "__main__":
    import os


    binnings = [
        # pEtaBin, jEtaBin, pPtRange[low,high]
        BinningMgr(0,0,[200,400] ),
        BinningMgr(1,0,[200,400] ),
        BinningMgr(0,1,[200,400] ),
        BinningMgr(1,1,[200,400] ),

        BinningMgr(0,0,[400,600] ),
        BinningMgr(1,0,[400,600] ),
        BinningMgr(0,1,[400,600] ),
        BinningMgr(1,1,[400,600] ),


        BinningMgr(0,0,[600,800] ),
        BinningMgr(1,0,[600,800] ),
        BinningMgr(0,1,[600,800] ),
        BinningMgr(1,1,[600,800] ),


        BinningMgr(0,0,[200,99999] ),
        BinningMgr(1,0,[200,99999] ),
        BinningMgr(0,1,[200,99999] ),
        BinningMgr(1,1,[200,99999] ),
    ]

    for binning in binnings:
        title = f'###### Running {binning} ######'
        seps = '#'*len(title)
        print( '\n'.join(['\n\n',seps,title,seps,'\n']))

        exec_command = f'python3 ./ctaggingVars.py {binning.pEtaBin} {binning.jEtaBin} {binning.pPtRangeL} {binning.pPtRangeR} &'
        print('[bash] ' + exec_command)
        os.system(exec_command)

        if _testing:
            print('[TESTING] end of 1 loop')
            break

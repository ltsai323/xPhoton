#!/usr/bin/env python3

def PrintHelp(mesg):
    print('''
            --------------- input arguments ----------------
            1. pEtaBin: 0,1
            2. jEtaBin: 0,1,2
            3. pPtbin: 0~20
            4. input step2.root file name

            mesg:
              {}
            ------------------------------------------------
            '''.format(mesg))
    exit(1)

datacard_template='''
imax *
jmax *
kmax *
---------------

shapes data_obs cat_BDT {ifile} bin_{Sbin.pEta}_{Sbin.jEta}_{Sbin.pPt}/BDT_data_signalRegion
shapes signalMC cat_BDT {ifile} bin_{Sbin.pEta}_{Sbin.jEta}_{Sbin.pPt}/BDT_gjet_signalRegion_norm bin_{Sbin.pEta}_{Sbin.jEta}_{Sbin.pPt}/BDT_gjet_signalRegion_$SYSTEMATIC_norm
shapes bkgShape cat_BDT {ifile} bin_{Bbin.pEta}_{Bbin.jEta}_{Bbin.pPt}/BDT_data_dataSideband_norm


---------------
bin          cat_BDT
observation  -1
------------------------------
bin          cat_BDT    cat_BDT
process      signalMC   bkgShape
process       0          1
rate         -1         -1
------------------------------
shapeUnc shape 1  -
'''

class BinMgr:
    def __init__(self, pETAbin, jETAbin, pPTbin):
        self.pEta = int(pETAbin)
        self.jEta = int(jETAbin)
        self.pPt  = int(pPTbin)
    def SigBin(self):
        return self
    def BkgBin(self):
        if self.pPt > 17:
            from copy import deepcopy
            out = deepcopy(self)
            out.pPt = 17
            return out
        return self


if __name__ == "__main__":
    import os
    try:
        pEtaBin, jEtaBin, pPtBin, ifilename = os.sys.argv[1:5]
        if abs(int(pEtaBin))>1: raise ValueError("pEtaBin is out of range -- "+pEtaBin)
        if abs(int(jEtaBin))>2: raise ValueError("jEtaBin is out of range -- "+jEtaBin)
        if abs(int(pPtBin))>25: raise ValueError("pPtBin  is out of range -- "+pPtBin)
        if 'root' not in ifilename: raise ValueError("input filename is not a root file -- "+ifilename)
    except ValueError as vErr:
        PrintHelp(vErr)
    inputbin = BinMgr(pEtaBin,jEtaBin,pPtBin)


    with open('datacard.txt','w') as ofile:
        ofile.write( datacard_template.format(ifile=ifilename,Sbin = inputbin.SigBin(), Bbin = inputbin.BkgBin()) )
        print("Here is your output datacard : datacard.txt")

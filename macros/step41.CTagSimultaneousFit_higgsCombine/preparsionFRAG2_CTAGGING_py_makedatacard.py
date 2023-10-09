#!/usr/bin/env python3

def WARNING(*args):
    print('[py_makedatacard-WARNING]',*args)
def PrintHelp(mesg):
    print('''
            --------------- input arguments ----------------
            1. getdatadetail.csv

            mesg:
              {}
            ------------------------------------------------
            '''.format(mesg))
    exit(1)

def LOG(*args):
    print('[combineFRAG1_py_makedatacard LOG] ',*args)

datacard_template='''
imax *
jmax *
kmax *
---------------

shapes data_obs cat_0 {ifile} {data0.HistName}
shapes signal_L cat_0 {ifile} {sigL0.HistName} {sigL0.SystName}
shapes signal_C cat_0 {ifile} {sigC0.HistName} {sigC0.SystName}
shapes signal_B cat_0 {ifile} {sigB0.HistName} {sigB0.SystName}
shapes fixDiJet cat_0 {ifile} {fake0.HistName}

shapes data_obs cat_1 {ifile} {data1.HistName}
shapes signal_L cat_1 {ifile} {sigL1.HistName} {sigL1.SystName}
shapes signal_C cat_1 {ifile} {sigC1.HistName} {sigC1.SystName}
shapes signal_B cat_1 {ifile} {sigB1.HistName} {sigB1.SystName}
shapes fixDiJet cat_1 {ifile} {fake1.HistName}

shapes data_obs cat_2 {ifile} {data2.HistName}
shapes signal_L cat_2 {ifile} {sigL2.HistName} {sigL2.SystName}
shapes signal_C cat_2 {ifile} {sigC2.HistName} {sigC2.SystName}
shapes signal_B cat_2 {ifile} {sigB2.HistName} {sigB2.SystName}
shapes fixDiJet cat_2 {ifile} {fake2.HistName}


---------------
bin          cat_0  cat_1  cat_2
observation     -1     -1     -1
------------------------------
bin              cat_0       cat_0       cat_0          cat_0          cat_1       cat_1       cat_1          cat_1          cat_2       cat_2       cat_2          cat_2
process       signal_L    signal_C    signal_B       fixDiJet       signal_L    signal_C    signal_B       fixDiJet       signal_L    signal_C    signal_B       fixDiJet
process       -2          -1           0                    1       -2          -1           0                    1       -2          -1           0                    1
rate          -1          -1          -1     {fakeYield:>16s}       -1          -1          -1     {fakeYield:>16s}       -1          -1          -1     {fakeYield:>16s}
------------------------------
Stat     shape 1 1 1 -  1 1 1 -  1 1 1 -
PUweight shape 1 1 1 -  1 1 1 -  1 1 1 -
'''

class BinMgr:
    def __init__(self, pETAbin, jETAbin, pPTbin):
        self.pEta = int(pETAbin)
        self.jEta = int(jETAbin)
        self.pPt  = int(pPTbin)
    def SigBin(self):
        return self
    def BkgBin(self):
        ### only used in 2016 original pt binning. Because no enough sideband statistics.
        if self.pPt > 17:
            WARNING(f'pt bin={self.pPt}. Which is forced to 17 to increase statistics. ONLY USED FOR 2016 ORIGINAL BINNING')
            from copy import deepcopy
            out = deepcopy(self)
            out.pPt = 17
            return out
        return self
class HistNameMgr:
    def __init__(self, theBIN:BinMgr, varNAME:str, usedNORM=False, additionalNAME=''):
        self.histName = varNAME
        self.b = theBIN
        self.usedNorm = usedNORM
        self.addName = additionalNAME
    @property
    def HistName(self):
        output = f'bin_{self.b.pEta}_{self.b.jEta}_{self.b.pPt}/{self.histName}'+self.addName
        if self.usedNorm: output += '_norm'
        LOG('Used hist name : ', output)
        return output
    @property
    def SystName(self):
        output = f'bin_{self.b.pEta}_{self.b.jEta}_{self.b.pPt}/{self.histName}_$SYSTEMATIC'
        if self.usedNorm: output += '_norm'
        LOG('Used syst name : ', output)
        return output

def H_CentralMC(theBIN,varNAME):
    return HistNameMgr(theBIN, varNAME, True, '_central')
def H_OriginalMC(theBIN,varNAME):
    return HistNameMgr(theBIN, varNAME, True, '_original')
def H_DataHist(theBIN,varNAME):
    return HistNameMgr(theBIN, varNAME,False, '')
def H_DataSideband(theBIN,varNAME):
    return HistNameMgr(theBIN, varNAME, True, '')

def InValidBin(iFILEname:str, inBIN:BinMgr):
    import ROOT
    infile = ROOT.TFile.Open(iFILEname)
    if not infile.Get(f'bin_{inBIN.pEta}_{inBIN.jEta}_{inBIN.pPt}'):
        return True
    return False

def CSV_Binning(csvROW):
    petabin = csvROW['pEtaBin']
    jetabin = csvROW['jEtaBin']
    pptbin  = csvROW['pPtBin']
    return BinMgr(petabin,jetabin,pptbin)

def GetDataCard(iFILEname,inputBIN, fakeYIELD):
    ifilename = iFILEname
    inputbin = inputBIN
    if InValidBin(ifilename, inputbin):
        raise IOError(f'input bin {inputbin.pEta}_{inputbin.jEta}_{inputbin.pPt} does not exist in {ifilename}. Skip this binning')

    data0 = H_DataHist(inputbin, 'jettag0_data_signalRegion')                 ,
    with open(f'datacard_{inputbin.pEta}_{inputbin.jEta}_{inputbin.pPt}.txt','w') as ofile:
        ofile.write( datacard_template.format(
            ifile= ifilename,
            data0 = H_DataHist(inputbin, 'jettag0_data_signalRegion')                 ,
            sigL0 = H_CentralMC(inputbin.SigBin(), 'jettag0_gjet_GJetsL_signalRegion'),
            sigC0 = H_CentralMC(inputbin.SigBin(), 'jettag0_gjet_GJetsC_signalRegion'),
            sigB0 = H_CentralMC(inputbin.SigBin(), 'jettag0_gjet_GJetsB_signalRegion'),
            fake0 = H_DataSideband(inputbin.BkgBin(), 'jettag0_data_dataSideband')    ,

            data1 = H_DataHist(inputbin, 'jettag1_data_signalRegion')                 ,
            sigL1 = H_CentralMC(inputbin.SigBin(), 'jettag1_gjet_GJetsL_signalRegion'),
            sigC1 = H_CentralMC(inputbin.SigBin(), 'jettag1_gjet_GJetsC_signalRegion'),
            sigB1 = H_CentralMC(inputbin.SigBin(), 'jettag1_gjet_GJetsB_signalRegion'),
            fake1 = H_DataSideband(inputbin.BkgBin(), 'jettag1_data_dataSideband')    ,

            data2 = H_DataHist(inputbin, 'jettag2_data_signalRegion')                 ,
            sigL2 = H_CentralMC(inputbin.SigBin(), 'jettag2_gjet_GJetsL_signalRegion'),
            sigC2 = H_CentralMC(inputbin.SigBin(), 'jettag2_gjet_GJetsC_signalRegion'),
            sigB2 = H_CentralMC(inputbin.SigBin(), 'jettag2_gjet_GJetsB_signalRegion'),
            fake2 = H_DataSideband(inputbin.BkgBin(), 'jettag2_data_dataSideband')    ,
            fakeYield = fakeYIELD) )
        print(f"Here is your output datacard : datacard_{inputbin.pEta}_{inputbin.jEta}_{inputbin.pPt}.txt")




if __name__ == "__main__":
    import os
    try:
        inCSVfile = os.sys.argv[1]
        if 'csv' not in inCSVfile: raise IOError('input a csv file')
        if not os.path.exists(inCSVfile): raise IOError(f'input file {inCSVfile} does not exist')
    except IOError as vErr:
        PrintHelp(vErr)

    import csv
    with open(inCSVfile,'r') as inFILE:
        csv_reader = csv.DictReader(inFILE)
        for row in csv_reader:
            inputBIN = CSV_Binning(row)
            iFILEname = row['inFile']
            fakeYIELD = row['fitDiJet']
            GetDataCard(iFILEname,inputBIN, fakeYIELD)

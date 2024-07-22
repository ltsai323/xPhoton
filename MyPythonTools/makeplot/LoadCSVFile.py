#!/usr/bin/env python3
import csv
NULLVAL=1e-100 # small enough, you will find a weird log scale plot

class CSVBinnedValue:
    def __init__(self, pPTbin:str, inVAL:str):
        self.pPtBin = int(pPTbin)
        self.value  = float(inVAL)

def loadcsvfile_fill_nullval(inLIST:list, assignedVAL:float):
    return [ CSVBinnedValue( in_entry.pPtBin, str(assignedVAL) ) for in_entry in inLIST ]
def loadcsvfile_no_nullvalue(inFILEname:str, var:str, pETAbin:int, jETAbin:int):
    with open(inFILEname, 'r') as ifile:
        csv_content = csv.DictReader(ifile)
        return [ CSVBinnedValue(c['pPtBin'],c[var]) for c in csv_content if c['pEtaBin']==str(pETAbin) and c['jEtaBin']==str(jETAbin) ]
def LoadCSVFile(inFILEname:str, var:str, pETAbin:int, jETAbin:int) -> list[CSVBinnedValue]:
    return loadcsvfile_no_nullvalue(inFILEname,var,pETAbin,jETAbin)
def LoadCSVFile_CopyNullEntry(inLIST:list, assignedVAL:float):
    return [ CSVBinnedValue( in_entry.pPtBin, str(assignedVAL) ) for in_entry in inLIST ]

if __name__ == "__main__":
    print('hi')
    a=LoadCSVFile('gjet_NLO_loop_sm_no_b_mass_NNPDF31_nlo_pch_as_0118/MG5result.csv', 'crossSectionC', 0, 0)
    print(a)

#!/usr/bin/env python3

import matplotlib.pyplot as plt
import numpy as np


class BinEntry:
    fityield = 0.
    bkgyield = 0.

    pptbin = 0
    petabin = 0
    jetabin = 0

def IsBin(entry, pETAbin, jETAbin, pPTbin=-1):
    if entry.petabin!= pETAbin: return False
    if entry.jetabin!= jETAbin: return False
    if pPTbin != -1:
        if entry.pptbin != pPTbin:  return False
    return True

def IsEtaBin(entry, pETAbin, jETAbin):
    if entry.petabin!= pETAbin: return False
    if entry.jetabin!= jETAbin: return False
    return True

def DrawPurity(entryList:list, outputNAME:str='', colorCODE:str='black', outLABEL='Purity'):

    import py_pt_ranges_definition
    py_pt_ranges_definition.testmode = 1
    x = sorted(entryList.keys())

    x_vals = py_pt_ranges_definition.PhoPtBinning("2016ReReco")
    for idx in x: print(idx,x_vals[idx])

    sorted_entries = [ entryList[ptbin] for ptbin in x ]
    y = [ entry.fityield/(entry.fityield+entry.bkgyield) for entry in sorted_entries ]

    plt.scatter(x_vals,y, linestyle='-', marker='o', color=colorCODE, label=outLABEL)

    plt.xlabel('photon pt in GeV')
    plt.ylabel('Purity')
    plt.title('Photon yield estimation in $\gamma$+jet channel')
    plt.grid(True)
    plt.legend()
    if outputNAME:
        plt.savefig(outputNAME)
        print('output file : ', outputNAME)


if __name__ == "__main__":
    loadedFitResults = []
    with open('2016ReReco.data.dat','r') as ifile:
        for line in ifile.readlines():
            linecontents = line.strip().split(' ')
            if len(linecontents) <= 1: continue
            entry = BinEntry()
            entry.petabin = int(linecontents[1])
            entry.jetabin = int(linecontents[2])
            entry.pptbin  = int(linecontents[0])
            entry.fityield= float(linecontents[3])
            entry.bkgyield= float(linecontents[5])
            loadedFitResults.append(entry)

    barrelPho_barrelJet = { entry.pptbin:entry for entry in loadedFitResults if IsBin(entry,0,0) }
    barrelPho_endcapJet = { entry.pptbin:entry for entry in loadedFitResults if IsBin(entry,0,1) }
    endcapPho_barrelJet = { entry.pptbin:entry for entry in loadedFitResults if IsBin(entry,1,0) }
    endcapPho_endcapJet = { entry.pptbin:entry for entry in loadedFitResults if IsBin(entry,1,1) }
    plt.clf()
    DrawPurity(barrelPho_barrelJet, outputNAME='out_0_0.pdf', outLABEL='barrelPho barrelJet')
    plt.clf()
    DrawPurity(barrelPho_endcapJet, outputNAME='out_0_1.pdf', outLABEL='barrelPho endcapJet')
    plt.clf()
    DrawPurity(endcapPho_barrelJet, outputNAME='out_1_0.pdf', outLABEL='endcapPho barrelJet')
    plt.clf()
    DrawPurity(endcapPho_endcapJet, outputNAME='out_1_1.pdf', outLABEL='endcapPho endcapJet')

    plt.clf()
    DrawPurity(barrelPho_barrelJet, colorCODE='blue'    , outLABEL='barrelPho barrelJet')
    DrawPurity(barrelPho_endcapJet, colorCODE='red'     , outLABEL='barrelPho endcapJet')
    DrawPurity(endcapPho_barrelJet, colorCODE='orange'  , outLABEL='endcapPho barrelJet')
    DrawPurity(endcapPho_endcapJet, colorCODE='green'   , outLABEL='endcapPho endcapJet')
    plt.savefig('out.pdf')

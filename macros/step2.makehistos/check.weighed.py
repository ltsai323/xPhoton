#!/usr/bin/env python3
import ROOT
import sys

def CheckWeighedStatus( theDIRECTORY, var ):
    hNormal = theDIRECTORY.Get(var)
    hWeight = theDIRECTORY.Get(var+'_weighed')

    int_normal = hNormal.Integral()
    int_weight = hWeight.Integral()
    diff = abs(int_normal-int_weight) / int_normal * 100.
    print( f'[INFO] {var} integration before weighting is {int_normal:.2e}. After weighting is {int_weight:.2e}. (Diff {diff:.2f}%)')

if __name__ == "__main__":
    inFile = ROOT.TFile.Open(sys.argv[1])

    CheckWeighedStatus( inFile.Get('DeepFlavour.bScore'), 'hsign' )
    CheckWeighedStatus( inFile.Get('DeepFlavour.bScore'), 'hfake' )


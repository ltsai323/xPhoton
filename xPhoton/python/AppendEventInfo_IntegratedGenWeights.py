#!/usr/bin/env python2

import ROOT

def IntegratedGenWeights(filename):
    f=ROOT.TFile.Open(filename)
    nt=f.Get('genweightsummary')

    Sum=0
    for a in nt:
        Sum+=a.sumupgenweight
    return Sum

def MergeNeeded( filedict ):
    if len( filedict.keys() ) > 1:
        return True
    return False



if __name__ == '__main__':
    import sys
    inputfiles=sys.argv[2:]

    for rootfile in inputfiles:
        print '%s, %d' % ( rootfile, IntegratedGenWeights(rootfile) )

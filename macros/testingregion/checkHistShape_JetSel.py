#!/usr/bin/env python2

import ROOT


# hist0 : hist before selection
# hist1 : hist after  selection
# scale hist0 to hist1. And check the shape

def histComp(hist0, hist1):
    sumH0=hist0.Integral()
    sumH1=hist1.Integral()
    if fabs(sumH0) < 1e-6: raise ValueError('Nothing in histogram. Not able to make comparison')
    scalefactor=hist1.Integral() / hist0.Integral()
    hist1.Scale(scalefactor)





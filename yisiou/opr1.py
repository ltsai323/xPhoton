#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)


for num in range(1, 2):

    string = 'root.exe -q mc.root btag_MC.C'
    print string
    os.system(string)

    string = 'root.exe -q data.root btag_data.C'
    print string
    os.system(string)

    string = 'root.exe -q .x fit_btag.C'
    print string
    os.system(string)
    
    #after putting the weight of "three flavour" and "isMatched and notMatched" into plot.C

    #string = 'root.exe mc.root plot.C'
    #print string
    #os.system(string)


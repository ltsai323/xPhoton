#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)


for num in range(1, 2):

    string = 'root.exe -q mc.root hist_MC.C'
    print string
    os.system(string)

    string = 'root.exe -q data.root hist_data.C'
    print string
    os.system(string)

    string = 'root.exe -q hist.root plot.C'
    print string
    os.system(string)




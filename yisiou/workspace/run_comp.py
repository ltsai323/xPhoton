#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)


for ptbin in range(0, 20):

    string = "root.exe -q 'comparison_n1n2.C("+str(ptbin)+")'"
    print(string)
    os.system(string)

#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)

ptbin = 6

string0 = "root.exe -q 'clousure_prod.C("+str(ptbin)+")'"

print(string0)
os.system(string0)

for num in range(0, 500):
    print('processing... '+str(num))

    string1 = "root.exe -q 'prod.C("+str(ptbin)+")'"

    string2 = 'python pull.py '+str(ptbin)

    string3 = 'root.exe -q pull_info.C'

    print string1
    os.system(string1)
    print(string2)
    os.system(string2)
    print string3
    os.system(string3)

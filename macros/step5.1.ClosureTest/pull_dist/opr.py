#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)

for num in range(0, 300):
    print('processing... '+str(num))
    string0 = 'root.exe -q pull_prod.C'

    string1 = 'python pull.py'

    string2 = 'root.exe -q pull_info.C'

    #string3 = "root.exe -q 'Draw_svxmass.C("+str(num)+")'"

    print string0
    os.system(string0)
    print(string1)
    os.system(string1)
    print string2
    os.system(string2)
    #print(string3)
    #os.system(string3)

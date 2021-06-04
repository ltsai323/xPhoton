#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
ROOT.gROOT.SetBatch(True)
ROOT.gROOT.LoadMacro("MakeHisto.C+")

# HACK
if len(argv) != 2:
    print ("USAGE: %s [1 or 2 (MC or data)]" %(argv[0]))
    exit(1)

t = ROOT.MakeHisto(int(argv[1]))
t.Loop()

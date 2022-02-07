#!/usr/bin/env python2
import ROOT
import sys
import os

f=ROOT.TFile.Open(sys.argv[1])
newf=ROOT.TFile('recover.root', 'recreate')
t=f.Get('t')

newf.cd()
t.CloneTree()
newf.Write()
newf.Close()
f.Close()

rootorig='orig/' + sys.argv[1].split('/')[-1]
os.rename(sys.argv[1], rootorig)
os.rename('recover.root', sys.argv[1])

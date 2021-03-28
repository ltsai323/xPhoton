#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os

# original code
#import ROOT
#ROOT.gROOT.SetBatch(True)

#for ff in range(1, 2):
#    print "get file %d" %(ff)
#    fname = "ggtree_mc_%d.root" %(ff)
#    print fname
#
#    #os.system('xrdcp root://eoscms.cern.ch//eos/cms/store/group/phys_smp/ggNtuples/13TeV/mc/V10_02_10_04/job_autumn18_gjet_pt40_MGG_80toInf/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/crab_job_autumn18_gjet_pt40_MGG_80toInf/190807_093654/0000/%s %s' %(fname, fname) )
#    runningCommandContent = "root.exe -b -q run.C\(%d\)" %(ff)
#    print runningCommandContent
#
#    os.system(runningCommandContent)
#    #os.system(' rm -f %s' %(fname))


# my new code
lines=[
#'root://se01.grid.nchc.org.tw//cms/store/user/ltsai/ggAnalysis/2016miniAODv3/jetSubVtxInfo/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8/crab_GJet_Pt20toInf_DoubleEMEnriched_MGG_40to80_TuneCP5_13TeV_Pythia8/201130_100629/0000/ggtree_mc_1.root',
'root://se01.grid.nchc.org.tw//cms/store/user/ltsai/ggAnalysis/2016miniAODv3/jetSubVtxInfo/SinglePhoton/crab_UL2016RunH/210225_071836/0000/ggtree_data_1.root',
]

commandContentOrig  = 'root -b -q src/run.C\(\\\"%s\\\",%d\)'
commandContent = 'root -b -q src/run2.C\(\\\"%s\\\",%d\) ; ls -lh | grep root'
if len(argv) > 1:
   inFile=argv[1]
   with open(inFile, 'r') as ifile:
      nchcPrefix='root://se01.grid.nchc.org.tw/'
      for remoteDir in ifile.readlines():
         fileID=remoteDir.split('_')[-1].split('.')[0]
         commandExec=commandContent % ( nchcPrefix+remoteDir.strip(), int(fileID) )
         print commandExec
         os.system(commandExec)
else:
##with open('crabMCList_amcatnlo_PUMoriond17_Pt100To250_evt2v2', 'r') as ifile:',
#with open('mcList_amcatnlo_100To250', 'r') as ifile:
#
#    lines=ifile.readlines()
   for rootFile in lines:

      b=rootFile.split('_')[-1]
      fileID=b.split('.')[0]


      # original shell command : 'root -b -q src/run.C("myfile.root", 1)'
      commandContent = commandContent%(rootFile.strip(),int(fileID))
      #runningCommandContent = 'root -b -q src/run.C\(\\\"file://%s\\\",%d\)' %(rootFile.strip(),0)
      print commandContent

      os.system(commandContent)

      #exit()


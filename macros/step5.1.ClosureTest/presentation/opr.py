#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)

os.system('mkdir -p ./plots_toy')
file = ROOT.TFile('./toy.root')
hFake = file.Get("toymc_BvsAll_FAKE")
nFake = hFake.Integral()
file.Close()

for ptbin in range(6, 7):
    os.system("root.exe -q 'toyfit_preparation.C("+str(ptbin)+")'")
    file = ROOT.TFile('./toy.root')
    hFake = file.Get("toymc_BvsAll_FAKE")
    nFake = hFake.Integral()
    file.Close()
    outfile = open('auto_datacard.txt',"w")
    outfile.write("imax * \n")
    outfile.write("jmax * \n")
    outfile.write("kmax * \n")
    outfile.write("--------------- \n")
    outfile.write("shapes sigB  cat0 ./toy.root toymc_BvsAll_B \n")
    outfile.write("shapes sigC  cat0 ./toy.root toymc_BvsAll_C \n")
    outfile.write("shapes bkgL  cat0 ./toy.root toymc_BvsAll_L \n")
    outfile.write("shapes fake  cat0 ./toy.root toymc_BvsAll_FAKE \n")
    outfile.write("shapes sigB  cat1 ./toy.root toymc_CvsL_B \n")
    outfile.write("shapes sigC  cat1 ./toy.root toymc_CvsL_C \n")
    outfile.write("shapes bkgL  cat1 ./toy.root toymc_CvsL_L \n")
    outfile.write("shapes fake  cat1 ./toy.root toymc_CvsL_FAKE \n")
    outfile.write("shapes sigB  cat2 ./toy.root toymc_CvsB_B \n")
    outfile.write("shapes sigC  cat2 ./toy.root toymc_CvsB_C \n")
    outfile.write("shapes bkgL  cat2 ./toy.root toymc_CvsB_L \n")
    outfile.write("shapes fake  cat2 ./toy.root toymc_CvsB_FAKE \n")
    outfile.write("\n")
    outfile.write("shapes data_obs cat0 ./toy.root toydata_BvsAll \n"  ) 
    outfile.write("shapes data_obs cat1 ./toy.root toydata_CvsL \n"  ) 
    outfile.write("shapes data_obs cat2 ./toy.root toydata_CvsB \n"  ) 
    outfile.write("--------------- \n")
    outfile.write("bin          cat0    cat1    cat2 \n")
    outfile.write("observation  -1      -1      -1   \n")
    outfile.write("------------------------------ \n")
    outfile.write("bin          cat0    cat0    cat0    cat0    cat1    cat1    cat1    cat1    cat2    cat2    cat2    cat2 \n")
    outfile.write("process      sigB    sigC    bkgL    fake    sigB    sigC    bkgL    fake    sigB    sigC    bkgL    fake \n")
    outfile.write("process      -1      0       1       2       -1      0       1       2       -1      0       1       2 \n")
    outfile.write("rate         1       1       1       %f      1       1       1       %f      1       1       1       %f \n" %(nFake,nFake,nFake) )
    outfile.write("--------------------------------     \n")

    outfile.close()

    string1 = 'text2workspace.py auto_datacard.txt -o ws.root -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO "map=.*/sigB.*:mu1[1000,0,500000]" --PO "map=.*/sigC.*:mu2[1000,0,500000]" --PO "map=.*/bkgL.*:mu3[1000,0,500000]" --PO "map=.*/fake.*:mu4[1,1,1]"'

    string2 = 'combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on'

    string3 = 'PostFitShapesFromWorkspace -d auto_datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root -o postfit.root -m 120 -f multidimfitTest.root:fit_mdf --postfit --print'

    string4 = "root.exe -q 'Draw_svxmass.C("+str(ptbin)+")'"

    string5 = "rm multidimfitTest.root higgsCombineTest.MultiDimFit.mH120.root combine_logger.out ws.root postfit.root"

    print(string1)
    os.system(string1)
    print(string2)
    os.system(string2)
    print(string3)
    os.system(string3)
    print(string4)
    os.system(string4)
    print(string5)
    os.system(string5)

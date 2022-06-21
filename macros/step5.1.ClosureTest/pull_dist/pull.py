#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)


for num in range(6, 7):
    outfile = open('auto_datacard.txt',"w")
    outfile.write("imax * \n")
    outfile.write("jmax * \n")
    outfile.write("kmax * \n")
    outfile.write("--------------- \n")
    outfile.write("shapes sigB	cat0 ./pull.root tag0_B \n")
    outfile.write("shapes sigC  cat0 ./pull.root tag0_C \n")
    outfile.write("shapes bkgL	cat0 ./pull.root tag0_L \n")
    outfile.write("shapes sigB  cat1 ./pull.root tag1_B \n")
    outfile.write("shapes sigC  cat1 ./pull.root tag1_C \n")
    outfile.write("shapes bkgL  cat1 ./pull.root tag1_L \n")
    outfile.write("shapes sigB  cat2 ./pull.root tag2_B \n")
    outfile.write("shapes sigC  cat2 ./pull.root tag2_C \n")
    outfile.write("shapes bkgL  cat2 ./pull.root tag2_L \n")
    #outfile.write("shapes sigB  cat3 ./pull.root h_jettag_0_%d_0_2_3 \n" %(num) )
    #outfile.write("shapes sigC  cat3 ./pull.root h_jettag_0_%d_0_1_3 \n" %(num) )
    #outfile.write("shapes bkgL  cat3 ./pull.root h_jettag_0_%d_0_0_3 \n" %(num) )
    outfile.write("\n")
    outfile.write("shapes data_obs cat0 ./random_toy.root btag \n" )
    outfile.write("shapes data_obs cat1 ./random_toy.root cvsl \n" )
    outfile.write("shapes data_obs cat2 ./random_toy.root cvsb \n" )
    #outfile.write("shapes data_obs cat3 ./toy.root h_jettag_0_%d_0_0_3 \n" %(num) )
    outfile.write("--------------- \n")
    #outfile.write("bin          cat0    cat1    cat2    cat3 \n")
    #outfile.write("observation  -1      -1      -1      -1 \n")
    outfile.write("bin		cat0	cat1	cat2 \n")
    outfile.write("observation	-1	-1	-1   \n")
    outfile.write("------------------------------ \n")
    #outfile.write("bin		cat0	cat0	cat0	cat1    cat1    cat1	cat2	cat2	cat2	cat3	cat3	cat3 \n")
    #outfile.write("process	sigB	sigC	bkgL	sigB    sigC    bkgL	sigB	sigC	bkgL	sigB	sigC	bkgL \n")
    #outfile.write("process 	-1	0	1	-1	0	1 	-1	0	1	-1	0	1 \n")
    #outfile.write("rate		1	1	1	1	1	1	1	1	1	1	1	1 \n")
    outfile.write("bin          cat0    cat0    cat0    cat1    cat1    cat1    cat2    cat2    cat2 \n")
    outfile.write("process      sigB    sigC    bkgL    sigB    sigC    bkgL    sigB    sigC    bkgL \n")
    outfile.write("process      -1      0       1       -1      0       1       -1      0       1    \n")
    outfile.write("rate         1       1       1       1       1       1       1       1       1    \n")
    outfile.write("--------------------------------     \n")
    #outfile.write("sigma shape  -       -       1.0     -       -       1.0     -       -       1.0     -       -       - \n")
    #outfile.write("alpha shape  -       1.0     -       -       1.0     -       -       1.0     -       -       -       - \n")
    #outfile.write("beta  shape  1.0     -       -       1.0     -       -       1.0     -       -       -       -       - \n")
    #outfile.write("sigma shape  -       -       1.0     -       -       1.0     -       -    	1.0 \n")
    #outfile.write("alpha shape  -       1.0     -       -       1.0     -       -       1.0     -   \n")
    #outfile.write("beta  shape  1.0     -       -       1.0     -       -       1.0     -       -   \n")
    outfile.close()


    string0 = 'text2workspace.py auto_datacard.txt -o ws.root -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO "map=.*/sigB.*:mu1[1000,0,1000000]" --PO "map=.*/sigC.*:mu2[1000,0,1000000]" --PO "map=.*/bkgL.*:mu3[1000,0,10000000]"'

    string1 = 'combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on'

    string2 = 'PostFitShapesFromWorkspace -d auto_datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root -o postfit.root -m 120 -f multidimfitTest.root:fit_mdf --postfit --print'

    #string3 = "root.exe -q pull_info.C"
    #string3 = "root.exe -q 'Draw_svxmass.C("+str(num)+")'"

    print string0
    os.system(string0)
    print(string1)
    os.system(string1)
    print string2
    os.system(string2)
    #print(string3)
    #os.system(string3)


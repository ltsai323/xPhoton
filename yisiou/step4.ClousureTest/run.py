#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)


for num in range(6, 7):

    file = ROOT.TFile('./toy_mc.root')
    hsigB0 = file.Get("tag0_B")
    hsigC0 = file.Get("tag0_C")
    hbkgL0 = file.Get("tag0_L")
    hsigB0entry = hsigB0.Integral()
    hsigC0entry = hsigC0.Integral()
    hbkgL0entry = hbkgL0.Integral()
    hsigB1 = file.Get("tag1_B")
    hsigC1 = file.Get("tag1_C")
    hbkgL1 = file.Get("tag1_L")
    hsigB1entry = hsigB1.Integral()
    hsigC1entry = hsigC1.Integral()
    hbkgL1entry = hbkgL1.Integral()
    hsigB2 = file.Get("tag2_B")
    hsigC2 = file.Get("tag2_C")
    hbkgL2 = file.Get("tag2_L")
    hsigB2entry = hsigB2.Integral()
    hsigC2entry = hsigC2.Integral()
    hbkgL2entry = hbkgL2.Integral()

    file.Close()


    outfile = open('auto_datacard.txt',"w")
    outfile.write("imax * \n")
    outfile.write("jmax * \n")
    outfile.write("kmax * \n")
    outfile.write("--------------- \n")
    outfile.write("shapes sigB  cat0 ./toy_mc.root tag0_B tag0_B_$SYSTEMATIC \n")
    outfile.write("shapes sigC  cat0 ./toy_mc.root tag0_C tag0_C_$SYSTEMATIC \n")
    outfile.write("shapes bkgL  cat0 ./toy_mc.root tag0_L tag0_L_$SYSTEMATIC \n")
    outfile.write("shapes sigB  cat1 ./toy_mc.root tag1_B tag1_B_$SYSTEMATIC \n")
    outfile.write("shapes sigC  cat1 ./toy_mc.root tag1_C tag1_C_$SYSTEMATIC \n")
    outfile.write("shapes bkgL  cat1 ./toy_mc.root tag1_L tag1_L_$SYSTEMATIC \n")
    outfile.write("shapes sigB  cat2 ./toy_mc.root tag2_B tag2_B_$SYSTEMATIC \n")
    outfile.write("shapes sigC  cat2 ./toy_mc.root tag2_C tag2_C_$SYSTEMATIC \n")
    outfile.write("shapes bkgL  cat2 ./toy_mc.root tag2_L tag2_L_$SYSTEMATIC \n")
    outfile.write("shapes sigB  cat3 ./toy_mc.root tag3_B \n")
    outfile.write("shapes sigC  cat3 ./toy_mc.root tag3_C \n")
    outfile.write("shapes bkgL  cat3 ./toy_mc.root tag3_L \n")
    outfile.write("\n")
    outfile.write("shapes data_obs cat0 ./toy_data.root tag0 \n"  ) 
    outfile.write("shapes data_obs cat1 ./toy_data.root tag1 \n"  ) 
    outfile.write("shapes data_obs cat2 ./toy_data.root tag2 \n"  ) 
    outfile.write("shapes data_obs cat3 ./toy_data.root tag3 \n"  ) 
    outfile.write("--------------- \n")
    #outfile.write("bin          cat0    cat1    cat2    cat3 \n")
    #outfile.write("observation  -1      -1      -1      -1 \n")
    outfile.write("bin          cat0    cat1    cat2 \n")
    outfile.write("observation  -1      -1      -1   \n")
    outfile.write("------------------------------ \n")
    #outfile.write("bin         cat0    cat0    cat0    cat1    cat1    cat1    cat2    cat2    cat2    cat3    cat3    cat3 \n")
    #outfile.write("process     sigB    sigC    bkgL    sigB    sigC    bkgL    sigB    sigC    bkgL    sigB    sigC    bkgL \n")
    #outfile.write("process     -1      0       1       -1      0       1       -1      0       1       -1      0       1 \n")
    #outfile.write("rate                1       1       1       1       1       1       1       1       1       1       1       1 \n")
    outfile.write("bin          cat0    cat0    cat0    cat1    cat1    cat1    cat2    cat2    cat2 \n")
    outfile.write("process      sigB    sigC    bkgL    sigB    sigC    bkgL    sigB    sigC    bkgL \n")
    outfile.write("process      -1      0       1       -1      0       1       -1      0       1    \n")
    outfile.write("rate         %f      %f      %f      %f      %f      %f      %f      %f      %f    \n" %(hsigB0entry, hsigC0entry, hbkgL0entry, hsigB1entry, hsigC1entry, hbkgL1entry, hsigB2entry, hsigC2entry, hbkgL2entry))
    outfile.write("--------------------------------     \n")
    #outfile.write("sigma shape  -       -       1.0     -       -       1.0     -       -       1.0     -       -       - \n")
    #outfile.write("sigma shape  -       -       -       -       -       -       -       -       -      -       -       - \n")
    #outfile.write("alpha shape  -       1.0     -       -       1.0     -       -       1.0     -       -       -       - \n")
    #outfile.write("alpha shape  -       -       -       -       -       -       -       -       -       -       -       - \n")
    #outfile.write("beta  shape  1.0     -       -       1.0     -       -       1.0     -       -       -       -       - \n")
    #outfile.write("beta  shape  -       -       -       -       -       -       -       -       -       -       -       - \n")

    #outfile.write("sigma shape  -       -       1.0     -       -       1.0     -       -       1.0 \n")
    outfile.write("sigma shape  -       -       -       -       -       -       -       -       - \n")
    #outfile.write("alpha shape  -       1.0     -       -       1.0     -       -       1.0     -   \n")
    outfile.write("alpha shape  -       -       -       -       -       -       -       -       -   \n")
    #outfile.write("beta  shape  1.0     -       -       1.0     -       -       1.0     -       -   \n")
    outfile.write("beta  shape  -       -       -       -       -       -       -       -       -   \n")



    outfile.close()

    string00 = "root.exe -q 'clousure_prod.C("+str(num)+")'"

    string0 = 'text2workspace.py auto_datacard.txt -o ws.root -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO "map=.*/sigB.*:mu1[1000,0,1000000]" --PO "map=.*/sigC.*:mu2[1000,0,1000000]" --PO "map=.*/bkgL.*:mu3[1000,0,5000000]"'

    string1 = 'combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on'

    string2 = 'PostFitShapesFromWorkspace -d auto_datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root -o postfit.root -m 120 -f multidimfitTest.root:fit_mdf --postfit --print'

    #string3 = "root.exe -q 'Draw_fit_postfit.C("+str(num)+")'"
    string3 = "root.exe -q 'Draw_svxmass.C("+str(num)+")'"


    print string00
    os.system(string00)
    print string0
    os.system(string0)
    print(string1)
    os.system(string1)
    print string2
    os.system(string2)
    print(string3)
    os.system(string3)


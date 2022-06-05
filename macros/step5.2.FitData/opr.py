#!/usr/bin/env python
import re
from sys import argv, stdout, stderr, exit
from optparse import OptionParser

import os
import ROOT
import sys
ROOT.gROOT.SetBatch(True)

str0 = "mkdir -p ./plots_fitdata"
print(str0)
os.system(str0)

str1 = "rm -rf Nfitted.txt"
print(str1)
os.system(str1)

str2 = "touch Nfitted.txt"
print(str2)
os.system(str2)


for ptbin in range(6, 7):

    string0 = "root.exe -q 'data_preparation.C("+str(ptbin)+")'"
    print(string0)
    os.system(string0)

    file = ROOT.TFile('./templates.root')
    hbkg = file.Get("MC_tag0_FAKE")
    bkgentries = hbkg.Integral()
    file.Close()

    outfile = open('auto_datacard.txt',"w")
    outfile.write("imax * \n")
    outfile.write("jmax * \n")
    outfile.write("kmax * \n")
    outfile.write("--------------- \n")
    outfile.write("shapes sigB  cat0 ./templates.root MC_tag0_B \n")
    outfile.write("shapes sigC  cat0 ./templates.root MC_tag0_C \n")
    outfile.write("shapes bkgL  cat0 ./templates.root MC_tag0_L \n")
    outfile.write("shapes fake  cat0 ./templates.root MC_tag0_FAKE \n")
    outfile.write("shapes sigB  cat1 ./templates.root MC_tag1_B \n")
    outfile.write("shapes sigC  cat1 ./templates.root MC_tag1_C \n")
    outfile.write("shapes bkgL  cat1 ./templates.root MC_tag1_L \n")
    outfile.write("shapes fake  cat1 ./templates.root MC_tag1_FAKE \n")
    outfile.write("shapes sigB  cat2 ./templates.root MC_tag2_B \n")
    outfile.write("shapes sigC  cat2 ./templates.root MC_tag2_C \n")
    outfile.write("shapes bkgL  cat2 ./templates.root MC_tag2_L \n")
    outfile.write("shapes fake  cat2 ./templates.root MC_tag2_FAKE \n")
    outfile.write("shapes sigB  cat3 ./templates.root MC_tag3_B \n")
    outfile.write("shapes sigC  cat3 ./templates.root MC_tag3_C \n")
    outfile.write("shapes bkgL  cat3 ./templates.root MC_tag3_L \n")
    outfile.write("shapes fake  cat3 ./templates.root MC_tag3_FAKE \n")
    outfile.write("\n")
    outfile.write("shapes data_obs cat0 ./templates.root DATA_tag0 \n"  ) 
    outfile.write("shapes data_obs cat1 ./templates.root DATA_tag1 \n"  ) 
    outfile.write("shapes data_obs cat2 ./templates.root DATA_tag2 \n"  ) 
    outfile.write("shapes data_obs cat3 ./templates.root DATA_tag3 \n"  ) 
    outfile.write("--------------- \n")
    outfile.write("bin          cat0    cat1    cat2 \n")
    outfile.write("observation  -1      -1      -1   \n")
    outfile.write("------------------------------ \n")
    outfile.write("bin          cat0    cat0    cat0    cat0    cat1    cat1    cat1    cat1    cat2    cat2    cat2    cat2 \n")
    outfile.write("process      sigB    sigC    bkgL    fake    sigB    sigC    bkgL    fake    sigB    sigC    bkgL    fake \n")
    outfile.write("process      -1      0       1       2       -1      0       1       2       -1      0       1       2 \n")
    outfile.write("rate         1       1       1       %f      1       1       1       %f      1       1       1       %f \n" %(bkgentries,bkgentries,bkgentries) )
    outfile.write("--------------------------------     \n")

    outfile.close()


    #string0 = "root.exe -q 'data_preparation.C("+str(ptbin)+")'"

    string1 = 'text2workspace.py auto_datacard.txt -o ws.root -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel --PO "map=.*/sigB.*:mu1[1000,0,1000000]" --PO "map=.*/sigC.*:mu2[1000,0,1000000]" --PO "map=.*/bkgL.*:mu3[1000,0,5000000]" --PO "map=.*/fake.*:mu4[1000,1,1]"'

    string2 = 'combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on'

    string3 = 'PostFitShapesFromWorkspace -d auto_datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root -o postfit.root -m 120 -f multidimfitTest.root:fit_mdf --postfit --print'

    string4 = "root.exe -q 'Draw_svxmass.C("+str(ptbin)+")'"


    #print(string0)
    #os.system(string0)
    print(string1)
    os.system(string1)
    print(string2)
    os.system(string2)
    print(string3)
    os.system(string3)
    print(string4)
    os.system(string4)


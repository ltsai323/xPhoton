#!/usr/bin/env sh

ifile=$2
tag=$1

root -b $ifile <<EOF
TTree* k = t
TFile* newfile = new TFile("reduced${tag}.root", "RECREATE")
TTree* newtree = (TTree*) k->CloneTree(10000)
newfile->cd()
newtree->Write()
newfile->Close()
EOF


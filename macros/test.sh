#!/usr/bin/env sh

file1=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/sigpythia.root
file2=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/SigPythia.root

root -b <<EOF
TCanvas* c1 = new TCanvas("c","", 700,1400)
c1->Divide(1,2)
c1->cd(1)

TFile* f1 = TFile::Open("$file1")
TTree* t1 = (TTree*) f1->Get("t")
t1->Draw("mva", "isMatched==1")

c1->cd(2)

//TFile* f2 = TFile::Open("$file2")
//TTree* t2 = (TTree*) f2->Get("t")
t1->Draw("mva_nocorr", "isMatched==1")

c1->SaveAs("checkplot_mva.png")
EOF

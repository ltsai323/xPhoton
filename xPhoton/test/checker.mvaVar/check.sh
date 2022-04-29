#!/usr/bin/env sh

ifile=$1
tag=$2

root -b $ifile <<EOF
t->Draw("calib_mva")
c1->SaveAs("mva${tag}.png")
EOF

#!/usr/bin/env sh
datafile=$1


label=data
ifile=$datafile
isMC=false
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC)
t.Loop(1)
EOF

#!/usr/bin/env sh
datafile=$1
signfile=$2
fakefile=$3

echo "used data file: $datafile"
echo "used sign file: $signfile"
echo "used fake file: $fakefile"

sleep 5

label=data
ifile=$datafile
isMC=false
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC)
t.Loop(1)
EOF

label=sig
ifile=$signfile
isMC=true
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC)
t.Loop(1)
EOF


label=QCD
ifile=$fakefile
isMC=true

root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC)
t.Loop(1)
EOF

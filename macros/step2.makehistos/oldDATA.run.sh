#!/usr/bin/env sh
datafile=new2016.data.root
signfile=new2016.sign.root
fakefile=

echo "used data file: $datafile"
echo "used sign file: $signfile"
echo "used fake file: $fakefile"

sleep 5

label=data
ifile=$datafile
isMC=false
root -b <<EOF
.L oldDATA.MakeHisto.C
MakeHisto t("$ifile","$label",$isMC, 1)
t.Loop(1)
EOF

label=sig
ifile=$signfile
isMC=true
root -b <<EOF
.L oldDATA.MakeHisto.C
MakeHisto t("$ifile","$label",$isMC, 0)
t.Loop(1)
EOF


#label=QCD
#ifile=$fakefile
#isMC=true
#
#root -b <<EOF
#.L oldDATA.MakeHisto.C+
#MakeHisto t("$ifile","$label",$isMC, 1)
#t.Loop(1)
#EOF

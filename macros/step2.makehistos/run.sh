#!/usr/bin/env sh
datafile=$1
signfile=$2
fakefile=$3
USEHLT=1

echo "used data file: $datafile"
echo "used sign file: $signfile"
echo "used fake file: $fakefile"
echo "Data and MC use HLT ? $USEHLT"

sleep 5

label=data
ifile=$datafile
isMC=false
if [ "$datafile" != "" ]; then
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC, $USEHLT)
t.SetDataEra("2016ReReco")
t.Loop(1)
EOF
fi

label=sig
ifile=$signfile
isMC=true
if [ "$signfile" != "" ]; then
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC,0)
t.Loop(1)
EOF
fi


label=QCD
ifile=$fakefile
isMC=true

if [ "$fakefile" != "" ]; then
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC,$USEHLT)
t.SetDataEra("2016ReReco")
t.Loop(1)
EOF
fi

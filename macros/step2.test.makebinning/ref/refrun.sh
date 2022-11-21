#!/usr/bin/env sh
datafile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.data.root
fakefile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.QCD.root
signfile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.sigMC.root
USEHLT=1


label=data
ifile=$datafile
isMC=false
if [ "$datafile" != "" ]; then
root -b <<EOF
.L ../../step2.makehistos/MakeHisto.C+
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
.L ../../step2.makehistos/MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC,0)
t.Loop(1)
EOF
fi


label=QCD
ifile=$fakefile
isMC=true

if [ "$fakefile" != "" ]; then
root -b <<EOF
.L ../../step2.makehistos/MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC,$USEHLT)
t.Loop(1)
EOF
fi

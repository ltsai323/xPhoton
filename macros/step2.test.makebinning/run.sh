#!/usr/bin/env sh
#datafile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.data.root
#fakefile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.QCD.root
#signfile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.sigMC.root
USEHLT=1

#fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root
datafile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.data.root
fakefile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.QCD.root
signfile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.sigMC.root

label=data
ifile=$datafile
isMC=false
if [ "$datafile" != "" ]; then
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC, $USEHLT)
t.SetDataEra("2016ReReco")
std::cout << "hi start!\n";
t.Loop(2)
EOF
fi

label=sig
ifile=$signfile
isMC=true
if [ "$signfile" != "" ]; then
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC,0)
t.Loop(2)
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
t.Loop(2)
EOF
fi

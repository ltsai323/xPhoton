#!/usr/bin/env sh
isMC=false
mkdir -p data ; cd data
root -b <<EOF
.L ../MakeHisto.C+
MakeHisto t("/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root","data",$isMC)
t.Loop(1)
EOF
mv makehisto_data.root makehisto_datatest.root


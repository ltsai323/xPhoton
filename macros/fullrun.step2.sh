#!/usr/bin/env sh
datafile=/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root
signfile=/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root
fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root

cd step2.makehistos
sh run.sh $datafile $signfile $fakefile
mv makehisto*.root storeroot/

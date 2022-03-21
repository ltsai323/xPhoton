#!/usr/bin/env sh
datafile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/data.root
fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/qcdmadgraph.root
signfile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/sigmadgraph.root

cd step2.makehistos
sh run.sh $datafile $signfile $fakefile
mv makehisto*.root ..

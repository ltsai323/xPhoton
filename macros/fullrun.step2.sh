#!/usr/bin/env sh
datafile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/data.root
fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/qcdpythia.root
signfile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/sigpythia.root

cd step2.makehistos
sh run.sh $datafile $signfile $fakefile
mv makehisto*.root ..

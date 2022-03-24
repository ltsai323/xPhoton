#!/usr/bin/env sh
datafile=hi.root
signfile=hj.root
fakefile=hk.root

cd step2.makehistos/run.sh $datafile $signfile $fakefile
sh run.sh
mv makehisto*.root storeroot/

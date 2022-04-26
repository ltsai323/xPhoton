#!/usr/bin/env sh
datafile=hi.root
signfile=hj.root
fakefile=hk.root

sh run.sh $datafile $signfile $fakefile
mv makehisto*.root storeroot/

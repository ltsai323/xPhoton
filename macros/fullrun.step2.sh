#!/usr/bin/env sh
if [ "$1" == "" ]; then
    echo 'use files listed internally'
    datafile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/data.root
    fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/qcdpythia.root
    signfile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/sigpythia.root
else
    echo 'use files externally'
    source $1
fi
echo "file list:"
echo "data : $datafile"
echo "sign : $signfile"
echo "fake : $fakefile"
sleep 2


cd step2.makehistos
sh run.sh $datafile $signfile $fakefile
mv makehisto*.root ..

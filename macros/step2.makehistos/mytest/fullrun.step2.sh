#!/usr/bin/env sh
if [ "$1" == "" ]; then
    echo 'use files listed internally'
    datafile=/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root
    fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root
    signfile=/home/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root
else
    echo 'use files externally'
    source $1
fi
echo "file list:"
echo "data : $datafile"
echo "sign : $signfile"
echo "fake : $fakefile"
sleep 2

# cleaning workspace
touch makehisto.root; /bin/rm makehisto*.root

cd ../
# cleaning workspace
touch makehisto.root; /bin/rm makehisto*.root

sh run.sh $datafile $signfile $fakefile
cd -
mv ../makehisto*.root .

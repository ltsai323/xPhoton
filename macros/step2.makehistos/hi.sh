#!/usr/bin/env sh
datafill=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/data.root
fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/qcdmadgraph.root
signfile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/sigmadgraph.root

sh test.sh $datafile $signfile $fakefile

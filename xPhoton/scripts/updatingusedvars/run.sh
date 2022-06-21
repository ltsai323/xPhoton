#!/usr/bin/env sh
for file in /home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/qcdmadgraph.root /home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/qcdpythia.root /home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/sigmadgraph.root /home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/sigpythia.root;
do
    echo $file
    sh xphotonInfoUpdate.sh ${file} &
    sleep 180
done

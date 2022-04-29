#!/usr/bin/env sh
cat > fullrun.inputfiles.conf <<EOF
datafile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/data.root
fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/qcdpythia.root
signfile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/sigpythia.root
EOF


sh fullrun.step2.sh fullrun.inputfiles.conf
sh fullrun.step3.sh
sh fullrun.step4.sh

#!/usr/bin/env sh
cat > fullrun.inputfiles.conf <<EOF
datafile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_data.root
fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_qcdpythia.root
signfile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_sigpythia.root
EOF

#datafile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_data.root
#fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_qcdmadgraph.root
#signfile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_sigmadgraph.root
/bin/rm *.tar


sh fullrun.step2.sh $PWD/fullrun.inputfiles.conf
sh fullrun.step3.sh
sh fullrun.step4.sh

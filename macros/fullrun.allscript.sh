#!/usr/bin/env sh
cat > fullrun.inputfiles.conf <<EOF
datafile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_data.root
fakefile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_qcdpythia.root
signfile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_sigpythia.root
EOF
#datafile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_data.root
#fakefile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_qcdmadgraph.root
#signfile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_sigmadgraph.root
#
#datafile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_data.root
#fakefile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_qcdpythia.root
#signfile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_sigpythia.root
/bin/rm *.tar


#sh fullrun.step2.sh $PWD/fullrun.inputfiles.conf
sh fullrun.step3.sh
sh fullrun.step4.sh

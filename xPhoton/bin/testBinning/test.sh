#!/usr/bin/env sh

tag=DATAfull
ifile=/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/updatingusedvars/updated_data.root
cat > hi.json <<EOF
{
    "dataera": "UL2018",
    "InputFiles": ["${ifile}"],
    "OutputFileName":"binned_test${tag}.root"
}
EOF
exec_xPhotonBinning hi.json


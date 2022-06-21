#!/usr/bin/env sh

cat > allprocessbinning.json <<EOF
{

    "file_data":   "binned_2016ReReco_data.root",
    "file_QCD":    "binned_2016ReReco_QCD.root",
    "file_signal": "binned_2016ReReco_sig.root",

    "OutputNameTemplate":"binnedHists"
}
EOF
python allBinnedHists.py allprocessbinning.json

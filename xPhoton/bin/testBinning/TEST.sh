#!/usr/bin/env sh
touch plots ; /bin/rm -r plots; mkdir plots
/bin/rm binned_2016ReReco_data.root
python runxPhotonBinning.data.py

cat > hi.json <<EOF
{

    "file_data":   "binned_2016ReReco_data.root",
    "file_QCD":    "binned_2016ReReco_data.root",
    "file_signal": "binned_2016ReReco_data.root",

    "OutputNameTemplate":"binnedHists"
}
EOF
python BinnedHists.TDataFrame.py hi.json

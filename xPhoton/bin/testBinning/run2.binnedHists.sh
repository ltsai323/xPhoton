#!/usr/bin/env sh


for pPtBin  in {0..20}; do
for pEtaBin in {0..1} ; do
for jEtaBin in {0..1} ; do
    cat > processbinning.json <<EOF
{
    "bin_phopt":  $pPtBin,
    "bin_phoeta": $pEtaBin,
    "bin_jeteta": $jEtaBin,

    "file_data":   "binned_2016ReReco_data.root",
    "file_QCD":    "binned_2016ReReco_QCD.root",
    "file_signal": "binned_2016ReReco_sig.root",

    "OutputNameTemplate":"binnedHists"
}
EOF
    python BinnedHists.py processbinning.json
done; done; done

hadd -f binnedHistList.root binnedHists.*.root


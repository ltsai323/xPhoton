#!/usr/bin/env sh
/bin/rm *.dat
/bin/rm *.png *.pdf
/bin/rm binnedHist*.root

python runxPhotonBinning.data.py&
python runxPhotonBinning.qcdmc.py&
python runxPhotonBinning.sigmc.py

echo 'sleeping and waiting for job finished'
sleep 180

sh test/allBinHistsProcessing.sh
python FitYields.allbinning.py > log.fitres
python LogInfoExtraction.py log.fitres
cat > arg_orig.json <<EOF
{
    "luminosity": 35.9,
    "MarkerStyle": 22,
    "MarkerColor": 46,
    "Title": "2016 ReReco in old code",
    "Label": "Old",
    "DATfile": "/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/data.yield.dat"
}
EOF
cat > arg_comp.json <<EOF
{
    "luminosity": 35.9,
    "MarkerStyle": 22,
    "MarkerColor": 39,
    "Title": "2016 ReReco in new code",
    "Label": "New",
    "DATfile": "/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/bin/testBinning/res.2016ReReco.chIsoRaw/data.yield.dat"
}
EOF
arg_trg=arg_orig.json
arg_cmp=arg_comp.json

root -b <<EOF
.L /wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/CompareYields.C
CompareYields("$arg_trg","$arg_cmp")
EOF

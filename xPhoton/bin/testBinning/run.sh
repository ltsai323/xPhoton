#!/usr/bin/env sh
touch plots ; /bin/rm -r plots; mkdir plots

#sh test.sh
#python FitYields.allbinning.py > log.fitres
#python LogInfoExtraction.py log.fitres

cat > arg_orig.json <<EOF
{
    "luminosity": 35.9,
    "MarkerStyle": 22,
    "MarkerColor": 46,
    "Title": "2016 ReReco in old code",
    "Label": "Old",
    "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/16yield_newformat.dat",
    "histnaming": "orig2016ReReco_%d_%d"
}
EOF
cat > arg_comp.json <<EOF
{
    "luminosity": 35.9,
    "MarkerStyle": 22,
    "MarkerColor": 39,
    "Title": "2016 ReReco in new code",
    "Label": "New",
    "DATfile": "/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/bin/testBinning/res.2016ReReco.chIsoRaw/data.yield.dat",
    "histnaming": "newcmp2016ReReco_chIsoRaw_%d_%d"
}
EOF
arg_trg=arg_orig.json
arg_cmp=arg_comp.json

root -b <<EOF
.L /wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/CompareYields.C
CompareYields("$arg_trg","$arg_cmp")
EOF

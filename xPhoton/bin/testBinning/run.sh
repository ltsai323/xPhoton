#!/usr/bin/env sh
echo 'run the binning hist code...'
sleep 5
touch plots ; /bin/rm -r plots; mkdir plots
/bin/rm binned*.root
python runxPhotonBinning.data.py &
python runxPhotonBinning.qcdmc.py &
python runxPhotonBinning.sigmc.py
sleep 20

python BinnedHists.TDataFrame.py allprocessbinning.json
exit
python FitYields.allbinning.py > log.fitres
python LogInfoExtraction.py log.fitres
# # old for 2016
# cat > arg_orig.json <<EOF
# {
#     "luminosity": 35.9,
#     "MarkerStyle": 22,
#     "MarkerColor": 46,
#     "Title": "2016 ReReco in old code",
#     "Label": "Old",
#     "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/16yield_newformat.dat",
#     "histnaming": "orig2016ReReco_%d_%d"
# }
# EOF
# old for 2015
cat > arg_orig.json <<EOF
{
    "luminosity": 2.26,
    "MarkerStyle": 8,
    "MarkerColor": 38,
    "Title": "2015 ReReco from RS result",
    "Label": "2015",
    "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/15yield_noInclusivePho_newformat.dat",
    "histnaming": "orig2015_%d_%d"
}
EOF
cat > arg_comp.json <<EOF
{
    "luminosity": 35.9,
    "MarkerStyle": 22,
    "MarkerColor": 39,
    "Title": "2016 ReReco in new code",
    "Label": "New",
    "DATfile": "data.yield.dat",
    "histnaming": "newcmp2016ReReco_chIsoRaw_%d_%d"
}
EOF
arg_trg=arg_orig.json
arg_cmp=arg_comp.json

root -b <<EOF
.L /wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/CompareYields.C
CompareYields("$arg_trg","$arg_cmp")
EOF

##!/usr/bin/env sh

dataera=$1
origera=2016

if [ $origera == 2016 ]; then
cat > arg_orig.json <<EOF
{
    "luminosity": 35.9,
    "MarkerStyle": 22,
    "MarkerColor": 46,
    "Title": "2016 ReReco in old processed",
    "Label": "Old16",
    "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/16yield_newformat.dat"
}
EOF
qq=1
fi
if [ "$origera" == 2015 ]; then
cat > arg_orig.json <<EOF
{
    "luminosity": 2.26,
    "MarkerStyle": 8,
    "MarkerColor": 38,
    "Title": "2015 ReReco from RS result",
    "Label": "2015",
    "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/15yield_noInclusivePho_newformat.dat"
}
EOF
qq=1
fi

if [ "$dataera" == 2016 ]; then
cat > arg_comp.json <<EOF
{
    "luminosity": 35.9,
    "MarkerStyle": 22,
    "MarkerColor": 39,
    "Title": "2016 ReReco in old processed AGAIN",
    "Label": "New",
    "DATfile": "data.yield.dat"
}
EOF
qq=1
fi
if [ "$dataera" == 2018 ]; then
cat > arg_comp.json <<EOF
{
    "luminosity": 59.96,
    "MarkerStyle": 22,
    "MarkerColor": 39,
    "Label": "UL18",
    "Title": "UL2018",
    "DATfile": "data.yield.dat"
}
EOF
qq=1
fi

if [ "$qq" == "" ]; then
    exit
fi

arg_trg=arg_orig.json
arg_cmp=arg_comp.json

root -b <<EOF
.L /wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/CompareYields.C
CompareYields("$arg_trg","$arg_cmp")
EOF

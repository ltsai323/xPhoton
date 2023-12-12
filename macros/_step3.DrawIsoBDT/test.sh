#!/usr/bin/env sh
touch logs ; /bin/rm -rf logs; mkdir logs



tmpjson="hi.json"
#for phoPtBin in {0..24}; do
#for phoEtaIdx in {0..1}; do
#for jetEtaIdx in {0..2}; do
phoPtBin=13
phoEtaIdx=0
jetEtaIdx=2

#    "data":"/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/makehisto_data.root",
#    "bkg": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/makehisto_QCD.root",
#    "sig": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/makehisto_sig.root",
cat > $tmpjson <<EOF
{
    "phoEtaBin": $phoEtaIdx,
    "jetEtaBin": $jetEtaIdx,
    "phoPtBin":  $phoPtBin,
    "rebinOption":1,
    "data":"../makehisto_data.root",
    "bkg": "../makehisto_QCD.root",
    "sig": "../makehisto_sig.root",
    "out_template": "disabled"
}
EOF

root -b <<EOF
.L Draw_IsovsBDT.C
Draw_IsovsBDT("$tmpjson")
EOF
echo done
exit

#done; done; done

#/bin/rm $tmpjson
#hadd -f isovsbdt_template.root iso_*.root
#/bin/rm  iso_*.root

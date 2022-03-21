#!/usr/bin/env sh
touch logs ; /bin/rm -rf logs; mkdir logs



tmpjson="hi.json"
#for phoPtBin in {0..24}; do
#for phoEtaIdx in {0..1}; do
#for jetEtaIdx in {0..2}; do
phoPtBin=13
phoEtaIdx=0
jetEtaIdx=0

cat > $tmpjson <<EOF
{
    "phoEtaBin": $phoEtaIdx,
    "jetEtaBin": $jetEtaIdx,
    "phoPtBin":  $phoPtBin,
    "rebinOption":1,
    "sidebandlower":14,
    "sidebandupper":20,
    "data":"/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/makehisto_data.root",
    "bkg": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/makehisto_QCD.root",
    "sig": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/makehisto_sig.root",
    "out_template": "disabled"
}
EOF

root -b > logs/job_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtBin} <<EOF
.L testing.C+
Draw_IsovsBDT("$tmpjson")
EOF
#done; done; done

/bin/rm $tmpjson
hadd -f isovsbdt_template.root iso_*.root
/bin/rm  iso_*.root

#!/usr/bin/env sh
touch logs ; /bin/rm -rf logs; mkdir logs



tmpjson="hi.json"
for phoPtBin in {0..24}; do
for phoEtaIdx in {0..1}; do
for jetEtaIdx in {0..2}; do


cat > $tmpjson <<EOF
{
    "phoEtaBin": $phoEtaIdx,
    "jetEtaBin": $jetEtaIdx,
    "phoPtBin":  $phoPtBin,
    "rebinOption":1,
    "sidebandlower":14,
    "sidebandupper":20,
    "data":"../step2.makehistos/storeroot_mcweightcut_on_lightcut_1/makehisto_data.root",
    "bkg": "../step2.makehistos/storeroot_mcweightcut_on_lightcut_1/makehisto_QCD_madgraph.root",
    "sig": "../step2.makehistos/storeroot_mcweightcut_on_lightcut_1/makehisto_sig_madgraph.root",
    "out_template": "disabled"
}
EOF

root -b > logs/job_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtBin} 2> /dev/null <<EOF
.L testing.C+
Draw_IsovsBDT("$tmpjson")
EOF
done; done; done

/bin/rm $tmpjson
hadd -f isovsbdt_template.root iso_*.root
/bin/rm  iso_*.root

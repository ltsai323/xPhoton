#!/usr/bin/env sh

iBin=0

for phoPtBin in {0..24}; do
for phoEtaIdx in {0..1}; do
for jetEtaIdx in {0..2}; do
root -b > logs/log_fakesample${iBin}_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtBin} 2> /dev/null <<EOF
.L Draw_IsovsBDT.C+
Draw_IsovsBDT(${phoEtaIdx},${jetEtaIdx},${phoPtBin},1, 14, 20, -10${iBin})
EOF
mv isovsbdt.root iso_${phoEtaIdx}_${jetEtaIdx}_${phoPtBin}_fakesample${iBin}.root
done; done; done;

hadd -f isovsbdt_template.root iso_*.root
/bin/rm  iso_*.root

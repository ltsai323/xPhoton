#!/usr/bin/env sh

#iBin=0

for iFile in `ls ../step2.makehistos/storeroot/makehisto_fakedata*.root `; do
outnametemplate=`echo $iFile | rev | cut -d'/' -f1 | cut -d'.' -f2-10 | rev | cut -d'_' -f2-10`    

for phoPtBin in {0..24}; do
for phoEtaIdx in {0..1}; do
for jetEtaIdx in {0..2}; do
root -b > logs/log_fakesample${iBin}_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtBin} 2> /dev/null <<EOF
.L Draw_IsovsBDT.C+
Draw_IsovsBDT(${iFile},${phoEtaIdx},${jetEtaIdx},${phoPtBin},1, 14, 20)
EOF
mv isovsbdt.root iso_${outnametemplate}_${phoEtaIdx}_${jetEtaIdx}_${phoPtBin}.root
done; done; done

hadd -f storeroot/isovsbdt_template_${outnametemplate}.root iso_*.root
/bin/rm  iso_*.root
done

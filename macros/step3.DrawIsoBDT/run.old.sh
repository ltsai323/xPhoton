#!/usr/bin/env sh
for phoEtaIdx in {0..1}; do
    echo processing to photon eta $phoEtaIdx
for jetEtaIdx in {0..2}; do
for phoPtBin in {0..20}; do

root -b > logs/job_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtBin}  <<EOF
.L Draw_IsovsBDT.C+
Draw_IsovsBDT($phoEtaIdx, $jetEtaIdx, $phoPtBin,
"../makehisto_data.root", "../makehisto_sig.root", "../makehisto_QCD.root", "disabled");
EOF
done; done; done

/bin/rm $tmpjson
hadd -f isovsbdt_template.root iso_*.root
/bin/rm  iso_*.root

#!/usr/bin/env sh

myexec() {
phoEtaIdx=$1
jetEtaIdx=$2
phoPtIdx=$3
tmpjson="hi_${phoEtaIdx}_${jetEtaIdx}_${phoPtIdx}.json"

cat > $tmpjson <<EOF
{
    "phoEtaBin": $phoEtaIdx,
    "jetEtaBin": $jetEtaIdx,
    "phoPtBin":  $phoPtIdx,
    "rebinOption":1,
    "data":"../makehisto_data.root",
    "bkg": "../makehisto_QCD.root",
    "sig": "../makehisto_gjet.root",
    "out_template": "disabled"
}
EOF

#root -b > logs/job_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtIdx} <<EOF
root -b  <<EOF
.L Draw_IsovsBDT.C+
Draw_IsovsBDT("$tmpjson")
EOF
/bin/rm $tmpjson
}

for phoEtaIdx in {0..1}; do
for jetEtaIdx in {0..2}; do
    echo processing to eta bins $phoEtaIdx $jetEtaIdx
for phoPtIdx in {0..1}; do
    myexec $phoEtaIdx $jetEtaIdx $phoPtIdx
    exit
done; done; done

wait
hadd -f isovsbdt_template.root iso_*.root
/bin/rm  iso_*.root

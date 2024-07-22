#!/usr/bin/env sh

for pEtaIdx in {0..1};  do
    for jEtaIdx in {0..1}; do
        for pPtIdx in {0..21}; do
            root -b -l -q "Draw_IsovsBDT.C($pEtaIdx,$jEtaIdx,$pPtIdx,1)" > /dev/null
            mv isovsbdt.root iso_${pEtaIdx}_${jEtaIdx}_${pPtIdx}.root
        done
    done
done
hadd -f isovsbdt_template.root iso_*.root

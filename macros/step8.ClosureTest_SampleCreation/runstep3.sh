#!/usr/bin/env sh
touch storeroot/fragmentsIsovsBDT; /bin/rm -r storeroot/fragmentsIsovsBDT; mkdir -p storeroot/fragmentsIsovsBDT/logs
touch storeroot/logs; /bin/rm -r storeroot/logs; mkdir -p storeroot/logs


for infile in `ls storeroot/fragmentsMakehisto/*.root`; do
    touch iso_hiii.root; /bin/rm iso_*.root
    echo $infile
    fname=`echo $infile | rev | cut -d'/' -f1 | cut -d'.' -f2-10 | rev | cut -d'_' -f2-10`
    echo $fname

    for phoPtBin in {0..24}; do
    for phoEtaIdx in {0..1}; do
    for jetEtaIdx in {0..2}; do
         echo "running Draw_IsovsBDT(\"${infile}\",${phoEtaIdx},${jetEtaIdx},${phoPtBin},1, 14, 20)"
         root -b > storeroot/fragmentsIsovsBDT/logs/log_fakesample${fname}_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtBin} 2> /dev/null <<EOF
.L ../step3.DrawIsoBDT/Draw_IsovsBDT.C
Draw_IsovsBDT("${infile}",${phoEtaIdx},${jetEtaIdx},${phoPtBin},1, 14, 20)
EOF
        mv isovsbdt.root iso_${fname}_${phoEtaIdx}_${jetEtaIdx}_${phoPtBin}.root
    done; done; done
    hadd storeroot/fragmentsIsovsBDT/iso_${fname}.root iso_*.root
    /bin/rm iso_*.root
done


for infile in `ls storeroot/makehisto*.root`; do
    touch iso_hi.root; /bin/rm iso_*.root
    fname=`echo $infile | rev | cut -d'/' -f1 | cut -d'.' -f2-10 | rev | cut -d'_' -f2-10`
    echo $fname

    for phoPtBin in {0..24}; do
    for phoEtaIdx in {0..1}; do
    for jetEtaIdx in {0..2}; do
        root -b > storeroot/logs/log_fakesample${fname}_phoEta${phoEtaIdx}_jetEta${jetEtaIdx}_phoPt${phoPtBin} 2> /dev/null <<EOF
.L ../step3.DrawIsoBDT/Draw_IsovsBDT.C
Draw_IsovsBDT("${infile}",${phoEtaIdx},${jetEtaIdx},${phoPtBin},1, 14, 20)
EOF
        mv isovsbdt.root iso_${fname}_${phoEtaIdx}_${jetEtaIdx}_${phoPtBin}.root
    done; done; done
    hadd storeroot/iso_${fname}.root iso_*.root
    /bin/rm  iso_*.root
done

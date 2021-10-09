#!/usr/bin/env sh

for ifile in `echo  storeroot/fragments/*.root`;
do
outname=`echo $ifile | rev | cut -d'/' -f1 | rev`
root -b <<EOF
.L ../step2.makehistos/MakeHisto.C
MakeHisto t("${ifile}",false)
t.Loop()
EOF
    mv output.root storeroot/fragmentsHisto/makehisto_${outname}
done

for ifile in `echo  storeroot/*.root`;
do
outname=`echo $ifile | rev | cut -d'/' -f1 | rev`
root -b <<EOF
.L ../step2.makehistos/MakeHisto.C
MakeHisto t("${ifile}",false)
t.Loop()
EOF
    mv output.root storeroot/makehisto_${outname}
done

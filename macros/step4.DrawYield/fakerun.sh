#!/usr/bin/env sh
# 1. relink isobsbdt_template.root for use script.
# 2. run the script.
# 3. move outputs into storage

for infile in `echo ../step3.DrawIsoBDT/storeroot/isovsbdt_template_fakesample*.root`;
do
    outname=`echo $infile | rev | cut -d'/' -f1 | cut -d'.' -f2-10 | rev | cut -d'_' -f3-10`
    touch isovsbdt_template.root; /bin/rm isovsbdt_template.root
    ln -s ../step3.DrawIsoBDT/storeroot/isovsbdt_template.root
    sh run.sh

    mv data_bkg_allphoton.dat    storeroot/${outname}_bkg_allphoton.dat
    mv data_bkg_barrelJet.dat    storeroot/${outname}_bkg_barrelJet.dat
    mv data_bkg_endcapJet.dat    storeroot/${outname}_bkg_endcapJet.dat
    mv data_yield_allphoton.dat  storeroot/${outname}_yield_allphoton.dat
    mv data_yield_barrelJet.dat  storeroot/${outname}_yield_barrelJet.dat
    mv data_yield_endcapJet.dat  storeroot/${outname}_yield_endcapJet.dat
    /bin/rm log*
done

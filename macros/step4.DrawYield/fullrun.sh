#!/usr/bin/env sh
# 1. relink isobsbdt_template.root for use script.
# 2. run the script.
# 3. move outputs into storage
touch isovsbdt_template.root; /bin/rm isovsbdt_template.root
ln -s ../step3.DrawIsoBDT/storeroot/isovsbdt_template.root
sh run.sh
mv data_bkg_allphoton.dat    storeroot/data_bkg_allphoton.dat
mv data_bkg_barrelJet.dat    storeroot/data_bkg_barrelJet.dat
mv data_bkg_endcapJet.dat    storeroot/data_bkg_endcapJet.dat
mv data_yield_allphoton.dat  storeroot/data_yield_allphoton.dat
mv data_yield_barrelJet.dat  storeroot/data_yield_barrelJet.dat
mv data_yield_endcapJet.dat  storeroot/data_yield_endcapJet.dat

/bin/rm log*

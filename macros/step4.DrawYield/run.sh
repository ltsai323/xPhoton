#!/usr/bin/env sh
# part 1 : fit and draw result and print informations to log
# part 2 : collect the results and create TTree readable file.
mkdir -p plots

for isEE in 0 1; do
for jetBin in 0 1 2; do
root -b > log.ebee_${isEE}_${jetBin} <<EOF
.L DrawYield.C+
DrawYield(${isEE},${jetBin})
EOF
done
done

# inclusive gamma measurement : no matter how jet distributed
echo "ptbin/I:EBEE/I:jetbin/I:bkg/F:bkg_err/F" > data_bkg_allphoton.dat
grep "EB bin " log.ebee_0_0 | grep BKG | awk '{print $3, 0, 0, $5, $7}' >> data_bkg_allphoton.dat
grep "EE bin " log.ebee_1_0 | grep BKG | awk '{print $3, 1, 0, $5, $7}' >> data_bkg_allphoton.dat
grep "EB bin " log.ebee_0_1 | grep BKG | awk '{print $3, 0, 1, $5, $7}' >> data_bkg_allphoton.dat
grep "EE bin " log.ebee_1_1 | grep BKG | awk '{print $3, 1, 1, $5, $7}' >> data_bkg_allphoton.dat
grep "EB bin " log.ebee_0_2 | grep BKG | awk '{print $3, 0, 2, $5, $7}' >> data_bkg_allphoton.dat
grep "EE bin " log.ebee_1_2 | grep BKG | awk '{print $3, 1, 2, $5, $7}' >> data_bkg_allphoton.dat

echo "ptbin/I:EBEE/I:jetbin/I:yields/F:yields_err/F" > data_yield_allphoton.dat
grep "EB bin " log.ebee_0_0 | grep SIG | awk '{print $3, 0, 0, $5, $7}' >> data_yield_allphoton.dat
grep "EE bin " log.ebee_1_0 | grep SIG | awk '{print $3, 1, 0, $5, $7}' >> data_yield_allphoton.dat
grep "EB bin " log.ebee_0_1 | grep SIG | awk '{print $3, 0, 1, $5, $7}' >> data_yield_allphoton.dat
grep "EE bin " log.ebee_1_1 | grep SIG | awk '{print $3, 1, 1, $5, $7}' >> data_yield_allphoton.dat
grep "EB bin " log.ebee_0_2 | grep SIG | awk '{print $3, 0, 2, $5, $7}' >> data_yield_allphoton.dat
grep "EE bin " log.ebee_1_2 | grep SIG | awk '{print $3, 1, 2, $5, $7}' >> data_yield_allphoton.dat

# gamma + barrel jet
echo "ptbin/I:EBEE/I:jetbin/I:bkg/F:bkg_err/F" > data_bkg_endcapJet.dat
grep "EB bin " log.ebee_0_1 | grep BKG | awk '{print $3, 0, 1, $5, $7}' >> data_bkg_endcapJet.dat
grep "EE bin " log.ebee_1_1 | grep BKG | awk '{print $3, 1, 1, $5, $7}' >> data_bkg_endcapJet.dat

echo "ptbin/I:EBEE/I:jetbin/I:yields/F:yields_err/F" > data_yield_endcapJet.dat
grep "EB bin " log.ebee_0_1 | grep SIG | awk '{print $3, 0, 1, $5, $7}' >> data_yield_endcapJet.dat
grep "EE bin " log.ebee_1_1 | grep SIG | awk '{print $3, 1, 1, $5, $7}' >> data_yield_endcapJet.dat

# gamma + endcap jet
echo "ptbin/I:EBEE/I:jetbin/I:bkg/F:bkg_err/F" > data_bkg_barrelJet.dat
grep "EB bin " log.ebee_0_0 | grep BKG | awk '{print $3, 0, 0, $5, $7}' >> data_bkg_barrelJet.dat
grep "EE bin " log.ebee_1_0 | grep BKG | awk '{print $3, 1, 0, $5, $7}' >> data_bkg_barrelJet.dat

echo "ptbin/I:EBEE/I:jetbin/I:yields/F:yields_err/F" > data_yield_barrelJet.dat
grep "EB bin " log.ebee_0_0 | grep SIG | awk '{print $3, 0, 0, $5, $7}' >> data_yield_barrelJet.dat
grep "EE bin " log.ebee_1_0 | grep SIG | awk '{print $3, 1, 0, $5, $7}' >> data_yield_barrelJet.dat




echo "ptbin/I:EBEE/I:jetbin/I:bkg/F:bkg_err/F" > data_bkg.dat
grep "EB bin " log.ebee_0_1 | grep BKG | awk '{print $3, 0, 1, $5, $7}' >> data_bkg.dat
grep "EE bin " log.ebee_1_1 | grep BKG | awk '{print $3, 1, 1, $5, $7}' >> data_bkg.dat
grep "EB bin " log.ebee_0_0 | grep BKG | awk '{print $3, 0, 0, $5, $7}' >> data_bkg.dat
grep "EE bin " log.ebee_1_0 | grep BKG | awk '{print $3, 1, 0, $5, $7}' >> data_bkg.dat

echo "ptbin/I:EBEE/I:jetbin/I:yields/F:yields_err/F" > data_yield.dat
grep "EB bin " log.ebee_0_1 | grep SIG | awk '{print $3, 0, 1, $5, $7}' >> data_yield.dat
grep "EE bin " log.ebee_1_1 | grep SIG | awk '{print $3, 1, 1, $5, $7}' >> data_yield.dat
grep "EB bin " log.ebee_0_0 | grep SIG | awk '{print $3, 0, 0, $5, $7}' >> data_yield.dat
grep "EE bin " log.ebee_1_0 | grep SIG | awk '{print $3, 1, 0, $5, $7}' >> data_yield.dat


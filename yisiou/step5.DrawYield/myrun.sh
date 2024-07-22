#!/usr/bin/env sh

touch plots ; /bin/rm -r plots
mkdir plots

./fit.py > log.fitting
echo "ptbin/I:EBEE/I:jetbin/I:bkg/F:bkg_err/F" > data.yield.dat
echo "ptbin/I:EBEE/I:jetbin/I:bkg/F:bkg_err/F" > data.bkg.dat
grep SIG log.fitting | awk '{print $2,$4,$6,$8, $10}' >> data.yield.dat
grep BKG log.fitting | awk '{print $2,$4,$6,$8, $10}' >> data.bkg.dat

#!/usr/bin/env sh
# part 1 : fit and draw result and print informations to log
# part 2 : collect the results and create TTree readable file.

for isEE in 0; do
for jetBin in 1; do
root -b > log.ebee_${isEE}_${jetBin} <<EOF
.L DrawYield.C
DrawYield(${isEE},${jetBin})
EOF
root -b > new.ebee_${isEE}_${jetBin} <<EOF
.L kk.C
DrawYield(${isEE},${jetBin})
EOF
done
done

diff log.ebee_0_1 new.ebee_0_1

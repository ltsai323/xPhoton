isEE=0
jetBin=0

root -b > log.ebee_${isEE}_${jetBin} <<EOF
.L DrawYield.C+
DrawYield(${isEE},${jetBin})
EOF

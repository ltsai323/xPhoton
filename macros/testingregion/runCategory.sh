#!/usr/bin/env sh


root -b <<EOF
.L JetFrac_CAT_Neta_Nphi.C
JetFractionCalc()
EOF
mv fractionHists.root frac_Neta_Nphi.root
root -b <<EOF
.L JetFrac_CAT_Neta_Pphi.C
JetFractionCalc()
EOF
mv fractionHists.root frac_Neta_Pphi.root
root -b <<EOF
.L JetFrac_CAT_Peta_Nphi.C
JetFractionCalc()
EOF
mv fractionHists.root frac_Peta_Nphi.root
root -b <<EOF
.L JetFrac_CAT_Peta_Pphi.C
JetFractionCalc()
EOF
mv fractionHists.root frac_Peta_Pphi.root

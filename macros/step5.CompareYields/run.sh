#!/usr/bin/env sh
arg_trg=arg_2015incl.json
arg_cmp=$1

root -b <<EOF
.L CompareYields.C
CompareYields("$arg_trg","$arg_cmp")
EOF

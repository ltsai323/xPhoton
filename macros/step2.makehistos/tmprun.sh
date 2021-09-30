#!/usr/bin/env sh

mkdir -p data ; cd data
root -b <<EOF
.L ../MakeHisto.C+
MakeHisto t(1)
t.Loop()
EOF
mv output.root makehisto_data.root


#!/usr/bin/env sh

for iBin in {0..9};
do
    echo $iBin
    root -b <<EOF
.L MakeHisto.C+
MakeHisto t(-10${iBin})
t.Loop()
EOF
    mv output.root storeroot/makehisto_fakedata${iBin}.root
done


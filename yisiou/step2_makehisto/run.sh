#!/usr/bin/env sh

root -b <<EOF
.L MakeHisto.C+
MakeHisto t(1)
t.Loop(1)
EOF
mv output.root makehisto_data.root

root -b <<EOF
.L MakeHisto.C+
MakeHisto t(2)
t.Loop(1)
EOF
mv output.root makehisto_sig_madgraph.root

root -b <<EOF
.L MakeHisto.C+
MakeHisto t(3)
t.Loop(1)
EOF
mv output.root makehisto_QCD_madgraph.root

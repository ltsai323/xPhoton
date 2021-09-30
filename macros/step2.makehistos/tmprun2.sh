#!/usr/bin/env sh

mkdir -p madgraph_sig ; cd madgraph_sig
root -b <<EOF
.L ../MakeHisto.C+
MakeHisto t(2)
t.Loop()
EOF
mv output.root makehisto_sig_madgraph.root

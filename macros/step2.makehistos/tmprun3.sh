#!/usr/bin/env sh

mkdir -p madgraph_qcd; cd madgraph_qcd
root -b <<EOF
.L ../MakeHisto.C+
MakeHisto t(3)
t.Loop()
EOF
cp output.root makehisto_QCD_madgraph.root

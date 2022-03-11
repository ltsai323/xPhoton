#!/usr/bin/env sh

label=data
file=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root
root -b <<EOF
.x TreeReduced.C("${file}", "${label}")
EOF

label=mc
file=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root
root -b <<EOF
.x TreeReduced.C("${file}", "${label}")
EOF

label=qcd
file=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root
root -b <<EOF
.x TreeReduced.C("${file}", "${label}")
EOF

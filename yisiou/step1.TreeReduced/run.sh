#!/usr/bin/env sh

#file=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root
file=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root
#file=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root

root -b <<EOF
.x TreeReduced.C("${file}")
EOF

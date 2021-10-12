#!/usr/bin/env sh

origfile=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root
newfile=hi.root

root -b <<EOF
.L EventSelection.C
EventSelection("${origfile}");
EOF

mv output.root $newfile 

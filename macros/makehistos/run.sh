#!/usr/bin/env sh

root -b <<EOF
.L MakeHisto.C
MakeHisto t(2)
t.Loop()
EOF
#mv output.root /home/ltsai/ReceivedFile/GJet/test/RSpreviousSample/output_MakeHisto.C.root

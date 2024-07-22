#!/usr/bin/env sh
faketemplate=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/FakeHistograms.root
outputfile=fulloutput.root
inputfile=/wk_cms/ltsai/ReceivedFile/GJet/latestsample/sigMC_madgraph.root

root -b $inputfile <<EOF
.x jetHists.C
EOF


hadd $outputfile output.root $faketemplate
/bin/rm output.root

#!/usr/bin/env sh
infile=/home/ltsai/ReceivedFile/GJet/old/old.2016ReReco.data.root
output=data.root
hltopt=0
root -b <<EOF
 .L MakeHisto.C++
 MakeHisto t("$infile", $hltopt);
 t.Loop();
 .q
EOF
mv output.root $output

output=sig.root
infile=/home/ltsai/ReceivedFile/GJet/old/old.2016ReReco.sigPythia.root
hltopt=0
root -b <<EOF
 .L MakeHisto.C++
 MakeHisto t("$infile", $hltopt);
 t.Loop();
 .q
EOF
mv output.root $output

infile=/home/ltsai/ReceivedFile/GJet/old/old.2016ReReco.QCDPythia.root
output=qcd.root
hltopt=1
root -b <<EOF
 .L MakeHisto.C++
 MakeHisto t("$infile", $hltopt);
 t.Loop();
 .q
EOF
mv output.root $output

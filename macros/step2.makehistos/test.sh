#!/usr/bin/env sh
datafile=$1
signfile=$2
fakefile=$3



label=data
ifile=$datafile
isMC=false
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC)
t.Loop(1)
EOF

# label=sig
# ifile=$signfile
# isMC=true
# root -b <<EOF
# .L MakeHisto.C+
# MakeHisto t("$ifile","$label",$isMC)
# t.Loop(1)
# EOF
# 
# 
# label=QCD
# ifile=$fakefile
# isMC=true
# root -b <<EOF
# .L MakeHisto.C+
# MakeHisto t("$ifile","$label",$isMC)
# t.Loop(1)
# EOF


if [ "$?" != "0" ]; then exit; fi


##   root -b  output.root <<EOF
##   TH1* horig = (TH1*) _file0->Get("");
##   TH1* hnew  = (TH1*) _file0->Get("");
##   EOF

     
#  echo 'start checking'
#  root -b orig.root > log.old <<EOF
#  char hname[50];
#  
#  for ( int etabin = 0; etabin < 2; ++etabin ) {
#  for ( int jetbin = 0; jetbin < 3; ++jetbin ) {
#  for ( int  ptbin = 0;  ptbin <20; ++ ptbin ) {
#      sprintf(hname, "h_BDT_%d_%d_%d_0", etabin,jetbin,ptbin);
#      TH1* h = (TH1*)_file0->Get(hname);
#      std::cout << "histname : " << h->GetName() << " with " << h->GetEntries() << " entries and mean=" << h->GetMean() << std::endl;
#  }}}
#  EOF
#diff log.old log.new


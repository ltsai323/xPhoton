ifile=../testasample.2016.QCD.root
label=QCD
isMC=true
USEHLT=1


root -b <<EOF
.L MakeHisto.C
MakeHisto t("$ifile","$label",$isMC, $USEHLT)
t.SetDataEra("2016ReReco")
t.Loop(1)
EOF

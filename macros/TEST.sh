#mv checkdata_ver2.root checkdata_ver2.old.root
echo only for makehist_data.root

# cleaning workspace
touch makehisto.root; /bin/rm makehisto*.root

cd step2.makehistos
# cleaning workspace
touch makehisto.root; /bin/rm makehisto*.root

label=data
datafile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.data.root
ifile=$datafile
isMC=false
USEHLT=0
if [ "$datafile" != "" ]; then
root -b <<EOF
.L MakeHisto.C+
MakeHisto t("$ifile","$label",$isMC, $USEHLT)
t.SetDataEra("2016ver2")
t.Loop(1)
EOF
fi
mv makehisto_data.root ../checkdata_ver2.root
cd ..

#root -b -q checkHLTbit2.C 

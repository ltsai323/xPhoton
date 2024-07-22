#!/usr/bin/env sh
datafile=$1
signfile=$2
qcdfile=$3
data_era="UL2016PostVFP"

function exec_code()
{
jetCutIdx=$1
inputcode=$2
outputfolder=$3

f_data=$4
f_sign=$5
f_qcd=$6
mkdir -p $outputfolder
root -b <<EOF
.L $inputcode
Loop($jetCutIdx, "$data_era", "data", "$f_data");
Loop($jetCutIdx, "$data_era", "gjet", "$f_sign");
Loop($jetCutIdx, "$data_era", "QCD" , "$f_qcd" );
EOF
hadd makehisto.root makehisto_*.root

mv makehisto.root $outputfolder/
mv makehisto_*.root $outputfolder/
}
function the_exit()
{
    echo $1
    exit
}


# check using default ptbin_definition
used_pt_def=../ptbin_definitions.h
unlink ptbin_definitions.h && ln -s $used_pt_def || the_exit "link failed to $used_pt_def"

cutIdx=0 # 0: no extra cut. 1: subJetVtxMass > 0. 2: CvsL > 0.155
mainFunc=makehistoDeepFlavour.C
outDir=DeepFlavour_cutIdx0
exec_code $cutIdx $mainFunc $outDir $datafile $signfile $qcdfile
exit
cutIdx=1 # 0: no extra cut. 1: subJetVtxMass > 0. 2: CvsL > 0.155
mainFunc=makehistoDeepFlavour.C
outDir=DeepFlavour_cutIdx1
exec_code $cutIdx $mainFunc $outDir $datafile $signfile $qcdfile
cutIdx=2 # 0: no extra cut. 1: subJetVtxMass > 0. 2: CvsL > 0.155
mainFunc=makehistoDeepFlavour.C
outDir=DeepFlavour_cutIdx2
exec_code $cutIdx $mainFunc $outDir $datafile $signfile $qcdfile

#cutIdx=0 # 0: no extra cut. 1: subJetVtxMass > 0. 2: CvsL > 0.155
#mainFunc=makehistoDeepCSV.C
#outDir=DeepCSV_cutIdx0_mergeBin_test1
#exec_code $cutIdx $mainFunc $outDir $datafile $signfile $qcdfile


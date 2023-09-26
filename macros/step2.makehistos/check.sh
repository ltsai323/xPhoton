#!/usr/bin/env sh
# valid dataEra = "2016ReReco", "UL16PreVFP", "UL16PostVFP", "UL2017", "UL2018"
function exec_code()
{
num=$1
inputcode=$2
outputfolder=$3
mkdir -p $outputfolder
root -b <<EOF
.L $inputcode
Loop($num, "UL16PreVFP", "data", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/data.root");
Loop($num, "UL16PreVFP", "gjet", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/gjet.madgraph.root");
Loop($num, "UL16PreVFP", "QCD", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/qcd.madgraph.root");
EOF
hadd makehisto.root makehisto_*.root

mv makehisto.root $outputfolder/
mv makehisto_*.root $outputfolder/
}
function test_code()
{
num=-1
inputcode=$1
outputfolder=$2
mkdir -p $outputfolder
root -b <<EOF
.L $inputcode
Loop($num, "UL16PreVFP", "testdata", "/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/UL16PreVFP_data.root");
EOF
}


# -1 to test
exec_code 0 makehistoDeepFlavour.C DeepFlavour_cutIdx0_mergeBin_test3
#exec_code 0 makehistoDeepCSV.C DeepCSV_cutIdx0_mergeBin_test3


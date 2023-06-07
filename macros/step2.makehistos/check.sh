#!/usr/bin/env sh

function exec_code()
{
num=$1
inputcode=$2
outputfolder=$3
mkdir -p $outputfolder
root -b <<EOF
.L $inputcode
Loop($num, "2016ReReco", "testdata", "/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/UL16PreVFP_data.root");
Loop($num, "2016ReReco", "testgjet", "/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/gjet.pythia.root");
Loop($num, "2016ReReco", "testQCD", "/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/qcd.madgraph.root");
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
Loop($num, "2016ReReco", "testdata", "/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/UL16PreVFP_data.root");
EOF
}


# -1 to test
exec_code 0 makehistoDeepFlavour.C DeepFlavour_cutIdx0_mergeBin_test3
exec_code 0 makehistoDeepCSV.C DeepCSV_cutIdx0_mergeBin_test3


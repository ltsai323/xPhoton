#!/usr/bin/env sh
# valid dataEra = "2016ReReco", "UL2016PreVFP", "UL2016PostVFP", "UL2017", "UL2018"
function the_exit()
{ echo "$1";exit; }

function change_running_location()
{
    outputLABEL=$1
    if [ "$2" == "-1" ]; then return 0; fi # running in test mode
    mkdir -p "$outputLABEL" ; cd "$outputLABEL" || the_exit "cd to $outputLABEL failed"
    for usedfile in ../{*.h,*.C}; do ln -s $usedfile; done
}
function tidy_up_working_area()
{
    outputFOLDER=$1
    for usedfile in ../{*.h,*.C}; do unlink $usedfile; done
    current_folder=`realpath .`
    mv $current_folder $outputFOLDER
}
function main_code()
{
num=$1
inputCODE=$2
outputLABEL=$3
outputFOLDER=$4


change_running_location $outputLABEL $num
root -b <<EOF
.L $inputCODE
Loop($num, "UL2016PreVFP", "data", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/data.root");
Loop($num, "UL2016PreVFP", "gjet", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/gjet.madgraph.root");
Loop($num, "UL2016PreVFP", "QCD", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/qcd.madgraph.root");
EOF

if [ "$num" == "-1" ]; then exit; fi
hadd makehisto.root makehisto_*.root
tidy_up_working_area /wk_cms3/ltsai/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/
}
function exec_code()
{ main_code "$1" "$2" "$3" > "$3"_log 2>&1; }
function test_code()
{ main_code "-1" "$2" "$3"; }

function link_pt_bin_definition()
{ unlink ptbin_definitions.h; ln -s $1 ptbin_definitions.h|| the_exit "link failed to $1"; }



link_pt_bin_definition ../ptbin_definitions_testmodeOrig.h
exec_code 0 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_Orig&
exec_code 1 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_Orig&
exec_code 2 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_Orig&
exec_code 0 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx0_mergeBin_Orig&
exec_code 1 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx1_mergeBin_Orig&
exec_code 2 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx2_mergeBin_Orig&
wait


link_pt_bin_definition ../ptbin_definitions_testmode0.h
exec_code 0 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_0&
exec_code 1 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_0&
exec_code 2 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_0&
exec_code 0 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx0_mergeBin_0&
exec_code 1 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx1_mergeBin_0&
exec_code 2 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx2_mergeBin_0&
wait



link_pt_bin_definition ../ptbin_definitions_testmode1.h
exec_code 0 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_1&
exec_code 1 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_1&
exec_code 2 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_1&
exec_code 0 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx0_mergeBin_1&
exec_code 1 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx1_mergeBin_1&
exec_code 2 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx2_mergeBin_1&
wait



link_pt_bin_definition ../ptbin_definitions_testmode2.h
exec_code 0 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_2&
exec_code 1 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_2&
exec_code 2 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_2&
exec_code 0 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx0_mergeBin_2&
exec_code 1 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx1_mergeBin_2&
exec_code 2 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx2_mergeBin_2&
wait



link_pt_bin_definition ../ptbin_definitions_testmode3.h
exec_code 0 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_3&
exec_code 1 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_3&
exec_code 2 makehistoDeepFlavour.C DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_3&
exec_code 0 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx0_mergeBin_3&
exec_code 1 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx1_mergeBin_3&
exec_code 2 makehistoDeepCSV.C DeepCSV_gjetMadgraph_cutIdx2_mergeBin_3&
wait

# real    73m22.047s
# user    343m22.508s
# sys     30m48.940s



#test_code 0 makehistoDeepFlavour.C DeepFlavour_cutIdx0_mergeBin_test3

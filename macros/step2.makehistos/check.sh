#!/usr/bin/env sh
# valid dataEra = "2016ReReco", "UL2016PreVFP", "UL2016PostVFP", "UL2017", "UL2018"
function the_exit()
{ echo "$1";exit; }

function change_running_location()
{
    echo "change_running_location start..."
    outputLABEL=$1
    if [ "$2" == "-1" ]; then return 0; fi # running in test mode
    mkdir -p "$outputLABEL" ; cd "$outputLABEL" || the_exit "cd to $outputLABEL failed"
    for usedfile in ../{*.h,*.C}; do ln -s $usedfile; done
    echo "change_running_location end..."
}
function tidy_up_working_area()
{
    echo "tidy_up_working_area start..."
    outputFOLDER=$1
    for usedfile in {*.h,*.C}; do unlink $usedfile; done
    current_folder=`realpath .`
    if [ -e "$outputFOLDER/$current_folder" ];then the_exit "output file existed. Nothing put to storage"; fi
    mv $current_folder $outputFOLDER
    echo "tidy_up_working_area end..."
}
function main_code()
{
num=$1
tagALGO=$2
outputLABEL=$3
outputFOLDER=$4
orig_path=$PWD


inputCODE=makehisto.C
change_running_location $outputLABEL $num
root -b <<EOF
.L $inputCODE
Loop($num, "UL2016PreVFP", "DeepFlavour", "data", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/data.root");
//Loop($num, "UL2016PreVFP", "DeepFlavour", "gjet", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/gjet.pythia.root");
//Loop($num, "UL2016PreVFP", "DeepFlavour", "QCD", "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/qcd.madgraph.root");
EOF

if [ "$num" == "-1" ]; then exit; fi
hadd makehisto.root makehisto_*.root
tidy_up_working_area /wk_cms3/ltsai/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/
cd $orig_path
}
function exec_code()
{ main_code "$1" "$2" "$3" > "$3"_log 2>&1; }
function test_code()
{ main_code "-1" "$2" "$3"; }


function link_pt_bin_definition()
{ unlink ptbin_definitions.h; ln -s $1 ptbin_definitions.h|| the_exit "link failed to $1"; }



link_pt_bin_definition ../ptbin_definitions_testmode5.h
#main_code 0 DeepCSV DeepCSV_gjetPythia_cutIdx0_mergeBin_Orig
#main_code 3 DeepCSV DeepCSV_gjetPythia_cutIdx3_mergeBin_Orig
#main_code 4 DeepCSV DeepCSV_gjetPythia_cutIdx4_mergeBin_Orig
main_code 5 DeepCSV DeepCSV_gjetPythia_cutIdx5_mergeBin_5

#!/usr/bin/env sh
function the_exit()
{ echo "$1";exit; }

function change_running_location()
{
    echo "change_running_location start..."
    outputLABEL=$1
    if [ "$2" == "-1" ]; then return 0; fi # running in test mode
    mkdir -p "$outputLABEL" ; cd "$outputLABEL" || the_exit "cd to $outputLABEL failed"
    echo "change directory to $PWD"
    echo "change_running_location end..."
}
function tidy_up_working_area()
{
    echo "tidy_up_working_area start..."
    outputFOLDER=$1
    current_folder=`realpath .`
    current_foldername=`basename $current_folder`
    echo "[tidyup] mv $current_folder $outputFOLDER"
    if [ -e "$outputFOLDER/$current_foldername" ];then the_exit "output file existed. Nothing put to storage"; fi
    mv $current_folder $outputFOLDER
    echo "tidy_up_working_area end..."
    echo "[output] files are stored at $outputFOLDER"
}

function compile_code()
{
inputCODE=makehisto.C

g++ `root-config --libs --cflags` \
    -I/wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/MyCommonTools/cpp/ptbin_definitions/ \
    $inputCODE -O3 -o makehisto.exe
}
function main_code()
{
num=$1
tagALGO=$2
outputLABEL=$3
outputFOLDER=`realpath $4`
orig_path=$PWD


#### compile makehisto.exe before execution
change_running_location $outputLABEL $num

### valid dataEra = "2016ReReco", "UL2016PreVFP", "UL2016PostVFP", "UL2017", "UL2018"
dataERA=UL2016PostVFP
file_data=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/data.root
file_sign=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/sig.madgraph.root
file_fake=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/qcd.madgraph.root

../makehisto.exe $num $dataERA $tagALGO data $file_data > log_data 2>&1 &
../makehisto.exe $num $dataERA $tagALGO gjet $file_sign > log_gjet 2>&1 &
../makehisto.exe $num $dataERA $tagALGO QCD  $file_fake > log_QCD  2>&1 &

echo "[AllJobSentToBKG]"
wait
echo "[AllJobsFinished]"

if [ "$num" == "-1" ]; then exit; fi
hadd -f makehisto.root makehisto_*.root
tidy_up_working_area $outputFOLDER
cd $orig_path
}
function exec_code()
{ main_code "$1" "$2" "$3" "$4" > "$3"_log 2>&1; }
# test_code ignores first command
function test_code()
{ echo "[In Test Mode]"; main_code "-1" "$2" "$3" "$4"; }


function link_pt_bin_definition()
{ unlink ptbin_definitions.h; ln -s $CMSSW_BASE/src/xPhoton/MyCommonTools/cpp/ptbin_definitions/$1 ptbin_definitions.h|| the_exit "link failed to $1"; }

### end of function definition ###



### usage

#ptDEF_H=$1
#cutIDX=$2
#tagALGO=$3
#outputLABEL=$4
#outputFOLDER=$5
#
#link_pt_bin_definition $ptDEF_H
#main_code $cutIDX $tagALGO $outputLABEL $outputFOLDER

#link_pt_bin_definition ptbin_definitions_testmode5.h
#main_code 5 DeepCSV DeepCSV_gjetMadgraph_cutIdx0_mergeBin_5

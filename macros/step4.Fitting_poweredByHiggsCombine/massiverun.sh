#!/usr/bin/env sh
function the_exit()
{ echo -e "$1";exit; }
function link_pt_bin_definition()
{ unlink py_pt_ranges_definition.py; ln -s $1 py_pt_ranges_definition.py|| the_exit "link failed to $1"; }
function main_func()
{
    storageDIR=$1
    outLABEL=$2

    /bin/rm -rf tmp_BDTFit*
    inputfile=${storageDIR}/${outLABEL}/makehisto.root
    outfolder=${storageDIR}/${outLABEL}/

    echo input file    : $inputfile
    echo output folder : $outfolder
    sh stepALL_higgscombine.sh $outLABEL $inputfile || the_exit "=====\n-----\nhiggs combine running failed\n-----\n======"
    mv $outLABEL/* $outfolder
    rmdir $outLABEL
}

storage_dir=/wk_cms3/ltsai/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos

link_pt_bin_definition ../py_pt_ranges_definition_testmodeOrig.py
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx0_mergeBin_Orig
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx1_mergeBin_Orig
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx2_mergeBin_Orig
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_Orig
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_Orig
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_Orig

link_pt_bin_definition ../py_pt_ranges_definition_testmode0.py
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx0_mergeBin_0
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx1_mergeBin_0
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx2_mergeBin_0
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_0
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_0
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_0

link_pt_bin_definition ../py_pt_ranges_definition_testmode1.py
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx0_mergeBin_1
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx1_mergeBin_1
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx2_mergeBin_1
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_1
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_1
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_1

link_pt_bin_definition ../py_pt_ranges_definition_testmode2.py
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx0_mergeBin_2
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx1_mergeBin_2
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx2_mergeBin_2
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_2
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_2
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_2

link_pt_bin_definition ../py_pt_ranges_definition_testmode3.py
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx0_mergeBin_3
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx1_mergeBin_3
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx2_mergeBin_3
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_3
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_3
main_func $storage_dir DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_3


# real    409m54.174s
# user    478m42.313s
# sys     1028m40.031s

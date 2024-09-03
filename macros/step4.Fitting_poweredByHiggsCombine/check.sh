#!/usr/bin/env sh
source ./runfrag.sh
storage_dir=/wk_cms3/ltsai/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/makehistos

link_pt_bin_definition py_pt_ranges_definition_testmode9.py
#main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx5_mergeBin_5
#main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx0_mergeBin_9
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx0_mergeBin_9
bark.sh 'Job1 Finished' 'DeepCSV_gjetMadgraph_cutIdx0_mergeBin_9'
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx4_mergeBin_9
bark.sh 'Job2 Finished' 'DeepCSV_gjetMadgraph_cutIdx4_mergeBin_9'
main_func $storage_dir DeepCSV_gjetMadgraph_cutIdx5_mergeBin_9
bark.sh 'Job3 Finished' 'DeepCSV_gjetMadgraph_cutIdx5_mergeBin_9'
bark.sh 'All job finished' 'check.sh in step4.Fitting_poweredByHiggsCombine'




# code cannot be paralelly executed

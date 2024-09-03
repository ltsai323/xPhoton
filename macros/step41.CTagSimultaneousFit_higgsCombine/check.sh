#!/usr/bin/env sh
source ./runfrag.sh

link_pt_bin_definition py_pt_ranges_definition_testmode9.py
exec_in_line DeepCSV_gjetMadgraph_cutIdx0_mergeBin_9
bark.sh 'Finished Job 1/3' 'DeepCSV_gjetMadgraph_cutIdx0_mergeBin_9'
exec_in_line DeepCSV_gjetMadgraph_cutIdx4_mergeBin_9
bark.sh 'Finished Job 2/3' 'DeepCSV_gjetMadgraph_cutIdx4_mergeBin_9'
exec_in_line DeepCSV_gjetMadgraph_cutIdx5_mergeBin_9
bark.sh 'Finished Job 3/3' 'DeepCSV_gjetMadgraph_cutIdx5_mergeBin_9'
#exec_in_line DeepCSV_gjetPythia_cutIdx5_mergeBin_5
#exec_in_line DeepFlavour_gjetPythia_cutIdx4_mergeBin_5
#exec_in_line DeepFlavour_gjetPythia_cutIdx5_mergeBin_5
bark.sh 'Step41 Finished' '~'

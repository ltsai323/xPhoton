#!/usr/bin/env sh
touch py_pt_ranges_definition.py; /bin/rm py_pt_ranges_definition.py
function exec_in_line()
{
    outLABEL=$1; 
    inDIR=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/;
    sh stepALL_higgscombine.sh $outLABEL $inDIR/$outLABEL | tee logALL_$outLABEL;
    mv logALL_$outLABEL $outLABEL/;
}


ln -s ../py_pt_ranges_definition_testmodeOrig.py py_pt_ranges_definition.py
exec_in_line DeepCSV_gjetMadgraph_cutIdx0_mergeBin_Orig
exec_in_line DeepCSV_gjetMadgraph_cutIdx1_mergeBin_Orig
exec_in_line DeepCSV_gjetMadgraph_cutIdx2_mergeBin_Orig
exec_in_line DeepCSV_gjetPythia_cutIdx0_mergeBin_Orig
exec_in_line DeepCSV_gjetPythia_cutIdx1_mergeBin_Orig
exec_in_line DeepCSV_gjetPythia_cutIdx2_mergeBin_Orig
exec_in_line DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_Orig
exec_in_line DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_Orig
exec_in_line DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_Orig
exec_in_line DeepFlavour_gjetPythia_cutIdx0_mergeBin_Orig
exec_in_line DeepFlavour_gjetPythia_cutIdx1_mergeBin_Orig
exec_in_line DeepFlavour_gjetPythia_cutIdx2_mergeBin_Orig

#ln -s ../py_pt_ranges_definition_testmode0.py py_pt_ranges_definition.py
#exec_in_line DeepCSV_gjetMadgraph_cutIdx0_mergeBin_0     
#exec_in_line DeepCSV_gjetMadgraph_cutIdx1_mergeBin_0     
#exec_in_line DeepCSV_gjetMadgraph_cutIdx2_mergeBin_0     
#exec_in_line DeepCSV_gjetPythia_cutIdx0_mergeBin_0       
#exec_in_line DeepCSV_gjetPythia_cutIdx1_mergeBin_0       
#exec_in_line DeepCSV_gjetPythia_cutIdx2_mergeBin_0       
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_0 
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_0 
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_0 
#exec_in_line DeepFlavour_gjetPythia_cutIdx0_mergeBin_0   
#exec_in_line DeepFlavour_gjetPythia_cutIdx1_mergeBin_0   
#exec_in_line DeepFlavour_gjetPythia_cutIdx2_mergeBin_0   
#
#ln -s ../py_pt_ranges_definition_testmode1.py py_pt_ranges_definition.py
#exec_in_line DeepCSV_gjetMadgraph_cutIdx0_mergeBin_1     
#exec_in_line DeepCSV_gjetMadgraph_cutIdx1_mergeBin_1     
#exec_in_line DeepCSV_gjetMadgraph_cutIdx2_mergeBin_1     
#exec_in_line DeepCSV_gjetPythia_cutIdx0_mergeBin_1       
#exec_in_line DeepCSV_gjetPythia_cutIdx1_mergeBin_1       
#exec_in_line DeepCSV_gjetPythia_cutIdx2_mergeBin_1       
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_1 
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_1 
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_1 
#exec_in_line DeepFlavour_gjetPythia_cutIdx0_mergeBin_1   
#exec_in_line DeepFlavour_gjetPythia_cutIdx1_mergeBin_1   
#exec_in_line DeepFlavour_gjetPythia_cutIdx2_mergeBin_1   
#
#ln -s ../py_pt_ranges_definition_testmode2.py py_pt_ranges_definition.py
#exec_in_line DeepCSV_gjetMadgraph_cutIdx0_mergeBin_2     
#exec_in_line DeepCSV_gjetMadgraph_cutIdx1_mergeBin_2     
#exec_in_line DeepCSV_gjetMadgraph_cutIdx2_mergeBin_2     
#exec_in_line DeepCSV_gjetPythia_cutIdx0_mergeBin_2       
#exec_in_line DeepCSV_gjetPythia_cutIdx1_mergeBin_2       
#exec_in_line DeepCSV_gjetPythia_cutIdx2_mergeBin_2       
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_2 
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_2 
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_2 
#exec_in_line DeepFlavour_gjetPythia_cutIdx0_mergeBin_2   
#exec_in_line DeepFlavour_gjetPythia_cutIdx1_mergeBin_2   
#exec_in_line DeepFlavour_gjetPythia_cutIdx2_mergeBin_2   

#ln -s ../py_pt_ranges_definition_testmode3.py py_pt_ranges_definition.py
#exec_in_line DeepCSV_gjetMadgraph_cutIdx0_mergeBin_3     
#exec_in_line DeepCSV_gjetMadgraph_cutIdx1_mergeBin_3     
#exec_in_line DeepCSV_gjetMadgraph_cutIdx2_mergeBin_3     
#exec_in_line DeepCSV_gjetPythia_cutIdx0_mergeBin_3       
#exec_in_line DeepCSV_gjetPythia_cutIdx1_mergeBin_3       
#exec_in_line DeepCSV_gjetPythia_cutIdx2_mergeBin_3       
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_3 
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_3 
#exec_in_line DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_3 
#exec_in_line DeepFlavour_gjetPythia_cutIdx0_mergeBin_3   
#exec_in_line DeepFlavour_gjetPythia_cutIdx1_mergeBin_3   
#exec_in_line DeepFlavour_gjetPythia_cutIdx2_mergeBin_3   

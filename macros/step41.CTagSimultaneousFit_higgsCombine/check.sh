#!/usr/bin/env sh
touch py_pt_ranges_definition.py; /bin/rm py_pt_ranges_definition.py
function exec_in_line()
{
    outLABEL=$1; 
    inDIR=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/;
    sh stepALL_higgscombine.sh $outLABEL $inDIR/$outLABEL | tee logALL_$outLABEL;
    mv logALL_$outLABEL $outLABEL/;
    /bin/rm -r cmd_history_step2_*;
    /bin/rm -r tmp_CTag_SimulFit*;
}


ln -s ../py_pt_ranges_definition_testmode5.py py_pt_ranges_definition.py
exec_in_line DeepCSV_gjetPythia_cutIdx5_mergeBin_5

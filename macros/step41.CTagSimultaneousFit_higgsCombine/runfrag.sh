
function test_in_line()
{
    outLABEL=$1; 
    inDIR=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/makehistos/;
    sh stepALL_higgscombine.sh $outLABEL $inDIR/$outLABEL ;
}
function exec_in_line()
{
    outLABEL=$1; 
    inDIR=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/makehistos/;
    sh stepALL_higgscombine.sh $outLABEL $inDIR/$outLABEL | tee logALL_$outLABEL;
    mv logALL_$outLABEL $outLABEL/;
    /bin/rm -r cmd_history_step2_*;
    /bin/rm -r tmp_CTag_SimulFit*;
}
function link_pt_bin_definition()
{ unlink py_pt_ranges_definition.py; ln -s $CMSSW_BASE/src/xPhoton/MyCommonTools/python/ptbin_definitions/$1 py_pt_ranges_definition.py|| the_exit "link failed to $1"; }

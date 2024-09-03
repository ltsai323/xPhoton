function the_exit()
{ echo -e "$1";exit; }
function link_pt_bin_definition()
{ unlink py_pt_ranges_definition.py; ln -s $CMSSW_BASE/src/xPhoton/MyCommonTools/python/ptbin_definitions/$1 py_pt_ranges_definition.py|| the_exit "link failed to $1"; }
function main_func()
{
    storageDIR=$1
    outLABEL=$2

    touch tmp_BDTFit_a ; /bin/rm -rf tmp_BDTFit*
    inputfile=${storageDIR}/${outLABEL}/makehisto.root
    outfolder=${storageDIR}/${outLABEL}/

    echo input file    : $inputfile
    echo output folder : $outfolder
    sh stepALL_higgscombine.sh $outLABEL $inputfile || the_exit "=====\n-----\nhiggs combine running failed\n-----\n======"
    mv $outLABEL/* $outfolder
    rmdir $outLABEL
    ln -s $outfolder
    echo "testing finished"
}


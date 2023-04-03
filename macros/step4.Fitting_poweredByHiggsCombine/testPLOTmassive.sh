#!/usr/bin/env sh
function plotSingle()
{
    pEtaBin=$1
    jEtaBin=$2
    pPtBin=$3
    inputdatadetail=`realpath $4`
    inputfile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/output_step2_makehist_2016ReReco_deepcsv_CUT_NOCUT.root

dataDetail=`grep $pEtaBin:$jEtaBin:$pPtBin: $inputdatadetail`
_dataEntries_=`echo $dataDetail | awk -F':' '{ print $4 }'`
_initialNsig_=`echo $dataDetail | awk -F':' '{ print $5 }'`
_initialNbkg_=`echo $dataDetail | awk -F':' '{ print $6 }'`
_pEtaBinDesc_=`echo $dataDetail | awk -F':' '{ print $7 }'`
_jEtaBinDesc_=`echo $dataDetail | awk -F':' '{ print $8 }'`
_pPtRangeStr_=`echo $dataDetail | awk -F':' '{ print $9 }'`

cd out_fit_result/BDTFit_${pEtaBin}_${jEtaBin}_${pPtBin}/

touch a.pdf; /bin/rm *.pdf
root -b -q '../../plot.C('$pEtaBin','$jEtaBin','$pPtBin',"'$_pEtaBinDesc_'","'$_jEtaBinDesc_'","'$_pPtRangeStr_'", "'$inputfile'")' > /dev/null || exit

mv *.pdf ../../checkplot/BDTFit_${pEtaBin}_${jEtaBin}_${pPtBin}.pdf
cd -
}

mkdir -p checkplot
/bin/rm checkplot/*

for pPtBin in {0..14}; do # for merged 2016 bin
    for pEtaBin in {0..1}; do
        for jEtaBin in {0..1}; do
            plotSingle $pEtaBin $jEtaBin $pPtBin getdatadetail.txt
done; done& done

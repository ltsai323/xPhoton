pEtaBin=1
jEtaBin=1
pPtBin=18
_pEtaBinDesc_='phoetadescription'
_jEtaBinDesc_='jetetadescription'
_pPtRangeStr_='ptdescription'
inputfile=/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/output_step2_makehist_2016ReReco_deepcsv_CUT_NOCUT.root


unlink postfit.root ; ln -s out_fit_result/BDTFit_${pEtaBin}_${jEtaBin}_${pPtBin}/postfit.root

root -b -q 'plot.C('$pEtaBin','$jEtaBin','$pPtBin',"'$_pEtaBinDesc_'","'$_jEtaBinDesc_'","'$_pPtRangeStr_'", "'$inputfile'")'

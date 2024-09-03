pEtaBin=$1
jEtaBin=$2
pPtBin=$3
# automatically trasnform to abs path
inputdatadetail=`realpath $4`
outDIR=$5


cmd_file=cmd_history_step2_${pEtaBin}_${jEtaBin}_${pPtBin}.sh
#cat > $cmd_file
touch $cmd_file ; /bin/rm $cmd_file
function cmd_exec() { echo -e "[step2.EXEC] $*"; echo "$*" >> $cmd_file; "$@"; }
function the_exit() { echo -e "\nvvvvv\n$1\n^^^^^\n\n"; exit; }

dataDetail=`grep $pEtaBin,$jEtaBin,$pPtBin, $inputdatadetail`
if [ "${dataDetail}" == "" ]; then the_exit "no such bin $pEtaBin $jEtaBin $pPtBin Abort..."; fi


_dataEntries_=`echo $dataDetail | awk -F',' '{ print $4 }'`
#_initialLsig_=`echo $dataDetail | awk -F',' '{ print $5 }'`
#_initialCsig_=`echo $dataDetail | awk -F',' '{ print $6 }'`
#_initialBsig_=`echo $dataDetail | awk -F',' '{ print $7 }'`
_pEtaBinDesc_=`echo $dataDetail | awk -F',' '{ print $9 }'`
_jEtaBinDesc_=`echo $dataDetail | awk -F',' '{ print $10}'`
_pPtRangeStr_=`echo $dataDetail | awk -F',' '{ print $11}'`
_input__file_=`echo $dataDetail | awk -F',' '{ print $12}'`
#
echo dataEntries $_dataEntries_
#echo initialLsig $_initialLsig_
#echo initialCsig $_initialCsig_
#echo initialBsig $_initialBsig_
echo pEtaBinDesc $_pEtaBinDesc_
echo jEtaBinDesc $_jEtaBinDesc_
echo pPtRangeStr $_pPtRangeStr_
echo input__file $_input__file_

## collect output
outdir=CTag_SimulFit_${pEtaBin}_${jEtaBin}_${pPtBin}
tmpdir=tmp_$outdir
cmd_exec touch $tmpdir ; cmd_exec /bin/rm -rf $tmpdir
cmd_exec mkdir -p $tmpdir; cmd_exec cd $tmpdir
cmd_exec mv ../datacard_${pEtaBin}_${jEtaBin}_${pPtBin}.txt datacard.txt

echo ---- starting point ----
python3 ../frag21_extract_initValues.py ../$outDIR  $pEtaBin $jEtaBin $pPtBin $inputdatadetail # creating calculated_init_value.txt
init_values=`cat calculated_init_value.txt`
_L_init_info_=`echo $init_values | awk -F' ' '{ print $1 }'`
_C_init_info_=`echo $init_values | awk -F' ' '{ print $2 }'`
_B_init_info_=`echo $init_values | awk -F' ' '{ print $3 }'`
_total_entry_=`echo $init_values | awk -F' ' '{ print $4 }'`


_initialLsig_=`echo $_L_init_info_ | awk -F',' '{ print $1}'`
_initialCsig_=`echo $_C_init_info_ | awk -F',' '{ print $1}'`
_initialBsig_=`echo $_B_init_info_ | awk -F',' '{ print $1}'`

_LsigRange_L_=`echo $_L_init_info_ | awk -F',' '{ print $2}'`
_CsigRange_L_=`echo $_C_init_info_ | awk -F',' '{ print $2}'`
_BsigRange_L_=`echo $_B_init_info_ | awk -F',' '{ print $2}'`

_LsigRange_H_=`echo $_L_init_info_ | awk -F',' '{ print $3}'`
_CsigRange_H_=`echo $_C_init_info_ | awk -F',' '{ print $3}'`
_BsigRange_H_=`echo $_B_init_info_ | awk -F',' '{ print $3}'`
# allow constant 
cmd_exec text2workspace.py datacard.txt -o ws.root \
    --X-no-check-norm \
    -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel \
    --PO "map=.*/signal_L:mu1[$_initialLsig_,$_LsigRange_L_,$_LsigRange_H_]" \
    --PO "map=.*/signal_C:mu2[$_initialCsig_,$_CsigRange_L_,$_CsigRange_H_]" \
    --PO "map=.*/signal_B:mu3[$_initialBsig_,$_BsigRange_L_,$_BsigRange_H_]" || exit

   
cmd_exec combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on || the_exit 'combine failed'
cmd_exec PostFitShapesFromWorkspace -d datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root  -m 120 -f multidimfitTest.root:fit_mdf --postfit --print --output postfit.root || the_exit 'PostFitShapesFromWorkspace failed'
cmd_exec python3 ../combineFRAG1_plot_ctagVars.py $_pEtaBinDesc_ $_jEtaBinDesc_ $_pPtRangeStr_ ${PWD}/postfit.root || the_exit 'failed to draw plot'
for pdfFile in *.pdf; do b=`echo $pdfFile | cut -d'.' -f1`; mv $pdfFile ${b}_${pEtaBin}_${jEtaBin}_${pPtBin}.pdf; done


cmd_exec cd ..
cmd_exec mv $tmpdir $outDIR/$outdir
mv $cmd_file $outDIR/$outdir/cmd_history_step2.sh

# if the job failed.the folder tmp_${outdir} would leave.

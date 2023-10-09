pEtaBin=$1
jEtaBin=$2
pPtBin=$3
# automatically trasnform to abs path
inputdatadetail=`realpath $4`
outDIR=$5


cat > cmd_history_step2.sh
function cmd_exec() { echo -e "[step2.EXEC] $*"; echo "$*" >> cmd_history_step2.sh; "$@"; }
function the_exit() { echo -e "\nvvvvv\n$1\n^^^^^\n\n"; exit; }

dataDetail=`grep $pEtaBin,$jEtaBin,$pPtBin, $inputdatadetail`
if [ "${dataDetail}" == "" ]; then the_exit "no such bin $pEtaBin $jEtaBin $pPtBin Abort..."; fi


_dataEntries_=`echo $dataDetail | awk -F',' '{ print $4 }'`
_initialLsig_=`echo $dataDetail | awk -F',' '{ print $5 }'`
_initialCsig_=`echo $dataDetail | awk -F',' '{ print $6 }'`
_initialBsig_=`echo $dataDetail | awk -F',' '{ print $7 }'`
_pEtaBinDesc_=`echo $dataDetail | awk -F',' '{ print $9 }'`
_jEtaBinDesc_=`echo $dataDetail | awk -F',' '{ print $10}'`
_pPtRangeStr_=`echo $dataDetail | awk -F',' '{ print $11}'`
_input__file_=`echo $dataDetail | awk -F',' '{ print $12}'`
#
echo dataEntries $_dataEntries_
echo initialLsig $_initialLsig_
echo initialCsig $_initialCsig_
echo initialBsig $_initialBsig_
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
# step1 test finished
# allow constant 
cmd_exec text2workspace.py datacard.txt -o ws.root \
    --X-no-check-norm \
    -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel \
    --PO "map=.*/signal_L:mu1[$_initialLsig_,0,$_dataEntries_]" \
    --PO "map=.*/signal_C:mu2[$_initialCsig_,0,$_dataEntries_]" \
    --PO "map=.*/signal_B:mu3[$_initialBsig_,0,$_dataEntries_]" || exit
   
cmd_exec combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on || the_exit 'combine failed'
cmd_exec PostFitShapesFromWorkspace -d datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root  -m 120 -f multidimfitTest.root:fit_mdf --postfit --print --output postfit.root || the_exit 'PostFitShapesFromWorkspace failed'
cmd_exec python3 ../combineFRAG1_plot_ctagVars.py $_pEtaBinDesc_ $_jEtaBinDesc_ $_pPtRangeStr_ ${PWD}/postfit.root || the_exit 'failed to draw plot'
for pdfFile in *.pdf; do b=`echo $pdfFile | cut -d'.' -f1`; mv $pdfFile ${b}_${pEtaBin}_${jEtaBin}_${pPtBin}.pdf; done


cmd_exec cd ..
cmd_exec mv $tmpdir $outDIR/$outdir

# if the job failed.the folder tmp_${outdir} would leave.

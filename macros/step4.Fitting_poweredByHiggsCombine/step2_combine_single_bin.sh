pEtaBin=$1
jEtaBin=$2
pPtBin=$3
# automatically trasnform to abs path
inputfile=`realpath $4`
inputdatadetail=`realpath $5`


# collect output
mkdir -p out_fit_result
outdir=BDTFit_${pEtaBin}_${jEtaBin}_${pPtBin}
tmpdir=tmp_$outdir
touch $tmpdir; /bin/rm -rf $tmpdir
mkdir -p $tmpdir; cd $tmpdir

function the_exit()
{ echo -e "\nvvvvv\n$1\n^^^^^\n"; exit 0; }



dataDetail=`grep $pEtaBin:$jEtaBin:$pPtBin: $inputdatadetail`
_dataEntries_=`echo $dataDetail | awk -F':' '{ print $4 }'`
_initialNsig_=`echo $dataDetail | awk -F':' '{ print $5 }'`
_initialNbkg_=`echo $dataDetail | awk -F':' '{ print $6 }'`
_pEtaBinDesc_=`echo $dataDetail | awk -F':' '{ print $7 }'`
_jEtaBinDesc_=`echo $dataDetail | awk -F':' '{ print $8 }'`
_pPtRangeStr_=`echo $dataDetail | awk -F':' '{ print $9 }'`

echo $_dataEntries_
echo $_initialNsig_
echo $_initialNbkg_
echo $_pEtaBinDesc_
echo $_jEtaBinDesc_
echo $_pPtRangeStr_

python3 ../combineFRAG1_py_makedatacard.py $pEtaBin $jEtaBin $pPtBin $inputfile || the_exit "combineFRAG1 failed datacard.txt creation"
text2workspace.py datacard.txt -o ws.root \
    -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel \
    --PO "map=.*/signalMC:mu1[$_initialNsig_,0,$_dataEntries_]" \
    --PO "map=.*/bkgShape:mu2[$_initialNbkg_,0,$_dataEntries_]"  || the_exit "text2workspace failed to generate ws.root"
    
combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on && \
PostFitShapesFromWorkspace -d datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root  -m 120 -f multidimfitTest.root:fit_mdf --postfit --print --output postfit.root || the_exit "PostFitShapeFromWorkspace failed to activate the command"
root -b -q '../combineFRAG2_plot.C('$pEtaBin','$jEtaBin','$pPtBin',"'$_pEtaBinDesc_'","'$_jEtaBinDesc_'","'$_pPtRangeStr_'", "'$inputfile'")' || "combineFRAG2_plot failed to active the command"


cd ..; mv $tmpdir out_fit_result/$outdir

# if the job failed.the folder tmp_${outdir} would leave.

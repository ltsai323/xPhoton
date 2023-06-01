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


# generate getdatadetail.txt
#python3 ../py_GetDataDetail.py $pEtaBin $jEtaBin $pPtBin 2016ReReco $inputfile || exit

dataDetail=`grep $pEtaBin:$jEtaBin:$pPtBin: $inputdatadetail`
_dataEntries_=`echo $dataDetail | awk -F':' '{ print $4 }'`
_initialNsig_=`echo $dataDetail | awk -F':' '{ print $5 }'`
_initialNbkg_=`echo $dataDetail | awk -F':' '{ print $6 }'`
_pEtaBinDesc_=`echo $dataDetail | awk -F':' '{ print $7 }'`
_jEtaBinDesc_=`echo $dataDetail | awk -F':' '{ print $8 }'`
_pPtRangeStr_=`echo $dataDetail | awk -F':' '{ print $9 }'`

python3 ../py_makedatacard.py $pEtaBin $jEtaBin $pPtBin $inputfile || exit
text2workspace.py datacard.txt -o ws.root \
    -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel \
    --PO "map=.*/signalMC:mu1[$_initialNsig_,0,$_dataEntries_]" \
    --PO "map=.*/bkgShape:mu2[$_initialNbkg_,0,$_dataEntries_]"  || exit
    
combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on && \
PostFitShapesFromWorkspace -d datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root  -m 120 -f multidimfitTest.root:fit_mdf --postfit --print --output postfit.root || exit
root -b -q '../plot.C('$pEtaBin','$jEtaBin','$pPtBin',"'$_pEtaBinDesc_'","'$_jEtaBinDesc_'","'$_pPtRangeStr_'", "'$inputfile'")' || exit


cd ..; mv $tmpdir out_fit_result/$outdir

# if the job failed.the folder tmp_${outdir} would leave.

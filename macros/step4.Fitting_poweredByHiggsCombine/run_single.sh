pEtaBin=$1
jEtaBin=$2
pPtBin=$3
# absolute path required
inputfile=/home/ltsai/Work/github/xPhoton/macros/step2.makehistos/DeepFlavour_cutIdx0/makehisto.root


# collect output
mkdir -p out_fit_result
outdir=BDTFit_${pEtaBin}_${jEtaBin}_${pPtBin}
tmpdir=tmp_$outdir
touch $tmpdir; /bin/rm -rf $tmpdir
mkdir -p $tmpdir; cd $tmpdir


# generate getdatadetail.txt
python3 ../py_GetDataDetail.py $pEtaBin $jEtaBin $pPtBin 2016ReReco $inputfile || exit

_dataEntries_=`tail -n1 getdatadetail.txt | awk -F':' '{ print $1 }'`
_initialNsig_=`tail -n1 getdatadetail.txt | awk -F':' '{ print $2 }'`
_initialNbkg_=`tail -n1 getdatadetail.txt | awk -F':' '{ print $3 }'`
_pEtaBinDesc_=`tail -n1 getdatadetail.txt | awk -F':' '{ print $4 }'`
_jEtaBinDesc_=`tail -n1 getdatadetail.txt | awk -F':' '{ print $5 }'`
_pPtRangeStr_=`tail -n1 getdatadetail.txt | awk -F':' '{ print $6 }'`

python3 ../py_makedatacard.py $pEtaBin $jEtaBin $pPtBin $inputfile || exit
text2workspace.py datacard.txt -o ws.root \
    -P HiggsAnalysis.CombinedLimit.PhysicsModel:multiSignalModel \
    --PO "map=.*/signalMC:mu1[$_initialNsig_,0,$_dataEntries_]" \
    --PO "map=.*/bkgShape:mu2[$_initialNbkg_,0,$_dataEntries_]"  || exit
    
combine --saveWorkspace -M MultiDimFit -d ws.root --saveFitResult --saveNLL --robustFit on && \
PostFitShapesFromWorkspace -d datacard.txt -w higgsCombineTest.MultiDimFit.mH120.root  -m 120 -f multidimfitTest.root:fit_mdf --postfit --print --output postfit.root || exit
root -b -q '../plot.C("'$_pEtaBinDesc_'","'$_jEtaBinDesc_'","'$_pPtRangeStr_'")' || exit


cd ..; mv $tmpdir out_fit_result/$outdir

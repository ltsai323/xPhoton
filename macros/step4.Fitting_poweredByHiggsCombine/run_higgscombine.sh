outputLabel=$1
inputfile=$2

if [ "$2" == "" ]; then
    echo "input root file not found! Abort"
    echo "argument : 1: output label. 2: input root file"
    exit
fi

function raiseError() { echo 'Please load higgs combine environment!';  exit 1; }
sh ~/goToWorkSession/higgsCombine.sh check && echo 'passed higgs combine env checking' || raiseError


touch out_fit_result; /bin/rm -r out_fit_result # clean up
echo "ptbin/I:EBEE/I:jetbin/I:fitvalue/F:fiterror/F" > 2016ReReco.data.yield.dat
echo "ptbin/I:EBEE/I:jetbin/I:fitvalue/F:fiterror/F" > 2016ReReco.data.bkg.dat


python3 py_GetDataDetail.py 2016ReReco $inputfile || exit
echo [$outputLabel] processing run_single.sh
#for pPtBin in {0..20}; do
for pPtBin in {0..15}; do # for merged 2016 bin
    for pEtaBin in {0..1}; do
        for jEtaBin in {0..1}; do

logfile=log_${pEtaBin}_${jEtaBin}_${pPtBin}
sh run_single.sh $pEtaBin $jEtaBin $pPtBin $inputfile getdatadetail.txt > $logfile 2>&1
sh extractFitValue.sh $logfile $pEtaBin $jEtaBin $pPtBin 2016ReReco.data.yield.dat 2016ReReco.data.bkg.dat
done; done& done

wait

echo [$outputLabel] collecting results
mv *.dat out_fit_result
mkdir out_fit_result/logs; mv log_* out_fit_result/logs/

sh collect_result.sh $outputLabel
echo [$outputLabel] all job finished

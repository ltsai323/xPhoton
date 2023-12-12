outputLabel=$1
inputfile=$2
data_era=UL2016PreVFP

if [ "$2" == "" ]; then
    echo "input root file not found! Abort"
    echo "argument : 1: output label. 2: input root file"
    exit
fi

function raiseError() { echo 'Please load higgs combine environment!';  exit 1; }
sh ~/goToWorkSession/higgsCombine.sh check && echo 'passed higgs combine env checking' || raiseError


echo "ptbin/I:EBEE/I:jetbin/I:fitvalue/F:fiterror/F" > ${data_era}.data.yield.dat
echo "ptbin/I:EBEE/I:jetbin/I:fitvalue/F:fiterror/F" > ${data_era}.data.bkg.dat


python3 step1_py_GetDataDetail.py $data_era $inputfile || exit
echo [$outputLabel] processing run_single.sh
for pPtBin in {0..20}; do # assigned binning > actual binning is allowed
    for pEtaBin in {0..1}; do
        for jEtaBin in {0..1}; do

logfile=log_${pEtaBin}_${jEtaBin}_${pPtBin}
sh step2_combine_single_bin.sh $pEtaBin $jEtaBin $pPtBin $inputfile getdatadetail.txt > $logfile 2>&1
sh step3_extractFitValue.sh $logfile $pEtaBin $jEtaBin $pPtBin ${data_era}.data.yield.dat ${data_era}.data.bkg.dat
done; done& done

wait

echo [$outputLabel] collecting results
mv *.dat out_fit_result
mkdir out_fit_result/logs; mv log_* out_fit_result/logs/

sh step4_collect_result.sh $outputLabel && mv out_fit_result $outputLabel
echo [$outputLabel] all job finished

echo tmp_BDTFit_blah is kept. you can simply delete them.

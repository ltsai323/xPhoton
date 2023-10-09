outputLabel=$1
inputfolder=$2
data_era=UL2016PreVFP

### note: define py_pt_definition.py before execute this code  ###

if [ "$2" == "" ]; then
    echo "input root file not found! Abort"
    echo "argument : 1: output label. 2: input root file"
    exit
fi
function cmd_exec() { echo -e "[stepALL.EXEC] $*"; "$@"; }
function the_exit() { echo -e "\nvvvvv\n$1\n^^^^^\n\n"; exit; }

sh ~/goToWorkSession/higgsCombine.sh check && echo 'passed higgs combine env checking' || the_exit 'Higgs Combine package needed!'


cmd_exec sh step1_preparsion.sh $data_era $inputfolder > log_step1_preparsion || the_exit 'step1 execution failed'

touch out_fit_result; /bin/rm -r out_fit_result
mkdir -p out_fit_result
echo [$outputLabel] processing step2: combine in single bin.
for pPtBin in {0..20}; do # assigned binning > actual binning is allowed
    for pEtaBin in {0..1}; do
        for jEtaBin in {0..1}; do
logfile=log_${pEtaBin}_${jEtaBin}_${pPtBin}
sh step2_combine_single_bin.sh $pEtaBin $jEtaBin $pPtBin getdatadetail.csv out_fit_result/ > $logfile 2>&1
done; done& done; wait

cmd_exec python3 step3_collect_postfit_info.py $data_era out_fit_result/ || the_exit 'step3 execution failed'

echo [$outputLabel] collecting results
mv *.csv out_fit_result/; mkdir -p out_fit_result/logs; mv log_* out_fit_result/logs/

outputFolder=$inputfolder/CTagSimultaneousFit
sh step4_collect_result.sh $outputLabel && mv out_fit_result $outputFolder && ln -s $outputFolder $outputLabel || the_exit 'step4 execution failed'
echo [$outputLabel] all job finished
echo [$ouptutLabel] Output is located at $outputFolder
#sh step4_collect_result.sh $outputLabel && mv out_fit_result $outputLabel || the_exit 'step4 execution failed'
#echo [$ouptutLabel] Output is located at $outputLabel



echo tmp_blah_blah is kept. you can simply delete them.

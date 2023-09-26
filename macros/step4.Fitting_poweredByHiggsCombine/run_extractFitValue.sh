echo "ptbin/I:EBEE/I:jetbin/I:fitvalue/F:fiterror/F" > 2016ReReco.data.yield.dat
echo "ptbin/I:EBEE/I:jetbin/I:fitvalue/F:fiterror/F" > 2016ReReco.data.bkg.dat

for pPtBin in {0..15}; do # for merged 2016 bin
    for pEtaBin in {0..1}; do
        for jEtaBin in {0..1}; do

logfile=out_fit_result/logs/log_${pEtaBin}_${jEtaBin}_${pPtBin}
sh extractFitValue.sh $logfile $pEtaBin $jEtaBin $pPtBin 2016ReReco.data.yield.dat 2016ReReco.data.bkg.dat
done; done& done

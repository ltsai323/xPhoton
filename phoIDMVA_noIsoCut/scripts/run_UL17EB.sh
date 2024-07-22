#!/usr/bin/env sh
# the whole running progress
# this running file is not well tested.

outFolder=TMVA_UL2017_EB
inputJson=../data/TMVATrainingUL2017PythiaEB.json

function EXIT {
echo -e '\n\n'
echo "[$outFolder] : " $1
echo -e '\n\n'
exit 1
}

mkdir $outFolder || EXIT "output folder failed"
cd $outFolder
#../exec.ReweightTrainingSample.sh
exec_ReweightTrainingSample \
        /wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/xPhoton/bin/step2.mergePDversion/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root \
        /wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/xPhoton/bin/step2.mergePDversion/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root \
        /wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/xPhoton/bin/step2.mergePDversion/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root \
        || EXIT 'Reweight failed'
hadd rw_out.root rw_outFrag*.root || EXIT 'hadd failed'

#../exec.TMVATraining.sh
exec_TMVATraining ../$inputJson || EXIT 'training failed'

../TMVAReport.sh hiii.root

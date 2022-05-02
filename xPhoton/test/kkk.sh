#!/usr/bin/env sh
for ifile in crab_UL18Data_miniAODv2__EGamma__Run2018A-UL2018_MiniAODv2-v1.root crab_UL18Data_miniAODv2__EGamma__Run2018B-UL2018_MiniAODv2-v1.root crab_UL18Data_miniAODv2__EGamma__Run2018C-UL2018_MiniAODv2-v1.root crab_UL18Data_miniAODv2__EGamma__Run2018D-UL2018_MiniAODv2-v2.root
do
    cat > hi.json <<EOF
{
    "nJobs": 10,
    "updateMVA":true,
    "updatePU":false,
    "updateBTagCalibration":false,
    "updateChIso":true,
    "isMC":false,
    "dataera":"UL2018",
    "InputFiles":[ "$ifile" ],

    "xmlFiles":[
        "/home/ltsai/ReceivedFile/hii/TMVA_UL2018_EB/weights/TMVAnalysis_BDT.weights.xml",
        "/home/ltsai/ReceivedFile/hii/TMVA_UL2018_EE/weights/TMVAnalysis_BDT.weights.xml"
        ],
    "OutputFileName":"updated_$ifile"
}
EOF
    exec_xPhotonInfoUpdate hi.json&
    sleep 120
done

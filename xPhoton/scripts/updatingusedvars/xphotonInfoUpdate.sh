#!/usr/bin/env sh
ifile=$1
relfile=`echo $ifile | rev | cut -d'/' -f1 | rev`
echo $relfile
cat > hi.json <<EOF
{
    "nJobs": 10,
    "updateMVA":true,
    "updatePU":false,
    "updateBTagCalibration":false,
    "updateChIso":true,
    "isMC":true,
    "dataera":"UL2018",
    "InputFiles":[ "$ifile" ],

    "xmlFiles":[
        "/home/ltsai/ReceivedFile/hii/TMVA_UL2018_EB/weights/TMVAnalysis_BDT.weights.xml",
        "/home/ltsai/ReceivedFile/hii/TMVA_UL2018_EE/weights/TMVAnalysis_BDT.weights.xml"
        ],
    "OutputFileName":"updated_$relfile"
}
EOF
time exec_xPhotonInfoUpdate hi.json&

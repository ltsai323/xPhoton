#!/usr/bin/env sh

name=DefaultBDT
cat > MLrun.json <<EOF
{
    "updateMVA": true,
    "updatePU": false,
    "updateBTagCalibration": false,
    "isMC": false,
    "dataera": "UL2018",
    "InputFiles": ["/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/scripts/simpletest_0.root"],
    "OutputFileName":"mvaUpdated.$name.root",
    "xmlFiles":[
    "../bin/default_EB/weights/TMVAClassification_BDT.weights.xml",
    "../bin/default_EE/weights/TMVAClassification_BDT.weights.xml"
    ]
}
EOF
exec_xPhotonInfoUpdate2 MLrun.json

root -b mvaUpdated.$name.root <<EOF
t->Draw("mva", "isMatched == 1" )
c1->SaveAs( Form("%s_%s.png","sigPho", "$name") )
t->Draw("mva", "isMatched != 1" )
c1->SaveAs( Form("%s_%s.png","bkgPho", "$name") )
EOF

#!/usr/bin/env sh

name=noMCEvtWeight
cat > MLrun.json <<EOF
{
    "updateMVA": true,
    "updatePU": false,
    "updateBTagCalibration": false,
    "isMC": false,
    "dataera": "UL2018",
    "InputFiles": [ "../../xPhoton/scripts/simpletest_0.root" ],
    "OutputFileName":"mvaUpdated.$name.root",
    "xmlFiles":[
"../scripts/TMVA_UL2018_EB/weights/TMVAnalysis_BDT.weights.xml",
"../scripts/TMVA_UL2018_EE/weights/TMVAnalysis_BDT.weights.xml"
    ]
}
EOF
#exec_xPhotonInfoUpdate2 MLrun.json

root -b mvaUpdated.$name.root <<EOF
t->Draw("mva", "fabs(recoEta) > 1.5 && chIsoRaw<2" )
c1->SaveAs( Form("%s_%s.png","sigPho_MEta", "$name") )
t->Draw("mva", "fabs(recoEta) > 1.5 && chIsoRaw > 5" )
c1->SaveAs( Form("%s_%s.png","sigPho_PEta", "$name") )
EOF
echo 'To show the plot, you need to execute '
echo "icat sigPho_PEta_$name.png sigPho_MEta_$name.png"


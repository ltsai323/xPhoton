#!/usr/bin/env sh
cat > MLrun.json <<EOF
{
    "nJobs": 10,
    "updateMVA": true,
    "updatePU": false,
    "updateBTagCalibration": false,
    "isMC": false,
    "dataera": "UL2018",
    "InputFiles": ["simpletest_0.root"],
    "OutputFileName":"mvaUpdated.simpletest.root"
}
EOF
exec_xPhotonInfoUpdate MLrun.json

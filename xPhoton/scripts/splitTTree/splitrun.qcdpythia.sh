#!/usr/bin/env sh
for ii in {0..9}; do
    echo $ii
cat > MLrun_${ii}.json <<EOF
{
    "nJobs": 10,
    "updateMVA": true,
    "updatePU": false,
    "updateBTagCalibration": false,
    "isMC": true,
    "dataera": "UL2018",
    "InputFiles": ["/home/ltsai/cms3/tmpfiles/QCDPythiaFrag_${ii}.root"],
    "OutputFileName":"mvaUpdated.qcdpythiaFrag.$ii.root"
}
EOF
exec_xPhotonInfoUpdate MLrun_${ii}.json &
done

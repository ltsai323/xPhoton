#!/usr/bin/env sh
for ii in {0..9}; do
    echo $ii
cat > MLrun_${ii}.json <<EOF
{
    "nJobs": 10,
    "updateMVA": true,
    "updatePU": false,
    "updateBTagCalibration": false,
    "isMC": false,
    "dataera": "UL2018",
    "InputFiles": ["/home/ltsai/cms3/tmpfiles/sigPythiaFrag_${ii}.root"],
    "OutputFileName":"mvaUpdated.sigpythiaFrag.$ii.root"
}
EOF
exec_xPhotonInfoUpdate MLrun_${ii}.json &
done


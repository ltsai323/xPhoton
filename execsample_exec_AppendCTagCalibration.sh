scram b 
time exec_AppendCTagCalibration 2016ReReco xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xPhoton.PUhat/crab_QCDmadgraph_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root  test.root && root -b test.root <<EOF
t->Show(3)
EOF


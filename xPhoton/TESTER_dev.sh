#!/usr/bin/env sh
#echo "data checking"
#./bin/exe.xPhotonRunner ggtree_datasample.root 0 && mv output_job_PhotonHFJet_0.root output_job_PhotonHFJet_dataorig.root
#make test; ./dev/exe.test.xPhotonRunner ggtree_datasample.root 1 && ./scripts/quickcheck/eventcontent.sh output_job_PhotonHFJet_dataorig.root output_job_PhotonHFJet_1.root 

echo "mc checking"
#./bin/exe.xPhotonRunner ggtree_mcsample.root 0 && mv output_job_PhotonHFJet_0.root output_job_PhotonHFJet_mcorig.root
make test; ./dev/exe.test.xPhotonRunner ggtree_mcsample.root 1 && ./scripts/quickcheck/eventcontent.sh output_job_PhotonHFJet_mcorig.root output_job_PhotonHFJet_1.root 

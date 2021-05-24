#!/usr/bin/env sh
make test; ./dev/exe.test.xPhotonRunner ggtree_datasample.root 1 && ./scripts/quickcheck/eventcontent.sh output_job_PhotonHFJet_orig.root output_job_PhotonHFJet_1.root 

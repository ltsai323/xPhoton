fin=/home/ltsai/ReceivedFile/GJet/test/ggtree_datasample.root

./bin/exe.xPhotonRunner      $fin 0 >/dev/null 2>&1
./dev/exe.test.xPhotonRunner $fin 1 >/dev/null 2>&1
scripts/quickcheck/eventcontent.sh output_job_PhotonHFJet_0.root output_job_PhotonHFJet_1.root

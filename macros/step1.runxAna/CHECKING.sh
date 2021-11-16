

keepoldfile=$1

if [ "$keepoldfile" != "" ]; then
    echo Previous results are kept
    mv output_job_PhotonHFJet_1.root kept.output_job_PhotonHFJet_1.root
    mv datasample_xPhotonHFJet.C.root kept.datasample_xPhotonHFJet.C.root
    mv datasample_xPhotonHFJet_subVtxInfo.C.root kept.datasample_xPhotonHFJet_subVtxInfo.C.root
fi

#sh running.sh xPhotonHFJet.C ; sh running.sh xPhotonHFJet_subVtxInfo.C ; exec_xPhotonRunner ggtree_mc_10.root 1

echo 'xAna 15 ver.'
ifile=datasample_xPhotonHFJet.C.root
sh checkSingleTree.sh $ifile > log.orig15

echo 'xAna subVtxInfo'
ifile=datasample_xPhotonHFJet_subVtxInfo.C.root
sh checkSingleTree.sh $ifile > log.orig16

echo 'my xPhoton'
ifile=output_job_PhotonHFJet_1.root
sh checkSingleTree.sh $ifile | sed 's/-99/ -1/' > log.myxPhoton

diff log.orig15 log.myxPhoton

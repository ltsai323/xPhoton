fin=ggtree_mc_1.root

dev/exe.test.xPhotonRunner $fin 1

#  #  echo 'old file'
#  ifile=output_job_PhotonHFJet_devRec.root
#  sh checktreeentries.sh $ifile
#  sh ../macros/step1.runxAna/checkSingleTree.sh $ifile > log.oldfile

echo 'new file'
ifile=output_job_PhotonHFJet_1.root
sh checktreeentries.sh $ifile
sh ../macros/step1.runxAna/checkSingleTree.sh $ifile > log.newfile

diff log.oldfile log.newfile

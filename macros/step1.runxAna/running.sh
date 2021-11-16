fexec=$1
#ifile="ggtree_datasample.root"
ifile="ggtree_mc_10.root"
echo $ifile

root -b <<EOF
cout << "$ifile";
.L $fexec
xPhotonHFJet("${ifile}", 0)
EOF
mv output_job_PhotonHFJet_0.root datasample_${fexec}.root


##  ## ifile="ggtree_mcsample.root"
##  ## echo $ifile
##  ## 
##  ## root -b <<EOF
##  ## cout << "$ifile";
##  ## .L $fexec
##  ## xPhotonHFJet("${ifile}", 0)
##  ## EOF
##  ## mv `ls | /bin/grep output ` mcsample_${fexec}.root



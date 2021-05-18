fexec=$1
ifile="ggtree_datasample.root"
echo $ifile

root -b <<EOF
cout << "$ifile";
.L $fexec
xPhotonHFJet("${ifile}", 0)
EOF
mv `ls | /bin/grep output ` datasample_${fexec}.root


##  ## ifile="ggtree_mcsample.root"
##  ## echo $ifile
##  ## 
##  ## root -b <<EOF
##  ## cout << "$ifile";
##  ## .L $fexec
##  ## xPhotonHFJet("${ifile}", 0)
##  ## EOF
##  ## mv `ls | /bin/grep output ` mcsample_${fexec}.root



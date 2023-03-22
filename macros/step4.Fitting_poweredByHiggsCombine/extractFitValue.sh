
inputFILE=$1
pETAbin=$2
jETAbin=$3
pPTbin=$4

sigFILE=$5
bkgFILE=$6


fitSig=`grep mu1 $inputFILE | grep ':' | cut -d'+' -f2`
fitBkg=`grep mu2 $inputFILE | grep ':' | cut -d'+' -f2`

echo "$pPTbin $pETAbin $jETAbin $fitSig 0" >> $sigFILE
echo "$pPTbin $pETAbin $jETAbin $fitBkg 0" >> $bkgFILE

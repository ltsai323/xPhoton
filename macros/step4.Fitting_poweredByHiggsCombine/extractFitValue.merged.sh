# merge fit result from yield and fake files into single file

inputFILE=$1
pETAbin=$2
jETAbin=$3
pPTbin=$4

outFILE=$5


fitSig=`grep 'mu1 :' $inputFILE | cut -d'+' -f2`
fitBkg=`grep 'mu2 :' $inputFILE | cut -d'+' -f2`

echo "$pPTbin $pETAbin $jETAbin $fitSig 0 $fitBkg 0" >> $outFILE

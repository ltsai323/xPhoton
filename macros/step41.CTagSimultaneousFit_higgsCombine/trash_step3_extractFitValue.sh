
inputFILE=$1
pETAbin=$2
jETAbin=$3
pPTbin=$4

sigFILE=$5
bkgFILE=$6


fitSig=`grep 'mu1 :' $inputFILE | cut -d'+' -f2`
fitBkg=`grep 'mu2 :' $inputFILE | cut -d'+' -f2`
#fitSig=`grep 'mu1 :' $inputFILE | grep ':' | grep '+' | cut -d'+' -f2`
#fitBkg=`grep 'mu2 :' $inputFILE | grep ':' | grep '+' | cut -d'+' -f2`

if [ "${fitSig}" != "" ]; then
    echo "$pPTbin $pETAbin $jETAbin $fitSig 0" >> $sigFILE
fi
if [ "${fitBkg}" != "" ]; then
    echo "$pPTbin $pETAbin $jETAbin $fitBkg 0" >> $bkgFILE
fi

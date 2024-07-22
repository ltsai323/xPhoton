#!/usr/bin/env sh
inputpath=$1
filenameOnly=`extractfilename.sh $inputpath`
outputDir=$2

mydir=$filenameOnly

if [ "$1" == "" ]; then
    echo "you need to input a text file"
    exit
fi

mkdir -p $outputDir/$mydir
idx=0
for file in `cat $inputpath`;
do
    xrdcp -f $file running.root
    /home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/bin/exe.xPhotonRunner running.root $idx
    let "idx=idx+1"
    mv output*.root $outputDir/$mydir/
done

hadd $outputDir/$mydir.root $outputDir/$mydir/*.root

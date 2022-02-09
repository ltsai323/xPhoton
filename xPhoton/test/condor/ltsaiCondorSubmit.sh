#!/usr/bin/env sh

textPath=$1

outputDir=$PWD
if [ "$textPath" == "" ]; then
    echo "you need to input a text file"
    exit
fi
filenameOnly=`extractfilename.sh $textPath`
mydir=$filenameOnly


mkdir -p $outputDir/$mydir
idx=0
cd $outputDir/$mydir
for file in `cat $outputDir/$textPath`;
do
    xrdcp -f $file running.root
    exec_xPhotonRunnerUL2018 running.root $idx
    let "idx=idx+1"
    /bin/rm running.root
done

hadd ../$mydir.root output*.root

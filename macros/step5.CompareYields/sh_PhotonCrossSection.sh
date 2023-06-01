#!/usr/bin/env sh
outputDir=2016ReReco_orig_binning

touch a.pdf; /bin/rm *.pdf 
touch $outputDir ; /bin/rm -rf $outputDir


python3 PhotonCrossSection_Comparison.py
#python3 PhotonCrossSection.py


mkdir $outputDir; mv *.pdf $outputDir/

echo "output directory : $outputDir"

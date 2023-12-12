#!/usr/bin/env sh
outputDir=NLO_loop_sm_no_b_mass_NNPDF3p1nnlo

touch a.pdf; /bin/rm *.pdf 
touch $outputDir ; /bin/rm -rf $outputDir


python3 PhotonCrossSection_Comparison.py
#python3 PhotonCrossSection.py


mkdir $outputDir; mv *.pdf $outputDir/

echo "output directory : $outputDir"

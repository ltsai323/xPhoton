#!/usr/bin/env sh
# purpose : Find fake sample and process run.sh
# 1. relink isovsbdt_template.root for use script.
# 2. run the script.
# 3. move outputs into storage

# define fit source
ifile=isovsbdt_template.root
unlink $ifile || rm $ifile
ifile=isovsbdt_fragments.sig.root
unlink $ifile || rm $ifile
ifile=isovsbdt_fragments.bkg.root
unlink $ifile || rm $ifile

sigfragment=../step8.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_sig.root
bkgfragment=../step8.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_bkg.root
originalfit=../step8.ClosureTest_SampleCreation/storeroot/iso_fakesample0.root                      

ln -s $sigfragment isovsbdt_fragments.sig.root
ln -s $bkgfragment isovsbdt_fragments.bkg.root
ln -s $originalfit isovsbdt_template.root
# define fit source end


python FitYields.allbinning.py > log.fittingres
python logInfoExtraction.py log.fittingres

sh ./ComparisonPlot_FitOverTruth.sh

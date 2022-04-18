#!/usr/bin/env sh
# fit.py has been verified the same as original fit.
ifile=isovsbdt_template.root
unlink $ifile || rm $ifile
ifile=isovsbdt_fragments.sig.root
unlink $ifile || rm $ifile
ifile=isovsbdt_fragments.bkg.root
unlink $ifile || rm $ifile

originalfit=../step8.ClosureTest_SampleCreation/storeroot/iso_fakesample0.root                      

# only used in Fake
sigfragment=../step8.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_sig.root
bkgfragment=../step8.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_bkg.root

ln -s $sigfragment isovsbdt_fragments.sig.root
ln -s $bkgfragment isovsbdt_fragments.bkg.root
ln -s $originalfit isovsbdt_template.root

python FitYields.allbinning.py > log.fittingres
python LogInfoExtraction.py log.fittingres




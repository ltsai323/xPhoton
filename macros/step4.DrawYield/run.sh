#!/usr/bin/env sh
# fit.py has been verified the same as original fit.

inputfile=$1
fakeSig=$2 # optional
fakeBkg=$3 # optional

# clean up
ifile=isovsbdt_template.root; unlink $ifile || rm $ifile
ln -s $inputfile isovsbdt_template.root

if [ "$fakeSig" != "" ]; then
    ifile=isovsbdt_fragments.sig.root; unlink $ifile || rm $ifile
    ifile=isovsbdt_fragments.bkg.root; unlink $ifile || rm $ifile
# only used in Fake
#fakeSig=../step8.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_sig.root
#fakeBkg=../step8.ClosureTest_SampleCreation/storeroot/fragmentsIsovsBDT/iso_fakesample0_bkg.root

    ln -s $fakeSig isovsbdt_fragments.sig.root
    ln -s $fakeBkg isovsbdt_fragments.bkg.root
fi



# cleaning figure storage
touch plots ; /bin/rm -r plots; mkdir plots


python FitYields.allbinning.JetSel.py > log.fittingres.jetSel
python LogInfoExtraction.py log.fittingres.jetSel
touch fit_jetSel; /bin/rm -r fit_jetSel; mkdir fit_jetSel; mv *.dat fit_jetSel; mv plots fit_jetSel

#python CountYields.pythia.py > log.signalMCres
#python LogInfoExtraction.py log.signalMCres
#mv data.yield.dat sigmc.yield.dat

python FitYields.allbinning.py > log.fittingres
python LogInfoExtraction.py log.fittingres


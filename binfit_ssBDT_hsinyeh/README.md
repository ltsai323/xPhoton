# Calculate photon yield and compare with 2015 results

Make Iso vs BDT histograms ( 1:MC, 2:Data ). Change the input samples in MakeHisto.h
``
python run.py 1
python run.py 2
``

Make Iso vs BDT fitting templates (get rid of unused histograms in the first steps, could combine it to the first step )
``
./mktemplate.sh
``

Fit data to get signal and background yield ( the option in Draw_yield_treeeff doesn't do anything now, because I directly loop over the all the photon and jet eta bins )
``
root -b 
.L ext-mL_fit.C
Draw_yield_treeeff("EB",0)
``

Compare with 2015 results 
``
root -b -q yield_compare_plot.C
``

#!/usr/bin/env sh
# cleaning figure storage
touch plots.step4 ; /bin/rm -r plots.step4
cd step4.DrawYield/

unlink isovsbdt_template.root || rm isovsbdt_template.root
ln -s ../isovsbdt_template.root

# cleaning figure storage
touch plots ; /bin/rm -r plots
mkdir plots

python FitYields.allbinning.py > log.fitting
python LogInfoExtraction.py log.fitting

cp data.*.dat ..
cp -r plots/ ../plots.step4

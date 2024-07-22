#!/usr/bin/env sh
# cleaning figure storage
touch plots.step4 ; /bin/rm -r plots.step4
touch fit_jetSel ; /bin/rm -r fit_jetSel

cd step4.DrawYield/
sh run.sh ../isovsbdt_template.root

#cp data.*.dat ..
#cp sigmc.*.dat ..
cp -r plots/ ../plots.step4
cp -r fit_jetSel/ ../plots.step4

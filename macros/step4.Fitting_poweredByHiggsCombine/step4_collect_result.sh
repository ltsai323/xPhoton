outname=${1:-defaultOut}

cd out_fit_result
for a in `echo *BDTFit*`; do mv $a/fitres.pdf fitres_${a}.pdf; done
tar -cf ../${outname}.tar *

echo output file : ${outname}.tar

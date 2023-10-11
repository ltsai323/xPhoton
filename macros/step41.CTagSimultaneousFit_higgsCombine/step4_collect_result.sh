outname=${1:-defaultOut}

cd out_fit_result && mv */*.pdf .
tar -cf ../${outname}.tar *

echo output file : ${outname}.tar

inFOLDER=$1
outname=${2:-defaultOut}

if [ ! -d $inFOLDER ]; then echo "[Input dir not found - step5_collect_result] input folder is '$inFOLDER'"; exit 1; fi
cd $inFOLDER && mv */*.pdf .
tar -cf ../${outname}.tar *

echo output file : ${outname}.tar

mkdir -p dataset/plots
root -l TMVAReport.C'("'$1'")'

for a in `ls dataset/plots/*.eps`; do epstopdf --nocompress $a; done

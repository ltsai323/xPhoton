#!/usr/bin/env sh
for fakeidx in {0..9};
do
echo $fakeidx
touch plots_fakesample${fakeidx} ; /bin/rm -r plots_fakesample${fakeidx}
mkdir plots_fakesample${fakeidx}
root -b <<EOF
.L TruthComparison.C
TruthComparison(${fakeidx},0,0)
TruthComparison(${fakeidx},0,1)
TruthComparison(${fakeidx},1,0)
TruthComparison(${fakeidx},1,1)
EOF
done

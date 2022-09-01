#!/usr/bin/env sh
cd step3.DrawIsoBDT
# cleaning storage
touch logs ; /bin/rm -rf logs; mkdir logs
touch isovsbdt_template.root; /bin/rm isovsbdt_template.root
sh run.sh
mv isovsbdt_template.root ..

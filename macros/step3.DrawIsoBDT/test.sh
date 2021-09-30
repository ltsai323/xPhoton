#!/usr/bin/env sh


root -b <<EOF
.L Draw_IsovsBDT.C
Draw_IsovsBDT(0,2,11,1, 14, 20)
EOF
mv isovsbdt.root orig.root
root -b <<EOF
.L aaa.C
Draw_IsovsBDT(0,2,11,1, 14, 20)
EOF
mv isovsbdt.root  new.root

#!/usr/bin/env sh


root -b <<EOF
.L testing.C
Draw_IsovsBDT("a.json")
EOF
#mv isovsbdt.root orig.root
#root -b <<EOF
#.L aaa.C
#Draw_IsovsBDT(0,2,11,1, 14, 20)
#EOF
#mv isovsbdt.root  new.root

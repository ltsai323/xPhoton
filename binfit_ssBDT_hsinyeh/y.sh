python run.py 2
./mktemplate.sh
root -b  <<EOF
.L ext-mL_fit.C
Draw_yield_treeeff("EB",0)
EOF

#root -q yy.C

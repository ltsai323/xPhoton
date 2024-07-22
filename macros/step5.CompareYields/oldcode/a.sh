#!/usr/bin/env sh


cat > arg1.json <<EOF
{
    "luminosity": 2.26,
    "MarkerStyle": 8,
    "MarkerColor": 38,
    "Label": "2015",
    "DATfile": "15yield_noInclusivePho.dat",
    "histnaming": "2015Yield_%d_%d"
}
EOF
cat > arg2.json <<EOF
{
    "luminosity": 59.96,
    "MarkerStyle": 22,
    "MarkerColor": 2,
    "Label": "UL2018",
    "DATfile": "../data.yield.dat",
    "histnaming": "2018Yield_%d_%d"
}
EOF

root -b -q yield_directCompare.C'("arg1.json", "arg2.json")'

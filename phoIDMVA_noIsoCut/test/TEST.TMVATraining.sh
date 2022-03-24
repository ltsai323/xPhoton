#!/usr/bin/env sh

cat > hi.json <<EFO
{
    "isEndcap": false,
    "useIsoVars": false,
    "useShapeVars": true,
    "UsedAlgorithm": ["BDT"],
    "OutputTemplate": "testing_hightPtOnly_%s",
    "InputFile": "rw_outFrag.2.root"
}
EFO
test_TMVATraining hi.json

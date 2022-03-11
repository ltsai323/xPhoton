#!/usr/bin/env sh

cat > hi.json <<EFO
{
    "isEndcap": false,
    "useIsoVars": false,
    "useShapeVars": true,
    "UsedAlgorithm": ["BDT"],
    "OutputTemplate": "testing_%s",
    "InputFile": "rw_out.root"
}
EFO
test_TMVATraining hi.json

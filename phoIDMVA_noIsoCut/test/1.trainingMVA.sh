#!/usr/bin/env sh
/bin/rm -r bkgPho_noMCEvtWeight.png
/bin/rm -r sigPho_noMCEvtWeight.png
/bin/rm -r testing.EB testing.EE

root -b -q TMVAtutorial.C'(false)'
mv TMVA.root dataset/
mv dataset/ testing.EB

root -b -q TMVAtutorial.C'(true)'
mv TMVA.root dataset/
mv dataset/ testing.EE

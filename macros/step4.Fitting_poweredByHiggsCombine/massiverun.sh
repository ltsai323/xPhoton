#!/usr/bin/env sh

sh run_higgscombine.sh newBin_deepflavour_CUT_NOCUT             ../step2.test.makebinning/newBin_deepflavour_CUT_NOCUT.root
sh run_higgscombine.sh newBin_deepflavour_CUT_subJetVtxMass     ../step2.test.makebinning/newBin_deepflavour_CUT_subJetVtxMass.root
sh run_higgscombine.sh newBin_deepflavour_CUT_CvsL              ../step2.test.makebinning/newBin_deepflavour_CUT_CvsL.root

sh run_higgscombine.sh newBin_deepcsv_CUT_NOCUT                 ../step2.test.makebinning/newBin_deepcsv_CUT_NOCUT.root
sh run_higgscombine.sh newBin_deepcsv_CUT_subJetVtxMass         ../step2.test.makebinning/newBin_deepcsv_CUT_subJetVtxMass.root
sh run_higgscombine.sh newBin_deepcsv_CUT_CvsL                  ../step2.test.makebinning/newBin_deepcsv_CUT_CvsL.root

#!/usr/bin/env sh

sh run.sh
mv fakesample*_sig.root storeroot/fragments/
mv fakesample*_bkg.root storeroot/fragments/
mv fakesample*.root storeroot/
mv record.dat storeroot/

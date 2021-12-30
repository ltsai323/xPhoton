#!/usr/bin/env sh

outputdir='plots/fragments'
mkdir -p $outputdir ; /bin/rm -r $outputdir; mkdir -p $outputdir
root -b -q ComparisonPlot_FitOverTruth.C

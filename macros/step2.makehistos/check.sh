#!/usr/bin/env sh
source ./executable_with_args.sh

#sh executable_with_args.sh \
#    ptbin_definitions_testmode5.h \
#    5 \
#    DeepCSV \
#    DeepCSV_gjetMadgraph_cutIdx5_mergeBin_5 \
#    /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/makehistos/

link_pt_bin_definition ptbin_definitions_testmode9.h
cutIDX=5
tagALGO=DeepCSV
outputLABEL=DeepCSV_gjetMadgraph_cutIdx0_mergeBin_9
outputFOLDER=test_output/
exec_code $cutIDX $tagALGO $outputLABEL $outputFOLDER
#test_code $cutIDX $tagALGO $outputLABEL $outputFOLDER

#!/usr/bin/env sh
source ./executable_with_args.sh

#sh executable_with_args.sh \
#    ptbin_definitions_testmode5.h \
#    5 \
#    DeepCSV \
#    DeepCSV_gjetMadgraph_cutIdx5_mergeBin_5 \
#    /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/makehistos/

binNUM=9
link_pt_bin_definition ptbin_definitions_testmode${binNUM}.h
tagALGO=DeepCSV
outputFOLDER=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/makehistos/
compile_code

cutIDX=0
outputLABEL=DeepCSV_gjetMadgraph_cutIdx${cutIDX}_mergeBin_${binNUM}
exec_code $cutIDX $tagALGO $outputLABEL $outputFOLDER &
#test_code $cutIDX $tagALGO $outputLABEL $outputFOLDER

cutIDX=4
outputLABEL=DeepCSV_gjetMadgraph_cutIdx${cutIDX}_mergeBin_${binNUM}
exec_code $cutIDX $tagALGO $outputLABEL $outputFOLDER &

cutIDX=5
outputLABEL=DeepCSV_gjetMadgraph_cutIdx${cutIDX}_mergeBin_${binNUM}
exec_code $cutIDX $tagALGO $outputLABEL $outputFOLDER &

echo "[All Job submitted]"
wait
echo "[All Job submitted]"

bark.sh 'Job Finished' 'All step2.makehisto finished'

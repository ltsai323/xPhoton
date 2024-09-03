#!/usr/bin/env sh
source ./executable_with_args.sh



link_pt_bin_definition ptbin_definitions_testmode9.h
exec_code 0 DeepCSV     DeepCSV_gjetMadgraph_cutIdx0_bin9 &
exec_code 4 DeepCSV     DeepCSV_gjetMadgraph_cutIdx4_bin9 &
exec_code 5 DeepCSV     DeepCSV_gjetMadgraph_cutIdx5_bin9 &

exec_code 0 DeepFlavour DeepFlavour_gjetMadgraph_cutIdx0_bin9 &
exec_code 4 DeepFlavour DeepFlavour_gjetMadgraph_cutIdx4_bin9 &
exec_code 5 DeepFlavour DeepFlavour_gjetMadgraph_cutIdx5_bin9 &
bark.sh "JobSubmitted9" "All job related to ptbin_definitions_testmode9.h submitted]"
wait
bark.sh "JobFinished9" "All job related to ptbin_definitions_testmode9.h finished]"

link_pt_bin_definition ptbin_definitions_testmodeOrig.h
exec_code 0 DeepCSV     DeepCSV_gjetMadgraph_cutIdx0_binOrig &
exec_code 4 DeepCSV     DeepCSV_gjetMadgraph_cutIdx4_binOrig &
exec_code 5 DeepCSV     DeepCSV_gjetMadgraph_cutIdx5_binOrig &

exec_code 0 DeepFlavour DeepFlavour_gjetMadgraph_cutIdx0_binOrig &
exec_code 4 DeepFlavour DeepFlavour_gjetMadgraph_cutIdx4_binOrig &
exec_code 5 DeepFlavour DeepFlavour_gjetMadgraph_cutIdx5_binOrig &
bark.sh "JobSubmittedORIG" "All job related to ptbin_definitions_testmodeOrig.h submitted]"
wait
bark.sh "JobFinishedORIG" "All job related to ptbin_definitions_testmodeOrig.h finished]"

bark.sh "JobFinished" "massiverun.sh at step2 finished"

# real    73m22.047s
# user    343m22.508s
# sys     30m48.940s



#test_code 0 makehistoDeepFlavour.C DeepFlavour_cutIdx0_mergeBin_test3

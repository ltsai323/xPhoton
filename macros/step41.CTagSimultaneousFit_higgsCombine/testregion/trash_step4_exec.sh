#!/usr/bin/env sh

function the_exec() {
outDIR=$1/$2/CTagSimultaneousFit/
outputLabel=$2
#ls $outDIR/*.CTag_SimulFit.csv || return 1;
if [ ! -f "$outDIR/UL2016.CTag_SimulFit.csv" ]; then echo 'jjj'; return 0; fi; # ignore file not found
echo $outDIR;
python3 step4_drawCSVresult.py UL2016PreVFP $outDIR/*.CTag_SimulFit.csv $outputLabel && mv csvCollect_*.pdf $outDIR/;
}

unlink py_pt_ranges_definition.py ; ln -s /wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/macros/py_pt_ranges_definition_testmodeOrig.py py_pt_ranges_definition.py
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx0_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx1_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx2_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx0_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx1_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx2_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx0_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx1_mergeBin_Orig
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx2_mergeBin_Orig

unlink py_pt_ranges_definition.py ; ln -s /wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/macros/py_pt_ranges_definition_testmode0.py py_pt_ranges_definition.py
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx0_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx1_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx2_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx0_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx1_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx2_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx0_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx1_mergeBin_0
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx2_mergeBin_0

unlink py_pt_ranges_definition.py ; ln -s /wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/macros/py_pt_ranges_definition_testmode1.py py_pt_ranges_definition.py
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx0_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx1_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx2_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx0_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx1_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx2_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx0_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx1_mergeBin_1
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx2_mergeBin_1

unlink py_pt_ranges_definition.py ; ln -s /wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/macros/py_pt_ranges_definition_testmode2.py py_pt_ranges_definition.py
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx0_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx1_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx2_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx0_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx1_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx2_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx0_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx1_mergeBin_2
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx2_mergeBin_2

unlink py_pt_ranges_definition.py ; ln -s /wk_cms3/ltsai/wk_cms/ltsai/github/xPhoton/macros/py_pt_ranges_definition_testmode3.py py_pt_ranges_definition.py
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx0_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx1_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetMadgraph_cutIdx2_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx0_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx1_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepCSV_gjetPythia_cutIdx2_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx1_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetMadgraph_cutIdx2_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx0_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx1_mergeBin_3
the_exec /home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/ DeepFlavour_gjetPythia_cutIdx2_mergeBin_3

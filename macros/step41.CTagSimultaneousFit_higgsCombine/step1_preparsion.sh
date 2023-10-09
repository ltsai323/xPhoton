#!/usr/bin/env sh
dataERA=$1
inputFOLDER=$2
#inputFOLDER=/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/DeepFlavour_gjetMadgraph_cutIdx0_mergeBin_0

function cmd_exec() {
  echo "[EXEC] $*"
  "$@"
}
cmd_exec python3 preparsionFRAG1_py_GetDataDetail.py $dataERA $inputFOLDER
cmd_exec python3 preparsionFRAG2_CTAGGING_py_makedatacard.py getdatadetail.csv

#!/usr/bin/env sh
function run_pre {
tagALGO=$1
dataERA=$2
outTAGS=$3
cutIDX=$4
ptbinDEF=`realpath $5`
root -b <<EOF
.L preselectionEfficiency.C
preselection_efficiency({
    "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root",\
    "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root",\
    "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step1.appendeventinfo/MCeff/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root"\
});
EOF
}

function run_sel {
tagALGO=$1
dataERA=$2
outTAGS=$3
cutIDX=$4
ptbinDEF=`realpath $5`
root -b <<EOF
.L selectionEffCalc.C
selLoop($cutIDX, "$dataERA", "$tagALGO", { \
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root", \
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root", \
            "/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root" \
            } )
EOF
}

function the_exec() {
tagALGO=$1
dataERA=$2
outTAGS=$3
cutIDX=$4
ptbinDEF=`realpath $5`

#output_folder=${dataERA}_${tagALGO}_${outTAGS}_cutIdx${cutIDX}

mkdir efficiencies; cd efficiencies;

for a in ../*.h ../*.C ; do ln -s $a; done
unlink ptbin_definitions.h; ln -s $ptbinDEF ptbin_definitions.h

run_pre $1 $2 $3 $4 $5 &
run_sel $1 $2 $3 $4 $5 &
wait


for datfiles in *.dat; do python3 ../makeCSVfromDAT.py $datfiles; done
for a in *.C *.h; do unlink $a; done
cd ..
}
function put_result() { mv efficiencies $1/; }

ptbinFILE=$CMSSW_BASE/src/xPhoton/MyCommonTools/cpp/ptbin_definitions/ptbin_definitions_testmode5.h
the_exec  DeepFlavour UL2016PreVFP gjetPythia_mergeBin5 0 $ptbinFILE
put_result /wk_cms3/ltsai/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/DeepFlavour_gjetPythia_cutIdx0_mergeBin_5/

the_exec  DeepCSV UL2016PreVFP gjetPythia_mergeBin5 0 $ptbinFILE
put_result /wk_cms3/ltsai/wk_cms/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/makehistos/DeepCSV_gjetPythia_cutIdx0_mergeBin_5/

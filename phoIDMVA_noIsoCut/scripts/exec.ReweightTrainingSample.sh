#!/usr/bin/env sh
exec_ReweightTrainingSample \
        /home/ltsai/ReceivedFile/GJet/latestsample/UL2018/testing/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root \
        /home/ltsai/ReceivedFile/GJet/latestsample/UL2018/testing/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root \
        /home/ltsai/ReceivedFile/GJet/latestsample/UL2018/testing/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root
hadd rw_out.root rw_outFrag*.root

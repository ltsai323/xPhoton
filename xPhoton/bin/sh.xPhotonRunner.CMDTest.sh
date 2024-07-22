
in_file_ggNtuple=test_gg/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8_trees.root
out_idx=0


dataEra=UL2016PreVFP
#exec_xPhotonRunnerGeneral $in_file_ggNtuple $out_idx $dataEra
#exec_xPhotonRunner2016ReReco $in_file_ggNtuple $out_idx
#exec_xPhotonRunner2017ReReco $in_file_ggNtuple $out_idx
#exec_xPhotonRunner2018ReReco $in_file_ggNtuple $out_idx
#exec_xPhotonRunnerUL2016PreVFP $in_file_ggNtuple $out_idx
exec_xPhotonRunnerUL2016PostVFP $in_file_ggNtuple $out_idx
#exec_xPhotonRunnerUL2017 $in_file_ggNtuple $out_idx
#exec_xPhotonRunnerUL2018 $in_file_ggNtuple $out_idx

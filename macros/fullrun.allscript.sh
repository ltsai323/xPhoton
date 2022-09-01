##!/usr/bin/env sh


cat > fullrun.inputfiles.conf <<EOF
datafile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.data.root
fakefile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.QCD.root
signfile=/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/2016.sigMC.root
EOF
#cat > fullrun.inputfiles.conf <<EOF
#datafile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_data.root
#fakefile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_qcdpythia.root
#signfile=/home/ltsai/ReceivedFile/GJet/latestsample/UL2018/correctMVA/updated/updated_sigpythia.root
#EOF

/bin/rm *.tar


sh fullrun.step2.sh $PWD/fullrun.inputfiles.conf
#sh testrun.step2.oldDATA.sh $PWD/fullrun.inputfiles.conf
sh fullrun.step3.sh

sh fullrun.step4.sh


## old for 2016
#cat > arg_orig.json <<EOF
#{
#    "luminosity": 35.9,
#    "MarkerStyle": 22,
#    "MarkerColor": 46,
#    "Title": "2016 ReReco in old processed",
#    "Label": "Old16",
#    "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/16yield_newformat.dat"
#}
#EOF

# old for 2015
cat > arg_orig.json <<EOF
{
    "lumifile": "/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step5.CompareYields/effLumi_2015.json",
    "MarkerStyle": 8,
    "MarkerColor": 38,
    "Title": "2015 ReReco from RS result",
    "Label": "2015",
    "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/15yield_noInclusivePho_newformat.dat"
}
EOF

# new for 2016
cat > arg_comp.json <<EOF
{
    "lumifile": "/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/macros/step5.CompareYields/effLumi_2016.json",
    "MarkerStyle": 22,
    "MarkerColor": 39,
    "Title": "2016 ReReco in old processed AGAIN",
    "Label": "New",
    "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/data.yield.dat"
}
EOF

# # new for 2018
# cat > arg_comp.json <<EOF
# {
#     "luminosity": 59.96,
#     "MarkerStyle": 22,
#     "MarkerColor": 39,
#     "Label": "UL18",
#     "Title": "UL2018",
#     "DATfile": "/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/data.yield.dat"
# }
# EOF
arg_trg=arg_orig.json
arg_cmp=arg_comp.json

root -b <<EOF
.L /wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/macros/step5.CompareYields/compareYield.C
CompareYields("$arg_trg","$arg_cmp")
EOF

#!/usr/bin/env python2
command='"export X509_USER_PROXY=/home/ltsai/.x509up_u54608; cd /home/ltsai/Work/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/test ; mkdir -p {fold} && cd {fold} ; python ../xphoton_path.py {file} ; mv *.root ../storeroot"'
import os
'''
flist=[
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/data_Run2016B_94XReReco_ver2v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/data_Run2016C_94XReReco_v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/data_Run2016D_94XReReco_v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/data_Run2016E_94XReReco_v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/data_Run2016F_94XReReco_v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/data_Run2016G_94XReReco_v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/data_Run2016H_94XReReco_v1.txt',
]
'''
flist=[
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2_16_05_2021.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2_16_05_2021.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2_16_05_2021.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2_16_05_2021.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2_16_05_2021.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2_16_05_2021.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2_16_05_2021.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2_16_05_2021.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/local_madgraphMLM/CRABdata_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2_16_05_2021.txt',
]

for f in flist:
    folder=f.split('/')[-1].split('.')[0]
    print folder
    os.system('/home/ltsai/script/qjob/submitJOB.py --command={} --name={}'.format(
        command.format(fold=folder,file=f),
        folder))

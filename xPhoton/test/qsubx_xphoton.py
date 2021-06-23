#!/usr/bin/env python2
mesg='Process local files'
command='"export X509_USER_PROXY=/home/ltsai/.x509up_u54608; cd /home/ltsai/Work/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/test ; mkdir -p {fold} && cd {fold} ; python ../xphoton_path.py {file} false"'
'''
mesg='Download 1 root file from T2 first and process it'
command='"export X509_USER_PROXY=/home/ltsai/.x509up_u54608; cd /home/ltsai/Work/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/test ; mkdir -p {fold} && cd {fold} ; python ../xphoton_path.py {file} false"'
'''
import os
dataflist=[
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016B_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016C_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016D_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016E_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016F_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016G_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016H_94X.txt',
    ]
madgraphflist=[
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/madgraphMLM/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
]
qcdflist=[
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_15to30_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_15to6500_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_30to50_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_3200toInf_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2_backup.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_50to80_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2_backup.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3-v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCD/crab_bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3_ext2-v2.txt',
]

if __name__ == '__main__':
    print mesg
    flist=qcdflist
    for f in flist:
        folder=f.split('/')[-1].split('.')[0]
        print folder
        os.system('/home/ltsai/script/qjob/submitJOB.py --command={} --name={}'.format(
            command.format(fold=folder,file=f),
            folder))

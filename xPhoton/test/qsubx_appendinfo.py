#!/usr/bin/env python2
mesg='Append additional information into MC'
command='"cd /home/ltsai/Work/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/test ; ../bin/exe.AppendEventInfo 1.0 {file} storeroot/{newfile}"'
'''
mesg='Download 1 root file from T2 first and process it'
command='"export X509_USER_PROXY=/home/ltsai/.x509up_u54608; cd /home/ltsai/Work/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/test ; mkdir -p {fold} && cd {fold} ; python ../xphoton_remote.py {file} false"'
'''
import os
dataflist=[
]
madgraphflist=[
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/madgraphMLM/crab_sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
]
qcdflist=[
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3v1.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v1.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_15to30_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_15to6500_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_30to50_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_3200toInf_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2_backup.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_50to80_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2_backup.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3-v1.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD/crab_bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3_ext2-v2.root',
]
qcd_madgraphlist=[
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v1.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.root',
'/home/ltsai/ReceivedFile/GJet/bkg_QCD_madgraph/crab_bkgMC_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
]

if __name__ == '__main__':
    print mesg
    flist=madgraphflist
    for f in flist:
        nameonly=f.split('/')[-1]
        os.system('/home/ltsai/script/qjob/submitJOB.py --command={} --name={}'.format(
            command.format(file=f,newfile=nameonly),
            nameonly))

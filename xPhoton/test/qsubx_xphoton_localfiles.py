#!/usr/bin/env python2
TESTmode=False
shmesg='Process local file by sh'
shcommand='"cd /home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/test ;sh xphoton_simple_idxReordered_abspath.sh  {file}"'
import os
# unchecked
local_dataflist=[
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016B_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016C_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016D_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016E_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016F_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016G_94X.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/data16_94X/Run2016H_94X.txt',
    ]
# unchecked
local_pythiaflist=[
'/home/ltsai/ReceivedFile/GJet/listedPaths/GJets/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/GJets/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/GJets/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.txt',
        ]

local_madgraphflist=[
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

# unchecked
localQCD_pythiaflist=[

"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3v1.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v1.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_15to30_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_15to6500_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8v3_ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_30to50_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_3200toInf_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2_backup.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_50to80_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2_backup.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3-v1.txt",
"/home/ltsai/ReceivedFile/GJet/listedPaths/QCDpythia/crab_bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3_ext2-v2.txt",
]

localQCD_madgraphlist=[
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT1000to1500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT100to200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v1.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT1500to2000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT2000toInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT200to300_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT300to500_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT500to700_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT50to100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3-v2.txt',
'/home/ltsai/ReceivedFile/GJet/listedPaths/QCDmadgraph/crab_crab_bkgMC_QCD_HT700to1000_TuneCUETP8M1_13TeV-madgraphMLM-pythia8_v3_ext1-v2.txt',
]

import os
def CheckExistancce(pathlist):
    if len( NotExistFiles(pathlist) ):
        raise IOError(
                'files not found : \n%s' % '\n   -> '.join(
                    NotExistFiles(pathlist)
                    ) )

    terminatecode=False
    for pathfile in pathlist:
        fin=open(pathfile,'r')

        notexistedFile=NotExistFiles( [l.strip() for l in fin.readlines()] )

        if len(notexistedFile)>0 :
            terminatecode=True
            print 'files not found:\n%s' % '\n   -> '.join(notexistedFile)
        fin.close()
    if terminatecode: raise IOError('terminated')



def NotExistFiles(files):
    return [ f for f in files if not os.path.isfile(f) ]


if __name__ == '__main__':
    command=shcommand
    mesg=shmesg

    print mesg
    flist=local_dataflist
    #flist=local_madgraphflist
    #flist=localQCD_madgraphlist
    #flist=local_pythiaflist
    #flist=localQCD_pythiaflist
    if TESTmode:
        print 'checking paths...'
        CheckExistancce(local_madgraphflist)
        CheckExistancce(local_pythiaflist)
        CheckExistancce(localQCD_madgraphlist)
        CheckExistancce(localQCD_pythiaflist)
        CheckExistancce(local_dataflist)

        exit(1)
    print 'Related path checking...'
    CheckExistancce(flist)
    for f in flist:
        folder=f.split('/')[-1].split('.')[0]
        print folder
        os.system('/home/ltsai/script/qjob/submitJOB.py --command=%s --name=%s --lowPriority' %(
            (command.format(file=f), folder) ) )
        #print      '/home/ltsai/script/qjob/submitJOB.py --command=%s --name=%s' %(
        #    (command.format(file=f), folder) )

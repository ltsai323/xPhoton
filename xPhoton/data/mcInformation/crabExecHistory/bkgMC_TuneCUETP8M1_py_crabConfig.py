#!/usr/bin/env python2
myArgs=[
        { 'reqName':'bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3v1'         , 'dataset':'/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM'},
        { 'reqName':'bkgMC_Pt_1000to1400_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2'   , 'dataset':'/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v1'          , 'dataset':'/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2'     , 'dataset':'/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_120to170_13TeV_TuneCUETP8M1_pythia8_v3-v2'          , 'dataset':'/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3-v2'        , 'dataset':'/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_1400to1800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2'   , 'dataset':'/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_15to30_13TeV_TuneCUETP8M1_pythia8_v3-v2'            , 'dataset':'/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_15to6500_13TeV_TuneCUETP8M1_pythia8_v3-v2'          , 'dataset':'/QCD_Pt_15to6500_FwdEnriched_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3-v2'          , 'dataset':'/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_170to300_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2'     , 'dataset':'/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-v2'        , 'dataset':'/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_1800to2400_13TeV_TuneCUETP8M1_pythia8_v3-ext1-v2'   , 'dataset':'/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8_v3-v2'        , 'dataset':'/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_2400to3200_13TeV_TuneCUETP8M1_pythia8v3_ext1-v2'    , 'dataset':'/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3-v2'          , 'dataset':'/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_300to470_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2'     , 'dataset':'/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_30to50_13TeV_TuneCUETP8M1_pythia8_v3-v2'            , 'dataset':'/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_3200toInf_13TeV_TuneCUETP8M1_pythia8_v3-v2'         , 'dataset':'/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2'          , 'dataset':'/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_470to600_13TeV_TuneCUETP8M1_pythia8_v3-v2'          , 'dataset':'/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_50to80_13TeV_TuneCUETP8M1_pythia8_v3-v2'            , 'dataset':'/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2'          , 'dataset':'/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2'     , 'dataset':'/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_600to800_13TeV_TuneCUETP8M1_pythia8_v3-v2'          , 'dataset':'/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_backup_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3-v2'         , 'dataset':'/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_800to1000_13TeV_TuneCUETP8M1_pythia8_v3_ext1-v2'    , 'dataset':'/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3-v1'           , 'dataset':'/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v1/MINIAODSIM'},
#        { 'reqName':'bkgMC_Pt_80to120_13TeV_TuneCUETP8M1_pythia8_v3_ext2-v2'      , 'dataset':'/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM'},
]
if __name__ == '__main__':

# Usage : python crabConfig.py (to create jobs)
#         ./multicrab -c status -d <work area> (to check job status)

    for myArg in myArgs:
        from CRABAPI.RawCommand import crabCommand
        from httplib import HTTPException
        from CRABClient.UserUtilities import config
        config = config()

        from multiprocessing import Process

        # Common configuration

        config.General.workArea     = 'SentJobs_CRAB'
        config.General.transferLogs = False
        config.JobType.pluginName   = 'Analysis' # PrivateMC
        config.JobType.psetName     = 'myggNtuplier_noanalyzer.py'
        #config.JobType.inputFiles   = ['Summer16_23Sep2016V4_MC_L2Relative_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC_L3Absolute_AK8PFchs.txt', 'Summer16_23Sep2016V4_MC.db']
        config.JobType.sendExternalFolder = True
        config.Data.inputDBS        = 'global'
        #config.Data.splitting       = 'LumiBased' # EventBased, FileBased, LumiBased (1 lumi ~= 300 events)
        config.Data.splitting       = 'FileBased' # EventBased, FileBased, LumiBased (1 lumi ~= 300 events)
        config.Data.totalUnits      = -1
        config.Data.publication     = False
        config.Site.storageSite     = 'T2_TW_NCHC'

        def submit(config):
            try:
                crabCommand('submit', config = config)
            except HTTPException, hte:
                print hte.headers

        # dataset dependent configuration

        config.General.requestName = myArg['reqName']
        #config.Data.unitsPerJob    = 40
        config.Data.unitsPerJob    = 1
        config.Data.inputDataset   = myArg['dataset']
        config.Data.outLFNDirBase  = '/store/user/ltsai/ggAnalysis/2016miniAODv3/jetSubVtxInfo'
        p = Process(target=submit, args=(config,))
        p.start()
        p.join()

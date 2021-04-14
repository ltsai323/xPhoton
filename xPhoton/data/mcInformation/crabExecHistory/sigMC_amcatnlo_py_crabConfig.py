#!/usr/bin/env python2
myArgs=[
            { 'reqName':'sigMC_Pt100To250_13TeV-amcatnlo-pythia8_v3-v3-v2_sub01'  , 'dataset':'/G1Jet_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM' },
            { 'reqName':'sigMC_Pt100To250_13TeV-amcatnlo-pythia8_v3-ext1-v2_sub01', 'dataset':'/G1Jet_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM' },
            { 'reqName':'sigMC_Pt100To250_13TeV-amcatnlo-pythia8_v3-ext2-v2_sub01', 'dataset':'/G1Jet_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v2/MINIAODSIM' },

            { 'reqName':'sigMC_Pt250To400_13TeV-amcatnlo-pythia8_v3-v2_sub01'     , 'dataset':'/G1Jet_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM' },
            { 'reqName':'sigMC_Pt250To400_13TeV-amcatnlo-pythia8_v3-ext1-v2_sub01', 'dataset':'/G1Jet_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM' },
            { 'reqName':'sigMC_Pt250To400_13TeV-amcatnlo-pythia8_v3-ext2-v1_sub01', 'dataset':'/G1Jet_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext2-v1/MINIAODSIM' },

            { 'reqName':'sigMC_Pt400To650_13TeV-amcatnlo-pythia8_v3-v2_sub01'     , 'dataset':'/G1Jet_Pt-400To650_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM' },
            { 'reqName':'sigMC_Pt400To650_13TeV-amcatnlo-pythia8_v3-ext1-v2_sub01', 'dataset':'/G1Jet_Pt-400To650_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM' },

            { 'reqName':'sigMC_Pt50To100_13TeV-amcatnlo-pythia8_v3-v2_sub01'      , 'dataset':'/G1Jet_Pt-50To100_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM' },
            { 'reqName':'sigMC_Pt50To100_13TeV-amcatnlo-pythia8_v3-ext1-v1_sub01' , 'dataset':'/G1Jet_Pt-50To100_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v1/MINIAODSIM' },

            { 'reqName':'sigMC_Pt650ToInf_13TeV-amcatnlo-pythia8_v3-v2_sub01'     , 'dataset':'/G1Jet_Pt-650ToInf_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3-v2/MINIAODSIM' },
            { 'reqName':'sigMC_Pt650ToInf_13TeV-amcatnlo-pythia8_v3-ext1-v2_sub01', 'dataset':'/G1Jet_Pt-650ToInf_TuneCUETP8M1_13TeV-amcatnlo-pythia8/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic_v3_ext1-v2/MINIAODSIM' },
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
        config.Data.outLFNDirBase  = '/store/user/ltsai/ggAnalysis/RunIISummer16MiniAODv3-PUMoriond17_94X_mcRun2_asymptotic__TuneCUETP8M1_13TeV_Pythia8/'
        p = Process(target=submit, args=(config,))
        p.start()
        p.join()

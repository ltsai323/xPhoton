global_input_info = [
    {"tag":"HT50to100",    "mcweight": 276887,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT100to200",   "mcweight": 20046.5,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT200to300",   "mcweight": 1627.78,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT300to500",   "mcweight": 355.923,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT500to700",   "mcweight": 31.702,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT700to1000",  "mcweight": 8.12001,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT1000to1500", "mcweight": 4.33087,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT1500to2000", "mcweight": 0.608651,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT2000toInf",  "mcweight": 0.29305,
'ifile':'/wk_cms/ltsai/CMSSW/CMSSW_9_4_14/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver5.UL18/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
]

class InputInfo:
    def __init__(self, input_dict):
        self.tag=input_dict['tag']
        self.ifile=input_dict['ifile']
        self.mcweight=input_dict['mcweight']
    def __repr__(self):
        return 'tag: %20s. mcweight: %10.4f. ifile: %s' %(self.tag,self.mcweight,self.ifile)
if __name__ == "__main__":
    import os
    for info_list in global_input_info:
        info = InputInfo(info_list)
        print      'xQCD2nd_ReweightChecking_Madgraph %s %s %f' % (info.tag, info.ifile, info.mcweight)
        os.system( 'xQCD2nd_ReweightChecking_Madgraph %s %s %f' % (info.tag, info.ifile, info.mcweight) )

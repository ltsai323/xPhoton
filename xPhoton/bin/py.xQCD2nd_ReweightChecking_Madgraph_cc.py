global_input_info = [
    {"tag":"HT50to100",    "mcweight": 2.1248e+6 ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT50to100.root",
        },
    {"tag":"HT100to200",   "mcweight": 12126.6   ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT100to200.root",
        },
    {"tag":"HT200to300",   "mcweight": 1053.94   ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT200to300.root",
        },
    {"tag":"HT300to500",   "mcweight": 228.55    ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT300to500.root",
        },
    {"tag":"HT500to700",   "mcweight": 18.5005   ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT500to700.root",
        },
    {"tag":"HT700to1000",  "mcweight": 6.49481   ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT700to1000.root",
        },
    {"tag":"HT1000to1500", "mcweight": 2.86964   ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT1000to1500.root",
        },
    {"tag":"HT1500to2000", "mcweight": 0.365085  ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT1500to2000.root",
        },
    {"tag":"HT2000toInf",  "mcweight":0.155885   ,
  "ifile":"/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/xPhoton/scripts/RUNbkgSumbit/bkgRunning/xQCDver4.hasQCDpthat/QCDHT2000toInf.root",
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

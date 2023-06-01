#!/usr/bin/env python3
global_input_info = [
    {"tag":"HT50to100",    "mcweight": 2.1248e+6 ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT100to200",   "mcweight": 12126.6   ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT200to300",   "mcweight": 1053.94   ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT300to500",   "mcweight": 228.55    ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT500to700",   "mcweight": 18.5005   ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT700to1000",  "mcweight": 6.49481   ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT1000to1500", "mcweight": 2.86964   ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT1500to2000", "mcweight": 0.365085  ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT2000toInf",  "mcweight":0.155885   ,
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/xQCD.1st.AppendEventInfo/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
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
        print    ( 'xQCD2nd_ReweightChecking_Madgraph %s %s %f' % (info.tag, info.ifile, info.mcweight) )
        os.system( 'xQCD2nd_ReweightChecking_Madgraph %s %s %f' % (info.tag, info.ifile, info.mcweight) )

#!/usr/bin/env python3
global_input_info = [
    {"tag":"HT50to100",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT50to100_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT100to200",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT100to200_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT200to300",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT200to300_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT300to500",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT300to500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT500to700",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT500to700_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT700to1000",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT700to1000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT1000to1500",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT1000to1500_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT1500to2000",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT1500to2000_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
    {"tag":"HT2000toInf",
    'ifile': '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.1st.AppendEventInfo/QCD_HT2000toInf_TuneCP5_PSWeights_13TeV-madgraphMLM-pythia8.root',
        },
]

class InputInfo:
    def __init__(self, input_dict):
        self.tag=input_dict['tag']
        self.ifile=input_dict['ifile']
    def __repr__(self):
        return 'tag: %20s. ifile: %s' %(self.tag,self.ifile)
if __name__ == "__main__":
    import os
    for info_list in global_input_info:
        info = InputInfo(info_list)

        tag = info.tag
        infile = info.ifile
        print    (f'xQCD2nd_ReweightChecking_Madgraph {tag} {infile}')
        os.system(f'xQCD2nd_ReweightChecking_Madgraph {tag} {infile}')

    outputDir = '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/xQCD.2nd/'
    os.system(f'mv xQCD2nd_ReweightChecking_Madgraph_cc_*.root {outputDir}/')
    print(f'\n[LOG] Your output has been put at {outputDir}')

#!/usr/bin/env python2
files=[
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_15to6500_FwdEnriched_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8.root",
'/home/ltsai/ReceivedFile/GJet/old/old.2016ReReco.QCDPythia.root'
]
if __name__ == "__main__":
    import json
    dataera="2016ReReco"
    outputtag='2016ReReco_QCD'
    with open('running.%s.json'%outputtag, 'w') as fout:
        outputcontent={
                'dataera': dataera,
                'InputFiles': files,
                'OutputFileName': 'binned_%s.root'%outputtag,
                }
        json.dump(outputcontent,fout)
    import os
    os.system( 'exec_xPhotonBinning running.%s.json'%outputtag )

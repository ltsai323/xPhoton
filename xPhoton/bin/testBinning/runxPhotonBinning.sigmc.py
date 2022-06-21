#!/usr/bin/env python2
files=[
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8.root",
#"/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8.root",
'/home/ltsai/ReceivedFile/GJet/old/old.2016ReReco.sigPythia.root'
]
if __name__ == "__main__":
    import json
    dataera="2016ReReco"
    outputtag='2016ReReco_sig'
    with open('running.%s.json'%outputtag, 'w') as fout:
        outputcontent={
                'dataera': dataera,
                'InputFiles': files,
                'OutputFileName': 'binned_%s.root'%outputtag,
                }
        json.dump(outputcontent,fout)
    import os
    os.system( 'exec_xPhotonBinning running.%s.json'%outputtag )

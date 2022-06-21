#!/usr/bin/env python2
files=[
'/home/ltsai/ReceivedFile/GJet/old/old.2016ReReco.data.root'
]
if __name__ == "__main__":
    import json
    dataera="2016ReReco"
    outputtag='2016ReReco_data'
    with open('running.%s.json'%outputtag, 'w') as fout:
        outputcontent={
                'dataera': dataera,
                'InputFiles': files,
                'OutputFileName': 'binned_%s.root'%outputtag,
                }
        json.dump(outputcontent,fout)
    import os
    os.system( 'exec_xPhotonBinning running.%s.json'%outputtag )

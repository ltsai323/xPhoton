#!/usr/bin/env python2
files=[
'/wk_cms/ltsai/CMSSW_11_0_0_pre3/src/xPhoton/macros/2016.QCD.root',
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
    print( 'job "exec_xPhotonBinning running.%s.json" finished'%outputtag )

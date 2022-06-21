#!/usr/bin/env python2
files=[
"../../scripts/RUNbkgSumbit/bkgRunning/Run2016B_94X.root",
"../../scripts/RUNbkgSumbit/bkgRunning/Run2016C_94X.root",
"../../scripts/RUNbkgSumbit/bkgRunning/Run2016D_94X.root",
"../../scripts/RUNbkgSumbit/bkgRunning/Run2016E_94X.root",
"../../scripts/RUNbkgSumbit/bkgRunning/Run2016F_94X.root",
"../../scripts/RUNbkgSumbit/bkgRunning/Run2016G_94X.root",
"../../scripts/RUNbkgSumbit/bkgRunning/Run2016H_94X.root",
]
if __name__ == "__main__":
    import json
    dataera="2016ReReco"
    outputtag='DATAfull'
    with open('running.json', 'w') as fout:
        outputcontent={
                'dataera': dataera,
                'InputFiles': files,
                'OutputFileName': 'binned_%s.root'%outputtag,
                }
        json.dump(outputcontent,fout)
    import os
    os.system( 'exec_xPhotonBinning running.json' )

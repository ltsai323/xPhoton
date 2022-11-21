#!/usr/bin/env python2

import json
class HLTInfo(object):
    def __init__(self,efflumi,hltname):
        self._HLT=hltname
        self._effLumi=efflumi
    def __str__(self):
        return 'result : HLT: %s, effective luminosity %.3f'%(self._HLT,self._effLumi)
    def Print(self, template):
        return template%(self._HLT,self._effLumi)

def HLTbin():
    content=[None] * 9
    content[0] = HLTInfo(0.0016, "hltEG22HEFilter") # di photon trigger.
    content[1] = HLTInfo(0.0066, "hltEG30HEFilter") # HLTPhoton30SequenceLooseHOverE
    content[2] = HLTInfo(0.0132, "hltEG36HEFilter")
    content[3] = HLTInfo(0.0264, "hltEG50HEFilter")
    content[4] = HLTInfo(0.13  , "hltEG75HEFilter")
    content[5] = HLTInfo(0.26  , "hltEG90HEFilter")
    content[6] = HLTInfo(0.54  , "hltEG120HEFilter")
    content[7] = HLTInfo(36.47 , "hltEG175HEFilter")
    content[8] = HLTInfo(36.47 , "hltEG300erEtFilter")
    return content
if __name__ == "__main__":
    hltbins=HLTbin()
    ptbins=[None]*23
    ptbins[ 0]=hltbins[0]
    ptbins[ 1]=hltbins[1]
    ptbins[ 2]=hltbins[2]
    ptbins[ 3]=hltbins[3]
    ptbins[ 4]=hltbins[3]
    ptbins[ 5]=hltbins[4]
    ptbins[ 6]=hltbins[5]
    ptbins[ 7]=hltbins[5]
    ptbins[ 8]=hltbins[6]
    ptbins[ 9]=hltbins[6]
    ptbins[10]=hltbins[6]
    ptbins[11]=hltbins[7]
    ptbins[12]=hltbins[7]
    ptbins[13]=hltbins[7]
    ptbins[14]=hltbins[7]
    ptbins[15]=hltbins[7]
    ptbins[16]=hltbins[7]
    ptbins[17]=hltbins[7]
    ptbins[18]=hltbins[7]
    ptbins[19]=hltbins[7]
    ptbins[20]=hltbins[7]
    ptbins[21]=hltbins[7]
    ptbins[22]=hltbins[7]

    lumi=[]
    name=[]
    bins=[]
    for ptbin, hltInfo in enumerate(ptbins):
        bins.append(ptbin)
        name.append(hltInfo._HLT)
        lumi.append(hltInfo._effLumi)
    outputcontent={
            'bin':bins,
            'HLTNames':name,
            'effectiveLuminosity':lumi,
            "MarkerStyle": 22,
            "MarkerColor": 38,
            "Title": "2016 ReReco",
            "Label": "2016",
            "DATfile": "nothing.dat"
            }
    json_obj = json.dumps(outputcontent, indent=2)
    with open('effLumi_2016.json','w') as outputfile:
        outputfile.write(json_obj)

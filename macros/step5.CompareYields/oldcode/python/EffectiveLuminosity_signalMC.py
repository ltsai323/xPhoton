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
    content=[None]
    content[0] = HLTInfo(1, "nothing") # for MC, no pre scale weight needed
    return content
if __name__ == "__main__":
    hltbins=HLTbin()
    ptbins=[None]*23
    ptbins[ 0]=hltbins[0]
    ptbins[ 1]=hltbins[0]
    ptbins[ 2]=hltbins[0]
    ptbins[ 3]=hltbins[0]
    ptbins[ 4]=hltbins[0]
    ptbins[ 5]=hltbins[0]
    ptbins[ 6]=hltbins[0]
    ptbins[ 7]=hltbins[0]
    ptbins[ 8]=hltbins[0]
    ptbins[ 9]=hltbins[0]
    ptbins[10]=hltbins[0]
    ptbins[11]=hltbins[0]
    ptbins[12]=hltbins[0]
    ptbins[13]=hltbins[0]
    ptbins[14]=hltbins[0]
    ptbins[15]=hltbins[0]
    ptbins[16]=hltbins[0]
    ptbins[17]=hltbins[0]
    ptbins[18]=hltbins[0]
    ptbins[19]=hltbins[0]
    ptbins[20]=hltbins[0]
    ptbins[21]=hltbins[0]
    ptbins[22]=hltbins[0]

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
            "MarkerStyle": 20,
            "MarkerColor": 12,
            "Title": "GJet MC",
            "Label": "MC",
            "DATfile": "nothing.dat"
            }
    json_obj = json.dumps(outputcontent, indent=2)
    with open('../data/effLumi_signalMC.json','w') as outputfile:
        outputfile.write(json_obj)

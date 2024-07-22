#!/usr/bin/env python
# quickly check MC and data distribution of parameter.



if __name__ == '__main__':
    import ROOT
    inputinfo=[
            ('data',  '/home/ltsai/ReceivedFile/GJet/data/data_Run2016H_94XReReco_v1.root'),
            ('mcsig', '/home/ltsai/ReceivedFile/GJet/GJet_pythia/Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
            ('mcbkg', '/home/ltsai/ReceivedFile/GJet/GJet_pythia/Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
        ]

    ibname='recoPt'
    itname='t'
    histinfo=[]
    obsrange=[]
    for label, ifname in inputinfo:
        itfile=ROOT.TFile.Open(ifname)
        ittree=itfile.Get(itname)
        if len(obsrange)==0: # use data range
            obsrange=[ittree.GetMinimum(itname) *0.8, ittree.GetMaximum(itname)]

        hist=ROOT.TH1F('_'.join(['h',ibname,label]), '', 100, obsrange[0], obsrange[1])
        ittree.Draw('>>'.join([ibname,hist.GetName()]),)
        highestpoint=hist.GetBinContent( hist.GetMaximumBin() )
        histinfo.append( {'label':label, 'hist':hist, 'tfile':itfile, 'ttree':ittree, 'maxBinContent':highestpoint} )


    scalefactor=histinfo[0]['maxBinContent']
    for hinfo in histinfo:
        hist=hinfo['hist']
        multiplier=scalefactor / hinfo['maxBinContent']
        hist.Scale(multiplier)

    canv=ROOT.TCanvas('c','',1000,1000)
    histinfo[1]['hist'].Draw('axis')
    for hinfo in histinfo:
        hinfo['hist'].Draw('same')

    canv.SaveAs('kk.png')


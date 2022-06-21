#!/usr/bin/env python2

makeHistoList=[
        #{ 'idx':4 ,'outName':'mc_DY.root' },
        #{ 'idx':1 ,'outName':'mc_hggfilter.root' },
        #{ 'idx':8 ,'outName':'mc_gjet6000.root' },
        #{ 'idx':16,'outName':'mc_gjet_MC.root' },
        #{ 'idx':13,'outName':'mc_TT.root' },
        #{ 'idx':9 ,'outName':'mc_Wgamma.root' },
        #{ 'idx':11,'outName':'mc_WJet.root' },
        #{ 'idx':6 ,'outName':'mc_WJet_amcnlo.root' },
        #{ 'idx':5 ,'outName':'mc_QCD.root' },
        #{ 'idx':15,'outName':'mc_QCD_noHLT.root' },
        #{ 'idx':14,'outName':'mc_QCD_Wmn.root' },

        { 'idx':2 ,'outName':'data.root' },
        { 'idx':3 ,'outName':'data_DY.root' },
        { 'idx':7 ,'outName':'data_WJet.root' },
    ]


if __name__ == '__main__':
    import ROOT
    import os
    ROOT.gROOT.LoadMacro('MakeHisto.C+')
    for mHisto in makeHistoList:
        ROOT.MakeHisto(mHisto['idx']).Loop()
        os.system('mv output.root store_roots/makeHistos/'+mHisto['outName'])

    # ROOT.gROOT.LoadMacro('QCD_HLT_pt.C')
    # os.system( 'my aaa.root store_roots/makeHistor/' )

    # ROOT.gROOT.LoadMacro('Draw_from.C("EB","BDT",5,1)')
    # os.systemmmm( 'mv template-1.root  store_roots/makeHistos/WJet_template.root')
    # ROOT.gROOT.LoadMacro('Draw_from.C("EE","BDT",5,1)')
    # os.systemmmm( 'mv template-1.root  store_roots/makeHistos/WJet_template_EE.root')

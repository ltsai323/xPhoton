#!/usr/bin/env python3

import ROOT
debug_mode = True


def draw(inTREE:ROOT.TTree,
        varNAME:str, outTAG:str, xAXIS:str,
        evtCUT:str, evtWEIGHT:str,
        binning:tuple=() ):
    histNAME = '_'.join((outTAG,xAXIS))
    v=f'{varNAME} >> {histNAME}'
    #print(f'drawing hist {histNAME}')
    if len(binning)>0:
        v+=f'({binning[0]:d},{binning[1]:.2f},{binning[2]:.2f})'
    print(f'ttree.Draw("{v}", "({evtCUT})*{evtWEIGHT}"')
    inTREE.Draw(v, f'({evtCUT})*{evtWEIGHT}')

    h = ROOT.gROOT.FindObject(histNAME)
    h.GetXaxis().SetTitle(xAXIS)
    h.SetTitle(varNAME)

    return h

def event_cut( additionalCUT:str='1'):
    def all_cuts(*args):
        return '&&'.join(args).replace('  ',' ')
    basic_cut = '&&'.join(['phoFillIdx==0', 'eleVeto==1', 'jetPt>30.', 'fabs(jetEta)<2.4', 'jetPUIDbit == 7', 'jetID==1']) # jetID == 1 is loose ID
    barrel_pho = '&&'.join(['fabs(recoSCEta)<1.4442'                       , 'HoverE<0.08', 'sieieFull5x5 < 0.012', 'phoIsoRaw<15.', 'chWorstIso<15.'])
    endcap_pho = '&&'.join(['fabs(recoSCEta)>1.566' , 'fabs(recoSCEta)<2.5', 'HoverE<0.05', 'sieieFull5x5 < 0.027', 'phoIsoRaw<15.', 'chWorstIso<15.'])


    return all_cuts( basic_cut, barrel_pho, additionalCUT )

BINNING_PHOPT = (100, 190.,1000.)
BINNING_PHOETA= (40, -2.5, 2.5)
BINNING_PHOPHI= (40,-4.,4.)
BINNING_CHISO = (40, 0., 15.)
BINNING_N_VTX = (50, 0., 50.)
BINNING_JETPT = (100, 0., 1000.)

def DrawData(inTREE):
    nTEMP = 'data_%s'
    outTAG = 'expdata'
    evtWEIGHT = '1'
    evtCUT = event_cut( 'recoPtCalib>190 && (((phoFiredTrgs>>7)&1)==1)')

    hists = {}
    if debug_mode:
        hists['phoEta'] = draw(inTREE,'recoEta'    ,outTAG,'phoEta', evtCUT, evtWEIGHT, BINNING_PHOETA)
        return hists
    hists['phoPt' ] = draw(inTREE,'recoPtCalib',outTAG,'phoPt' , evtCUT, evtWEIGHT, BINNING_PHOPT )
    hists['phoEta'] = draw(inTREE,'recoEta'    ,outTAG,'phoEta', evtCUT, evtWEIGHT, BINNING_PHOETA)
    hists['phoPhi'] = draw(inTREE,'recoPhi'    ,outTAG,'phoPhi', evtCUT, evtWEIGHT, BINNING_PHOPHI)
    hists['chiso' ] = draw(inTREE,'chIsoRaw'   ,outTAG,'chiso' , evtCUT, evtWEIGHT, BINNING_CHISO )
    hists['nVtx'  ] = draw(inTREE,'nVtx'       ,outTAG,'nVtx'  , evtCUT, evtWEIGHT, BINNING_N_VTX )
    hists['jetPt' ] = draw(inTREE,'jetPt'      ,outTAG,'jetPt' , evtCUT, evtWEIGHT, BINNING_JETPT )
    return hists
def DrawMC(inTREE, outTAG,additionalCUT:str = '1',  evtWEIGHT:str='1'):
    evtCUT = event_cut( '&&'.join([additionalCUT, 'recoPt>190.']) )

    hists = {}
    if debug_mode:
        hists['phoEta'] = draw(inTREE,'recoEta'    ,outTAG,'phoEta', evtCUT, evtWEIGHT, BINNING_PHOETA)
        return hists
    hists['phoPt' ] = draw(inTREE,'recoPt'     ,outTAG,'phoPt' , evtCUT, evtWEIGHT, BINNING_PHOPT )
    hists['phoEta'] = draw(inTREE,'recoEta'    ,outTAG,'phoEta', evtCUT, evtWEIGHT, BINNING_PHOETA)
    hists['phoPhi'] = draw(inTREE,'recoPhi'    ,outTAG,'phoPhi', evtCUT, evtWEIGHT, BINNING_PHOPHI)
    hists['chiso' ] = draw(inTREE,'chIsoRaw'   ,outTAG,'chiso' , evtCUT, evtWEIGHT, BINNING_CHISO )
    hists['nVtx'  ] = draw(inTREE,'nVtx'       ,outTAG,'nVtx'  , evtCUT, evtWEIGHT, BINNING_N_VTX )
    hists['jetPt' ] = draw(inTREE,'jetPt'      ,outTAG,'jetPt' , evtCUT, evtWEIGHT, BINNING_JETPT )
    return hists

class TFileAndTree:
    def __init__(self,inFILEname:str):
        self.tfile = ROOT.TFile.Open(inFILEname)
        ttree = self.tfile.Get('t')
        from testmodule_smalltree import GetSmallTree
        self.ttree = GetSmallTree(ttree, 1000) if debug_mode else ttree

def MainFunc():
    datafile = TFileAndTree('/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/data.root'         )
    fakefile = TFileAndTree('/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/qcd.madgraph.root' )
    signfile = TFileAndTree('/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PostVFP/sig.pythia.root'   )



    expdata = DrawData( datafile.ttree )
    hsignA = DrawMC  ( signfile.ttree, 'signALL', # all weights
            'isMatched==1', 'mcweight *puwei * scalefactor_photon* jetP4Smear')
    hsign0 = DrawMC  ( signfile.ttree, 'sign0', # only luminosity weight
            'isMatched==1', 'mcweight')
    hsign1 = DrawMC  ( signfile.ttree, 'sign1', # lunminosity wieght + puwei
            'isMatched==1', 'mcweight *puwei')
    hsign2 = DrawMC  ( signfile.ttree, 'sign2', # lumi + pho sf
            'isMatched==1', 'mcweight * scalefactor_photon')
    hsign3 = DrawMC  ( signfile.ttree, 'sign3', # lumi + jetP4Smear
            'isMatched==1', 'mcweight * jetP4Smear')

    hfakeA = DrawMC  ( fakefile.ttree, 'fakeALL', # all weights
            'isMatched!=1', 'mcweight *puwei * scalefactor_photon* jetP4Smear')
    hfake0 = DrawMC  ( fakefile.ttree, 'fake0', # only luminosity weight
            'isMatched!=1', 'mcweight')
    hfake1 = DrawMC  ( fakefile.ttree, 'fake1', # lunminosity wieght + puwei
            'isMatched!=1', 'mcweight *puwei')
    hfake2 = DrawMC  ( fakefile.ttree, 'fake2', # lumi + pho sf
            'isMatched!=1', 'mcweight *scalefactor_photon')
    hfake3 = DrawMC  ( fakefile.ttree, 'fake3', # lumi + jetP4Smear
            'isMatched!=1', 'mcweight * jetP4Smear')
    hfake4 = DrawMC  ( fakefile.ttree, 'fake4', # lumi + pass max pu
            'isMatched!=1&&passMaxPUcut', 'mcweight * weight_passMaxPUcut')

    #canv = ROOT.TCanvas('c1','', 800,800)
    #canv.SetLogy()
    #h["phoPhi"].Draw("EP")
    #canv.SaveAs("hi.png")

    outfile = ROOT.TFile('dataMCcomp.root', 'recreate')
    def writeTo(outFILE, histDICT):
        dirName = histDICT['phoEta'].GetName().split('_')[0]
        tdir = outFILE.mkdir(dirName)
        tdir.cd()
        for objname, hist in histDICT.items():
            hist.SetName(objname)
            hist.Write()
    writeTo(outfile, expdata)

    writeTo(outfile, hsignA)
    writeTo(outfile, hsign0)
    writeTo(outfile, hsign1)
    writeTo(outfile, hsign2)
    writeTo(outfile, hsign3)

    writeTo(outfile, hfakeA)
    writeTo(outfile, hfake0)
    writeTo(outfile, hfake1)
    writeTo(outfile, hfake2)
    writeTo(outfile, hfake3)
    writeTo(outfile, hfake4)

    outfile.Close()









if __name__ == "__main__":
    MainFunc()


#!/usr/bin/env python3
import ROOT
from py_pt_ranges_definition import PhoPtBinning
from array import array
full_pt_range = []
MAX_HLTBIT = 8

def info(mesg):
    print(f'i@ {mesg}')

def GetArgs_IOFile(argv):
    if len(argv) < 3:
        info(f'[NoArgument] in debug mode')
        return (['ggtree_data_1031.root'], 'aa.root')
    outputFILE = argv[2]
    inputFILEs = argv[1]

    return (inputFILEs.split(','), outputFILE) # output a list and a str

def rangeDef(hltBIT):
    ''' (Nbins, xmin, xmax) '''
    if hltBIT == 0: return (40, 10, 50) # EG22
    if hltBIT == 1: return (40, 25, 80) # EG30
    if hltBIT == 2: return (40, 28,100) # EG36
    if hltBIT == 3: return (40, 40,120) # EG50
    if hltBIT == 4: return (40, 60,150) # EG75
    if hltBIT == 5: return (40, 80,200) # EG90
    if hltBIT == 6: return (40,100,250) # EG120
    if hltBIT == 7: return (40,150,400) # EG175
    if hltBIT == 8: return (40,200,800) # EG300er


def EvtSelection_BarrelPhoton():
    return "phoPFChIso[0]<2&&((phoIDbit[0]>>2)&1) == 1 && phoIDMVA[0] > 0.9  && fabs(phoEta[0]) < 1.5 && phoEleVeto[0] == 1"
def EvtSelection_EndcapPhoton():
    return "phoPFChIso[0]<2&&((phoIDbit[0]>>2)&1) == 1 && phoIDMVA[0] > 0.9  && fabs(phoEta[0]) > 1.5 && phoEleVeto[0] == 1"
def EvtSelection(barrelORendcap):
    if barrelORendcap == 'barrel':
        return EvtSelection_BarrelPhoton()
    if barrelORendcap == 'endcap':
        return EvtSelection_EndcapPhoton()

def PassPhoTrig(iBIT):
    return f"( ((phoFiredSingleTrgs[0]>>{iBIT})&1) == 1 )"
def FailPhoTrig(iBIT):
    return f"( ((phoFiredSingleTrgs[0]>>{iBIT})&1) == 1 )"
def PassJetTrig():
    return f"jetFiredTrgs[0]!=0"
def FailJetTrig():
    return f"jetFiredTrgs[0]==0"




def HLTPassingInRange(tDIR, tTREE, hltBIT, barrelORendcap):
    if hltBIT < 1 or hltBIT > MAX_HLTBIT:
        raise IOError(f'[InvalidArgument] The definition range of argument hltBIT is 1~8, the input value "{ hltBIT }" is out of range')
    tDIR.cd()
    hist_binning = rangeDef(hltBIT)
    global full_pt_range

    presel = EvtSelection(barrelORendcap)

    hists = {}
    hists['both'] =  ROOT.TH1F(f'{barrelORendcap}_both', '', hist_binning[0], hist_binning[1], hist_binning[2])
    hists['base'] =  ROOT.TH1F(f'{barrelORendcap}_base', '', hist_binning[0], hist_binning[1], hist_binning[2])
    hists['trg']  =  ROOT.TH1F(f'{barrelORendcap}_trg' , '', hist_binning[0], hist_binning[1], hist_binning[2])
    if len(full_pt_range) > 0:
        hists['both_FullRange'] =  ROOT.TH1F(f'{barrelORendcap}_both_Full', '', len(full_pt_range)-1, array('d',full_pt_range))
        hists['base_FullRange'] =  ROOT.TH1F(f'{barrelORendcap}_base_Full', '', len(full_pt_range)-1, array('d',full_pt_range))



    tTREE.Draw(f'phoEt >> {hists["both"].GetName()}', '&&'.join([presel,PassPhoTrig(hltBIT), PassPhoTrig(hltBIT-1)]))
    tTREE.Draw(f'phoEt >> {hists["base"].GetName()}', '&&'.join([presel                    , PassPhoTrig(hltBIT-1)]))
    tTREE.Draw(f'phoEt >> {hists["trg" ].GetName()}', '&&'.join([presel,PassPhoTrig(hltBIT)                       ]))
    if len(full_pt_range) > 0:
        tTREE.Draw(f'phoEt >> {hists["both_FullRange"].GetName()}', '&&'.join([presel,PassPhoTrig(hltBIT), PassPhoTrig(hltBIT-1)]))
        tTREE.Draw(f'phoEt >> {hists["base_FullRange"].GetName()}', '&&'.join([presel                    , PassPhoTrig(hltBIT-1)]))

    for key,hist in hists.items():
        hist.Write()



if __name__ == "__main__":
    import sys
    inFILEs, outFILE = GetArgs_IOFile(sys.argv)
    tchain = ROOT.TChain('ggNtuplizer/EventTree')
    for infile in inFILEs:
        info(f'[AddFile] {infile}')
        tchain.Add(infile)

    out_file = ROOT.TFile(outFILE, 'recreate')

    dataERA = 'UL2016PostVFP'
    full_pt_range = PhoPtBinning(dataERA)
    for hltBIT in range(1,MAX_HLTBIT+1): # check 1~8 instead of 0~7
        t_dir = out_file.mkdir(f'HLTbit{hltBIT}')
        HLTPassingInRange(t_dir,tchain, hltBIT, 'barrel')
        HLTPassingInRange(t_dir,tchain, hltBIT, 'endcap')
    out_file.Write()
    out_file.Close()


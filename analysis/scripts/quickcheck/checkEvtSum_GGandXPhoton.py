#!/usr/bin/env python3
import ROOT
import uproot
import numpy as np

def GetGGNtupleEntries(generalfilepath:str)->float:
    ch = ROOT.TChain('ggNtuplizer/EventTree')
    ch.Add(generalfilepath)
    return ch.GetEntries()

def GetXPhotonEntries(xphotonfilepath:str)->float:
    ifile = uproot.open(xphotonfilepath)
    ntuple = ifile['genweightsummary']

    sumgenweight_list = ntuple['sumupgenweight'].array()
    return sum(sumgenweight_list)


if __name__ == "__main__":
    numG_ch20to40_80toINF = GetGGNtupleEntries("/wk_cms3/ltsai/CRAB_FILES/UL16PreVFP_GJetPythia/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/crab_UL16PreVFP_GJetPythia_GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/221221_101221/0000/*.root")
    numX_ch20to40_80toINF = GetXPhotonEntries('GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root')
    print( numG_ch20to40_80toINF, numX_ch20to40_80toINF, numG_ch20to40_80toINF-numX_ch20to40_80toINF)

    numG_ch20toINF_40to80 = GetGGNtupleEntries('/wk_cms3/ltsai/CRAB_FILES/UL16PreVFP_GJetPythia/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8/crab_UL16PreVFP_GJetPythia_GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8/221221_100622/0000/*.root')
    numX_ch20toINF_40to80 = GetXPhotonEntries('GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root')
    print( numG_ch20toINF_40to80, numX_ch20toINF_40to80, numG_ch20toINF_40to80-numX_ch20toINF_40to80)

    numG_ch40toINF = GetGGNtupleEntries('/wk_cms3/ltsai/CRAB_FILES/UL16PreVFP_GJetPythia/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/crab_UL16PreVFP_GJetPythia_GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8/221221_100858/0000/*.root')
    numX_ch40toINF        = GetXPhotonEntries('GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root')
    print( numG_ch40toINF, numX_ch40toINF, numG_ch40toINF-numX_ch40toINF)

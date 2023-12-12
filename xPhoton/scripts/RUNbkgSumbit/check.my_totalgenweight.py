#!/usr/bin/env python3

import ROOT

if __name__ == "__main__":
    ifile_gg = ROOT.TFile.Open("hhh.root")
    gghist = ifile_gg.Get("ggNtuplizer/hSumGenWeight")
    sumupGenWeight_gg = gghist.Integral()

    ifile_my = ROOT.TFile.Open("bkgRunning/ul2016postvfp/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root")
    ntuple = ifile_my.Get("genweightsummary")

    sumupGenWeight_my = sum([evt.sumupgenweight for evt in ntuple])

    sumdiff = sumupGenWeight_gg-sumupGenWeight_my

    print(f'sumup ggntuple: {sumupGenWeight_gg} mycalculated: {sumupGenWeight_my}. The diff is {sumdiff}')

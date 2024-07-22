#!/usr/bin/env python3

import json
import numpy as np
import ROOT


def convert_xs_to_fb(val:float,unit:str)->float:
    if unit == 'fb': return val
    if unit == 'pb': return val * 1000.
    raise IOError('convert_xs_to_fb() : unknown unit "%s"'%unit)
def convert_lumi_to_fbINV(val:float,unit:str)->float:
    if unit == '1/fb': return val
    if unit == '1/pb': return val / 1000.
    raise IOError('convert_lumi_to_fbINV() : unknown unit "%s"'%unit)

class JsonIO:
    def __init__(self,inFILEname:str):
        with open(inFILEname,'r') as infile:
            self.data = json.load(infile)

    def XS(self, pdNAME:str) -> dict:
        return { ver: convert_xs_to_fb(info['xs'][0],info['xs'][2]) for ver, info in self.data[pdNAME] }
    def LumiPer1Mevt(self, pdNAME:str) -> dict:
        for ver, info in self.data[pdNAME]: print(ver,convert_lumi_to_fbINV(info['lumiper1Mevt'][0],info['lumiper1Mevt'][2]))
        return { ver: convert_lumi_to_fbINV(info['lumiper1Mevt'][0],info['lumiper1Mevt'][2]) for ver, info in self.data[pdNAME] }


class xPhotonInfo:
    integratedGenWeight = 0.
    integratedLuminosity = 0.
    crossSection = 0.
    mcweight = 0.
    def __init__(self, pdNAME:str):
        self.PD = pdNAME

def LoadXPhotonInfo(PD:str, inFILEname:str) -> xPhotonInfo:
    output = xPhotonInfo(PD)

    ifile = ROOT.TFile.Open(inFILEname)
    itree = ifile.Get('t')
    for ievt in itree:
        output.integratedGenWeight = ievt.integratedGenWeight
        output.integratedLuminosity = ievt.integratedLuminosity
        output.crossSection = ievt.crossSection
        output.mcweight = ievt.mcweight
        ifile.Close()
        return output
    raise IOError('LoadXPhotonInfo() : no any event found in this file "%s"'%inFILEname)


def PrintCheckResult(jsonINFO:JsonIO, xphotonINFO:xPhotonInfo):
    PD = xphotonINFO.PD
    XSload = xphotonINFO.crossSection
    mcweight_recalc = xphotonINFO.crossSection * xphotonINFO.integratedLuminosity / xphotonINFO.integratedGenWeight
    mcweight_load = xphotonINFO.mcweight
    mcweight_genXsec = xphotonINFO.integratedLuminosity * 1e6 /  jsonINFO.LumiPer1Mevt(PD) / xphotonINFO.integratedGenWeight

    print(f'PD: {PD}')
    print(f' -- mcweight from genXsec {mcweight_genXsec}, load {mcweight_load}, recalc {mcweight_recalc}')


if __name__ == '__main__':
    jsonInfo = JsonIO("../../data/summaryJson/summary_UL16PreVFP_GJetPythia.json")


    info_20to40_80toINF = LoadXPhotonInfo(
            "GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8" ,
            '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root'
            )
    PrintCheckResult(jsonInfo,info_20to40_80toINF)
    info_20toINF_40to80 = LoadXPhotonInfo(
            "GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8" ,
            '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCP5_13TeV_Pythia8.root'
            )
    PrintCheckResult(jsonInfo,info_20toINF_40to80)
    info_40toINF = LoadXPhotonInfo(
            "GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8" ,
            '/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/step3.btagSFappended/GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCP5_13TeV_Pythia8.root'
            )
    PrintCheckResult(jsonInfo,info_40toINF)

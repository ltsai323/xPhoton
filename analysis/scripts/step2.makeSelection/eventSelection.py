#!/usr/bin/env python2
import ROOT

def basic_selection():
    return ''
def photon_selection():
    return ''
def jet_selection():
    return ''

def binning_phopt():
    return ''
def binning_phoeta():
    return ''
def binning_jeteta():
    return ''

if __name__ == "__main__":
    dframe=ROOT.RDataFrame('t',"/home/ltsai/ReceivedFile/GJet/latestsample/QCD_madgraph.root")
    dframe.Filter("recoEta>10")


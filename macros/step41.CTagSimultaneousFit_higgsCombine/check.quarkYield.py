#!/usr/bin/env python3

import ROOT
def LOG(*args):
    print('[check.quarkYield LOG] ', *args)
def GetHist(
    iFILE:ROOT.TFile, histNAME:str,
    lineCOLOR:int = 2,
    lineWIDTH:int = 0,
    fillCOLOR:int = 0,
    fillSTYLE:int = 1,
    markerCOLOR:int = 1,
    markerSTYLE:int = 33,
    markerSIZE:int = 0,
    xAXISname:str = '',
    ):
    LOG(f'GetHist() : Loading {histNAME}')
    h = iFILE.Get(histNAME)
    h.SetLineColor(lineCOLOR)
    h.SetLineWidth(lineWIDTH)
    h.SetFillColor(fillCOLOR)
    h.SetFillStyle(fillSTYLE)

    h.SetMarkerColor(markerCOLOR)
    h.SetMarkerStyle(markerSTYLE)
    h.SetMarkerSize(markerSIZE)

    if xAXISname == 'hist.GetTitle()':
        h.GetXaxis().SetTitle(h.GetTitle())
    else:
        h.GetXaxis().SetTitle(xAXISname)

    return h

def CheckHist(iFILE, folderNAME):
    hc = iFILE.Get(f'{folderNAME}/signal_C')
    hb = iFILE.Get(f'{folderNAME}/signal_B')
    hl = iFILE.Get(f'{folderNAME}/signal_L')
    print(f'quark yield = b({hb.Integral():8.1f}), c({hc.Integral():8.1f}), l({hl.Integral():8.1f})')


if __name__ == "__main__":
    inFILE = 'postfit.root'
    ifile = ROOT.TFile.Open(inFILE)
    CheckHist(ifile,'cat_0_postfit')
    CheckHist(ifile,'cat_1_postfit')
    CheckHist(ifile,'cat_2_postfit')


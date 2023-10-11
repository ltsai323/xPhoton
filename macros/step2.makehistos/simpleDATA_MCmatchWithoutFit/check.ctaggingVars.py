#!/usr/bin/env python3

import ROOT
from xPhoton.analysis.MyCanvas import MyCanvasSetup, MyRatioCanvasSetup
from xPhoton.analysis.PlotObjectMgr import HistFraming as framingFUNC
from xPhoton.analysis.PlotObjectMgr import Legend

def GetHist(
    iFILE:ROOT.TFile, histNAME:str,
    lineCOLOR:int = 2,
    lineWIDTH:int = 0,
    fillCOLOR:int = 0,
    fillSTYLE:int = 1,
    markerCOLOR:int = 1,
    markerSTYLE:int = 33,
    markerSIZE:int = 0):
    h = iFILE.Get(histNAME)
    h.SetLineColor(lineCOLOR)
    h.SetLineWidth(lineWIDTH)
    h.SetFillColor(fillCOLOR)
    h.SetFillStyle(fillSTYLE)

    h.SetMarkerColor(markerCOLOR)
    h.SetMarkerStyle(markerSTYLE)
    h.SetMarkerSize(markerSIZE)


    return h
def HistFraming(h, varNAME):
    '''
    Setup a TH1 like object.
    No argument needed.
    '''
    binwidth = h.GetXaxis().GetBinWidth(1)
    framingFUNC(h,
                xLABEL=varNAME,yLABEL=f'Entries / {binwidth}',
                minFACTOR = 0.5e-1, maxFACTOR = 1e4
                )


def varCheckInCTaggingWeighted(varNAME:str, inFILE:ROOT.TFile):
    print(f'[INFO] received input file {inFILE.GetName()}')
    hdata = GetHist(inFILE,f'{varNAME}/hdata',
                    markerCOLOR=1, markerSIZE=2)
    hsign = GetHist(inFILE,f'{varNAME}/hsign_weighed',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001)
    hfake = GetHist(inFILE,f'{varNAME}/hfake_weighed',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001)
    hside = GetHist(inFILE,f'{varNAME}/hside',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001)
    ''' scaling section '''
    hsign_w_orig = inFILE.Get("weight_integration/hsign")
    hsign_w_weig = inFILE.Get("weight_integration/hsign_weighed")
    re_normalization_sign = hsign_w_orig.GetBinContent(1) / hsign_w_weig.GetBinContent(1)
    hsign.Scale(re_normalization_sign)

    hfake_w_orig = inFILE.Get("weight_integration/hfake")
    hfake_w_weig = inFILE.Get("weight_integration/hfake_weighed")
    re_normalization_fake = hfake_w_orig.GetBinContent(1) / hfake_w_weig.GetBinContent(1)
    hfake.Scale(re_normalization_fake)


    the_factor = round(hdata.Integral() / (hsign.Integral()+hfake.Integral()),2)
    print(f'[BUGGING] tunned scale factor : {the_factor}')
    hsign.Scale(the_factor)
    hfake.Scale(the_factor)
    hside.Scale(hfake.Integral() / hside.Integral())

    hdata.SetTitle( 'data in 19.52 fb^{-1}')
    hsign.SetTitle(f'weighed gjet MC sample (#times{the_factor})')
    hfake.SetTitle(f'weighed QCD MC samele (#times{the_factor})')
    hside.SetTitle(f'data sideband as di-jet contribution')
    ''' scaling section end'''

    return draw_stackplot_comparison("weighed_"+varNAME, inFILE.GetName(), hdata, hsign, hside)

    return draw_stackplot_comparison(varNAME, inFILE.GetName(), hdata, hsign, hside)
def varCheck(varNAME:str, inFILE:ROOT.TFile):
    print(f'[INFO] received input file {inFILE.GetName()}')
    hdata = GetHist(inFILE,f'{varNAME}/hdata',
                    markerCOLOR=1, markerSIZE=2)
    hsign = GetHist(inFILE,f'{varNAME}/hsign',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001)
    hfake = GetHist(inFILE,f'{varNAME}/hfake',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001)
    hside = GetHist(inFILE,f'{varNAME}/hside',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001)
    ''' scaling section '''
    the_factor = round(hdata.Integral() / (hsign.Integral()+hfake.Integral()),2)
    print(f'[BUGGING] tunned scale factor : {the_factor}')
    hsign.Scale(the_factor)
    hfake.Scale(the_factor)
    hside.Scale(hfake.Integral() / hside.Integral())

    hdata.SetTitle( 'data in 19.52 fb^{-1}')
    hsign.SetTitle(f'gjet MC sample (#times{the_factor})')
    hfake.SetTitle(f'QCD MC samele (#times{the_factor})')
    hside.SetTitle(f'data sideband as di-jet contribution')
    ''' scaling section end'''

    return draw_stackplot_comparison(varNAME, inFILE.GetName(), hdata, hsign, hside)


def draw_stackplot_comparison(varNAME, inFILE, hDATA, hSIGN, hFAKE):
    ROOT.gROOT.SetBatch(True)
    hdata = hDATA
    hsign = hSIGN
    hfake = hFAKE

    canv, upperpad, lowerpad = MyRatioCanvasSetup()
    upperpad.cd()

    stackplot = ROOT.THStack('hs', '')
    #stackplot.SetTitle(ftag)

    stackplot.Add(hsign, "HIST")
    stackplot.Add(hfake, "HIST")
    #stackplot.Add(hside, "HIST")
    stackplot.Draw()
    HistFraming(stackplot, varNAME)

    useLogScale = False
    if useLogScale:
        maxFACTOR = 1e3
        stackplot.SetMinimum( 1e-3 )
        stackplot.SetMaximum( hdata.GetMaximum() * maxFACTOR)
        canv.SetLogy()
        pad.SetLogy()
    else:
        minFACTOR = 1e-2
        maxFACTOR = 1.5
        stackplot.SetMinimum( hdata.GetMinimum() * minFACTOR)
        stackplot.SetMaximum( hdata.GetMaximum() * maxFACTOR)

    #stackplot.GetXaxis().SetTitle( hdata.GetXaxis().SetTitle() )


    stackplot.Draw()
    hdata.Draw("E0 P SAME")


    fileFrag = inFILE.split('.')[0].split('_')
    if len(fileFrag) == 8:
        # input file as the format: out_kinematics_0_1__ptcut_400_600.root
        pEtaName='PETAnotfound'
        if fileFrag[2] == '0':
            pEtaName = '|\eta^{\gamma}| < 1.4442'
        if fileFrag[2] == '1':
            pEtaName = '1.566 < |\eta^{\gamma}| < 2.5'

        jEtaName='JETAnotfound'
        if fileFrag[3] == '0':
            jEtaName = '|\eta^{jet}| < 1.5'
        if fileFrag[3] == '1':
            jEtaName = '1.5 < |\eta^{jet}| < 2.4'
        pPtName = f'p_{{T}}^{{\gamma}} = [{fileFrag[-2]},{fileFrag[-1]}] GeV'

        leg_title = ','.join([pEtaName,jEtaName,pPtName])
    else:
        # other input file
        leg_title = 'UL2016PreVFP'

    leg = Legend( p0_=(0.2,0.68), p1_=(0.8,0.90), title=leg_title, useNDC=True)

    leg.AddEntry(hdata, hdata.GetTitle(), 'p')
    leg.AddEntry(hsign, hsign.GetTitle(), 'f')
    leg.AddEntry(hfake, hfake.GetTitle(), 'f')
    leg.Draw()

    lowerpad.cd()

    hratio = hdata.Clone('dataOVERmc')
    hratio.Divide(hdata,stackplot.GetStack().Last())

    hratio.SetTitle('')
    hratio.SetStats(False)
    hratio.SetMinimum(0.5)
    hratio.SetMaximum(1.6)
    hratio.GetXaxis().SetTitleSize(0.11)
    hratio.GetXaxis().SetLabelSize(0.11)
    hratio.GetYaxis().SetTitleSize(0.11)
    hratio.GetYaxis().SetLabelSize(0.11)
    hratio.GetYaxis().SetTitleOffset(0.4)
    hratio.GetYaxis().SetNdivisions(905)
    hratio.GetYaxis().CenterTitle(True)
    hratio.SetLineColor(1)
    hratio.SetXTitle( stackplot.GetXaxis().GetTitle() )
    hratio.SetYTitle('Data/MC')
    #hratio.SetMinimum(0.7)
    #hratio.SetMaximum(1.3)

    hratio.Draw("P")

    refline = ROOT.TLine(
            hratio.GetXaxis().GetXmin(), 1.,
            hratio.GetXaxis().GetXmax(), 1.)
    refline.SetLineColor(1)
    refline.SetLineStyle(2) # dashed line
    refline.Draw("SAME")
    hratio.Draw("P SAME")

    ftag = '_'.join(fileFrag)
    canv.SaveAs(f"varCheck_{varNAME}_{ftag}.pdf")
    #canv.SaveAs(f"varCheck_{outTAG}.pdf")
    #canv.SaveAs(f"varCheck_{varNAME}_{ftag}.C")
if __name__ == "__main__":
    import sys
    inputfile = sys.argv[1]
    print(f'[INFO] input file {inputfile}\n\n\n')


    import xPhoton.analysis.MyCanvas
    #xPhoton.analysis.MyCanvas.testing = False
    xPhoton.analysis.MyCanvas.isTransparent = False

    ### Get re-normalization factor
    inFile = ROOT.TFile.Open(inputfile)


    varCheck('DeepFlavour.bScore',inFile)
    varCheck('DeepCSV.CvsL',inFile)
    varCheck('DeepCSV.CvsB',inFile)
    varCheckInCTaggingWeighted('DeepFlavour.bScore',inFile)
    varCheckInCTaggingWeighted('DeepCSV.CvsL',inFile)
    varCheckInCTaggingWeighted('DeepCSV.CvsB',inFile)
    varCheck('mva',inFile)
    varCheck('recoPhi',inFile)

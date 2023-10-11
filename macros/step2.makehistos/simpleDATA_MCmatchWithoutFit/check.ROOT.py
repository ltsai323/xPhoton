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
def HistFraming(h):
    '''
    Setup a TH1 like object.
    No argument needed.
    '''
    binwidth = h.GetXaxis().GetBinWidth(1)
    framingFUNC(h,
                xLABEL='BDT score',yLABEL=f'Entries / {binwidth}',
                minFACTOR = 0.5e-1, maxFACTOR = 1e4
                )

    # h.GetXaxis().SetTitle('BDT score')
    # h.GetYaxis().SetTitle('Entries / 0.2')
    # h.SetMaximum(1e7)
    # h.SetMinimum(1e3)


def varCheck(varNAME:str, inFILE:str='out_kinematics.root'):
    import xPhoton.analysis.MyCanvas
    xPhoton.analysis.MyCanvas.testing = False
    print(f'[INFO] received input file {inFILE}')


    # remove .root name
    ftag = '.'.join(inFILE.split('.')[:-1])

    ROOT.gROOT.SetBatch(True)
    ifile = ROOT.TFile.Open(inFILE)
    hdata = GetHist(ifile,f'{varNAME}/hdata',
                    markerCOLOR=1, markerSIZE=2)
    hsign = GetHist(ifile,f'{varNAME}/hsign',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001)
    hfake = GetHist(ifile,f'{varNAME}/hfake',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001)
    ''' scaling section '''
    the_factor = round(hdata.Integral() / (hsign.Integral()+hfake.Integral()),2)
    print(f'[BUGGING] tunned scale factor : {the_factor}')
    #the_factor = 1.63 # factor from barrel, barrel, 200 to inf
    #the_factor = 1.65 # factor from barrel, barrel, 200 to 400
    #the_factor = 1.28 # factor from barrel, barrel, 400 to 600
    #the_factor = 1.17 # factor from barrel, barrel, 600 to 800
    hsign.Scale(the_factor)
    hfake.Scale(the_factor)
    ''' scaling section end'''



    #canv, pad = MyCanvasSetup()
    canv, upperpad, lowerpad = MyRatioCanvasSetup()
    upperpad.cd()

    stackplot = ROOT.THStack('hs', ftag)
    stackplot.Add(hsign, "HIST")
    stackplot.Add(hfake, "HIST")
    stackplot.Draw()
    HistFraming(stackplot)

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

    stackplot.GetXaxis().SetTitle(varNAME)
    stackplot.SetTitle('')


    stackplot.Draw()
    hdata.Draw("E0 P SAME")
    #hdata.Draw("E0 P")


    fileFrag = inFILE.split('.')[0].split('_')
    if len(fileFrag) == 8:
        # input file as the format: out_kinematics_0_1__ptcut_400_600.root
        pEtaName='PETAnotfound'
        for idx, frag in enumerate(fileFrag):
            print(idx,frag)
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
        leg_title = ''

    leg = Legend( p0_=(0.2,0.68), p1_=(0.8,0.90), title=leg_title, useNDC=True)

    leg.AddEntry(hdata, 'data in 19.52 fb^{-1}', 'p')
    leg.AddEntry(hsign, f'gjet MC sample (#times{the_factor})', 'f')
    leg.AddEntry(hfake, f'QCD MC samele (#times{the_factor})', 'f')
    leg.Draw()

    lowerpad.cd()

    hratio = hdata.Clone('dataOVERmc')
    hratio.Divide(hdata,stackplot.GetStack().Last())

    hratio.SetTitle('')
    hratio.SetStats(False)
    hratio.SetMinimum(0.0)
    hratio.SetMaximum(2.1)
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

    #pad.BuildLegend()

    canv.SaveAs(f"varCheck_{varNAME}_{ftag}.pdf")
    #canv.SaveAs(f"varCheck_{varNAME}_{ftag}.C")
if __name__ == "__main__":
    import sys
    inputfile = sys.argv[1]
    print(f'[INFO] input file {inputfile}\n\n\n')


    import xPhoton.analysis.MyCanvas
    xPhoton.analysis.MyCanvas.isTransparent = False
    #varCheck('DeepFlavour.bScore',inputfile)
    #varCheck('DeepCSV.CvsL',inputfile)
    #varCheck('DeepCSV.CvsB',inputfile)
    varCheck('mva',inputfile)
    #varCheck('recoPhi',inputfile)
    #varCheck('recoEta',inputfile)
    #varCheck('recoPhi',inputfile)
    #varCheck('recoEta',inputfile)
    #varCheck('r9Full5x5',inputfile)
    #varCheck('s4Full5x5',inputfile)
    #varCheck('rho',inputfile)
    #varCheck('sieieFull5x5',inputfile)

    #varCheck('sieipFull5x5',inputfile)
    #varCheck('recoSCEta',inputfile)
    #varCheck('rawE',inputfile)
    #varCheck('scEtaWidth',inputfile)
    #varCheck('scPhiWidth',inputfile)
    #varCheck('esEnergyOverSCRawEnergy',inputfile)

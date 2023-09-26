#!/usr/bin/env python3

import ROOT
from xPhoton.analysis.MyCanvas import MyCanvasSetup, MyRatioCanvasSetup
from xPhoton.analysis.PlotObjectMgr import HistFraming as framingFUNC
from xPhoton.analysis.PlotObjectMgr import Legend
from py_pt_ranges_definition import PhoPtBinning

def LOG(*args):
    print('[LOG] ', *args)

class BinnedYield:
    def __init__(self, datFILE):


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
    h = iFILE.Get(histNAME)
    h.SetLineColor(lineCOLOR)
    h.SetLineWidth(lineWIDTH)
    h.SetFillColor(fillCOLOR)
    h.SetFillStyle(fillSTYLE)

    h.SetMarkerColor(markerCOLOR)
    h.SetMarkerStyle(markerSTYLE)
    h.SetMarkerSize(markerSIZE)

    h.GetXaxis().SetTitle(xAXISname)


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

class CommonVars:
    def __init__(self, inFILE):
        self.ifile = inFILE
        self.canv, self.upperpad, self.lowerpad = MyRatioCanvasSetup()

### old variables loading method
def varCheckInCTaggingWeighted(varNAME:str, inFILE:ROOT.TFile):
    print(f'[INFO] received input file {inFILE.GetName()}')
    hdata = GetHist(inFILE,f'{varNAME}/hdata',
                    markerCOLOR=1, markerSIZE=2, xAXISname=varName)
    hsign = GetHist(inFILE,f'{varNAME}/hsign_weighed',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001, xAXISname=varName)
    hfake = GetHist(inFILE,f'{varNAME}/hfake_weighed',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
    hside = GetHist(inFILE,f'{varNAME}/hside',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
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

    ## old version modification needed
    #return draw_stackplot_comparison("weighed_"+varNAME, inFILE.GetName(), hdata, hsign, hside)

    #return draw_stackplot_comparison(varNAME, inFILE.GetName(), hdata, hsign, hside)


def merge_hist(newname, hists):
    h = hists[0].Clone()
    h.SetName(newname)

    hists.pop(0)
    for hist in hists: h.Add(hist)
    return h

def CTaggingVarCentral(folderNAME:str, commonobj:CommonVars):
    inFILE = commonobj.ifile
    binName=folderNAME
    for i in range(3):
        varName = f'jettag{i:d}'
        print(f'[INFO] received input file {inFILE.GetName()}')
        hdata = GetHist(inFILE,f'{folderNAME}/{varName}_data_signalRegion',
                        markerCOLOR=1, markerSIZE=2, xAXISname=varName)
        hsign1= GetHist(inFILE,f'{folderNAME}/{varName}_gjet_GJetsL_signalRegion_central',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001, xAXISname=varName)
        hsign2= GetHist(inFILE,f'{folderNAME}/{varName}_gjet_GJetsC_signalRegion_central',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001, xAXISname=varName)
        hsign3= GetHist(inFILE,f'{folderNAME}/{varName}_gjet_GJetsB_signalRegion_central',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001, xAXISname=varName)
        hfake1= GetHist(inFILE,f'{folderNAME}/{varName}_QCD_DiJetL_signalRegion_central',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
        hfake2= GetHist(inFILE,f'{folderNAME}/{varName}_QCD_DiJetC_signalRegion_central',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
        hfake3= GetHist(inFILE,f'{folderNAME}/{varName}_QCD_DiJetB_signalRegion_central',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
        hside = GetHist(inFILE,f'{folderNAME}/{varName}_data_dataSideband',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
        hsign = merge_hist(f'{varName}_gjet_signalRegion_central', [hsign1,hsign2,hsign3])
        #hfake = merge_hist(f'{varName}_QCD_signalRegion_central',  [hfake1,hfake2,hfake3])
        hfake = hfake1.Clone(f'{varName}_QCD_signalRegion_central')
        hfake.Add(hfake2)
        hfake.Add(hfake3)

        ''' scaling section '''
        the_factor = round(hdata.Integral() / (hsign.Integral()+hfake.Integral()),2)
        print(f'[BUGGING] tunned scale factor : {the_factor}')
        hsign.Scale(the_factor)
        hfake.Scale(the_factor)
        hside.Scale(hfake.Integral() / hside.Integral())

        hdata.SetTitle( 'data in 19.52 fb^{-1}')
        hsign.SetTitle(f'gjet MC sample (#times{the_factor})')
        hfake.SetTitle(f'QCD MC samele (#times{the_factor})')
        hside.SetTitle(f'di-jet contribution from data sideband')
        ''' scaling section end'''

        pEtaBin, jEtaBin, pPtBin = [ int(thebin) for thebin in binName.split('_')[1:] ]

        legTitle = binning_info(pEtaBin,jEtaBin,pPtBin)
        newfilename = f"varCheck_{varName}_{pEtaBin}_{jEtaBin}_{pPtBin}_central"
        draw_stackplot_comparison(newfilename, legTitle, hdata, hsign, hside, commonobj)
def CTaggingVarOriginal(folderNAME:str, commonobj:CommonVars):
    inFILE = commonobj.ifile
    binName=folderNAME
    for i in range(3):
        varName = f'jettag{i:d}'
        print(f'[INFO] received input file {inFILE.GetName()}')
        hdata = GetHist(inFILE,f'{folderNAME}/{varName}_data_signalRegion',
                        markerCOLOR=1, markerSIZE=2, xAXISname=varName)
        hsign1= GetHist(inFILE,f'{folderNAME}/{varName}_gjet_GJetsL_signalRegion_original',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001, xAXISname=varName)
        hsign2= GetHist(inFILE,f'{folderNAME}/{varName}_gjet_GJetsC_signalRegion_original',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001, xAXISname=varName)
        hsign3= GetHist(inFILE,f'{folderNAME}/{varName}_gjet_GJetsB_signalRegion_original',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001, xAXISname=varName)
        hfake1= GetHist(inFILE,f'{folderNAME}/{varName}_QCD_DiJetL_signalRegion_original',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
        hfake2= GetHist(inFILE,f'{folderNAME}/{varName}_QCD_DiJetC_signalRegion_original',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
        hfake3= GetHist(inFILE,f'{folderNAME}/{varName}_QCD_DiJetB_signalRegion_original',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
        hside = GetHist(inFILE,f'{folderNAME}/{varName}_data_dataSideband',
                        lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
        hsign = merge_hist(f'{varName}_gjet_signalRegion_original', [hsign1,hsign2,hsign3])
        hfake = merge_hist(f'{varName}_QCD_signalRegion_original',  [hfake1,hfake2,hfake3])

        ''' scaling section '''
        the_factor = round(hdata.Integral() / (hsign.Integral()+hfake.Integral()),2)
        print(f'[BUGGING] tunned scale factor : {the_factor}')
        hsign.Scale(the_factor)
        hfake.Scale(the_factor)
        hside.Scale(hfake.Integral() / hside.Integral())

        hdata.SetTitle( 'data in 19.52 fb^{-1}')
        hsign.SetTitle(f'gjet MC sample (#times{the_factor})')
        hfake.SetTitle(f'QCD MC samele (#times{the_factor})')
        hside.SetTitle(f'di-jet contribution from data sideband')
        ''' scaling section end'''

        pEtaBin, jEtaBin, pPtBin = [ int(thebin) for thebin in binName.split('_')[1:] ]

        legTitle = binning_info(pEtaBin,jEtaBin,pPtBin)
        newfilename = f"varCheck_{varName}_{pEtaBin}_{jEtaBin}_{pPtBin}_original"
        draw_stackplot_comparison(newfilename, legTitle, hdata, hsign, hside, commonobj)
def BDTCheck(folderNAME:str, commonobj:CommonVars):
    inFILE = commonobj.ifile
    varName='BDTscore'
    binName=folderNAME
    print(f'[INFO] received input file {inFILE.GetName()}')
    hdata = GetHist(inFILE,f'{folderNAME}/BDT_data_signalRegion',
                    markerCOLOR=1, markerSIZE=2, xAXISname=varName)
    hsign = GetHist(inFILE,f'{folderNAME}/BDT_gjet_signalRegion',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=2 , fillSTYLE=1001, xAXISname=varName)
    hfake = GetHist(inFILE,f'{folderNAME}/BDT_QCD_signalRegion',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)
    hside = GetHist(inFILE,f'{folderNAME}/BDT_data_dataSideband',
                    lineCOLOR=1 , lineWIDTH=2, fillCOLOR=38, fillSTYLE=1001, xAXISname=varName)

    ''' scaling section '''
    the_factor = round(hdata.Integral() / (hsign.Integral()+hfake.Integral()),2)
    print(f'[BUGGING] tunned scale factor : {the_factor}')
    hsign.Scale(the_factor)
    hfake.Scale(the_factor)
    hside.Scale(hfake.Integral() / hside.Integral())

    hdata.SetTitle( 'data in 19.52 fb^{-1}')
    hsign.SetTitle(f'gjet MC sample (#times{the_factor})')
    hfake.SetTitle(f'QCD MC samele (#times{the_factor})')
    hside.SetTitle(f'di-jet contribution from data sideband')
    ''' scaling section end'''

    pEtaBin, jEtaBin, pPtBin = [ int(thebin) for thebin in binName.split('_')[1:] ]

    legTitle = binning_info(pEtaBin,jEtaBin,pPtBin)
    newfilename = f"varCheck_{varName}_{pEtaBin}_{jEtaBin}_{pPtBin}"
    draw_stackplot_comparison(newfilename, legTitle, hdata, hsign, hside, commonobj)

    low_statistics_warning = True if hsign.GetEntries() < 100 or hfake.GetEntries() < 100 else False
    return low_statistics_warning

def binning_info(pETAbin, jETAbin, pPTbin):
    # input file as the format: out_kinematics_0_1__ptcut_400_600.root
    pEtaName='PETAnotfound'
    if pETAbin == 0:
        pEtaName = '|\eta^{\gamma}| < 1.4442'
    if pETAbin == 1:
        pEtaName = '1.566 < |\eta^{\gamma}| < 2.5'

    jEtaName='JETAnotfound'
    if jETAbin == 0:
        jEtaName = '|\eta^{jet}| < 1.5'
    if jETAbin == 1:
        jEtaName = '1.5 < |\eta^{jet}| < 2.4'

    pt_ranges = PhoPtBinning('UL2016')
    pPTrange = [ pt_ranges[pPTbin],pt_ranges[pPTbin+1] ]
    pPtName = f'p_{{T}}^{{\gamma}} = [{pPTrange[0]},{pPTrange[1]}] GeV'

    return ','.join([pEtaName,jEtaName,pPtName])
def extract_binning_info_from_filename(inFILE):
    fileFrag = inFILE.split('.')[0].split('_')
    if len(fileFrag) == 8:
        petabin = int(fileFrag[2])
        jetabin = int(fileFrag[3])
        pptrange = [ int(fileFrag[-2]), int(fileFrag[-1]) ]
        return binning_info(petabin,jetabin,pptrange)
    return 'FAILED_EXTRACTED_BINNING_INFO'



def draw_stackplot_comparison(
        outputFILEname,
        legendTITLE,
        hDATA, hSIGN, hFAKE,
        commonobj:CommonVars):
    ROOT.gROOT.SetBatch(True)
    hdata = hDATA
    hsign = hSIGN
    hfake = hFAKE

    canv = commonobj.canv
    upperpad = commonobj.upperpad
    lowerpad = commonobj.lowerpad
    #canv, upperpad, lowerpad = MyRatioCanvasSetup()
    upperpad.cd()

    stackplot = ROOT.THStack('hs', '')

    stackplot.Add(hsign, "HIST")
    stackplot.Add(hfake, "HIST")
    stackplot.Draw()
    HistFraming(stackplot, hsign.GetXaxis().GetTitle())

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

    #leg_title = binning_info(pETAbin,jETAbin,pPTrange)
    leg_title = legendTITLE

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


    ndof = 0.
    chi2 = 0.
    for ibin in range(1,hratio.GetNbinsX()+1):
        bincont = hratio.GetBinContent(ibin)
        binerro = hratio.GetBinError(ibin)
        LOG(f"bin{ibin} at content {bincont:.2e} and error {binerro:.2e}. The calculated chi2 is {(bincont-1)*(bincont-1)/binerro/binerro:.2e}")
        if bincont == 0.: continue
        ndof += 1
        c2 = (bincont - 1.)**2 / binerro / binerro
        chi2 += c2
    chi2_value = chi2 / ndof
    latex = ROOT.TLatex()
    latex.SetTextSize(0.14)
    latex.SetNDC()
    latex.DrawLatex(0.45,0.9, f'chi2/dof = {chi2_value:.1f}')

    refline = ROOT.TLine(
            hratio.GetXaxis().GetXmin(), 1.,
            hratio.GetXaxis().GetXmax(), 1.)
    refline.SetLineColor(1)
    refline.SetLineStyle(2) # dashed line
    refline.Draw("SAME")
    hratio.Draw("P SAME")

    canv.SaveAs(f"{outputFILEname}.pdf")
if __name__ == "__main__":
    import sys
    #inputfile = sys.argv[1]
    inputfile = 'makehisto.root'
    print(f'[INFO] input file {inputfile}\n\n\n')
    inputfitresult = 'UL2016PreVFP.data.bkg.dat'


    import xPhoton.analysis.MyCanvas
    xPhoton.analysis.MyCanvas.isTransparent = False

    inFile = ROOT.TFile.Open(inputfile)

    commonobj = CommonVars(inFile)

    for pEtaBin in range(2):
        for jEtaBin in range(2):
            for pPtBin in range(10,16):
                lowStatusWarning = BDTCheck(f'bin_{pEtaBin}_{jEtaBin}_{pPtBin}',commonobj)
                if lowStatusWarning == True:
                    ptrange = PhoPtBinning('UL2016')
                    LOG(f'\n------\n[bin_{pEtaBin}_{jEtaBin}_{pPtBin}] pt {ptrange[pPtBin]} to {ptrange[pPtBin+1]} gjet or QCD has very low statistics. Attempt not to draw plot\n------\n')
                    continue
                CTaggingVarOriginal(f'bin_{pEtaBin}_{jEtaBin}_{pPtBin}',commonobj)
                CTaggingVarCentral(f'bin_{pEtaBin}_{jEtaBin}_{pPtBin}',commonobj)

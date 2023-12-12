#!/usr/bin/env python3

import ROOT
from array import array

from py_pt_ranges_definition import PhoPtBinning
from py_pt_ranges_definition import FindEffLumi
from DATReadingTools import ReadEvt_FitResult, ReadEvt_Eff, BinValue



def NewCanvas(isRatioPlot):
    class MyCanvas:
        def __init__(self):
            self.canv = ROOT.TCanvas('canv','',1000,1200)
            self.pads = []
        def cd(self,layer= 0):
            if layer == 0:
                self.canv.cd()
                return
            self.pads[layer-1].cd()
            self.pads[layer-1].Draw()
        def SaveAs(self,filename):
            self.canv.SaveAs(filename)

    canv = MyCanvas()
    canv.canv.SetFillColor(4000)
    canv.canv.SetFillStyle(4000)

    if isRatioPlot:
        # cd(0) canvas
        # cd(1) upperpad
        # cd(2) lowerpad
        canv.cd()

        upperpad = ROOT.TPad('upperpad','',0.,0.25,1.,1.)
        upperpad.SetBottomMargin(0)
        upperpad.SetFillColor(4000)
        upperpad.SetFillStyle(4000)
        upperpad.Draw()
        upperpad.cd()
        upperpad.SetLogy()
        upperpad.SetGrid()
        canv.pads.append(upperpad)

        canv.cd()
        lowerpad = ROOT.TPad('lowerpad','',0.,0.,1.,0.25)
        lowerpad.SetTopMargin(0)
        lowerpad.SetFillColor(4000)
        lowerpad.SetFillStyle(4000)
        lowerpad.cd()
        lowerpad.SetGridy()
        canv.pads.append(lowerpad)

        canv.cd()
    else:
        canv.cd()

        allofpad = ROOT.TPad('allofpad','',0.,0.,1.,0.98)
        allofpad.SetTicks(1,1)
        allofpad.SetTopMargin(0.05)
        allofpad.SetBottomMargin(0.12)
        allofpad.SetLeftMargin(0.135)
        allofpad.SetRightMargin(0.06)
        allofpad.SetGrid()
        allofpad.Draw()
        allofpad.cd()
        allofpad.SetLogy()
        canv.pads.append(allofpad)

        canv.cd()
    return canv
def MyLegend(hists):
    #leg = ROOT.TLegend(0.35, 0.55, 0.88, 0.90)
    leg = ROOT.TLegend(0.29, 0.71, 0.90, 0.92)
    #leg.SetHeader()
    leg.SetFillColor(0)
    leg.SetShadowColor(0)
    leg.SetBorderSize(1)

    for hist in hists:
        hist_desc = str()

        name = hist.GetName()
        if '0_0' in name: hist_desc = '|y^{#gamma}|<1.4442,|y^{jet}|<1.5'
        if '0_1' in name: hist_desc = '|y^{#gamma}|<1.4442,1.5<|y^{jet}|<2.4'
        if '1_0' in name: hist_desc = '1.566<|y^{#gamma}|<2.5,|y^{jet}|<1.5'
        if '1_1' in name: hist_desc = '1.566<|y^{#gamma}|<2.5,1.5<|y^{jet}|<2.4'
        if not hist_desc: hist_desc = name
        leg.AddEntry(hist,hist_desc,'pl')
    return leg
def MyLegend_Sep(hists,refhists):
    leg = ROOT.TLegend(0.29, 0.71, 0.90, 0.92)
    leg.SetFillColor(0)
    #leg.SetFillColor(4000)
    #leg.SetFillStyle(4000)
    leg.SetShadowColor(0)
    leg.SetBorderSize(1)
    leg.SetNColumns(2)

    for hist,refhist in zip(hists,refhists):
        hist_desc = str()

        name = hist.GetName()
        if '0_0' in name: hist_desc = 'barrel #gamma, barrel jet (x10^{6})'
        if '0_1' in name: hist_desc = 'barrel #gamma, endcap jet (x10^{4})'
        if '1_0' in name: hist_desc = 'endcap #gamma, barrel jet (x10^{2})'
        if '1_1' in name: hist_desc = 'endcap #gamma, endcap jet'
        if not hist_desc: hist_desc = name
        leg.AddEntry(hist,hist_desc,'pl')
        leg.AddEntry(refhist,'2015 '+hist_desc,'pl')
    return leg



# bin_width and eff_lumi re-scale
def Hist_PhotonCrossSection(pETAbin,jETAbin, ptBINNING, fitVALUES, effSOURCES = {}):
    histname = 'h_photonCrossSection_%d_%d' % (pETAbin,jETAbin)
    hist = ROOT.TH1F( histname, '#gamma+jet cross section', len(ptBINNING)-1, ptBINNING )

    hist.GetXaxis().SetTitle('E^{#gamma}_{T} (GeV)')
    hist.GetYaxis().SetTitle('d^{3} #sigma / dE^{#gamma}_{T} dy^{#gamma} dy^{jet} [pb/GeV]')
    for binIdx in range(1,hist.GetNbinsX()+1):
        pPtBin = binIdx-1

        fitvalue, fiterror = BinValue(pETAbin,jETAbin,pPtBin, fitVALUES)
        bin_numerator = fitvalue


        eff_sum = 1.
        for effname,effsource in effSOURCES.items():
            jetabin = 0 if effname == 'presel' else jETAbin
            effval,efferr = BinValue(pETAbin,jetabin,pPtBin, effsource)
            eff_sum *= effval

        fbTOpb = 1e-3 # 1fb = 0.001pb
        eff_lumi = FindEffLumi(dataEra,pPtBin) / fbTOpb # fb-1 -> pb-1
        print(f'eff lumi of pt: {pPtBin} is {eff_lumi}')
        peta_width=1.4442*2. if pETAbin == 0 else (2.5-1.566)*2.
        jeta_width=1.5*2.    if jETAbin == 0 else (2.4-1.5  )*2.
        ppt_width=ptBINNING[pPtBin+1]-ptBINNING[pPtBin] if pPtBin != hist.GetNbinsX() else 1000.
        bin_denominator = peta_width*jeta_width*ppt_width * eff_lumi * eff_sum

        hist.SetBinContent( binIdx, bin_numerator / bin_denominator )
        hist.SetBinError(binIdx,0.) #no error currently

    hist.SetLineWidth(2)
    hist.SetMarkerSize(2)
    return hist

# no bin_width and eff_lumi re-scale
def Hist_ValueAssignment(pETAbin,jETAbin, ptBINNING, fitVALUES, effSOURCES= {}):
    histname = 'h_historicalCrossSection_%d_%d' % (pETAbin,jETAbin)
    hist = ROOT.TH1F( histname, '#gamma+jet cross section', len(ptBINNING)-1, ptBINNING )

    hist.GetXaxis().SetTitle('E^{#gamma}_{T} (GeV)')
    hist.GetYaxis().SetTitle('d^{3} #sigma / dE^{#gamma}_{T} dy^{#gamma} dy^{jet} [pb/GeV]')
    for binIdx in range(1,hist.GetNbinsX()+1):
        pPtBin = binIdx-1

        fitvalue, fiterror = BinValue(pETAbin,jETAbin,pPtBin, fitVALUES)
        bin_numerator = fitvalue


        hist.SetBinContent( binIdx, fitvalue )
        hist.SetBinError(binIdx, fiterror)

    hist.SetLineWidth(2)
    hist.SetMarkerSize(2)
    return hist
if __name__ == '__main__':
    import sys
    inputDATfile = sys.argv[1]

    refXSfile = inputDATfile
    # no ptbin etabin re-weight
    #refXSfile='/wk_cms/ltsai/CMSSW/Run3Winter22/CMSSW_12_2_4/src/xPhoton/macros/step5.CompareYields/data/2015_cross_section_gjet_fromSMP16003.dat'
    #refXSfile='/home/ltsai/ReceivedFile/GJet/latestsample/MG5_generateResult/sm_no_b_mass/out_mergeMG5Result.dat'
    #refXSfile='/home/ltsai/ReceivedFile/out_mergeMG5Result.dat'
    #refXSfile='/home/ltsai/ReceivedFile/NLO_loop_sm_no_b_mass_CT14nnlo/out_mergeMG5Result.dat'
    #refXSfile='/home/ltsai/ReceivedFile/NLO_loop_sm_no_b_mass_NNPDF3p1nnlo/out_mergeMG5Result.dat'
    refvalues = ReadEvt_FitResult(refXSfile)
    #inputfile='16yield_newformat.dat'
    #XS_datafile='/wk_cms/ltsai/CMSSW/Run3Winter22/CMSSW_12_2_4/src/xPhoton/macros/step5.CompareYields/data/2015_cross_section_gjet_fromSMP16003.dat'

    ''' only for 2016 ReReco data '''
    XS_datafile='/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/deepcsv_CUT_NOCUT/2016ReReco.data.yield.dat'
    effsource = {}
    jetselectfile = '/wk_cms/ltsai/github/xPhoton/macros/step2.1.efficienciesCalc/UL2016PreVFP/dat_jetSelections.dat'
    signalregfile = '/wk_cms/ltsai/github/xPhoton/macros/step2.1.efficienciesCalc/UL2016PreVFP/dat_phoControlReg.dat'
    phoselectfile = '/wk_cms/ltsai/github/xPhoton/macros/step2.1.efficienciesCalc/UL2016PreVFP/dat_preselectionEfficiency.dat'
    ''' only for 2016 ReReco data '''
    cmpvalues = ReadEvt_FitResult(XS_datafile)

    effsource['presel'] = ReadEvt_Eff(phoselectfile)
    effsource['sigreg'] = ReadEvt_Eff(signalregfile)
    effsource['jetsel'] = ReadEvt_Eff(jetselectfile)

    dataEra = '2016ReReco'
    pt_binning = array( 'd', PhoPtBinning(dataEra) )
    for idx, val in enumerate(pt_binning): print('- bin %2d : %.0f'%(idx,val) )

    canv = NewCanvas(False)

    cmphists = []
    refhists = []
    markers = [34,33,28,27]
    #colors = [2,45,8,29]
    cmpcolors = 1
    refcolors = 2
    histIDX = 0
    for pEtaBin in range(2):
        for jEtaBin in range(2):
            canv.cd(1)
            #cmphist = Hist_ValueAssignment(pEtaBin,jEtaBin, pt_binning, cmpvalues)
            cmphist = Hist_PhotonCrossSection(pEtaBin,jEtaBin, pt_binning, cmpvalues, effsource)

            cmphist.SetMarkerStyle(markers[histIDX])
            #cmphist.SetLineColor(colors[histIDX])
            cmphist.SetLineColor(cmpcolors)
            cmphist.SetMarkerColor(cmpcolors)
            cmphists.append(cmphist)


            refhist = Hist_ValueAssignment(pEtaBin,jEtaBin, pt_binning, refvalues)

            refhist.SetMarkerStyle(markers[histIDX])
            #refhist.SetLineColor(colors[histIDX])
            refhist.SetLineColor(refcolors)
            refhist.SetMarkerColor(refcolors)
            refhists.append(refhist)


            histIDX += 1
    canv.cd(1)
    for hist in cmphists:
        hist.Draw('EP SAME')
    leg = MyLegend(cmphists)
    leg.Draw()
    canv.SaveAs('h_photonCrossSection.pdf')



    h = cmphists[-1]
    ymin = h.GetMinimum() if h.GetMinimum() != 0 else 1e-6
    ymax = h.GetMaximum()


    zoomfactor = 1.
    for cmphist, refhist in zip(reversed(cmphists),reversed(refhists) ):
        cmphist.Scale(zoomfactor)
        cmphist.SetMaximum( ymax*1e12 )
        cmphist.SetMinimum( ymin*0.5 )
        refhist.Scale(zoomfactor)
        zoomfactor *= 100.
    h.Draw('EP')
    for cmphist,refhist in zip(cmphists,refhists):
        refhist.Draw('EP SAME')
        cmphist.Draw('EP SAME')
    leg_sep = MyLegend_Sep(cmphists,refhists)
    leg_sep.Draw()
    canv.SaveAs('h_photonCrossSection_sep.pdf')

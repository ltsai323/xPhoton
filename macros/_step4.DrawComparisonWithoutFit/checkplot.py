#!/usr/bin/env python3

import ROOT

g_canv=ROOT.TCanvas('c1','',1000,1000)

def checkplot(ifile:ROOT.TFile):
    varname = 'BDT'
    print(f'bin_0_0_13/{varname}_data_dataSideband_norm')
    h_datasideband = ifile.Get(f'bin_0_0_13/{varname}_data_dataSideband_norm')

    h_data = ifile.Get(f'bin_0_0_13/{varname}_data_signalRegion')
    num_data = h_data.Integral()

    # no c-tagging reweight.
    h_oldL = ifile.Get(f'bin_0_0_13/{varname}_gjet_signalRegion_shapeUncUp')

    num_oldL = h_oldL.Integral()
    bkgnum_old = num_data - num_oldL
    print(f'makeplot() : Invalid sideband yield {bkgnum_old:.2e}. data({num_data:.2e}), L({num_oldL:.2e})')
    rrratio = num_oldL / num_data
    print(f'makeplot() : data / MCs = {rrratio:.3f}')

def testplot(ifile:ROOT.TFile, varname:str):
    class OutputStruct:
        stack_orig = None
        stack_weig = None
    print(f'overall_binning/{varname}_data_dataSideband_norm')
    h_datasideband = ifile.Get(f'overall_binning/{varname}_data_dataSideband_norm')

    h_data = ifile.Get(f'overall_binning/{varname}_data_signalRegion')
    num_data = h_data.Integral()

    # no c-tagging reweight.
    h_oldL = ifile.Get(f'overall_binning/{varname}_gjet_GJetsL_signalRegion_original')
    h_oldC = ifile.Get(f'overall_binning/{varname}_gjet_GJetsC_signalRegion_original')
    h_oldB = ifile.Get(f'overall_binning/{varname}_gjet_GJetsB_signalRegion_original')


    num_oldL = h_oldL.Integral()
    num_oldC = h_oldC.Integral()
    num_oldB = h_oldB.Integral()

    bkgnum_old = num_data - num_oldL - num_oldC - num_oldB
    print(f'makeplot() : Invalid sideband yield {bkgnum_old:.2e}. data({num_data:.2e}), L({num_oldL:.2e}), C({num_oldC:.2e}), B({num_oldB:.2e})')
    rrratio = (num_oldL+num_oldC+num_oldB) / num_data
    print(f'makeplot() : data / MCs = {rrratio:.3f}')

    #if bkgnum_old<0.: raise IOError(f'makeplot() : Invalid sideband yield {bkgnum_old:.2e}. data({num_data:.2e}), L({num_oldL:.2e}), C({num_oldC:.2e}), B({num_oldB:.2e})')

    #h_datasideband_old = h_datasideband.Clone(h_datasideband.GetName()+'_original')
    #h_datasideband_old.Scale(bkgnum_old)

    h_oldL.SetFillColor(41)
    h_oldC.SetFillColor(30)
    h_oldB.SetFillColor(46)
    h_oldL.SetFillStyle(1001)
    h_oldC.SetFillStyle(1001)
    h_oldB.SetFillStyle(1001)
    #h_datasideband_old.SetFillColor(14)
    stack_old = ROOT.THStack('stack_old','')
    #stack_old.Add(h_datasideband_old)
    stack_old.Add(h_oldL)
    stack_old.Add(h_oldC)
    stack_old.Add(h_oldB)
    g_canv.cd()

    h_data.SetMarkerSize(4)
    h_data.SetMarkerStyle(33)
    h_data.Draw("EP")
    h_oldL.Draw('hist SAME')
    h_data.Draw("EP SAME")
    g_canv.SaveAs('hi.png')
    return



    # c-tagging weighted hists
    h_newL = ifile.Get(f'{varname}_gjet_GJetsL_signalRegion_central')
    h_newC = ifile.Get(f'{varname}_gjet_GJetsC_signalRegion_central')
    h_newB = ifile.Get(f'{varname}_gjet_GJetsB_signalRegion_central')
def makeplot(ifile:ROOT.TFile, varname:str):
    class OutputStruct:
        stack_orig = None
        stack_weig = None
    print(f'overall_binning/{varname}_data_dataSideband_norm')
    h_datasideband = ifile.Get(f'overall_binning/{varname}_data_dataSideband_norm')

    h_data = ifile.Get(f'overall_binning/{varname}_data_signalRegion')
    num_data = h_data.Integral()

    # no c-tagging reweight.
    h_oldL = ifile.Get(f'overall_binning/{varname}_gjet_GJetsL_signalRegion_original')
    h_oldC = ifile.Get(f'overall_binning/{varname}_gjet_GJetsC_signalRegion_original')
    h_oldB = ifile.Get(f'overall_binning/{varname}_gjet_GJetsB_signalRegion_original')


    num_oldL = h_oldL.Integral()
    num_oldC = h_oldC.Integral()
    num_oldB = h_oldB.Integral()

    bkgnum_old = num_data - num_oldL - num_oldC - num_oldB
    print(f'makeplot() : Invalid sideband yield {bkgnum_old:.2e}. data({num_data:.2e}), L({num_oldL:.2e}), C({num_oldC:.2e}), B({num_oldB:.2e})')
    rrratio = (num_oldL+num_oldC+num_oldB) / num_data
    print(f'makeplot() : data / MCs = {rrratio:.3f}')
    exit(1)
    if bkgnum_old<0.: raise IOError(f'makeplot() : Invalid sideband yield {bkgnum_old:.2e}. data({num_data:.2e}), L({num_oldL:.2e}), C({num_oldC:.2e}), B({num_oldB:.2e})')

    h_datasideband_old = h_datasideband.Clone(h_datasideband.GetName()+'_original')
    h_datasideband_old.Scale(bkgnum_old)

    h_oldL.SetFillColor(41)
    h_oldC.SetFillColor(30)
    h_oldB.SetFillColor(46)
    h_datasideband_old.SetFillColor(14)
    stack_old = ROOT.THStack('stack_old','')
    stack_old.Add(h_datasideband_old)
    stack_old.Add(h_oldL)
    stack_old.Add(h_oldC)
    stack_old.Add(h_oldB)

    stack_old.Draw('nostack')
    h_data.Draw("EP SAME")
    g_canv.SaveAs('hi.png')



    return

    # c-tagging weighted hists
    h_newL = ifile.Get(f'{varname}_gjet_GJetsL_signalRegion_central')
    h_newC = ifile.Get(f'{varname}_gjet_GJetsC_signalRegion_central')
    h_newB = ifile.Get(f'{varname}_gjet_GJetsB_signalRegion_central')





if __name__ == '__main__':
    ifilename = 'makehisto.root'
    ifile = ROOT.TFile.Open(ifilename)

    #checkplot(ifile)
    testplot(ifile,'jettag0')

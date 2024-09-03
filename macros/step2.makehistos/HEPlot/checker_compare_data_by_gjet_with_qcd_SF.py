#!/usr/bin/env python3

import ROOT

debug_mode=False
def BUG(mesg):
    if debug_mode: print(f'bug@ {mesg}')
def info(mesg):
    print(f'i@ {mesg}')

def GetArgs_IOFile(argv):
    if len(argv) == 3:
        return (argv[1],argv[2])

    global debug_mode
    debug_mode = True
    BUG(f'[NoArgs] Debug mode activated')
    return ('makehisto.root','out.root')

def GetRatioGraph(hNUMERATOR, stackDENUMERATOR, outNAME) -> ROOT.TGraphAsymmErrors:
    stacked_components = stackDENUMERATOR.GetHists()
    h_denumerator = stacked_components.At(0).Clone('h_denominator')
    h_denumerator.Reset()
    for idx in range(stacked_components.GetSize()):
        h_denumerator.Add(stacked_components.At(idx))

    out_graph = ROOT.TGraphAsymmErrors()
    out_graph.Divide(hNUMERATOR, h_denumerator, 'pois')
    out_graph.SetName(outNAME)
    return out_graph
def GetMergedHist(inFILE:ROOT.TFile, folder:str, outNAME:str, histNAMEs:list) -> ROOT.TH1F:
    h_out = None
    for histname in histNAMEs:
        h = inFILE.Get(f'{folder}/{histname}')
        if h_out == None:
            h_out = h.Clone()
            h_out.SetName(outNAME)
            h_out.Reset()
        h_out.Add(h)
    return h_out



def GetImportantHistsWithNLOScaleFactorToQCD(histDICT:dict, constantSF:float = -1) -> list:
    ''' histDICT = {
            'data': 'datahist', 'gjet': 'gjethist', 'qcd': 'qcdhist',
            'o_stack': 'stackedhistname for output', 'o_ratio': 'ratio plot from TGraphAsymmErrors for output'
            }

        returned value: all ROOT object need to be saved
    '''
    hDATA = histDICT['data']
    hDATA.SetTitle('data')

    hGJET = histDICT['gjet']
    hGJET.SetTitle('gjet')
    hGJET.SetFillColor(46)
    hGJET.SetFillStyle(1001)
    hGJET.SetLineColor(0)
    hGJET.SetLineWidth(2)

    h_QCD = histDICT['qcd' ]
    h_QCD.SetFillColor(32)
    h_QCD.SetFillStyle(1001)
    h_QCD.SetLineColor(0)
    h_QCD.SetLineWidth(2)
    print(f'data {hDATA.Integral()} , gjet {hGJET.Integral()}, qcd {h_QCD.Integral()}.')

    if h_QCD.Integral() > 0:
        scale_factor_NLO = ( hDATA.Integral() - hGJET.Integral() )/h_QCD.Integral() if constantSF<0 else constantSF
        h_QCD.SetTitle(f'QCD with SF {scale_factor_NLO:.2f}')
        h_QCD.Scale(scale_factor_NLO)
    else:
        h_QCD.SetTitle(f'QCD failed to calculate SF')


    stackplot = ROOT.THStack(histDICT['o_stack'], 'stacked for simulation samples')
    stackplot.Add(hGJET)
    stackplot.Add(h_QCD)

    ratio_graph = GetRatioGraph(hDATA, stackplot, histDICT['o_ratio'])

    return [hDATA, hGJET, h_QCD, stackplot, ratio_graph]



def ExtractObject(inFILE, binningFOLDER, outFOLDER):
    folder = binningFOLDER
    info(f'[FolderAccessed] Successfully go to {folder}')
    h_data = GetMergedHist(inFILE, folder, 'jettag0_data'          , ['jettag0_data', ])
    h_gjet = GetMergedHist(inFILE, folder, 'jettag0_gjet_original' , [ 'jettag0_gjet_original', ] )
    h_qcd  = GetMergedHist(inFILE, folder, 'jettag0_QCD_original'  , [ 'jettag0_QCD_original', ] )

    hist_dict = { 'data': h_data, 'gjet': h_gjet, 'qcd':  h_qcd,
        'o_stack': 'jettag0_stacked_original', 'o_ratio': 'jettag0_ratio_original', }
    root_obj_list1 = GetImportantHistsWithNLOScaleFactorToQCD(hist_dict)


    h_data = GetMergedHist(inFILE, folder, 'jettag0_data'         , ['jettag0_data', ])
    h_gjet = GetMergedHist(inFILE, folder, 'jettag0_gjet_central' , [ 'jettag0_gjet_central', ] )
    h_qcd  = GetMergedHist(inFILE, folder, 'jettag0_QCD_central'  , [ 'jettag0_QCD_central', ] )

    hist_dict = { 'data': h_data, 'gjet': h_gjet, 'qcd':  h_qcd,
        'o_stack': 'jettag0_stacked_central', 'o_ratio': 'jettag0_ratio_central', }
    root_obj_list2 = GetImportantHistsWithNLOScaleFactorToQCD(hist_dict)


    outFOLDER.cd()
    for root_obj in root_obj_list1:
        BUG(f'[WriteOutput] root object name {root_obj.GetName()}')
        root_obj.Write()
    for root_obj in root_obj_list2:
        BUG(f'[WriteOutput] root object name {root_obj.GetName()}')
        root_obj.Write()
    outFOLDER.Write()

if __name__ == "__main__":
    import sys
    inFILE,outFILE = GetArgs_IOFile(sys.argv)

    in_file = ROOT.TFile.Open(inFILE)

    out_file = ROOT.TFile(outFILE, 'RECREATE')
    for jet_bin in range(2):
        for eta_bin in range(2):
            for pt_bin in range(22):
                binning_folder = f'bin_{jet_bin}_{eta_bin}_{pt_bin}'
                BUG(f'[AccessFolder] Try to access {binning_folder}')
                if binning_folder not in in_file.GetListOfKeys():
                    info(f'[FolderNotInROOTfile] folder "{ binning_folder }" does not in the ROOT file. Skip')
                    continue
                info(f'create folder "{ binning_folder }"')
                out_folder = out_file.mkdir(binning_folder)
                ExtractObject(in_file, binning_folder, out_folder)

    out_file.Close()

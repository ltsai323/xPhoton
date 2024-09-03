#!/usr/bin/env python3

import ROOT
MAX_HLTBIT=8

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
    return ('aa.root','out.root')

def GetImportantHists(inFILE, histFOLDER:str, detectorGEOMETRY:str) -> list:
    output_hists = {}

    output_hists['both'] = inFILE.Get(f'{histFOLDER}/{detectorGEOMETRY}_both')
    output_hists['base'] = inFILE.Get(f'{histFOLDER}/{detectorGEOMETRY}_base')
    n = f'{detectorGEOMETRY}_ratio'
    output_hists[n] = ROOT.TGraphAsymmErrors()
    output_hists[n].BayesDivide(output_hists['both'],output_hists['base'])
    output_hists[n].SetName(n)

    output_hists['both_f'] = inFILE.Get(f'{histFOLDER}/{detectorGEOMETRY}_both_Full')
    output_hists['base_f'] = inFILE.Get(f'{histFOLDER}/{detectorGEOMETRY}_base_Full')
    n = f'{detectorGEOMETRY}_ratio_Full'
    output_hists[n] = ROOT.TGraphAsymmErrors()
    output_hists[n].BayesDivide(output_hists['both_f'],output_hists['base_f'])
    output_hists[n].SetName(n)

    return output_hists



if __name__ == "__main__":
    import sys
    inFILE,outFILE = GetArgs_IOFile(sys.argv)

    in_file = ROOT.TFile.Open(inFILE)

    out_file = ROOT.TFile(outFILE, 'RECREATE')
    for hltbit in range(MAX_HLTBIT+1):
        folder = f'HLTbit{hltbit}'
        BUG(f'[AccessFolder] Try to access {folder}')
        if folder not in in_file.GetListOfKeys(): continue
        info(f'[FolderAccessed] Successfully go to {folder}')
        hists_barrel = GetImportantHists(in_file,folder,'barrel')
        hists_endcap = GetImportantHists(in_file,folder,'endcap')

        out_folder = out_file.mkdir(folder)
        out_folder.cd()
        for label,hist in hists_barrel.items():
            BUG(f'[WriteOutput] histogram {hist.GetName()}')
            hist.Write()
        for label,hist in hists_endcap.items():
            BUG(f'[WriteOutput] histogram {hist.GetName()}')
            hist.Write()
        out_folder.Write()

    out_file.Close()

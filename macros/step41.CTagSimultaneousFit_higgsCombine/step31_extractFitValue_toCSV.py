#!/usr/bin/env python3

import ROOT


class FitVar:
    def __init__(self,var):
        self.val = var.getVal()
        self.err = var.getError()
        self.errUp = var.getErrorHi()
        self.errDn = var.getErrorLo()
    def __str__(self):
        return f'val = {self.val}+-{self.err}. And errUp {self.errUp} / errDn {self.errDn}'

def GetFitResult(inFILE:str) -> dict:
    #inFILE = 'multidimfitTest.root'

    infile = ROOT.TFile.Open(inFILE)
    fitres = infile.Get('fit_mdf')
    var_dict = { v.GetName():v for v in  fitres.floatParsFinal() }
    infile.Close()
    #FitVar(var_dict['mu1'])
    #FitVar(var_dict['mu2'])
    #FitVar(var_dict['shapeUnc'])

    return { name:FitVar(var) for name,var in var_dict.items() }
def ShowFitResult(inFILE:str) -> None:
    fitres = GetFitResult(inFILE)
    for n,fitr in fitres.items():
        print(n,fitr)

def get_binnings(string) -> dict:
    parts = string.split('_')
    numbers = []
    for part in parts:
        if part.isdigit():
            numbers.append(int(part))
    return { 'pEtaBin': numbers[0], 'jEtaBin': numbers[1], 'pPtBin': numbers[2] }

def get_input_file( pETAbin, jETAbin, pPTbin, inFOLDER ):
    inputfile = f'{inFOLDER}/CTag_SimulFit_{pETAbin}_{jETAbin}_{pPTbin}/multidimfitTest.root'
    if os.path.exists(inputfile):
        return inputfile
    sys.stderr.write(f'[check.ctaggingVars-ERROR] bin_{pETAbin}_{jETAbin}_{pPTbin} failed to find "{inputfile}", skip it\n')
    return None

import csv
if __name__ == "__main__":
    #ShowFitResult('DeepCSV_gjetPythia_cutIdx4_mergeBin_5/CTag_SimulFit_0_0_14/multidimfitTest.root')
    #exit(1)

    import sys
    dataERA, inFOLDER = sys.argv[1:]
    fit_sig = []
    fit_bkg = []
    fit_shapeUnc = []
    fit_l = []
    fit_c = []
    fit_b = []
    fit_PUweight = []
    fit_Stat = []
    import os
    bdt_fit_dirs = [ inFOLDER+'/'+the_dir for the_dir in os.listdir(inFOLDER) if 'CTag_SimulFit' == the_dir[:len('CTag_SimulFit')] ]

    for res_dir in bdt_fit_dirs:
        binning = get_binnings(res_dir)
        pEtaBin = binning['pEtaBin']
        jEtaBin = binning['jEtaBin']
        pPtBin  = binning['pPtBin']

        fitres = GetFitResult( res_dir+'/multidimfitTest.root' )
        fill = lambda content, var: content.append({
                'pEtaBin': pEtaBin,
                'jEtaBin': jEtaBin,
                'pPtBin': pPtBin,
                'values': fitres[var].val,
                'errors': fitres[var].err,
                'errUp': fitres[var].errUp,
                'errDn': fitres[var].errDn,
                })
        fill(fit_l, 'mu1')
        fill(fit_c, 'mu2')
        fill(fit_b, 'mu3')
        fill(fit_PUweight, 'PUweight')
        fill(fit_Stat, 'Stat')

    def write_to_csv(newfilename, contents):
        if len(contents) == 0:
            raise IOError('nothing will recorded in '+newfilename)
        with open(newfilename,'w') as newfile:
            csvwritter = csv.DictWriter(newfile, fieldnames=contents[0].keys())
            csvwritter.writeheader()
            csvwritter.writerows(contents)
            print('[CSV Generated] '+newfilename)
    write_to_csv( f'{dataERA}.data.l.csv', fit_l )
    write_to_csv( f'{dataERA}.data.c.csv', fit_c )
    write_to_csv( f'{dataERA}.data.b.csv', fit_b )
    write_to_csv( f'{dataERA}.data.PUweight.csv', fit_PUweight )
    write_to_csv( f'{dataERA}.data.Stat.csv', fit_Stat )



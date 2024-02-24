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


import csv
if __name__ == "__main__":
    # ShowFitResult('BDTFit_0_0_14/multidimfitTest.root')
    # exit(1)
    fit_sig = []
    fit_bkg = []
    fit_shapeUnc = []
    import os
    bdt_fit_dirs = [ the_dir for the_dir in os.listdir() if 'BDTFit' == the_dir[:len('BDTFit')] ]
    bdt_fit_dirs.sort()
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
        fill(fit_sig, 'mu1')
        fill(fit_bkg, 'mu2')
        fill(fit_shapeUnc, 'shapeUnc')

    import sys
    tag = sys.argv[1]
    def write_to_csv(newfilename, contents):
        if len(contents) == 0:
            raise IOError('nothing will recorded in '+newfilename)
        with open(newfilename,'w') as newfile:
            csvwritter = csv.DictWriter(newfile, fieldnames=contents[0].keys())
            csvwritter.writeheader()
            csvwritter.writerows(contents)
            print('[CSV Generated] '+newfilename)
    write_to_csv( f'{tag}.data.yield.csv', fit_sig )
    write_to_csv( f'{tag}.data.bkg.csv', fit_bkg )
    write_to_csv( f'{tag}.data.shapeUnc.csv', fit_shapeUnc )



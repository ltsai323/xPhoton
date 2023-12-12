#!/usr/bin/env python3
import ROOT

printbug = False
def LOG(*args):
    if printbug:
        print('[check.ctaggingVars-LOG] ', *args)
def BUG(*args):
    if printbug:
        print('[check.ctaggingVars-BUGGING] ', *args)

def funcFRAG1_chi2_calc( hDATA, hSIGN):
    chi2 = 0.
    for ibin in range(1,hDATA.GetNbinsX()+1):
        bin_data_val = hDATA.GetBinContent(ibin)
        bin_data_err = hDATA.GetBinError(ibin)

        bin_sign_val = hSIGN.GetBinContent(ibin)
        bin_sign_err = hSIGN.GetBinError(ibin)
        #if bincont == 0 and binerro == 0:
        #    continue
        if bin_data_val < 1e-8: continue
        err2 = bin_data_err**2 + bin_sign_err**2
        val2 = (bin_data_val - bin_sign_val)**2
        chi2 += val2 / err2
    ndof = hDATA.GetNbinsX() - 1;
    return chi2 / ndof

def GetChi2(inFILE, folderNAME):
    data_obs = inFILE.Get(f'{folderNAME}/data_obs')
    totalFit = inFILE.Get(f'{folderNAME}/TotalProcs')

    return funcFRAG1_chi2_calc(data_obs,totalFit)


def FracCalc(*args):
    sum_up = sum(args)
    return ( v/sum_up for v in args )

def GetInputFile( pETAbin, jETAbin, pPTbin, inFOLDER ):
    ## only for test
    #inputfile = 'testregion/postfit.root'
    #return inputfile
    inputfile = f'{inFOLDER}/CTag_SimulFit_{pETAbin}_{jETAbin}_{pPTbin}/postfit.root'
    if os.path.exists(inputfile):
        return inputfile
    sys.stderr.write(f'[check.ctaggingVars-ERROR] bin_{pETAbin}_{jETAbin}_{pPTbin} failed to find "{inputfile}", skip it\n')
    return None

def GetInfo(pEtaBin,jEtaBin,pPtBin, inFOLDER, outputLIST):
    inputfile = GetInputFile( pEtaBin, jEtaBin, pPtBin, inFOLDER )
    if inputfile == None: return

    LOG(f'input file {inputfile}\n\n')




    inFile = ROOT.TFile.Open(inputfile)
    int_L = inFile.Get('cat_0_postfit/signal_L').Integral()
    int_C = inFile.Get('cat_0_postfit/signal_C').Integral()
    int_B = inFile.Get('cat_0_postfit/signal_B').Integral()
    frac_L, frac_C, frac_B = FracCalc(int_L,int_C,int_B)

    chi2_tag0 = GetChi2(inFile, 'cat_0_postfit')
    chi2_tag1 = GetChi2(inFile, 'cat_1_postfit')
    chi2_tag2 = GetChi2(inFile, 'cat_2_postfit')

    ## output
    outputLIST.append({
        'pEtaBin':    pEtaBin,
        'jEtaBin':    jEtaBin,
        'pPtBin':     pPtBin,

        'frac_L':     frac_L,
        'frac_C':     frac_C,
        'frac_B':     frac_B,

        'fit_yield_L':int_L,
        'fit_yield_C':int_C,
        'fit_yield_B':int_B,

        'chi2_jet0':  chi2_tag0,
        'chi2_jet1':  chi2_tag1,
        'chi2_jet2':  chi2_tag2,
        })
    inFile.Close()
    return

if __name__ == "__main__":
    import os
    import sys
    dataERA, inFOLDER = sys.argv[1:]

    from py_pt_ranges_definition import ptbin_ranges
    maxptbin = len( ptbin_ranges(dataERA) )
    csv_output = []
    for pEtaBin in range(2):
        for jEtaBin in range(2):
            for pPtBin in range(maxptbin):
                GetInfo(pEtaBin, jEtaBin, pPtBin, inFOLDER, csv_output)

    if len(csv_output) == 0: raise IOError('[step3_collect_postfit_info-ERROR] no any information found ')
    with open('UL2016.CTag_SimulFit.csv', 'w') as outFile:
        import csv
        csv_writer = csv.DictWriter(outFile, fieldnames = csv_output[0].keys())
        csv_writer.writeheader()
        csv_writer.writerows(csv_output)
        print("Here is your output: UL2016.CTag_SimulFit.csv")

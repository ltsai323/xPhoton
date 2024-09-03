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

def get_input_file( pETAbin, jETAbin, pPTbin, inFOLDER ):
    inputfile = f'{inFOLDER}/CTag_SimulFit_{pETAbin}_{jETAbin}_{pPTbin}/multidimfitTest.root'
    if os.path.exists(inputfile):
        return inputfile
    sys.stderr.write(f'[check.ctaggingVars-ERROR] bin_{pETAbin}_{jETAbin}_{pPTbin} failed to find "{inputfile}", skip it\n')
    return None

import uncertainties as unc

def get_fit_result(inFILE):
    fit_result = inFILE.Get('fit_mdf')

    final_params = fit_result.floatParsFinal()

    # Loop through the parameters and print their names and values
    readout = {}
    for i in range(final_params.getSize()):
        param = final_params.at(i)
        readout[param.GetName()] = unc.ufloat(param.getVal(),param.getError())
    return readout
    ### some feature in RooFitResult
    '''
    fit_result.numInvalidNLL()
    fit_result.numStatusHistory()
    fit_result.status()
    fit_result.minNll() # the minized FCN value.
    fit_result.covarianceMatrix().Print()
    '''
def GetInfo_(pEtaBin,jEtaBin,pPtBin, inFOLDER, outputLIST):
    inputfile = get_input_file( pEtaBin, jEtaBin, pPtBin, inFOLDER )
    if inputfile == None: return

    LOG(f'input file {inputfile}\n\n')
    inFile = ROOT.TFile.Open(inputfile)
    fitres = get_fit_result(inFile)
    fitL = fitres['mu1']
    fitC = fitres['mu2']
    fitB = fitres['mu3']
    fitUncPU = fitres['PUweight']
    fitUncStat = fitres['Stat']

    int_L = fitL.nominal_value
    int_C = fitC.nominal_value
    int_B = fitB.nominal_value

    frac_L, frac_C, frac_B = FracCalc(int_L,int_C,int_B)

    chi2_tag0 = 0
    chi2_tag1 = 0
    chi2_tag2 = 0

    ## output
    outputLIST.append({
        'pEtaBin':    pEtaBin,
        'jEtaBin':    jEtaBin,
        'pPtBin':     pPtBin,

        'frac_L':     frac_L,
        'frac_C':     frac_C,
        'frac_B':     frac_B,

        'fit_yield_L':fitL.nominal_value,
        'fit_yield_C':fitC.nominal_value,
        'fit_yield_B':fitB.nominal_value,

        'fit_error_L':fitL.std_dev,
        'fit_error_C':fitC.std_dev,
        'fit_error_B':fitB.std_dev,

        'chi2_jet0':  chi2_tag0,
        'chi2_jet1':  chi2_tag1,
        'chi2_jet2':  chi2_tag2,
        })
    inFile.Close()
    return
def GetInfo(pEtaBin,jEtaBin,pPtBin, inFOLDER, outputLIST):
    inputfile = GetInputFile( pEtaBin, jEtaBin, pPtBin, inFOLDER )
    if inputfile == None: return

    LOG(f'input file {inputfile}\n\n')




    inFile = ROOT.TFile.Open(inputfile)
    int_L = inFile.Get('cat_0_postfit/signal_L').Integral()
    int_C = inFile.Get('cat_0_postfit/signal_C').Integral()
    int_B = inFile.Get('cat_0_postfit/signal_B').Integral()
    frac_L, frac_C, frac_B = FracCalc(int_L,int_C,int_B)

    #chi2_tag0 = GetChi2(inFile, 'cat_0_postfit')
    #chi2_tag1 = GetChi2(inFile, 'cat_1_postfit')
    #chi2_tag2 = GetChi2(inFile, 'cat_2_postfit')
    chi2_tag0 = 0
    chi2_tag1 = 0
    chi2_tag2 = 0

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

    from py_pt_ranges_definition import PhoPtBinning
    maxptbin = len( PhoPtBinning(dataERA) )
    csv_output = []
    for pEtaBin in range(2):
        for jEtaBin in range(2):
            for pPtBin in range(maxptbin):
                #GetInfo(pEtaBin, jEtaBin, pPtBin, inFOLDER, csv_output)
                GetInfo_(pEtaBin, jEtaBin, pPtBin, inFOLDER, csv_output)

    if len(csv_output) == 0: raise IOError('[step3_collect_postfit_info-ERROR] no any information found ')
    with open('UL2016.CTag_SimulFit.csv', 'w') as outFile:
        import csv
        csv_writer = csv.DictWriter(outFile, fieldnames = csv_output[0].keys())
        csv_writer.writeheader()
        csv_writer.writerows(csv_output)
        print("Here is your output: UL2016.CTag_SimulFit.csv")

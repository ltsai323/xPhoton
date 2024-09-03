#!/usr/bin/env python3
import os
from pathlib import Path

import tools.rFitResult as rFitResult

def info(mesg):
    print(f'i@ {mesg}')
def BUG(mesg):
    print(f'bug@ {mesg}')
def GetArgs_IOFile(argv):
    try:
        folder,pETAbin,jETAbin,pPTbin, getDATAdetail = argv[1:]
        info(f'args : inFOLDER "{ folder }", pETAbin: "{ pETAbin }", jETAbin: "{ jETAbin }", pPTbin: "{ pPTbin }", getDATAdetail: "{ getDATAdetail }"')
        return (folder, int(pETAbin), int(jETAbin), int(pPTbin), getDATAdetail)

    except:
        print('''\n\n\n Extract C/B ratio and (C+B) / (L+C+B) ratio from fitted result.
                Input arg1: input folder containing CTag_SimulFit_*_*_*/multidimfitTest.root
                Input arg2: pho Eta bin [0,1]
                Input arg3: jet Eta bin [0,1]
                Input arg4: pho Pt  bin [0,N]
                Input arg5: path to getdatadetail.txt
                \n\n''')
        print(f''' current input args : "{ [ f'arg{idx+1}={val}' for idx, val in enumerate(argv[1:]) ] }" ''')
def PreviousMultiDimFit( inFOLDER, pETAbin, jETAbin, pPTbin ):
    prev_pPTbin = pPTbin - 1
    fullname = f"{inFOLDER}/CTag_SimulFit_{pETAbin}_{jETAbin}_{prev_pPTbin}/multidimfitTest.root"
    info(f'[AccessingROOTfile] Calculated path to multidimfitTest.root is "{ fullname }"')
    p = Path(fullname)
    if p.is_file():
        return fullname
    else:
        info(f'-- [FILE_NOT_FOUND] The file is invalid, use default value for fitting...')
        return None
def GetDataEntries(pETAbin,jETAbin,pPTbin,getDATAdetail) -> int:
    binning = f'{pETAbin},{jETAbin},{pPTbin}'
    len_bin = len(binning)
    with open(getDATAdetail, 'r') as fIN:
        for line in fIN.readlines():
            if line[:len_bin] != binning: continue
            entries = line.split(',')[3]
            return int(entries)



class RatioResult:
    def __init__(self, ratioCB, ratioHAD, theDESC):
        self.ratio_cb = ratioCB
        self.ratio_had = ratioHAD
        self.desc = theDESC

''' memo
 mu1: L yield
 mu2: C yield
 mu3: B yield
'''
def GetCBRatio(inFILE:str) -> float:
    result = rFitResult.GetFitResult(infile)
    yieldC = result['mu2'].val
    yieldB = result['mu3'].val
    return yieldC / yieldB
def GetHadronRatio(inFILE:str) -> float:
    result = rFitResult.GetFitResult(infile)
    yieldL = result['mu1'].val
    yieldC = result['mu2'].val
    yieldB = result['mu3'].val
    BUG(f'[Got info] mu1:"{ yieldL }", mu2:"{ yieldC }", mu3:"{ yieldB }"')
    total = yieldL + yieldC + yieldB
    yieldH = yieldC + yieldB
    return yieldH / total




def GetRatiosFromInputFile(inFILE) -> RatioResult:
    DEFAULT_CB_RATIO = 5.0
    DEFAULT_HADRON_RATIO = 0.2

    if infile is None:
        ratio_cb = DEFAULT_CB_RATIO
        ratio_had= DEFAULT_HADRON_RATIO
        info(f'[DefaultRatio] Use default values: ratio_cb="{ ratio_cb }", ratio_had="{ ratio_had }"')
        desc = "DefaultValue"
    else:
        ratio_cb = GetCBRatio(infile)
        ratio_had= GetHadronRatio(infile)
        info(f'[CalculatedRatio] Use previous values: ratio_cb="{ ratio_cb }", ratio_had="{ ratio_had }"')
        desc = "CalculatedValue"
    return RatioResult(ratio_cb, ratio_had, desc)

FIT_RANGE = 0.4 # fit with number range in initValue +- dataEntries * 40%
def get_full_range(initVAL, totVAL, desc):
    if desc == "DefaultValue":
        return (initVAL, 0., totVAL)
    if desc == "CalculatedValue":
        val_range = totVAL * FIT_RANGE
        lower_val = initVAL - val_range if initVAL > val_range else 0.
        upper_val = initVAL + val_range if initVAL+val_range < totVAL else totVAL
        return (initVAL, lower_val, upper_val)
    raise IOError(f'[InvalidInput] Input desc "{ desc }" is invalid')


def GetLightValues(data_entries, ratioRES):
    init_val = data_entries * (1.-ratioRES.ratio_had)
    return get_full_range(init_val, data_entries, ratioRES.desc)
def GetCharmValues(data_entries, ratioRES):
    init_val = data_entries * ratioRES.ratio_had * ratioRES.ratio_cb/(ratioRES.ratio_cb+1.)
    return get_full_range(init_val, data_entries, ratioRES.desc)
def GetBeautyValues(data_entries, ratioRES):
    init_val = data_entries * ratioRES.ratio_had * 1./(ratioRES.ratio_cb+1.)
    return get_full_range(init_val, data_entries, ratioRES.desc)

def str_converter(v):
    #return f'{v:.2f}'
    ''' input a tuple from GetBLAHValues() function '''
    ''' get a "initVAL,lowerRANGE,upperRANGE" string '''
    return f'{v[0]:.2f},{v[1]:.2f},{v[2]:.2f}'

if __name__ == "__main__":
    import sys
    # python3 frag21_extract_initValues.py ../$outDIR  $pEtaBin $jEtaBin $pPtBin $inputdatadetail
    # python3 frag21_extract_initValues.py  DeepCSV_gjetPythia_cutIdx3_mergeBin_1 0 0 3 DeepCSV_gjetPythia_cutIdx3_mergeBin_1/getdatadetail.csv
    inFOLDER, pETAbin, jETAbin, pPTbin, getDATAdetail = GetArgs_IOFile(sys.argv)

    infile = PreviousMultiDimFit(inFOLDER, pETAbin, jETAbin, pPTbin)
    ratio_result = GetRatiosFromInputFile(infile)

    data_entries = GetDataEntries(pETAbin, jETAbin, pPTbin, getDATAdetail)
    init_l = GetLightValues(data_entries, ratio_result)
    init_c = GetCharmValues(data_entries, ratio_result)
    init_b = GetBeautyValues(data_entries, ratio_result)

    info(f'[Result] init_l:"{ init_l }", int_c:"{ init_c }", init_b:"{ init_b }", entries:"{ data_entries }", desc:"{ ratio_result.desc }"')


    out_filename = 'calculated_init_value.txt'
    with open(out_filename, 'w') as f_out:
        rec_l = str_converter(init_l)
        rec_c = str_converter(init_c)
        rec_b = str_converter(init_b)

        f_out.write(f'{rec_l} {rec_c} {rec_b} {data_entries} {ratio_result.desc}\n')
    info(f'[Outfile] Output file put to "{ out_filename }"')

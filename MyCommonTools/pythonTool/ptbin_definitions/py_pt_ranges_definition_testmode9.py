#!/usr/bin/env python3

import py_pt_ranges_definition_testmode_base


testmode = 9
def PhoPtBinning(dataERA):
    return py_pt_ranges_definition_testmode_base.PhoPtBinning(dataERA,testmode)
def hltbin_ptbin_definition(dataERA):
    return py_pt_ranges_definition_testmode_base.hltbin_ptbin_definition(dataERA, testmode)
def FindEffLumi(dataERA,ptBIN):
    return py_pt_ranges_definition_testmode_base.FindEffLumi(dataERA,ptBIN, testmode)


if __name__ == "__main__":
    currentDataEra = 'UL2016PreVFP'
    def get_pt_region(arr,idx):
        l_val = str(arr[idx])
        r_val = str(arr[idx+1]) if idx+1 < len(arr) else 'inf'
        return f'[{l_val},{r_val}]'
    pho_pt_def = PhoPtBinning(currentDataEra)
    hlt_bining = hltbin_ptbin_definition(currentDataEra)
    for idx,hltbit in enumerate(hlt_bining):
        print(f'@pt bin {idx:2d} : {get_pt_region(pho_pt_def,idx)} \t with hlt bin {hltbit} and eff lumi {FindEffLumi(currentDataEra,idx)}')

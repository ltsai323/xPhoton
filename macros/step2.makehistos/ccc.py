#!/usr/bin/env python3

import ROOT

def GetHistInfo(fileNAME, histNAME):
    f = ROOT.TFile.Open(fileNAME)
    h = f.Get(histNAME)
    print('file opened')
    for ibin in range(h.GetNbinsX()):
        yield (ibin+1,h.GetBinContent(ibin+1))

if __name__ == "__main__":
    #file1 = 'processed_file_new/makehisto_data.root'
    #file2 = 'processed_file_ref/makehisto_data.root'
    file1 = 'makehisto_data_new.root'
    file2 = 'makehisto_data_ref.root'
    histNAME = 'bin_0_0_8/BDT_data_signalRegion'
    for value1,value2 in zip( GetHistInfo(file1,histNAME),GetHistInfo(file2,histNAME) ):
        #if value1[1] != value2[1]: raise ValueError(f'@bin%d, new value is not the same as ref. ( %.5e / %.5e )'%(value1[0],value1[1],value2[1]))
        print(f'@bin%d, new value is not the same as ref. ( %.5e / %.5e )'%(value1[0],value1[1],value2[1]))

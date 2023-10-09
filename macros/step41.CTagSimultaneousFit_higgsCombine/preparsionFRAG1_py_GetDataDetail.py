#!/usr/bin/env python3

import ROOT
def PrintHelp(mesg):
    print('''
            --------------- input arguments ----------------
            1. input data era: 2016ReReco,UL2017,UL2018, UL2016PreVFP, UL2016PostVFP
            2. input directory name containing makehisto.root and UL2016PreVFP.data.bkg.dat

            mesg:
              {}
            ------------------------------------------------
            '''.format(mesg))
    exit(1)
showdetail = False
def BUG(*args):
    if showdetail:
        print('[py_GetDataDetail-BUG]', *args)
def LOG(*args):
    print('[py_GetDataDetail-LOG]', *args)
from py_pt_ranges_definition import ptbin_ranges

def GetPtRange(ptBIN,dataERA):
    pt_bin = int(ptBIN)
    pt_def = list(ptbin_ranges(dataERA))
    if pt_bin+1 == len(pt_def):
        return '%d<P_{T#gamma}<Inf'%(pt_def[pt_bin])
    return '%d<P_{T#gamma}<%d'%(pt_def[pt_bin],pt_def[pt_bin+1])
def GetEtaRange(etaBIN,iNAME):
    etaBin = int(etaBIN)
    if etaBin == 0: return '|#eta_{%s}|<1.4442'%iNAME
    if etaBin == 1: return '1.566<|#eta_{%s}|<2.5'%iNAME
    return ''

def GetDataEntries(ifilename,pETAbin,jETAbin,pPTbin):
    if not ifile.Get('bin_%s_%s_%s'%(pETAbin,jETAbin,pPTbin)):
        raise ValueError(
                '-- Error -- GetDataDetail.py : No Bin %s_%s_%s found in %s' %
                (pETAbin,jETAbin,pPTbin,ifilename) )
    hdata=ifile.Get('bin_%s_%s_%s/BDT_data_signalRegion'%(pETAbin,jETAbin,pPTbin))
    hgjet=ifile.Get('bin_%s_%s_%s/BDT_gjet_signalRegion'%(pETAbin,jETAbin,pPTbin))
    BUG(f'input file {ifile.GetName()}')
    BUG(f'{GetDataEntries.__name__}, data name : ','bin_%s_%s_%s/BDT_data_signalRegion'%(pETAbin,jETAbin,pPTbin))
    BUG(f'{GetDataEntries.__name__}, data name : ','bin_%s_%s_%s/BDT_gjet_signalRegion'%(pETAbin,jETAbin,pPTbin))

    dataEntries = hdata.GetEntries()
    if dataEntries        < 1: raise ValueError("-- Error -- GetDataDetail.py : At Bin %s_%s_%s: Nothing in data."%(pEtaBin,jEtaBin,pPtBin))
    if hgjet.GetEntries() < 1: raise ValueError("-- Error -- GetDataDetail.py : At Bin %s_%s_%s: Nothing in signal MC."%(pEtaBin,jEtaBin,pPtBin))
    return int(dataEntries) + 1

def InValidBin(inFILE:ROOT, pETAbin, jETAbin, pPTbin):
    if not inFILE.Get(f'bin_{pETAbin}_{jETAbin}_{pPTbin}'):
        return True
    return False

def joIN(*argv):
    return ':'.join( [str(val) for val in argv] ) + '\n'

if __name__ == "__main__":
    import os
    dat_file_name = 'UL2016PreVFP.data.bkg.dat'
    try:
        dataEra, inFOLDER= os.sys.argv[1:]
        inROOTfile = f'{inFOLDER}/makehisto.root'
        inDATbkgYIELD = f'{inFOLDER}/{dat_file_name}'
        if not os.path.exists(inROOTfile):
            raise IOError(f'input folder {inFOLDER} does not contain makehisto.root')
        if not os.path.exists(inDATbkgYIELD):
            raise IOError(f'input folder {inFOLDER} does not contain {dat_file_name}')

    except ValueError as vErr:
        PrintHelp(vErr)
    LOG(f'Using {inROOTfile}')
    LOG(f'Using {inDATbkgYIELD}')

    ### load bkg dat yield
    from DATReadingTools import ReadEvt_FitResult, ReadEvt_Eff, BinValue
    fit_bkgs = ReadEvt_FitResult(inDATbkgYIELD)

    ### load histogram
    ifile = ROOT.TFile.Open(inROOTfile)


    csv_output = []
    maxptbin = len( ptbin_ranges(dataEra) )
    for pEtaBin in range(2):
        for jEtaBin in range(2):
            for pPtBin in range(maxptbin):
                BUG(f'step1_py_GetDataDetail.py at bin {pEtaBin}_{jEtaBin}_{pPtBin}')
                try:
                    if InValidBin(ifile, pEtaBin, jEtaBin, pPtBin):
                        raise ValueError(f'folder bin_{pEtaBin}_{jEtaBin}_{pPtBin} does not exist in root file: {ifile}')
                    dataEntries = GetDataEntries(ifile, pEtaBin,jEtaBin,pPtBin)
                    fake_value, fake_error = BinValue(pEtaBin,jEtaBin,pPtBin, fit_bkgs)
                    bkgEntries = round(fake_value,2)
                    sigEntries = dataEntries - fake_value
                    lInit = int(sigEntries * 0.85)
                    cInit = int(sigEntries * 0.10)
                    bInit = int(sigEntries * 0.05)


                    pptRange = GetPtRange(pPtBin,dataEra)
                    petaRange = GetEtaRange(pEtaBin,'#gamma')
                    jetaRange = GetEtaRange(jEtaBin,'jet')

                    csv_output.append( {
                            'pEtaBin':pEtaBin,
                            'jEtaBin':jEtaBin,
                            'pPtBin':pPtBin,
                            'dataEntries':dataEntries,
                            'lInit':lInit,
                            'cInit':cInit,
                            'bInit':bInit,
                            'fitDiJet':bkgEntries,
                            'pEtaRange':petaRange,
                            'jEtaRange':jetaRange,
                            'pPtRange':pptRange,
                            'inFile':inROOTfile,
                        } )
                except ValueError as msg:
                    print(msg)
                    print(f'--- skip bin {pEtaBin}_{jEtaBin}_{pPtBin} ---')

    if len(csv_output) == 0:
        raise IOError('nothing recorded. abort...')
    with open('getdatadetail.csv','w', newline='') as newfile:
        import csv
        csv_writer = csv.DictWriter(newfile, fieldnames = csv_output[0].keys())
        csv_writer.writeheader()
        csv_writer.writerows(csv_output)
        print("Here is your output: getdatadetail.csv")

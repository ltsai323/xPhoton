#!/usr/bin/env python3

def PrintHelp(mesg):
    print('''
            --------------- input arguments ----------------
            1. input data era: 2016ReReco,UL2017,UL2018, UL2016
            2. input step2.root file name

            mesg:
              {}
            ------------------------------------------------
            '''.format(mesg))
    exit(1)
from py_pt_ranges_definition import pt_ranges_test_for_merge_bin as ptbin_ranges
#def ptbin_ranges(dataERA):
#    # comes from step2.makehisto ptbin_ranges()
#    if dataERA == '2016ReReco' or dataERA == 'UL2016':
#        return (25,34,40,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000)
#    raise ValueError('data era %s has not been supported yet.'%dataERA)
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
    hdata=ifile.Get('bin_%s_%s_%s/BDT_data_signalRegion'%(pETAbin,jETAbin,pPTbin))
    hgjet=ifile.Get('bin_%s_%s_%s/BDT_gjet_signalRegion'%(pETAbin,jETAbin,pPTbin))

    dataEntries = hdata.GetEntries()
    if dataEntries        < 1: raise ValueError("-- Error -- GetDataDetail.py : At Bin %s_%s_%s: Nothing in data."%(pEtaBin,jEtaBin,pPtBin))
    if hgjet.GetEntries() < 1: raise ValueError("-- Error -- GetDataDetail.py : At Bin %s_%s_%s: Nothing in signal MC."%(pEtaBin,jEtaBin,pPtBin))
    return int(dataEntries) + 1


def joIN(*argv):
    return ':'.join( [str(val) for val in argv] ) + '\n'

if __name__ == "__main__":
    import os
    try:
        # all input as string
        dataEra, ifilename = os.sys.argv[1:]
        if 'root' not in ifilename: raise ValueError("input filename is not a root file -- "+ifilename)
    except ValueError as vErr:
        PrintHelp(vErr)

    import ROOT
    ifile = ROOT.TFile.Open(ifilename)


    with open('getdatadetail.txt','w') as ofile:
        ofile.write('pEtaBin:jEtaBin:pPtBin:dataEntries:sigInit:bkgInit:pEtaRange:jEtaRange:pPtRange\n')
        for pEtaBin in range(2):
            for jEtaBin in range(2):
                #for pPtBin in range(21): # for old 2016 binning
                for pPtBin in range(16): # for merge bin test
                    try:
                        dataEntries = GetDataEntries(ifile, pEtaBin,jEtaBin,pPtBin)
                        sigEntries = int( float(dataEntries)*0.7 )+1
                        bkgEntries = int( float(dataEntries)*0.3 )+1

                        pptRange = GetPtRange(pPtBin,dataEra)
                        petaRange = GetEtaRange(pEtaBin,'#gamma')
                        jetaRange = GetEtaRange(jEtaBin,'jet')

                        ofile.write(joIN(pEtaBin,jEtaBin,pPtBin,dataEntries,sigEntries,bkgEntries,petaRange,jetaRange,pptRange))
                    except ValueError as msg:
                        print(msg)
                        print('--- skip this entry ---')
        print("Here is your output: getdatadetail.txt")


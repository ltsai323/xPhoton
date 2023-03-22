#!/usr/bin/env python3

def PrintHelp(mesg):
    print('''
            --------------- input arguments ----------------
            1. pEtaBin: 0,1
            2. jEtaBin: 0,1,2
            3. pPtbin: 0~20
            4. input data era: 2016ReReco,UL2017,UL2018, UL2016
            5. input step2.root file name

            mesg:
              {}
            ------------------------------------------------
            '''.format(mesg))
    exit(1)
def ptbin_ranges(dataERA):
    # comes from step2.makehisto ptbin_ranges()
    if dataERA == '2016ReReco' or dataERA == 'UL2016':
        return (25,34,40,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000) # size = 16. ptbin = [0,15]
    raise ValueError('data era %s has not been supported yet.'%dataERA)
def GetPtRange(ptBIN,dataERA):
    pt_bin = int(ptBIN)
    pt_def = list(ptbin_ranges(dataERA))
    return '%d<P_{T#gamma}<%d'%(pt_def[pt_bin],pt_def[pt_bin+1])
def GetEtaRange(etaBIN,iNAME):
    etaBin = int(etaBIN)
    if etaBin == 0: return '|#eta_{%s}|<1.4442'%iNAME
    if etaBin == 1: return '1.566<|#eta_{%s}|<2.5'%iNAME
    return ''

def GetDataEntries(ifilename,pETAbin,jETAbin,pPTbin):
    import ROOT
    ifile=ROOT.TFile.Open(ifilename)
    hdata=ifile.Get('bin_%s_%s_%s/BDT_data_signalRegion'%(pETAbin,jETAbin,pPTbin))
    hgjet=ifile.Get('bin_%s_%s_%s/BDT_gjet_signalRegion'%(pETAbin,jETAbin,pPTbin))

    dataEntries = hdata.GetEntries()
    if dataEntries        < 1: raise ValueError("-- Error -- GetDataDetail.py : At Bin %s_%s_%s: Nothing in data."%(pEtaBin,jEtaBin,pPtBin))
    if hgjet.GetEntries() < 1: raise ValueError("-- Error -- GetDataDetail.py : At Bin %s_%s_%s: Nothing in signal MC."%(pEtaBin,jEtaBin,pPtBin))
    return int(dataEntries) + 1


def joIN(*argv):
    return ':'.join( [str(val) for val in argv] )

if __name__ == "__main__":
    import os
    try:
        # all input as string
        pEtaBin, jEtaBin, pPtBin, dataEra, ifilename = os.sys.argv[1:]
        if abs(int(pEtaBin))>1: raise ValueError("pEtaBin is out of range -- "+pEtaBin)
        if abs(int(jEtaBin))>2: raise ValueError("jEtaBin is out of range -- "+jEtaBin)
        if abs(int(pPtBin))>25: raise ValueError("pPtBin  is out of range -- "+pPtBin)
        if 'root' not in ifilename: raise ValueError("input filename is not a root file -- "+ifilename)
    except ValueError as vErr:
        PrintHelp(vErr)

    dataEntries = GetDataEntries(ifilename, pEtaBin,jEtaBin,pPtBin)
    sigEntries = int( float(dataEntries)*0.7 )+1
    bkgEntries = int( float(dataEntries)*0.3 )+1

    pptRange = GetPtRange(pPtBin,dataEra)
    petaRange = GetEtaRange(pEtaBin,'#gamma')
    jetaRange = GetEtaRange(jEtaBin,'jet')




    with open('getdatadetail.txt','w') as ofile:
        ofile.write('dataEntries:sigInit:bkgInit:pEtaRange:jEtaRange:pPtRange\n')
        ofile.write(joIN(dataEntries,sigEntries,bkgEntries,petaRange,jetaRange,pptRange))
        print("Here is your output: getdatadetail.txt")


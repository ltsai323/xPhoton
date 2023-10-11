#!/usr/bin/env python3
summaryfile='../data/summaryJson/summary_18QCDMadgraph.json'
ARG_tmpdir='step1.xsinfoAppended'
ARG_outdir='step2.mergePDversion'
ARG_datalumi={ 2016: 35.9, 2017:41.54, 2018:59.96, 'UL2016PreVFP':19.52, 'UL2016PostVFP':16.81 }
TESTmode=False
testDict={
  "QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8": {
    "v15-v1":
"../test/QCD18/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8/QCD_HT300to500_TuneCP5_13TeV-madgraphMLM-pythia8.root",

        },
}
import os
from xPhoton.xPhoton.AppendEventInfo import FindXSInfo, nodir, ShowPD, ShowDetail, FindWeightFile
from xPhoton.xPhoton.Managers.LogMgr import InitLogger, GetLogger
mylog=GetLogger(__name__)

def MYLOG(func, mesg):
    n_file = os.path.basename(__file__)
    n_func = func.__name__
    print(f'{n_file} {n_func}(): {mesg}')

import ROOT
def IntegratedGenWeights(filename: str ) -> float:
    '''
    Get integrated genweight from input root file
    Loaded ntuple : genweightsummary
    Get number recorded in "sumupgenweight" branch

    Arg :
        fileList : root file name

    Return :
        float number
    '''
    f=ROOT.TFile.Open(filename)
    nt=f.Get('genweightsummary')

    Sum=0.
    for a in nt:
        Sum+=a.sumupgenweight
    return Sum

def MergeNeeded( filedict ):
    if len( filedict.keys() ) > 1:
        return True
    return False


def MergeOutputs( primarydataset, inputlist ):
    inputfiles=[ fpath for ver, fpath in inputlist.items() ]
    movecommand='mv {oldfolder}/%s {newfolder}/%s.root'.format(oldfolder=ARG_tmpdir,newfolder=ARG_outdir)
    haddcommand='hadd -f {newfolder}/%s.root %s'.format(newfolder=ARG_outdir)

    mylog.debug(haddcommand % (primarydataset, ' '.join( [ ARG_tmpdir+'/'+ nodir(fpath) for fpath in inputfiles] )))
    if not TESTmode:
        if len(inputfiles) == 1:
            os.system( movecommand % (nodir(inputfiles[0]), primarydataset) )
        elif len(inputfiles) > 1:
            os.system( haddcommand % (primarydataset, ' '.join( [ ARG_tmpdir+'/'+ nodir(fpath) for fpath in inputfiles] )))
        else:
            mylog.warning('nothing found in category %s' % primarydataset)


def executeCommand( xsweight_,
        integratedGenWeight_,
        dataera_,
        isQCD_,
        inputfile_,
        ):

    xs = xsweight_
    genW = integratedGenWeight_ # integrated gen weight
    lumi = ARG_datalumi[dataera_] # integrated luminosity
    iFile = inputfile_ # input file
    oFile = ARG_tmpdir+'/'+nodir(inputfile_) # output file, put to new directory
    isQCD = 'true' if isQCD_ else 'false'

    ## no GenHT reweight version
    bashCommand = f'exec_AppendEventInfo_noGenHTcut {xs:.8e} {genW} {lumi:.8e} {iFile} {oFile}'
    print(bashCommand)

    if not dataera_ in ARG_datalumi:
        raise KeyError('input key "%d" not foun. Available options are [%s]' %
                ( dataera_, ', '.join(['%d'%_s for _s in ARG_datalumi.keys()]) )
                )

    if TESTmode:
        mylog.debug(bashCommand)
    else:
        os.system(bashCommand)
def executeCommandToTmp( xsweight_,
        integratedGenWeight_,
        dataera_,
        isQCD_,
        inputfile_,
        weightfile_=''):
    execfile='exec_AppendEventInfo'

    if not dataera_ in ARG_datalumi:
        print(dataera_)
        raise KeyError('input key "%d" not foun. Available options are [%s]' %
                ( dataera_, ', '.join(['%d'%_s for _s in ARG_datalumi.keys()]) )
                )


    xs=xsweight_
    integratedGenWeight=integratedGenWeight_
    integratedLuminosity=ARG_datalumi[dataera_]
    inputfile=inputfile_
    #outdir = ARG_tmpdir
    outputfile=ARG_tmpdir+'/'+nodir(inputfile_)
    isqcd = 'true' if isQCD_ else 'false'
    weightfile=weightfile_

    if 'root' in weightfile_ and os.path.exists(weightfile_):
        MYLOG(executeCommandToTmp, '--- execute with GenHT cut and reweighted PU weight ---')
        execcommand = f'exec_AppendEventInfo {xs:.2e} {integratedGenWeight:.8e} {integratedLuminosity:.8e} {inputfile:s} {outputfile:s} {isqcd:s} {weightfile:s}'
    else:
        MYLOG(executeCommandToTmp, '--- NO GenHT related information ---')
        execcommand = f'exec_AppendEventInfo_noGenHTcut {xs:.8e} {integratedGenWeight:.8e} {integratedLuminosity:.8e} {inputfile:s} {outputfile:s}'


    if TESTmode:
        print(execcommand)
    else:
        os.system( execcommand )

def CheckWorkingDir():
    import os
    if not os.path.exists(ARG_tmpdir) or not os.path.isdir(ARG_tmpdir): os.mkdir(ARG_tmpdir)
    if not os.path.exists(ARG_outdir) or not os.path.isdir(ARG_outdir): os.mkdir(ARG_outdir)

def GetXS(pd_, ver_, summaryfile_):
    xs,xserr,xsunit=FindXSInfo(pd_,ver_,summaryfile_)
    if   xsunit=='pb': xs *= 1000.
    elif xsunit=='fb': pass
    else :             mylog.error( 'recorded Xsection in "%s" unit in file %s. Which is not "pb" or "fb". Need to convert it manually!' % (xsunit, summaryfile_) )
    return xs

if __name__ == '__main__':
    arg_summaryfile='../data/summaryJson/summary_bkgMC_madgraph.json'
    arg_dataera=2016
    arg_isQCD=True

    InitLogger(level='info')
    mylog=GetLogger(__name__)
    CheckWorkingDir()

    version=''

    targetDict=testDict
    integratedgenweights = { pd:sum( [IntegratedGenWeights(fpath) for ver,fpath in info.items()] )
            for pd, info in targetDict.items() }

    for pd, info in targetDict.items():
        for ver, rootfile in info.items():
            xs,xserr,xsunit=FindXSInfo(pd,ver,summaryfile)
            if   xsunit=='pb': xs *= 1000.
            elif xsunit=='fb': pass
            else :             mylog.error( 'recorded Xsection in "%s" unit in file %s. Which is not "pb" or "fb". Need to convert it manually!' % (xsunit, summaryfile) )
            print( type(xs))
            executeCommandToTmp( xs, integratedgenweights[pd], arg_dataera, arg_isQCD, rootfile, weight_file )
        MergeOutputs(pd, info)


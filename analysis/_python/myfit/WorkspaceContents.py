from xPhoton.xPhoton.Managers.AdditionalFunctionMgr import ImportAddFunc
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
from xPhoton.analysis.myfit.RooFitSpaceMgr import RooFitSpaceMgr
import ROOT

logger=GetLogger(__name__)

#factory_histpdf='HistPdf::{name}({var},{datahist})'
#factory_var='{name}({xmin},{xval})'
#factory_num='{name}({xdef},{xmin},{xmax})'


if __name__ == '__main__':
    from array import array

    space=ROOT.RooWorkspace('space',False)
    myspace=RooFitSpaceMgr(space)

    var='r9'
    inputinfo=[
    ('data' , '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists_data_Run2016G.root'),
    ('mcsig', '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists_mcbkg_Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
    ('mcbkg', '/home/ltsai/Work/workspaceGammaPlusJet/storeroot/outputParHists_mcsig_Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root'),
    ]
    inputfile=[ ROOT.TFile.Open(p) for t,p in inputinfo ]
    inputhist=[ f.Get(var) for f in inputfile ]
    varrange=( inputhist[0].GetXaxis().GetXmin(), inputhist[0].GetXaxis().GetXmax() )
    CreateVar( myspace, var, varrange )

    creategaussianpdf(myspace)
    for (label,p), hist in zip(inputinfo,inputhist):
        if label=='data': continue
        CreateHistPDF( myspace, hist, label )




    logger.debug('writing to root file')
    myspace.Write('newfile.root')
    del myspace
    for ifile in inputfile:
        ifile.Close()
        logger.debug(ifile.GetName() + ' is closed')
    logger.debug('successfully done')


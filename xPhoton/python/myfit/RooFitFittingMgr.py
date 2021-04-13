import ROOT
from xPhoton.xPhoton.Managers.AdditionalFunctionMgr import ImportAddFunc
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
from xPhoton.xPhoton.myfit.RooFitSpaceMgr import RooFitSpaceMgr
logger=GetLogger(__name__)

# if the variables/pdfs owning postfix means the objects are produced and controled by this procedure.
PROCESSNAMEPOSTFIX='FitMgr'
def Naming( *args ):
    return '_'.join(args)

class RooFitFittingMgr(object):
    def __init__(self, inputworkspace):
        if not isinstance(inputworkspace, (RooFitSpaceMgr,None)):
            logger.error('constructing object failed. Input RooFitSpaceMgr object')

        self._workspace=inputworkspace
        self._observ=None
        self._target=None
        self._fitpdf=None # pdf

        self._pdfcomponents=[] # [ (label,pdf) ]
        self._additionalInfo=ImportAddFunc()

        self.loadinfos=[]
        pass

    def __del__(self):
        #self._workspace.Write()
        self._workspace=None
        for info in self.loadinfos:
            logger.info( 'Closing file ' + info['file'].GetName() )
            info['file'].Close()
    # input RooDataHist or RooDataSet. RooRealVar
    def SetFitTarget(self, dataset, obs):
        self._target=dataset
        self._observ=obs

    def SetPDF_Components(self, label,pdf):
        self._pdfcomponents.append( (label,pdf) )
    def SetPDF_Target(self,pdf):
        self._fitpdf=pdf
    # input the whole building function, which returns a tuple in (name, RooAbsPdf)
    def BuildPDFComponent(self, **kwargs):
        label, pdf = self._additionalInfo.ImportFunction(**kwargs)
        self._pdfcomponents.append( (label,pdf) )
    def BuildPDFTotal(self, **kwargs):
        self.SetPDF_Target( self._additionalInfo.ImportFunction(**kwargs) )
        for infoMgr in self._additionalInfo:
            a=infoMgr.GetExecRes()

    def reserveitem(self, item):
        self._workspace.ReserveItem(item, PROCESSNAMEPOSTFIX.format(item.GetName()))
        logger.debug(item.GetName())

    def PerformFitting(self, useMinos=False):
        self._fitpdf.fitTo(self._target, ROOT.RooFit.Minos(useMinos))


    def CalculateDrawingContent(self):
        plotframe=self._observ.frame( ROOT.RooFit.Title('') )
        self._target.plotOn(plotframe, ROOT.RooFit.Name('data'))

        self._fitpdf.plotOn(plotframe,
                ROOT.RooFit.LineColor(4),
                ROOT.RooFit.LineWidth(4),
                ROOT.RooFit.Name('totFit')
                )
        i=2
        for label, pdf in self._pdfcomponents:
            self._fitpdf.plotOn(plotframe,
                    ROOT.RooFit.LineColor(i),
                    ROOT.RooFit.LineWidth(5),
                    ROOT.RooFit.Name(label),
                    ROOT.RooFit.Components(pdf.GetName())
                    )
            i=i+4
            logger.debug('Plot component with name : '+label)
        return plotframe
    # loadinfo = [ ('label','objname') ]
    def LoadObjects(self, filepath, loadinfo, saveANDrenameToworkspace=False):
        openedfile=ROOT.TFile.Open(filepath)
        label=loadinfo[0]
        name=loadinfo[1]
        print name
        loadedobj=openedfile.Get(name)
        #loadedobj=( label, openedfile.Get(name) )
        #self.loadinfos.append( (openedfile, loadedobj) )
        if saveANDrenameToworkspace:
            self._workspace.ReserveItem( loadedobj,
                    Naming(label,loadedobj.GetName(),PROCESSNAMEPOSTFIX)
                    )

        self.loadinfos.append( {
                    'file':openedfile,
                    'obj':loadedobj,
                    'label':label
                } )
        return self.loadinfos[-1]['obj']
    def GetObservableName(self):
        return self._observ.GetName()

if __name__ == '__main__':
    ws=RooFitSpaceMgr()
    a=RooFitFittingMgr(ws)

    loadingobject=('data' , 'mva')
    loadingobject=('mcsig', 'mva')
    loadingobject=('mcbkg', 'mva')


    a.LoadObjects(
            filepath='a.root',
            loadinfo=loadingobject,
            saveANDrenameToworkspace=True
            )
    a.SetFitTarget(someRooDataHist,someRooRealVar)

    a.SetPDF_Components(label1,someRooAbsPdf1)
    a.SetPDF_Components(label2,someRooAbsPdf2)
    a.SetPDF_Components(label3,someRooAbsPdf3)

    a.SetPDF_Target(someRooAbsPdf)
    a.PerformFitting()
    a.CalculateDrawingContent


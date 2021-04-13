import ROOT
from xPhoton.xPhoton.Managers.AdditionalFunctionMgr import ImportAddFunc
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
logger=GetLogger(__name__)

LOADEDITEMPOSTFIX='_loaded'

def Naming( name, postfix='' ):
    return name+postfix

#class RooFitIOMgr(object):
class RooFitSpaceMgr(object):
    def __init__(self, workspace='space', loadFile=''):
        logger.debug('init space')

        self._loadfile=ROOT.TFile.Open(loadFile) if '.root' in loadFile else None
        self._space=self._loadfile.Get(workspace) if self._loadfile else ROOT.RooWorkspace('space',False)

        self._keptItem=[]
        self._additionalInfo=ImportAddFunc()
        self._written=False

        self._loadinfos=[] # (tfile, {'label':tobject, 'label2':tobject2 }

    def __del__(self):
        logger.info('deleting RooFitSpaceMgr')
        del self._space
        self._space=None
        if self._loadfile: self._loadfile.Close()
        logger.info('deleted  RooFitSpaceMgr')


    def check_duplicate(self, newobj):
        for storedobj in self._keptItem:
            if newobj.GetName() == storedobj:
                raise IOError('Duplicated check failed! please change imported object name : "{0}"'.format(obj.GetName()))
    def check_inputtype(self, obj, thetypes):
        if not isinstance( obj, thetypes ):
            raise TypeError('input object as an argument of function in a wrong type. This object belongs to "{belong}" but "{types}" are needed'.format(belong=type(obj), types=accaptabletypes))




    def saving(self, obj):
        logger.debug( 'saving %s in workspace'% obj.GetName() )
        getattr(self._space,'import')(obj) # for ROOT 5.x
        #self._space.Import(obj) # for ROOT 6.x
        logger.debug    ('       %s saved (for check, this name needs to be the same as above.)'%obj.GetName())

    def namingitem(self, obj, newname=''):
        if newname:
            obj.SetName(newname)
    def writetofile(self, filename):
        if self._written:
            logger.error('This workspace has been written!')
            raise IOError()
        outfile=ROOT.TFile(filename, 'recreate')
        outfile.cd()
        self._space.Write()
        outfile.Close()
        logger.debug('space written to %s'%(filename))

        #del self._space
        self._space=None
        self.written=True
        logger.debug('workspace destroyed')

    def ReserveItem(self, obj,newname=''):
        self.namingitem(obj,newname)

        self.check_duplicate(obj)
        self.saving(obj)
        self._keptItem.append(obj.GetName())

    def AddComponent(self, **kwargs):
        self._additionalInfo.ImportFunction(**kwargs)

    def Write(self, newfilename=None):
        if newfilename:
            self.writetofile(newfilename)
    def RenameObj(self, obj, newname):
        if newname: obj.SetName(newname)

    def LoadVar(self, name):
        return self._space.var(name)
    def LoadPdf(self, name):
        return self._space.pdf(name)
    def Factory(self, content):
        self._space.factory(content)

    def CreateDataHist(self,hist,obsname, outname):
        logger.debug('data hist creating!')
        roobs=self.LoadVar(obsname)

        datahist=ROOT.RooDataHist(outname,outname,
                ROOT.RooArgList(roobs), hist)
        self.ReserveItem(datahist)
        return datahist

    def CreatePDF_Add(self, extpdfnames, outname):
        for pdfname in extpdfnames: self.check_inputtype(pdfname,(str))
        extpdfs = [ self.LoadPdf(pdfname) for pdfname in extpdfnames ]
        extpdf0=self.LoadPdf(extpdfnames[0])
        extpdf1=self.LoadPdf(extpdfnames[1])

        outpdf=ROOT.RooAddPdf(outname,outname,
                ROOT.RooArgList(*extpdfs)
                )
        self.ReserveItem(outpdf)
        return outpdf
    def CreatePDF_Extended(self, pdfname, yieldname, outname):
        self.check_inputtype(pdfname,   str)
        self.check_inputtype(yieldname, str)
        logger.debug('extPDF creating! with name %s'%outname)
        xvar=self.LoadVar(yieldname)
        yieldvar=self.LoadVar(yieldname)
        pdf=self.LoadPdf(pdfname)

        extpdf=ROOT.RooExtendPdf(outname,outname, pdf,yieldvar)
        self.ReserveItem(extpdf)
        return extpdf
    def CreatePDF_Hist(self, datahist, obsname, outname):
        logger.debug('histPDF creating! with name %s'%datahist.GetName())
        xvar=self.LoadVar(obsname)

        histpdf=ROOT.RooHistPdf(outname,outname,
                ROOT.RooArgSet( xvar ), datahist,
                0 )
        self.ReserveItem(histpdf)
        logger.debug('histPDF created and stored!')

        return histpdf


    def CreateVar_const(self, name, xval):
        xvar=ROOT.RooRealVar( name,name, xval )
        self.ReserveItem(xvar)
        return xvar
    def CreateVar_Yield(self, name, maxval, initval=0.):
        ival=initval if initval else maxval*0.7
        xvar=ROOT.RooRealVar( name,name, ival, 0., maxval )
        self.ReserveItem(xvar)
        return xvar

    def CreateVar(self, name, xrange=[0.0,1.1]):
        if not isinstance(xrange, (tuple,list) ):
            log.error( 'input a wrong range format in xrange variable. (the content is {0})'.format(xrange) )
            exit(1)
        xvar=ROOT.RooRealVar( name,name, xrange[0], xrange[1])
        self.ReserveItem(xvar)
        return xvar


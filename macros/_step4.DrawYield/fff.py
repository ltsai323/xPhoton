#!/usr/bin/env python2
import xPhoton.xPhoton.Managers.LogMgr as LogMgr
mylog=LogMgr.GetLogger()
import ROOT

PHOPT_RANGE=[25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000]



class PDFComponent(object):
    def __init__(self, RooAbsPdfObj, numVar):
        self.pdf=RooAbsPdfObj
        self.num=numVar
        self.extpdf=PDFComponent.MakeExtended( self.pdf, self.num )
    @staticmethod
    def MakeExtended(pdf, num):
        n=pdf.GetName()
        return ROOT.RooExtendPdf('e'+n, '', pdf, num)
    def Extended(self):
        return self.extpdf
    def GetName(self):
        return self.extpdf.GetName()
def plotComponent(fitpdf, frame, pdf, name='hi',
        linewidth=4, linecolor=0, fillcolor=0,fillstyle=1001, drawopt='F'):
    fitpdf.plotOn(frame,
            ROOT.RooFit.Components( pdf.GetName() ),
            ROOT.RooFit.Name(name),
            ROOT.RooFit.LineWidth(linewidth),
            ROOT.RooFit.LineColor(linecolor),
            ROOT.RooFit.FillStyle(fillstyle),
            ROOT.RooFit.FillColor(fillcolor),
            ROOT.RooFit.DrawOption(drawopt),
            )

class MyBin(object):
    def __init__(self, phoptbin, phoetabin, jetetabin):
        self.phoptbin=phoptbin
        self.phoetabin=phoetabin
        self.jetetabin=jetetabin
    def naming(self, nametemplate):
        return nametemplate % (self.phoetabin, self.jetetabin, self.phoptbin)

class FittingWorkspace(ROOT.RooWorkspace):
    def __init__(self):
        super(FittingWorkspace,self).__init__('_space',False)
        self.MYcanv=ROOT.TCanvas('c1','',1200,1000)
        self.MYcanv.SetFillColor(4000)
        self.MYcanv.SetFillStyle(4000)
    def SetVar(self, name):
        self.MYvarObj=self.var(name)
    def SetVarObj(self, obj):
        self.MYvarObj=obj
    def SetFitTarget(self, dataset):
        self.MYtargetObj=dataset

    def myImport(self, obj):
        getattr(self, 'import')(obj)
    def mySaveSnapShot(self, name, pars):
        self.saveSnapshot(name, pars, True)
    def myLoadSnapShot(self, snapshot):
        self.loadSnapshot(snapshot)
    def myWriteSpace(self, oname):
        outputfile=ROOT.TFile(oname,'recreate')
        outputfile.cd()
        self.Write()
        outputfile.Close()
        print 'workspace is stored at %s'%oname

    def TwoComponentsFit(self,mybin,
            hist_sig, hist_bkg):
        mylog.debug('TwoComponentFit() : status 01: loading variable from workspace')
        var=self.MYvarObj
        INIT_SIGFRAC=0.7

        mylog.debug('TwoComponentFit() : Check with input sigHist name : %s' % (hist_sig.GetName()) )
        mylog.debug('TwoComponentFit() : Check with input bkgHist name : %s' % (hist_bkg.GetName()) )
        datahist_data=self.MYtargetObj
        datahist_sig=ROOT.RooDataHist( mybin.naming('_dh_sig.%d_%d_%d'), '', ROOT.RooArgList(var), hist_sig )
        datahist_bkg=ROOT.RooDataHist( mybin.naming('_dh_bkg.%d_%d_%d'), '', ROOT.RooArgList(var), hist_bkg )
        self.myImport(datahist_sig)
        self.myImport(datahist_bkg)
        allnum=self.MYtargetObj.sumEntries()
        print allnum
        mylog.debug('TwoComponentFit() : status 02: Creating signal PDF')
        pdf_sig=PDFComponent(
                ROOT.RooHistPdf( mybin.naming('_pdf_sig.%d_%d_%d'), '', ROOT.RooArgSet(var), datahist_sig, 0),
                ROOT.RooRealVar( mybin.naming('_num_sig.%d_%d_%d'), '', allnum*INIT_SIGFRAC, 0., allnum)
                )
        mylog.debug('TwoComponentFit() : status 03: creating background PDF')
        pdf_bkg=PDFComponent(
                ROOT.RooHistPdf( mybin.naming('_pdf_bkg.%d_%d_%d'), '', ROOT.RooArgSet(var), datahist_bkg, 0),
                ROOT.RooRealVar( mybin.naming('_num_bkg.%d_%d_%d'), '', allnum*INIT_SIGFRAC, 0., allnum)
                )
        mylog.debug('TwoComponentFit() : status 04: creating total PDF for fit')
        pdf_all=ROOT.RooAddPdf( mybin.naming('_fitpdf.%d_%d_%d'), '', ROOT.RooArgList(pdf_sig.Extended(),pdf_bkg.Extended()) )

        mylog.debug('TwoComponentFit() : status 05 : datahist entries : %d are ready for fit.' % datahist_data.sumEntries())
        if datahist_data.sumEntries() >= 1.:
            #pdf_all.fitTo(datahist_data, ROOT.RooFit.PrintLevel(-1))
            pdf_all.fitTo(datahist_data)
        mylog.debug('TwoComponentFit() : status 06: import fit fragments into workspace.')
        space.myImport(pdf_all)

        print('-----------------------------------------------------')
        print('Data %5.1f events, and %5.1f fitted'%( datahist_data.sumEntries(), (pdf_sig.num.getVal()+pdf_bkg.num.getVal()) ))
        print('ptbin %d  etabin %d  jetbin %d SIG %5.1f #pm %5.1f events'% ( mybin.phoptbin,mybin.phoetabin,mybin.jetetabin, pdf_sig.num.getVal(), pdf_sig.num.getError() ))
        print('ptbin %d  etabin %d  jetbin %d BKG %5.1f #pm %5.1f events'% ( mybin.phoptbin,mybin.phoetabin,mybin.jetetabin, pdf_bkg.num.getVal(), pdf_bkg.num.getError() ))


        return {'fitpdf': pdf_all.GetName(), 'components':[pdf_sig.GetName(), pdf_bkg.GetName()], 'var': self.MYvarObj.GetName() }

    def DrawFitRes(self, mybin, figname, fitres ):
        dataset=self.MYtargetObj
        var=self.MYvarObj

        self.MYcanv.cd()
        var=self.var(fitres['var'])
        pdf_all=self.pdf(fitres['fitpdf'])

        xframe=var.frame()
        xframe.SetTitle('')
        dataset.plotOn(xframe)
        xframe.SetMaximum( xframe.GetMaximum() * 1.5 )
        pdf_all.plotOn(xframe, ROOT.RooFit.Name('fitpdf'),
                ROOT.RooFit.FillColor(30),
                ROOT.RooFit.LineColor(0),
                ROOT.RooFit.DrawOption('F')
                )
        chi2Val=xframe.chiSquare()

        plotComponent(pdf_all, xframe, self.pdf(fitres['components'][1]), name='bkg',
                fillcolor=42, fillstyle=1001, drawopt='f'
                )
        plotComponent(pdf_all, xframe, self.pdf(fitres['components'][0]), name='sig',
                linewidth=7, linecolor=46, drawopt='l'
                )
        dataset.plotOn(xframe, ROOT.RooFit.MarkerSize(2))
        xframe.Draw()

        phoetaregion='|#eta^{#gamma}|<1.4442' if mybin.phoetabin==0 else '1.566<|#eta^{#gamma}|<2.5'
        jetetaregion='|#eta^{jet}|<1.4442' if mybin.jetetabin==0 else '1.566<|#eta^{jet}|<2.5'
        phoptregion='%d < p^{#gamma}_{T} < %d' % (PHOPT_RANGE[mybin.phoptbin],PHOPT_RANGE[mybin.phoptbin+1])
        leg=ROOT.TLegend(0.15, 0.55, 0.65, 0.85, '#splitline{%s}{%s} #splitline{%s}{chi2/nDof = %.1f/9}'%(phoetaregion,jetetaregion,phoptregion, chi2Val) )
        Nsig=self.var( mybin.naming('num_sig.%s_%s_%s') )
        Nbkg=self.var( mybin.naming('num_bkg.%s_%s_%s') )
        leg.AddEntry( dataset, 'Data', 'p')
        leg.AddEntry( xframe.findObject('sig'), '#splitline{signal photon}{ = %.1f #pm %.1f}'%(Nsig.getVal(),Nsig.getError()), 'l' )
        leg.AddEntry( xframe.findObject('fitpdf'), 'Fitting', 'f' )
        leg.AddEntry( xframe.findObject('bkg'), '#splitline{fake photon}{ = %.1f #pm %.1f}'%(Nbkg.getVal(),Nbkg.getError()), 'f' )

        leg.SetBorderSize(0)
        leg.SetNColumns(2)
        leg.SetTextAlign(32)
        leg.Draw()

        print 'fitting quality : chi2/nDof = %.3f / %s = %.3f' % ( chi2Val, '10-2', chi2Val/8 )
        self.MYcanv.Update()
        self.MYcanv.SaveAs(figname)

class LoadedWorkspace(object):
    def __init__(self, infile):
        self._ifile=ROOT.TFile.Open(infile)
        self.loadspace=self._ifile.Get('space')
        self.truth_sig=0
        self.truth_bkg=0
        self.MYtargetObj=None

    def __del__(self):
        self._ifile.Close()

    def SetVar(self, varname):
        self.MYvarObj=self.loadspace.var(varname)

    def Cleaning(self):
        if self.MYtargetObj:
            del self.MYtargetObj
            self.MYtargetObj=None
            self.truth_sig=0
            self.truth_bkg=0

    def GenerateFakeDataset(self, sigbin):
        self.Cleaning()
        origdata_sig=self.loadspace.pdf( sigbin.naming('epdf_sig.%d_%d_%d') )
        origdata_bkg=self.loadspace.pdf( sigbin.naming('epdf_bkg.%d_%d_%d') )
        origvar_sig=self.loadspace.var( sigbin.naming('num_sig.%d_%d_%d') )
        origvar_bkg=self.loadspace.var( sigbin.naming('num_bkg.%d_%d_%d') )
        newdata_sig=origdata_sig.generate( ROOT.RooArgSet(self.MYvarObj), origvar_sig.getVal() )
        newdata_bkg=origdata_bkg.generate( ROOT.RooArgSet(self.MYvarObj), origvar_bkg.getVal() )

        self.MYtargetObj=newdata_sig.Clone( sigbin.naming('fakedata.%d_%d_%d'))
        self.MYtargetObj.append(newdata_bkg)
        self.truth_sig=origvar_sig.getVal()
        self.truth_bkg=origvar_bkg.getVal()

    def TwoComponentsFit(self,mybin,
            hist_sig, hist_bkg):
        mylog.debug('TwoComponentFit() : status 01: loading variable from workspace')
        var=self.MYvarObj
        INIT_SIGFRAC=0.7

        mylog.debug('TwoComponentFit() : Check with input sigHist name : %s' % (hist_sig.GetName()) )
        mylog.debug('TwoComponentFit() : Check with input bkgHist name : %s' % (hist_bkg.GetName()) )
        datahist_data=self.MYtargetObj
        datahist_sig=ROOT.RooDataHist( mybin.naming('dh_sig.%d_%d_%d'), '', ROOT.RooArgList(var), hist_sig )
        datahist_bkg=ROOT.RooDataHist( mybin.naming('dh_bkg.%d_%d_%d'), '', ROOT.RooArgList(var), hist_bkg )
        #self.myImport(datahist_sig)
        #self.myImport(datahist_bkg)
        allnum=self.MYtargetObj.sumEntries()
        print allnum
        mylog.debug('TwoComponentFit() : status 02: Creating signal PDF')
        pdf_sig=PDFComponent(
                ROOT.RooHistPdf( mybin.naming('pdf_sig.%d_%d_%d'), '', ROOT.RooArgSet(var), datahist_sig, 0),
                ROOT.RooRealVar( mybin.naming('num_sig.%d_%d_%d'), '', allnum*INIT_SIGFRAC, 0., allnum)
                )
        mylog.debug('TwoComponentFit() : status 03: creating background PDF')
        pdf_bkg=PDFComponent(
                ROOT.RooHistPdf( mybin.naming('pdf_bkg.%d_%d_%d'), '', ROOT.RooArgSet(var), datahist_bkg, 0),
                ROOT.RooRealVar( mybin.naming('num_bkg.%d_%d_%d'), '', allnum*INIT_SIGFRAC, 0., allnum)
                )
        mylog.debug('TwoComponentFit() : status 04: creating total PDF for fit')
        pdf_all=ROOT.RooAddPdf( mybin.naming('fitpdf.%d_%d_%d'), '', ROOT.RooArgList(pdf_sig.Extended(),pdf_bkg.Extended()) )

        mylog.debug('TwoComponentFit() : status 05 : datahist entries : %d are ready for fit.' % datahist_data.sumEntries())
        if datahist_data.sumEntries() >= 1.:
            pdf_all.fitTo(datahist_data, ROOT.RooFit.PrintLevel(-1))
        mylog.debug('TwoComponentFit() : status 06: import fit fragments into workspace.')
        #space.myImport(pdf_all)

        print('-----------------------------------------------------')
        print('Data %5.1f events, and %5.1f fitted'%( datahist_data.sumEntries(), (pdf_sig.num.getVal()+pdf_bkg.num.getVal()) ))
        print('ptbin %d  etabin %d  jetbin %d SIG %5.1f #pm %5.1f events'% ( mybin.phoptbin,mybin.phoetabin,mybin.jetetabin, pdf_sig.num.getVal(), pdf_sig.num.getError() ))
        print('ptbin %d  etabin %d  jetbin %d BKG %5.1f #pm %5.1f events'% ( mybin.phoptbin,mybin.phoetabin,mybin.jetetabin, pdf_bkg.num.getVal(), pdf_bkg.num.getError() ))


        return {'fitpdf': pdf_all.GetName(), 'components':[pdf_sig.GetName(), pdf_bkg.GetName()], 'var': self.MYvarObj.GetName() }


def GetArg_inputfile(argv):
    return argv[1]

if __name__ == '__main__':
    import sys

    LogMgr.InitLogger(level='debug')
    mylog=LogMgr.GetLogger(__name__)
    ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.ERROR)
    loadspace=LoadedWorkspace( GetArg_inputfile(sys.argv) )
    loadspace.SetVar('BDTscore')

    infile=ROOT.TFile.Open('isovsbdt_template.root')
    space=FittingWorkspace()

    space.factory('BDTscore[-1.,1.]')
    #space.SetVar('BDTscore')
    #space.SetVarObj( loadspace.var )

    for phoeta in range(2):
        for jeteta in range(2):
            for phopt in range(21):
                mylog.debug('indexes are pEta:%d jEta:%d pPt:%d' % (phoeta,jeteta,phopt) )
                sigbin=MyBin(phopt, phoeta, jeteta)
                bkgpt = phopt if phopt < 17 else 17
                bkgbin=MyBin(bkgpt, phoeta, jeteta)

                h_sig =infile.Get( sigbin.naming('gjet_%d_%d_%d_px1_chIso') )
                h_bkg =infile.Get( bkgbin.naming('data_%d_%d_%d_px2_chIso') )


                loadspace.GenerateFakeDataset(sigbin)
                mylog.debug('generated events : %.1f'%loadspace.MYtargetObj.sumEntries() )

                #loadspace.MYtargetObj.plotOn(xaxis, ROOT.RooFit.Binning(10))
                #space.SetFitTarget( loadspace.MYtargetObj )
                pdfnames=loadspace.TwoComponentsFit( sigbin,
                        h_sig, h_bkg,
                        )

                #exit(1)



    mylog.info('start writing fit fragments to root file')
    mylog.info('job finished')

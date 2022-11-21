#!/usr/bin/env python2
import xPhoton.xPhoton.Managers.LogMgr as LogMgr
mylog=LogMgr.GetLogger()
import ROOT

#PHOPT_RANGE=[25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000] # old
PHOPT_RANGE=[25,34,41,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000]


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
        super(FittingWorkspace,self).__init__('space',False)
        self.MYcanv=ROOT.TCanvas('c1','',1200,1000)
        self.MYcanv.SetFillColor(4000)
        self.MYcanv.SetFillStyle(4000)
    def SetVar(self, name):
        self.MYvarObj=self.var(name)
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
        datahist_sig=ROOT.RooDataHist( mybin.naming('dh_sig.%d_%d_%d'), '', ROOT.RooArgList(var), hist_sig )
        datahist_bkg=ROOT.RooDataHist( mybin.naming('dh_bkg.%d_%d_%d'), '', ROOT.RooArgList(var), hist_bkg )
        self.myImport(datahist_sig)
        self.myImport(datahist_bkg)
        allnum=datahist_data.sumEntries()
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
            #pdf_all.fitTo(datahist_data, ROOT.RooFit.PrintLevel(-1))
            pdf_all.fitTo(datahist_data)
        mylog.debug('TwoComponentFit() : status 06: import fit fragments into workspace.')
        self.myImport(pdf_all)

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
        pdf_all.plotOn(xframe,
                ROOT.RooFit.FillColor(0),
                ROOT.RooFit.LineColor(2),
                ROOT.RooFit.DrawOption('l')
                )
        chi2Val=xframe.chiSquare()

        plotComponent(pdf_all, xframe, self.pdf(fitres['components'][1]), name='bkg',
                linecolor=1,linewidth=1,fillcolor=38, fillstyle=3001, drawopt='f'
                )
        plotComponent(pdf_all, xframe, self.pdf(fitres['components'][0]), name='sig',
                linecolor=1,linewidth=1,fillcolor=46, fillstyle=3002, drawopt='f'
                )
        pdf_all.plotOn(xframe, ROOT.RooFit.Name('fitpdf'),
                ROOT.RooFit.FillColor(0),
                ROOT.RooFit.LineColor(2),
                ROOT.RooFit.LineWidth(4),
                ROOT.RooFit.DrawOption('l')
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
        leg.AddEntry( xframe.findObject('fitpdf'), 'Fitting', 'l' )
        leg.AddEntry( xframe.findObject('sig'), '#splitline{signal photon}{ = %.1f #pm %.1f}'%(Nsig.getVal(),Nsig.getError()), 'f' )
        leg.AddEntry( xframe.findObject('bkg'), '#splitline{fake photon}{ = %.1f #pm %.1f}'%(Nbkg.getVal(),Nbkg.getError()), 'f' )

        leg.SetBorderSize(0)
        leg.SetNColumns(2)
        #leg.SetTextAlign(32)
        leg.SetFillColor(4000)
        leg.SetFillStyle(4000)
        leg.Draw()

        print 'fitting quality : chi2/nDof = %.3f / %s = %.3f' % ( chi2Val, '10-2', chi2Val/8 )
        self.MYcanv.Update()
        self.MYcanv.SaveAs(figname)




def GetArg_phoeta(argv):
    return int(argv[1])
def GetArg_jeteta(argv):
    return int(argv[2])

if __name__ == '__main__':
    import sys
    isFake=False
    if isFake:
        sigFragFile=ROOT.TFile('isovsbdt_fragments.sig.root')
        bkgFragFile=ROOT.TFile('isovsbdt_fragments.bkg.root')

    LogMgr.InitLogger(level='info')
    mylog=LogMgr.GetLogger(__name__)
    ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.ERROR)
    infile=ROOT.TFile.Open('isovsbdt_template.root')
    #space=MyWorkspace()
    space=FittingWorkspace()

    space.factory('BDTscore[-1.,1.]')
    var=space.var('BDTscore')
    space.SetVar('BDTscore')


    for phoeta in range(2):
        for jeteta in range(2):
            for phopt in range(21):
                mylog.debug('indexes are pEta:%d jEta:%d pPt:%d' % (phoeta,jeteta,phopt) )
                sigbin=MyBin(phopt, phoeta, jeteta)
                bkgpt = phopt if phopt < 17 else 17
                #bkgpt = phopt if phopt < 19 else 19
                bkgbin=MyBin(bkgpt, phoeta, jeteta)

                mylog.debug( 'status 01: Loading hists from file.' )
                h_data=infile.Get('data_%d_%d_%d_px1_chIso'%(phoeta,jeteta,phopt))
                h_sig =infile.Get( sigbin.naming('gjet_%d_%d_%d_px1_chIso') )
                h_bkg =infile.Get( bkgbin.naming('data_%d_%d_%d_px2_chIso') )

                if h_data.GetNbinsX() > 10 : h_data.Rebin(10)
                if h_sig .GetNbinsX() > 10 : h_sig.Rebin(10)
                if h_bkg .GetNbinsX() > 10 : h_bkg.Rebin(10)

                mylog.debug( 'status 03: Creating datahist' )
                fitsources_data=ROOT.RooDataHist( sigbin.naming('dh_data.%d_%d_%d'), '', ROOT.RooArgList(var), h_data)
                space.myImport( fitsources_data )
                space.SetFitTarget( fitsources_data )


                mylog.debug( 'status 04: To fitting function' )
                pdfnames=space.TwoComponentsFit( sigbin,
                        h_sig, h_bkg,
                        )

                mylog.debug( 'status 05: Drawing output plots' )
                space.DrawFitRes( sigbin, sigbin.naming('plots/checking_%d_%d_%d.pdf'),pdfnames )
                mylog.debug( 'status ended: finished of a loop node')

    mylog.info('start writing fit fragments to root file')
    space.myWriteSpace('fitres_workspace.root')
    del space
    mylog.info('job finished')

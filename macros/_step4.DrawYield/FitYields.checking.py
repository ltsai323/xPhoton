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

#asdf
def MakePullHist(
        sigratio,
        space,
        snapshotname='fitres',
        ):
    genevt=1000
    pullloop=1000
    SIGRATIO=sigratio
    randoms=ROOT.TRandom3()
    yield_truth=genevt*SIGRATIO

    num=space.var('num_sig')
    h_pull=ROOT.TH1F( naming('pull'), 'pull distribution', 60 -6.,6.)
    for i in range(pullloop):
        space.myLoadSnapShot('fitres')


        pdf=space.pdf('fitpdf')
        toydata=pdf.generate( ROOT.RooArgSet(var), randoms.Poisson(genevt) )
        pdf.fitTo(toydata, ROOT.RooFit.PrintLevel(-1))

        fitval=num.getVal()
        fiterr=num.getError()
        h_pull.Fill( (fitval-yield_truth)/fiterr )
    return h_pull

class MyWorkspace(ROOT.RooWorkspace):
    def __init__(self):
        super(MyWorkspace,self).__init__('space',False)
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
        allnum=h_data.GetEntries()
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
        space.myImport(pdf_all)

        print('-----------------------------------------------------')
        print('Data %5.1f events, and %5.1f fitted'%( datahist_data.sumEntries(), (pdf_sig.num.getVal()+pdf_bkg.num.getVal()) ))
        #print( mybin.naming('ptbin %d  etabin %d  jetbin %d SIG {val:.1f} #pm {err:.1f} events'.format(val=pdf_sig.num.getVal(),err= pdf_sig.num.getError())) )
        #print( mybin.naming('ptbin %d  etabin %d  jetbin %d BKG {val:.1f} #pm {err:.1f} events'.format(val=pdf_bkg.num.getVal(),err= pdf_bkg.num.getError())) )
        print('ptbin %d  etabin %d  jetbin %d SIG %5.1f #pm %5.1f events'% ( mybin.phoptbin,mybin.phoetabin,mybin.jetetabin, pdf_sig.num.getVal(), pdf_sig.num.getError() ))
        print('ptbin %d  etabin %d  jetbin %d BKG %5.1f #pm %5.1f events'% ( mybin.phoptbin,mybin.phoetabin,mybin.jetetabin, pdf_bkg.num.getVal(), pdf_bkg.num.getError() ))


        return {'fitpdf': pdf_all.GetName(), 'components':[pdf_sig.GetName(), pdf_bkg.GetName()], 'var': self.MYvarObj.GetName() }

    def DrawFitRes(self, figname, fitres ):
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

        phoetaregion='|#eta^{#gamma}|<1.4442' if PHOETABIN==0 else '1.566<|#eta^{#gamma}|<2.5'
        jetetaregion='|#eta^{jet}|<1.4442' if JETETABIN==0 else '1.566<|#eta^{jet}|<2.5'
        phoptregion='%d < p^{#gamma}_{T} < %d' % (PHOPT_RANGE[PHOPTBIN],PHOPT_RANGE[PHOPTBIN+1])
        leg=ROOT.TLegend(0.15, 0.55, 0.65, 0.85, '#splitline{%s}{%s} #splitline{%s}{chi2/nDof = %.1f/9}'%(phoetaregion,jetetaregion,phoptregion, chi2Val) )
        Nsig=self.var( naming('num_sig') )
        Nbkg=self.var( naming('num_bkg') )
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



def DrawFitRes( figname, space, dataset, fitres, canv=ROOT.TCanvas('','',1200,1000)):
    canv.cd()
    var=space.var(fitres['var'])
    pdf_all=space.pdf(fitres['fitpdf'])

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

    plotComponent(pdf_all, xframe, space.pdf(fitres['components'][1]), name='bkg',
            fillcolor=42, fillstyle=1001, drawopt='f'
            )
    plotComponent(pdf_all, xframe, space.pdf(fitres['components'][0]), name='sig',
            linewidth=7, linecolor=46, drawopt='l'
            )
    dataset.plotOn(xframe, ROOT.RooFit.MarkerSize(2))
    xframe.Draw()

    phoetaregion='|#eta^{#gamma}|<1.4442' if PHOETABIN==0 else '1.566<|#eta^{#gamma}|<2.5'
    jetetaregion='|#eta^{jet}|<1.4442' if JETETABIN==0 else '1.566<|#eta^{jet}|<2.5'
    phoptregion='%d < p^{#gamma}_{T} < %d' % (PHOPT_RANGE[PHOPTBIN],PHOPT_RANGE[PHOPTBIN+1])
    leg=ROOT.TLegend(0.15, 0.55, 0.65, 0.85, '#splitline{%s}{%s} #splitline{%s}{chi2/nDof = %.1f/9}'%(phoetaregion,jetetaregion,phoptregion, chi2Val) )
    Nsig=space.var( naming('num_sig') )
    Nbkg=space.var( naming('num_bkg') )
    leg.AddEntry( dataset, 'Data', 'p')
    leg.AddEntry( xframe.findObject('sig'), '#splitline{signal photon}{ = %.1f #pm %.1f}'%(Nsig.getVal(),Nsig.getError()), 'l' )
    leg.AddEntry( xframe.findObject('fitpdf'), 'Fitting', 'f' )
    leg.AddEntry( xframe.findObject('bkg'), '#splitline{fake photon}{ = %.1f #pm %.1f}'%(Nbkg.getVal(),Nbkg.getError()), 'f' )

    leg.SetBorderSize(0)
    leg.SetNColumns(2)
    leg.SetTextAlign(32)
    leg.Draw()

    print 'fitting quality : chi2/nDof = %.3f / %s = %.3f' % ( chi2Val, '10-2', chi2Val/8 )
    canv.Update()
    canv.SaveAs(figname)
''' checking '''
def DrawFitSource( figname, space, datasets, fitres, canv=ROOT.TCanvas('c0','',1200,1000)):
    canv.cd()
    var=space.var(fitres['var'])
    pdf_all=space.pdf(fitres['fitpdf'])

    xframe=var.frame()
    xframe.SetTitle('')
    xframe.SetMaximum( xframe.GetMaximum() * 1.5 )

    '''
    plotComponent(pdf_all, xframe, space.pdf(fitres['components'][1]), name='bkg',
            fillcolor=42, fillstyle=1001, drawopt='f'
            )
    '''
    plotComponent(pdf_all, xframe, space.pdf(fitres['components'][0]), name='sig',
            linewidth=7, linecolor=46, drawopt='l'
            )
    datasets['sig'].plotOn(xframe, ROOT.RooFit.Name('sigSource'), ROOT.RooFit.MarkerSize(2))
    #chi2Val=xframe.chiSquare()
    xframe.Draw()

    phoetaregion='|#eta^{#gamma}|<1.4442' if PHOETABIN==0 else '1.566<|#eta^{#gamma}|<2.5'
    jetetaregion='|#eta^{jet}|<1.4442' if JETETABIN==0 else '1.566<|#eta^{jet}|<2.5'
    phoptregion='%d < p^{#gamma}_{T} < %d' % (PHOPT_RANGE[PHOPTBIN],PHOPT_RANGE[PHOPTBIN+1])
    leg=ROOT.TLegend(0.15, 0.55, 0.65, 0.85, '#splitline{%s}{%s} #splitline{%s}{chi2/nDof = %.1f/9}'%(phoetaregion,jetetaregion,phoptregion, chi2Val) )
    Nsig=space.var( naming('num_sig') )
    #Nbkg=space.var( naming('num_bkg') )
    leg.AddEntry( datasets['sig'], 'Fake sample sig', 'p')
    #leg.AddEntry( datasets['bkg'], 'Fake sample bkg', 'p')
    leg.AddEntry( xframe.findObject('sig'), '#splitline{signal photon}{ = %.1f #pm %.1f}'%(Nsig.getVal(),Nsig.getError()), 'l' )
    #leg.AddEntry( xframe.findObject('bkg'), '#splitline{fake photon}{ = %.1f #pm %.1f}'%(Nbkg.getVal(),Nbkg.getError()), 'f' )

    leg.SetBorderSize(0)
    leg.SetNColumns(2)
    leg.SetTextAlign(32)
    leg.Draw()

    print 'fitting quality : chi2/nDof = %.3f / %s = %.3f' % ( chi2Val, '10-2', chi2Val/8 )
    canv.Update()
    canv.SaveAs(figname)
''' checked '''

#asdf
def pulling(space, pdf_all, var, canv=ROOT.TCanvas('c2','',1200,1000)):
    canv.cd()
    space.myImport(pdf_all)
    params=pdf_all.getParameters(ROOT.RooArgSet(var))
    param_init=space.mySaveSnapShot('fitres', params)
    SIGRATIO=(pdf_sig.num.getVal()/(pdf_sig.num.getVal()+pdf_bkg.num.getVal()))

    pullhist=MakePullHist(SIGRATIO,space)
    pullhist.Fit('gaus')
    pullhist.Draw()
    canv.SaveAs('pullCheck2.pdf')



    space.myWriteSpace('tmpout.root')

PHOPTBIN=0
PHOETABIN=0
JETETABIN=0
def setbinning(phoeta, jeteta, phopt):
    PHOPTBIN=phopt
    PHOETABIN=phoeta
    JETETABIN=jeteta
def naming(name):
    return '%s.%d_%d_%d'%(name,PHOETABIN,JETETABIN,PHOPTBIN)
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

    LogMgr.InitLogger(level='debug')
    mylog=LogMgr.GetLogger(__name__)
    ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.ERROR)
    infile=ROOT.TFile.Open('isovsbdt_template.root')
    #space=MyWorkspace()
    space=FittingWorkspace()

    space.factory('BDTscore[-1.,1.]')
    var=space.var('BDTscore')
    space.SetVar('BDTscore')

    canv=ROOT.TCanvas('canv','',1200,1000)
    canv.SetFillStyle(4000)
    canv.SetFillColor(4000)

    for phoeta in range(2):
        for jeteta in range(2):
            for phopt in range(21):
                mylog.debug('indexes are pEta:%d jEta:%d pPt:%d' % (phoeta,jeteta,phopt) )
                PHOPTBIN=phopt
                PHOETABIN=phoeta
                JETETABIN=jeteta
                sigbin=MyBin(phopt, phoeta, jeteta)
                bkgpt = phopt if phopt < 17 else 17
                bkgbin=MyBin(bkgpt, phoeta, jeteta)

                mylog.debug( 'status 01: Loading hists from file.' )
                h_data=infile.Get('data_%d_%d_%d_px1_chIso'%(phoeta,jeteta,phopt))
                h_sig =infile.Get('gjet_%d_%d_%d_px1_chIso'%(phoeta,jeteta,phopt))

                exphoptbin= phopt if phopt < 17 else 17
                h_bkg =infile.Get('data_%d_%d_%d_px2_chIso'%(phoeta,jeteta,exphoptbin))
                if h_data.GetNbinsX() > 10 : h_data.Rebin(10)
                if h_sig .GetNbinsX() > 10 : h_sig.Rebin(10)
                if h_bkg .GetNbinsX() > 10 : h_bkg.Rebin(10)

                mylog.debug( 'status 03: Creating datasets and entries of %s is %d' % (h_bkg.GetName(), h_bkg.GetEntries()) )
                fitsources_data=ROOT.RooDataHist( naming('dh_data'), '', ROOT.RooArgList(var), h_data)
                space.myImport( fitsources_data )
                space.SetFitTarget( fitsources_data )
                mylog.debug( 'status 03.1: Get data %s'% fitsources_data.GetName() )
                mylog.debug( 'status 03.2: Get data2 %s'% space.data(fitsources_data.GetName()).GetName() )
                fitsources_sig =ROOT.RooDataHist( naming('dh_sig' ), '', ROOT.RooArgList(var), h_sig )
                fitsources_bkg =ROOT.RooDataHist( naming('dh_bkg' ), '', ROOT.RooArgList(var), h_bkg )

                mylog.debug( 'status 04: To fitting function' )
                mylog.debug( 'status 04.1: Find hist name %s'% infile.Get( sigbin.naming('gjet_%d_%d_%d_px1_chIso') ) ),
                mylog.debug( 'status 04.2: Find hist name %s'% infile.Get( bkgbin.naming('data_%d_%d_%d_px2_chIso') ) ),
                pdfnames=space.TwoComponentsFit( sigbin,
                        infile.Get( sigbin.naming('gjet_%d_%d_%d_px1_chIso') ),
                        infile.Get( bkgbin.naming('data_%d_%d_%d_px2_chIso') ),
                        )
                mylog.debug( 'status 05: Fitted, drawing output plots' )
                space.DrawFitRes( sigbin.naming('plots/checking_%d_%d_%d.pdf'),pdfnames )
                #  if isFake:
                #      dhdict={
                #              'sig': ROOT.RooDataHist( naming('dh_sigTruth'), '', ROOT.RooArgList(var),
                #                  sigFraFile.Get('gjet_%d_%d_%d_px1_chIso'%(PHOETABIN,JETETABIN,PHOPTBIN))),
                #              'bkg': ROOT.RooDataHist( naming('dh_bkgTruth'), '', ROOT.RooArgList(var),
                #                  bkgFraFile.Get('data_%d_%d_%d_px1_chIso'%(PHOETABIN,JETETABIN,PHOPTBIN))),
                #              }
                #      DrawFitSource('plots/checking_%d_%d_%d.pdf'%(phoeta,jeteta,phopt),
                #              space, fitsources_data, pdfnames, canv)
                mylog.debug( 'status ended: Binning fitted.' )
    mylog.info('start writing fit fragments to root file')
    space.myWriteSpace('fitres_workspace.root')
    del space
    mylog.info('job finished')

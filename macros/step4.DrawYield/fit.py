#!/usr/bin/env python2
import ROOT

PHOPT_RANGE=[25,34,40,55,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000,1500,2000,3000,10000]

'''
class FitSources(object):
    def __init__(self, prefix, xvar):
        self._prefix=prefix
        self.hist_target=None
        self.hist_templates={'sig':None, 'bkg':None}
        self.xvar=xvar
        self.datahists={'sig':None, 'bkg':None, 'trg':None}
    def SetHistTemplate(self, name,hist):
        if not name in self.hist_templates: raise KeyError('SetTemplate() : input key "%s" is invalid'%name)
        self.hist_templates[name]=hist
    def SetHistTarget(self, hist):
        self.hist_target=hist
    def MakeDataHist(self, externalworkspace=None):
        self.datahists['trg']=ROOT.RooDataHist(self._prefix+'_dh_trg','', ROOT.RooArgList(self.xvar), self.hist_target)
        self.datahists['sig']=ROOT.RooDataHist(self._prefix+'_dh_sig','', ROOT.RooArgList(self.xvar), self.hist_templates['sig'])
        self.datahists['bkg']=ROOT.RooDataHist(self._prefix+'_dh_bkg','', ROOT.RooArgList(self.xvar), self.hist_templates['bkg'])

    def __setitem__(self, key, val):
        raise KeyError('FitSources::__setitem__(): additional item is not available')
    def __getitem__(self, key):
        if key in self.datahists: return self.datahists[key]
        raise KeyError('input key "%s" not found'%key)

    def iteritems(self):
        if len(self)==0:self.MakeDataHist()
        return self.datahists.iteritems()
    def __len__(self):
        return int( sum([1 for val in self.datahists.values() if val]) )
    '''

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



def TwoComponentsFit(space, varname,
        datahist_data,datahist_sig,datahist_bkg,
        ):
    var=space.var(varname)
    INIT_SIGFRAC=0.7

    allnum=h_data.GetEntries()
    pdf_sig=PDFComponent(
            ROOT.RooHistPdf( naming('pdf_sig'), '', ROOT.RooArgSet(var), datahist_sig, 0),
            ROOT.RooRealVar( naming('num_sig'), '', allnum*INIT_SIGFRAC, 0., allnum)
            )
    pdf_bkg=PDFComponent(
            ROOT.RooHistPdf( naming('pdf_bkg'), '', ROOT.RooArgSet(var), datahist_bkg, 0),
            ROOT.RooRealVar( naming('num_bkg'), '', allnum*INIT_SIGFRAC, 0., allnum)
            )
    pdf_all=ROOT.RooAddPdf( naming('fitpdf'), '', ROOT.RooArgList(pdf_sig.Extended(),pdf_bkg.Extended()) )

    pdf_all.fitTo(datahist_data, ROOT.RooFit.PrintLevel(-1))
    space.myImport(pdf_all)

    print '-----------------------------------------------------'
    print 'Data %5.1f events, and %5.1f fitted'%( datahist_data.sumEntries(), (pdf_sig.num.getVal()+pdf_bkg.num.getVal()) )
    print 'ptbin %d  etabin %d  jetbin %d SIG %5.1f #pm %5.1f events'% ( PHOPTBIN,PHOETABIN,JETETABIN, pdf_sig.num.getVal(), pdf_sig.num.getError() )
    print 'ptbin %d  etabin %d  jetbin %d BKG %5.1f #pm %5.1f events'% ( PHOPTBIN,PHOETABIN,JETETABIN, pdf_bkg.num.getVal(), pdf_bkg.num.getError() )


    return {'fitpdf': pdf_all.GetName(), 'components':[pdf_sig.GetName(), pdf_bkg.GetName()], 'var': varname}



def DrawFitRes( figname, space, dataset, fitres, canv=ROOT.TCanvas('c0','',1200,1000)):
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

#asdf
def pulling(space, pdf_all, var, canv=ROOT.TCanvas('c2','',1200,1000)):
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

if __name__ == '__main__':
    ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.ERROR)
    infile=ROOT.TFile.Open('isovsbdt_template.root')
    space=MyWorkspace()

    space.factory('BDTscore[-1.,1.]')
    var=space.var('BDTscore')

    canv=ROOT.TCanvas('canv','',1200,1000)
    canv.SetFillStyle(4000)
    canv.SetFillColor(4000)
    for phoeta in range(2):
        for jeteta in range(2):
            for phopt in range(21):
                PHOPTBIN=phopt
                PHOETABIN=phoeta
                JETETABIN=jeteta

                h_data=infile.Get('data_%d_%d_%d_px1_chIso'%(phoeta,jeteta,phopt))
                h_sig =infile.Get('gjet_%d_%d_%d_px1_chIso'%(phoeta,jeteta,phopt))
                #h_bkg =infile.Get('data_%d_%d_%d_px2_chIso'%(phoeta,jeteta,phopt))
                exphoptbin= phopt if phopt < 17 else 17
                h_bkg =infile.Get('data_%d_%d_%d_px2_chIso'%(phoeta,jeteta,exphoptbin))
                if h_data.GetNbinsX() > 10 : h_data.Rebin(10)
                if h_sig .GetNbinsX() > 10 : h_sig.Rebin(10)
                if h_bkg .GetNbinsX() > 10 : h_bkg.Rebin(10)

                fitsources_data=ROOT.RooDataHist( naming('dh_data'), '', ROOT.RooArgList(var), h_data)
                fitsources_sig =ROOT.RooDataHist( naming('dh_sig' ), '', ROOT.RooArgList(var), h_sig )
                fitsources_bkg =ROOT.RooDataHist( naming('dh_bkg' ), '', ROOT.RooArgList(var), h_bkg )

                pdfnames=TwoComponentsFit(space, 'BDTscore',
                        datahist_data=fitsources_data,
                        datahist_sig =fitsources_sig,
                        datahist_bkg =fitsources_bkg,
                        )
                DrawFitRes('plots/check_%d_%d_%d.pdf'%(phoeta,jeteta,phopt),
                        space, fitsources_data, pdfnames, canv)
    space.myWriteSpace('fitres_workspace.root')

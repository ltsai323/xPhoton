#!/usr/bin/env python2
import ROOT
SIGFRAC=0.7

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
    '''
    def ExportTo(externalworkspace, storexvar=False):
        if storexvar:
            getattr(externalworkspace,'import')(self.xvar)
        for datahist in self.datahists.values():
            getattr(externalworkspace,'import')(datahist)
            '''

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
    def GetComponentName(self):
        return self.extpdf.GetName()
def plotComponent(name, fitpdf, frame, pdfcomponent,
        linewidth=4, linecolor=2, fillcolor=4000,fillstyle=4000):
    fitpdf.plotOn(frame,
            ROOT.RooFit.Components( pdfcomponent.GetComponentName() ),
            ROOT.RooFit.Name(name),
            ROOT.RooFit.LineWidth(linewidth),
            ROOT.RooFit.LineColor(linecolor),
            ROOT.RooFit.FillStyle(fillstyle),
            ROOT.RooFit.FillColor(fillcolor),
            ROOT.RooFit.DrawOption("F"),
            )

def MakePull(
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
    h_pull=ROOT.TH1F('pull', 'pull distribution', 100, -10.,10.)
    for i in range(pullloop):
        space.myLoadSnapShot('fitres')


        pdf=space.pdf('fitpdf')
        toydata=pdf.generate( ROOT.RooArgSet(var), randoms.Poisson(genevt))
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
'''
class MyWorkspace(object):
    def __init__(self):
        #self._____tmpfile=ROOT.TFile('/tmp/hi.root','recreate')

        self.space=ROOT.RooWorkspace('space',False)
    def Import(self, obj):
        getattr(self.space, 'import')(obj)
    def SaveSnapShot(self, name, pars):
        self.space.saveSnapshot(name, pars, True)
    def LoadSnapShot(self, snapshot):
        self.space.loadSnapshot(snapshot)
    def WriteSpace(self, oname):
        outputfile=ROOT.TFile(oname,'recreate')
        outputfile.cd()
        self.space.Write()
        outputfile.Close()
        print 'workspace is stored at %s'%oname
'''


if __name__ == '__main__':
    infile=ROOT.TFile.Open('isovsbdt_template.root')

    h_data=infile.Get('data_0_0_8_px1_chIso')
    h_sig =infile.Get('gjet_0_0_8_px1_chIso')
    h_bkg =infile.Get('data_0_0_8_px2_chIso')
    h_data.Rebin(10)
    h_sig.Rebin(10)
    h_bkg.Rebin(10)


    space=MyWorkspace()
    var=ROOT.RooRealVar('x', 'x', -1., 1., 'BDT output')
    space.myImport(var)

    fitsources=FitSources('hi', var)
    fitsources.SetHistTarget(h_data)
    fitsources.SetHistTemplate('sig', h_sig)
    fitsources.SetHistTemplate('bkg', h_bkg)
    fitsources.MakeDataHist()

    allnum=h_data.GetEntries()
    pdf_sig=PDFComponent(
            ROOT.RooHistPdf('pdf_sig', '', ROOT.RooArgSet(var), fitsources['sig'], 0),
            ROOT.RooRealVar('num_sig', '', allnum*SIGFRAC, 0., allnum)
            )
    pdf_bkg=PDFComponent(
            ROOT.RooHistPdf('pdf_bkg', '', ROOT.RooArgSet(var), fitsources['bkg'], 0),
            ROOT.RooRealVar('num_bkg', '', allnum*SIGFRAC, 0., allnum)
            )
    pdf_all=ROOT.RooAddPdf('fitpdf', '', ROOT.RooArgList(pdf_sig.Extended(),pdf_bkg.Extended()) )

    pdf_all.fitTo(fitsources['trg'])

    canv=ROOT.TCanvas('c1','', 1200,1000)
    xframe=var.frame()
    fitsources['trg'].plotOn(xframe)
    pdf_all.plotOn(xframe, ROOT.RooFit.Name('fitpdf'), ROOT.RooFit.LineColor(2))
    plotComponent('sig', pdf_all, xframe, pdf_sig,
            linewidth=1, linecolor=38, fillcolor=38, fillstyle=3002
            )
    plotComponent('bkg', pdf_all, xframe, pdf_bkg,
            linewidth=1, linecolor=30, fillcolor=2, fillstyle=3144
            )
    xframe.Draw()
    canv.SaveAs('plots/test_IfitEB_0_0_8.pdf')

    pulltest=True
    space.myImport(pdf_all)
    params=pdf_all.getParameters(ROOT.RooArgSet(var))
    param_init=space.mySaveSnapShot('fitres', params)
    SIGRATIO=(pdf_sig.num.getVal()/(pdf_sig.num.getVal()+pdf_bkg.num.getVal()))
    if pulltest:
        hhh=MakePull(SIGRATIO,space)
        hhh.Fit('gaus')
        hhh.Draw()
        canv.SaveAs('pullCheck2.pdf')



    space.myWriteSpace('tmpout.root')

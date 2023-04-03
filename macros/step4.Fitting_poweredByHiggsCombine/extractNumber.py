#!/usr/bin/env python3

def UpperPad():
    upperpad = ROOT.TPad('upperpad','upperpad',0.,0.245,1.,0.98)

    upperpad.SetTicks(1,1)
    upperpad.SetTopMargin(0.05)
    upperpad.SetBottomMargin(0.019)
    upperpad.SetLeftMargin(0.135)
    upperpad.SetRightMargin(0.06)
    return upperpad
def LowerPad():
    lowerpad = ROOT.TPad("lowerpad","lowerpad",0.,0.0,1.,0.258)

    lowerpad.SetTicks(1,1)
    lowerpad.SetTopMargin(0.0)
    lowerpad.SetBottomMargin(0.35)
    lowerpad.SetLeftMargin(0.135)
    lowerpad.SetRightMargin(0.06)
    return lowerpad
def MyCanvas():
    canv = ROOT.TCanvas('c1','',600,700)

    canv.SetFillColor(4000)
    canv.SetFillStyle(4000)
    return canv

def MyRatioPlot(rREALvar,rDATASET, rABSpdf, xTITLE, yTITLE):
    hNumerator = rDATASET.createHistogram('h_num', rREALvar, ROOT.RooFit.Binning(10))
    hNumerator.Sumw2(False)
    hNumerator.SetBinErrorOption(ROOT.TH1.kPoisson)
    hDenominator = rABSpdf.createHistogram('h_den',rREALvar, ROOT.RooFit.Binning(10))
    for ibin in range(1,11):
        print('ibin %d and dat pdf hist : %f and err %f' % (ibin,hNumerator  .GetBinContent(ibin), hNumerator  .GetBinError(ibin)) )
        print('ibin %d and abs pdf hist : %f and err %f' % (ibin,hDenominator.GetBinContent(ibin), hDenominator.GetBinError(ibin)) )

    hratioPlot = hNumerator.Clone()
    hratioPlot.Sumw2()
    hratioPlot.SetTitle('')
    hratioPlot.GetXaxis().SetTitleSize(0.11)
    hratioPlot.GetXaxis().SetLabelSize(0.11)
    hratioPlot.GetYaxis().SetTitleSize(0.11)
    hratioPlot.GetYaxis().SetLabelSize(0.11)
    hratioPlot.GetYaxis().SetTitleOffset(0.4)
    hratioPlot.GetYaxis().SetNdivisions(905)
    hratioPlot.GetYaxis().CenterTitle(True)
    hratioPlot.SetLineColor(ROOT.kBlack)
    hratioPlot.SetXTitle(xTITLE)
    hratioPlot.SetYTitle(yTITLE)
    hratioPlot.Divide(hNumerator,hDenominator,1.,1.)
    hratioPlot.SetMinimum(0.)
    hratioPlot.SetMaximum(2.)
    return hratioPlot
#TH1D* ratioPlot(TH1D* hNumerator, TH1D* hDenominator, string xTitle, string yTitle){
#
#    TH1D* hratioPlot = (TH1D*)hNumerator -> Clone();
#    hratioPlot -> GetXaxis()->SetTitleSize(0.11);
#    hratioPlot -> GetXaxis()->SetLabelSize(0.11);
#    hratioPlot -> GetYaxis()->SetTitleSize(0.11);
#    hratioPlot -> GetYaxis()->SetLabelSize(0.11); 
#    hratioPlot -> GetYaxis()->SetTitleOffset(0.4);
#    hratioPlot -> GetYaxis()->SetNdivisions(905);
#    hratioPlot -> GetYaxis()->CenterTitle(true);
#    hratioPlot -> SetLineColor(kBlack);
#    hratioPlot -> SetXTitle(Form("%s",xTitle.c_str()));
#    hratioPlot -> SetYTitle(Form("%s",yTitle.c_str()));
#    hratioPlot -> Divide(hNumerator,hDenominator,1.,1.);
#    hratioPlot -> SetMinimum(0.);
#    hratioPlot -> SetMaximum(2.);
#
#return hratioPlot;
#}


import ROOT
if __name__ == "__main__":
    ifile=ROOT.TFile.Open('higgsCombineTest.MultiDimFit.mH120.root')
    workspace=ifile.Get('w')
    workspace.loadSnapshot('MultiDimFit')

    mu1=workspace.var('mu1')
    mu2=workspace.var('mu2')
    shapeUnc=workspace.var('shapeUnc')

    print(mu1.getVal(), mu1.getError())
    print(mu2.getVal(), mu2.getError())

    var=workspace.var('CMS_th1x')

    totPDF=workspace.pdf('pdf_bincat_BDT_nuis')


    dataset=workspace.data('data_obs')
    sp = dataset.split(ROOT.RooCategory("CMS_channel", "") ) # return a TList
    for iCat in range(sp.GetSize()):
        print('category in idx %d : %s with entries %d'%(iCat,sp.At(iCat).GetName(), sp.At(iCat).sumEntries()))

    '''
    canv=MyCanvas()
    upperpad=UpperPad()
    lowerpad=LowerPad()
    upperpad.Draw()
    lowerpad.Draw()

    upperpad.cd()
    frame=var.frame()
    frame.GetXaxis().SetTitle('')
    frame.SetTitle('')
    dataset.plotOn(frame) # force frame plots in the corrected axis

    totPDF.plotOn(frame,ROOT.RooFit.Components('shapeBkg_bkgShape_cat_BDT_rebinPdf'),
            ROOT.RooFit.LineColor(31), ROOT.RooFit.LineWidth(2),
            ROOT.RooFit.FillColor(31), ROOT.RooFit.FillStyle(3004),
            ROOT.RooFit.DrawOption("F L")
            )
    totPDF.plotOn(frame, ROOT.RooFit.Components('shapeSig_cat_BDT_signalMC_morph'),
            ROOT.RooFit.LineColor(46), ROOT.RooFit.LineWidth(2),
            ROOT.RooFit.FillColor(46), ROOT.RooFit.FillStyle(3002),
            ROOT.RooFit.DrawOption("F L")
            )
    totPDF.plotOn(frame,
            ROOT.RooFit.LineColor(2), ROOT.RooFit.LineWidth(4),
            )
    dataset.plotOn(frame) # put data on the top
    frame.Draw()

    lowerpad.cd()
    ratioplot=MyRatioPlot(var,dataset,totPDF,'x','y')
    ratioplot.Draw()

    canv.SaveAs("hi.png")
    '''



#!/usr/bin/env python2
import ROOT
'''
canv=ROOT.TCanvas('c1','',1200,1000)
canv.SetFillColor(4000)
canv.SetFillStyle(4000)
canv.SetFrameFillStyle(4000)
canv.SetFrameFillColor(4000)
'''
def CloneVisualization(source,target):
    target.SetFillColor( source.GetFillColor() )
    target.SetFillStyle( source.GetFillStyle() )
    target.SetLineColor( source.GetLineColor() )
    target.SetLineStyle( source.GetLineStyle() )
    target.SetMarkerColor( source.GetMarkerColor() )
    target.SetMarkerStyle( source.GetMarkerStyle() )
def drawrratios(targethist, compdict, output):
    hdata=targethist
    hists=[ hist for hist in compdict.keys() ]
    hopts=[ compdict[hist] for hist in hists ]

    ratioplots=[ ROOT.TRatioPlot(hdata,hist) for hist in hists ]
    for ratioplot in ratioplots:
        lines=ROOT.std.vector('double')()
        lines+=[1.]
        ratioplot.SetGridlines(lines)
        ratioplot.Draw()
    lowergraphs=[ ratioplot.GetLowerRefGraph() for ratioplot in ratioplots ]
    [ CloneVisualization(source=hist, target=graph) for hist,graph in zip(hists,lowergraphs) ]
    for graph in lowergraphs:
        graph.SetMinimum(0.5)
        graph.SetMaximum(1.5)

    ratioplots[0].Draw()
    ratioplots[0].GetLowYaxis().SetNdivisions(505)
    ratioplots[0].GetXaxis().SetTitle('jjjjjj')
    ratioplots[0].GetXaxis().SetTitleSize(0)
    ratioplots[0].GetLowerRefYaxis().SetTitle('Data/MC')
    ratioplots[0].GetUpperRefYaxis().SetTitle('Entries')

    upperpad=ratioplots[0].GetUpperPad()
    lowerpad=ratioplots[0].GetLowerPad()
    upperpad.SetFillColor(4000)
    upperpad.SetFillStyle(4000)
    lowerpad.SetFillColor(4000)
    lowerpad.SetFillStyle(4000)

    #canv.Clear()
    canv.cd()
    upperpad.Draw()
    upperpad.cd()
    [ hist.Draw('same hist') for hist in hists ]
    hdata.Draw('same p')

    leg=ROOT.TLegend( 0.20, 0.70, 0.75, 0.85, 'nVtx', 'NDC' )
    [ leg.AddEntry(hist, hopt, 'l') for hist,hopt in zip(hists,hopts) ]
    leg.AddEntry(hdata, 'data', 'e')
    leg.Draw()

    canv.cd()
    lowerpad.Draw()
    lowerpad.cd()
    [ graph.Draw('p') for graph in lowergraphs ]

    canv.Update()
    canv.SaveAs(output)
def drawNVtx_barrel( tsimu, tdata ):
    etaCut='fabs(recoEta) < 1.4442'
    #tsimu.Draw('nVtx>>hcalb', 'mcweight*puwei * (%s)'%etaCut)
    #tsimu.Draw('nVtx>>horig', 'mcweight*%s' % etaCut)
    tsimu.Draw('nVtx>>hcalb', 'puwei * (%s)'%etaCut)
    tsimu.Draw('nVtx>>horig', '%s' % etaCut)
    tdata.Draw('nVtx>>hdata', '%s' % etaCut)
def drawNVtx_endcap( tsimu, tdata ):
    etaCut='fabs(recoEta) > 1.566 && fabs(recoEta) < 2.5'
    #tsimu.Draw('nVtx>>hcalb', 'mcweight*puwei * (%s)'%etaCut)
    #tsimu.Draw('nVtx>>horig', 'mcweight*%s' % etaCut)
    tsimu.Draw('nVtx>>hcalb', 'puwei * (%s)'%etaCut)
    tsimu.Draw('nVtx>>horig', '%s' % etaCut)
    tdata.Draw('nVtx>>hdata', '%s' % etaCut)
def drawRho_barrel( tsimu, tdata ):
    etaCut='fabs(recoEta) < 1.4442'
    tsimu.Draw('nVtx>>hcalb', 'mcweight*puwei * (%s)'%etaCut)
    tsimu.Draw('nVtx>>horig', 'mcweight*%s' % etaCut)
    tdata.Draw('nVtx>>hdata', '%s' % etaCut)
def drawRho_endcap( tsimu, tdata ):
    etaCut='fabs(recoEta) > 1.566 && fabs(recoEta) < 2.5'
    tsimu.Draw('rho>>hcalb', 'mcweight*puwei * (%s)'%etaCut)
    tsimu.Draw('rho>>horig', 'mcweight*%s' % etaCut)
    tdata.Draw('rho>>hdata', '%s' % etaCut)
def drawNVtx_30bins_barrel( tsimu, tdata ):
    etaCut='fabs(recoEta) < 1.4442 && nVtx < 31'
    #tsimu.Draw('nVtx>>hcalb', 'mcweight*puwei * (%s)'%etaCut)
    #tsimu.Draw('nVtx>>horig', 'mcweight*%s' % etaCut)
    tsimu.Draw('nVtx>>hcalb', 'puwei * (%s)'%etaCut)
    tsimu.Draw('nVtx>>horig', '%s' % etaCut)
    tdata.Draw('nVtx>>hdata', '%s' % etaCut)
def drawNVtx_30bins_endcap( tsimu, tdata ):
    etaCut='fabs(recoEta) > 1.566 && fabs(recoEta) < 2.5 && nVtx < 31'
    #tsimu.Draw('nVtx>>hcalb', 'mcweight*puwei * (%s)'%etaCut)
    #tsimu.Draw('nVtx>>horig', 'mcweight*%s' % etaCut)
    tsimu.Draw('nVtx>>hcalb', 'puwei * (%s)'%etaCut)
    tsimu.Draw('nVtx>>horig', '%s' % etaCut)
    tdata.Draw('nVtx>>hdata', '%s' % etaCut)

def DrawRho(funcTreeDrawing_, outputName):
    import sys
    fsimu=ROOT.TFile.Open(sys.argv[1])
    fdata=ROOT.TFile.Open('/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root')
    tsimu=fsimu.Get('t')
    tdata=fdata.Get('t')


    hcalb=ROOT.TH1F('hcalb','',75,0.,75.)
    horig=ROOT.TH1F('horig','',75,0.,75.)
    hdata=ROOT.TH1F('hdata','',75,0.,75.)

    #tsimu.Draw('nVtx>>hcalb', 'puwei')
    #tsimu.Draw('nVtx>>horig')
    #tdata.Draw('nVtx>>hdata')
    funcTreeDrawing_( tsimu, tdata )

    scalingfunc=lambda hist: hist.Scale( float(sum([hdata.GetBinContent(ibin+1) for ibin in range(hdata.GetNbinsX())]) ) / float(sum([hist.GetBinContent(ibin+1) for ibin in range(hist.GetNbinsX())])) )
    scalingfunc(hcalb)
    scalingfunc(horig)

    maximum=hdata.GetMaximum() * 1.5
    hdata.SetMaximum( maximum )
    hcalb.SetMaximum( maximum )
    horig.SetMaximum( maximum )

    hdata.GetXaxis().SetTitle('rho')
    hcalb.GetXaxis().SetTitle('rho')
    horig.GetXaxis().SetTitle('rho')


    horig.SetLineColor(3)
    hcalb.SetLineColor(2)

    drawrratios(
            hdata,
            { hcalb: 'calibrated MC', horig: 'original MC' },
            output=outputName
            )
def DrawNumPV(funcTreeDrawing_, outputName):
    import sys
    fsimu=ROOT.TFile.Open(sys.argv[1])
    fdata=ROOT.TFile.Open('/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root')
    tsimu=fsimu.Get('t')
    tdata=fdata.Get('t')


    hcalb=ROOT.TH1F('hcalb','',75,0.,75.)
    horig=ROOT.TH1F('horig','',75,0.,75.)
    hdata=ROOT.TH1F('hdata','',75,0.,75.)

    #tsimu.Draw('nVtx>>hcalb', 'puwei')
    #tsimu.Draw('nVtx>>horig')
    #tdata.Draw('nVtx>>hdata')
    funcTreeDrawing_( tsimu, tdata )

    scalingfunc=lambda hist: hist.Scale( float(sum([hdata.GetBinContent(ibin+1) for ibin in range(hdata.GetNbinsX())]) ) / float(sum([hist.GetBinContent(ibin+1) for ibin in range(hist.GetNbinsX())])) )
    scalingfunc(hcalb)
    scalingfunc(horig)

    maximum=hdata.GetMaximum() * 1.5
    hdata.SetMaximum( maximum )
    hcalb.SetMaximum( maximum )
    horig.SetMaximum( maximum )

    hdata.GetXaxis().SetTitle('nVtx')
    hcalb.GetXaxis().SetTitle('nVtx')
    horig.GetXaxis().SetTitle('nVtx')


    horig.SetLineColor(3)
    hcalb.SetLineColor(2)

    drawrratios(
            hdata,
            { hcalb: 'calibrated MC', horig: 'original MC' },
            output=outputName
            )
def DrawNumPV_30bins(funcTreeDrawing_, outputName):
    import sys
    fsimu=ROOT.TFile.Open(sys.argv[1])
    fdata=ROOT.TFile.Open('/home/ltsai/ReceivedFile/GJet/latestsample/Run2016_Legacy.root')
    tsimu=fsimu.Get('t')
    tdata=fdata.Get('t')


    hcalb=ROOT.TH1F('hcalb','',30,0.,30.)
    horig=ROOT.TH1F('horig','',30,0.,30.)
    hdata=ROOT.TH1F('hdata','',30,0.,30.)

    #tsimu.Draw('nVtx>>hcalb', 'puwei')
    #tsimu.Draw('nVtx>>horig')
    #tdata.Draw('nVtx>>hdata')
    funcTreeDrawing_( tsimu, tdata )

    scalingfunc=lambda hist: hist.Scale( float(sum([hdata.GetBinContent(ibin+1) for ibin in range(hdata.GetNbinsX())]) ) / float(sum([hist.GetBinContent(ibin+1) for ibin in range(hist.GetNbinsX())])) )
    scalingfunc(hcalb)
    scalingfunc(horig)

    maximum=hdata.GetMaximum() * 1.5
    hdata.SetMaximum( maximum )
    hcalb.SetMaximum( maximum )
    horig.SetMaximum( maximum )

    hdata.GetXaxis().SetTitle('nVtx')
    hcalb.GetXaxis().SetTitle('nVtx')
    horig.GetXaxis().SetTitle('nVtx')


    horig.SetLineColor(3)
    hcalb.SetLineColor(2)

    drawrratios(
            hdata,
            { hcalb: 'calibrated MC', horig: 'original MC' },
            output=outputName
            )
if __name__ == '__main__':
    #DrawNumPV(drawNVtx_barrel, 'ratio_barrel.png')
    #DrawNumPV(drawNVtx_endcap, 'ratio_endcap.png')
    #DrawRho(drawRho_barrel, 'ratio_barrel.png')
    #DrawRho(drawRho_endcap, 'ratio_endcap.png')
    canv=ROOT.TCanvas('c1','',1200,1000)
    canv.SetFillColor(4000)
    canv.SetFillStyle(4000)
    canv.SetFrameFillStyle(4000)
    canv.SetFrameFillColor(4000)
    DrawNumPV_30bins(drawNVtx_30bins_barrel, 'ratio_barrel.png')
    DrawNumPV_30bins(drawNVtx_30bins_endcap, 'ratio_endcap.png')

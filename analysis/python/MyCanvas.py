#!/usr/bin/env python2

import ROOT
isTransparent = False
def LOG(*args):
    print('[MyCanvas-LOG] ', *args)
def Pad(name='pad'):
    #pad=ROOT.TPad(name, name, 0., 0.245, 1., 0.98)
    pad=ROOT.TPad(name, name, 0., 0.175, 1., 0.98)
    pad.SetTicks(1,1)
    pad.SetTopMargin(0.04464108)
    #pad.SetBottomMargin(0.10)
    pad.SetLeftMargin(0.1340582)
    pad.SetRightMargin(0.06)
    Transparent(pad, isTransparent)
    return pad
def UpperPad(name='upperpad', xRANGE=(0.,1.)):
    pad=ROOT.TPad(name, name, xRANGE[0], 0.245, xRANGE[1], 0.98)
    pad.SetTicks(1,1)
    pad.SetTopMargin(0.05)
    pad.SetBottomMargin(0.019)
    pad.SetLeftMargin(0.135)
    pad.SetRightMargin(0.06)
    Transparent(pad, isTransparent)
    return pad
def LowerPad(name='lowerpad', xRANGE=(0.,1.)):
    pad=ROOT.TPad(name, name, xRANGE[0],0.,xRANGE[1],0.258)
    pad.SetTicks(1,1)
    pad.SetTopMargin(0.0)
    pad.SetBottomMargin(0.35)
    pad.SetLeftMargin(0.135)
    pad.SetRightMargin(0.06)
    Transparent(pad, isTransparent)
    return pad
def Transparent(pad, isTransparent:bool):
    if isTransparent:
        pad.SetFillColor(4000)
        pad.SetFillStyle(4000)
class MyCanvas(ROOT.TCanvas):
    def __init__(self, name='canv', width=1200, height=1000):
        super(MyCanvas,self).__init__(name,name, width, height)

        self.upperpad = UpperPad()
        self.upperpad.Draw()
        self.lowerpad = LowerPad()
        self.lowerpad.Draw()
    def Transparent(self, isTransparent:bool):
        if isTransparent:
            Transparent(self, True)
            Transparent(self.upperpad, True)
            Transparent(self.lowerpad, True)
        else:
            Transparent(self, False)
            Transparent(self.upperpad, False)
            Transparent(self.lowerpad, False)

def MyRatioCanvasSetup(width=800, height=900):
    ## half of 16:9 = 8:9
    canv = ROOT.TCanvas('c1','', width, height)
    Transparent(canv, isTransparent)

    upperpad = UpperPad()
    Transparent(upperpad, isTransparent)

    lowerpad = LowerPad()
    Transparent(lowerpad, isTransparent)

    canv.cd()
    upperpad.Draw()
    lowerpad.Draw()
    return (canv, upperpad, lowerpad)
def MassiveRatioCanvasSetup(numRATIOplot=4):
    width1=800
    height1=900
    ## half of 16:9 = 8:9
    canv = ROOT.TCanvas('c1','', width1*numRATIOplot, height1)
    Transparent(canv, isTransparent)

    xSep = 1. / float(numRATIOplot)
    xRangeL = [ round(xSep *  idx   ,2) for idx in range(numRATIOplot) ]
    xRangeR = [ round(xSep * (idx+1),2) for idx in range(numRATIOplot) ]
    LOG(f'massive TPad xRangeL = {xRangeL}')
    LOG(f'massive TPad xRangeR = {xRangeR}')

    canv.cd()
    outPads = [None]*numRATIOplot
    for idx, x_range in enumerate(zip(xRangeL,xRangeR)):
        upperpad = UpperPad(name=f'upperpad{idx}', xRANGE=x_range)
        Transparent(upperpad, isTransparent)

        lowerpad = LowerPad(name=f'lowerpad{idx}', xRANGE=x_range)
        Transparent(lowerpad, isTransparent)

        upperpad.Draw()
        lowerpad.Draw()
        outPads[idx] = (upperpad,lowerpad)
    return (canv, outPads)
def MyCanvasSetup(width=800, height=900):
    ## half of 16:9 = 8:9
    canv = ROOT.TCanvas('c1','', width, height)
    Transparent(canv, isTransparent)

    pad = Pad()
    Transparent(pad, isTransparent)

    canv.cd()
    pad.Draw()
    return (canv, pad)


if __name__ == '__main__':
    canv=MyCanvas()

    h=ROOT.TH1F('h','',10,0.,1.)
    h.Fill(0.8)
    h.Draw()
    canv.SaveAs('k.pdf')

    canv, upperpad, lowerpad = MyRatioCanvasSetup()


#!/usr/bin/env python2

import ROOT
class MyCanvas(ROOT.TCanvas):
    def __init__(self, name='canv', width=1200, height=1000):
        super(MyCanvas,self).__init__(name,name, width, height)
        self.SetFillColor(4000)
        self.SetFillStyle(4000)


if __name__ == '__main__':
    canv=MyCanvas()

    h=ROOT.TH1F('h','',10,0.,1.)
    h.Fill(0.8)
    h.Draw()
    canv.SaveAs('k.pdf')



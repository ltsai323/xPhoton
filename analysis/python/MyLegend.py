#!/usr/bin/env python2

import ROOT
class MyLegend(ROOT.TLegend):
    def __init__(self, p0=(0.0,0.0), p1=(1.0,1.0)):
        super(MyLegend,self).__init__(p0[0],p0[1],p1[0],p1[1])
        self.SetFillColor(4000)
        self.SetFillStyle(4000)
        self.SetBorderSize(0)


if __name__ == '__main__':
    canv=ROOT.TCanvas('canv','',1200,1000)

    h=ROOT.TH1F('h','',10,0.,1.)
    h.Fill(0.8)
    h.Draw()
    leg=MyLegend( (0.2,0.2), (0.5,0.7) )
    leg.AddEntry(h, 'hiii', 'l')
    leg.Draw()
    canv.SaveAs('k.pdf')




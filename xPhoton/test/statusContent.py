import ROOT

def sethist(hist):
    hist.SetMaximum( hist.GetMaximum()*1.3 )
def SetNumber(hist):
    for idx in range(1,hist.GetNbinsX()+1):
        print hist.GetBinContent(idx)
def printPercentNumber(hevt,text):
    text.SetTextAlign(22)
    text.SetTextColor(46)
    totnum=sum( [hevt.GetBinContent(ibin) for ibin in range(1,hevt.GetNbinsX()+1)] )
    for ibin in range(1,hevt.GetNbinsX()+1):
        print float(ibin)-0.5
        text.DrawText( (float(ibin)-0.5),
                hevt.GetBinContent(ibin) + totnum*0.05,
                '{0:.1f}%'.format((hevt.GetBinContent(ibin)/totnum)*100)
                )
    return text
def printNumber(hevt,text):
    import locale
    locale.setlocale(locale.LC_ALL, 'en_US')
    text.SetTextAlign(22)
    text.SetTextColor(46)
    maxnum=max( [hevt.GetBinContent(ibin) for ibin in range(1,hevt.GetNbinsX()+1)] )
    for ibin in range(1,hevt.GetNbinsX()+1):
        print float(ibin)-0.5
        text.DrawText( (float(ibin)-0.5),
                hevt.GetBinContent(ibin) + maxnum*0.07,
                '{0:n}'.format(int(hevt.GetBinContent(ibin)))
                )
    return text

settingHIST=lambda hist: hist.SetMaximum( hist.GetMaximum()*1.3 )

def PrintHist(hevt,outname):
    settingHIST(hevt)
    SetNumber(hevt)

    hevt.Draw()
    text=ROOT.TText()
    printNumber(hevt,text)
    canv.SaveAs(outname)


if __name__ == '__main__':
    canv=ROOT.TCanvas('c1','',600,500)
    canv.SetFillStyle(4000);

    import sys
    f=ROOT.TFile.Open(sys.argv[1])
    outputtag=sys.argv[1].split('.')[0]

    for name in [ 'nEleMatched' ]:
        hist=f.Get(name)
        PrintHist(hist, 'record_%s_%s.pdf'%(outputtag,name))

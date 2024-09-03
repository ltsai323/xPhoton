#!/usr/bin/env python3
import ROOT



def HistFraming( h, xLABEL='', yLABEL='', minFACTOR = 0.1, maxFACTOR = 1.5 ):
    h.SetMinimum( h.GetMinimum() * minFACTOR)
    h.SetMaximum( h.GetMaximum() * maxFACTOR)
    h.GetXaxis().SetTitle(xLABEL)
    h.GetXaxis().SetTitleSize(0.05)
    h.GetXaxis().SetLabelSize(0.03)

    h.GetYaxis().SetTitle(yLABEL)
    #h.GetYaxis().SetTitleSize(0.11)
    h.GetYaxis().SetTitleSize(0.04)
    h.GetYaxis().SetTitleOffset(0.8)
    h.GetYaxis().SetLabelSize(0.03)
    h.GetYaxis().SetNdivisions(905)
    #h.GetYaxis().CenterTitle(True)
    #h.GetYaxis().SetMaxDigits(3)
    # h.SetStats(False)
    ROOT.TGaxis.SetMaxDigits(3)

def HistSetting_GeneralStyling_( hist_, xlabel_='', ylabel_=''):
    hist_.GetYaxis().SetRangeUser( 1e-1, hist_.GetMaximum()*1.5 )
    hist_.GetXaxis().SetTitle(xlabel_)
    hist_.GetXaxis().SetTitleSize(0.05)
    hist_.GetXaxis().SetLabelSize(0.03)

    hist_.GetYaxis().SetTitle(ylabel_)
    hist_.GetYaxis().SetTitleSize(0.11)
    hist_.GetYaxis().SetTitleOffset(0.4)
    hist_.GetYaxis().SetLabelSize(0.03)
    hist_.GetYaxis().SetNdivisions(905)
    #hist_.GetYaxis().CenterTitle(True)
    #hist_.GetYaxis().SetMaxDigits(3)
    ROOT.TGaxis.SetMaxDigits(3)

    hist_.SetStats(False)
def HistSetting_GeneralStyling( hist_, xlabel_='', ylabel_=''):
    HistSetting_UpperStyling(hist_,xlabel_,ylabel_)
def HistSetting_UpperStyling( hist_, xlabel_='', ylabel_=''):
    hist_.GetYaxis().SetRangeUser( 1e-1, hist_.GetMaximum()*1.5 )
    hist_.GetXaxis().SetTitle(xlabel_)
    hist_.GetXaxis().SetTitleSize(0.05)
    hist_.GetXaxis().SetLabelSize(0.03)

    hist_.GetYaxis().SetTitle(ylabel_)
    hist_.GetYaxis().SetTitleSize(0.06)
    hist_.GetYaxis().SetTitleOffset(0.6)
    hist_.GetYaxis().SetLabelSize(0.03)
    hist_.GetYaxis().SetNdivisions(905)
    #hist_.GetYaxis().CenterTitle(True)
    #hist_.GetYaxis().SetMaxDigits(3)
    ROOT.TGaxis.SetMaxDigits(3)

    hist_.SetStats(False)
def Styling(hist, **xargs):
    if 'title' in xargs: hist.SetTitle(xargs["title"])
    if 'titleSIZE' in xargs: hist.SetTitleSize(xargs["titleSIZE"])
    if 'titleOFFSET' in xargs: hist.SetTitleOffset(xargs["titleOFFSET"])

    if 'xTITLE' in xargs: hist.GetXaxis().SetTitle(xargs["xTITLE"])
    if 'xTITLEsize' in xargs: hist.GetXaxis().SetTitleSize(xargs["xTITLEsize"])
    if 'xTITLEoffset' in xargs: hist.GetXaxis().SetTitleOffset(xargs["xTITLEoffset"])
    if 'xLABELsize' in xargs: hist.GetXaxis().SetLabelOffset(xargs["xLABELsize"])
    if 'xLABELoffset' in xargs: hist.GetXaxis().SetLabelOffset(xargs["xLABELoffset"])
    if 'xDIV' in xargs: hist.GetXaxis().SetNdivisions(xargs["xDIV"])

    if 'yTITLE' in xargs: hist.GetYaxis().SetTitle(xargs["yTITLE"])
    if 'yTITLEsize' in xargs: hist.GetYaxis().SetTitleSize(xargs["yTITLEsize"])
    if 'yTITLEoffset' in xargs: hist.GetYaxis().SetTitleOffset(xargs["yTITLEoffset"])
    if 'yLABELsize' in xargs: hist.GetYaxis().SetLabelOffset(xargs["yLABELsize"])
    if 'yLABELoffset' in xargs: hist.GetYaxis().SetLabelOffset(xargs["yLABELoffset"])
    if 'yDIV' in xargs: hist.GetYaxis().SetNdivisions(xargs["yDIV"])

    if 'maxDIGIT' in xargs: ROOT.TGaxis.SetMaxDigits(xargs["maxDIGIT"])
    hist.SetStats(False)


def CloneVisualization( histTOFROM, histTO ):
    histTO.SetLineColor  ( histFROM.GetLineColor() )
    histTO.SetLineWidth  ( histFROM.GetLineWidth() )
    histTO.SetFillColor  ( histFROM.GetFillColor() )
    histTO.SetFillStyle  ( histFROM.GetFillStyle() )
    histTO.SetMarkerStyle( histFROM.GetMarkerStyle() )
    histTO.SetMarkerColor( histFROM.GetMarkerColor() )
    histTO.SetMarkerSize ( histFROM.GetMarkerSize()  )

def Visualization(hist, **xargs):
    setting = 'fillCOLOR'
    if 'fillCOLOR' in xargs: hist.SetFillColor(xargs["fillCOLOR"])
    if 'fillSTYLE' in xargs: hist.SetFillStyle(xargs["fillSTYLE"])
    if 'lineCOLOR' in xargs: hist.SetLineColor(xargs["lineCOLOR"])
    if 'lineWIDTH' in xargs: hist.SetLineWidth(xargs["lineWIDTH"])
    if 'lineSTYLE' in xargs: hist.SetLineStyle(xargs["lineSTYLE"])
    if 'markerCOLOR' in xargs: hist.SetMarkerColor(xargs["markerCOLOR"])
    if 'markerSIZE' in xargs: hist.SetMarkerSize(xargs["markerSIZE"])
    if 'title' in xargs: hist.SetTitle(xargs["title"])

    if 'xTITLE' in xargs: hist.GetXaxis().SetTitle(xargs["xLABEL"])
    if 'xRANGE' in xargs: hist.GetYaxis().SetRangeUser(*xargs["xRANGE"])

    if 'yTITLE' in xargs: hist.GetYaxis().SetTitle(xargs["yTITLE"])
    if 'yRANGE' in xargs: hist.GetYaxis().SetRangeUser(*xargs["yRANGE"])
def GetRange(hist, scale:str) -> tuple:
    if scale == 'linear':
        return (0.               , hist.GetMaximum() * 1.5)
    if scale == 'log':
        return (hist.GetMinumum(), hist.GetMaximum() * 1000.)
    raise IOError(f'[Invalid Input Argument] (scale={scale}) is invalid, Only accept "linear" and "log"')


if __name__ == "__main__":
    print('kk')

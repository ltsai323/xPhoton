#!/usr/bin/env python2
import ROOT

class RootObjFormatMgr(object):
    @staticmethod
    def CanvasStyler(canv):
        canv.SetFillColor(4000)
        canv.SetFillStyle(4000)
        #canv.SetFrameFillColor(4000)
        #canv.SetFrameFillStyle(4000)
    @staticmethod
    def HistogramStyler(hist, line=0, fill=0, marker=0):
        hist.SetStats(False)
    @staticmethod
    def AxisStyler(axis):
        pass
    @staticmethod
    def PadStyler(pad):
        pass
    @staticmethod
    def LineStyler(hist):
        pass
colorset_={
        0: 33,
        1: 38,
        2: 40,
        }

def GetColor(idx):
    return colorset_[idx]
def GetLineStyle(idx):
    return idx
#def GetMarkerStyle(j

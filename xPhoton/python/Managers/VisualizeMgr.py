#!/usr/bin/env python2
import ROOT

class LineSettingMgr(object):
    def __init__(self):
        self.width=None
        self.color=None

class FillSettingMgr(object):
    def __init__(self):
        self.style=None
        self.color=None

class VisualizeMgr(object):
    def __inti__(self, lineObj, fillObj):
        self._lineMgr=lineObj
        self._fillMgr=fillObj

    def RooPlotOpt(self):
        output=[]
        if self._lineMgr.color != None: output.append(ROOT.RooFit.LineColor(self._lineMgr.color))
        if self._lineMgr.width != None: output.append(ROOT.RooFit.LineWidth(self._lineMgr.width))
        if self._fillMgr.color != None: output.append(ROOT.RooFit.FillColor(self._fillMgr.color))
        if self._fillMgr.style != None: output.append(ROOT.RooFit.FillStyle(self._fillMgr.style))
        return output

    def SetupTObject(self,obj):
        if self._lineMgr.color != None: obj.SetLineColor(self._lineMgr.color)
        if self._lineMgr.width != None: obj.SetLineWidth(self._lineMgr.width)
        if self._fillMgr.color != None: obj.SetFillColor(self._fillMgr.color)
        if self._fillMgr.style != None: obj.SetFillStyle(self._fillMgr.style)



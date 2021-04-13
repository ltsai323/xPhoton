#!/usr/bin/env python2

import ROOT
from types import MethodType
import os
from xPhoton.xPhoton.Managers.LogMgr import GetLogger
from xPhoton.xPhoton.Managers.AdditionalFunctionMgr import ImportAddFunc
logging=GetLogger(__name__)
LEN=96.38

def ClearWorkspace(NeedToClean, directory='storefig'):
    if NeedToClean:
        if os.listdir(directory):
            print 'cleaning temporary files'
            os.system('/bin/rm %s/*'%(directory))
        else:
            print 'You have a clean workspace'
class DrawingMgr(object):
    def __init__(self, width=1000, height=1000):
        self._tmpTFile=ROOT.TFile('tmp.root','recreate')
        self._tmpTFile.cd()
        self._drawObj=[]
        self._drawArg=[]
        self._cwidth=width
        self._cheight=height
        self._canvasSetting={}

        self._addfuncMGR=ImportAddFunc()


    def __del__(self):
        self._drawObj=[]
        self._drawArg=[]
        self._tmpTFile.Close() # write nothing
    def grabrootobj(self, obj, opt):
        self._drawObj.append(obj)
        self._drawArg.append(opt)
        return self._drawObj[-1]
    def AddPlotContent(self, **kwargs):
        if not 'function' in kwargs:
            logging.error('importing function but no any "function" argument input')
            exit(1)
        self._addfuncMGR.ImportFunction(**kwargs)

    def ExportFig(self, output='hi.png', logScale=False, transparentCanv=True, redraw=False):
        canv=ROOT.TCanvas('c1','', self._cwidth,self._cheight)

        canv.SetLogy(logScale)
        if transparentCanv:
            canv.SetFillColor(4000)
            canv.SetFillStyle(4000)
            canv.SetFrameFillColor(4000)
            canv.SetFrameFillStyle(4000)

        for funcMgr in self._addfuncMGR:
            funcMgr.Exec()
        if redraw:
            for funcMgr in self._addfuncMGR:
                funcMgr.GetExecRes().Draw( funcMgr.GetArg('drawOpt') )
        canv.SaveAs(output)

    def CanvasSetup(self, logScale=False): # asdf not completed
        self._canvasSetting
    def Delete(self):
        self.__del__()
    @staticmethod
    def GeneralSetting():
        ROOT.gROOT.SetBatch(True)


''' need to be modified

# plot line by TLine
def AdditionalLine(self,p0,p1,drawOpt=''):
    self._drawObj.append(ROOT.TLine(p0[0],p0[1],p1[0],p1[1]))
    line=self._drawObj[-1]
    line.SetLineWidth(4)
    line.SetLineColor(32)
    line.Draw(drawOpt)

# plot text by TLatex
def PointInfo(self,x,y,content):
    self._drawObj.append(ROOT.TLatex())
    latex=self._drawObj[-1]
    latex.SetTextSize(0.040)
    #latex.SetTextAlign(13)
    latex.DrawLatex(x,y,content)


def accessTxtFile(filename):
    from readTxt import readTxt
    #filename='txtStored/ex2.txt'
    #filename='txtStored/ex1_filtered.txt'
    outname='fig2D_{label}_%s.png' % (readTxt.filenameParser(filename))
    data=readTxt(filename)
    xVal=[]
    yVal=[]
    zVal=[]

    for x,y,z in data:
        xVal.append(x)
        yVal.append(y)
        zVal.append(z*1000)
    return (xVal,yVal,zVal, outname)

def TGraph2DCreation(self,x,y,z,graphname='g',title='Height\ Measurement(\mu m)'):
   from array import array
   xval=array('f',x)
   yval=array('f',y)
   zval=array('f',z)

   self._drawObj.append( ROOT.TGraph2D(len(x), xval, yval, zval) )
   graph=self._drawObj[-1]
   graph.SetNameTitle( graphname, '{0};x(mm);y(mm)'.format(title) )
   graph.SetLineColor(8)
   graph.SetLineWidth(4)
   graph.SetFillStyle(3001)
   graph.SetFillColor(8)
   return graph

def TH2Creation(x,y,z):
    hist=ROOT.TH2F('hist','Height\ Measurement(\mu m);x(mm);y(mm)',
            45, -10, 35,
            43,-20,-450)
    for xval, yval, zval in zip(x,y,z):
        hist.Fill(xval,yval,zval)
    hist.SetStats(False)
    return hist
def TH2Creation_8InchHGCal(self,x,y,z,drawOpt='COLZ',title='Height\ Measurement(\mu m)', initNoValue=-999., fontSize=None):
    x0=LEN/2.
    y0=x0*3**0.5*-1.
    space=1.05*LEN
    self._drawObj.append(
        ROOT.TH2F('hist','%s;x(mm);y(mm)'%(title),
            15, x0-space, x0+space,
            15, y0-space, y0+space)
        )
    hist=self._drawObj[-1]
    M=max(z)
    m=min(z)
    for xval, yval, zval in zip(x,y,z):
        Z=int(zval*100)
        hist.Fill(xval,yval,float(Z)/100)
    for binX in range( hist.GetXaxis().GetNbins() ):
        for binY in range( hist.GetYaxis().GetNbins() ):
            if not hist.GetBinContent(binX+1,binY+1):
                hist.SetBinContent(binX+1,binY+1,initNoValue)
    hist.GetZaxis().SetRangeUser(1.2*m,1.2*M)
    hist.SetStats(False)
    hist.Draw(drawOpt)
    if fontSize:
        hist.SetMarkerSize(fontSize)
        hist.Draw('text:same')
    return hist
def TH2CCreation_8InchHGCal(self,x,y,z,drawOpt='COLZ',title='Height\ Measurement(\mu m)',fontSize=None):
    x0=LEN/2.
    y0=x0*3**0.5*-1.
    space=1.05*LEN
    self._drawObj.append(
        ROOT.TH2C('hist','%s;x(mm);y(mm)'%(title),
            10, x0-space, x0+space,
            10, y0-space, y0+space)
        )
    hist=self._drawObj[-1]
    M=max(z)
    m=min(z)
    for xval, yval, zval in zip(x,y,z):
        hist.Fill(xval,yval,zval)
    hist.GetZaxis().SetRangeUser(1.2*m,1.2*M)
    hist.SetStats(False)
    hist.Draw(drawOpt)
    if fontSize:
        hist.SetMarkerSize(fontSize)
        hist.Draw('text:same')
    return hist
if __name__ == '__main__':
    from readTxt import readTxt
    filenames=[
            ('../txtStored/HsinYeiData/Module2.rtf', 'HSData'),
            #('../txtStored/HsinYeiData/Module3.rtf', 'HSData'),
            #('../txtStored/HsinYeiData/NO.23.rtf',   'HSData'),
            ]
    DrawingMgr.GeneralSetting()
    for fname,figtag in filenames:
        plot1=DrawingMgr(width=1600,height=1000)
        xVal,yVal,zVal,fignameTemplate = accessTxtFile(fname)
        mean=0.
        dev=0.
        for i in zVal:
            mean+=i/(float(len(zVal)))
        for i in zVal:
            dev+=(i-mean)**2 / float(len(zVal))
        dev=dev**0.5
        for idx in range(len(zVal)):
            zVal[idx] = zVal[idx] - mean
        plot1.AddPlotContent(
                function=TH2Creation_8InchHGCal,
                x=xVal,y=yVal,z=zVal, drawOpt='COLZ',
                #title='\Delta h\ {from}\ h_{0}=%.2f+-%.2f\ \mu m' % (mean,dev)
                #title='#splitline{HGCal Module : %s}{Flatness Measurement}' % (readTxt.filenameParser(fname))
                title='Flatness Measurement to HGCal Module : %s' % (readTxt.filenameParser(fname)),
                fontSize=1.6
                )

        points=[
                (0.         ,0.),
                (LEN        ,0.),
                (LEN*1.5    , -1.*LEN*3.**0.5/2.),
                (LEN        , -1.*LEN*3.**0.5),
                (0.         , -1.*LEN*3.**0.5),
                (-1.*LEN*0.5, -1.*LEN*3.**0.5/2.)
                ]

        plot1.AddPlotContent( function=AdditionalLine, p0=points[0],p1=points[1],drawOpt='')
        plot1.AddPlotContent( function=AdditionalLine, p0=points[1],p1=points[2],drawOpt='')
        plot1.AddPlotContent( function=AdditionalLine, p0=points[2],p1=points[3],drawOpt='')
        plot1.AddPlotContent( function=AdditionalLine, p0=points[3],p1=points[4],drawOpt='')
        plot1.AddPlotContent( function=AdditionalLine, p0=points[4],p1=points[5],drawOpt='')
        plot1.AddPlotContent( function=AdditionalLine, p0=points[5],p1=points[0],drawOpt='')


        #for x,y,z in zip(xVal,yVal,zVal):
        #    #plot1.AddPlotContent( function=PointInfo, x=x, y=y, content=str(z-mean) )
        #    plot1.AddPlotContent( function=PointInfo, x=x, y=y, content='{0:.2f}'.format(z) )

        plot1.ExportFig( fignameTemplate.format(label=figtag) )
        plot1.Delete()
'''

#!/usr/bin/env python2
from __future__ import print_function
import ROOT
import xPhoton.xPhoton.Managers.LogMgr as LogMgr
mylog=LogMgr.GetLogger(__name__)

class MyHist1D(ROOT.TH1F):
    def __init__(self, *args):
        super(MyHist1D,self).__init__(*args)
        self.Sumw2()

class HistMgr1D(object):
    def __init__(self, prefix_):
        mylog.debug("it's init function")
        self._hists={}
        self._prefix=prefix_
        mylog.debug('prefix = ' + self._prefix)
        return

    def FullName(self, name):
        fullname='_'.join( [self._prefix, name] )
        '''
        found=False
        for h in self._hists.iteritems():
            if fullname == h.GetName(): found=True
        if not found:
            raise NameError('name %s not found in the dict' % name)
        '''
        return fullname

    @staticmethod
    def _makeHist(name,title, nbin, xmin, xmax):
        #return ROOT.TH1F(name,title, *args)
        return MyHist1D(name,title, nbin, xmin, xmax)

    def CreateHist(self, name, title, nbin, xmin, xmax):
        self.__setitem__( name, self._makeHist(self.FullName(name), title, nbin, xmin, xmax) )
        return

    def WriteTo(self, tfile):
        tfile.mkdir(self._prefix).cd()
        for key, val in self._hists.iteritems():
            print('start writing')
            print(val)
            val.Write()
            print('end of writing')

    def __setitem__(self, key, item):
        if key in self._hists:
            mylog.warning('[%s] key duplicated!!!  please check' % key)
        self._hists.__setitem__( key, item )

    def __getitem__(self, key):
        return self._hists.__getitem__(key)


if __name__ == '__main__':
    LogMgr.InitLogger(level='debug')
    mylog=LogMgr.GetLogger(__name__)
    hists=HistMgr1D('myprefix')
    hists.CreateHist('hiii', 'hi',100, 0., 100.)
    hists['newhist'] = ROOT.TH1F('newhist', '', 10, 0., 1.)
    print(hists.FullName('hiii'))
    canv=ROOT.TCanvas('c1','',500,500)
    hists['hiii'].Fill(3)
    hists['hiii'].Draw()
    canv.SaveAs("hi.png")


#!/usr/bin/env python2
import ROOT
import xPhoton.xPhoton.Managers.LogMgr as LogMgr
mylog=LogMgr.GetLogger(__name__)

class MyTH1(ROOT.TH1F):
    def __init__(self, *args):
        super(MyCanvas,self).__init__(*args)
        self.Sumw2()
class HistMgr1D(dict):
    def __init__(self, prefix):
        mylog.debug('it"s a init func')
        #dict.__init__(self,{})
        super(HistMgr1D, self).__init__({})
        self._prefix = prefix
        mylog.debug('prefix = ' + self._prefix)

    def FullName(self, name):
        #if self.__getitem__(name):
        return '_'.join( [self._prefix,name] )
        raise NameError('name %s not found in the dict' % name)

    @staticmethod
    def _makeHist(name,title, *args):
        return ROOT.TH1F(name,title, *args)


    def CreateHist(self, name, *args):
        self.__setitem__( name, self._makeHist( self.FullName(name), name+' distribution', *args) )

    def __setitem__(self, key, item):
        if key in self.__dict__:
            mylog.warning('[%s] key duplicated!!!  please check' % key)
        self.__dict__.__setitem__( key, item )

    def __getitem__(self, key):
        return self.__dict__.__getitem__(key)




if __name__ == '__main__':
    LogMgr.InitLogger(level='debug')
    mylog=LogMgr.GetLogger(__name__)
    hists=HistMgr1D('myprefix')
    hists.CreateHist('hiii', 100, 0., 100.)
    hists['newhist'] = ROOT.TH1F('newhist', 'newhist', 10, 0., 1.)
    print hists.FullName('hiii')
    canv=ROOT.TCanvas('c1','',500,500)
    hists['hiii'].Fill(3)
    hists['hiii'].Draw()
    canv.SaveAs("hi.png")


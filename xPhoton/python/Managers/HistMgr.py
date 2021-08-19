#!/usr/bin/env python2
import ROOT
import xPhoton.xPhoton.Managers.LogMgr as LogMgr
mylog=LogMgr.GetLogger(__name__)

class HistMgr1D(dict):
    def __init__(self, prefix):
        mylog.debug('it"s a init func')
        #self.__dict__={}
        self._prefix = prefix
        mylog.debug('prefix = ' + self._prefix)

    def FullName(self, name):
        print self.kkk
        #if self.__getitem__(name):
        return '_'.join( [self._prefix,name] )
        raise NameError('name %s not found in the dict' % name)

    @staticmethod
    def _makeHist(name, *args):
        return ROOT.TH1F(name,name, *args)


    def CreateHist(self, name, *args):
        self.__setitem__( name, self._makeHist( self.FullName(name), *args) )
    def __setitem__(self, key, item):
        if key in self.__dict__:
            mylog.warning('[%s] key duplicated!!!  please check' % key)
        self.__dict__.__setitem__( key, item )

    def __getitem__(self, key):
        return self.__dict__.__getitem__(key)

    def __repr__(self):
        return repr(self.__dict__)

    def __len__(self):
        return len(self.__dict__)

    def __delitem__(self, key):
        del self.__dict__[key]

    def clear(self):
        return self.__dict__.clear()

    def copy(self):
        return self.__dict__.copy()

    def has_key(self, k):
        return k in self.__dict__

    def update(self, *args, **kwargs):
        return self.__dict__.update(*args, **kwargs)

    def keys(self):
        return self.__dict__.keys()

    def values(self):
        return self.__dict__.values()

    def iteritems(self):
        return self.__dict__.iteritems()

    def pop(self, *args):
        return self.__dict__.pop(*args)

    def __cmp__(self, dict_):
        return self.__cmp__(self.__dict__, dict_)

    def __contains__(self, item):
        return item in self.__dict__

    def __iter__(self):
        return iter(self.__dict__)

    def __unicode__(self):
        return unicode(repr(self.__dict__))




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


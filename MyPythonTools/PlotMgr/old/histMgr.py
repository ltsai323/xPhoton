#!/usr/bin/env python2
from __future__ import print_function
import ROOT

class histMgr(object):
    def __init__(self, *prefixs):
        self._prefixs=[ str(prefix) for prefix in prefixs ]
        self.hDict={}
        if hasattr(self, '_prefixs'):
            print('my prefix is {}'.format(self._prefixs))
        else:
            print(' input prefixes are {}'.format(prefixs))
            print('type : {}'.format( type(prefixs) ))
            print('leng : {}'.format( len(prefixs) ))
    def Create1D(self, name, nbin, xmin, xmax):
        self.hDict[name]=ROOT.TH1F(self.FullName(name),name,nbin,xmin,xmax)
        self.hDict[name].Sumw2()

    def Create2D(self, name, xbin, xmin, xmax, ybin, ymin, ymax):
        self.hDict[name]=ROOT.TH2F(self.FullName(name),name, xbin,xmin,xmax, ybin,ymin,ymax)
        self.hDict[name].Sumw2()
    def Create(self, name, obj):
        self.hDict[name]=obj
        return
        if obj.InheritsFrom('TH1'): self.hDict[name]=obj
        raise TypeError( 'histMgr::Create() : input key %s inserts a weired object' % name )


    @staticmethod
    def RaiseKeyError(funcname,key):
        raise KeyError( 'histMgr::%s() : input key %s not found' % (funcname,key) )
    def FullName(self, name):
        return '_'.join( self._prefixs+[name] )
    def GetHist(self, key):
        if key in self.hDict:
            return self.hDict[key]
        histMgr.RaiseKeyError('GetHist',name)

    def __setitem__(self, key, val):
        self.Create(key,val)
    def __getitem__(self,key):
        return self.GetHist(key)
    def __len__(self):
        return len(self.hDict)
    def __iter__(self):
        return self.hDict.__iter__()
    def iteritems(self):
        return self.hDict.iteritems()
    def values(self):
        return self.hDict.values()
    def keys(self):
        return self.hDict.keys()

if __name__ == '__main__':
    h=histMgr(prefix='hiii_')
    h.Create1D('test', 20, 0., 5.)

    #h.Create( 'kkk', h.GetHist('test') )
    #h.Fill('test', 20) # need accomplished
    h['test'].Fill(3)

    canv=ROOT.TCanvas('c1','',1200,1000)
    #h.Draw('test', 'e0 p0') # need accomplished
    h['test'].Draw()
    canv.SaveAs('hi.png')

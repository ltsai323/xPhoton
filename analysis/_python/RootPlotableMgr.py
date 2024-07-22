#!/usr/bin/env python2
import ROOT

class PlotableMgr(object):
    def __init__(self, *prefixs):
        self._prefixs=[ str(prefix) for prefix in prefixs ]
        self.plotables={}
        self.plot_opts={}
        if hasattr(self, '_prefixs'):
            print 'my prefix is {}'.format(self._prefixs)
        else:
            print ' input prefixes are {}'.format(prefixs)
            print 'type : {}'.format( type(prefixs) )
            print 'leng : {}'.format( len(prefixs) )
    def CreateHist1D(self, name, nbin, xmin, xmax):
        self.plotables[name]=ROOT.TH1F(self.FullName(name),name,nbin,xmin,xmax)
        self.plotables[name].Sumw2()
        self.pltOption[name]=''


    def CreateHist2D(self, name, xbin, xmin, xmax, ybin, ymin, ymax):
        self.plotables[name]=ROOT.TH2F(self.FullName(name),name, xbin,xmin,xmax, ybin,ymin,ymax)
        self.plotables[name].Sumw2()
    def Create(self, name, obj,opt=''):
        self.plotables.setObj(name,obj,opt)
        return
    def CreateLegend(self, name, p0,p1, NDC=False):
        self.plotables[name]=ROOT.TLegend( p0[0],p0[1],p1[0],p1[1], name, 'NDC' if NDC else '' )
        self.pltOption[name]=''
        return leg
    def VisualizationSetup(name,setfunc):
        setfunc( self.plotables[name] )
    def SetDrawOpt(self, name, opt):
        self.plotables[name][1]=opt
    def getObj(self,name):
        return self.plotables[name][0]
    def setObj(self,name,obj,opt=''):
        self.plotables[name]=obj
        self.pltOption[name]=opt
    def DrawObj(self,name, additionalopt=''):
        self.plotables[name].Draw( ' '.join([self.pltOption[name],additionalopt]) )


    @staticmethod
    def _raiseKeyError(funcname,key):
        raise KeyError( 'histMgr::%s() : input key %s not found' % (funcname,key) )
    def FullName(self, name):
        return '_'.join( self._prefixs+[name] )
    def GetHist(self, key):
        if key in self.plotables:
            return self.plotables[key]
        histMgr._raiseKeyError('GetHist',name)

    def __setitem__(self, key, val):
        self.Create(key,val)
    def __getitem__(self,key):
        return self.getobj(key)
    def __len__(self):
        return len(self.plotables)
    def __iter__(self):
        return self.plotables.__iter__()
    def iteritems(self):
        return self.plotables.iteritems()
    def values(self):
        return self.plotables.values()
    def keys(self):
        return self.plotables.keys()

#!/usr/bin/env python2
from __future__ import print_function

import ROOT
from xPhoton.xPhoton.Managers.LogMgr import GetLogger


mylog=GetLogger(__name__)
class ColorMgr(dict):
    _INITNUM=10000
    _CURRENTNUM=_INITNUM
    __TColorObjs__=[]
    __colorcode_dict__ = {}
    def __init__(self):
        self.__dict__=ColorMgr.__colorcode_dict__
        ColorMgr.DefineColorSpace()





    @staticmethod
    def DefineColor(name,r_,g_,b_):
        if name in ColorMgr.__colorcode_dict__:
            mylog.info('Name %s is duplicated, ignoring'%name)
            return None
        ColorMgr.__colorcode_dict__[name] = ColorMgr._CURRENTNUM
        ColorMgr.__TColorObjs__=ROOT.TColor(ColorMgr._CURRENTNUM,r_,g_,b_)
        ColorMgr._CURRENTNUM+=1
    @staticmethod
    def DefineColorSpace():
        print('defining self color')
        ColorMgr.DefineColor('lightred',      255,158,157)
        ColorMgr.DefineColor('heavyred',      218, 70, 60)
        ColorMgr.DefineColor('lightblue',     255,158,157)
        ColorMgr.DefineColor('heavyblue',     174,203,219)
        ColorMgr.DefineColor('lightgreen',     57, 72,177)
        ColorMgr.DefineColor('heavygreen',     80,151,106)
        ColorMgr.DefineColor('lightpurple',   239,229,255)
        ColorMgr.DefineColor('heavypurple',    69, 41,141)
        ColorMgr.DefineColor('lightdark',     156,153,164)
        ColorMgr.DefineColor('heavydark',      29, 29, 31)

        ColorMgr.DefineColor('gentlewhite',   251,246,240)
        ColorMgr.DefineColor('heavyorange',   244,120, 75)


    def __setitem__(self, key, item):
        raise IOError("MyColorMgr doesn't support newly assign color. Please use DefineColor() function")
        #self.__dict__[key] = item

    def __getitem__(self, key):
        return self.__dict__[key]

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
    from xPhoton.xPhoton.Managers.LogMgr import InitLogger
    log=InitLogger(level='info')
    fin=ROOT.TFile.Open('/home/ltsai/Work/workspaceGammaPlusJet/xPhoton/xPhoton/zee_noNEles2.root')
    hin=fin.Get('nEleMatched')

    canv=ROOT.TCanvas('c1','',1200,1000)
    colors=ColorMgr()
    hin.SetFillColor( colors['lightred'] )
    #colors.DefineColor('testblue', 227,233,249)
    #hin.SetFillColor( colors['testblue'] )
    hin.Draw()
    canv.SaveAs('hi.png')



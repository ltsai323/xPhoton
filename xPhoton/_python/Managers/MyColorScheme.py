#!/usr/bin/env python2

from xPhoton.xPhoton.Managers.VisualizeMgr import LineSettingMgr,FillSettingMgr,VisualizeMgr

mycolorscheme={}

# for data
line=LineSettingMgr()
line.width=4
line.color=1

fill=FillSettingMgr()
fill.color=None
fill.style=None

mycolorscheme.update( {'data0':VisualizeMgr(line,fill)} )

# for mc tot
line=LineSettingMgr()
line.width=3
line.color=3

fill=FillSettingMgr()
fill.color=3
fill.style=3

mycolorscheme.update( {'fitTot':VisualizeMgr(line,fill)} )

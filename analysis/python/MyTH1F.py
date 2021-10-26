#!/usr/bin/env python2

import ROOT
def DataDrawingSetup(hist, color=0, markersize=3, linestyle=0):
    if      color != 0:  colorsteup(hist,     color)
    if  linestyle != 0: lstylesetup(hist, linestyle)
    if markersize != 0: hist.SetMarkerSize(markersize)
def MCDrawingSetup(hist, color=0, fillstyle=0, linestyle=0);
    if     color != 0:  colorsetup(hist,    color)
    if linestyle != 0: lstylesetup(hist,linestyle)
    if fillstyle != 0: fstylesetup(hist,fillstyle)

def  colorsetup(hist, idx):
    pass
def lstylesetup(hist, idx):
    pass
def fstylesetup(hist, idx):
    pass

if __name__ == '__main__':
    pass



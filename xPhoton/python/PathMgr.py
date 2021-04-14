#!/usr/bin/env python2
import os

def CMSPath(ipath):
    return '/'.join( [os.environ['CMSSW_BASE'], 'src', ipath] )

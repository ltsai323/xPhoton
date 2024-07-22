#!/usr/bin/env python2

import os

def CMSPath(relativepath):
    return '/'.join( [os.environ['CMSSW_BASE'],'src',relativepath] )

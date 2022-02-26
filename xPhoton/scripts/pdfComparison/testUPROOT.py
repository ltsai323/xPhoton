#!/usr/bin/env python3

import uproot
import numpy as np
import awkward1 as awk
import matplotlib.pyplot as plt
import mplhep


def hi():
    ifile=uproot.open('output.root')
    myhist=ifile['data/data_bScore']

    print( mplhep.histplot(myhist.to_boost()) )
    plt.style.use(mplhep.style.CMS)
    mplhep.histplot(myhist.to_boost())
    mplhep.cms.label()

    #myhist.to_hist().plot()
    myhist.show()

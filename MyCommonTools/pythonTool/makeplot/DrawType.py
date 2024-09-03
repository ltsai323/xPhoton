#!/usr/bin/env python3
import matplotlib.pyplot as plt
from makeplot.ScatterPlot_PointsConverter import XYscatterPoints
from makeplot.ratiotool import TakeRatio

MARKER_STYLE = [ 'o', '^', 's', 'D' ]
COLORS = [ 'blue', 'green', 'orange', 'purple' ]

def draw_EP(xySCATTERwithDESC:[XYscatterPoints],
        inTITLE:str = 'blah',
        yTITLE:str = '$d^{3}\sigma$ / d$\eta_{\gamma}$ d$\eta_{C}$ d$p_{T}^{\gamma}$',
        yRANGE:tuple = (), logY:bool = True,
        ):
    plt.clf()
    fig = plt.figure(facecolor='none', edgecolor='none', figsize=(6, 4), dpi=80)

    for idx, xy_scatter_with_desc in enumerate(xySCATTERwithDESC):
        plt.errorbar(
                xy_scatter_with_desc.x,
                xy_scatter_with_desc.y,
           yerr=xy_scatter_with_desc.y_err,
          label=xy_scatter_with_desc.desc,
                markersize=3,fmt=MARKER_STYLE[idx], color=COLORS[idx])

    plt.title(inTITLE)
    plt.xlabel('$p_{T}^{\gamma}$ (GeV)')
    plt.ylabel(yTITLE)
    if yRANGE and len(yRANGE)>0.: plt.ylim(yRANGE[0],yRANGE[1])
    else: print('[AutoYrange - INFO:makeplot.tools] Input yRANGE not found. Auto value.')
    if logY: plt.yscale('log')
    plt.legend()

def draw_EP_ratio(xySCATTERwithDESC:[XYscatterPoints],
        inTITLE:str = 'blah',
        yTITLE:str = '$d^{3}\sigma$ / d$\eta_{\gamma}$ d$\eta_{C}$ d$p_{T}^{\gamma}$',
        yRANGE:tuple = (), logY:bool = True,
        ratioTITLE:str = 'ratio',
        ratioYrange:tuple = (0.5,1.5),
        ):
    plt.clf()
    fig, (ax1, ax2) = plt.subplots(2, 1, sharex=True, gridspec_kw={'height_ratios': [3, 1]},
            facecolor='none', edgecolor='none', figsize=(6,4),dpi=80,
            )


    ## fill upper pad
    for idx, xy_scatter_with_desc in enumerate(xySCATTERwithDESC):
        ax1.errorbar(
                xy_scatter_with_desc.x,
                xy_scatter_with_desc.y,
           yerr=xy_scatter_with_desc.y_err,
          label=xy_scatter_with_desc.desc,
                markersize=3,fmt=MARKER_STYLE[idx], color=COLORS[idx])
    ax1.set_title(inTITLE)
    ax1.set_ylabel(yTITLE)

    ax1.set_yscale('log')
    if yRANGE and len(yRANGE)>0.:
        if logY and yRANGE[0] < 0.:
            print(f'[LogScale - WARNING] Failed log transform to  y axis range {yRANGE}. Use normal scale.')
        else:
            ax1.set_ylim(yRANGE[0],yRANGE[1])
            if not logY: ax1.set_yscale('linear')
    ax1.legend()

    ax2.axhline(y=1, color='black', linestyle='--', label='Ratio=1')
    ## fill lower pad
    for _idx, xy_scatter in enumerate(TakeRatio(xySCATTERwithDESC)):
        idx = _idx+1
        x = xy_scatter.x
        y = xy_scatter.y
        yErr = xy_scatter.y_err
        desc = xy_scatter.desc
        ax2.errorbar(x,y,yErr, markersize=3, fmt=MARKER_STYLE[idx], color=COLORS[idx])


    ax2.set_xlabel('$p_{T}^{\gamma}$ (GeV)')
    ax2.set_ylabel(ratioTITLE)
    ax2.set_ylim(*ratioYrange)
if __name__ == "__main__":
    testdat2 = XYscatterPoints(
            x = [ 3, 4, 5 ],
            y = [18,12,14],
            y_err = [0.1,0.1,0.1],
            desc='test dat2')
    testdata = XYscatterPoints(
            x = [ 3, 4, 5 ],
            y = [13,14,15],
            y_err = [0.1,0.1,0.1],
            desc='test data')
    # draw_EP      ([testdata,testdat2],
    #         inTITLE='hi', yTITLE='useless')
    draw_EP_ratio([testdata,testdat2],
            inTITLE='hi', yTITLE='useless')
    plt.savefig('hi.jpg')


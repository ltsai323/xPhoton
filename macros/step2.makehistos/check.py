#!/usr/bin/env python3

import uproot4 as uproot
import matplotlib.pyplot as plt
import numpy as np

def mystackplot( myEDGE,
        *binCONTENTs,
        labelS=[],
                ):
    my_edges = myEDGE[1:-1]

    if len(binCONTENTs) != len(labelS):
        raise ValueError(
            'mystackplot() : length of histogram(%d) and label(%s) are different.'%
            (len(binCONTENTs),len(labelS)))
    bin_contents = []
    for bin_content, label in zip(binCONTENTs,labelS):
        my_bin_content = bin_content[1:]
        if len(bin_contents) == 0:
            bin_contents.append(my_bin_content)
        else:
            bin_contents.append(my_bin_content+bin_contents[-1])

    for b in bin_contents:
        print('stacked bin contents : ', b)
    colors = ['red', 'blue', 'green']
    for bin_content, label, thecolor in zip(reversed(bin_contents),reversed(labelS), colors):
        print('hii')
        plt.step(my_edges, my_bin_content,
            where='post', color=thecolor, label=label)

if __name__ == "__main__":

    ifile = uproot.open("test_makeComparisonHistWithoutFit/makehisto.root")

    hdata = ifile['overall_binning/BDT_data_signalRegion']
    # throw out first underflow and overflow bins
    data_bin_content = hdata.values()[1:-1]
    data_bin_posserr = np.sqrt(data_bin_content)
    data_xaxis_edges = np.array(hdata.edges())[1:-1]
    data_xaxiscenter = (data_xaxis_edges[:-1] + data_xaxis_edges[1:]) /2.


    plt.errorbar(
            data_xaxiscenter, data_bin_content,
            xerr = 0, yerr = data_bin_posserr,
            fmt='o', color='black', ecolor='black', capsize=4, label='data')



    #hsign = ifile['overall_binning/BDT_gjet_signalRegion_shapeUncUp']
    hsign = ifile['overall_binning/BDT_gjet_signalRegion']
    # throw out first underflow and overflow bins
    sign_bin_content = hsign.values()[1:] * 19.52 / 35.9
    sign_bin_posserr = np.sqrt(sign_bin_content)
    sign_xaxis_edges = np.array(hsign.edges()[1:-1]) # remove underflow and overflow


    hfake = ifile['overall_binning/BDT_QCD_signalRegion_shapeUncUp']
    # throw out first underflow and overflow bins
    fake_bin_content = hfake.values()[1:] * 19.52 / 35.9
    fake_bin_posserr = np.sqrt(fake_bin_content)

    print('sign_xaxis_val s : ', sign_bin_content)
    print('sign_xaxis_edges : ', sign_xaxis_edges)
    print('data_xaxis_cnter : ', data_xaxiscenter)

    mystackplot(hsign.edges(),
                hsign.values(), hfake.values(),
                labelS = [ 'gjet', "QCD" ])
    # plt.stackplot(
    #     sign_xaxis_edges,
    #     sign_bin_content, fake_bin_content,
    #     labels=['gjet', 'QCD']
    #               )


    plt.yscale('log')
    plt.ylabel('entries')
    plt.xlabel('BDT score')

    plt.legend(loc='upper left')
    filename='hi.pdf'
    plt.savefig(filename)
    print('file saved : '+filename)


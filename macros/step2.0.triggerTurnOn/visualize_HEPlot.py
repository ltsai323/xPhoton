import uproot
import numpy as np
import mplhep as hep
import matplotlib.pyplot as plt
import math

# Open the ROOT file
file = uproot.open("dataMCcomp_endcapPhoton.root")

# Access the 'expdata' directory
def getHist(tFILE, dirNAME):
    return tFILE[f'{dirNAME}/phoEta'].to_hist()

expdata = file['expdata']

# Read histograms
#phoPt = expdata['phoPt'].to_hist()
#phoEta = expdata['phoEta'].to_hist()
#phoPhi = expdata['phoPhi'].to_hist()
hdata = getHist(file, 'expdata')
hsign = getHist(file, 'sign0')
hfake = getHist(file, 'fake0')

def getOrder(maxNUMBER:float) -> float:
    index_to_10 = int(math.log10(maxNUMBER))
    return 10**index_to_10


# Create a ratio plot function
def ratio_plot(hist2, hist1, xlabel, ylabel, title):
    fig, (ax, ax_ratio) = plt.subplots(2, 1, gridspec_kw={'height_ratios': [3, 1]}, sharex=True)

    # Main plot
    hep.histplot(hist1, ax=ax, label='Hist 1')
    hep.histplot(hist2, ax=ax, label='Hist 2')

    max_num = max(hist2.values())
    min_num = min(hist2.values())
    order = getOrder(max_num)
    ax.set_xlabel('')
    ax.set_ylabel(ylabel, fontsize=14, labelpad=18)
    #ax.yaxis.set_major_locator(plt.MultipleLocator(order))
    #ax.yaxis.set_minor_locator(plt.MultipleLocator(0.2*order))
    ax.set_ylim(min_num, max_num*1.5)
    ax.legend()

    # Ratio plot
    ratio = hist1.values() / hist2.values()
    print(f'[Check content] hist1 has ')
    print(f'[__dir__()]')
    for name in hist1.__dir__():
        print(f'    {name}')

    print(f'[values()]')
    for val,var in zip(hist1.values(), hist1.variances()):
        print(f'    {val} +- {var}')

    #ratio_err = ratio * np.sqrt((hist1.errors() / hist1.values())**2 + (hist2.errors() / hist2.values())**2)
    bin_centers = hist1.axes[0].centers

    ax.ticklabel_format(style='sci', axis='y', scilimits=(0,3), useMathText=True)

    #ax_ratio.errorbar(bin_centers, ratio, yerr=ratio_err, fmt='o', color='k')
    ax_ratio.errorbar(bin_centers, ratio, yerr=[0 for a in ratio], fmt='o', color='k')
    ax_ratio.xaxis.set_major_locator(plt.MultipleLocator(0.5))
    ax_ratio.xaxis.set_minor_locator(plt.MultipleLocator(0.1))
    ax_ratio.set_xlabel(xlabel, fontsize=14, labelpad=5)

    ax_ratio.set_ylabel('data/MC', fontsize=14, labelpad=10)
    ax_ratio.set_ylim(0.5,1.5)

    plt.suptitle(title)
    plt.show()
    #outname = 'hi.png'
    #plt.savefig(outname)
    #print(f'[SavedOutput] {outname}')

# Assuming histograms are already normalized
# Plot phoPt ratio
#ratio_plot(phoPt, phoEta, xlabel='pT', ylabel='Events', title='phoPt / phoEta Ratio')
ratio_plot(hdata, hsign, xlabel='$\eta^{\gamma}$', ylabel='Events', title='data / gjet')

# You can add more ratio plots similarly for other histograms if needed
# ratio_plot(phoPt, phoPhi, xlabel='pT', ylabel='Events', title='phoPt / phoPhi Ratio')

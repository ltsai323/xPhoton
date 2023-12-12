#!/usr/bin/env python3

import matplotlib.pyplot as plt
import pandas as pd

def WARNING(*args): sys.stderr.write('[check.ctaggingVars-WARNING] %s'% (args)+'\n')
def LOG    (*args): print('[check.ctaggingVars-LOG] %s'% (args))

def draw_something(pandasDATAframe, xDATA, outTAG, columnNAME, yAXISname='', figTITLE = ''):
    plt.cla() # clear previous result
    df = pandasDATAframe

    cut_0_0 = 'pEtaBin==0 and jEtaBin==0'
    cut_0_1 = 'pEtaBin==0 and jEtaBin==1'
    cut_1_0 = 'pEtaBin==1 and jEtaBin==0'
    cut_1_1 = 'pEtaBin==1 and jEtaBin==1'

    def myscatter(cut_, **args):
        sel_data = df.query(cut_)
        ydata = sel_data[columnNAME]
        xdata = [ xDATA[ptbin] for ptbin in sel_data['pPtBin'] ]

        plt.scatter(xdata, ydata, **args)
        plt.plot   (xdata, ydata, args['color'], linestyle='-')
    myscatter(cut_0_0, label='Barrel $\gamma$, Barrel Jet', color='C0', marker='o')
    myscatter(cut_0_1, label='Barrel $\gamma$, Endcap Jet', color='C1', marker='*')
    myscatter(cut_1_0, label='Endcap $\gamma$, Barrel Jet', color='C2', marker='^')
    myscatter(cut_1_1, label='Endcap $\gamma$, Endcap Jet', color='C3', marker='D')

    plt.xlabel('$P_{T}^{\gamma}$ in GeV')
    plt.ylabel(yAXISname)
    plt.title(figTITLE)
    plt.grid(True)
    plt.legend()

    outputfilename = f'csvCollect_{outTAG}_{columnNAME}.pdf'
    plt.savefig(outputfilename)
    LOG(f'output fig: {outputfilename}')

def check_no_low_statistics(dF):
    df = dF

    bYield = df[df['fit_yield_B']<10]
    if len( bYield ) < 10:
        for evtIdx, row in bYield.iterrows():
            totnum = row['fit_yield_B']+row['fit_yield_C']+row['fit_yield_L']
            WARNING(f"bin_{row['pEtaBin']:.0f}_{row['jEtaBin']:.0f}_{row['pPtBin']:2.0f}: fitted b yield is {row['fit_yield_B']:5.2f} in total {totnum:.2f}")

    cYield = df[df['fit_yield_C']<10]
    if len( cYield ) < 10:
        for evtIdx, row in cYield.iterrows():
            totnum = row['fit_yield_B']+row['fit_yield_C']+row['fit_yield_L']
            WARNING(f"bin_{row['pEtaBin']:.0f}_{row['jEtaBin']:.0f}_{row['pPtBin']:2.0f}: fitted c yield is {row['fit_yield_C']:5.2f} in total {totnum:.2f}")

class CommonObj:
    csv_file = ''
    df = None
    pt_def = []
    outtag = ''
    def DrawSomething(self,*args):
        draw_something(self.df,self.pt_def,self.outtag, *args)
    def CheckNoLowStatistics(self):
        check_no_low_statistics(self.df)

if __name__ == "__main__":
    import sys
    dataERA, csvFILE, outTAG = sys.argv[1:] if len(sys.argv) >3 else ('UL2016PreVFP', 'UL2016.CTag_SimulFit.csv', 'hi')

    from py_pt_ranges_definition import ptbin_ranges
    pt_def = ptbin_ranges(dataERA)
    print(f'\n\n len of pt range is {len(pt_def)}\n\n')

    # suppress useless too small float point warning.
    import warnings
    warnings.filterwarnings("ignore", category=UserWarning, module="numpy")

    m = CommonObj()
    m.df = pd.read_csv(csvFILE)
    m.pt_def = pt_def
    m.outtag = outTAG

    m.CheckNoLowStatistics()
    m.DrawSomething('frac_L', 'composition', 'L quark compositions')
    m.DrawSomething('frac_C', 'composition', 'C quark compositions')
    m.DrawSomething('frac_B', 'composition', 'B quark compositions')
    m.DrawSomething('chi2_jet0', '$\chi^2$', 'fitting $\chi^2$ to bScore')
    m.DrawSomething('chi2_jet1', '$\chi^2$', 'fitting $\chi^2$ to CvsL')
    m.DrawSomething('chi2_jet2', '$\chi^2$', 'fitting $\chi^2$ to CvsB')

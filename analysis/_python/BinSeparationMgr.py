#!/usr/bin/env python2

pt_bin_2016=[25,34,40,55,70,85,100,115,135,155,175,200,220,250,300,1000]
etabin_2016=[-0.1, 1.5, 2.5] # 0: EB, 1: EE
etabin_name=['EB', 'EE']

def _inputcheck(argv):
    if len(argv) < 2 or not 'root' in argv[1]:
        raise IOError('input a root file!')
    import os
    if not os.path.isfile(argv[1]):
        raise IOError('input root file not found')

def _writeSummaryFile(summaryname='README_binSep.txt'):
    summaryfile=open(summaryname,'w')
    word_template='%s bin %s = ( %.0f, %.0f )\n'
    for idx in range( len(eta_bins) - 1 ):
        summaryfile.write( word_template % ('Eta', etabin_name(idx), eta_bins[idx], eta_bins[idx+1]) )
    summaryfile.write('\n')
    for idx in range( len(pt_bins) - 1 ):
        summaryfile.write( word_template % ('Pt', str(idx), pt_bins[idx], pt_bins[idx+1]) )

if __name__ == '__main__':
    import ROOT
    import sys

    _inputcheck(sys.argv)
    df=ROOT.ROOT.Experimental.TDataFrame('t', sys.argv[1])
    outputname='%s_{etabin}_{ptbin}.root' % sys.argv[1].split('.')[0]

    pt_bins=pt_bin_2016
    etabins=etabin_2016

    for idx_pt in range( len(pt_bins) - 1 ):
        loweredge_pt = pt_bins[idx_pt]
        upperedge_pt = pt_bins[idx_pt + 1]

        for idx_eta in range( len(etabins) - 1 ):
            loweredge_eta = etabins[idx_eta]
            upperedge_eta = etabins[idx_eta + 1]

            df.Filter(
                    'recoPt > %.4f && recoPt < %.4f && recoSCEta > %.4f && recoSCEta < %.4f' % (loweredge_pt, upperedge_pt, upperedge_eta, upperedge_eta)
                     ).SnapShot('t_', outputname.format(ptbin=idx_pt, etabin=idx_eta) )

    _writeSummaryFile('hi.txt')

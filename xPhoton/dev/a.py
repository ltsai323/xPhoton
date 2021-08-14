import ROOT
import sys
file=ROOT.TFile.Open( sys.argv[1] )
tree=file.Get('t')

for evt in tree:
    trg1=evt.firedTrgs
    trg2=evt.firedTrgsL

    exactlySame=True
    for ibit in range(15):
        if (trg1>>ibit&1) != (trg2>>ibit2&1):
            exactlySame=False
print 'result. firedTrgI and firedTrgL is the same ? {}'.format(exactlySame)

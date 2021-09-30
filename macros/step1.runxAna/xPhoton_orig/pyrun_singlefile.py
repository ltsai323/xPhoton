import ROOT
import sys
execfile='xPhotonHFJet_origversion.C'


infile=sys.argv[1]
idx=sys.argv[2] if len(sys.argv)>2 else 0
ROOT.gROOT.ProcessLine('.L %s+'%execfile)
ROOT.xPhotonHFJet(infile, idx)

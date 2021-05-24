#!/usr/bin/env python2
# ./this.py ggtree.root
import ROOT
import sys

if __name__ == '__main__':
   if len(sys.argv) < 2:
      raise IOError(' A input root file is needed to run this file')
   inputfile=sys.argv[1]
   infile=ROOT.TFile.Open(inputfile)
   intree=infile.Get('ggNtuplizer/EventTree')

   evtlimit=10

   for evt in intree:
      pt = [ p for p in evt.jetPt ]
      #mm = [ m for m in evt.jetSecVtxMass ]
      phi = [ p for p in evt.jetPhi ]


      #print {'JETPT': pt, 'SECMASS': mm, 'PHI': phi }
      print 'jetpt  {}'.format(pt)
      print 'jetphi {}'.format(phi)
      #print 'jetSMt {}'.format(mm)
      evtlimit-=1
      if evtlimit == 0: break

   infile.Close

#!/usr/bin/env python2

def GetFile(argv):
    if len(argv) < 2: raise IOError('You need to input a log file')
    return argv[1]

class MyBin(object):
    def __init__(self, lineword):
        keywords=lineword.strip().split()
        self._phoPbin=int(  keywords[1])
        self._phoEbin=int(  keywords[3])
        self._jetEbin=int(  keywords[5])
        self.fitvalue=float(keywords[7])
        self.fiterror=float(keywords[9])
    def __repr__(self):
        return '(ptbin,etabin,jetbin)=(%d,%d,%d) and fit result = (%.1f,%.1f)' % (self._phoPbin,self._phoEbin,self._jetEbin,self.fitvalue,self.fiterror)
    def DATExport(self):
        return ' '.join( [str(val) for val in [self._phoPbin,self._phoEbin,self._jetEbin, self.fitvalue,self.fiterror]]) + '\n'
    def IsBarrelJet(self):
        return True if self._jetEbin == 0 else False

def ExportToDAT(binvalues, outputfile):
    ofile=open(outputfile,'w')

    ofile.write('ptbin/I:EBEE/I:jetbin/I:fiterror/F:fitvalue/F\n')
    for v in binvalues: ofile.write( v.DATExport() )
    ofile.close()



if __name__ == "__main__":
    import sys
    infile=open( GetFile(sys.argv), 'r')

    lines=infile.readlines()
    sigvals=[ MyBin(line) for line in lines if 'SIG' in line ]
    bkgvals=[ MyBin(line) for line in lines if 'BKG' in line ]

    for sig in sigvals: print sig
    for bkg in bkgvals: print bkg
    ExportToDAT(sigvals, 'yield.dat')
    ExportToDAT(bkgvals, 'bkg.dat')

    sigbarrel=[ mybin for mybin in sigvals if     mybin.IsBarrelJet() ]
    sigendcap=[ mybin for mybin in sigvals if not mybin.IsBarrelJet() ]
    bkgbarrel=[ mybin for mybin in bkgvals if     mybin.IsBarrelJet() ]
    bkgendcap=[ mybin for mybin in bkgvals if not mybin.IsBarrelJet() ]

    ExportToDAT(bkgbarrel, 'bkg_barrelJetOnly.dat')
    ExportToDAT(bkgendcap, 'bkg_endcapJetOnly.dat')
    ExportToDAT(sigbarrel, 'yield_barrelJetOnly.dat')
    ExportToDAT(sigendcap, 'yield_endcapJetOnly.dat')

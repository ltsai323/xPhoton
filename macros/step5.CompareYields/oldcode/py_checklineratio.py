#!/usr/bin/env python2

def getfile(ifile):
    import os
    if os.path.isfile(ifile):
        print ifile
        return open(ifile,'r')
    raise IOError('input file %s not found'%ifile)
def findYield(line):
    contents=line.strip().split(' ')
    mydigit=contents[3] if len(contents)>1 else 'None'
    try:
        float(mydigit)
        return float(mydigit)
    except ValueError:
        return None
def Mesg(line, val):
    contents=line.strip().split(' ')
    pt_bin=contents[0]
    etabin=contents[1]
    jetbin=contents[2]
    print 'pho Pt:%3s phoEta:%3s jetEta:%3s  : get yield ratio = %.3f' % (pt_bin,etabin,jetbin, val)


if __name__ == '__main__':
    f15=getfile('15yield.dat')
    f16=getfile('16yield.dat')

    for lline, rline in zip( f15.readlines(), f16.readlines() ):
        yield15=findYield(lline)
        yield16=findYield(rline)
        if not yield15: continue
        if not yield16: continue
        Mesg(lline, yield15/yield16*35.9/2.26)

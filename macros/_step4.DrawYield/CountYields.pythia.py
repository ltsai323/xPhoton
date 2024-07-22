#!/usr/bin/env python2
import xPhoton.xPhoton.Managers.LogMgr as LogMgr
mylog=LogMgr.GetLogger()
import ROOT

class MyBin(object):
    def __init__(self, phoptbin, phoetabin, jetetabin):
        self.phoptbin=phoptbin
        self.phoetabin=phoetabin
        self.jetetabin=jetetabin
    def naming(self, nametemplate):
        return nametemplate % (self.phoetabin, self.jetetabin, self.phoptbin)



if __name__ == '__main__':

    LogMgr.InitLogger(level='info')
    mylog=LogMgr.GetLogger(__name__)
    infile=ROOT.TFile.Open('isovsbdt_template.root')



    for phoeta in range(2):
        for jeteta in range(2):
            for phopt in range(21):
                mylog.debug('indexes are pEta:%d jEta:%d pPt:%d' % (phoeta,jeteta,phopt) )
                mybin=MyBin(phopt, phoeta, jeteta)

                h_sig =infile.Get( mybin.naming('gjet_%d_%d_%d_px1_chIso') )

                countyield=h_sig.Integral()
                counterror=countyield**0.5

                print('-----------------------------------------------------')
                print('Data %5.1f events, and %5.1f fitted'%( countyield, countyield ))
                print('ptbin %d  etabin %d  jetbin %d SIG %5.1f #pm %5.1f events'% ( mybin.phoptbin,mybin.phoetabin,mybin.jetetabin, countyield, counterror ))
                print('ptbin %d  etabin %d  jetbin %d BKG %5.1f #pm %5.1f events'% ( mybin.phoptbin,mybin.phoetabin,mybin.jetetabin, 0, 0) )

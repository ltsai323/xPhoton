#!/usr/bin/env python2

import ROOT
from array import array

HTBINSEP=array('d', [50,100,200,300,500,700,1000,1500,2000,9999])
def HTbin():
    return HTBINSEP
def HTbinsize():
    return len(HTBINSEP)-1

class HistName(object):
    declareCounter=0
    def __init__(self):
        self._postfix=HistName.Counter()
        self._histList={}
    def name(self, inname):
        hname=inname+'.'+self._postfix
        if not inname in self._histList.keys():
            self._histList[inname] =  ROOT.TH1F(hname,'', HTbinsize(), HTbin())
        return 'GenHT >> ' + hname

    def MaekHistGlobal(self):
        for key,val in self._histList.iteritems():
            val.SetDirectory(0)
    @classmethod
    def Counter(cls):
        cls.declareCounter+=1
        return str(cls.declareCounter)
    def PrintCounter(self):
        print(self._postfix)
def main(ifilename):
    ifile=ROOT.TFile.Open(ifilename)
    itree=ifile.Get('t')

    n=HistName()
    itree.Draw( n.name('hadB'), 'leadingJetHadFlvr==5' )
    itree.Draw( n.name('prtB'), 'abs(leadingJetPartonID) == 5' )
    itree.Draw( n.name('genB'), 'abs(leadingJetGenPartonID) == 5' )
    itree.Draw( n.name('lheB'), 'abs(lhePID)==5' )

    itree.Draw( n.name('hadBANDlheB'), 'abs(lhePID)==5 && leadingJetHadFlvr==5')
    itree.Draw( n.name('hadBANDleadinglheB'), 'abs(lhePID[-1])==5 && leadingJetHadFlvr==5')
    itree.Draw( n.name('hadBANDgenB'), 'leadingJetHadFlvr && abs(leadingJetGenPartonID)==5')
    itree.Draw( n.name('hadBANDprtB'), 'leadingJetHadFlvr && abs(leadingJetPartonID)==5')
    itree.Draw( n.name('prtBANDlheB'), 'abs(leadingJetPartonID)==5 && lhePID==5')
    itree.Draw( n.name('prtBANDleadinglheB'), 'abs(leadingJetPartonID)==5 && lhePID[-1]==5')
    
    n.MaekHistGlobal()
    return n



if __name__ == "__main__":

    hist0=main("output_job_PhotonHFJet_lheOrigSort.root")
    outfile=ROOT.TFile('kkkoutput.root', 'recreate')
    outfile.cd()
    for name, hist in hist0._histList.iteritems():
        hist.Write()
    outfile.Close()

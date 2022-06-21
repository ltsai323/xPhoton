#!/usr/bin/env python2
import json
import ROOT

class JsonInfo(object):
    def __init__(self, jsonname):
        with open(jsonname, 'r') as jsonfile:
            info=json.load(jsonfile)
            self.bin_phopt      =info['bin_phopt']
            self.bin_phoeta     =info['bin_phoeta']
            self.bin_jeteta     =info['bin_jeteta']


            self.iFile_data     =info['file_data']
            self.iFile_sign     =info['file_signal']
            self.iFile_fake     =info['file_QCD']
            self.oNameTemplate  =info['OutputNameTemplate']
    def NewHistNaming(self, nametemplate):
        return nametemplate
    def OldHistNaming(self, nametemplate):
        return nametemplate % (self.bin_phoeta,self.bin_jeteta,bin_phopt)
    def OutputFileName(self):
        return self.oNameTemplate+'.%d_%d_%d.root'% (self.bin_phoeta,self.bin_jeteta,self.bin_phopt)

class MyTree(object):
    def __init__(self, fname, tname='binnedTree'):
        self.ifile=ROOT.TFile.Open(fname)
        self.itree=self.ifile.Get(tname)
    def __del__(self):
        self.ifile.Close()
    def Draw(self, *args):
        #for idx,arg in enumerate(args):
        #    print 'arg %d : %s' % (idx,arg)
        self.itree.Draw(*args)
def Selection(*args):
    overallcuts=[]
    for argcut in args:
        if isinstance(argcut, str) : overallcuts.append(argcut)
        if isinstance(argcut, list): overallcuts.extend(argcut)
    return '(' + '&&'.join(overallcuts) + ')'
class DrawSelections(object):
    def __init__(self):
        self.Init()
    def Selections(self, *args):
        self._selections=[]
        for argcut in args:
            if isinstance(argcut, str) : self._selections.append(argcut)
            if isinstance(argcut, list): self._selections.extend(argcut)
        return self.Get()
    def PutWeights(self, *args):
        for argcut in args:
            if isinstance(argcut, str) : self._weights.append(argcut)
            if isinstance(argcut, list): self._weights.extend(argcut)
    def Init(self):
        self._selections=[]
        self._weights=[]
    def Get(self):
        return '('+'&&'.join(self._selections)+')' + ' '.join(('*'+c for c in self._weights))

class HistCollector(object):
    def __init__(self):
        self._names=[]
    def NewHistName(self, name):
        self._names.append(name)
        return name
    def ObtainHistObjects(self):
        self._objs=[ ROOT.gROOT.FindObject(name) for name in self._names ]
    def WriteTo(self, tfileObj):
        tfileObj.cd()
        for obj in self._objs: obj.Write()
NUMBIN_MATCHEDPHOSTAT=5
NUMBIN_EVTPARITY=2
NUMBIN_JETFLVR=3
if __name__ == "__main__":
    import sys

    args=JsonInfo(sys.argv[1])

    tdata=MyTree(args.iFile_data)
    tsign=MyTree(args.iFile_sign)
    tfake=MyTree(args.iFile_fake)

    oFile=ROOT.TFile( args.OutputFileName(), "RECREATE")
    oFile.cd()

    sel_binning=[
            'bin_phopt == %d'   % args.bin_phopt,
            'bin_phoeta == %d'  % args.bin_phoeta,
            'bin_jeteta == %d'  % args.bin_jeteta,
            ]
    # use calib_chIso
    #sel_SG='region_pho == 1'
    #sel_SB='region_pho ==-1'
    # use chIsoRaw
    sel_SG='region_phoOrig == 1'
    sel_SB='region_phoOrig ==-1'
    sel_jetCut='jetSel==1'

    sel_matchGenPho='isMatched==1'
    sel_nonMatchPho='isMatched!=1'



    ''' writing histograms '''
    phohistHistory=HistCollector()
    ### data in photon part {{{
    histsetting='(10,-1.,1.)'
    hname=phohistHistory.NewHistName('data_signalRegion')
    tdata.Draw('mva >> %s%s'%(hname,histsetting), Selection(sel_binning,sel_SG))
    hname=phohistHistory.NewHistName('data_sidebandRegion')
    tdata.Draw('mva >> %s%s'%(hname,histsetting), Selection(sel_binning,sel_SB))
    hname=phohistHistory.NewHistName('data_allRegion')
    tdata.Draw('mva >> %s%s'%(hname,histsetting), Selection(sel_binning) )

    hname=phohistHistory.NewHistName('data_signalRegion_jetSel')
    tdata.Draw( 'mva >> %s%s'%(hname,histsetting), Selection(sel_binning,sel_SG,sel_jetCut) )
    hname=phohistHistory.NewHistName('data_sidebandRegion_jetSel')
    tdata.Draw( 'mva >> %s%s'%(hname,histsetting), Selection(sel_binning,sel_SB,sel_jetCut) )
    hname=phohistHistory.NewHistName('data_allRegion_jetSel')
    tdata.Draw( 'mva >> %s%s'%(hname,histsetting), Selection(sel_binning,sel_jetCut) )
    ### data end }}}

    '''  WEIGHT NEEDED!!!! '''
    evtCut=DrawSelections()
    evtCut.PutWeights('w_evt')
    ### signal MC in photon part {{{
    histsetting='(10,-1.,1.)'
    hname=phohistHistory.NewHistName('gjet_signalRegion')
    tsign.Draw('mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_SG,sel_matchGenPho)
            )
    hname=phohistHistory.NewHistName('gjet_sidebandRegion')
    tsign.Draw('mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_SB,sel_matchGenPho)
            )
    hname=phohistHistory.NewHistName('gjet_allRegion')
    tsign.Draw('mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_matchGenPho)
            )

    hname=phohistHistory.NewHistName('gjet_signalRegion_jetSel')
    tsign.Draw( 'mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_SG,sel_jetCut,sel_matchGenPho)
            )
    hname=phohistHistory.NewHistName('gjet_sidebandRegion_jetSel')
    tsign.Draw( 'mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_SB,sel_jetCut,sel_matchGenPho)
            )
    hname=phohistHistory.NewHistName('gjet_allRegion_jetSel')
    tsign.Draw( 'mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_jetCut,sel_matchGenPho)
            )
    ### signal MC end }}}
    ### background MC in photon part {{{
    histsetting='(10,-1.,1.)'
    hname=phohistHistory.NewHistName('qcd_signalRegion')
    tfake.Draw('mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_SG,sel_nonMatchPho)
            )
    hname=phohistHistory.NewHistName('qcd_sidebandRegion')
    tfake.Draw('mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_SB,sel_nonMatchPho)
            )
    hname=phohistHistory.NewHistName('qcd_allRegion')
    tfake.Draw('mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_nonMatchPho)
            )

    hname=phohistHistory.NewHistName('qcd_signalRegion_jetSel')
    tfake.Draw( 'mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_SG,sel_jetCut,sel_nonMatchPho)
            )
    hname=phohistHistory.NewHistName('qcd_sidebandRegion_jetSel')
    tfake.Draw( 'mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_SB,sel_jetCut,sel_nonMatchPho)
            )
    hname=phohistHistory.NewHistName('qcd_allRegion_jetSel')
    tfake.Draw( 'mva >> %s%s'%(hname,histsetting),
            evtCut.Selections(sel_binning,sel_jetCut,sel_nonMatchPho)
            )
    ### background MC end }}}


    jethistHistory=HistCollector()
    ''' writing histograms end '''

    oFile.cd()
    phohistHistory.ObtainHistObjects()
    jethistHistory.ObtainHistObjects()


    oDir=oFile.mkdir( 'photonFit_%d_%d_%d' % (args.bin_phoeta,args.bin_jeteta,args.bin_phopt) )
    phohistHistory.WriteTo(oDir)
    jethistHistory.WriteTo(oFile)


    oFile.Close()

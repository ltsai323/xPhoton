#!/usr/bin/env python2
# need to use ROOT verison > 6.14
import ROOT
import json

class JsonInfo(object):
    def __init__(self, jsonname):
        with open(jsonname, 'r') as jsonfile:
            info=json.load(jsonfile)


            self.iFile_data     =str(info['file_data'])
            self.iFile_sign     =str(info['file_signal'])
            self.iFile_fake     =str(info['file_QCD'])
            self.oNameTemplate  =info['OutputNameTemplate']
    def NewHistNaming(self, nametemplate):
        return nametemplate
    def OldHistNaming(self, nametemplate):
        return nametemplate % (self.bin_phoeta,self.bin_jeteta,bin_phopt)
    def OutputFileName(self):
        return self.oNameTemplate+'.root'

def Selection(*args):
    overallcuts=[]
    for argcut in args:
        if isinstance(argcut, str) : overallcuts.append(argcut)
        if isinstance(argcut, list): overallcuts.extend(argcut)
    return '&&'.join(overallcuts)
class HistCollector(object):
    def __init__(self, dirname_=''):
        self._hists=[]
        self._dirname=dirname_
        self._histSetupFunc=None
    def SetPhoEtaBin(self,bin_): self._pEtaBin=bin_
    def SetJetEtaBin(self,bin_): self._jEtaBin=bin_
    def SetPhoPtBin (self,bin_): self._pPtBin =bin_
    def ReserveHist(self,hist_): self._hists.append(hist_)
    def SetHistSetupFunc(self,func_): self._histSetupFunc=func_
    def WriteTo(self,oFile_):
        oFile_.cd()
        oDir=oFile_.mkdir( self._dirname + '_%d_%d_%d'%(self._pEtaBin,self._jEtaBin,self._pPtBin) )
        oDir.cd()
        for hist in self._hists:
            if self._histSetupFunc:
                self._histSetupFunc(hist)
            hist.Write()
class Histo1DSetup(object):
    def __init__(self):
        self._bin=1
        self._xmin=0
        self._xmax=1
        self._name='htemp'
        self._tag=''
    def SetBinning(self, bin_,xmin_,xmax_):
        self._bin=bin_
        self._xmin=xmin_
        self._xmax=xmax_
    def SetName(self,name_):
        self._name=name_
    def SetTag(self,tag_):
        self._tag=tag_
    def Get(self):
        return (self._name,self._tag,self._bin,self._xmin,self._xmax)
def Visualization(hist):
    hist.GetXaxis().SetTitle( hist.GetTitle() )
    hist.SetTitle('')

if __name__ == "__main__":
    import sys

    args=JsonInfo(sys.argv[1])

    tname='binnedTree'
    TDF = ROOT.RDataFrame
    dataframe=TDF('binnedTree',args.iFile_data)
    signframe=TDF('binnedTree',args.iFile_sign)
    fakeframe=TDF('binnedTree',args.iFile_fake)

    # use calib_chIso
    sel_SR='region_pho == 1'
    sel_SB='region_pho ==-1'
    # use chIsoRaw
    sel_jetCut='jetSel==1'

    sel_matchGenPho='isMatched> 0'
    sel_nonMatchPho='isMatched!=1'


    oFile=ROOT.TFile('newfile.root','recreate')
    oFile.cd()
    etabinning=( (pEtaBin,jEtaBin)
            for pEtaBin in range(2)
            for jEtaBin in range(3) )
    ptbinning=[ pPtBin for pPtBin in range(21) ]

    for pEtaBin, jEtaBin in etabinning:

        # 2 : inclusive photon : not to apply jet selection
        etaSel = [ 'bin_phoeta==%d' % pEtaBin ]
        if jEtaBin != 2: etaSel.append( 'bin_jeteta==%d' % jEtaBin )
        etaSelection='&&'.join(etaSel)

        etabinneddata=dataframe.Filter(etaSelection)
        etabinnedsign=signframe.Filter(etaSelection+'&&isMatched==1')
        etabinnedfake=fakeframe.Filter(etaSelection+'&&isMatched!=1')

        print('process eta binning pEta:%d jEta:%d'%(pEtaBin,jEtaBin))
        for pPtBin in ptbinning:
            ### dataframes building section {{{
            data_all=etabinneddata.Filter('bin_phopt==%d'%pPtBin)
            sign_all=etabinnedsign.Filter('bin_phopt==%d'%pPtBin)
            fake_all=etabinnedfake.Filter('bin_phopt==%d'%pPtBin)
            data_SR=data_all.Filter(sel_SR)
            sign_SR=sign_all.Filter(sel_SR)
            fake_SR=fake_all.Filter(sel_SR)
            data_SB=data_all.Filter(sel_SB)
            sign_SB=sign_all.Filter(sel_SB)
            fake_SB=fake_all.Filter(sel_SB)

            '''
            jetCut_data_all=data_all.Filter(sel_jetCut)
            jetCut_sign_all=sign_all.Filter(sel_jetCut)
            jetCut_fake_all=fake_all.Filter(sel_jetCut)
            jetCut_data_SR =data_SR .Filter(sel_jetCut)
            jetCut_sign_SR =sign_SR .Filter(sel_jetCut)
            jetCut_fake_SR =fake_SR .Filter(sel_jetCut)
            jetCut_data_SB =data_SB .Filter(sel_jetCut)
            jetCut_sign_SB =sign_SB .Filter(sel_jetCut)
            jetCut_fake_SB =fake_SB .Filter(sel_jetCut)
            '''
            ### end of dataframes building section }}}

            hists=HistCollector('photonFit')
            hists.SetPhoPtBin(pPtBin)
            hists.SetPhoEtaBin(pEtaBin)
            hists.SetJetEtaBin(jEtaBin)

            hconf=Histo1DSetup()


            hconf.SetTag('BDTscore') # section {{{
            hconf.SetBinning(10,-1.,1.)

            hconf.SetName('data_allRegion')
            hists.ReserveHist( data_all.Histo1D(hconf.Get(),'mva') )
            hconf.SetName('data_signalRegion')
            hists.ReserveHist( data_SR .Histo1D(hconf.Get(),'mva') )
            hconf.SetName('data_sidebandRegion')
            hists.ReserveHist( data_SB .Histo1D(hconf.Get(),'mva') )

            hconf.SetName('sign_allRegion')
            hists.ReserveHist( sign_all.Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'calib_mva', 'w_evt') )
            hconf.SetName('sign_signalRegion')
            hists.ReserveHist( sign_SR .Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'calib_mva', 'w_evt') )
            hconf.SetName('sign_sidebandRegion')
            hists.ReserveHist( sign_SB .Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'calib_mva', 'w_evt') )
            hconf.SetName('origsign_allRegion')
            hists.ReserveHist( sign_all.Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            hconf.SetName('origsign_signalRegion')
            hists.ReserveHist( sign_SR .Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            hconf.SetName('origsign_sidebandRegion')
            hists.ReserveHist( sign_SB .Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )

            hconf.SetName('fake_allRegion')
            hists.ReserveHist( fake_all.Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'calib_mva', 'w_evt') )
            hconf.SetName('fake_signalRegion')
            hists.ReserveHist( fake_SR .Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'calib_mva', 'w_evt') )
            hconf.SetName('fake_sidebandRegion')
            hists.ReserveHist( fake_SB .Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'calib_mva', 'w_evt') )
            hconf.SetName('origfake_allRegion')
            hists.ReserveHist( fake_all.Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            hconf.SetName('origfake_signalRegion')
            hists.ReserveHist( fake_SR .Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            hconf.SetName('origfake_sidebandRegion')
            hists.ReserveHist( fake_SB .Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            # section end }}}

            '''
            hconf.SetTag('BDTscore') # section {{{
            hconf.SetBinning(10,-1.,1.)

            hconf.SetName('jetSel_data_allRegion')
            hists.ReserveHist( jetCut_data_all.Histo1D(hconf.Get(),'mva') )
            hconf.SetName('jetSel_data_signalRegion')
            hists.ReserveHist( jetCut_data_SR .Histo1D(hconf.Get(),'mva') )
            hconf.SetName('jetSel_data_sidebandRegion')
            hists.ReserveHist( jetCut_data_SB .Histo1D(hconf.Get(),'mva') )

            hconf.SetName('jetSel_sign_allRegion')
            hists.ReserveHist( jetCut_sign_all.Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            hconf.SetName('jetSel_sign_signalRegion')
            hists.ReserveHist( jetCut_sign_SR .Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            hconf.SetName('jetSel_sign_sidebandRegion')
            hists.ReserveHist( jetCut_sign_SB .Filter(Selection(sel_matchGenPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )

            hconf.SetName('jetSel_fake_allRegion')
            hists.ReserveHist( jetCut_fake_all.Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            hconf.SetName('jetSel_fake_signalRegion')
            hists.ReserveHist( jetCut_fake_SR .Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            hconf.SetName('jetSel_fake_sidebandRegion')
            hists.ReserveHist( jetCut_fake_SB .Filter(Selection(sel_nonMatchPho)).Histo1D(hconf.Get(),'mva', 'w_evt') )
            # section end }}}
            '''
            hists.SetHistSetupFunc(Visualization)
            hists.WriteTo(oFile)
    oFile.Close()

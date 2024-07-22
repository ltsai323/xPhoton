#!/usr/bin/env python2
import json

from xPhoton.xPhoton.Managers.PathMgr import CMSPath

def ExtractDigit(word):
    digits=[]

    digit=''
    for i, c in enumerate(word):
        if c.isdigit():
            digit+=c
            if i+1 == len(word) and digit:
                digits.append(digit)
                break
            if not word[i+1].isdigit():
                digits.append(digit)
                digit=''
    return digits

def PatternAnalysis_filename(word):
    output=[ True, if 'inf' in word.lower() else False ]
    output.extend(ExtractDigit(word))
    return output
def PatternRecognization_filename(word1,word2):
    pattern1=PatternAnalysis_filename(word1)
    pattern2=PatternAnalysis_filename(word2)
    if len(pattern1)<2: return False
    if len(pattern2)<2: return False
    # recognize first and second number in filename (Inf is also a number)
    if pattern1[1] == pattern2[1]:     # 1st number
        if pattern1[0] == pattern2[0]: # Inf exists
            return True
        if pattern1[2] == pattern2[2]: # 2nd number
            return True
    return False

class XSconnector(object):
    def __init__(self, jsonname, filelist, primaryatasetlist):
        self._infiles=filelist
        self._inpdata=primaryatasetlist
        self._file=open( CMSPath(jsonname),'r')
        self._data=json.load(self._file)
        self._loadinfo=[ None ] * len(self._infiles)
        self.Match()
    def Match(self):
        self.checkDataValid()
        for idx, pd  in enumerate(self._inpdata):

            for loadcontent in self._data:
                if loadcontent['pd'] == pd:
                    self._loadinfo[idx]=loadcontent
                    break

    def checkDataValid(self):
        if not isinstance(self._infiles, (list,tuple)):
            raise IOError('input files need to be a list')
        if not isinstance(self._inpdata, (list,tuple)):
            raise IOError('input primary datasets need to be a list')
        if len(self._infiles) != len(self._inpdata):
            raise IOError('length of input files list and input primary datasets list are not the same')

    def ResetInputFiles(self, filelist):
        if len(filelist) != len(self._infiles):
            raise IOError('new file list has different length comparing to old file list')
        for idx in range(len(self._infiles)):
            oldfile=self._infiles[idx]
            newfile=filelist[idx]
            swapable=PatternRecognization_filename(newfile,oldfile)
            if not swapable:
                raise ImportError('new imported file cannot be recognized!!!!\n--- Old file : %s\n--- New file : %s' % (oldfile,newfile) )

            self._infiles[idx]=newfile




if __name__ == '__main__':
    print ExtractDigit('asdfk320kldfjto2391lksjie90489')

    '''
    bkgpythia=XSconnector(
        'xPhoton/xPhoton/data/mcInformation/summary_bkgMC_pythia.json', [
            None,
        ], [
            'QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_1000to1400_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_120to170_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_1400to1800_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_15to30_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_15to6500_FwdEnriched_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_170to300_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_1800to2400_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_2400to3200_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_300to470_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_30to50_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_3200toInf_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_470to600_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_50to80_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_600to800_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_800to1000_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8',
            'QCD_Pt_80to120_TuneCUETP8M1_13TeV_pythia8',
            ] )
        '''

    '''
    sigamcatnlo=XSconnector(
        'xPhoton/xPhoton/data/mcInformation/summary_sigMC_amcatnlo.json', [
            None,
        ], [
            'G1Jet_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-100To250_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-250To400_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-400To650_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-400To650_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-50To100_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-50To100_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-650ToInf_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            'G1Jet_Pt-650ToInf_TuneCUETP8M1_13TeV-amcatnlo-pythia8',
            ] )
        '''

    sigpythia=XSconnector(
        'xPhoton/xPhoton/data/mcInformation/summary_sigMC_pythia.json', [
            '/home/ltsai/ReceivedFile/GJet/GJet_pythia/Pt20to40_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
            '/home/ltsai/ReceivedFile/GJet/GJet_pythia/Pt20toInf_DoubleEMEnriched_MGG40to80_TuneCUETP8M1_13TeV_pythia8.root',
            '/home/ltsai/ReceivedFile/GJet/GJet_pythia/Pt40toInf_DoubleEMEnriched_MGG80toInf_TuneCUETP8M1_13TeV_pythia8.root',
        ], [
            'GJet_Pt-20to40_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8',
            'GJet_Pt-20toInf_DoubleEMEnriched_MGG-40to80_TuneCUETP8M1_13TeV_Pythia8',
            'GJet_Pt-40toInf_DoubleEMEnriched_MGG-80toInf_TuneCUETP8M1_13TeV_Pythia8',
            ] )

    sigmadgraph=XSconnector(
        'xPhoton/xPhoton/data/mcInformation/summary_sigMC_madgraph.json', [
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-100To200_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-200To400_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-400To600_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-40To100_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3-v2.root',
            '/home/ltsai/ReceivedFile/GJet/madgraphMLM/sigMC_HT-600ToInf_13TeV-madgraphMLM-pythia8_v3_ext1-v2.root',
        ], [
            'GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-100To200_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-200To400_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-400To600_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-40To100_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            'GJets_HT-600ToInf_TuneCUETP8M1_13TeV-madgraphMLM-pythia8',
            ])

    sigpythiaflat=XSconnector(
        'xPhoton/xPhoton/data/mcInformation/summary_sigMC_pythiaFlat.json', [
            '/home/ltsai/ReceivedFile/GJet/pythiaFlat/Pt1500To6000_TuneCUETP8M1Flat_20M.root',
        ], [
            'GJet_Pt-15To6000_TuneCUETP8M1-Flat_13TeV_pythia8_20M',
            ] )

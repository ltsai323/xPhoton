#!/usr/bin/env python3

import ROOT

_showInfo = True

##########################
### selection sections ###
##########################
def basic_cut():
    return 'jetPt>30. && phoFillIdx == 0 && eleVeto == 1'
def signalregion_cut():
    return '&&'.join(['chIsoRaw<2.',basic_cut()])
def datasideband_cut():
    return '&&'.join(['chIsoRaw>5.',basic_cut()])
def binning(phoETAbin, jetETAbin,ptRANGE ):
    cuts = f'recoPt>{ptRANGE[0]} && recoPt<{ptRANGE[1]}'
    if phoETAbin == 0:
        cuts += '&& TMath::Abs(recoSCEta)<1.4442'
    if phoETAbin == 1:
        cuts += '&& TMath::Abs(recoSCEta)>1.566 && TMath::Abs(recoSCEta)<2.5'
    if jetETAbin == 0:
        cuts += '&& TMath::Abs(jetEta)<1.5'
    if jetETAbin == 1:
        cuts += '&& TMath::Abs(jetEta)>1.5 && TMath::Abs(jetEta)<2.4'
    return cuts

def is_signal_pho():
    return '(isMatched == 1 || isMatched == 1 || isConverted == 1)'
def is_fake_pho():
    return f'(!{is_signal_pho()})'
def all_cuts(*args):
    the_info = '(' + '&&'.join(args) + ')'
    if _showInfo:
        funcName = all_cuts.__name__
        print(f'[INFO] {funcName:10s}: {the_info}')
    return the_info
def all_weight(arg):
    the_info = f'*({arg})'
    if _showInfo:
        funcName = all_weight.__name__
        print(f'[INFO] {funcName:10s}: {the_info}')
    return the_info

def MC_weight_general(arg = '1'): # weight to luminosity 1 fb inv
    basicWeight = 'genWeight*crossSection/integratedGenWeight*puwei'
    return all_weight('*'.join([arg,basicWeight]))
##############################
### selection sections end ###
##############################




########################
### useful functions ###
########################
def GetTree(inFILE:str):
    infile = ROOT.TFile.Open(inFILE)
    intree = infile.Get('t')

    return (infile, intree)
def draw_with_info(tree, arg_var, arg_cut):
    print(f'[ROOT] tree.Draw("{arg_var}", "{arg_cut}")\n\n')
    tree.Draw(arg_var, arg_cut)

############################
### useful functions end ###
############################



##############################
### generalization section ###
##############################
class BinningProcessor:
    def __init__(self, dataTREE, signTREE, fakeTREE):
        self.dataTree = dataTREE
        self.signTree = signTREE
        self.fakeTree = fakeTREE

    def SetBinningInfo(self, pETAbin:int, jETAbin:int, ptRANGE:tuple):
        self.bincut = binning(pETAbin, jETAbin, ptRANGE)
        self.outtag = f'{pETAbin}_{jETAbin}__ptcut_{ptRANGE[0]}_{ptRANGE[1]}'
    @property
    def bin_cut(self):
        if hasattr(self, 'bincut'):
            return getattr(self, 'bincut')
        print('[WARNING] BinningProcessor::bin_cut() : No binning info found\n\n')
        return '1' # prevent && operation failed

    def SetOutFile(self, outFILE):
        self.outfile = outFILE
        print(f'[INFO] output file {outFILE.GetName()}')
##################################
### generalization section end ###
##################################



#####################
### Main function ###
#####################

## defined a reserved name.
WEIGHT_INTEGRATION = '0'
def create_folder(oFILE:ROOT.TFile, varNAME:str):
    folderName = varNAME if varNAME != WEIGHT_INTEGRATION else 'weight_integration'
    return oFILE.mkdir(folderName)
def get_var_general(
        outFILE:ROOT.TDirectory, dataTREE, signTREE, fakeTREE, binningSTR,
        dataVAR, signVAR, fakeVAR, histBINNING:tuple, additionalWEIGHT='1'):


    outFILE.cd()
    var = dataVAR
    #outDir = outFILE.mkdir(var)
    outDir = create_folder(outFILE, var)
    outDir.cd()
    nbin = histBINNING[0]
    xmin = histBINNING[1]
    xmax = histBINNING[2]
    print( f'[INFO] binning information = {nbin}, {xmin}, {xmax}')

    hdata = ROOT.TH1F(f'hdata', var, nbin, xmin, xmax)
    hside = ROOT.TH1F(f'hside', var, nbin, xmin, xmax)
    hsign = ROOT.TH1F(f'hsign', var, nbin, xmin, xmax)
    hfake = ROOT.TH1F(f'hfake', var, nbin, xmin, xmax)

    draw_with_info(dataTREE,
            f'{dataVAR} >> {hdata.GetName()}',
            #all_cuts('phoFiredTrgs>>7&1==1', basic_cut(),binningSTR)
            all_cuts('phoFiredTrgs>>7&1==1', signalregion_cut(),binningSTR)
            + '* ( 1/19.52)' # normalize luminosity to 1 fb inv
            )
    draw_with_info(dataTREE,
            f'{dataVAR} >> {hside.GetName()}',
            all_cuts('phoFiredTrgs>>7&1==1', datasideband_cut(),binningSTR)
            + '* ( 1/19.52)' # normalize luminosity to 1 fb inv
            )
    draw_with_info(signTREE,
            f'{signVAR} >> {hsign.GetName()}',
            #all_cuts(is_signal_pho(), basic_cut(),binningSTR)
            all_cuts(is_signal_pho(), signalregion_cut(),binningSTR)
           +MC_weight_general()
            )
    draw_with_info(fakeTREE,
            f'{fakeVAR} >> {hfake.GetName()}',
            #all_cuts(is_fake_pho(),basic_cut(),binningSTR)
            all_cuts(is_fake_pho(),signalregion_cut(),binningSTR)
           +MC_weight_general()
           ## all_cuts(is_fake_pho(),basic_cut(),binningSTR, 'passMaxPUcut==1')
           # all_cuts(is_fake_pho(),signalregion_cut(),binningSTR, 'passMaxPUcut==1')
           #+MC_weight_general('weight_passMaxPUcut')
            )

    hdata.Write()
    hside.Write()
    hsign.Write()
    hfake.Write()

    norm_sign = hsign.Integral()
    norm_fake = hfake.Integral()

    del hdata
    del hside
    del hsign
    del hfake

    if additionalWEIGHT == '1': return
    print(f'[DEBUG] var "{var}" keep moving to additional weight {additionalWEIGHT}\n')
    hsign_w = ROOT.TH1F(f'hsign_weighed', var, nbin, xmin, xmax)
    hfake_w = ROOT.TH1F(f'hfake_weighed', var, nbin, xmin, xmax)
    draw_with_info(signTREE,
            f'{signVAR} >> {hsign_w.GetName()}',
            #all_cuts(is_signal_pho(), basic_cut(),binningSTR)
            all_cuts(is_signal_pho(), signalregion_cut(),binningSTR)
           +MC_weight_general(additionalWEIGHT)
            )
    draw_with_info(fakeTREE,
            f'{fakeVAR} >> {hfake_w.GetName()}',
            #all_cuts(is_fake_pho(),basic_cut(),binningSTR)
            all_cuts(is_fake_pho(),signalregion_cut(),binningSTR)
           +MC_weight_general(additionalWEIGHT)
           # all_cuts(is_fake_pho(),basic_cut(),binningSTR, 'passMaxPUcut==1')
           #+MC_weight_general('weight_passMaxPUcut')
            )

    norm_sign_w = hsign_w.Integral()
    norm_fake_w = hfake_w.Integral()

    ## re-normalization applied c-tagging rewieght.
    hsign_w.Scale(norm_sign/norm_sign_w)
    hfake_w.Scale(norm_fake/norm_fake_w)

    hsign_w.Write()
    hfake_w.Write()
    del hsign_w
    del hfake_w


#########################
### Main function end ###
#########################


class HistSetup:
    def __init__(self, varSET, histBINinfo:tuple, additionalWEIGHT = '1'):
        '''
        varSET = str : all variable used the same variable name
        vaerSET = ['data var', 'sign var', 'fake var']
        histBINinfo = (nbin, xmin, xmax)
        '''
        thesamevarname = True if isinstance(varSET, str) else False
        self.datavar = varSET if thesamevarname else varSET[0]
        self.signvar = varSET if thesamevarname else varSET[1]
        self.fakevar = varSET if thesamevarname else varSET[2]
        self.nbin = histBINinfo[0]
        self.xmin = histBINinfo[1]
        self.xmax = histBINinfo[2]
        self.weig = additionalWEIGHT

def GetVar( binPROCESSOR, histSETUP ):
    get_var_general(
            binPROCESSOR.outfile,
            binPROCESSOR.dataTree,
            binPROCESSOR.signTree,
            binPROCESSOR.fakeTree,
            binPROCESSOR.bin_cut,

            histSETUP.datavar,
            histSETUP.signvar,
            histSETUP.fakevar,
            [ histSETUP.nbin, histSETUP.xmin, histSETUP.xmax ],
            histSETUP.weig)



if __name__ == "__main__":
    import sys
    # set default value if argumented
    hasArg = len(sys.argv) == 4+1
    petabin = sys.argv[1] if hasArg else 0
    jetabin = sys.argv[2] if hasArg else 0
    pptrangelow = sys.argv[3] if hasArg else 200
    pptrangehigh = sys.argv[4] if hasArg else 99999
    _testing = False if hasArg else True


    ROOT.gROOT.SetBatch(True)

    ## load files
    infile_data, intree_data = GetTree("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/data.root")
    #infile_sign, intree_sign = GetTree("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/gjet.pythia.root")
    infile_sign, intree_sign = GetTree("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/gjet.madgraph.root")
    infile_fake, intree_fake = GetTree("/home/ltsai/ReceivedFile/GJet/latestsample/UL2016PreVFP/qcd.madgraph.root")
    #infile_data, intree_data = GetTree("/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/Run2016_Legacy_ctagReshape.root")
    #infile_sign, intree_sign = GetTree("/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/sigMC_madgraph_ctagReshaped.root")
    #infile_fake, intree_fake = GetTree("/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/QCD_madgraph_ctagReshape.root")





    ## control the outputs
    hist_SETTING = [
        HistSetup(['mva','calib_mva','calib_mva'], (20, -1.,1.)),
        HistSetup('DeepFlavour.bScore', (20, 0.,1.), 'DeepFlavour.ctagWeight.central'),
        HistSetup('DeepFlavour.CvsL',   (20, 0.,1.), 'DeepFlavour.ctagWeight.central'),
        HistSetup('DeepFlavour.CvsB',   (20, 0.,1.), 'DeepFlavour.ctagWeight.central'),
        HistSetup('DeepCSV.bScore',     (20, 0.,1.), 'DeepCSV.ctagWeight.central'),
        HistSetup('DeepCSV.CvsL',       (20, 0.,1.), 'DeepCSV.ctagWeight.central'),
        HistSetup('DeepCSV.CvsB',       (20, 0.,1.), 'DeepCSV.ctagWeight.central'),
        HistSetup('recoPhi', (40,-3.5,3.5)),
        ]


    thebin = (petabin,jetabin,[pptrangelow,pptrangehigh])
    binned_processor = BinningProcessor(intree_data, intree_sign, intree_fake)
    binned_processor.SetBinningInfo(*thebin)

    outfilename = 'out_ctaggingVars_%s.root'%binned_processor.outtag
    newfile = ROOT.TFile(outfilename, 'recreate')
    binned_processor.SetOutFile(newfile)

    ## main loop
    for h_setup in hist_SETTING:
        GetVar(binned_processor, h_setup)
        if _testing:
            print('[TESTING] end of 1 loop')
            break
    # Used to find integration
    # This is a trick to use TTree::Draw() to find out the re-normalization of ctag reweight
    # re_norm_factor = hsign.GetBinContent(1) / hsign_weighed.GetBinContent(1)
    #                = Total original weight / Total new weight
    weight_integration = HistSetup(WEIGHT_INTEGRATION, (1,0.,1.),'DeepFlavour.ctagWeight.central')
    GetVar(binned_processor, weight_integration)
    newfile.Close()

    infile_fake.Close()
    infile_sign.Close()
    infile_data.Close()

    print('[INFO] end of ctaggingVars.py')

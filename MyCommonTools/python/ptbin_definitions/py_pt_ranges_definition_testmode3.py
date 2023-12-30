#!/usr/bin/env python3
testmode = 3
currentDataEra = 'UL2016PreVFP'
def PrintTestMode():
    print('testmode', testmode)

# original version (testmode = -1)
def pt_ranges(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return (25,34,40,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000)
def hltbin_ptbin(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return ( 0, 1, 2, 3, 3, 4,  5,  5,  6,  6,  6,  7,  7,  7,  7,  7,  7,  8,  8,  8,   8)


# stable version (testmode = 0)
def pt_ranges_test_for_merge_bin(dataERA):
    # comes from step2.makehisto ptbin_ranges()
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return (25,34,56,70,100,115,135,175,190,220,250,300,350,400,500,700) # bin range = 0~15 (contain 15)
def hltbin_ptbin_definition_merbe_bin(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return ( 0, 1, 3, 3,  5,  5,  6,  6,  7,  7,  7,  7,  7,  8,  8,  8)


# test mode == 1
def pt_ranges_test_for_merge_bin_test1(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return (25,34,56,70,100,115,135,175,220,250,300,350,400,500,700)
def hltbin_ptbin_definition_merbe_bin_test1(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return ( 0, 1, 3, 3,  5,  5,  6,  7,  7,  7,  7,  7,  8,  8,  8)


# test mode == 2
def pt_ranges_test_for_merge_bin_test2(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return (25,34,56,70,100,115,135,190,220,250,300,350,400,500,700)
def hltbin_ptbin_definition_merbe_bin_test2(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return ( 0, 1, 3, 3,  5,  5,  6,  7,  7,  7,  7,  7,  8,  8,  8)

# test mode == 3
def pt_ranges_test_for_merge_bin_test3(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return (25,34,56,70,100,115,135,190,250,300,350,400,500,700)
def hltbin_ptbin_definition_merbe_bin_test3(dataERA):
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return ( 0, 1, 3, 3,  5,  5,  6,  7,  7,  7,  7,  8,  8,  8)

def ptbin_ranges_2016(dataERA):
    # comes from step2.makehisto ptbin_ranges()
    if dataERA == '2016ReReco' or dataERA == 'UL2016PreVFP' or dataERA == 'UL2016PostVFP':
        return (25,34,40,56,70,85,100,115,135,155,175,190,200,220,250,300,350,400,500,750,1000)

class HLTEntry:
    ''' creating HLT entry '''
    #def __init__(self,name_:str,effLUMI_:float) -> None:
    def __init__(self,name_,effLUMI_):
        self.name = name_
        self.effLumi = effLUMI_
    @property
    def EffLuminosity(self):
        return self.effLumi

# update at 2023/May/19
HLTBIT_2016_106X = {
    0: HLTEntry("hltEG22HEFilter", 0.0016),
    1: HLTEntry("hltEG30HEFilter", 0.0066),
    2: HLTEntry("hltEG36HEFilter", 0.0132),
    3: HLTEntry("hltEG50HEFilter", 0.0264),
    4: HLTEntry("hltEG75HEFilter", 0.13),
    5: HLTEntry("hltEG90HEFilter", 0.26),
    6: HLTEntry("hltEG120HEFilter", 0.54),
    7: HLTEntry("hltEG175HEFilter", 36.47),
    8: HLTEntry("hltEG300erEtFilter", 36.47),
    }
HLTBIT_UL2016PreVFP = {
        0: HLTEntry("hltEG22HEFilter" , 0.001037),
        1: HLTEntry("hltEG30HEFilter" , 0.004471),
        2: HLTEntry("hltEG36HEFilter" , 0.008846),
        3: HLTEntry("hltEG50HEFilter" , 0.018724),
        4: HLTEntry("hltEG75HEFilter" , 0.082953),
        5: HLTEntry("hltEG90HEFilter" , 0.16333),
        6: HLTEntry("hltEG120HEFilter", 0.338109),
        7: HLTEntry("hltEG175HEFilter", 19.497897),
    8: HLTEntry("hltEG300erEtFilter", 19.497897),
        }
HLTBIT_UL2016PostVFP = {
        0: HLTEntry("hltEG22HEFilter" , 0.000578),
        1: HLTEntry("hltEG30HEFilter" , 0.002208),
        2: HLTEntry("hltEG36HEFilter" , 0.004424),
        3: HLTEntry("hltEG50HEFilter" , 0.012644),
        4: HLTEntry("hltEG75HEFilter" , 0.053053),
        5: HLTEntry("hltEG90HEFilter" , 0.103566),
        6: HLTEntry("hltEG120HEFilter", 0.20459),
        7: HLTEntry("hltEG175HEFilter", 16.812151),
    8: HLTEntry("hltEG300erEtFilter", 16.812151),
        }


def PhoPtBinning(dataERA):
    if testmode == -1:
        return pt_ranges(dataERA)
    if testmode == 0:
        return pt_ranges_test_for_merge_bin(dataERA)
    if testmode == 1:
        return pt_ranges_test_for_merge_bin_test1(dataERA)
    if testmode == 2:
        return pt_ranges_test_for_merge_bin_test2(dataERA)
    if testmode == 3:
        return pt_ranges_test_for_merge_bin_test3(dataERA)
def ptbin_ranges(dataERA): #asdf tmp func
    return PhoPtBinning(dataERA)
def hltbin_ptbin_definition(dataERA):
    if testmode == -1:
        return hltbin_ptbin(dataERA)
    if testmode == 0:
        return hltbin_ptbin_definition_merbe_bin(dataERA)
    if testmode == 1:
        return hltbin_ptbin_definition_merbe_bin_test1(dataERA)
    if testmode == 2:
        return hltbin_ptbin_definition_merbe_bin_test2(dataERA)
    if testmode == 3:
        return hltbin_ptbin_definition_merbe_bin_test3(dataERA)
    return None
def FindEffLumi(dataERA, ptBIN):
    hltbit_definition = None
    if dataERA == '2016ReReco':
        hltbit_definition = HLTBIT_2016_106X
    if dataERA == "UL2016PreVFP":
        hltbit_definition = HLTBIT_UL2016PreVFP
    if dataERA == "UL2016PostVFP":
        hltbit_definition = HLTBIT_UL2016PostVFP
    if hltbit_definition == None: raise ValueError('FindEffLumi() : input dataera %s is not valid'%dataERA)

    ggbit = hltbin_ptbin_definition(dataERA)[ptBIN]
    return hltbit_definition[ggbit].EffLuminosity
if __name__ == "__main__":
    def get_pt_region(arr,idx):
        l_val = str(arr[idx])
        r_val = str(arr[idx+1]) if idx+1 < len(arr) else 'inf'
        return f'[{l_val},{r_val}]'
    pho_pt_def = PhoPtBinning(currentDataEra)
    hlt_bining = hltbin_ptbin_definition(currentDataEra)
    for idx,hltbit in enumerate(hlt_bining):
        print(f'@pt bin {idx:2d} : {get_pt_region(pho_pt_def,idx)} \t with hlt bin {hltbit} and eff lumi {FindEffLumi(currentDataEra,idx)}')


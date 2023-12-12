#!/usr/bin/env python3

import ROOT
class DAT:
    def __init__(self,evt):
        self.petabin = evt.EBEE
        self.jetabin = evt.jetbin
        self.pptbin = evt.ptbin
    @property
    def val(self):
        if hasattr(self,'value'): return getattr(self,'value')
        raise ValueError('DAT:: No value set in the record')
    @property
    def err(self):
        if hasattr(self,'error'): return getattr(self,'error')
        raise ValueError('DAT:: No error set in the record')

    def is_bin(self,pETAbin,jETAbin,pPTbin):
        if pETAbin != self.petabin: return False
        if jETAbin != self.jetabin: return False
        if pPTbin  != self.pptbin : return False
        return True
    def record(self, val, err):
        self.value = val
        self.error = err
    def __str__(self,newstr):
        return 'bins(%d,%d,%d): %s' % (self.petabin,self.jetabin,self.pptbin,newstr)


def ReadEvt(inputfile, DAT_STRUCTURE) -> list:
    inputtree=ROOT.TTree('dat_read_tree','')
    inputtree.ReadFile(inputfile)

    output_rec = []
    for evt in inputtree:
        output_rec.append(DAT_STRUCTURE(evt))
    return output_rec

#ptbin/I:EBEE/I:jetbin/I:fitvalue/F:fiterror/F
class DAT_FitResult(DAT):
    def __init__(self,evt):
        super().__init__(evt)
        self.record(evt.fitvalue, evt.fiterror)

    def __str__(self):
        return super().__str__( 'fits (%8.4f +- %8.4f)' % (self.val,self.err) )
    def __repr__(self):
        return self.__str__()
def ReadEvt_FitResult(inputfile) -> DAT_FitResult:
    return ReadEvt(inputfile, DAT_FitResult)


#ptbin/I:EBEE/I:jetbin/I:sel_passed/F:sel_overall/F:sel_ratio/F:sig_passed/F:sig_overall/F:sig_ratio/F
class DAT_Efficiency(DAT):
    class Eff:
        def __init__(self, _pass, _all, _eff):
            self.passed = _pass
            self.overall = _all
            self.efficiency = _eff
        @property
        def ratio(self):
            return self.efficiency

    def __init__(self,evt):
        super().__init__(evt)
        self.selection = DAT_Efficiency.Eff(evt.sel_passed, evt.sel_overall, evt.sel_ratio)
        self.sigregion = DAT_Efficiency.Eff(evt.sig_passed, evt.sig_overall, evt.sig_ratio)
    def __str__(self):
        return super().__str__( 'selection efficiency = %8.4f and signral region efficiency = %8.4f' % (self.selection.ratio, self.sigregion.ratio) )
def ReadEvt_Efficiencies(inputfile) -> DAT_Efficiency:
    return ReadEvt(inputfile, DAT_Efficiency)

#ptbin/I:EBEE/I:jetbin/I:sel_passed/F:sel_overall/F:sel_ratio/F:sig_passed/F:sig_overall/F:sig_ratio/F
class DAT_SignalRegionEfficiency(DAT):
    def __init__(self,evt):
        super().__init__(evt)
        self.record(evt.sig_ratio,0.)
    def __str__(self):
        return super().__str__( 'fiducial photon efficiency (%8.4f +- %8.4f)' % (self.val,self.err) )
def ReadEvt_SignalRegEff(inputfile) -> DAT_SignalRegionEfficiency:
    return ReadEvt(inputfile, DAT_SignalRegionEfficiency)

#ptbin/I:EBEE/I:jetbin/I:sel_passed/F:sel_overall/F:sel_ratio/F:sig_passed/F:sig_overall/F:sig_ratio/F
class DAT_SelectionEfficiency(DAT):
    def __init__(self,evt):
        super().__init__(evt)
        self.record(evt.sel_ratio,0.)
    def __str__(self):
        return super().__str__( 'selection (%8.4f +- %8.4f)' % (self.val,self.err) )
def ReadEvt_SelectionEff(inputfile) -> DAT_SelectionEfficiency:
    return ReadEvt(inputfile, DAT_SelectionEfficiency)
#phoeta/I:jeteta/I:phopt/I:efficiency/F
class DAT_PreselectionEfficiency(DAT):
    def __init__(self,evt):
        super().__init__(evt)
        self.record(evt.efficiency,0.)
    def __str__(self):
        return super().__str__( 'preselection (%8.4f +- %8.4f)' % (self.val,self.err) )
def ReadEvt_PreSelectEff(inputfile) -> DAT_PreselectionEfficiency:
    return ReadEvt(inputfile, DAT_PreselectionEfficiency)
#phoeta/I:jeteta/I:phopt/I:efficiency/F:error/F
class DAT_Eff(DAT):
    def __init__(self,evt):
        super().__init__(evt)
        self.record(evt.efficiency,0.)
    def __str__(self):
        return super().__str__( 'preselection (%8.4f +- %8.4f)' % (self.val,self.err) )
def ReadEvt_Eff(inputfile) -> DAT_Eff:
    return ReadEvt(inputfile, DAT_Eff)


def BinValue(pETAbin:int,jETAbin:int,pPTbin:int, vals:DAT) -> tuple:
    for val in vals:
        if val.is_bin(pETAbin,jETAbin,pPTbin):
            return (val.val,val.err)
    raise ValueError('BinValue(): bin %d %d %d not found in %s', pETAbin,jETAbin,pPTbin, vals)

if __name__ == "__main__":
    inputfile='/home/ltsai/ReceivedFile/GJet/latestsample/2016ReReco_ctagReshaped/deepcsv_CUT_NOCUT/2016ReReco.data.yield.dat'
    fitvalues = ReadEvt_FitResult(inputfile)

    for pEtaBin in range(2):
        for jEtaBin in range(2):
            for pPtBin in range(5):
                fitvalue, fiterror = BinValue(pEtaBin,jEtaBin,pPtBin, fitvalues)
                print(f'[INFO] @bin {pEtaBin}_{jEtaBin}_{pPtBin} : fit value and error = {fitvalue} +- {fiterror}')

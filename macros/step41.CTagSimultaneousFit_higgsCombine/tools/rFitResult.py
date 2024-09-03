#!/usr/bin/env python3
import ROOT
class FitVar:
    def __init__(self,var):
        self.val = var.getVal()
        self.err = var.getError()
        self.errUp = var.getErrorHi()
        self.errDn = var.getErrorLo()
    def __str__(self):
        return f'val = {self.val}+-{self.err}. And errUp {self.errUp} / errDn {self.errDn}'

def GetFitResult(inFILE:str) -> dict:
    #inFILE = 'multidimfitTest.root'
    ''' result:
    PUweight val = 0.025027585999296546+-1.3555026083729884. And errUp 1.3555026083729884 / errDn -1.3555026083729884
    Stat val = -0.03884253883541512+-0.19699998109081382. And errUp 0.19699998109081382 / errDn -0.19699998109081382
    mu1 val = 4.8428990684056+-32.88114017569109. And errUp 29.26527341270537 / errDn 0.0
    mu2 val = 109.15928168395632+-20.263257233806584. And errUp 17.605021747587458 / errDn -20.465670226838355
    mu3 val = 49.451955261251506+-18.302456140192273. And errUp 16.57968726890065 / errDn -19.645158784265114
    '''

    infile = ROOT.TFile.Open(inFILE)
    fitres = infile.Get('fit_mdf')
    var_dict = { v.GetName():v for v in  fitres.floatParsFinal() }
    infile.Close()

    return { name:FitVar(var) for name,var in var_dict.items() }


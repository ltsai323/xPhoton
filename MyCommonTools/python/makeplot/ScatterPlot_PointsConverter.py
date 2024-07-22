#!/usr/bin/env python3
import makeplot.LoadCSVFile as lCSV
from dataclasses import dataclass
from uncertainties import ufloat
from typing import List # used before python3.9

PRINT_BUG = False
def BUG(*args):
    if PRINT_BUG: print('[BUG] ', *args)

class XYArrayExtract:
    def __init__(self, phoPTvals:list):
        self._phoPt = phoPTvals
    #def GetXarr(self,pPTbinnedCONTENTlist:list[lCSV.CSVBinnedValue]):
    def GetXarr(self,pPTbinnedCONTENTlist:List[lCSV.CSVBinnedValue]):
        implementNULL = False

        xy_values = { self._phoPt[v.pPtBin]: v.value for v in pPTbinnedCONTENTlist }
        if implementNULL:
            for ppt in self._phoPt:
                if not ppt in xy_values:
                    xy_values[ppt] = NULLVAL
        x_value = [ k            for k in sorted(xy_values.keys()) ]
        return x_value
    #def GetYarr(self,pPTbinnedCONTENTlist:list[lCSV.CSVBinnedValue]):
    def GetYarr(self,pPTbinnedCONTENTlist:List[lCSV.CSVBinnedValue]):
        implementNULL = False

        xy_values = { self._phoPt[v.pPtBin]: v.value for v in pPTbinnedCONTENTlist }
        if implementNULL:
            for ppt in self._phoPt:
                if not ppt in xy_values:
                    xy_values[ppt] = NULLVAL
        y_value = [ xy_values[k] for k in sorted(xy_values.keys()) ]
        return y_value

## used as the input x-y points of matplotlib
@dataclass
class XYscatterPoints:
#class MatPlotDrawables:
    x:[float]
    y:[float]
    y_err:[float]
    desc:str

    def __repr__(self):
        return f'XYscatterPoints: {self.desc}'
def default_XYscatterPoints():
    return XYscatterPoints(x=[],y=[],y_err=[],desc='no any value inside')

## generator. Used in for loop. The first input becomes denominator. The others are numerator.
from typing import Generator
def take_ratio_without_error(xySCATTERwithDESC:[XYscatterPoints]) -> Generator[XYscatterPoints,None,None]:
    value_error_dict = lambda my_obj: { x:ufloat(v,e) for x,v,e in zip(my_obj.x,my_obj.y,my_obj.y_err) }
    denominator = value_error_dict(xySCATTERwithDESC[0])

    for idx, xy_scatter_with_desc in enumerate(xySCATTERwithDESC[1:]):
        BUG(xy_scatter_with_desc)
        numerator = value_error_dict(xy_scatter_with_desc)
        BUG('numerator ', numerator)
        BUG('denominator ', denominator)

        xList = [                          x  for x in numerator.keys() if x in denominator and abs(denominator[x]) > 1e-12 ]
        BUG(xList)
        #ratio = [ numerator[x]/denominator[x] for x in xList ]
        ratio = []
        for x in xList:
            BUG(' value a/b = %.3e/%.3e'%(numerator[x].nominal_value,denominator[x].nominal_value))
            ratio.append(numerator[x]/denominator[x])
        yield XYscatterPoints(
                x=xList, y=[r.nominal_value for r in ratio],y_err=[r.std_dev for r in ratio],desc=xy_scatter_with_desc.desc)
def take_ratio_with_error(xySCATTERwithDESC:[XYscatterPoints]) -> Generator[XYscatterPoints,None,None]:
    value_error_dict = lambda my_obj: { x:ufloat(v,e) for x,v,e in zip(my_obj.x,my_obj.y,my_obj.y_err) }
    denominator = value_error_dict(xySCATTERwithDESC[0])

    for idx, xy_scatter_with_desc in enumerate(xySCATTERwithDESC[1:]):
        BUG(xy_scatter_with_desc)
        numerator = value_error_dict(xy_scatter_with_desc)
        BUG('numerator ', numerator)
        BUG('denominator ', denominator)

        xList = [                          x  for x in numerator.keys() if x in denominator and abs(denominator[x]) > 1e-12 ]
        BUG(xList)
        #ratio = [ numerator[x]/denominator[x] for x in xList ]
        ratio = []
        for x in xList:
            BUG(' value a/b = %.3e/%.3e'%(numerator[x].nominal_value,denominator[x].nominal_value))
            ratio.append(numerator[x]/denominator[x])
        yield XYscatterPoints(
                x=xList, y=[r.nominal_value for r in ratio],y_err=[r.std_dev for r in ratio],desc=xy_scatter_with_desc.desc)
def TakeRatio(xySCATTERwithDESC:[XYscatterPoints]) -> Generator[XYscatterPoints,None,None]:
    return take_ratio_with_error(xySCATTERwithDESC)
if __name__ == "__main__":
    print('hi')

    from py_pt_ranges_definition import PhoPtBinning
    pt_axis = PhoPtBinning('UL2016PreVFP')
    a = XYArrayExtract(pt_axis)
    ps = [
            lCSV.CSVBinnedValue(2,13.5),
            lCSV.CSVBinnedValue(3,23.5),
            lCSV.CSVBinnedValue(7,73.5),
            ]
    print(a.GetXarr(ps),a.GetYarr(ps) )

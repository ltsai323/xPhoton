#!/usr/bin/env python3
import matplotlib.pyplot as plt
import makeplot.tools as myTool
from makeplot.ratiotool import TakeRatio
from makeplot.drawingprocess import DrawingProcess
from makeplot.file_collecter import FileWithDesc
from makeplot.ratiotool import draw_EP_ratio

class NewFileWithDesc:
    def __init__(self, fRATIOu, fRATIOd, desC):
        self.fRatioU = fRATIOu
        self.fRatioD = fRATIOd
        self.desc = desC
def get_data_point(theINPUT:FileWithDesc) -> myTool.XYscatterPoints:
    from py_pt_ranges_definition import FindEffLumi
    def get_data_point_(inCSVfile:str, desc:str,pETAbin:int,jETAbin:int) -> myTool.XYscatterPoints:
        value_pair = myTool.LoadCSVFile(inCSVfile, 'fit_yield_C', pETAbin,jETAbin)
        error_pair = myTool.LoadCSVFile_CopyNullEntry(value_pair, 0.)
        ptbins = ( p.pPtBin for p in value_pair )
        eff_lumis = [ FindEffLumi('UL2016PreVFP',ptbin) for ptbin in ptbins ]


        pt_arr,_values = myTool.GetXYscatterPOINT(value_pair)
        _     , errors = myTool.GetXYscatterPOINT(error_pair)
        eta_scaler = 1.4442*2 if pETAbin == 0 else (2.5-1.556)*2
        pt_scaler = lambda idx: pt_arr[idx+1]-pt_arr[idx] if idx+1 < len(pt_arr) else -999
        #values = [ v/eff_lumis[idx]/pt_scaler(idx)/eta_scaler for idx,v in enumerate(_values ) ] ## differential cross section
        values = _values ## yield

        return myTool.XYscatterPoints(x=pt_arr,y=values,y_err=errors,desc=desc)
    barrel_data_point = get_data_point_(theINPUT.file,theINPUT.desc+'in barrel photon region',0,0)
    endcap_data_point = get_data_point_(theINPUT.file,theINPUT.desc+'in endcap photon region',1,0)
    return [endcap_data_point,barrel_data_point]

def draw_scatter_plot(
        yRANGE:list,
        xySCATTERpointS:[myTool.XYscatterPoints],
        inTITLE:str = '$\gamma$+c yield ratio in barrel photon and endcap photon',
        outFIGname:str = 'h_testbarrelpho.png',
        ):

    draw_EP_ratio( xySCATTERpointS,
            yTITLE='fitted yield of $\gamma$+c ',
            yRANGE = yRANGE,
            logY = True,
            ratioTITLE = 'barrel/endcap',
            ratioYrange = (0.5,5.5),
            inTITLE=inTITLE)
    plt.savefig(outFIGname)
    print(f'[fig output - LOG] {outFIGname}')
    plt.close()



if __name__ == "__main__":
    import makeplot.file_collecter as inputs
    f = inputs.FileWithDesc(
            file='DeepCSV_gjetPythia_cutIdx5_mergeBin_4/UL2016.CTag_SimulFit.csv',
            desc='UL2016 preVFP data')

    def task(draw_obj):
        the_title = 'testing hiii $\gamma$'
        draw_obj.DrawSingle(f,
                inTITLE=the_title,
            outFIGtemplate='barrel.pdf')

    tag='UL2016PreVFP_data'
    task( DrawingProcess(draw_scatter_plot,hackDATAfunc=get_data_point,taG=tag) )

#!/usr/bin/env python3
from makeplot_ratiotool import TakeRatio
import matplotlib.pyplot as plt
from makeplot_tools import  draw_EP
from makeplot_ratiotool import draw_EP_ratio
from makeplot_tools import XYscatterPoints
from makeplot_drawingprocess import DrawingProcess,HackData
import makeplot_tools as myTool

def draw_scatter_plot(
        yRANGE:list,
        xySCATTERpointS:[XYscatterPoints],
        inTITLE:str = '',
        outFIGname:str = 'h_testbarrelpho.png',
        ):

    print(f'[fig output - LOG] Generating {outFIGname}')
    draw_EP_ratio( xySCATTERpointS,
            yTITLE='weighed $\gamma$+c yield',
            yRANGE = yRANGE,
            logY = True,
            inTITLE=inTITLE,
            ratioTITLE = 'Matching Eff',
            ratioYrange = (0.3,1.05),
            )
    plt.savefig(outFIGname)
    plt.close()


class NewFileWithDesc:
    def __init__(self, fRATIOu, fRATIOd, desC):
        self.fRatioU = fRATIOu
        self.fRatioD = fRATIOd
        self.desc = desC
def get_data_point(theINPUT:NewFileWithDesc,pETAbin:int=0,jETAbin:int=0) -> XYscatterPoints:
    def get_data_point_(inCSVfile:str, desc:str,pETAbin:int,jETAbin:int) -> XYscatterPoints:
        value_pair = myTool.LoadCSVFile(inCSVfile, 'value', pETAbin,jETAbin)
        error_pair = myTool.LoadCSVFile(inCSVfile, 'error', pETAbin,jETAbin)

        pt_arr, values = myTool.GetXYscatterPOINT(value_pair)
        _     , errors = myTool.GetXYscatterPOINT(error_pair)

        return XYscatterPoints(x=pt_arr,y=values,y_err=errors,desc=desc)

    U_data_point = get_data_point_(theINPUT.fRatioU,theINPUT.desc,pETAbin,jETAbin)
    D_data_point = get_data_point_(theINPUT.fRatioD,theINPUT.desc,pETAbin,jETAbin)
    inputdatapoint = [D_data_point,U_data_point]
    return list(TakeRatio(inputdatapoint))[0]
def get_data_point_barrel(theINPUT) -> XYscatterPoints:
    return get_data_point(theINPUT, pETAbin=0,jETAbin=0)
def get_data_point_endcap(theINPUT) -> XYscatterPoints:
    return get_data_point(theINPUT, pETAbin=1,jETAbin=0)


def draw_scatter_plot_ratio(
        yRANGE:list,
        xySCATTERpointS:[XYscatterPoints],
        inTITLE:str = 'truth $\gamma$+c / $\gamma$+b',
        outFIGname:str = 'h_testbarrelpho.png',
        ):

    print(f'[fig output - LOG] Generating {outFIGname}')
    draw_EP( xySCATTERpointS,
            yTITLE = 'weighed $\gamma$+c yield',
            yRANGE = yRANGE,
            logY = False,
            inTITLE = inTITLE)
    plt.savefig(outFIGname)
    plt.close()
if __name__ == "__main__":
    import makeplot_file_collecter as inputs
    f1L = inputs.mcLeadingC_intrinsicC_0118_nf5
    f2L = inputs.mcLeadingC_perturbativeC_0118_nf5
    f3L = inputs.mcLeadingC_perturbativeC_0118_nf3

    f1P = inputs.mcPredictedC_intrinsicC_0118_nf5
    f2P = inputs.mcPredictedC_perturbativeC_0118_nf5
    f3P = inputs.mcPredictedC_perturbativeC_0118_nf3
    def task(draw_obj):
        draw_obj.DrawSingle( f1P,f1L,inTITLE='$\gamma$+c yield from 5NFS intrinsic charm',outFIGtemplate = 'NNPDF31_nlo_as_0118.pdf')
        draw_obj.DrawSingle( f2P,f2L,inTITLE='$\gamma$+c yield from 5NFS perturbative charm',outFIGtemplate = 'NNPDF31_nlo_pch_as_0118.pdf')
        draw_obj.DrawSingle( f3P,f3L,inTITLE='$\gamma$+c yield from 3NFS perturbative charm',outFIGtemplate = 'NNPDF31_nlo_pch_as_0118_nf3.pdf')

    tag = 'LeadingCEff'
    task( DrawingProcess(draw_scatter_plot,hackDATAfunc=HackData.barrel_data,taG='_'.join([tag,'barrelPho'])) )
    task( DrawingProcess(draw_scatter_plot,hackDATAfunc=HackData.endcap_data,taG='_'.join([tag,'endcapPho'])) )



    f1 = NewFileWithDesc( f1L.file,f1P.file, '5NFS intrinsic charm' )
    f2 = NewFileWithDesc( f2L.file,f2P.file, '5NFS perturbative charm' )
    f3 = NewFileWithDesc( f3L.file,f3P.file, '3NFS perturbative charm' )

    def task(draw_obj):
        draw_obj.DrawSingle( f1,f2,f3 ,inTITLE='Matching efficiency between $\gamma$+leading jet over $\gamma$+c',outFIGtemplate = 'all.pdf')

    tag = 'LeadingCEff'
    task( DrawingProcess(draw_scatter_plot_ratio,hackDATAfunc=get_data_point_barrel,taG='_'.join([tag,'barrelPho'])) )
    task( DrawingProcess(draw_scatter_plot_ratio,hackDATAfunc=get_data_point_endcap,taG='_'.join([tag,'endcapPho'])) )

#!/usr/bin/env python3
import matplotlib.pyplot as plt
import makeplot.tools as myTool
from makeplot.ratiotool import TakeRatio
from makeplot.drawingprocess import DrawingProcess
from makeplot.file_collecter import FileWithDesc

class NewFileWithDesc:
    def __init__(self, fRATIOu, fRATIOd, desC):
        self.fRatioU = fRATIOu
        self.fRatioD = fRATIOd
        self.desc = desC
def get_data_point(theINPUT:FileWithDesc) -> myTool.XYscatterPoints:
    def get_data_point_(inCSVfile:str, desc:str,pETAbin:int,jETAbin:int) -> myTool.XYscatterPoints:
        value_pair = myTool.LoadCSVFile(inCSVfile, 'value', pETAbin,jETAbin)
        error_pair = myTool.LoadCSVFile(inCSVfile, 'error', pETAbin,jETAbin)

        pt_arr, values = myTool.GetXYscatterPOINT(value_pair)
        _     , errors = myTool.GetXYscatterPOINT(error_pair)

        return myTool.XYscatterPoints(x=pt_arr,y=values,y_err=errors,desc=desc)
    barrel_data_point = get_data_point_(theINPUT.file,theINPUT.desc,0,0)
    endcap_data_point = get_data_point_(theINPUT.file,theINPUT.desc,1,0)
    return list(TakeRatio( [endcap_data_point,barrel_data_point] ))[0]

def draw_scatter_plot(
        yRANGE:list,
        xySCATTERpointS:[myTool.XYscatterPoints],
        inTITLE:str = '$\gamma$+c yield ratio in barrel photon and endcap photon',
        outFIGname:str = 'h_testbarrelpho.png',
        ):

    myTool.draw_EP( xySCATTERpointS,
            yTITLE='ratio to $\gamma$+c in barrel/endcap',
            yRANGE = yRANGE,
            logY = False,
            inTITLE=inTITLE)
    plt.savefig(outFIGname)
    print(f'[fig output - LOG] {outFIGname}')
    plt.close()



if __name__ == "__main__":
    import makeplot.file_collecter as inputs
    #f1 = inputs.mcPredictedC_intrinsicC_0118_nf5
    #f2 = inputs.mcPredictedC_perturbativeC_0118_nf5
    #f3 = inputs.mcPredictedC_perturbativeC_0118_nf3
    f1 = inputs.mc_tester_c
    f2 = inputs.mc_tester_b

    def task(draw_obj):
        the_title = 'testing hiii $\gamma$'
        draw_obj.DrawSingle( f1, f2,
                inTITLE=the_title,
            outFIGtemplate='checking.pdf')

    tag='ratioOfBarrelCtoEndcapC_predicted'
    task( DrawingProcess(draw_scatter_plot,hackDATAfunc=get_data_point,taG=tag) )

#!/usr/bin/env python3
import matplotlib.pyplot as plt
import makeplot.tools as myTool
from makeplot.ratiotool import TakeRatio
from makeplot.drawingprocess import DrawingProcess
from makeplot.file_collecter import FileWithDesc
from makeplot.ratiotool import draw_EP_ratio,draw_EP_ratio_lowerLined
import makeplot.ScatterPlot_PointsConverter as pointConv
import makeplot.LoadCSVFile as lCSV
from uncertainties import ufloat

class NewFileWithDesc:
    def __init__(self, fRATIOu, fRATIOd, desC):
        self.fRatioU = fRATIOu
        self.fRatioD = fRATIOd
        self.desc = desC
def get_data_point(theINPUT:FileWithDesc) -> pointConv.XYscatterPoints:
    from py_pt_ranges_definition import FindEffLumi, PhoPtBinning
    pt_binning = PhoPtBinning('UL2016PreVFP')
    def get_data_point_(inCSVfile:str, desc:str,pETAbin:int,jETAbin:int) -> pointConv.XYscatterPoints:
        value_pair = lCSV.LoadCSVFile(inCSVfile, 'fit_yield_C', pETAbin,jETAbin)
        error_pair = lCSV.LoadCSVFile(inCSVfile, 'fit_error_C', pETAbin,jETAbin)

        jetsel_eff = lCSV.LoadCSVFile(csv_jetsel, 'efficiency', pETAbin, jETAbin)
        jetsel_err = lCSV.LoadCSVFile(csv_jetsel, 'error'     , pETAbin, jETAbin)
        phoreg_eff = lCSV.LoadCSVFile(csv_phoreg, 'efficiency', pETAbin, jETAbin)
        phoreg_err = lCSV.LoadCSVFile(csv_phoreg, 'error'     , pETAbin, jETAbin)
        presel_eff = lCSV.LoadCSVFile(csv_presel, 'efficiency', pETAbin, jETAbin)
        presel_err = lCSV.LoadCSVFile(csv_presel, 'error'     , pETAbin, jETAbin)
        ptbins = ( p.pPtBin for p in value_pair )
        eff_lumis = [ FindEffLumi('UL2016PreVFP',ptbin) for ptbin in ptbins ]


        conv = pointConv.XYArrayExtract(pt_binning)
        pt_arr = conv.GetXarr(value_pair)
        yields = conv.GetYarr(value_pair)
        errors = conv.GetYarr(error_pair)

        js_eff = conv.GetYarr(jetsel_eff)
        js_err = conv.GetYarr(jetsel_err)
        pr_eff = conv.GetYarr(phoreg_eff)
        pr_err = conv.GetYarr(phoreg_err)
        ps_eff = conv.GetYarr(presel_eff)
        ps_err = conv.GetYarr(presel_err)
        unfold_yield = []
        unfold_error = []
        for y,e,jse,jsE,pre,prE,pse,psE in zip(yields,errors,js_eff,js_err,pr_eff,pr_err,ps_eff,ps_err):
            the_yield = ufloat(y,e)
            eff_js = ufloat(jse,jsE)
            eff_pr = ufloat(pre,prE)
            eff_ps = ufloat(pse,psE)
            unfold_value = the_yield/eff_js/eff_pr/eff_ps
            unfold_yield.append(unfold_value.nominal_value)
            unfold_error.append(unfold_value.std_dev)


        eta_scaler = 1.4442*2 if pETAbin == 0 else (2.5-1.556)*2
        pt_scaler = lambda idx: pt_arr[idx+1]-pt_arr[idx] if idx+1 < len(pt_arr) else 999999.
        #values = [ v/eff_lumis[idx]/pt_scaler(idx)/eta_scaler for idx,v in enumerate(yields) ] ## differential cross section
        values = [ v/eff_lumis[idx]/pt_scaler(idx)/eta_scaler for idx,v in enumerate(unfold_yield) ] ## differential cross section
        error_ = [ v/eff_lumis[idx]/pt_scaler(idx)/eta_scaler for idx,v in enumerate(unfold_error) ] ## differential cross section

        return pointConv.XYscatterPoints(x=pt_arr,y=values,y_err=error_,desc=desc)
    barrel_data_point = get_data_point_(theINPUT.file,theINPUT.desc+' in barrel photon region',0,0)
    #endcap_data_point = get_data_point_(theINPUT.file,theINPUT.desc+' in endcap photon region',1,0)
    return [barrel_data_point]
def get_data_point_MC(theINPUT:FileWithDesc) -> pointConv.XYscatterPoints:
    from py_pt_ranges_definition import FindEffLumi, PhoPtBinning
    pt_binning = PhoPtBinning('UL2016PreVFP')
    def get_data_point_(inCSVfile:str, desc:str,pETAbin:int,jETAbin:int) -> pointConv.XYscatterPoints:
        value_pair = lCSV.LoadCSVFile(inCSVfile, 'value', pETAbin,jETAbin)
        error_pair = lCSV.LoadCSVFile(inCSVfile, 'error', pETAbin,jETAbin)
        #error_pair = lCSV.LoadCSVFile_CopyNullEntry(value_pair, 0.)
        ptbins = ( p.pPtBin for p in value_pair )
        eff_lumis = [ FindEffLumi('UL2016PreVFP',ptbin) for ptbin in ptbins ]


        conv = pointConv.XYArrayExtract(pt_binning)
        pt_arr = conv.GetXarr(value_pair)
        yields = conv.GetYarr(value_pair)
        errors = conv.GetYarr(error_pair)
        eta_scaler = 1.4442*2 if pETAbin == 0 else (2.5-1.556)*2
        pt_scaler = lambda idx: pt_arr[idx+1]-pt_arr[idx] if idx+1 < len(pt_arr) else -999
        values = [ v/eff_lumis[idx]/pt_scaler(idx)/eta_scaler for idx,v in enumerate(yields) ] ## differential cross section

        return pointConv.XYscatterPoints(x=pt_arr,y=values,y_err=errors,desc=desc)
    barrel_data_point = get_data_point_(theINPUT.file,theINPUT.desc+' in barrel photon region',0,0)
    #endcap_data_point = get_data_point_(theINPUT.file,theINPUT.desc+' in endcap photon region',1,0)
    return [barrel_data_point]

def draw_scatter_plot(
        yRANGE:list,
        xySCATTERpointS:[pointConv.XYscatterPoints],
        inTITLE:str = '$\gamma$+c yield ratio in barrel photon and endcap photon',
        outFIGname:str = 'h_testbarrelpho.png',
        ):

    #plt.clf()
    draw_EP_ratio( xySCATTERpointS,
    #draw_EP_ratio_lowerLined( xySCATTERpointS,
            #yTITLE='fitted yield of $\gamma$+c ',
            yTITLE='$d^2\sigma/dp^\gamma_T d\eta^\gamma$',
            yRANGE = yRANGE,
            logY = True,
            ratioTITLE = 'barrel/endcap',
            #ratioYrange = (0.5,5.5),
            ratioYrange = (0.5,1.5),
            inTITLE=inTITLE)
    #plt.savefig(outFIGname)
    #print(f'[fig output - LOG] {outFIGname}')
    #plt.close()



if __name__ == "__main__":
    csv_jetsel = '../step2.1.efficienciesCalc/UL2016PreVFP_DeepFlavour_gjetPythia_mergeBin5_cutIdx5/dat_jetSelections.csv'
    csv_phoreg = '../step2.1.efficienciesCalc/UL2016PreVFP_DeepFlavour_gjetPythia_mergeBin5_cutIdx5/dat_phoControlReg.csv'
    csv_presel = '../step2.1.efficienciesCalc/UL2016PreVFP_DeepFlavour_gjetPythia_mergeBin5_cutIdx5/dat_preselectionEfficiency.csv'
    import makeplot.file_collecter as inputs
    f1= inputs.FileWithDesc(
            file='DeepCSV_gjetPythia_cutIdx5_mergeBin_5/UL2016.CTag_SimulFit.csv',
            desc='Flight Distance > 5$\sigma$')
    f1M = inputs.FileWithDesc(
        file='/wk_cms3/ltsai/wk_cms/ltsai/github/MG5scripts/gjet_NLO_loop_sm_no_b_mass_NNPDF31_nlo_as_0118/MG5result_mcPredicted_leading_c.csv',
        desc='NNPDF3.1 intrinsic charm 5NFS, leading $\gamma+C$')
    #f2= inputs.FileWithDesc(
    #        file='DeepCSV_gjetPythia_cutIdx4_mergeBin_5/UL2016.CTag_SimulFit.csv',
    #        desc='Flight Distance > 3$\sigma$')
    #f3= inputs.FileWithDesc(
    #        file='DeepFlavour_gjetPythia_cutIdx5_mergeBin_5/UL2016.CTag_SimulFit.csv',
    #        desc='$\gamma$+c')
    #f4= inputs.FileWithDesc(
    #        file='DeepFlavour_gjetPythia_cutIdx4_mergeBin_5/UL2016.CTag_SimulFit.csv',
    #        desc='$\gamma$+c')

    def task(*draw_obj):
        the_title = 'differencial cross section of $\gamma$ + c channel'
        draw_obj[0].DrawSingle(f1,
                inTITLE=the_title,
            outFIGtemplate='DeepCSV_cutIdx5.pdf')
        draw_obj[1].DrawSingle(f1M,
                inTITLE=the_title,
            outFIGtemplate='DeepCSV_cutIdx5.pdf')
        outFIGname = 'DeepCSV_cutIdx5.pdf'
        plt.savefig(outFIGname)
        print(f'[fig output - LOG] {outFIGname}')
        plt.close()

    tag='UL2016PreVFP_data'
    task(
            DrawingProcess(draw_scatter_plot,hackDATAfunc=get_data_point,taG=tag),
            DrawingProcess(draw_scatter_plot,hackDATAfunc=get_data_point_MC,taG=tag) )

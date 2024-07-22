import ROOT as rt
import CMS_lumi, tdrstyle
import array


def example_plot(iPeriod, iPos,drawFUNC, funcARGs, canvNAME):
    #set the tdr style

    #change the CMS_lumi variables (see CMS_lumi.py)
    CMS_lumi.lumi_7TeV = "4.8 fb^{-1}"
    CMS_lumi.lumi_8TeV = "18.3 fb^{-1}"
    CMS_lumi.writeExtraText = 1
    CMS_lumi.extraText = "Preliminary"
    CMS_lumi.lumi_sqrtS = "13 TeV" # used with iPeriod = 0, e.g. for simulation-only plots (default is an empty string)

    if( iPos==0 ): CMS_lumi.relPosX = 0.12

    W_ref = 800;
    H_ref = 600;
    W = W_ref
    H  = H_ref

    # 
    # Simple example of macro: plot with CMS name and lumi text
    #  (this script does not pretend to work in all configurations)
    # iPeriod = 1*(0/1 7 TeV) + 2*(0/1 8 TeV)  + 4*(0/1 13 TeV) 
    # For instance: 
    #               iPeriod = 3 means: 7 TeV + 8 TeV
    #               iPeriod = 7 means: 7 TeV + 8 TeV + 13 TeV 
    #               iPeriod = 0 means: free form (uses lumi_sqrtS)
    # Initiated by: Gautier Hamel de Monchenault (Saclay)
    # Translated in Python by: Joshua Hardenbrook (Princeton)
    # Updated by:   Dinko Ferencek (Rutgers)
    #

    # references for T, B, L, R
    T = 0.08*H_ref
    B = 0.15*H_ref
    L = 0.15*W_ref
    R = 0.04*W_ref

    canvas = rt.TCanvas("c2","c2",50,50,W,H)
    canvas.SetFillColor(0)
    canvas.SetBorderMode(0)
    canvas.SetFrameFillStyle(0)
    canvas.SetFrameBorderMode(0)
    canvas.SetLeftMargin( L/W )
    canvas.SetRightMargin( R/W )
    canvas.SetTopMargin( T/H )
    canvas.SetBottomMargin( B/H )
    canvas.SetTickx(0)
    canvas.SetTicky(0)


    h1 = drawFUNC(funcARGs)
    #draw the lumi text on the canvas
    CMS_lumi.CMS_lumi(canvas, iPeriod, iPos)


    #update the canvas to draw the legend
    canvas.Update()
    canvas.RedrawAxis()
    canvas.GetFrame().Draw()

    canvas.SaveAs(canvNAME+".pdf")

class __func_args__:
    pass

def myplot(funcARGs):
    tdrstyle.setTDRStyle()

    h1 = rt.TH1F("h1","",100,0,10)
    rnd = rt.TRandom3()
    for a in range(100):
        h1.Fill( rnd.Rndm() * 10.)
    #SetTDRStyleToHist(h1)
    h1.GetYaxis().SetTitle("hiiii")
    h1.GetXaxis().SetTitle("kkkk")
    h1.Draw()
    return h1

if __name__ == "__main__":
    func_args = __func_args__
    ## second argument : iPos 11:mark left, 12:mark center, 13:mark right
    example_plot(20160, 11, myplot, func_args, 'hi')

from link_fityield import *
def args(argv):
    if len(argv) < 4:
        print 'use default binning ( pEta0, jEta0, pPt3 )'
        return (0,0,3)
    v1=int(argv[1])
    v2=int(argv[2])
    v3=int(argv[3])
    pEta = v1 if v1 < 2 else 0
    jEta = v2 if v2 < 2 else 0
    pPt  = v3 if v3 <21 else 3
    return (pEta,jEta,pPt)

if __name__ == "__main__":
    import sys
    LogMgr.InitLogger(level='info')
    mylog=LogMgr.GetLogger(__name__)
    ROOT.RooMsgService.instance().setGlobalKillBelow(ROOT.RooFit.ERROR)
    infile=ROOT.TFile.Open('isovsbdt_template.root')

    space=FittingWorkspace()

    space.factory('BDTscore[-1.,1.]')
    var=space.var('BDTscore')
    space.SetVar('BDTscore')


    phoeta,jeteta,phopt = args(sys.argv)
    if True:
                mylog.debug('indexes are pEta:%d jEta:%d pPt:%d' % (phoeta,jeteta,phopt) )
                sigbin=MyBin(phopt, phoeta, jeteta)
                #bkgpt = phopt if phopt < 17 else 17
                bkgpt = phopt if phopt < 19 else 19
                bkgbin=MyBin(bkgpt, phoeta, jeteta)

                mylog.debug( 'status 01: Loading hists from file.' )
                print('data_%d_%d_%d_px1_chIso'%(phoeta,jeteta,phopt))
                print( infile.Get('data_%d_%d_%d_px1_chIso'%(phoeta,jeteta,phopt)).GetName() )

                h_data=infile.Get('data_%d_%d_%d_px1_chIso'%(phoeta,jeteta,phopt))
                h_sig =infile.Get( sigbin.naming('gjet_%d_%d_%d_px1_chIso') )
                h_bkg =infile.Get( bkgbin.naming('data_%d_%d_%d_px2_chIso') )

                if h_data.GetNbinsX() > 10 : h_data.Rebin(10)
                if h_sig .GetNbinsX() > 10 : h_sig.Rebin(10)
                if h_bkg .GetNbinsX() > 10 : h_bkg.Rebin(10)
                for ibin in range(1,h_data.GetNbinsX()+1):
                    h_data.SetBinError( ibin,
                            h_data.GetBinContent(ibin)*0.7 )
                            #( h_data.GetBinError(ibin)**2 + h_sig.GetBinError(ibin)**2 )**0.5 )

                mylog.debug( 'status 03: Creating datahist' )
                fitsources_data=ROOT.RooDataHist( sigbin.naming('dh_data.%d_%d_%d'), '', ROOT.RooArgList(var), h_data)
                space.myImport( fitsources_data )
                space.SetFitTarget( fitsources_data )


                mylog.debug( 'status 04: To fitting function' )
                pdfnames=space.TwoComponentsFit( sigbin,
                        h_sig, h_bkg,
                        )

                mylog.debug( 'status 05: Drawing output plots' )
                space.DrawFitRes( sigbin, sigbin.naming('plots/checking_%d_%d_%d.pdf'),pdfnames )
                mylog.debug( 'status ended: finished of a loop node')

    mylog.info('start writing fit fragments to root file')
    space.myWriteSpace('fitres_workspace.root')
    del space
    mylog.info('job finished')

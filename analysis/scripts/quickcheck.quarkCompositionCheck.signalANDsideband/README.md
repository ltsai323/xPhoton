Here is to get b/c/L quark composition.
* qcdCHECKER_plotQuarkCompositionSep_differentSelection.C
Histogram creation. Use "Draw" and cut strings to get histograms.
Currently this code selects:
 1. Draw jetPt spectrum
 2. Under selections :
   - Basic xPhoton/MakeHisto selection in signal photon region.
   - Basic xPhoton/MakeHisto selection in sideband photon region.
   - Basic photon selection and genHT selection in addition in signal photon region.
   - Basic photon selection and genHT selection in addition in sideband photon region;

* qcdCHECKER_generalDrawing.C
Vistualize histogram as figures.
 1. Draw bComposition / cComposition / LComposition in separate figure.
 2. Convert histogram to TGraph.


Directly check QCD sample without any selection.
The only selection is to make sure event contains leading jet.

* qcdCHECKER_interestingHIST.C
Generate histogram by "Draw" and cut strings.
Separate ptbin and HT-slices. This code helps me to know where the spike comes from.

 - mcweight spectrum in each jet pt bin. (which is used to check the composition of each HT-slices in a pt bin).
 - jetpt spectrum of b/c/L yields in each HT-slices.

* qcdCHECKER_plotHTSlicesComposition.C
Normalize sum of yields from each HT-slices. So yield becomes composition.
Draw jet pt spectrum with mcweight in all HT-slices.

* qcdCHECKER_plotMCWeightComposition.C
Check yield compositions with mcweight in each pt bin.
 - Load mcweight spectrum from each HT slices and each pt bin.
 - Collect 1 pt bin and draw mcweight spectrum in all HT-slices.
 
* qcdCHECKER_plotQuarkComposition.C
Normalize sum of quark yields into 1. So quark yields becomes quark composition.
Draw quark composition plots in a stack plot. Use filled color and all compositions.
Such that the y axis is always from 0 to 1.


* qcdCHECKER_jetPtBinCutDecider.C
Use different algorithm to decide pt bin threshold at each HT-slices.
To prevent too large weight from PU.


* qcdCHECKER_histTOcheckCUTs.C
The accomplished version as qcdCHECKER_interestingHIST.C. 
 - Add cuts from qcdCHECKER_jetPtBinCutDecider.C
 - Folders to compare different cuts.
* qcdCHECKER_plotQuarkCompositionSep_differentSelection.C
The accomplished version as qcdCHECKER_plotQuarkComposition.C.
 - Separate drawing to each quark composition.
 - Compare quark composition spectrum in each selections.

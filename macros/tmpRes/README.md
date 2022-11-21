# checking region
Check the reason why UL2018 gives a 1.2x signal photon contribution.
2016 ReReco and 2015 are similar.

* [ ] Original : use calib_mva and calib_chIso
* [x] 1st trial : use chIsoRaw
 - Contidion remains
* [x] 2nd trial : use chIso and use 2016ReReco
 - Condition remains
* [x] 3rd trial : use chIso and use 2016ReReco in previous sample
 - Barrel photon is good. But endcap photon failed.
* [x] 4th trial : Use recoSCEta to define EB/EE region.
 - The figure becomes extremely weird.
* [x] 5th trial : Back to use xsweight instead of mcweight, And use bin 4 for separate signal region in data.
 - The endcap situation kept
* [x] 6th trial : use bin 5 for separate signal region in endcap.
 - The endcap situation kept
* [x] 7th trial : Try not to update error bar in MC sample.
 - Nothing changed.
* [x] 8th trial : Try to disable if(ebee==1 && HoverE < 0.01 && chIsoRaw<2&& mva>0.35 && eleVeto==1 )
 - endcap has enormous improvement! but there needed some further cuts.
* [x] 9th trial : Try to disable pt/MET <0.7 cut
 - lot pt region failed.
* [x] 10th trial: Use new code
 - Behave exactly the same as old code!
* [x] 11st trial: Use newer root file
 - Huge difference! new data contains lots of photon!!! Need to check xPhotonHFJet.cc
* [ ] 12nd trial: I doubt that new processed 2016 data sample is all photon, not only leading photon
 - pending
* [x] 13rd trial: Try to apply eleVeto in new processed xPhoton
 - FINISHEDDDDDD!!!!!! IT's OK NOWWWWWWW

## Conclusion
* disable if(ebee==1 && HoverE < 0.01 && chIsoRaw<2&& mva>0.35 && eleVeto==1 )
* apply eleVeto cut
* For the most previous version, the 16/15 comparison in endcap also have the decay tendency.

## Use 2016ReReco to find the difference in calib_chIso
* [x] 16.1st   : Use 2016 new processed data and calib_chIso!
 - nothing changed.
* [x] 16.2nd   : Use mcweight instead of xsweight
 - nothing changed.
* [x] 16.3rd   : Use sideband region 3.5~10 (EB) and 3~10 (EE)
 - perfectly match old result.
* [x] 16.4th   : Use sideband region 7~13 (EB) and 6~12 (EE)
 - ONLY for last 2 pt bins, the fitting reports higher yields (1.2x) at modified sideband region.
* [x] 16.5th   : Previous signal region and sideband region are wrong. Corrected.
 - Barrel photon region. The 16/15 comparison is better. But endcap comparison is bad.
* [x] 16.6th   : Not to put eleVeto cut again.
 - All plots comes to very bad!!
* [x] 16.7th   : The signal region of EE changed to 0~2!
 - Endcap photon is bad.
 - Even if signal region of endcap is opened to 0~2. This just multiplied a factor to original yield. The negative slope kept its tendency.
* [x] 16.8th   : stable version:
 - data: use recoPtCalib and calib_chIso.
 - mc  : use recoPt and chIsoRaw.
 - signal region   : 0~2 for EB and 0~1.5 for EE.
 - sideband region : 7~13 for EB and 6~12 for EE.
 - eleVeto used.
 - No HLT used.
 - Use JetY to separate jet eta bin.
 - Known issue : barrel photon fit is good. But endcap photon fit has a negative slope. (and a bump at endcap jet.)
 - [Issue] Cannot find problem in endcap. What causes this slope?
* [x] 16.9th   : Disable photonpt / MET cut to see whether the vanished yield recovers or not. (A pt dependency is found on yield comparison especially at endcap photon region.)
 - The main difference is only applied on low pt region. So this is not able to resolve the pt dependency.
* [x] 16.10th  : Modify the fidicuial region definition and a sieie cut in paper used. Detail: 1.4442 < recoSCEta < 1.566 and recoSCEta > 2.5 are removed, instead of use recoEta. sieie < 0.012(0.027) in EB(EE).
 - Small variation.
* [x] 16.11st  : Use all photon instead of leading photon.
 - Small variation. But the EE tendency is the same.
* [x] 16.12nd  : regard all fake as signal photon. Check whether the yield fits 2015 result or not
 - The pt dependency kept and most of binnning still lower than 2015. So it seems to be the issue of selection.
* [x] 16.13rd  : Disable all selections in step2
 - The pt dependency kept. But the lowest part is almost 1.
* [x] 16.14th  : Retrieve eleVeto / sieie / HoverE cuts
* [x] 16.15th  : Retrieve HLT / fiucial region / MET/Pt cuts.
* [x] 16.16th  : Active all cut except eleVeto cut.
 - No comment...
* [x] 16.17th  : effective luminosity is put at each binning at each HLT. Select only 1 HLT at 1 binning.
 - The exponential shape is good except for the boundary of pre-scale and non pre-scale region.
* [x] 16.18th  : Select HLT not due to event passed. Use trigger turn on curve and pt distribution (While turn on curve failed).
 - Somehow the second bin has very large cross section
 - Other binning are very GOOOOOOOOOD.
* [ ] 16.19th  : Optimize pt binning.
## Turn to use UL2018.
* [x] 18.1st   : Use 2018 data
 - Endcap is good. But lots of additional data in barrel region.
 - for low pt region, 2016 and 2018 behaves different. I thought it is coming from pre-scale
* [ ] 18.2nd   : Use 2018 data. After check of 16.11st. Something strange at endcap photon. Checking whether it is a dataset related feature.
## HLT bit check.
* [ ] HLTbit.1st : Bin 13 and 14 seems not to apply HLT300. Try to use lower bit.

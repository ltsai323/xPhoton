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

## Use 2016ReReco to find the difference in calib_chIso
* [x] 16.1st   : Use 2016 new processed data and calib_chIso!
 - nothing changed.
* [x] 16.2nd   : Use mcweight instead of xsweight
 - nothing changed.
* [x] 16.3rd   : Use sideband region 3.5~10 (EB) and 3~10 (EE)
 - perfectly match old result.
* [x] 16.4th   : Use sideband region 7~13 (EB) and 6~12 (EE)
 - ONLY for last 2 pt bins, the fitting reports higher yields (1.2x) at modified sideband region.
EE : a turn on at low pt region? ~175
EB : 0.9 efficiency.
## Turn to use UL2018.
* [x] 18.1st   : Use 2018 data
 - Endcap is good. But lots of additional data in barrel region.
 - for low pt region, 2016 and 2018 behaves different. I thought it is coming from pre-scale

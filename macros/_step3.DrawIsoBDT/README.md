run.sh : runable
test.sh : process it at specific bin and make a comparison in old and new file.
fakerun.sh : process all bins in fake sample.
fullrun.sh : execute run.sh and tidy up such that the process can be fully processed in each step.

Project histogram into signal region and sideband region.
The signal region is named 'px1_chIso' and sideband region is named 'px2_chIso'.
Where the definition of signal region is chIsoRaw<2 and sideband is chIsoRaw>5 and chIsoRaw<15.
'all' tags is the original distributions.

List of variables and histograms in each phoEta_jetEta_phoPt bins:
* MVA score :
    - `{SourceName}_pEtaBin_jEtaBin_pPtBin_px1_chIso`
    - `{SourceName}_pEtaBin_jEtaBin_pPtBin_px2_chIso`
    - `{SourceName}_pEtaBin_jEtaBin_pPtBin_all`
* jetDeepCSVDiscriminatorTags_BvsAll :
    - `{SourceBin}_btagDeepCSV.{SystType}_0_{JetFlavourBin}__pEtaBin_jEtaBin_pPtBin__{phoMatchStatus}_{parity}`
* jetDeepCSVDiscriminatorTags_CvsL   :
    - `{SourceBin}_btagDeepCSV.{SystType}_1_{JetFlavourBin}__pEtaBin_jEtaBin_pPtBin__{phoMatchStatus}_{parity}`
* jetDeepCSVDiscriminatorTags_CvsB   :
    - `{SourceBin}_btagDeepCSV.{SystType}_2_{JetFlavourBin}__pEtaBin_jEtaBin_pPtBin__{phoMatchStatus}_{parity}`
* jetSubVtxMass                      :
    - `{SourceBin}_btagDeepCSV.{SystType}_3_{JetFlavourBin}__pEtaBin_jEtaBin_pPtBin__{phoMatchStatus}_{parity}`


- SourceName : 'gjet', 'data', 'qcd'. Notice that this is a string, not an integer.
- JetFlavourBin : 0 = lightJet, 1 = cJet, 2 = bJet
- phoMatchStatus : No comment
- parity : No Comment
